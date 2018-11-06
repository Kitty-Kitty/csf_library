/*******************************************************************************
*
*Copyright: fz
*
*Author: fz
*
*File name: css_device_io.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:26
*
*Description: Class(css_device_io)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_device_io.hpp"

using css::core::css_device_io;


css_device_io::css_device_io() {

}



css_device_io::~css_device_io() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_device_io::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 css_device_io::post(csf_message& message) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 css_device_io::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_device_io::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message css_device_io::pop() {

	return  csf_nullptr;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_device_io::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 css_device_io::post(const csf_message& message) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 css_device_io::post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message css_device_io::pop() {

	return  csf_nullptr;
}