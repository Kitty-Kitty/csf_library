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
*Date: 07-10��-2018 16:50:26
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
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_device::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 css_device::post(csf_message& message) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 css_device::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_device::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message css_device::pop() {

	return  csf_nullptr;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_device::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ���ӹ���������
 */
csf_connect_factory_manager& css_device::get_connect_factory_manager() {

	return m_connect_factory_manager;
}


/**
 * ��ʾ���ӹ���������
 * 
 * @param newVal
 */
csf_void css_device::set_connect_factory_manager(csf_connect_factory_manager& newVal) {

	m_connect_factory_manager = newVal;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 css_device::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 css_device::post(const csf_message& message) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message css_device::pop() {

	return  csf_nullptr;
}