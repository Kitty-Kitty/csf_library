/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 28-7��-2018 14:23:33
*
*Description: Class(csf_connect) ��ʾͨ�ſ�����
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_connect.hpp"

using csf::core::module::connect::csf_connect;


csf_connect::csf_connect()
	: m_type(csf_connect_type_none)
	, m_sync(csf_false)
	, m_status(0)
	, m_factory(csf_nullptr)
	, m_read_timeout(0)
	, m_write_timeout(0) {

}



csf_connect::~csf_connect() {

}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


csf_url& csf_connect::get_remote_url() {

	return m_remote_url;
}


/**
 * 
 * @param newVal
 */
csf_int32 csf_connect::set_remote_url(csf_url& newVal) {

	m_remote_url = newVal;

	return csf_success;
}


/**
 * ��ʾ���ص�������ַ
 */
csf_url& csf_connect::get_local_url() {

	return m_local_url;
}


/**
 * ��ʾ���ص�������ַ
 * 
 * @param newVal
 */
csf_int32 csf_connect::set_local_url(csf_url& newVal) {

	m_local_url = newVal;

	return csf_success;
}


/**
 * ��ʾ����connect�Ĺ������ַ
 */
csf_connect_factory* csf_connect::get_factory() {

	return m_factory;
}


/**
 * ��ʾ����connect�Ĺ������ַ
 * 
 * @param newVal
 */
csf_void csf_connect::set_factory(csf_connect_factory* newVal) {

	m_factory = newVal;
}


csf_uint32 csf_connect::get_read_timeout() {

	return m_read_timeout;
}


/**
 * 
 * @param newVal
 */
csf_void csf_connect::set_read_timeout(csf_uint32 newVal) {

	m_read_timeout = newVal;
}


/**
 * ��ʾд��ʱʱ�䣬��λΪ���롣
 */
csf_uint32 csf_connect::get_write_timeout() {

	return m_write_timeout;
}


/**
 * ��ʾд��ʱʱ�䣬��λΪ���롣
 * 
 * @param newVal
 */
csf_void csf_connect::set_write_timeout(csf_uint32 newVal) {

	m_write_timeout = newVal;
}


/**
 * ��ʾ��������Ϣ
 * 
 * @param url    ��ʾ���ӵ�ַ
 */
csf_int32 csf_connect::open(const csf_url& url) {

	return csf_success;
}


/**
 * ��ʾ�ر�����
 */
csf_int32 csf_connect::close() {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������������
 * 
 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��ָ�����������
 * 
 * @param buf    ��ʾ���ݵĻ����ַ
 * @param len    ��ʾ���ݻ���ĳ���
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ�������ӵ�������Ŀ��Ϣ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
*/
csf_int32 csf_connect::set_option() {

	return csf_success;
}


/**
* ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
*/
csf_int32 csf_connect::get_option() {

	return csf_success;
}


/**
 * ��ʾд��csf_buffer����
 * 
 * @param buffer    ��ʾ��Ҫд���csf_buffer����
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring����
 * 
 * @param csfstr    ��ʾcsf_csfstring������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring����
 * 
 * @param chain    ��ʾcsf_chain������
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��csf_buffer����
 * 
 * @param buffer    ��ʾ��Ҫд���csf_buffer����
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��ָ�����������
 * 
 * @param buf    ��ʾ���ݵĻ����ַ
 * @param len    ��ʾ���ݻ���ĳ���
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
 * 
 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
 * 
 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring����
 * 
 * @param csfstr    ��ʾcsf_csfstring������
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ���ö���ʱʱ��
 * 
 * @param timeout_ms
 * @param callback    ��ʾ��ʱ�ص�������
 */
csf_int32 csf_connect::set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring����
 * 
 * @param chain    ��ʾcsf_chain������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����д��ʱʱ��
 * 
 * @param timeout_ms
 * @param callback    ��ʾ��ʱ�ص�������
 */
csf_int32 csf_connect::set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������������
 * 
 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_connect::read(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}