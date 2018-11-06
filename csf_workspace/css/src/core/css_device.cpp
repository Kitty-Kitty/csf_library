/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_device.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:26
*
*Description: Class(css_device)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_device.hpp"

using css::core::css_device;


css_device::css_device() {

}



css_device::~css_device() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_device::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示发送一个message内容
 * 
 * @param message    表示添加的消息内容
 */
csf_int32 css_device::post(csf_message& message) {

	return 0;
}


/**
 * 根据类型、回调函数和信息内容创建消息
 * 
 * @param type    表示消息类型
 * @param callback    表示回调函数
 * @param element    表示消息内容
 */
csf_int32 css_device::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_device::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示弹出消息内容
 */
csf::core::system::message::csf_message css_device::pop() {

	return  csf_nullptr;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_device::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示连接工厂管理器
 */
csf_connect_factory_manager& css_device::get_connect_factory_manager() {

	return m_connect_factory_manager;
}


/**
 * 表示连接工厂管理器
 * 
 * @param newVal
 */
csf_void css_device::set_connect_factory_manager(csf_connect_factory_manager& newVal) {

	m_connect_factory_manager = newVal;
}


/**
 * 根据类型、回调函数和信息内容创建消息
 * 
 * @param type    表示消息类型
 * @param callback    表示回调函数
 * @param element    表示消息内容
 */
csf_int32 css_device::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * 表示发送一个message内容
 * 
 * @param message    表示添加的消息内容
 */
csf_int32 css_device::post(const csf_message& message) {

	return 0;
}


/**
 * 表示弹出消息内容
 */
csf::core::system::message::csf_message css_device::pop() {

	return  csf_nullptr;
}