/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 17:41:45
*
*Description: Class(csf_configure_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_configure_manager.hpp"
#include "csf_attribute_include.h"


using csf::core::system::csf_configure_manager;


csf_configure_manager::csf_configure_manager() {

}



csf_configure_manager::~csf_configure_manager() {

}

/**
* 表示根据items属性路径查找一个element。
* 返回：非null表示满足items所有路径的节点；null表示没有查找到满足路径的节点；
*
* @param items    items属性路径
*/
const csf_element& csf_configure_manager::find_element(const csf_list<csf_string>& items) {

	csf_element				*tmp_element = csf_nullptr;


	//循环遍历所有列表，查找符合路径需求的节点
	for (auto &tmp_configure : get_configures()) {
		tmp_element = (csf_element*)&(tmp_configure.second.find_element(items));
		if (tmp_element->not_null()) {
			return *tmp_element;
		}
	}

	return csf_element::get_null();
}



/**
* 功能：初始化配置管理器中的其他配置信息，主要指模块配置信息，负载配置信息部分内容
* 返回：true表示初始化成功；false表示初始化失败
*/
csf_bool csf_configure_manager::init() {

	csf_bool					tmp_bool_ret = csf_false;


	//判断配置信息列表的合法性，如果为空则直接返回错误
	if (get_configures().empty()) {
		csf_log_ex(error, csf_log_code_error, "configures is null");
		return csf_false;
	}

	//开始初始化模块配置管理器信息
	tmp_bool_ret = init_module_configures(get_module_configures(), get_configures());
	if (!tmp_bool_ret) {
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init module configures succeed!");
	}

	//开始初始化负载配置管理器信息
	tmp_bool_ret = init_measure_configure(get_measure_configure(), get_configures());
	if (!tmp_bool_ret) {
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init measure configure succeed!");
	}

	return csf_true;
}


/**
* 功能：初始化模块配置管理器
* 返回：true表示初始化成功；false表示初始化失败
*
* @param module_configures    表示处理后保存输出的模块配置信息
* @param configures    表示当前已经解析的配置文件信息
*/
csf_bool csf_configure_manager::init_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
	, csf_map<csf_string, csf_configure>& configures) {

	csf_bool						tmp_bool_ret = csf_false;


	//开始初始化模块配置部分内容
	tmp_bool_ret = add_module_configures(get_module_configures(), csf_list<csf_string>{CSF_CONFIGURE_STRING(modules_configure)});
	if (!tmp_bool_ret) {
		csf_log_ex(warning, csf_log_code_warning, "add module configures failed!");
		return csf_false;
	}

	return csf_true;
}


/**
* 功能：初始化负载配置管理器
* 返回：true表示初始化成功；false表示初始化失败
*
* @param measure_configure    表示处理后保存输出的模块配置信息
* @param configures    表示当前已经解析的配置文件信息
*/
csf_bool csf_configure_manager::init_measure_configure(csf_measure_configure& measure_configure
	, csf_map<csf_string, csf_configure>& configures) {


	csf_attribute_manager					tm_attribute_manager(this);


	tm_attribute_manager.add(CSF_CONFIGURE_STRING(device_measure)
		, csf_attribute_int(csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(device_io_measure)
		, csf_attribute_int(csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(client_measure)
		, csf_attribute_int(csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(time_resolution)
		, csf_attribute_time(csf_attribute_time::csf_time_unit_ms
			, csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(timer_resolution)
		, csf_attribute_time(csf_attribute_time::csf_time_unit_ms
			, csf_attribute_boundary("(0, n)")));

	measure_configure.set_device_limit((csf_int32)tm_attribute_manager.get_value<csf_attribute_int>(CSF_CONFIGURE_STRING(device_measure)));
	measure_configure.set_device_io_limit((csf_int32)tm_attribute_manager.get_value<csf_attribute_int>(CSF_CONFIGURE_STRING(device_io_measure)));
	measure_configure.set_connect_limit((csf_int32)tm_attribute_manager.get_value<csf_attribute_int>(CSF_CONFIGURE_STRING(client_measure)));
	measure_configure.set_time_resolution((csf_int32)tm_attribute_manager.get_value<csf_attribute_time>(CSF_CONFIGURE_STRING(time_resolution)));
	measure_configure.set_timer_resolution((csf_int32)tm_attribute_manager.get_value<csf_attribute_time>(CSF_CONFIGURE_STRING(timer_resolution)));

	csf_log_ex(notice, csf_log_code_notice
		, "%s"
		, measure_configure.to_string().c_str());

	return csf_true;
}


/**
* 功能：向模块配置管理器中添加一个模块配置信息，同时遍历信息下的所有子模块信息
* 返回：true表示初始化成功；false表示初始化失败
*
* @param module_configures    表示处理后保存输出的模块配置信息
* @param module_element    表示当前获取到的模块信息
*/
csf_bool csf_configure_manager::add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
	, csf_element& module_element) {

	csf_element						*tmp_element_ret = &module_element;


	//先判断自己是否为模块节点，如果是则添加
	if (tmp_element_ret->is_null()) {
		return csf_false;
	}
	else {
		if (CSF_CONFIGURE_STRING(module) == tmp_element_ret->get_name()) {
			return add_module_configure(module_configures, *tmp_element_ret);
		}
	}

	//遍历所有子节点内容
	for (auto &tmp_element : tmp_element_ret->get_children()) {
		add_module_configures(module_configures, tmp_element);
	}

	return csf_true;
}


/**
* 功能：向模块配置管理器中添加一个模块配置信息
* 返回：true表示初始化成功；false表示初始化失败
*
* @param module_configures    表示处理后保存输出的模块配置信息
* @param module_element    表示当前获取到的模块信息
*/
csf_bool csf_configure_manager::add_module_configure(csf_map<csf_string, csf_module_configure>& module_configures
	, csf_element& module_element) {

	csf_string						tmp_string_name = "";
	csf_string						tmp_string_file = "";


	//校验数据的合法性，没有问题则插入到模块列表中
	if (module_element.is_null()) {
		return csf_false;
	}

	tmp_string_name = module_element.find("name");
	tmp_string_file = module_element.find("file");

	if (tmp_string_name.empty() || tmp_string_file.empty()) {
		return csf_false;
	}

	module_configures.insert(
		csf_map<csf_string, csf_module_configure>::value_type(tmp_string_name
			, csf_module_configure(tmp_string_name, tmp_string_file)));

	csf_log_ex(notice, csf_log_code_notice
		, "add module_configure[name: %s  file: %s] succeed!"
		, tmp_string_name.c_str()
		, tmp_string_file.c_str());

	return csf_true;
}


/**
* 功能：向模块配置管理器中添加一个模块配置信息，同时遍历信息下的所有子模块信息
* 返回：true表示初始化成功；false表示初始化失败
*
* @param module_configures    表示处理后保存输出的模块配置信息
* @param items    表示当前模块信息路径
*/
csf_bool csf_configure_manager::add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
	, const csf_list<csf_string>& items) {

	csf_element						*tmp_element_ret = csf_nullptr;


	tmp_element_ret = (csf_element *)&find_element(items);
	if (tmp_element_ret->is_null()) {
		return csf_false;
	}
	else {
		return add_module_configures(module_configures, *tmp_element_ret);
	}
	return csf_false;
}



/**
* 功能：根据模块名称查询模块配置信息
* 返回：非空对象表示成功；非对象表示失败；
*
* @param name    表示模块的名称
*/
const csf_module_configure& csf_configure_manager::find_module_configure(const csf_string& name) {

	csf_map<csf_string, csf_module_configure>::iterator				tmp_iter;


	//这里的查询考虑线程安全的原因是系统的模块配置信息在系统启动后就固定不变
	tmp_iter = get_module_configures().find(name);
	if (tmp_iter != get_module_configures().end()) {
		return tmp_iter->second;
	}

	return csf_module_configure::get_null();
}