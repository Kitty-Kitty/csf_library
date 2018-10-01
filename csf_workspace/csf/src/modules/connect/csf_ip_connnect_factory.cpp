/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connnect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_connnect_factory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connnect_factory.hpp"
#include "csf_tcp_connect.hpp"
#include "csf_udp_connect.hpp"


using csf::modules::connect::csf_ip_connnect_factory;


csf_ip_connnect_factory::csf_ip_connnect_factory() {

}



csf_ip_connnect_factory::~csf_ip_connnect_factory() {

}





/**
 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 */
csf_connect_ptr csf_ip_connnect_factory::create(const csf_connect::csf_connect_type type) {

	return  m_null_connect_ptr;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connnect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connnect_factory::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 */
csf_connect_ptr csf_ip_connnect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url) {

	if (type & csf_connect::csf_connect_type::csf_connect_type_tcp) {
		csf_tcp_connect		*tmp_tcp_connect = new csf_tcp_connect();

		if (tmp_tcp_connect->set_local_url((csf_url&)local_url)) {
			delete tmp_tcp_connect;
			return m_null_connect_ptr;
		}
		else {
			csf_connect_ptr tmp_tcp_connect_ptr(tmp_tcp_connect);

			
		}
	}
	return  m_null_connect_ptr;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connnect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connnect_factory::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
 */
csf_connect_ptr csf_ip_connnect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	return  m_null_connect_ptr;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connnect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connnect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connnect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ��ʾ�����������ӣ����ٳɹ�����0��ʧ�ܷ���<0����ֵ��
 * 
 * @param connect    ��ʾ��Ҫ���ٵ�����
 */
csf_int32 csf_ip_connnect_factory::destroy(const csf_connect_ptr connect) {

	return 0;
}