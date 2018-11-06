/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:37
*
*Description: Class(csf_connect_factory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_connect_factory.hpp"
#include "csf_connect.hpp"

using namespace csf::core::module::connect;
using csf::core::module::connect::csf_connect_factory;


csf_connect_factory::csf_connect_factory() {

}



csf_connect_factory::~csf_connect_factory() {

}





/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_connect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory::init(const csf_configure_manager * conf_mg) {

	return get_timeout_manager().init();
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_connect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory::start(const csf_configure_manager * conf_mg) {

	return get_timeout_manager().start();
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_connect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_connect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 */
csf_connect_ptr csf_connect_factory::create(const csf_connect::csf_connect_type type) {

	return  m_null_connect_ptr;
}


/**
 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 */
csf_connect_ptr csf_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url) {

	return  m_null_connect_ptr;
}


/**
 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
 */
csf_connect_ptr csf_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	return  m_null_connect_ptr;
}


/**
 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
 * 
 * @param connect    ��ʾ��Ҫ���ٵ�����
 */
csf_int32 csf_connect_factory::destroy(const csf_connect_ptr connect) {

	return 0;
}