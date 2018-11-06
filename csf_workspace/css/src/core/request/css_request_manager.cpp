/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_request_manager.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:30
*
*Description: Class(css_request_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_request_manager.hpp"

using css::core::css_request_manager;


css_request_manager::css_request_manager() {

}



css_request_manager::~css_request_manager() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_request_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_request_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_request_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示线程处理函数，主要从队列中获取请求进行处理
 */
csf_void css_request_manager::process() {

}