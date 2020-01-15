/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_times_task.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:52
*
*Description: Class(csf_times_task) 表示指定次数的任务，用于记录次数
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_times_task.hpp"

using csf::core::utils::task::csf_times_task;


csf_times_task::csf_times_task()
	: m_sequence(0)
	, m_times(0) {

}



csf_times_task::~csf_times_task() {

}





/**
 * 表示处理接口，当只有is_process返回true后才能process。
 */
csf_int32 csf_times_task::process() {

	return 0;
}


/**
 * 表示是否进行处理,如果is_process返回true，才能执行process。
 */
csf_bool csf_times_task::is_process() {

	return csf_true;
}


/**
 * 判断是否需要删除，如果is_delete返回true则删除task。
 */
csf_bool csf_times_task::is_delete() {

	return csf_true;
}