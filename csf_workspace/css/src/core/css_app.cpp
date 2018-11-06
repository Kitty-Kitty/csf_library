/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_app.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:25
*
*Description: Class(css_app)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_app.hpp"

using css::core::css_app;


css_app::css_app() {

}



css_app::~css_app() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_app::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_app::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 css_app::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


csf_message_manager& css_app::get_message_manager() {

	return m_message_manager;
}


/**
 * 
 * @param newVal
 */
void css_app::set_message_manager(csf::core::system::message::csf_message_manager newVal) {

	m_message_manager = newVal;
}


/**
 * 表示发送一个message内容
 * 
 * @param message    表示添加的消息内容
 */
csf_int32 css_app::post(csf_message& message) {

	return 0;
}


/**
 * 根据类型、回调函数和信息内容创建消息
 * 
 * @param type    表示消息类型
 * @param callback    表示回调函数
 * @param element    表示消息内容
 */
csf_int32 css_app::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * 表示弹出消息内容
 */
csf::core::system::message::csf_message css_app::pop() {

	return  csf_nullptr;
}


/**
 * 表示发送一个message内容
 * 
 * @param message    表示添加的消息内容
 */
csf_int32 css_app::post(const csf_message& message) {

	return 0;
}


/**
 * 根据类型、回调函数和信息内容创建消息
 * 
 * @param type    表示消息类型
 * @param callback    表示回调函数
 * @param element    表示消息内容
 */
csf_int32 css_app::post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

	return 0;
}


/**
 * 表示弹出消息内容
 */
csf::core::system::message::csf_message css_app::pop() {

	return  csf_nullptr;
}