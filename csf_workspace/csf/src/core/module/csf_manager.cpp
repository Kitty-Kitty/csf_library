/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:43
*
*Description: Class(csf_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_manager.hpp"

using csf::core::module::csf_manager;


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}