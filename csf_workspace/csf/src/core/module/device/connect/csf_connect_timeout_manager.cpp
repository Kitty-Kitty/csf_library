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

	csf_int32															tmp_count = 0;
	csf_map<csf_connect_timeout*, csf_connect_wrapper>::iterator		tmp_iter;


	timeout.set_expired();
	{
		csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

		//��ѯ�������Ƿ������Ҫ��key���������������Ų�ѯ���ƶ��󣬱�������
		tmp_iter = get_connect_collector().find(&timeout);
		if (tmp_iter == get_connect_collector().end()) {
			return csf_succeed;
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

	static csf_connect_timeout									tmp_timeout;
	csf_connect_wrapper											tmp_wrapper(m_null_connect_ptr, tmp_timeout);
	csf::core::module::connect::csf_connect_callback			tmp_callback = csf_nullptr;
	csf_map<csf_connect_timeout*, csf_connect_wrapper>::iterator		tmp_iter;
	csf_uint64													tmp_time = csf::core::utils::time::system_time::get_time();


	//��ȡһ����Ҫ�����connect_wrapper����
	{
		csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

		//�Ӷ����л�ȡ��ֵ��С�ģ������ж��Ƿ���ڡ���������д���
		tmp_iter = get_connect_collector().begin();
		if (tmp_iter == get_connect_collector().end()) {

			csf_msleep((csf_uint32)get_idle_interval());

			return;
		}
		
		//���ʱ��Ϊ0��ʾδ���ã�������һ��ʱ�䡣���½ڵ���Ϣ���ȴ����γ�ʱ����
		if (0 == tmp_iter->second.get_timeout().get_time()) {

			tmp_wrapper = tmp_iter->second;
			tmp_wrapper.get_timeout().set_time(tmp_time);

			get_connect_collector().erase(tmp_iter++);
			get_connect_collector().insert(
				csf_map<csf_connect_timeout*, csf_connect_wrapper>::value_type(
					&(tmp_wrapper.get_timeout()), tmp_wrapper));

			return;
		}

		//�жϹ��������Ӧ�����Ӷ�����д���
		if (!tmp_iter->second.get_timeout().is_expired(tmp_time)) {

			//�����ǰ���е�keyֵ
			if (tmp_iter->second.get_timeout().get_time() > tmp_time) {

				tmp_wrapper = tmp_iter->second;

				get_connect_collector().erase(tmp_iter++);
				get_connect_collector().insert(
					csf_map<csf_connect_timeout*, csf_connect_wrapper>::value_type(
						&(tmp_wrapper.get_timeout()), tmp_wrapper));
			}

			csf_msleep((csf_uint32)get_idle_interval());
			
			return;
		}
		else {

			//����ȡ�����ڶ�����д���
			tmp_wrapper = tmp_iter->second;
			get_connect_collector().erase(tmp_iter++);
		}
	}

	if (tmp_wrapper.get_connect_ptr() != m_null_connect_ptr) {

		//����Ӧ�Ĺ��ڶ�����д���
		//�����ʱ�����еĻص�������Ϊ�գ�����ûص��������д���
		//���û�лص���������ֱ�ӹر����Ӵ���
		tmp_callback = tmp_wrapper.get_timeout().get_handle();
		if (tmp_callback) {
			csf_connect_error	tmp_error;

			tmp_error.set_error(csf_connect_error::csf_connect_code::csf_connect_code_timeout
				, "connect[0x%x] timeout."
				, tmp_wrapper.get_connect_ptr().get());

			tmp_callback(tmp_wrapper.get_connect_ptr(), tmp_error);
		}
		else {
			tmp_wrapper.get_connect_ptr()->close();
		}
	}
}