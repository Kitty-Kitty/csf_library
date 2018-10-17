/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 15:10:39
*
*Description: Class(csf_ip_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connect.hpp"

using csf::modules::connect::csf_ip_connect;



csf_ip_connect::~csf_ip_connect() {

}


csf_url& csf_ip_connect::get_remote_url() {

	return m_remote_url;
}


/**
*
* @param new_value
*/
csf_int32 csf_ip_connect::set_remote_url(csf_url& new_value) {

	if (csf_ip_url::is_valid_type(new_value)) {
		m_remote_url = (csf_ip_url&)new_value;
		return csf_success;
	}

	return csf_failure;
}


/**
* ��ʾ���ص�������ַ
*/
csf_url& csf_ip_connect::get_local_url() {

	return m_local_url;
}


/**
* ��ʾ���ص�������ַ
*
* @param new_value
*/
csf_int32 csf_ip_connect::set_local_url(csf_url& new_value) {

	if (csf_ip_url::is_valid_type(new_value)) {
		m_local_url = (csf_ip_url&)new_value;
		return csf_success;
	}

	return csf_failure;
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
csf_int32 csf_ip_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��csf_buffer���ݡ�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
 * 
 * @param buffer    ��ʾ��Ҫд���csf_buffer����
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_ip_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring���ݡ�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
 * 
 * @param csfstr    ��ʾcsf_csfstring������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_ip_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

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
csf_int32 csf_ip_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_ip_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_ip_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

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
csf_int32 csf_ip_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring���ݡ�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
 * 
 * @param chain    ��ʾcsf_chain������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_ip_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}


/**
*
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code    ��ʾboost�Ĵ�����Ϣ
* @param len    ��ʾ���ݳ�����Ϣ
*/
csf_bool csf_ip_connect::async_write_callback(const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 len) {

	async_callback(this, callback, csf_ip_connect_error(error_code));
	return csf_true;
}


/**
*
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code    ��ʾboost�Ĵ�����Ϣ
* @param len    ��ʾ���ݳ�����Ϣ
*/
csf_bool csf_ip_connect::async_read_callback(const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 len) {

	async_callback(this, callback, csf_ip_connect_error(error_code));
	return csf_true;
}