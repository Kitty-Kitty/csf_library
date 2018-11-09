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

	if (get_socket().is_open()) {

		try {
			int									tmp_ret_int = 0;
			struct linger						tmp_linger = { 0, 0 };
			boost::system::error_code			tmp_error_code;


			tmp_ret_int = setsockopt(get_socket().native()
				, SOL_SOCKET
				, SO_LINGER
				, (char*)(&tmp_linger)
				, sizeof(struct linger));

			get_socket().cancel();
			get_socket().shutdown(boost::asio::socket_base::shutdown_both, tmp_error_code);
			get_socket().close();
		}
		catch (boost::exception& e)	{
			csf_log_ex(error, csf_log_code_error
				, "socket[0x%x url:%s] close failed! reason:[%s -- %s]."
				, this
				, get_local_url().get_url().c_str()
				, boost::current_exception_diagnostic_information().c_str()
				, boost::diagnostic_information(e).c_str());
		}
	}
	return csf_succeed;
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
* ��Ҫ�����ǣ���һ��������ַ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param url    ��ʾ��Ҫ�����ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::listen(const csf_url& url, const csf_connect_callback& callback) {

	csf::modules::connect::csf_ip_url &ip_url = (csf::modules::connect::csf_ip_url&)url;

	try {
		//����Ѿ������ˣ��򷵻�ʧ��
		if (csf_nullptr != get_acceptor()) {

			csf_log_ex(error, csf_log_code_error
				, "listen[url:%s] failed! connect is listening."
				, ip_url.get_url().c_str());

			return csf_failure;
		}

		//����һ��acceptor������ʵ��tcp����
		set_acceptor(new boost::asio::ip::tcp::acceptor(
				get_socket().get_io_service()
				, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip_url.get_ip())
				, ip_url.get_port())));

		async_accept(callback);
	}
	catch (boost::exception& e) {

		csf_log_ex(error, csf_log_code_error
			, "listen [url:%s] failed! reason:[%s -- %s]."
			, ip_url.get_url().c_str()
			, boost::current_exception_diagnostic_information().c_str()
			, boost::diagnostic_information(e).c_str());

		return csf_failure;
	}

	return csf_succeed;
}


/**
* ��Ҫ�����ǣ���Ҫ����һ����ַ��
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param url    ��ʾ��Ҫ�����ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::connect(const csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_chain& chain, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param url    ��ʾ��Ҫ�������ݵ�Ŀ�ĵ�ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
*
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_char_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_buffer_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_csfstr_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_chain& chain, const csf_uint32 len, const csf_chain_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ�ŵĻ������
*
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_char_buffer_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_buffer_buffer_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_csfstr_buffer_read_callback& callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_chain_buffer_read_callback& callback) {

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
csf_int32 csf_tcp_connect::sync_write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	//ѭ�������������ݣ�ֱ�����ݷ������Ϊֹ
	while (tmp_send_length < (csf_int32)len)
	{
		tmp_length = get_socket().send(
			boost::asio::buffer(buf + tmp_send_length, len - tmp_send_length)
			, 0
			, tmp_error_code);
		if (tmp_length <= 0 || tmp_error_code) {

			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));

			return csf_failure;
		}
		tmp_send_length += tmp_length;
	}

	exception_callback(shared_from_this(), callback, csf_ip_connect_error());

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
	get_socket().async_write_some(boost::asio::buffer(buf, len)
			, boost::bind(&csf_tcp_connect::async_write_callback
			, this
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return len;
}


/**
* ��ʾԶ�̵�������ַ
*/
const csf_url& csf_tcp_connect::get_remote_url() const {

	//�ж����ڵĵ�ַ�Ƿ���ڣ�������ֱ�ӷ���
	if (csf_ip_connect::get_remote_url().get_url().empty()) {

		((csf_ip_url&)csf_ip_connect::get_remote_url()).set_url(
			get_socket().remote_endpoint().address().to_string()
			, get_socket().remote_endpoint().port());
	}

	return csf_ip_connect::get_remote_url();
}


/**
* ��ʾ���ص�������ַ
*/
const csf_url& csf_tcp_connect::get_local_url() const {

	//�ж����ڵĵ�ַ�Ƿ���ڣ�������ֱ�ӷ���
	if (csf_ip_connect::get_local_url().get_url().empty()) {

		((csf_ip_url&)csf_ip_connect::get_remote_url()).set_url(
			get_socket().local_endpoint().address().to_string()
			, get_socket().local_endpoint().port());
	}

	return csf_ip_connect::get_local_url();
}


/**
* ��Ҫ�����ǣ��첽tcp������accept��������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf::core::base::csf_int32 csf_tcp_connect::async_accept(const csf_connect_callback callback) {

	csf_tcp_connect		*tmp_connect = csf_nullptr;

	while (csf_true) {
		try	{
			//������Ҫ�����Щʱ��newʧ�ܵ�����
			tmp_connect = new csf_tcp_connect(this);
			if (tmp_connect) {
				break;
			}
			else {
				csf_log_ex(error
					, csf_log_code_error
					, "create csf_tcp_connect() instance failed!");
			}
		}
		catch (boost::exception& e) {

			csf_log_ex(error, csf_log_code_error
				, "create csf_tcp_connect() instance exception! reason:[%s -- %s]."
				, boost::current_exception_diagnostic_information().c_str()
				, boost::diagnostic_information(e).c_str());

			continue;
		}
	}

	csf_tcp_connect_ptr connect_ptr(tmp_connect);

	//Ϊÿ���������һ��ʱ�������ҪΪ�˷��㳬ʱ�������ӵȴ���
	//conn_socket_ptr->m_time = m_parking_p->m_current_millsec;
	get_acceptor()->async_accept(
		connect_ptr->get_socket()
		, boost::bind(&csf_tcp_connect::accept_handle, this, connect_ptr, callback, _1));

	return csf_succeed;
}


/**
* ��Ҫ�����ǣ��첽tcp������accept�ص���������
* ���أ���
*
* @param connect_ptr    ��ʾ��ǰ����ͨ�����Ӷ���
* @param callback    ��ʾ��Ҫ���صĻص�����
* @param ec    ��ʾ��ǰ�Ĵ�����Ϣ
*/
csf_void csf_tcp_connect::accept_handle(csf_tcp_connect_ptr connect_ptr
	, const csf_connect_callback callback
	, boost::system::error_code ec) {

	if (ec)	{

		csf_log_ex(error
			, csf_log_code_error
			, "accept connect failed! reason:[%d] %s"
			, ec.value()
			, boost::system::system_error(ec).what());

		return;
	}

	set_read_timeout(csf_connect_timeout_default_ms, csf_nullptr);

	async_accept(callback);

	static csf_uchar  len[10] = { 0, };
	static boost::system::error_code tmp_error;
	static csf_buffer			tmp_buffer;
	static csf_connect_callback tmp_callback = csf_nullptr;
	//get_socket().receive(boost::asio::buffer(len, sizeof(len)), 0, tmp_error);
	get_socket().async_receive(boost::asio::buffer(len, sizeof(len)),
		boost::bind(&csf_tcp_connect::read_handle,
			this, connect_ptr, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

	//��������ӽ��룬�����
	if (csf_nullptr != callback) {
		callback(connect_ptr, csf_connect_error());
	}
}


csf_bool csf_tcp_connect::read_handle(csf_tcp_connect_ptr connect_ptr, const boost::system::error_code ec, csf_uint32 str_len) {

	return csf_true;
}