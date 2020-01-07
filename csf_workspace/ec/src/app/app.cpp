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
*Date: 25-6��-2018 17:11:08
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


	//����app�İ汾��Ϣ
	tmp_app.get_version().set_version(
		csf_ec_version
		, CSF_EC_VER
		, CSF_EC_VAR
		, "ec app"
	);

	//�����������в���
	if (!tmp_app_option.get_option(argc, argv)) {
		return 0;
	}

	//��ʼ��ʼ��app
	tmp_bool = tmp_app.init(csf_nullptr);
	if (tmp_bool) {
		csf_log(error, "app init failed!");
	}
	else {
		csf_log(notice, "app init succeed!");
	}

	//��ʼ����app
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