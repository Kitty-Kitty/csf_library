/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:43
*
*Description: Class(csf_message)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_message.hpp"

using csf::core::system::message::csf_message;


csf_message::csf_message()
	: m_callback(csf_null)
	, m_type(csf_message_type_none) {

}



csf_message::~csf_message() {

}





/**
 * 根据csf_message_type和callback创建一个csf_message
 * 
 * @param type    表示message的类型
 * @param callback    表示message的回调函数
 */
csf_message::csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback) {

}


/**
 * 根据csf_message_type和callback创建一个csf_message
 * 
 * @param type    表示message的类型
 * @param callback    表示message的回调函数
 * @param element
 */
csf_message::csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

}