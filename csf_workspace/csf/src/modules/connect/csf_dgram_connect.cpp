/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_dgram_connect.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 29-7月-2018 15:13:08
*
*Description: Class(csf_dgram_connect) 表示通信库，网络报文连接信息内容
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_dgram_connect.hpp"

using csf::modules::connect::csf_dgram_connect;


csf_dgram_connect::csf_dgram_connect()
	: m_type(csf_connect_type_none)
	, m_sync(csf_false)
	, m_status(0)
	, m_factory(csf_nullptr)
	, m_read_timeout(0)
	, m_write_timeout(0)
	, m_configure_manager(csf_nullptr) {

}



csf_dgram_connect::~csf_dgram_connect() {

}





/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_dgram_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示打开连接信息.
 * 返回：0表示成功；非0表示失败；
 * 
 * @param url    表示连接地址
 */
csf_int32 csf_dgram_connect::open(const csf_url& url) {

	return 0;
}


/**
 * 表示关闭连接.
 * 返回：0表示成功；非0表示失败；
 */
csf_int32 csf_dgram_connect::close() {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_dgram_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设置连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_dgram_connect::set_option() {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_dgram_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示获取连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_dgram_connect::get_option() {

	return 0;
}


/**
 * 表示设置读超时时间.
 * 返回：0表示成功；非0表示失败；
 * 
 * @param timeout_ms
 * @param callback    表示超时回调函数。
 */
csf_int32 csf_dgram_connect::set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


csf_url& csf_dgram_connect::get_remote_url() {

	return m_remote_url;
}


/**
 * 表示设置写超时时间。
 * 返回：0表示成功；非0表示失败；
 * 
 * @param timeout_ms
 * @param callback    表示超时回调函数。
 */
csf_int32 csf_dgram_connect::set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * 
 * @param newVal
 */
csf_int32 csf_dgram_connect::set_remote_url(csf_url& newVal) {

	m_remote_url = newVal;

	return csf_success;
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
csf_int32 csf_dgram_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示本地的主机地址
 */
csf_url& csf_dgram_connect::get_local_url() {

	return m_local_url;
}


/**
 * 表示写入csf_buffer内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_dgram_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示本地的主机地址
 * 
 * @param newVal
 */
csf_int32 csf_dgram_connect::set_local_url(csf_url& newVal) {

	m_local_url = newVal;

	return csf_success;
}


/**
 * 表示发送csf_csfstring内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_dgram_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容。
 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
 * 
 * @param chain    表示csf_chain的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_dgram_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示创建connect的工厂类地址
 */
csf_connect_factory* csf_dgram_connect::get_factory() {

	return m_factory;
}


/**
 * 表示读取数据并存在指定缓存链表中。
 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
 * 
 * @param chain    表示读取数据存在的csf_csfstring
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_dgram_connect::read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示创建connect的工厂类地址
 * 
 * @param newVal
 */
csf_void csf_dgram_connect::set_factory(csf_connect_factory* newVal) {

	m_factory = newVal;
}


csf_uint32 csf_dgram_connect::get_read_timeout() {

	return m_read_timeout;
}


/**
 * 表示读取数据并存在指定缓存位置。
 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
 * 
 * @param buffer    表示读取数据存在的csf_buffer
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_dgram_connect::read(const csf_buffer& buffer, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * 
 * @param newVal
 */
csf_void csf_dgram_connect::set_read_timeout(csf_uint32 newVal) {

	m_read_timeout = newVal;
}


/**
 * 表示写超时时间，单位为毫秒。
 */
csf_uint32 csf_dgram_connect::get_write_timeout() {

	return m_write_timeout;
}


/**
 * 表示读取数据并存在指定缓存位置。
 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
 * 
 * @param csfstr    表示读取数据存在的csf_csfstring
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_dgram_connect::read(const csf_csfstring& csfstr, const csf_connect_callback callback) {

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
csf_int32 csf_dgram_connect::read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写超时时间，单位为毫秒。
 * 
 * @param newVal
 */
csf_void csf_dgram_connect::set_write_timeout(csf_uint32 newVal) {

	m_write_timeout = newVal;
}


/**
 * 表示读取数据并存在指定缓存链表中。
 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
 * 
 * @param chain    表示读取数据存在的csf_csfstring
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_dgram_connect::read(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}