/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:44
*
*Description: Class(csf_message_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_message_manager.hpp"

using csf::core::system::message::csf_message_manager;


csf_message_manager::csf_message_manager() {

}



csf_message_manager::~csf_message_manager() {

}





/**
 * 表示添加回调函数
 * 
 * @param type    表示消息的类型
 */
csf_int32 csf_message_manager::add(const csf_message::csf_message_type type) {

	return 0;
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_message_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示发送一个message内容
 * 
 * @param message    表示添加的消息内容
 */
csf_int32 csf_message_manager::post(const csf::core::system::message::csf_message& message) {

	return 0;
}


/**
 * 表示添加回调函数
 * 
 * @param type    表示消息的类型
 * @param callback    表示回调函数
 */
csf_int32 csf_message_manager::del(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_manager_callback callback) {

	return 0;
}


/**
 * 根据类型、回调函数和信息内容创建消息
 * 
 * @param type    表示消息类型
 * @param callback    表示回调函数
 * @param element    表示消息内容
 */
csf_int32 csf_message_manager::post(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_message_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示弹出消息内容
 */
csf::core::system::message::csf_message csf_message_manager::pop() {

	return csf::core::system::message::csf_message();
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_message_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* 功能：
*    表示处理消息的函数
* 返回：
*    无
*/
csf_void csf_message_manager::process() {

}