/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_windows_platform.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:54
*
*Description: Class(csf_windows_platform)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_windows_platform.hpp"

using csf::core::system::platform::csf_windows_platform;


csf_windows_platform::csf_windows_platform() {

}



csf_windows_platform::~csf_windows_platform() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_windows_platform::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_windows_platform::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_windows_platform::stop(const csf_configure_manager * conf_mg) {

	return 0;
}