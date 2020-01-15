/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: csf_master.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_master)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_master.hpp"
#include "csf_vm_option.hpp"

using csf::core::module::csf_master;


/**
 * 功能：
 *    模块初始化，进行模块启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 */
csf::core::base::csf_int32 csf_master::init() {

	csf_bool			tmp_bool_ret = csf_false;
	csf_int32			tmp_int_ret = csf_failure;
	csf_vm				tmp_vm;
	csf_vm_option		tmp_vm_option(tmp_vm);


	//解析程序运行参数
	if (!tmp_vm_option.get_option(get_argc(), get_argv())) {
		return 0;
	}

	//初始化虚拟机对象
	tmp_int_ret = tmp_vm.init(csf_nullptr);
	if (csf_failure == tmp_int_ret) {
		return csf_failure;
	}

	//获取虚拟机的名称
	if (tmp_vm.get_name().empty()) {
		return csf_failure;
	}
	else {
		set_name(tmp_vm.get_name());
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
 */
csf::core::base::csf_int32 csf_master::start() {

	return csf_succeed;
}


/**
 * 功能：
 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 */
csf::core::base::csf_int32 csf_master::stop() {

	return 0;
}


/**
 * 功能：
 *    该函数主要用于启动master中的所有vm
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_master::start_vm() {

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于停止master中的所有vm
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_master::stop_vm() {

	return csf_true;
}