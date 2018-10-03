/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_tcp_connect.hpp
*
*Version: 1.0
*
*Date: 02-10��-2018 14:18:00
*
*Description: Class(csf_tcp_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_tcp_connect.hpp"

using csf::modules::connect::csf_tcp_connect;


csf_tcp_connect::~csf_tcp_connect() {

}




/**
* ģ���ʼ��
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_tcp_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��ʾ��������Ϣ.
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param url    ��ʾ���ӵ�ַ
*/
csf_int32 csf_tcp_connect::open(const csf_url& url) {

	return 0;
}


/**
* ��ʾ�ر�����.
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*/
csf_int32 csf_tcp_connect::close() {

	return 0;
}


/**
* ģ������
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_tcp_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��ʾ�������ӵ�������Ŀ��Ϣ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
*/
csf_int32 csf_tcp_connect::set_option() {

	return 0;
}


/**
* ģ��ֹͣ
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_tcp_connect::stop(const csf_configure_manager * conf_mg) {

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
csf_int32 csf_tcp_connect::write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(buf, len, callback);
}


/**
* ��ʾд��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_buffer& buffer
	, const csf_connect_callback callback) {

	return write(((csf_buffer&)buffer).get_buffer(), ((csf_buffer&)buffer).length(), callback);
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_csfstring& csfstr
	, const csf_connect_callback callback) {

	return write(((csf_csfstring&)csfstr).get_buffer(), ((csf_csfstring&)csfstr).length(), callback);
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_chain& chain
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(chain, callback);
}


/**
* ��ʾд��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_buffer& buffer
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(buffer, callback);
}


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	if (csf_nullptr == buf || len <= 0) {

		csf_ip_connect_error	tmp_error;

		tmp_error.set_error(csf_failure, "data[0x%x] length[%d] is null!", buf, len);
		exception_callback(this, callback, tmp_error);

		return csf_failure;
	}

	if (get_sync()) {
		return sync_write(buf, len, callback);
	}
	else {
		return async_write(buf, len, callback);
	}
}


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::sync_write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	//ѭ�������������ݣ�ֱ�����ݷ������Ϊֹ
	while (tmp_send_length < (csf_int32)len)
	{
		tmp_length = get_socket().send(boost::asio::buffer(buf + tmp_send_length, len - tmp_send_length), 0, tmp_error_code);
		if (tmp_length <= 0 || tmp_error_code) {

			exception_callback(this, callback, csf_ip_connect_error(tmp_error_code));

			return csf_failure;
		}
		tmp_send_length += tmp_length;
	}

	exception_callback(this, callback, csf_ip_connect_error());

	return len;
}


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::async_write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	//������Ҫ��������һ�󣬾ͷ��Ͳ���ȫ�ˡ�������linuxƽ̨�¸����׳����������
	get_socket().async_write_some(boost::asio::buffer(buf, len),
		boost::bind(&csf_tcp_connect::async_write_callback
			, this
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return len;
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_csfstring& csfstr
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(csfstr, callback);
}


/**
* ��ʾ����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

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
csf_int32 csf_tcp_connect::read(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ��ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param url    ��ʾ�������ݵ�Զ�˵�ַ
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(const csf_chain& chain
	, const csf_url& url
	, const csf_connect_callback callback) {

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
csf_int32 csf_tcp_connect::read(const csf_buffer& buffer
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ��ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(const csf_buffer& buffer
	, const csf_connect_callback callback) {

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
csf_int32 csf_tcp_connect::read(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ��ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(const csf_csfstring& csfstr
	, const csf_connect_callback callback) {

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
csf_int32 csf_tcp_connect::read(const csf_csfstring& csfstr
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* ��ʾ��ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(const csf_chain& chain
	, const csf_connect_callback callback) {

	return 0;
}