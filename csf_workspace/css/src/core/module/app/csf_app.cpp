/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_app.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7月-2018 17:33:42
*
*Description: Class(csf_app)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_app.hpp"
#include "csf_container_convert.hpp"
#include "csf_attribute_default_value.hpp"


using csf::core::module::app::csf_app;



/**
* 模块初始化
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_app::init(const csf_configure_manager* conf_mg) {

	csf_bool							tmp_bool_ret = csf_false;
	csf_string							tmp_string_ret = "";


	//解析配置文件，将所有信息保存到configure_manager中
	tmp_bool_ret = init_configure_manager(get_config_mg(), get_root_configure_file());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	/************************************************************************/
	/* 程序当前工作目录主要有三个方面数据来源，优先级依次如下：                 */
	/*		1、环境变量获取；													*/
	/*		2、配置文件获取；													*/
	/*		3、程序运行时自带的参数；											*/
	/* 该优先级的定义主要是方便满足程序的维护需求       						*/
	/************************************************************************/
	//获取系统的工作根目录地址，并配置到日志系统中
	get_attribute_manager().add("work_directory"
		, csf_attribute_string(csf_list<csf_string>({ "configures", "work_directory" })));;

	tmp_string_ret = get_attribute_manager().get_value<csf_attribute_string>("work_directory");
	if (!tmp_string_ret.empty()) {
		set_work_directory(tmp_string_ret);
	}
	
	//加载启动日志系统，为程序提供日志服务
	tmp_bool_ret = init_logger(get_config_mg(), get_work_directory());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}
	
	//开始初始化系统模块、负载限制相关信息
	tmp_bool_ret = get_config_mg().init();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//开始初始化系统模块工厂管理器
	tmp_bool_ret = init_module_manager(get_config_mg());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

#if 0
	get_attribute_manager().add("time"
		, csf_attribute_time(csf_list<csf_string>({ "configures", "size" }) 
			, csf_attribute_time::csf_time_unit_s 
			, csf_attribute_boundary("(0, 10]")
			, csf_attribute_default_value<csf_attribute_time, csf_int32>(100)));;

	csf_int64 tmp_int64 = get_attribute_manager().get_value<csf_attribute_time>("time");

#endif

	return  csf_success;
}


/**
* 模块启动
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_app::start(const csf_configure_manager* conf_mg) {

	return  csf_success;
}


/**
* 模块停止
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_app::stop(const csf_configure_manager* conf_mg) {

	return  csf_success;
}


/**
* 该函数主要用于初始化app的日志系统。
* 返回：true表示初始化日志系统成功；false表示初始化日志系统失败。
*
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
* @param work_directory    表示程序默认的工作根目录地址
*/
csf_bool csf_app::init_logger(csf::core::system::csf_configure_manager& configure_manager, csf_string work_directory) {

	csf_int32					tmp_int32_ret = 0;


	//配置logger的配置管理器地址，让日志系统也有属性配置信息
	get_logger().set_configure_manager(&get_config_mg());

	//如果程序配置了工作根目录，则需要配置到日志系统中
	if (!work_directory.empty()) {
		get_logger().set_path(work_directory);
	}

	//先初始化日志系统，查看是否存在问题
	tmp_int32_ret = get_logger().init(&get_config_mg());
	if (tmp_int32_ret) {
		csf_log_ex(critical, csf_log_code_critical, "init logger failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init logger succeed!");
	}

	//初始化日志系统成功，则开始启动日志系统
	tmp_int32_ret = get_logger().start(&get_config_mg());
	if (tmp_int32_ret) {
		csf_log_ex(critical, csf_log_code_critical, "start logger failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "start logger succeed!");
	}

	return csf_true;
}


/**
* 该函数主要用于初始化app的模块管理器
* 返回：true表示初始化成功；false表示初始化失败。
*
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app::init_module_manager(csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//初始化模块工厂管理器信息
	tmp_int_ret = get_module_manager().init(get_configure_manager());
	if (tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "module manager init failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "module manager init succeed!");
	}

	//启动模块工厂管理器信息
	tmp_int_ret = get_module_manager().start(get_configure_manager());
	if (tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "module manager start failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "module manager start succeed!");
	}

	return csf_true;
}


/**
* 功能：根据设备名称查询指定设备地址
* 返回：非空表示成功；空表示失败；
*
* @param mid    表示设备名称
*/
csf_device* csf_app::find_device(const csf_string& mid) {

	csf_unordered_map<csf_string, csf_device*>::iterator			tmp_iter;


	if (mid.empty()) {
		return csf_false;
	}

	csf_shared_lock<decltype(m_devices_mutex)>			tmp_lock(m_devices_mutex);

	tmp_iter = get_devices().find(mid);
	if (tmp_iter != get_devices().end()) {
		return tmp_iter->second;
	}

	return  csf_nullptr;
}


/**
* 功能：根据设备名称添加指定设备地址到设备列表中
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备名称
* @param device
*/
csf_bool csf_app::add_device(const csf_string& mid, const csf_void* device) {

	csf_device					*tmp_device = csf_nullptr;


	//校验数据合法性
	if (!device || mid.empty()) {
		return csf_false;
	}

	//查找该名称的设备是否存在
	tmp_device = find_device(mid);
	if (tmp_device) {
		return csf_false;
	}
	
	csf_unqiue_lock<decltype(m_devices_mutex)>			tmp_lock(m_devices_mutex);

	//设备不存在则插入新设备
	get_devices().insert(csf_unordered_map<csf_string, csf_device*>::value_type((csf_string&)mid, (csf_device*)device));

	return csf_true;
}


/**
* 功能：根据设备名称删除指定设备地址
* 返回：true表示成功；false表示失败；
*
* @param mid    表示设备名称
*/
csf_bool csf_app::del_device(const csf_string& mid) {
	
	csf_unordered_map<csf_string, csf_device*>::iterator			tmp_iter;


	//校验数据合法性
	if (mid.empty()) {
		return csf_false;
	}

	csf_unqiue_lock<decltype(m_devices_mutex)>			tmp_lock(m_devices_mutex);

	//查找设备，并删除
	tmp_iter = get_devices().find(mid);
	if (tmp_iter != get_devices().end()) {
		get_devices().erase(tmp_iter);
		return csf_true;
	}

	return csf_false;
}