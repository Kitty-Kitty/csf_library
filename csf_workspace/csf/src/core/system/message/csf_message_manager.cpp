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
*Date: 27-6��-2018 17:28:44
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
 * ��ʾ��ӻص�����
 * 
 * @param type    ��ʾ��Ϣ������
 */
csf_int32 csf_message_manager::add(const csf_message::csf_message_type type) {

	return 0;
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_message_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ����һ��message����
 * 
 * @param message    ��ʾ��ӵ���Ϣ����
 */
csf_int32 csf_message_manager::post(const csf::core::system::message::csf_message& message) {

	return 0;
}


/**
 * ��ʾ��ӻص�����
 * 
 * @param type    ��ʾ��Ϣ������
 * @param callback    ��ʾ�ص�����
 */
csf_int32 csf_message_manager::del(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_manager_callback callback) {

	return 0;
}


/**
 * �������͡��ص���������Ϣ���ݴ�����Ϣ
 * 
 * @param type    ��ʾ��Ϣ����
 * @param callback    ��ʾ�ص�����
 * @param element    ��ʾ��Ϣ����
 */
csf_int32 csf_message_manager::post(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_message_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ������Ϣ����
 */
csf::core::system::message::csf_message csf_message_manager::pop() {

	return csf::core::system::message::csf_message();
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_message_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ���ܣ�
*    ��ʾ������Ϣ�ĺ���
* ���أ�
*    ��
*/
csf_void csf_message_manager::process() {

}