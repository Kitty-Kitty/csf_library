/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 15:10:39
*
*Description: Class(csf_ip_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connect.hpp"

using csf::modules::connect::csf_ip_connect;



csf_ip_connect::~csf_ip_connect() {

}


csf_url& csf_ip_connect::get_remote_url() {

	return m_remote_url;
}


/**
*
* @param new_value
*/
csf_int32 csf_ip_connect::set_remote_url(csf_url& new_value) {

	if (csf_ip_url::is_valid_type(new_value)) {
		m_remote_url = (csf_ip_url&)new_value;
		return csf_success;
	}

	return csf_failure;
}


/**
* 表示本地的主机地址
*/
csf_url& csf_ip_connect::get_local_url() {

	return m_local_url;
}


/**
* 表示本地的主机地址
*
* @param new_value
*/
csf_int32 csf_ip_connect::set_local_url(csf_url& new_value) {

	if (csf_ip_url::is_valid_type(new_value)) {
		m_local_url = (csf_ip_url&)new_value;
		return csf_success;
	}

	return csf_failure;
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
csf_int32 csf_ip_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入csf_buffer内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_ip_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_ip_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param chain    表示csf_chain的内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_ip_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入csf_buffer内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_ip_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_ip_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_ip_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param chain    表示csf_chain的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_ip_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}


/**
*
* @param callback    表示异常处理句柄信息
* @param error_code    表示boost的错误信息
* @param len    表示数据长度信息
*/
csf_bool csf_ip_connect::async_write_callback(const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 len) {

	async_callback(this, callback, csf_ip_connect_error(error_code));
	return csf_true;
}


/**
*
* @param callback    表示异常处理句柄信息
* @param error_code    表示boost的错误信息
* @param len    表示数据长度信息
*/
csf_bool csf_ip_connect::async_read_callback(const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 len) {

	async_callback(this, callback, csf_ip_connect_error(error_code));
	return csf_true;
}