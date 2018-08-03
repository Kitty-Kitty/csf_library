/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:37
*
*Description: Class(csf_connect_factory)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_connect_factory.hpp"

using csf::core::module::device::csf_connect_factory;


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

	return 0;
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

	return 0;
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
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 */
csf_connect* csf_connect_factory::create(const csf::core::module::device::csf_connect_type type) {

	return  NULL;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 */
csf_connect* csf_connect_factory::create(const csf_connect_type type, const csf_url& local_url) {

	return  NULL;
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
 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
 */
csf_connect* csf_connect_factory::create(const csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	return  NULL;
}


/**
 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
 * 
 * @param connect    ��ʾ��Ҫ���ٵ�����
 */
csf_int32 csf_connect_factory::destroy(const csf_connect* connect) {

	return 0;
}