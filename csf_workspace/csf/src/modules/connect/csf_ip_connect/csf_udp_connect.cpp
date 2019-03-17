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
*Date: 25-2月-2019 19:09:10
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
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_udp_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示打开连接信息.
 * 返回：0表示成功；非0表示失败；
 *
 * @param url    表示连接地址
 */
csf_int32 csf_udp_connect::open(const csf_url& url) {

	return 0;
}


/**
 * 表示关闭连接.
 * 返回：0表示成功；非0表示失败；
 */
csf_int32 csf_udp_connect::close() {

	close_socket();

	return csf_connect::close();
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_udp_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设置连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_udp_connect::set_option() {

	return 0;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_udp_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示获取连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_udp_connect::get_option() {

	return 0;
}


/**
 * 主要功能是：需要连接一个地址。
 * 返回：0表示成功；非0表示失败；
 *
 * @param url    表示读取数据存在的指定缓存长度
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_udp_connect::connect(const csf_url& url, const csf_connect_callback& callback) {

	csf::modules::connect::csf_ip_url  tmp_ip_url;


	//对url内容进行合法性处理，避免出现处理异常
	if (csf_ip_url::is_valid_type(url)) {
		tmp_ip_url = (csf::modules::connect::csf_ip_url&)url;
	}
	else {
		if (csf_failure == tmp_ip_url.parse(url.get_url())) {
			csf_log_ex(error, csf_log_code_error
				, "connect [url:%s] failed! url format failed!"
				, url.get_url().c_str());
			return csf_failure;
		}
	}

	//设置远端地址
	set_send_endpoint(boost::asio::ip::udp::endpoint(
		boost::asio::ip::address::from_string(tmp_ip_url.get_ip())
		, tmp_ip_url.get_port()));
	//设置远端url
	set_remote_url(tmp_ip_url);
	//清除连接信息
	flush_string();

	csf_log_ex(notice, csf_log_code_notice
		, "connect[url:%s] succeed! %s"
		, tmp_ip_url.get_url().c_str()
		, to_string().c_str());

	return csf_succeed;
}


/**
* 主要功能是：打开一个监听地址。
* 返回：0表示成功；非0表示失败；
*
* @param url    表示需要监听的地址
* @param callback    表示读取数据存在的指定缓存长度
*/
csf_int32 csf_udp_connect::listen(const csf_url& url, const csf_connect_callback& callback) {

	csf::modules::connect::csf_ip_url  tmp_ip_url;


	//对url内容进行合法性处理，避免出现处理异常
	if (csf_ip_url::is_valid_type(url)) {
		tmp_ip_url = (csf::modules::connect::csf_ip_url&)url;
	}
	else {
		if (csf_failure == tmp_ip_url.parse(url.get_url())) {
			csf_log_ex(error, csf_log_code_error
				, "listen[url:%s] failed! url format failed!"
				, url.get_url().c_str());
			return csf_failure;
		}
	}

	try {
		//错误码
		boost::system::error_code	tmp_error_code;
		//创建一个连接点
		boost::asio::ip::udp::endpoint tmp_endpoint = listen_endpoint(tmp_ip_url);

		//打开一个udp连接对象
		get_socket().open(tmp_endpoint.protocol());

		//打开后配置socket属性
		set_option_after_open(tmp_ip_url);

		//绑定连接对象
		get_socket().bind(tmp_endpoint, tmp_error_code);
		if (tmp_error_code) {

			csf_ip_connect_error  tmp_connect_error(tmp_error_code);

			csf_log_ex(error, csf_log_code_error
				, "listen [url:%s] failed! reason:[%s]."
				, tmp_ip_url.get_url().c_str()
				, tmp_connect_error.to_string().c_str());

			exception_callback(shared_from_this()
				, callback
				, tmp_connect_error);
			return csf_failure;
		}
		//绑定后配置socket属性
		set_option_after_bind(tmp_ip_url);
		//设置本地url
		set_local_url(tmp_ip_url);
		//清除连接信息
		flush_string();

		//调用回调函数通知接收数据等各种处理
		async_callback(shared_from_this(), callback, csf_ip_connect_error());
	}
	catch (boost::exception& e) {

		csf_log_ex(error, csf_log_code_error
			, "listen [url:%s] failed! reason:[%s -- %s]."
			, tmp_ip_url.get_url().c_str()
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
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_udp_connect::write(csf_connect_buffer<csf_buffer>& buffer
	, csf_url& url
	, const csf_connect_callback& callback) {

	//如果地址为空，则返回失败
	if (url.get_url().empty()) {
		return csf_failure;
	}

	//如果地址不变，则不用更新发送地址
	if (get_remote_url().get_url() != url.get_url()) {

		if (csf_failure == connect(url, callback)) {
			return csf_failure;
		}
	}

	//调用发送函数
	return csf_ip_connect::write(buffer, callback);
}


/**
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示内容的缓存地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_udp_connect::sync_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer();
	csf_int32						tmp_total_length = buffer.get_length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	get_write_timeout().flush_time();

	//循环发送数据内容，直到数据发送完成为止
	while (tmp_send_length < (csf_int32)tmp_total_length)
	{
		tmp_length = get_socket().send_to(boost::asio::buffer(tmp_buf + tmp_send_length, tmp_total_length - tmp_send_length)
			, get_send_endpoint()
			, 0
			, tmp_error_code);
		if (tmp_length <= 0 || tmp_error_code) {

			exception_callback(shared_from_this()
				, callback
				, csf_ip_connect_error(tmp_error_code));

			return csf_failure;
		}
		tmp_send_length += tmp_length;
	}

	exception_callback(shared_from_this(), callback, csf_ip_connect_error());

	return tmp_total_length;
}


/**
* 主要功能是：同步读取数据，并放入指定缓存。
* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
*
* @param buffer    表示内容的缓存地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_udp_connect::sync_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	csf_uchar						*tmp_buf = buffer.get_buffer();
	csf_int32						tmp_total_length = buffer.get_length();
	csf_int32						tmp_length = 0;
	csf_int32						tmp_receive_length = 0;
	boost::system::error_code		tmp_error_code;


	do {

		get_read_timeout().flush_time();

		//接收数据
		tmp_length = get_socket().receive_from(boost::asio::buffer(tmp_buf + tmp_receive_length, tmp_total_length - tmp_receive_length)
			, get_receive_endpoint()
			, 0
			, tmp_error_code);
		if (tmp_error_code) {
			//如果出现通信错误，则错误处理
			exception_callback(shared_from_this(), callback, csf_ip_connect_error(tmp_error_code));
			return csf_failure;
		}
		else if (tmp_length <= 0) {
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
 * 表示写入指定缓存的内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 *
 * @param buffer    表示内容的缓存地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_udp_connect::async_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	get_write_timeout().flush_time();

	//这里主要是数据量一大，就发送不完全了。尤其在linux平台下更容易出现这个问题
	get_socket().async_send_to(boost::asio::buffer(buffer.get_buffer()
		, buffer.get_length())
		, get_send_endpoint()
		, boost::bind(&csf_udp_connect::async_write_callback
			, this
			, std::ref(buffer)
			, shared_from_this()
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return buffer.get_length();
}


/**
 * 主要功能是：异步读取数据，并放入指定缓存。
 * 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
 *
 * @param buffer    表示内容的缓存地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_udp_connect::async_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	get_read_timeout().flush_time();

	get_socket().async_receive_from(boost::asio::buffer(buffer.get_buffer(), buffer.get_length())
		, get_receive_endpoint()
		, 0
		, boost::bind(&csf_udp_connect::async_read_callback
			, this
			, std::ref(buffer)
			, shared_from_this()
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return 0;
}


/**
 * 主要功能：
 *    表示socket连接对象
 * 返回：
 *    0：表示成功；
 *    非0：表示失败；
 */
csf_int32 csf_udp_connect::close_socket() {

	if (get_socket().is_open()) {

		try {
			int									tmp_ret_int = 0;
			struct linger						tmp_linger = { 0, 0 };
			boost::system::error_code			tmp_error_code;


			//设置为立即关闭处理，避免出现延时关闭的问题
			tmp_ret_int = setsockopt(get_socket().native()
				, SOL_SOCKET
				, SO_LINGER
				, (char*)(&tmp_linger)
				, sizeof(struct linger));

			//取消所有处理，关闭收发，关闭连接对象
			get_socket().cancel();
			get_socket().shutdown(boost::asio::socket_base::shutdown_both, tmp_error_code);
			get_socket().close();
		}
		catch (boost::exception& e) {
			csf_log_ex(error
				, csf_log_code_error
				, "close %s failed! reason:[%s -- %s]."
				, to_string().c_str()
				, boost::current_exception_diagnostic_information().c_str()
				, boost::diagnostic_information(e).c_str());

			return csf_failure;
		}
	}

	return csf_succeed;
}


/**
* 表示远程的主机地址
*/
const csf_url& csf_udp_connect::get_remote_url() const {

	return csf_ip_connect::get_remote_url();
}


/**
* 表示本地的主机地址
*/
const csf_url& csf_udp_connect::get_local_url() const {

	//判断现在的地址是否存在，存在则直接返回
	if (csf_ip_connect::get_local_url().get_url().empty()
		&& get_socket().is_open()) {

		((csf_ip_url&)csf_ip_connect::get_local_url()).set_url(
			get_socket().local_endpoint().address().to_string()
			, get_socket().local_endpoint().port());
	}

	return csf_ip_connect::get_local_url();
}


/**
* 主要功能是：
*    创建一个地址监听用的endpoint。不同的类型包括单播、组播、广播
* 返回：
*    一个endpoint对象
*
* @param url    表示当前的ip url地址信息
*/
boost::asio::ip::udp::endpoint csf_udp_connect::listen_endpoint(csf::modules::connect::csf_ip_url& url) {

	boost::asio::ip::udp	tmp_protocol = boost::asio::ip::udp::v4();


	//获取udp的协议类型，支持ipv4和ipv6
	if (url.is_ipv6()) {
		tmp_protocol = boost::asio::ip::udp::v6();
	}
	//创建一个endpoint
	if (csf_connect::csf_connect_type_multicast
	 	== (get_type() & csf_connect::csf_connect_type_multicast)) {

		return boost::asio::ip::udp::endpoint(
			tmp_protocol
			, url.get_port());
	}
	else if (csf_connect::csf_connect_type_broadcast
		== (get_type() & csf_connect::csf_connect_type_broadcast)) {
#if __linux__
		return boost::asio::ip::udp::endpoint(
			boost::asio::ip::address::from_string(url.get_ip())
			, url.get_port());
#else
		return boost::asio::ip::udp::endpoint(
			tmp_protocol
			, url.get_port());
#endif
	}
	else {
		return boost::asio::ip::udp::endpoint(
			boost::asio::ip::address::from_string(url.get_ip())
			, url.get_port());
	}
}


/**
* 主要功能是：
*    在socket打开之后设置选项
* 返回：
*    true ：表示设置成功；
*    false：表示设置失败；
*
* @param url    表示当前的ip url地址信息
*/
csf_bool csf_udp_connect::set_option_after_open(csf::modules::connect::csf_ip_url& url) {

	if (csf_connect::csf_connect_type_multicast
		== (get_type() & csf_connect::csf_connect_type_multicast)) {

		//配置地址复用
		get_socket().set_option(boost::asio::ip::udp::socket::reuse_address(true));
	}
	else if (csf_connect::csf_connect_type_broadcast
		== (get_type() & csf_connect::csf_connect_type_broadcast)) {

		//如果是广播地址，则需要开启广播功能
		get_socket().set_option(boost::asio::socket_base::broadcast(true));
	}
	else {

		//udp的设置项
	}

	return csf_true;
}


/**
* 主要功能是：
*    在socket绑定之后设置选项
* 返回：
*    true ：表示设置成功；
*    false：表示设置失败；
*
* @param url    表示当前的ip url地址信息
*/
csf_bool csf_udp_connect::set_option_after_bind(csf::modules::connect::csf_ip_url& url) {

	if (csf_connect::csf_connect_type_multicast
		== (get_type() & csf_connect::csf_connect_type_multicast)) {

		//配置地址复用
		get_socket().set_option(boost::asio::ip::udp::socket::reuse_address(true));
		/* Enable reception of our own multicast */
		// 		ret_int = setsockopt(m_udp_socket.native(), IPPROTO_IP, IP_MULTICAST_LOOP, (char*)(&loop), sizeof(loop));
		// 		if (ret_int)
		// 		{
		// 			return PC_FALSE;
		// 		}
		get_socket().set_option(boost::asio::ip::multicast::enable_loopback(false));

		get_socket().set_option(
			boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string(url.get_ip())));
	}
	else if (csf_connect::csf_connect_type_broadcast
		== (get_type() & csf_connect::csf_connect_type_broadcast)) {

		//如果是广播地址，则需要开启广播功能
		get_socket().set_option(boost::asio::socket_base::broadcast(true));
	}
	else {

		//udp的设置项
	}
	/* Set the TTL on packets to 250 */
	// 		ret_int = setsockopt(m_udp_socket.native(), IPPROTO_IP, IP_MULTICAST_TTL, (char*)(&ttl), sizeof(ttl));
	// 		if (ret_int)
	// 		{
	// 			return PC_FALSE;
	// 		}
	get_socket().set_option(boost::asio::ip::multicast::hops(csf_udp_connect_default_tll));

	return csf_true;
}