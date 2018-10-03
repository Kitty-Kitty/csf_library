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

	return 0;
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
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(buf, len, callback);
}


/**
* 表示写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_buffer& buffer
	, const csf_connect_callback callback) {

	return write(((csf_buffer&)buffer).get_buffer(), ((csf_buffer&)buffer).length(), callback);
}


/**
* 表示发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_csfstring& csfstr
	, const csf_connect_callback callback) {

	return write(((csf_csfstring&)csfstr).get_buffer(), ((csf_csfstring&)csfstr).length(), callback);
}


/**
* 表示发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_chain& chain
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(chain, callback);
}


/**
* 表示写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_buffer& buffer
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(buffer, callback);
}


/**
* 表示写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
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
	get_socket().async_write_some(boost::asio::buffer(buf, len),
		boost::bind(&csf_tcp_connect::async_write_callback
			, this
			, callback
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred));

	return len;
}


/**
* 表示发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_csfstring& csfstr
	, const csf_url& url
	, const csf_connect_callback callback) {

	return write(csfstr, callback);
}


/**
* 表示发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_tcp_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buf    表示读取数据存在的指定缓存地址
*
* @param len    表示读取数据存在的指定缓存长度
* @param url    表示发送数据的远端地址
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param chain    表示读取数据存在的csf_csfstring
* @param url    表示发送数据的远端地址
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_chain& chain
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的csf_buffer
* @param url    表示发送数据的远端地址
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_buffer& buffer
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的csf_buffer
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_buffer& buffer
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buf    表示读取数据存在的指定缓存地址
*
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_uchar* buf
	, const csf_uint32 len
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param csfstr    表示读取数据存在的csf_csfstring
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_csfstring& csfstr
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param csfstr    表示读取数据存在的csf_csfstring
* @param url    表示发送数据的远端地址
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_csfstring& csfstr
	, const csf_url& url
	, const csf_connect_callback callback) {

	return 0;
}


/**
* 表示读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param chain    表示读取数据存在的csf_csfstring
* @param callback    表示读取的回调函数
*/
csf_int32 csf_tcp_connect::read(const csf_chain& chain
	, const csf_connect_callback callback) {

	return 0;
}