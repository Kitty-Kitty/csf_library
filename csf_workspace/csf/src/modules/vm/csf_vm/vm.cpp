/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: vm.h
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 25-6月-2018 17:11:08
*
*Description: Class(vm)
*
*Others:
*
*History:
*******************************************************************************/

#ifdef WIN32
#include <windows.h>
#endif

#include "csf_vm_option.hpp"
#include "vm.hpp"
#include "csf_common_master.hpp"


int main(int argc, char** argv)
{
	csf_int32								tmp_bool = csf_false;
	//csf::core::module::csf_app			tmp_vm("D:\\project_work\\project\\css_workspace\\common_server_framework\\csf_workspace\\csf\\example\\vm\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app			tmp_vm("D:\\project_work\\csf_workspace\\csf\\example\\vm\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app			tmp_vm("D:\\project_work\\csf_library\\csf_workspace\\csf\\example\\vm\\config\\csf_configs.xml", "xml");
	csf::modules::vm::csf_common_master		tmp_master(argc, argv);
	csf::core::module::csf_vm				tmp_vm;
	csf::core::module::csf_vm_option		tmp_vm_option(tmp_vm);
	//csf::core::module::csf_app			tmp_vm("E:\\project_work\\arm_project\\kitty\\project\\trunk\\csf_library\\csf_workspace\\ec\\config\\csf_configs.xml", "xml");


	//设置vm的版本信息
	tmp_vm.get_version().set_version(
		csf_vm_version
		, CSF_VM_VER
		, CSF_VM_VAR
		, "csf vm"
	);

	//解析程序运行参数
	if (!tmp_vm_option.get_option(argc, argv)) {
		csf_log(error, "vm option error!");
		return -1;
	}

	//开始初始化vm
	tmp_bool = tmp_master.init();
	if (tmp_bool) {
		csf_log(error, "vm init failed!");
		return -1;
	}
	else {
		csf_log(notice, "vm init succeed!");
	}

	//开始运行vm
	tmp_bool = tmp_master.start();
	if (tmp_bool) {
		csf_log(error, "vm start failed!");
		return -1;
	}
	else {
		csf_log(notice, "vm start succeed!");
	}

	while (csf_true) {
		csf_msleep(10000);
	}
	printf("hello world!\r\n");
	return 0;
}