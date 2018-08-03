/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:49
*
*Description: Class(csf_stream_connect)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_stream_connect.hpp"

using csf::core::module::device::csf_stream_connect;


csf_stream_connect::csf_stream_connect() {

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
 * ��ʾ��������Ϣ
 * 
 * @param url    ��ʾ���ӵ�ַ
 */
void csf_stream_connect::open(csf::core::module::device::csf_url url) {

}


/**
 * ��ʾ�ر�����
 */
csf::core::base::csf_uint32 csf_stream_connect::close() {

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
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback) {

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
 * ��ʾ���ӵ�����
 */
csf::core::module::device::csf_connect_type csf_stream_connect::get_type() {

	return m_type;
}


/**
 * ��ʾд��ָ�����������
 * 
 * @param buffer    ��ʾ���ݵĻ����ַ
 * @param length    ��ʾ���ݻ���ĳ���
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(csf_uchar* buffer, csf_uint32 length, csf_url& url, csf_connect_callback callback) {

	return 0;
}


void csf_stream_connect::get_address() {

}


/**
 * ��ʾ���ӵ�����
 * 
 * @param newVal
 */
csf_int32 csf_stream_connect::set_type(csf::core::module::device::csf_connect_type newVal) {

	m_type = newVal;
}


csf_url& csf_stream_connect::get_remote_url() {

	return m_remote_url;
}


void csf_stream_connect::set_address() {

}


void csf_stream_connect::set_option() {

}


/**
 * 
 * @param newVal
 */
csf_int32 csf_stream_connect::set_remote_url(csf_url& newVal) {

	m_remote_url = newVal;
}


/**
 * ��ʾ���ص�������ַ
 */
csf_url& csf_stream_connect::get_local_url() {

	return m_local_url;
}


void csf_stream_connect::get_option() {

}


/**
 * ��ʾ���ص�������ַ
 * 
 * @param newVal
 */
csf_int32 csf_stream_connect::set_local_url(csf_url& newVal) {

	m_local_url = newVal;
}


/**
 * ��ʾд��csf_buffer����
 * 
 * @param buffer    ��ʾ��Ҫд���csf_buffer����
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(csf_buffer& buffer, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring����
 * 
 * @param csfstr    ��ʾcsf_csfstring������
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(csf_csfstring& csfstr, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ����csf_csfstring����
 * 
 * @param csfstr    ��ʾcsf_csfstring������
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��csf_buffer����
 * 
 * @param buffer    ��ʾ��Ҫд���csf_buffer����
 * @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(csf_buffer& buffer, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾд��ָ�����������
 * 
 * @param buffer    ��ʾ���ݵĻ����ַ
 * @param length    ��ʾ���ݻ���ĳ���
 * @param callback    ��ʾ��Ҫ���صĻص�����
 */
csf_int32 csf_stream_connect::write(csf_uchar* buffer, csf_uint32 length, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
 * 
 * @param length    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(csf_uchar* buffer, csf_int32 length, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
 * @param url    ��ʾ�������ݵ�Զ�˵�ַ
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(csf_buffer& buffer, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(csf_buffer& buffer, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param buffer    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
 * 
 * @param length    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(csf_uchar* buffer, csf_int32 length, csf_connect_callback callback) {

	return 0;
}


/**
 * ��ʾ��ȡ���ݲ�����ָ������λ��
 * 
 * @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
 * @param callback    ��ʾ��ȡ�Ļص�����
 */
csf_int32 csf_stream_connect::read(csf_csfstring& csfstr, csf_connect_callback callback) {

	return 0;
}