/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_connect_factory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connect_factory.hpp"
#include "csf_tcp_connect.hpp"
#include "csf_udp_connect.hpp"


using csf::modules::connect::csf_ip_connect_factory;


csf_ip_connect_factory::csf_ip_connect_factory() {

// 	get_version().set_version(
// 		csf_version
// 		, CSF_VER
// 		, 
// 	);
}



csf_ip_connect_factory::~csf_ip_connect_factory() {

}





/**
 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type) {

	csf_connect					*tmp_connect = csf_nullptr;

	if (type & csf_connect::csf_connect_type::csf_connect_type_tcp) {
		tmp_connect = new csf_tcp_connect(*this);
	}
	else if (type & csf_connect::csf_connect_type::csf_connect_type_udp) {
		tmp_connect = new csf_udp_connect(*this);
	}
	else {
		return m_null_connect_ptr;
	}

	csf_connect_ptr tmp_connect_ptr(tmp_connect);

	get_connect_collector().insert(tmp_connect, tmp_connect_ptr);

	return tmp_connect_ptr;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connect_factory::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url) {

	csf_connect_ptr					tmp_connect_ptr = create(type);

	if (tmp_connect_ptr == m_null_connect_ptr) {
		return m_null_connect_ptr;
	}
	else {
		if (tmp_connect_ptr->set_local_url((csf_url&)local_url)) {
			get_connect_collector().remove(tmp_connect_ptr.get());
			return m_null_connect_ptr;
		}
	}
	
	return  tmp_connect_ptr;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connect_factory::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	csf_connect_ptr					tmp_connect_ptr = create(type, local_url);

	if (tmp_connect_ptr == m_null_connect_ptr) {
		return m_null_connect_ptr;
	}
	else {
		if (tmp_connect_ptr->set_remote_url((csf_url&)remote_url)) {
			get_connect_collector().remove(tmp_connect_ptr.get());
			return m_null_connect_ptr;
		}
	}

	return  tmp_connect_ptr;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* ��ʾģ���create �� destroy ������塣                                              */
/* ÿ����Ҫͨ��ģ�鹤��������ģ�鶼��Ҫ��Ӹú궨�塣                                    */
/* ����module_type��ʾ��ģ��������ƣ�����ʵ���˹��췽��Ϊ��                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(csf_ip_connect_factory)