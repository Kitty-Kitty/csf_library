/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:53
*
*Description: Class(csf_stream_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_stream_connect.hpp"

using csf::modules::connect::csf_stream_connect;


csf_stream_connect::csf_stream_connect()
	: m_type(csf_connect_type_none)
	, m_sync(csf_false)
	, m_status(0)
	, m_factory(csf_nullptr)
	, m_read_timeout(0)
	, m_write_timeout(0)
	, m_configure_manager(csf_nullptr) {

}



csf_stream_connect::~csf_stream_connect() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_stream_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ��������Ϣ.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param url    ��ʾ���ӵ�ַ
 */
csf_int32 csf_stream_connect::open(const csf_url& url) {

	return 0;
}


/**
 * ��ʾ�ر�����.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 */
csf_int32 csf_stream_connect::close() {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_stream_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�������ӵ�������Ŀ��Ϣ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 */
csf_int32 csf_stream_connect::set_option() {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_stream_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ��ȡ���ӵ�������Ŀ��Ϣ��
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
 */
csf_int32 csf_stream_connect::get_option() {

	return 0;
}


/**
 * ��ʾ���ö���ʱʱ��.
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param timeout_ms
 * @param callback    ��ʾ��ʱ�ص�������
 */
csf_int32 csf_stream_connect::set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


csf_url& csf_stream_connect::get_remote_url() {

	return m_remote_url;
}


/**
 * ��ʾ����д��ʱʱ�䡣
 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
 * 
 * @param timeout_ms
 * @param callback    ��ʾ��ʱ�ص�������
 */
csf_int32 csf_stream_connect::set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * 
 * @param new_value
 */
csf_int32 csf_stream_connect::set_remote_url(csf_url& new_value) {

	m_remote_url = new_value;

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
csf_int32 csf_stream_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ���ص�������ַ
 */
csf_url& csf_stream_connect::get_local_url() {

	return m_local_url;
}


/**
 * ��ʾд��csf_buffer���ݡ�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
 * 
 * @param buffer    ��ʾ��Ҫд���csf_buffer����
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ���ص�������ַ
 * 
 * @param new_value
 */
csf_int32 csf_stream_connect::set_local_url(csf_url& new_value) {

	m_local_url = new_value;

	return 0;
}


/**
 * ��ʾ����csf_csfstring���ݡ�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
 * 
 * @param csfstr    ��ʾcsf_csfstring������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

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
csf_int32 csf_stream_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_stream_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_stream_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

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
csf_int32 csf_stream_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring���ݡ�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
 * 
 * @param chain    ��ʾcsf_chain������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
 * 
 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����connect�Ĺ������ַ
 */
csf_connect_factory* csf_stream_connect::get_factory() {

	return m_factory;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ�����������С�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����connect�Ĺ������ַ
 * 
 * @param new_value
 */
csf_void csf_stream_connect::set_factory(csf_connect_factory* new_value) {

	m_factory = new_value;
}


csf_uint32 csf_stream_connect::get_read_timeout() {

	return m_read_timeout;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
 * 
 * @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * 
 * @param new_value
 */
csf_void csf_stream_connect::set_read_timeout(csf_uint32 new_value) {

	m_read_timeout = new_value;
}


/**
 * ��ʾд��ʱʱ�䣬��λΪ���롣
 */
csf_uint32 csf_stream_connect::get_write_timeout() {

	return m_write_timeout;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ�á�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��ʱʱ�䣬��λΪ���롣
 * 
 * @param new_value
 */
csf_void csf_stream_connect::set_write_timeout(csf_uint32 new_value) {

	m_write_timeout = new_value;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ�����������С�
 * ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
 * 
 * @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}