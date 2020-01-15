/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:51
*
*Description: Class(csf_task_manager) 表示任务管理器
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_task_manager.hpp"

using csf::core::utils::task::csf_task_manager;


csf_task_manager::csf_task_manager()
	: m_configure_manager(csf_null)
	, m_status(csf_task_status_none) {

}



csf_task_manager::~csf_task_manager() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_task_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_task_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_task_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}