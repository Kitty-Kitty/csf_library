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

	int abc = 1;
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
		catch (boost::exception& e) {
			csf_log_ex(error, csf_log_code_error
				, "%s close failed! reason:[%s -- %s]."
				, to_string().c_str()
				, boost::current_exception_diagnostic_information().c_str()
				, boost::diagnostic_information(e).c_str());
		}
	}

	return csf_connect::close();
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

			exception_callback(shared_from_this()
				, callback
				, csf_ip_connect_error(
					csf_connect_error::csf_connect_code::csf_connect_code_listen
					, "is listening"));

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

		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(
				csf_connect_error::csf_connect_code::csf_connect_code_listen
				, boost::diagnostic_information(e)));

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
// csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//������Բ��������ݵ�У�鴦��������������ݶ�ȡ��Ч��
// 	if (csf_nullptr == buf
// 		|| len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes
// 				, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//�����Ƿ��лص����������ж�ʹ���첽����ͬ��
// 	if (csf_nullptr == callback) {
// 		return sync_write(buf, len, callback);
// 	}
// 	else {
// 		return async_write(buf, len, callback);
// 	}
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫд���csf_buffer����
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {
// 
// 	return write(buffer.get_buffer(), buffer.length(), callback);
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param csfstr    ��ʾcsf_csfstring������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {
// 
// 	return write(csfstr.get_buffer(), csfstr.length(), callback);
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param chain    ��ʾcsf_chain������
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::write(csf_chain& chain, const csf_connect_callback& callback) {
// 
// 	csf_buffer				tmp_buffer(chain.length());
// 
// 	chain.convert(tmp_buffer);
// 
// 	return write(tmp_buffer, callback);
// }


/**
* ��Ҫ�����ǣ�д��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
// 	if (buffer.get_is_sync()) {
// 		return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�д��csf_buffer���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//���ж����ݵĺϷ��ԣ�֮���ٴ���
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
		return csf_failure;
	}

	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
	if (buffer.get_is_sync()) {
		//return sync_write(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
		return sync_write(buffer, callback);
	}
	else {
		//return async_write(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
		return async_write(buffer, callback);
	}
	return 0;
}


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (!buffer.is_valid()) {
// 		return exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 	}
// 
// 	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
// 	if (buffer.get_is_sync()) {
// 		return sync_write(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* ��Ҫ�����ǣ�����csf_csfstring���ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ��Ҫ���͵����ݻ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (!buffer.is_valid()) {
// 		return exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 	}
// 
// 	//�Ƚ�chainת��Ϊbuffer����Ϊһ���������ڴ�ռ����
// 	csf_buffer				tmp_buffer(buffer.get_buffer()->length());
// 
// 	buffer.get_buffer()->convert(tmp_buffer);
// 
// 	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
// 	if (buffer.get_is_sync()) {
// 		return sync_write(tmp_buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(tmp_buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buf    ��ʾ��ȡ���ݴ��ڵ�ָ�������ַ
*
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (csf_nullptr == buf
// 		|| len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
// 	if (csf_nullptr == callback) {
// 		return sync_read(buf, len, callback);
// 	}
// 	else {
// 		return async_read(buf, len, callback);
// 	}
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵ�csf_buffer
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//ʣ��ռ����ʱ����ֱ�Ӵ���
// 	if (buffer.avail() >= len) {
// 		return read(buffer.get_buffer(), len, callback);
// 	}
// 	else {
// 		//���ʣ��Ŀռ䲻�㣬�򱨳��쳣
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param csfstr    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//ʣ��ռ����ʱ����ֱ�Ӵ���
// 	if (csfstr.length() >= len) {
// 		return read(csfstr.get_buffer(), len, callback);
// 	}
// 	else {
// 		//���ʣ��Ŀռ䲻�㣬�򱨳��쳣
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param chain    ��ʾ��ȡ���ݴ��ڵ�csf_csfstring
* @param len    ��ʾ��ȡ���ݴ��ڵ�ָ�����泤��
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 
// 	csf_int32		tmp_length = 0;
// 	csf_buffer		tmp_buffer(len);
// 
// 	//chainֻ�ܽ���ͬ�����պͱ��洦��
// 	tmp_length = read(tmp_buffer, len, csf_nullptr);
// 	if (tmp_length >= (csf_int32)len) {
// 		chain.add(tmp_buffer);
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error());
// 		return csf_succeed;
// 	}
// 	else {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_operation_error, "read data error"));
// 
// 		return csf_failure;
// 	}
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ�ŵĻ������
*
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 	//����filled��־λ
// 	set_is_filled(buffer.get_is_filled());
// 
// 	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
// 	if (buffer.get_is_sync()) {
// 		return sync_read(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_read(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 
// 	return csf_succeed;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//���ж����ݵĺϷ��ԣ�֮���ٴ���
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
				, "not enough storage available"));
		return csf_failure;
	}
	//����filled��־λ
	set_is_filled(buffer.get_is_filled());

	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
	if (buffer.get_is_sync()) {
		//return sync_read(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
		return sync_read(buffer, callback);
	}
	else {
		//return async_read(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
		return async_read(buffer, callback);
	}
	return 0;
}


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ������λ�á�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 	//����filled��־λ
// 	set_is_filled(buffer.get_is_filled());
// 
// 	//����csf_connect_buffer�ı�־λ���ж��첽��ͬ��
// 	if (buffer.get_is_sync()) {
// 		return sync_read(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_read(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* ��Ҫ�����ǣ���ȡ���ݲ�����ָ�����������С�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���ȡ�����ݳ��ȣ�
*
* @param buffer    ��ʾ��ȡ���ݴ��ڵĻ������
* @param callback    ��ʾ��ȡ�Ļص�����
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	//���ж����ݵĺϷ��ԣ�֮���ٴ���
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 
// 		return csf_failure;
// 	}
// 
// 	return read(*(buffer.get_buffer()), buffer.get_length(), callback);
// }


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::sync_write(const csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	csf_int32						tmp_length = 0;
// 	csf_int32						tmp_send_length = 0;
// 	boost::system::error_code		tmp_error_code;
// 
// 
// 	get_write_timeout().flush_time();
// 
// 	//ѭ�������������ݣ�ֱ�����ݷ������Ϊֹ
// 	while (tmp_send_length < (csf_int32)len)
// 	{
// 		tmp_length = get_socket().send(
// 			boost::asio::buffer(buf + tmp_send_length, len - tmp_send_length)
// 			, 0
// 			, tmp_error_code);
// 		if (tmp_length <= 0 || tmp_error_code) {
// 
// 			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
// 
// 			return csf_failure;
// 		}
// 		tmp_send_length += tmp_length;
// 	}
// 
// 	exception_callback(shared_from_this(), callback, csf_ip_connect_error());
// 
// 	return len;
// }


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::async_write(const csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	get_write_timeout().flush_time();
// 
// 	//������Ҫ��������һ�󣬾ͷ��Ͳ���ȫ�ˡ�������linuxƽ̨�¸����׳����������
// 	get_socket().async_write_some(boost::asio::buffer(buf, len)
// 		, boost::bind(&csf_tcp_connect::ip_async_write_callback
// 			, this
// 			, buf
// 			, len
// 			, callback
// 			, boost::asio::placeholders::error
// 			, boost::asio::placeholders::bytes_transferred));
// 
// 	return len;
// }


/**
* ��Ҫ�����ǣ������첽д����ص�����
* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
*
* @param buf		 ��ʾ���ݵĻ����ַ
* @param src_len	 ��ʾ��Ҫ�������Դ���ݻ���ĳ���
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code  ��ʾboost�Ĵ�����Ϣ
* @param write_len   ��ʾ��ǰʵ��д�Ļ��泤��
*/
// csf_bool csf_tcp_connect::ip_async_write_callback(const csf_uchar* buf
// 	, const csf_uint32 src_len
// 	, const csf_connect_callback& callback
// 	, const boost::system::error_code& error_code
// 	, csf_uint32 write_len) {
// 
// 	//�������������մ�����
// 	if (error_code) {
// 		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_false;
// 	}
// 	//����Ѿ���������������ݣ��������ص�����
// 	if (write_len >= src_len) {
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_true;
// 	}
// 	else {
// 		//���û�з�����ȫ�����в������ݣ����������
// 		async_write(buf + write_len, src_len - write_len, callback);
// 	}
// 
// 	return csf_true;
// }


/**
* ��Ҫ�����ǣ�ͬ����ȡ���ݣ�������ָ�����档
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::sync_read(csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	csf_int32						tmp_length = 0;
// 	csf_int32						tmp_receive_length = 0;
// 	boost::system::error_code		tmp_error_code;
// 
// 
// 	 do {
// 
// 		get_read_timeout().flush_time();
// 
// 		//��������
// 		tmp_length = get_socket().receive(boost::asio::buffer(buf + tmp_receive_length, len - tmp_receive_length)
// 			, 0
// 			, tmp_error_code);
// 		if (tmp_error_code) {
// 			//�������ͨ�Ŵ����������
// 			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
// 			return csf_failure;
// 		}
// 		else if (tmp_receive_length <= 0) {
// 			//��������������ݴ��������⴦��
// 			csf_ip_connect_error			tmp_error;
// 
// 			tmp_error.set_error(csf_connect_error::csf_connect_code_operation_error
// 				,"receive data length[ %d <=0 ]"
// 				, tmp_length);
// 			exception_callback(shared_from_this(), callback, tmp_error);
// 			return csf_failure;
// 		}
// 		else {
// 			//�ۼ����ݳ���
// 			tmp_receive_length += tmp_length;
// 		}
// 
// 	} while ((csf_int32)len > tmp_receive_length && csf_true == get_is_filled());		//�ж��Ƿ�������������Ҫ��ѭ������ֱ�������
// 
// 	return tmp_receive_length;
// }


/**
* ��Ҫ�����ǣ��첽��ȡ���ݣ�������ָ�����档
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
*
* @param buf    ��ʾ���ݵĻ����ַ
* @param len    ��ʾ���ݻ���ĳ���
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
// csf_int32 csf_tcp_connect::async_read(csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	get_read_timeout().flush_time();
// 
// 	get_socket().async_receive(boost::asio::buffer(buf, len)
// 		, boost::bind(&csf_tcp_connect::ip_async_read_callback
// 			, this
// 			, buf
// 			, len
// 			, callback
// 			, boost::asio::placeholders::error
// 			, boost::asio::placeholders::bytes_transferred));
// 
// 	return 0;
// }


/**
* ��Ҫ�����ǣ������첽������ص�����
* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
*
* @param buf		 ��ʾ���ݵĻ����ַ
* @param buf_len	 ��ʾ��Ҫ�������Դ���ݻ���ĳ���
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code  ��ʾboost�Ĵ�����Ϣ
* @param read_len   ��ʾ��ǰʵ��д�Ļ��泤��
*/
// csf_bool csf_tcp_connect::ip_async_read_callback(csf_uchar* buf
// 	, const csf_uint32 buf_len
// 	, const csf_connect_callback& callback
// 	, const boost::system::error_code& error_code
// 	, csf_uint32 read_len) {
// 
// 	//�������������մ�����
// 	if (error_code) {
// 		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_false;
// 	}
// 
// 	//�����Ҫ�����������ݣ���������գ�ֱ������������ȫ
// 	if (csf_false == get_is_filled()) {
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_true;
// 	}
// 	else {
// 		//����Ѿ���������������ݣ��������ص�����
// 		if (read_len >= buf_len) {
// 			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 			return csf_true;
// 		}
// 		else {
// 			//���û�з�����ȫ�����в������ݣ����������
// 			async_read(buf + read_len, buf_len - read_len, callback);
// 		}
// 	}
// 
// 	return csf_true;
// }




/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ���ݵĻ����ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::sync_write(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer()->get_buffer();
	csf_int32						tmp_total_length = buffer.get_buffer()->length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	get_write_timeout().flush_time();

	//ѭ�������������ݣ�ֱ�����ݷ������Ϊֹ
	while (tmp_send_length < (csf_int32)tmp_total_length)
	{
		tmp_length = get_socket().send(
			boost::asio::buffer(tmp_buf + tmp_send_length, tmp_total_length - tmp_send_length)
			, 0
			, tmp_error_code);
		if (tmp_length <= 0 || tmp_error_code) {

			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));

			return csf_failure;
		}
		tmp_send_length += tmp_length;
	}

	exception_callback(shared_from_this(), callback, csf_ip_connect_error());

	return tmp_total_length;
}


/**
* ��ʾд��ָ����������ݡ�
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ�д������ݳ��ȣ�
*
* @param buffer    ��ʾ���ݵĻ����ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::async_write(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {


	get_write_timeout().flush_time();

	//������Ҫ��������һ�󣬾ͷ��Ͳ���ȫ�ˡ�������linuxƽ̨�¸����׳����������
	get_socket().async_write_some(boost::asio::buffer(buffer.get_buffer()->get_buffer()
		, buffer.get_length())
		, boost::bind(&csf_tcp_connect::ip_async_write_callback
			, this
			, std::ref(buffer)
			, shared_from_this()
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return buffer.get_length();
}


/**
* ��Ҫ�����ǣ�ͬ����ȡ���ݣ�������ָ�����档
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
*
* @param buffer    ��ʾ���ݵĻ����ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::sync_read(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer()->get_buffer();
	csf_int32						tmp_total_length = buffer.get_length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_receive_length = 0;
	boost::system::error_code		tmp_error_code;


	do {

		get_read_timeout().flush_time();

		//��������
		tmp_length = get_socket().receive(boost::asio::buffer(tmp_buf + tmp_receive_length
			, tmp_total_length - tmp_receive_length)
			, 0
			, tmp_error_code);
		if (tmp_error_code) {
			//�������ͨ�Ŵ����������
			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
			return csf_failure;
		}
		else if (tmp_receive_length <= 0) {
			//��������������ݴ��������⴦��
			csf_ip_connect_error			tmp_error;

			tmp_error.set_error(csf_connect_error::csf_connect_code_operation_error
				, "receive data length[ %d <= 0 ]"
				, tmp_length);
			exception_callback(shared_from_this(), callback, tmp_error);
			return csf_failure;
		}
		else {
			//�ۼ����ݳ���
			tmp_receive_length += tmp_length;
		}

	} while ((csf_int32)tmp_total_length > tmp_receive_length
		&& csf_true == buffer.get_is_filled());		//�ж��Ƿ�������������Ҫ��ѭ������ֱ�������

	return tmp_receive_length;
}


/**
* ��Ҫ�����ǣ��첽��ȡ���ݣ�������ָ�����档
* ���أ�С�ڵ���0��ʾʧ�ܣ�����0��ʾ�ɹ���������ݳ��ȣ�
*
* @param buffer    ��ʾ���ݵĻ����ַ
* @param callback    ��ʾ��Ҫ���صĻص�����
*/
csf_int32 csf_tcp_connect::async_read(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	get_read_timeout().flush_time();

	get_socket().async_receive(boost::asio::buffer(buffer.get_buffer()->get_buffer(), buffer.get_length())
		, boost::bind(&csf_tcp_connect::ip_async_read_callback
			, this
			, std::ref(buffer)
			, shared_from_this()
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return 0;
}


/**
* ��Ҫ�����ǣ������첽д����ص�����
* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
*
* @param buffer		 ��ʾ���ݵĻ���
* @param connect_ptr ��ʾ��ǰ���������Ӷ���
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code  ��ʾboost�Ĵ�����Ϣ
* @param length		��ʾ��ǰʵ��д�Ļ��泤��
*/
csf_bool csf_tcp_connect::ip_async_write_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {


	//�������������մ�����
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	//����Ѿ���������������ݣ��������ص�����
	if (length >= buffer.get_length()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//���û�з�����ȫ�����в������ݣ�����»�����Ϣ��������
		buffer.get_buffer()->set_pos(buffer.get_buffer()->get_pos() + length);
		buffer.set_length(buffer.get_length() - length);

		async_write(std::ref(buffer), callback);
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ������첽������ص�����
* ���أ�0��ʾ����ɹ�����0��ʾ����ʧ��
*
* @param buffer		 ��ʾ���ݵĻ���
* @param connect_ptr ��ʾ��ǰ���������Ӷ���
* @param callback    ��ʾ�쳣��������Ϣ
* @param error_code  ��ʾboost�Ĵ�����Ϣ
* @param length   ��ʾ��ǰʵ��д�Ļ��泤��
*/
csf_bool csf_tcp_connect::ip_async_read_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {

	//�������������մ�����
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	//�����Ҫ�����������ݣ���������գ�ֱ������������ȫ
	if (csf_false == buffer.get_is_filled()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//����Ѿ���������������ݣ��������ص�����
		if (length >= buffer.get_length()) {
			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
			return csf_true;
		}
		else {
			//���û�з�����ȫ�����в������ݣ�����»�����Ϣ��������
			buffer.get_buffer()->set_pos(buffer.get_buffer()->get_pos() + length);
			buffer.set_length(buffer.get_length() - length);

			async_read(std::ref(buffer), callback);
		}
	}

	return csf_true;
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

		((csf_ip_url&)csf_ip_connect::get_local_url()).set_url(
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
		try {
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

	//Ϊÿ���������һ��ʱ�������ҪΪ�˷��㳬ʱ�������ӵȴ���
	get_acceptor()->async_accept(
		tmp_connect->get_socket()
		, boost::bind(&csf_tcp_connect::accept_handle
			, this
			, csf_tcp_connect_ptr(tmp_connect)
			, callback
			, _1));

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

	if (ec) {

		csf_log_ex(error
			, csf_log_code_error
			, "accept connect failed! reason:[%d] %s"
			, ec.value()
			, boost::system::system_error(ec).what());

		return;
	}

	//�����ȴ���һ��tcp��������
	async_accept(callback);

	//���ÿ����ӳ�ʱ�������������ʱ�䣬���ʾ�����ӣ���Ҫ�رմ���
	if (get_factory()) {
		connect_ptr->set_read_timeout(
			((csf_ip_connect_factory*)get_factory())->get_connect_timeout(), csf_nullptr);
	}
	else {
		connect_ptr->set_read_timeout(csf_connect_timeout_default_ms, csf_nullptr);
	}
	
	csf_log_ex(info
		, csf_log_code_info
		, "accept %s."
		, connect_ptr->to_string().c_str());

	//���ûص�����֪ͨ�������ݵȸ��ִ���
	async_callback((csf_connect_ptr&)connect_ptr, callback, csf_ip_connect_error());
}

