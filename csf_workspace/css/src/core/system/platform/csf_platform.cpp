/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_platform.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:47
*
*Description: Class(csf_platform)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_platform.hpp"

using csf::core::system::platform::csf_platform;


csf_platform::csf_platform() {

}



csf_platform::~csf_platform() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_platform::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_platform::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 
 * @param type
 */
csf::core::base::csf_void csf_platform::csf_module(csf::core::module::csf_module_type type) {

}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_platform::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块的类型
 * 
 * @param new_value
 */
csf::core::base::csf_void csf_platform::set_type(csf::core::module::csf_module_type new_value) {

	m_type = newVal;
}