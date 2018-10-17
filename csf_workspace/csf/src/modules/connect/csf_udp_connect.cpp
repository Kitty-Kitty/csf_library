/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_udp_connect.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 14:18:02
*
*Description: Class(csf_udp_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_udp_connect.hpp"

using csf::modules::connect::csf_udp_connect;



csf_udp_connect::~csf_udp_connect() {

}



/**
* ģ���ʼ��
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_udp_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��ʾ��������Ϣ.
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param url    ��ʾ���ӵ�ַ
*/
csf_int32 csf_udp_connect::open(const csf_url& url) {

	return 0;
}


/**
* ��ʾ�ر�����.
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*/
csf_int32 csf_udp_connect::close() {

	return 0;
}


/**
* ģ������
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_udp_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��ʾ�������ӵ�������Ŀ��Ϣ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
*/
csf_int32 csf_udp_connect::set_option() {

	return 0;
}


/**
* ģ��ֹͣ
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_udp_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
*/
csf_int32 csf_udp_connect::get_option() {

	return 0;
}


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾд��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾд��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_udp_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}
