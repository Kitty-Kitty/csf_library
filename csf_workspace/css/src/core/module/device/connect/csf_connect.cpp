﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:37
*
*Description: Class(csf_connect)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_connect.hpp"

using csf::core::module::device::csf_connect;


csf_connect::csf_connect()
	: m_type(csf_connect_type_none)
	, m_sync(csf_false)
	, m_status(0)
	, m_factory(csf_null)
	, m_read_timeout(0)
	, m_write_timeout(0) {

}



csf_connect::~csf_connect() {

}





/**
 * 表示通过factory创建一个connect
 * 
 * @param factory    表示需要创建connect的工厂类
 */
csf_void csf_connect::csf_connect(csf_connect_factory* factory) {

}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


csf_url& csf_connect::get_remote_url() {

	return m_remote_url;
}


/**
 * 
 * @param newVal
 */
csf_int32 csf_connect::set_remote_url(csf_url& newVal) {

	m_remote_url = newVal;
}


/**
 * 表示本地的主机地址
 */
csf_url& csf_connect::get_local_url() {

	return m_local_url;
}


/**
 * 表示本地的主机地址
 * 
 * @param newVal
 */
csf_int32 csf_connect::set_local_url(csf_url& newVal) {

	m_local_url = newVal;
}


/**
 * 表示创建connect的工厂类地址
 */
csf_connect_factory* csf_connect::get_factory() {

	return m_factory;
}


/**
 * 表示创建connect的工厂类地址
 * 
 * @param newVal
 */
void csf_connect::set_factory(csf_connect_factory* newVal) {

	m_factory = newVal;
}


csf_uint32 csf_connect::get_read_timeout() {

	return m_read_timeout;
}


/**
 * 
 * @param newVal
 */
void csf_connect::set_read_timeout(csf_uint32 newVal) {

	m_read_timeout = newVal;
}


/**
 * 表示写超时时间，单位为毫秒。
 */
csf_uint32 csf_connect::get_write_timeout() {

	return m_write_timeout;
}


/**
 * 表示写超时时间，单位为毫秒。
 * 
 * @param newVal
 */
void csf_connect::set_write_timeout(csf_uint32 newVal) {

	m_write_timeout = newVal;
}


/**
 * 表示打开连接信息
 * 
 * @param url    表示连接地址
 */
void csf_connect::open(const csf_url& url) {

}


/**
 * 表示关闭连接
 */
csf::core::base::csf_uint32 csf_connect::close() {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存链表中
 * 
 * @param chain    表示读取数据存在的csf_csfstring
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入指定缓存的内容
 * 
 * @param buf    表示内容的缓存地址
 * @param len    表示内容缓存的长度
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


void csf_connect::set_option() {

}


void csf_connect::get_option() {

}


/**
 * 表示写入csf_buffer内容
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容
 * 
 * @param chain    表示csf_chain的内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入csf_buffer内容
 * 
 * @param buffer    表示需要写入的csf_buffer内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示写入指定缓存的内容
 * 
 * @param buf    表示内容的缓存地址
 * @param len    表示内容缓存的长度
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buf    表示读取数据存在的指定缓存地址
 * 
 * @param len    表示读取数据存在的指定缓存长度
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buffer    表示读取数据存在的csf_buffer
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buffer    表示读取数据存在的csf_buffer
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_buffer& buffer, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param buf    表示读取数据存在的指定缓存地址
 * 
 * @param len    表示读取数据存在的指定缓存长度
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param csfstr    表示读取数据存在的csf_csfstring
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_csfstring& csfstr, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容
 * 
 * @param csfstr    表示csf_csfstring的内容
 * @param url    表示需要发送数据的目的地址
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示设置读超时时间
 * 
 * @param timeout_ms
 * @param callback    表示超时回调函数。
 */
csf_int32 csf_connect::set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示发送csf_csfstring内容
 * 
 * @param chain    表示csf_chain的内容
 * @param callback    表示需要返回的回调函数
 */
csf_int32 csf_connect::write(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示设置写超时时间
 * 
 * @param timeout_ms
 * @param callback    表示超时回调函数。
 */
csf_int32 csf_connect::set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存位置
 * 
 * @param csfstr    表示读取数据存在的csf_csfstring
 * @param url    表示发送数据的远端地址
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示读取数据并存在指定缓存链表中
 * 
 * @param chain    表示读取数据存在的csf_csfstring
 * @param callback    表示读取的回调函数
 */
csf_int32 csf_connect::read(const csf_chain& chain, const csf_connect_callback callback) {

	return 0;
}