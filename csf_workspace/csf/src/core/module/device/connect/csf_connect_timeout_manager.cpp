/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_connect_timeout_manager.hpp
*
*Version: 1.0
*
*Date: 04-11��-2018 10:44:37
*
*Description: Class(csf_connect_timeout_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_connect_timeout_manager.hpp"
#include "system_time.hpp"

using csf::core::module::connect::csf_connect_timeout_manager;


csf_connect_timeout_manager::csf_connect_timeout_manager()
	: m_idle_interval(csf_connect_timeout_process_idle_interval_ms) {

}



csf_connect_timeout_manager::~csf_connect_timeout_manager() {

}


/**
* ��Ҫ�����ǣ��������������Ƴ�һ�������Ӷ��󣬸�ɾ������ֻ�ǽ���������Ϊ������ʱ��������ֱ�ӵ�ɾ��������������ɾ����Ҫ�ȴ���ʱ������ɡ�
* ���أ�0��ʾ�ɹ���ȡ���Ӷ��󣻷�0��ʾ����
*
* @param timeout    ��ʾɾ���ĳ�ʱ����
*/
csf_int32 csf_connect_timeout_manager::remove(csf_connect_timeout& timeout) {

	csf_int32																tmp_count = 0;
	csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::iterator		tmp_iter;


	timeout.set_expired();
	{
		csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

		//��ѯ�������Ƿ������Ҫ��key���������������Ų�ѯ���ƶ��󣬱�������
		tmp_iter = get_connect_collector().find(&timeout);
		if (tmp_iter == get_connect_collector().end()) {
			return csf_failure;
		}
		else {
			get_connect_collector().erase(tmp_iter++);
		}
	}

	return csf_succeed;
}


/**
* ��Ҫ�����ǣ���ʱ�̴߳������ӿ�
* ���أ���
*/
csf_void csf_connect_timeout_manager::expired_process_cycle() {

	csf_connect_wrapper_ptr										tmp_wrapper;
	csf_int32													tmp_cycle_times = 0;				//��ʾ���δ�����Ҫ�����ĸ���


	//�ô�����һ�����̷߳�ʽ���еģ�����ÿ���̵߳�ǰ���������������㹫ʽΪ��
	//��ǰ��������=(��ǰ���������� + �߳�����) / �߳�������
	//������ҪĿ���ǣ�
	//1����֤�����̶߳�����ִ��һ�Σ�
	//2����ǰ���������� / �߳�����  ���������������������ݾ�Զ��������
	tmp_cycle_times = (get_connect_queue().size() + get_thread_pool().get_thread_number()) / get_thread_pool().get_thread_number();
	for (csf_int32 i = 0; i < tmp_cycle_times; i++) {

		if (!get_connect_queue().pop_front(tmp_wrapper)) {
			//���ȡ��ǰ��һ��ʧ�ܣ���Ĭ�϶�����û�пɴ�����������
			//һ�ֿ����Ǳ������̴߳�����
			csf_msleep((csf_uint32)get_idle_interval());

			return;
		}

		process_connect_wrapper(tmp_wrapper);
	}

	//������У���������ߴ���
	csf_msleep((csf_uint32)get_idle_interval());
}


/**
* ��Ҫ�����ǣ�
*    ���ָ����connect_wrapper�����Ƿ�ʱ�Ĵ���
* ���أ���
*
* @param wrapper    ��ʾ��ǰ��Ҫ���������Ӷ���
*/
csf_void csf_connect_timeout_manager::process_connect_wrapper(csf_connect_wrapper_ptr& wrapper) {

	csf::core::module::connect::csf_connect_callback	tmp_callback = csf_nullptr;
	csf_uint64											tmp_time = 0;
	csf_bool											tmp_is_timeout = csf_false;


	if (csf_nullptr == wrapper.get()) {
		return;
	}

	//����һ�µ�ǰʱ�䣬�����ж��Ƿ�ʱ
	tmp_time = csf::core::utils::time::system_time::get_time();

	//���ʱ��Ϊ0��ʾδ���ã�������һ��ʱ�䡣���½ڵ���Ϣ���ȴ����γ�ʱ����
	if (0 == wrapper->get_timeout().get_time()) {

		wrapper->get_timeout().set_time(tmp_time);
		get_connect_queue().push_back(wrapper);
		//remove(wrapper->get_timeout());
		return;
	}

	//�жϹ��������Ӧ�����Ӷ�����д���
	if (!wrapper->get_timeout().is_expired(tmp_time)) {
		get_connect_queue().push_back(wrapper);
		return;
	}
	else {

		//����ȡ�����ڶ�����д���
		if (csf_succeed == remove(wrapper->get_timeout())) {
			tmp_is_timeout = csf_true;
		}
		else {
			tmp_is_timeout = csf_false;
		}
	}

	if (wrapper->get_connect_ptr() != m_null_connect_ptr) {

		if (csf_false == tmp_is_timeout) {
			wrapper->get_connect_ptr()->close();
			return;
		}

		//����Ӧ�Ĺ��ڶ�����д���
		//�����ʱ�����еĻص�������Ϊ�գ�����ûص��������д���
		//���û�лص���������ֱ�ӹر����Ӵ���
		tmp_callback = wrapper->get_timeout().get_handle();
		if (csf_nullptr == tmp_callback) {
			wrapper->get_connect_ptr()->close();
			return;
		}

		csf_connect_error	tmp_error;

		tmp_error.set_error(csf_connect_error::csf_connect_code::csf_connect_code_timeout
			, "timeout[%lld ms]"
			, wrapper->get_timeout().get_timeout());

		csf_log_ex(warning
			, csf_log_code_warning
			, "connect[%p] %s"
			, wrapper->get_connect_ptr().get()
			, tmp_error.to_string().c_str());

		try {
			tmp_callback(wrapper->get_connect_ptr(), tmp_error);
		}
		catch (std::exception &e) {
			csf_log_ex(error
				, csf_log_code_error
				, "timeout manager exception[%s]"
				, e.what());
		}
	}
}