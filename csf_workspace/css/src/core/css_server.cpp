/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_server.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:32
*
*Description: Class(css_server)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_server.hpp"

using css::core::css_server;


css_server::css_server() {

}



css_server::~css_server() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_server::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_server::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_server::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


csf_message_manager& css_server::get_message_manager() {

	return m_message_manager;
}


/**
 * 
 * @param newVal
 */
void css_server::set_message_manager(csf::core::system::message::csf_message_manager newVal) {

	m_message_manager = newVal;
}