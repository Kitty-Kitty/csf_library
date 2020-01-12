/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: csf_vm.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:43
*
*Description: Class(csf_vm)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_vm.hpp"

using csf::core::module::csf_vm;


csf_vm::csf_vm()
	: m_slaves{csf_nullptr, } {

}



csf_vm::~csf_vm() {

}





/**
 * 功能：
 *    模块初始化，进行模块启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_vm::init(const csf_configure_manager * conf_mg) {
	csf_bool							tmp_bool_ret = csf_false;
	csf_string							tmp_string_ret = "";


	csf_log(notice, "init vm[%s]...", get_version().to_string().c_str());

	/************************************************************************/
	/* 程序当前工作目录主要有三个方面数据来源，优先级(1<2<3)依次如下：          */
	/*		1、环境变量获取；													*/
	/*		2、配置文件获取；													*/
	/*		3、程序运行时自带的参数；											*/
	/* 该优先级的定义主要是方便满足程序的维护需求       						*/
	/************************************************************************/
	tmp_bool_ret = init_work_directory();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//表示保存当前app信息到指定文件中
	tmp_bool_ret = save_information();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//解析配置文件，将所有信息保存到configure_manager中
	tmp_bool_ret = init_configure_manager(get_config_mg(), get_root_configure_file());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//加载启动日志系统，为程序提供日志服务
	tmp_bool_ret = init_logger(get_config_mg(), get_work_directory());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//初始化虚拟机的名称
	tmp_bool_ret = init_vm_name();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	return csf_succeed;
}


/**
 * 功能：
 *    模块启动，进行模块启动工作。表示模块已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_vm::start(const csf_configure_manager * conf_mg) {

	csf_bool							tmp_bool_ret = csf_false;


	//加载启动日志系统，为程序提供日志服务
	tmp_bool_ret = init_logger(get_config_mg(), get_work_directory());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	return 0;
}


/**
 * 功能：
 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_vm::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 功能：
 *    该函数主要用于初始化vm的名称
 * 返回：
 *    true  :  表示初始化成功；
 *    false :  表示初始化失败。
 */
csf_bool csf_vm::init_vm_name() {

	csf_string							tmp_string_ret = "";


	get_attribute_manager().add("name"
		, csf_attribute_string(csf_list<csf_string>({ "vm_configure", "name" })
			, csf_attribute_exception_critical()));

	//获取当前配置的工作目录地址
	tmp_string_ret = get_attribute_manager().get_value<csf_attribute_string>("name");
	if (!tmp_string_ret.empty()) {
		set_name(tmp_string_ret);
		csf_log(notice, "set vm[name:%s] succeed!", tmp_string_ret.c_str());
		return csf_true;
	}
	else {
		set_name("");
		csf_log(error, "set vm failed! not found name in configure files!");
	}

	return csf_false;
}


/**
 * 功能：
 *    初始化共享内存资源
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败；
 */
csf_bool csf_vm::init_shared_memory() {

	return csf_true;
}