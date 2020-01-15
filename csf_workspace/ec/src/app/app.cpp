/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: app.h
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 25-6月-2018 17:11:08
*
*Description: Class(app)
*
*Others:
*
*History:
*******************************************************************************/

#ifdef WIN32
#include <windows.h>
#endif

#include "csf_app_option.hpp"
#include "app.hpp"


int main(int argc, char** argv)
{
	csf_int32								tmp_bool = csf_false;
	//csf::core::module::csf_app			tmp_app("D:\\project_work\\project\\css_workspace\\common_server_framework\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app			tmp_app("D:\\project_work\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app			tmp_app("D:\\project_work\\csf_library\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	csf::core::module::csf_app				tmp_app;
	csf::core::module::csf_app_option		tmp_app_option(tmp_app);
	//csf::core::module::csf_app			tmp_app("E:\\project_work\\arm_project\\kitty\\project\\trunk\\csf_library\\csf_workspace\\ec\\config\\csf_configs.xml", "xml");


	//模拟实现程序段错误
	//csf_int32			*tmp_value = NULL;
	//csf_int32			tmp_dest = *tmp_value;

	//设置app的版本信息
	tmp_app.get_version().set_version(
		csf_ec_version
		, CSF_EC_VER
		, CSF_EC_VAR
		, "ec app"
	);

	//解析程序运行参数
	if (!tmp_app_option.get_option(argc, argv)) {
		csf_log(error, "app option error!");
		return 0;
	}

	//开始初始化app
	tmp_bool = tmp_app.init(csf_nullptr);
	if (tmp_bool) {
		csf_log(error, "app init failed!");
	}
	else {
		csf_log(notice, "app init succeed!");
	}

	//开始运行app
	tmp_bool = tmp_app.start(csf_nullptr);
	if (tmp_bool) {
		csf_log(error, "app start failed!");
	}
	else {
		csf_log(notice, "app start succeed!");
	}

	while (csf_true) {
		csf_msleep(10000);
	}
	printf("hello world!\r\n");
	return 0;
}