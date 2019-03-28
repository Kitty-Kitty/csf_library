/*******************************************************************************
*
*Copyright: fangzhenmu
*
*Author: fangzhenmu
*
*File name: csf_request_manager.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:57
*
*Description: Class(csf_request_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_request_manager.hpp"

using csf::core::service::csf_request_manager;


csf_request_manager::csf_request_manager() {

}



csf_request_manager::~csf_request_manager() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_request_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_request_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_request_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}