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
*Date: 27-6月-2018 17:28:49
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
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_stream_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示打开连接信息
 * 
 * @param url    表示连接地址
 */
void csf_stream_connect::open(csf::core::module::device::csf_url url) {

}


/**
 * 表示关闭连接
 */
csf::core::base::csf_uint32 csf_stream_connect::close() {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_stream_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param csfstr    表示读取数据存在的csf_csfstring
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_stream_connect::read(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_stream_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示连接的类型
 */
csf::core::module::device::csf_connect_type csf_stream_connect::get_type() {

	return m_type;
}


/**
 * 表示写入指定缓存的内容
 * 
 * @param buffer    表示内容的缓存地址
 * @param length    表示内容缓存的长度
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_stream_connect::write(csf_uchar* buffer, csf_uint32 length, csf_url& url, csf_connect_callback callback) {

	return 0;
}


void csf_stream_connect::get_address() {

}


/**
 * 表示连接的类型
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
 * 表示本地的主机地址
 */
csf_url& csf_stream_connect::get_local_url() {

	return m_local_url;
}


void csf_stream_connect::get_option() {

}


/**
 * 表示本地的主机地址
 * 
 * @param newVal
 */
csf_int32 csf_stream_connect::set_local_url(csf_url& newVal) {

	m_local_url = newVal;
}


/**
 * 表示写入csf_buffer内容
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_stream_connect::write(csf_buffer& buffer, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_stream_connect::write(csf_csfstring& csfstr, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_stream_connect::write(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入csf_buffer内容
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_stream_connect::write(csf_buffer& buffer, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入指定缓存的内容
 * 
 * @param buffer    表示内容的缓存地址
 * @param length    表示内容缓存的长度
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_stream_connect::write(csf_uchar* buffer, csf_uint32 length, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buffer    表示读取数据存在的指定缓存地址
 * 
 * @param length    表示读取数据存在的指定缓存长度
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_stream_connect::read(csf_uchar* buffer, csf_int32 length, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buffer    表示读取数据存在的csf_buffer
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_stream_connect::read(csf_buffer& buffer, csf_url& url, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buffer    表示读取数据存在的csf_buffer
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_stream_connect::read(csf_buffer& buffer, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buffer    表示读取数据存在的指定缓存地址
 * 
 * @param length    表示读取数据存在的指定缓存长度
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_stream_connect::read(csf_uchar* buffer, csf_int32 length, csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param csfstr    表示读取数据存在的csf_csfstring
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_stream_connect::read(csf_csfstring& csfstr, csf_connect_callback callback) {

	return 0;
}