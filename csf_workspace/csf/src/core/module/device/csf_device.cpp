/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 17:33:44
*
*Description: Class(csf_device)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_app.hpp"
#include "csf_device.hpp"
#include "csf_device_io.hpp"

using csf::core::module::csf_device;


/**
* 功能：根据模块的mid查找一个设备对象
* 返回：非空表示成功；空表示失败；
*
* @param mid    表示设备的模块编号
*/
csf_device_io* csf_device::find_device_io(const csf_string& mid) {

	csf_unordered_map<csf_string, csf_device_io*>::iterator			tmp_iter;


	if (mid.empty()) {
		return csf_nullptr;
	}

	csf_shared_lock<decltype(m_device_ioes_mutex)>			tmp_lock(m_device_ioes_mutex);

	tmp_iter = get_device_ioes().find(mid);
	if (tmp_iter != get_device_ioes().end()) {
		return tmp_iter->second;
	}

	return  csf_nullptr;
}


/**
* 功能：根据模块的mid向device中插入一个设备对象
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备的模块编号
* @param device_io    表示device_io模块对象地址
*/
csf_bool csf_device::add_device_io(const csf_string& mid, const csf_device_io* device_io) {

	csf_device_io				*tmp_device_io = csf_nullptr;


	if (!device_io || mid.empty()) {
		return csf_false;
	}

	tmp_device_io = find_device_io(mid);
	if (!tmp_device_io) {

		csf_unqiue_lock<decltype(m_device_ioes_mutex)>			tmp_lock(m_device_ioes_mutex);

		get_device_ioes().insert(csf_unordered_map<csf_string, csf_device_io*>::value_type(mid, (csf_device_io*)device_io));

		return csf_true;
	}

	return csf_false;
}


/**
* 功能：根据模块的mid从设备列表中删除一个设备对象
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备的模块编号
*/
csf_bool csf_device::del_device_io(const csf_string& mid) {

	csf_unordered_map<csf_string, csf_device_io*>::iterator			tmp_iter;


	if (mid.empty()) {
		return csf_false;
	}

	csf_unqiue_lock<decltype(m_device_ioes_mutex)>			tmp_lock(m_device_ioes_mutex);

	tmp_iter = get_device_ioes().find(mid);
	if (tmp_iter != get_device_ioes().end()) {
		get_device_ioes().erase(tmp_iter);
		return csf_true;
	}

	return csf_false;
}




/**
* 功能：初始化device_io对象
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备的模块编号
* @param device_io    表示device_io模块对象地址
*/
csf_bool csf_device::init_device_io(const csf_string& mid, csf_device_io* device_io) {

 	csf_int32			tmp_int_ret = csf_failure;
 
 
 	if (!device_io) {
 		return csf_false;
 	}
 
 	//开始初始化设备
 	tmp_int_ret = device_io->init(get_configure_manager());
 	if (csf_failure == tmp_int_ret) {
 		csf_log(warning, "init %s failed!", device_io->to_string().c_str());
 		return csf_false;
 	}
 	else {
 		csf_log(notice, "init %s succeed!", device_io->to_string().c_str());
 	}

	return csf_true;
}


/**
* 功能：启动device_io对象
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备的模块编号
* @param device_io    表示device_io模块对象地址
*/
csf_bool csf_device::start_device_io(const csf_string& mid, csf_device_io* device_io) {

	csf_int32			tmp_int_ret = csf_failure;


	if (!device_io) {
		return csf_false;
	}

	//开始初始化设备
	tmp_int_ret = device_io->start(get_configure_manager());
	if (csf_failure == tmp_int_ret) {
		csf_log(warning, "start %s failed!", device_io->to_string().c_str());
		return csf_false;
	}
	else {
		csf_log(notice, "start %s succeed!", device_io->to_string().c_str());
	}

	return csf_true;
}


/**
* 功能：启动device_io对象
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备的模块编号
* @param device_io    表示device_io模块对象地址
*/
csf_bool csf_device::stop_device_io(const csf_string& mid, csf_device_io* device_io) {

	csf_int32			tmp_int_ret = csf_failure;


	if (!device_io) {
		return csf_false;
	}

	//开始初始化设备
	tmp_int_ret = device_io->stop(get_configure_manager());
	if (csf_failure == tmp_int_ret) {
		csf_log(warning, "stop %s failed!", device_io->to_string().c_str());
		return csf_false;
	}
	else {
		csf_log(notice, "stop %s succeed!", device_io->to_string().c_str());
	}

	return csf_true;
}


/**
* 功能：
*    初始化所有device io 设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
csf_bool csf_device::init_device_ioes() {

	//依次遍历设备，初始化设备
	for (auto &tmp_iter : get_device_ioes()) {
		init_device_io(tmp_iter.first, tmp_iter.second);
	}
	return csf_true;
}


/**
* 功能：
*    启动所有device io 设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
csf_bool csf_device::start_device_ioes() {

	//依次遍历设备，初始化设备
	for (auto &tmp_iter : get_device_ioes()) {
		start_device_io(tmp_iter.first, tmp_iter.second);
	}
	return csf_true;
}


/**
* 功能：
*    停止所有device io 设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
csf_bool csf_device::stop_device_ioes() {

	//依次遍历设备，初始化设备
	for (auto &tmp_iter : get_device_ioes()) {
		stop_device_io(tmp_iter.first, tmp_iter.second);
	}
	return csf_true;
}