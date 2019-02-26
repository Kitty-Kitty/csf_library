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
*Date: 02-10月-2018 14:18:00
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
* 模块初始化
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_tcp_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* 表示打开连接信息.
* 返回：0表示成功；非0表示失败；
*
* @param url    表示连接地址
*/
csf_int32 csf_tcp_connect::open(const csf_url& url) {

	return 0;
}


/**
* 表示关闭连接.
* 返回：0表示成功；非0表示失败；
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
* 模块启动
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_tcp_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* 表示设置连接的属性项目信息。
* 返回：0表示成功；非0表示失败。
*/
csf_int32 csf_tcp_connect::set_option() {

	return 0;
}


/**
* 模块停止
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_tcp_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* 主要功能是：打开一个监听地址。
* 返回：0表示成功；非0表示失败；
*
* @param url    表示需要监听的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::listen(const csf_url& url, const csf_connect_callback& callback) {

	csf::modules::connect::csf_ip_url &ip_url = (csf::modules::connect::csf_ip_url&)url;

	try {
		//如果已经监听了，则返回失败
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

		//创建一个acceptor，用于实现tcp监听
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
* 主要功能是：需要连接一个地址。
* 返回：0表示成功；非0表示失败；
*
* @param url    表示需要监听的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::connect(const csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//这里可以不进行数据的校验处理，这样会减少数据读取的效率
// 	if (csf_nullptr == buf
// 		|| len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes
// 				, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//根据是否有回调函数，来判断使用异步还是同步
// 	if (csf_nullptr == callback) {
// 		return sync_write(buf, len, callback);
// 	}
// 	else {
// 		return async_write(buf, len, callback);
// 	}
// 	return 0;
// }


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {
// 
// 	return write(buffer.get_buffer(), buffer.length(), callback);
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {
// 
// 	return write(csfstr.get_buffer(), csfstr.length(), callback);
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param callback    表示需要返回的回调函数
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
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//根据csf_connect_buffer的标志位来判断异步与同步
// 	if (buffer.get_is_sync()) {
// 		return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//先判断数据的合法性，之后再处理
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
		return csf_failure;
	}

	//根据csf_connect_buffer的标志位来判断异步与同步
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
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
// 	if (!buffer.is_valid()) {
// 		return exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 	}
// 
// 	//根据csf_connect_buffer的标志位来判断异步与同步
// 	if (buffer.get_is_sync()) {
// 		return sync_write(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
// 	if (!buffer.is_valid()) {
// 		return exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 	}
// 
// 	//先将chain转化为buffer，成为一个连续的内存空间后处理
// 	csf_buffer				tmp_buffer(buffer.get_buffer()->length());
// 
// 	buffer.get_buffer()->convert(tmp_buffer);
// 
// 	//根据csf_connect_buffer的标志位来判断异步与同步
// 	if (buffer.get_is_sync()) {
// 		return sync_write(tmp_buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_write(tmp_buffer.get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buf    表示读取数据存在的指定缓存地址
*
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
// 	if (csf_nullptr == buf
// 		|| len <= 0) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
// 		return csf_failure;
// 	}
// 
// 	//根据csf_connect_buffer的标志位来判断异步与同步
// 	if (csf_nullptr == callback) {
// 		return sync_read(buf, len, callback);
// 	}
// 	else {
// 		return async_read(buf, len, callback);
// 	}
// 	return 0;
// }


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的csf_buffer
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//剩余空间充足时，则直接处理
// 	if (buffer.avail() >= len) {
// 		return read(buffer.get_buffer(), len, callback);
// 	}
// 	else {
// 		//如果剩余的空间不足，则报出异常
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
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param csfstr    表示读取数据存在的csf_csfstring
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//剩余空间充足时，则直接处理
// 	if (csfstr.length() >= len) {
// 		return read(csfstr.get_buffer(), len, callback);
// 	}
// 	else {
// 		//如果剩余的空间不足，则报出异常
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
* 主要功能是：读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param chain    表示读取数据存在的csf_csfstring
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
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
// 	//chain只能进行同步接收和保存处理
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
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存放的缓存对象
*
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 	//更新filled标志位
// 	set_is_filled(buffer.get_is_filled());
// 
// 	//根据csf_connect_buffer的标志位来判断异步与同步
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
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//先判断数据的合法性，之后再处理
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
				, "not enough storage available"));
		return csf_failure;
	}
	//更新filled标志位
	set_is_filled(buffer.get_is_filled());

	//根据csf_connect_buffer的标志位来判断异步与同步
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
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
// 	if (!buffer.is_valid()) {
// 		exception_callback(shared_from_this()
// 			, callback
// 			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
// 				, "not enough storage available"));
// 		return csf_failure;
// 	}
// 	//更新filled标志位
// 	set_is_filled(buffer.get_is_filled());
// 
// 	//根据csf_connect_buffer的标志位来判断异步与同步
// 	if (buffer.get_is_sync()) {
// 		return sync_read(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	else {
// 		return async_read(buffer.get_buffer()->get_buffer(), buffer.get_length(), callback);
// 	}
// 	return 0;
// }


/**
* 主要功能是：读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	//先判断数据的合法性，之后再处理
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
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
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
// 	//循环发送数据内容，直到数据发送完成为止
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
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_tcp_connect::async_write(const csf_uchar* buf
// 	, const csf_uint32 len
// 	, const csf_connect_callback& callback) {
// 
// 	get_write_timeout().flush_time();
// 
// 	//这里主要是数据量一大，就发送不完全了。尤其在linux平台下更容易出现这个问题
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
* 主要功能是：处理异步写处理回调函数
* 返回：0表示处理成功；非0表示处理失败
*
* @param buf		 表示内容的缓存地址
* @param src_len	 表示需要被处理的源内容缓存的长度
* @param callback    表示异常处理句柄信息
* @param error_code  表示boost的错误信息
* @param write_len   表示当前实际写的缓存长度
*/
// csf_bool csf_tcp_connect::ip_async_write_callback(const csf_uchar* buf
// 	, const csf_uint32 src_len
// 	, const csf_connect_callback& callback
// 	, const boost::system::error_code& error_code
// 	, csf_uint32 write_len) {
// 
// 	//如果处理错误，则按照错误处理
// 	if (error_code) {
// 		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_false;
// 	}
// 	//如果已经发送完成所有数据，则正常回调返回
// 	if (write_len >= src_len) {
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_true;
// 	}
// 	else {
// 		//如果没有发送完全，还有部分数据，则继续发送
// 		async_write(buf + write_len, src_len - write_len, callback);
// 	}
// 
// 	return csf_true;
// }


/**
* 主要功能是：同步读取数据，并放入指定缓存。
* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
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
// 		//接收数据
// 		tmp_length = get_socket().receive(boost::asio::buffer(buf + tmp_receive_length, len - tmp_receive_length)
// 			, 0
// 			, tmp_error_code);
// 		if (tmp_error_code) {
// 			//如果出现通信错误，则错误处理
// 			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
// 			return csf_failure;
// 		}
// 		else if (tmp_receive_length <= 0) {
// 			//如果出现数据内容错误，则另外处理
// 			csf_ip_connect_error			tmp_error;
// 
// 			tmp_error.set_error(csf_connect_error::csf_connect_code_operation_error
// 				,"receive data length[ %d <=0 ]"
// 				, tmp_length);
// 			exception_callback(shared_from_this(), callback, tmp_error);
// 			return csf_failure;
// 		}
// 		else {
// 			//累加数据长度
// 			tmp_receive_length += tmp_length;
// 		}
// 
// 	} while ((csf_int32)len > tmp_receive_length && csf_true == get_is_filled());		//判断是否填充满，如果需要则循环处理直到填充满
// 
// 	return tmp_receive_length;
// }


/**
* 主要功能是：异步读取数据，并放入指定缓存。
* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
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
* 主要功能是：处理异步读处理回调函数
* 返回：0表示处理成功；非0表示处理失败
*
* @param buf		 表示内容的缓存地址
* @param buf_len	 表示需要被处理的源内容缓存的长度
* @param callback    表示异常处理句柄信息
* @param error_code  表示boost的错误信息
* @param read_len   表示当前实际写的缓存长度
*/
// csf_bool csf_tcp_connect::ip_async_read_callback(csf_uchar* buf
// 	, const csf_uint32 buf_len
// 	, const csf_connect_callback& callback
// 	, const boost::system::error_code& error_code
// 	, csf_uint32 read_len) {
// 
// 	//如果处理错误，则按照错误处理
// 	if (error_code) {
// 		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_false;
// 	}
// 
// 	//如果需要接收所有数据，则继续接收，直到完整接收完全
// 	if (csf_false == get_is_filled()) {
// 		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 		return csf_true;
// 	}
// 	else {
// 		//如果已经发送完成所有数据，则正常回调返回
// 		if (read_len >= buf_len) {
// 			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
// 			return csf_true;
// 		}
// 		else {
// 			//如果没有发送完全，还有部分数据，则继续发送
// 			async_read(buf + read_len, buf_len - read_len, callback);
// 		}
// 	}
// 
// 	return csf_true;
// }




/**
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示内容的缓存地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::sync_write(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer()->get_buffer();
	csf_int32						tmp_total_length = buffer.get_buffer()->length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	get_write_timeout().flush_time();

	//循环发送数据内容，直到数据发送完成为止
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
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示内容的缓存地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::async_write(csf_connect_buffer<csf_buffer>& buffer
	, const csf_connect_callback& callback) {


	get_write_timeout().flush_time();

	//这里主要是数据量一大，就发送不完全了。尤其在linux平台下更容易出现这个问题
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
* 主要功能是：同步读取数据，并放入指定缓存。
* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
*
* @param buffer    表示内容的缓存地址
* @param callback    表示需要返回的回调函数
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

		//接收数据
		tmp_length = get_socket().receive(boost::asio::buffer(tmp_buf + tmp_receive_length
			, tmp_total_length - tmp_receive_length)
			, 0
			, tmp_error_code);
		if (tmp_error_code) {
			//如果出现通信错误，则错误处理
			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
			return csf_failure;
		}
		else if (tmp_receive_length <= 0) {
			//如果出现数据内容错误，则另外处理
			csf_ip_connect_error			tmp_error;

			tmp_error.set_error(csf_connect_error::csf_connect_code_operation_error
				, "receive data length[ %d <= 0 ]"
				, tmp_length);
			exception_callback(shared_from_this(), callback, tmp_error);
			return csf_failure;
		}
		else {
			//累加数据长度
			tmp_receive_length += tmp_length;
		}

	} while ((csf_int32)tmp_total_length > tmp_receive_length
		&& csf_true == buffer.get_is_filled());		//判断是否填充满，如果需要则循环处理直到填充满

	return tmp_receive_length;
}


/**
* 主要功能是：异步读取数据，并放入指定缓存。
* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
*
* @param buffer    表示内容的缓存地址
* @param callback    表示需要返回的回调函数
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
* 主要功能是：处理异步写处理回调函数
* 返回：0表示处理成功；非0表示处理失败
*
* @param buffer		 表示内容的缓存
* @param connect_ptr 表示当前的网络连接对象
* @param callback    表示异常处理句柄信息
* @param error_code  表示boost的错误信息
* @param length		表示当前实际写的缓存长度
*/
csf_bool csf_tcp_connect::ip_async_write_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {


	//如果处理错误，则按照错误处理
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	//如果已经发送完成所有数据，则正常回调返回
	if (length >= buffer.get_length()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//如果没有发送完全，还有部分数据，则更新缓存信息继续发送
		buffer.get_buffer()->set_pos(buffer.get_buffer()->get_pos() + length);
		buffer.set_length(buffer.get_length() - length);

		async_write(std::ref(buffer), callback);
	}

	return csf_true;
}


/**
* 主要功能是：处理异步读处理回调函数
* 返回：0表示处理成功；非0表示处理失败
*
* @param buffer		 表示内容的缓存
* @param connect_ptr 表示当前的网络连接对象
* @param callback    表示异常处理句柄信息
* @param error_code  表示boost的错误信息
* @param length   表示当前实际写的缓存长度
*/
csf_bool csf_tcp_connect::ip_async_read_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {

	//如果处理错误，则按照错误处理
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	//如果需要接收所有数据，则继续接收，直到完整接收完全
	if (csf_false == buffer.get_is_filled()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//如果已经发送完成所有数据，则正常回调返回
		if (length >= buffer.get_length()) {
			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
			return csf_true;
		}
		else {
			//如果没有发送完全，还有部分数据，则更新缓存信息继续发送
			buffer.get_buffer()->set_pos(buffer.get_buffer()->get_pos() + length);
			buffer.set_length(buffer.get_length() - length);

			async_read(std::ref(buffer), callback);
		}
	}

	return csf_true;
}


/**
* 表示远程的主机地址
*/
const csf_url& csf_tcp_connect::get_remote_url() const {

	//判断现在的地址是否存在，存在则直接返回
	if (csf_ip_connect::get_remote_url().get_url().empty()) {

		((csf_ip_url&)csf_ip_connect::get_remote_url()).set_url(
			get_socket().remote_endpoint().address().to_string()
			, get_socket().remote_endpoint().port());
	}

	return csf_ip_connect::get_remote_url();
}


/**
* 表示本地的主机地址
*/
const csf_url& csf_tcp_connect::get_local_url() const {

	//判断现在的地址是否存在，存在则直接返回
	if (csf_ip_connect::get_local_url().get_url().empty()) {

		((csf_ip_url&)csf_ip_connect::get_local_url()).set_url(
			get_socket().local_endpoint().address().to_string()
			, get_socket().local_endpoint().port());
	}

	return csf_ip_connect::get_local_url();
}


/**
* 主要功能是：异步tcp监听的accept处理函数。
* 返回：0表示成功；非0表示失败；
*
* @param callback    表示需要返回的回调函数
*/
csf::core::base::csf_int32 csf_tcp_connect::async_accept(const csf_connect_callback callback) {

	csf_tcp_connect		*tmp_connect = csf_nullptr;


	while (csf_true) {
		try {
			//这里主要解决有些时候new失败的问题
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

	//为每个连接添加一个时间戳，主要为了方便超时、空连接等处理
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
* 主要功能是：异步tcp监听的accept回调处理函数。
* 返回：无
*
* @param connect_ptr    表示当前网络通信连接对象
* @param callback    表示需要返回的回调函数
* @param ec    表示当前的错误信息
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

	//继续等待下一个tcp连接请求
	async_accept(callback);

	//设置空连接超时处理。如果超过该时间，则表示空连接，需要关闭处理。
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

	//调用回调函数通知接收数据等各种处理
	async_callback((csf_connect_ptr&)connect_ptr, callback, csf_ip_connect_error());
}

