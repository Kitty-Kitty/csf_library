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
*Date: 04-11月-2018 10:44:37
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
* 主要功能是：从连接容器中移除一个的连接对象，该删除操作只是将连接设置为立即超时，而不是直接的删除操作。真正的删除需要等待超时处理完成。
* 返回：0表示成功获取连接对象；非0表示错误；
*
* @param timeout    表示删除的超时对象
*/
csf_int32 csf_connect_timeout_manager::remove(csf_connect_timeout& timeout) {

	csf_int32																tmp_count = 0;
	csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::iterator		tmp_iter;


	timeout.set_expired();
	{
		csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

		//查询容器中是否存在需要的key对象，如果存在则接着查询相似对象，遍历处理
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
* 主要功能是：超时线程处理函数接口
* 返回：无
*/
csf_void csf_connect_timeout_manager::expired_process_cycle() {

	csf_connect_wrapper_ptr										tmp_wrapper;
	csf_int32													tmp_cycle_times = 0;				//表示本次处理需要遍历的个数


	//该处理是一个多线程方式进行的，所以每个线程当前处理任务数量计算公式为：
	//当前处理数量=(当前的总连接数 + 线程数量) / 线程数量；
	//其中主要目的是：
	//1、保证所有线程都至少执行一次；
	//2、当前的总连接数 / 线程数量  不整除导致最后的连接数据久远不被处理
	tmp_cycle_times = (get_connect_queue().size() + get_thread_pool().get_thread_number()) / get_thread_pool().get_thread_number();
	for (csf_int32 i = 0; i < tmp_cycle_times; i++) {

		if (!get_connect_queue().pop_front(tmp_wrapper)) {
			//如果取最前的一个失败，则默认队列中没有可处理连接数据
			//一种可能是被其他线程处理了
			csf_msleep((csf_uint32)get_idle_interval());

			return;
		}

		process_connect_wrapper(tmp_wrapper);
	}

	//如果空闲，则进行休眠处理
	csf_msleep((csf_uint32)get_idle_interval());
}


/**
* 主要功能是：
*    针对指定的connect_wrapper进行是否超时的处理
* 返回：无
*
* @param wrapper    表示当前需要被处理连接对象
*/
csf_void csf_connect_timeout_manager::process_connect_wrapper(csf_connect_wrapper_ptr& wrapper) {

	csf::core::module::connect::csf_connect_callback	tmp_callback = csf_nullptr;
	csf_uint64											tmp_time = 0;
	csf_bool											tmp_is_timeout = csf_false;


	if (csf_nullptr == wrapper.get()) {
		return;
	}

	//更新一下当前时间，用于判断是否超时
	tmp_time = csf::core::utils::time::system_time::get_time();

	//如果时间为0表示未配置，则配置一个时间。更新节点信息，等待不次超时处理。
	if (0 == wrapper->get_timeout().get_time()) {

		wrapper->get_timeout().set_time(tmp_time);
		get_connect_queue().push_back(wrapper);
		//remove(wrapper->get_timeout());
		return;
	}

	//判断过期则对相应的连接对象进行处理
	if (!wrapper->get_timeout().is_expired(tmp_time)) {
		get_connect_queue().push_back(wrapper);
		return;
	}
	else {

		//这里取出过期对象进行处理
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

		//对相应的过期对象进行处理。
		//如果超时对象中的回调函数不为空，则调用回调函数进行处理。
		//如果没有回调函数，则直接关闭连接处理
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