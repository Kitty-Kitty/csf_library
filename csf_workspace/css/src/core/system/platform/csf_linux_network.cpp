/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_linux_network.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:42
*
*Description: Class(csf_linux_network)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_linux_network.hpp"

using csf::core::system::platform::csf_linux_network;


csf_linux_network::csf_linux_network() {

}



csf_linux_network::~csf_linux_network() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_linux_network::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_linux_network::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_linux_network::stop(const csf_configure_manager * conf_mg) {

	return 0;
}