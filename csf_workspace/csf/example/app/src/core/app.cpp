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
*Date: 25-6ÔÂ-2018 17:11:08
*
*Description: Class(app)
*
*Others:
*
*History:
*******************************************************************************/

#include <windows.h>
#include "app.hpp"


int main(int argc, char** argv)
{
	csf_int32								tmp_bool = csf_false;
	//csf::core::module::csf_app			tmp_app("D:\\project_work\\project\\css_workspace\\common_server_framework\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app			tmp_app("D:\\project_work\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app				tmp_app("D:\\project_work\\csf_library\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");
	//csf::core::module::csf_app			tmp_app;
	csf::core::module::csf_app			tmp_app("E:\\Trans-Control-CO\\DS-C12N-DO\\trunk\\DS-C12N-DO-VDU\\csf_workspace\\csf\\example\\app\\config\\csf_configs.xml", "xml");


	csf_buffer			*tmp_buf = new csf_buffer(10);


	tmp_buf->cat("hello!");
	delete tmp_buf;


	tmp_bool = tmp_app.init(csf_nullptr);
	if (tmp_bool) {
		csf_log(error, "app init failed!");
	}
	else {
		csf_log(notice, "app init succeed!");
	}

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