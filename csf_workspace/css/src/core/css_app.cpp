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
*Date: 07-10��-2018 16:50:25
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
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_app::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_app::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
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
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 css_app::post(csf_message& message) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 css_app::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message css_app::pop() {

	return  csf_nullptr;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 css_app::post(const csf_message& message) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 css_app::post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message css_app::pop() {

	return  csf_nullptr;
}