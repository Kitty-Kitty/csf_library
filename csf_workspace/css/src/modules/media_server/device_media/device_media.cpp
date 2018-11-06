/*******************************************************************************
*
*Copyright: fz
*
*Author: fz
*
*File name: device_media.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:34
*
*Description: Class(device_media)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "device_media.hpp"

using css::modules::media_server::device_media::device_media;


device_media::device_media() {

}



device_media::~device_media() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 device_media::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 device_media::post(csf_message& message) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 device_media::post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 device_media::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message device_media::pop() {

	return  csf_nullptr;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 device_media::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ���ӹ���������
 */
csf_connect_factory_manager& device_media::get_connect_factory_manager() {

	return m_connect_factory_manager;
}


/**
 * ��ʾ���ӹ���������
 * 
 * @param newVal
 */
void device_media::set_connect_factory_manager(csf_connect_factory_manager& newVal) {

	m_connect_factory_manager = newVal;
}