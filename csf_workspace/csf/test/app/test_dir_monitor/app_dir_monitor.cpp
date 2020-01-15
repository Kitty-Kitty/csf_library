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

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

#include "dir_monitor/dir_monitor.hpp"


#ifdef WIN32
	#define TEST_DIR1 "E:\\project_work\\arm_project\\kitty\\project\\trunk\\csf_library\\csf_workspace\\ec\\platform\\win32\\app\\ec_app"
#else
	#define TEST_DIR1 "/udisk/project/"
#endif

#define		csf_app_version				1000000
#define		CSF_APP_VERSION				"V1.0.0"
#define		CSF_APP_VAR					"test_dir_monitor"
#define		CSF_APP_VER					CSF_APP_VAR "/" CSF_APP_VERSION


void event_handler(boost::asio::dir_monitor& dm, const boost::system::error_code &ec, const boost::asio::dir_monitor_event &ev)
{
	if (ec) {
		std::cout << "Error code " << ec << std::endl;
	}
	else {
		std::cout << ev << std::endl;
		// Keep it posted forever.
		dm.async_monitor([&](const boost::system::error_code &ec, const boost::asio::dir_monitor_event &ev) {
			event_handler(dm, ec, ev);
		});
	}
}

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;
	std::string				tmp_path = "";


	if (argc > 1) {
		tmp_path = argv[1];
	}
	else {
		tmp_path = TEST_DIR1;
	}

	try {
		boost::filesystem::create_directories(tmp_path);
	}
	catch (boost::filesystem::filesystem_error e) {
		std::cout << "create directory[" << tmp_path << "] failed!" << std::endl;
		std::cout << e.what() << std::endl;
	}

	if (!boost::filesystem::is_directory(tmp_path)) {
		printf("path[%s] is not a directory!!\r\n", tmp_path.c_str());
		printf("usage: app  [directory] \r\n");
		return 1;
	}

	boost::asio::dir_monitor dm(io_service);
	dm.add_directory(TEST_DIR1);
	dm.async_monitor([&](const boost::system::error_code &ec, const boost::asio::dir_monitor_event &ev) {
		event_handler(dm, ec, ev);
	});

	//boost::asio::io_service::work workload(io_service);
	io_service.run();

	//system("PAUSE");

	return 0;
}