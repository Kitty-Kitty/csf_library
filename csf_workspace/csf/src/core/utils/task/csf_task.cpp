/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:50
*
*Description: Class(csf_task) 表示定时任务
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_task.hpp"

using csf::core::utils::task::csf_task;


csf_task::csf_task()
	: m_type(csf_task_type_none)
	, m_status(csf_task_status_none)
	, m_callback(csf_null)
	, m_delete_callback(csf_null)
	, m_time(0)
	, m_offset(0)
	, m_decorator(csf_null)
	, m_interval(0)
	, m_task_manager(csf_null) {

}



csf_task::~csf_task() {

}





/**
 * 根据task的类型和类型创建一个任务
 * 
 * @param manager    表示任务管理器的地址
 * @param type    表示类型数值
 * @param offset    表示任务间隔时间
 * @param interval    任务执行的间隔时间
 * @param callback    任务的执行回调函数
 * @param delete_callback    任务删除的执行回调函数
 */
csf_task::csf_task(const csf_task_manager* manager, const csf_task_type type, const csf_time offset, const csf_time interval, const csf_task_callback callback, const csf_task_delete_callback delete_callback) {

}


/**
 * 表示处理接口，当只有is_process返回true后才能process。
 */
csf_int32 csf_task::process() {

	return 0;
}


/**
 * 表示是否进行处理,如果is_process返回true，才能执行process。
 */
csf_bool csf_task::is_process() {

	return csf_true;
}


/**
 * 判断是否需要删除，如果is_delete返回true则删除task。
 */
csf_bool csf_task::is_delete() {

	return csf_true;
}


/**
 * 表示任务所属的任务管理器
 */
csf_task_manager* csf_task::get_task_manager() {

	return m_task_manager;
}


/**
 * 表示任务所属的任务管理器
 * 
 * @param newVal
 */
void csf_task::set_task_manager(const csf_task_manager* newVal) {

	m_task_manager = newVal;
}


/**
 * 表示处理接口，当只有is_delete返回true后才能process_delete。
 */
csf_int32 csf_task::process_delete() {

	return 0;
}