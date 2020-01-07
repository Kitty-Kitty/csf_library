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
*Date: 27-6��-2018 17:28:43
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
 * ����csf_message_type��callback����һ��csf_message
 * 
 * @param type    ��ʾmessage������
 * @param callback    ��ʾmessage�Ļص�����
 */
csf_message::csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback) {

}


/**
 * ����csf_message_type��callback����һ��csf_message
 * 
 * @param type    ��ʾmessage������
 * @param callback    ��ʾmessage�Ļص�����
 * @param element
 */
csf_message::csf_message(const csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

}