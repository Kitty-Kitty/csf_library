/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Version: 1.0
*
*Date: 02-10月-2018 14:17:59
*
*Description: Class(csf_stream_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_stream_connect.hpp"

using csf::modules::connect::csf_stream_connect;



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
 * 表示打开连接信息.
 * 返回：0表示成功；非0表示失败；
 * 
 * @param url    表示连接地址
 */
csf_int32 csf_stream_connect::open(const csf_url& url) {

	return 0;
}


/**
 * 表示关闭连接.
 * 返回：0表示成功；非0表示失败；
 */
csf_int32 csf_stream_connect::close() {

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
 * 表示设置连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_stream_connect::set_option() {

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
 * 表示获取连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_stream_connect::get_option() {

	return 0;
}


/**
 * 表示设置读超时时间.
 * 返回：0表示成功；非0表示失败；
 * 
 * @param timeout_ms
 * @param callback    表示超时回调函数。
 */
csf_int32 csf_stream_connect::set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}


/**
 * 表示设置写超时时间。
 * 返回：0表示成功；非0表示失败；
 * 
 * @param timeout_ms
 * @param callback    表示超时回调函数。
 */
csf_int32 csf_stream_connect::set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) {

	return 0;
}
