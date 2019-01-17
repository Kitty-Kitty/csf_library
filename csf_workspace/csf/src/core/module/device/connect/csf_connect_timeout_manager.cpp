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

	csf_int32															tmp_count = 0;
	csf_map<csf_connect_timeout*, csf_connect_wrapper>::iterator		tmp_iter;


	timeout.set_expired();
	{
		csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

		//查询容器中是否存在需要的key对象，如果存在则接着查询相似对象，遍历处理
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
* 主要功能是：超时线程处理函数接口
* 返回：无
*/
csf_void csf_connect_timeout_manager::expired_process_cycle() {

	static csf_connect_timeout									tmp_timeout;
	csf_connect_wrapper											tmp_wrapper(m_null_connect_ptr, tmp_timeout);
	csf::core::module::connect::csf_connect_callback			tmp_callback = csf_nullptr;
	csf_map<csf_connect_timeout*, csf_connect_wrapper>::iterator		tmp_iter;
	csf_uint64													tmp_time = csf::core::utils::time::system_time::get_time();


	//获取一个需要处理的connect_wrapper对象
	{
		csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

		//从队列中获取数值最小的，并且判断是否过期。过期则进行处理
		tmp_iter = get_connect_collector().begin();
		if (tmp_iter == get_connect_collector().end()) {

			csf_msleep((csf_uint32)get_idle_interval());

			return;
		}
		
		//如果时间为0表示未配置，则配置一个时间。更新节点信息，等待不次超时处理。
		if (0 == tmp_iter->second.get_timeout().get_time()) {

			tmp_wrapper = tmp_iter->second;
			tmp_wrapper.get_timeout().set_time(tmp_time);

			get_connect_collector().erase(tmp_iter++);
			get_connect_collector().insert(
				csf_map<csf_connect_timeout*, csf_connect_wrapper>::value_type(
					&(tmp_wrapper.get_timeout()), tmp_wrapper));

			return;
		}

		//判断过期则对相应的连接对象进行处理
		if (!tmp_iter->second.get_timeout().is_expired(tmp_time)) {

			//如果当前队列的key值
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

			//这里取出过期对象进行处理
			tmp_wrapper = tmp_iter->second;
			get_connect_collector().erase(tmp_iter++);
		}
	}

	if (tmp_wrapper.get_connect_ptr() != m_null_connect_ptr) {

		//对相应的过期对象进行处理。
		//如果超时对象中的回调函数不为空，则调用回调函数进行处理。
		//如果没有回调函数，则直接关闭连接处理
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