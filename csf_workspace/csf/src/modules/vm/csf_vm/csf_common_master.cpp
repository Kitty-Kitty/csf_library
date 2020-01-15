/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: csf_common_master.hpp
*
*Version: 1.0
*
*Date: 15-1月-2020 18:46:53
*
*Description: Class(csf_common_master)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_common_master.hpp"
#include "csf_vm_option.hpp"

using csf::modules::vm::csf_common_master;


csf_common_master::~csf_common_master() {

}


/**
 * 
 * @param argc    表示当前程序的运行参数个数
 * 
 * @param argv    表示当前运行参数数值内容
 */
csf_common_master::csf_common_master(int argc, char** argv)
	: csf_master(argc, argv) {

}


/**
 * 功能：
 *    该函数主要用于启动master中的所有vm
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_master::start_vm() {


	csf_int32			tmp_int_ret = csf_failure;


	if (csf_nullptr == get_vm()) {
		return csf_false;
	}

	csf::core::module::csf_vm_option	tmp_vm_option(*get_vm());

	//解析程序运行参数
	if (!tmp_vm_option.get_option(get_argc(), get_argv())) {
		return 0;
	}

	//初始化虚拟机对象
	tmp_int_ret = get_vm()->init(csf_nullptr);
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "init vm failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "init vm succeed!");
	}

	//启动虚拟机对象
	tmp_int_ret = get_vm()->start(csf_nullptr);
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "start vm failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "start vm succeed!");
	}

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于停止master中的所有vm
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_master::stop_vm() {


	csf_int32			tmp_int_ret = csf_failure;


	if (csf_nullptr == get_vm()) {
		return csf_false;
	}

	//停止虚拟机对象
	tmp_int_ret = get_vm()->stop(csf_nullptr);
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "stop vm failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "stop vm succeed!");
	}
	return csf_true;
}


/**
 * 功能：
 *    处理当前进程的输入参数信息。
 * 返回：
 *    0   ：表示成功；
 *    非0 ：表示失败；
 */
csf::core::base::csf_int32 csf_common_master::process_option() {

	csf::core::module::csf_vm				tmp_vm;
	csf::core::module::csf_vm_option		tmp_vm_option(tmp_vm);


	//解析程序运行参数
	if (!tmp_vm_option.get_option(get_argc(), get_argv())) {
		return 0;
	}
	return 0;
}


/**
 * 功能：
 *    初始化共享内存资源
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败；
 */
csf_bool csf_common_master::init_shared_memory() {

	csf_int32			tmp_int_ret = csf_failure;
	csf_char			tmp_buf[128] = { 0, };


	//生成共享内存的名称
	csf_snprintf(tmp_buf
		, csf_sizeof(tmp_buf)
		, "master_%s", get_name().c_str());

	//这里"csf_sizeof(csf_vm) * 2"主要为了分配充足的共享空间，避免空间不足而错误
	tmp_int_ret = get_sm().create(tmp_buf, csf_sizeof(csf_vm) * 2);
	if (csf_failure == tmp_int_ret) {
		return csf_false;
	}

	return csf_true;
}


/**
 * 功能： 模块初始化，进行模块启动前的准备工作。 返回： 0   ：表示成功 非0 ：表示失败
 */
csf::core::base::csf_int32 csf_common_master::init() {

	return csf_master::init();
}


/**
 * 功能： 模块启动，进行模块启动工作。表示模块已经正常运行。 返回： 0   ：表示成功 非0 ：表示失败
 */
csf::core::base::csf_int32 csf_common_master::start() {

	csf_bool			tmp_bool_ret = csf_false;


	//初始化虚拟机对象
	tmp_bool_ret = init_shared_memory();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "init_shared_memory() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "init_shared_memory() succeed!");
	}

	//在共享内存中创建虚拟机对象
	set_vm(get_sm().create_object<csf_vm>(get_name()));
	if (csf_nullptr == get_vm()) {
		csf_log(error
			, "create_object() [%s : null] failed!"
			, get_name().c_str()
		);
		return csf_failure;
	}
	else {
		csf_log(notice
			, "create_object() [%s : %p] succeed!"
			, get_name().c_str()
			, get_vm()
		);
	}

	//启动虚拟机对象
	tmp_bool_ret = start_vm();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	return csf_succeed;
}


/**
 * 功能： 模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。 返回： 0   ：表示成功 非0 ：表示失败
 */
csf::core::base::csf_int32 csf_common_master::stop() {

	csf_bool			tmp_bool_ret = csf_false;


	//启动虚拟机对象
	tmp_bool_ret = stop_vm();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	return 0;
}