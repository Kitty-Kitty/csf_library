/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_ip_connnect_factory.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 29-7月-2018 15:13:09
*
*Description: Class(csf_ip_connnect_factory) 表示ip网络通信连接工厂类
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_ip_connnect_factory.hpp"

using csf::modules::connect::csf_ip_connnect_factory;



/**
 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 */
csf_connect* csf_ip_connnect_factory::create(const csf::core::module::connect::csf_connect::csf_connect_type type) {

	return  NULL;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connnect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_ip_connnect_factory::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 * @param local_url    表示连接打开的本地地址
 */
csf_connect* csf_ip_connnect_factory::create(const csf::core::module::connect::csf_connect::csf_connect_type type, const csf_url& local_url) {

	return  NULL;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connnect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_ip_connnect_factory::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 * @param local_url    表示连接打开的本地地址
 * @param remote_url    表示连接打开的远程地址
 */
csf_connect* csf_ip_connnect_factory::create(const csf::core::module::connect::csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	return  NULL;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_ip_connnect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connnect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connnect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
 * 
 * @param connect    表示需要销毁的连接
 */
csf_int32 csf_ip_connnect_factory::destroy(const csf_connect* connect) {

	return 0;
}