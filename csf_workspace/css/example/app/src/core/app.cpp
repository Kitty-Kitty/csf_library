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

#include "app.hpp"


int main(int argc, char** argv)
{
	csf_bool								tmp_bool = csf_false;
	csf::core::module::app::csf_app			tmp_app("D:\\project_work\\project\\css_workspace\\common_server_framework\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	//csf::core::module::app::csf_app			tmp_app("D:\\project_work\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	
	//csf::core::module::app::csf_app			tmp_app;


	tmp_bool = tmp_app.init(csf_nullptr);
	if (!tmp_bool) {
		csf_log(error, "app init failed!");
	}
	printf("hello world!\r\n");
	return 0;
}