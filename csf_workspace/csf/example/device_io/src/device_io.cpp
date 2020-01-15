/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: device_io.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 24-7月-2018 22:17:27
*
*Description: Class(device_io) 表示设备的子设备内容。
*
*Others:
*
*History:
*******************************************************************************/

#include "device_io.hpp"

using test::device_io;


device_io::device_io() {

}



device_io::~device_io() {

}





/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 device_io::del(const csf_element& element, const csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 device_io::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 device_io::ctrl(const csf_element& element, const csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 device_io::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 device_io::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 device_io::update(const csf_element& element, const csf_device_operation_callback callback) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 device_io::add(const csf_element& element, const csf_device_operation_callback callback) {

	return 0;
}