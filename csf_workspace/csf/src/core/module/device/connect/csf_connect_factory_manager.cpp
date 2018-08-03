/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 28-7月-2018 14:23:34
*
*Description: Class(csf_connect_factory_manager) 表示连接工厂管理器
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_connect_factory_manager.hpp"

using csf::core::module::connect::csf_connect_factory_manager;


csf_connect_factory_manager::csf_connect_factory_manager() {

}



csf_connect_factory_manager::~csf_connect_factory_manager() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect_factory_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect_factory_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect_factory_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}
