/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:37
*
*Description: Class(csf_connect_factory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_connect_factory.hpp"
#include "csf_connect.hpp"

using namespace csf::core::module::connect;
using csf::core::module::connect::csf_connect_factory;


csf_connect_factory::csf_connect_factory() {

}



csf_connect_factory::~csf_connect_factory() {

}





/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_connect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect_factory::init(const csf_configure_manager * conf_mg) {

	return get_timeout_manager().init();
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_connect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect_factory::start(const csf_configure_manager * conf_mg) {

	return get_timeout_manager().start();
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_connect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_connect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 */
csf_connect_ptr csf_connect_factory::create(const csf_connect::csf_connect_type type) {

	return  m_null_connect_ptr;
}


/**
 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 * @param local_url    表示连接打开的本地地址
 */
csf_connect_ptr csf_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url) {

	return  m_null_connect_ptr;
}


/**
 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 * @param local_url    表示连接打开的本地地址
 * @param remote_url    表示连接打开的远程地址
 */
csf_connect_ptr csf_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	return  m_null_connect_ptr;
}


/**
 * 表示销毁网络连接，销毁成功返回0，失败返回<0的数值。
 * 
 * @param connect    表示需要销毁的连接
 */
csf_int32 csf_connect_factory::destroy(const csf_connect_ptr connect) {

	return 0;
}