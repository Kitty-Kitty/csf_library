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
csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_chain& chain, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buf    表示读取数据存在的指定缓存地址
*
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_char_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的csf_buffer
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_buffer_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param csfstr    表示读取数据存在的csf_csfstring
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_csfstr_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param chain    表示读取数据存在的csf_csfstring
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_chain& chain, const csf_uint32 len, const csf_chain_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存放的缓存对象
*
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_char_buffer_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_buffer_buffer_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_csfstr_buffer_read_callback& callback) {

	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_chain_buffer_read_callback& callback) {

	return 0;
}


/**
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::sync_write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	csf_int32						tmp_length = 0;
	csf_int32						tmp_send_length = 0;
	boost::system::error_code		tmp_error_code;


	//循环发送数据内容，直到数据发送完成为止
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
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::async_write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	//这里主要是数据量一大，就发送不完全了。尤其在linux平台下更容易出现这个问题
	get_socket().async_write_some(boost::asio::buffer(buf, len)
			, boost::bind(&csf_tcp_connect::async_write_callback
			, this
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return len;
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

		((csf_ip_url&)csf_ip_connect::get_remote_url()).set_url(
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
		try	{
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

	csf_tcp_connect_ptr connect_ptr(tmp_connect);

	//为每个连接添加一个时间戳，主要为了方便超时、空连接等处理
	//conn_socket_ptr->m_time = m_parking_p->m_current_millsec;
	get_acceptor()->async_accept(
		connect_ptr->get_socket()
		, boost::bind(&csf_tcp_connect::accept_handle, this, connect_ptr, callback, _1));

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

	//如果有连接进入，则调用
	if (csf_nullptr != callback) {
		callback(connect_ptr, csf_connect_error());
	}
}


csf_bool csf_tcp_connect::read_handle(csf_tcp_connect_ptr connect_ptr, const boost::system::error_code ec, csf_uint32 str_len) {

	return csf_true;
}