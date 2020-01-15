/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_platform.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Class(csf_platform)
*
*Others:
*
*History:
*
*******************************************************************************/

#ifdef WIN32
#include <process.h>
#else
#include <unistd.h>
#endif
#include <boost/filesystem.hpp>
#include "csf_logger.hpp"
#include "csf_platform.hpp"


using csf::core::system::platform::csf_platform;


csf_platform::csf_platform() {

}



csf_platform::~csf_platform() {

}


/**
 * 功能：
 *    设置程序运行的工作目录
 * 返回：
 *    0   ：表示成功；
 *    非0 ：表示失败；
 * 
 * @param newVal    表示工作目录地址
 */
csf_int32 csf_platform::set_work_directory(csf_string newVal) {

	//如果需要设置的工作目录地址为空，则使用程序文件存在的目录作为默认的工作目录
	if (newVal.empty()) {
		return csf_failure;
	}
	
	boost::filesystem::path		tmp_path(newVal);
	boost::system::error_code	tmp_ec;

	//判断需要被使用的工作目录是否已经存在，不存在则返回错误
	if (!boost::filesystem::is_directory(tmp_path)) {
		csf_log(critical
			, "set work directory failed! not found directory[%s]."
			, newVal.c_str()
		);
		return csf_failure;
	}

	//设置当前的工作目录
	boost::filesystem::current_path(tmp_path, tmp_ec);
	if (tmp_ec) {
		csf_log(critical
			, "set work directory failed! directory[%s] error_code[%d]: %s."
			, newVal.c_str()
			, tmp_ec.value()
			, tmp_ec.message().c_str()
		);
		return csf_failure;
	}
	else {
		csf_log(critical
			, "set work directory succeed! directory[%s]."
			, newVal.c_str()
		);
	}

	return csf_succeed;
}


/**
 * 功能：
 *    获取当前程序所在的目录地址
 * 返回：
 *    当前程序存放目录地址字符串，如果获取失败，则目录地址字符串为空。
 */
csf_string csf_platform::current_path() {

	boost::filesystem::path		tmp_path;
	boost::system::error_code	tmp_ec;


	tmp_path = boost::filesystem::current_path(tmp_ec);
	if (tmp_ec) {
		csf_log(error
			, "get current path failed! error_code[%d]: %s."
			, tmp_ec.value()
			, tmp_ec.message().c_str()
		);
		return "";
	}
	else {
		csf_log(notice
			, "get current path succeed! directory[%s]."
			, tmp_path.string().c_str()
		);
		return tmp_path.string();
	}
	return "";
}


/**
 * 功能：
 *    获取当前进程的PID数值，用于记录使用
 * 返回：
 *    返回当前进程的PID数值，成功则返回非0；失败则返回0；
 */
csf_uint32 csf_platform::get_pid() {
	return getpid();
}


/**
 * 功能：
 *    保存pid等信息到文件中
 * 返回：
 *    csf_true  ：  表示保存pid信息成功；
 *    csf_false ：  表示保存pid信息失败；
 *
 * @param file    表示需要将信息保存的目的文件地址
 */
csf_bool csf_platform::save_pid(csf_string file) {

	boost::system::error_code	tmp_ec;
	csf_string					tmp_str_directories = "";
	csf_uint32					tmp_pid = 0;


	tmp_str_directories = file.substr(0, file.find_last_of(boost::filesystem::path::preferred_separator));
	boost::filesystem::path		tmp_directories(tmp_str_directories);

	if (!boost::filesystem::exists(tmp_directories, tmp_ec)) {
		//如果文件不存在，则创建该文件
		if (!boost::filesystem::create_directories(tmp_directories, tmp_ec)) {
			csf_log(error
				, "create directories failed! directories[%s] error_code[%d]: %s."
				, tmp_str_directories.c_str()
				, tmp_ec.value()
				, tmp_ec.message().c_str()
			);
			return csf_false;
		}
		else {
			csf_log(notice
				, "create directories succeed! directories[%s]."
				, tmp_str_directories.c_str()
			);
		}
	}

	boost::filesystem::path		tmp_path(file);
	//表示获取当前进程的pid数值
	tmp_pid = get_pid();
	if (tmp_pid <= 0) {
		csf_log(error
			, "get pid failed! pid file[%s]."
			, file.c_str()
		);
		return csf_false;
	}
	else {
		boost::filesystem::ofstream		tmp_ofstream{ tmp_path };
		tmp_ofstream << tmp_pid << "\n";

		csf_log(error
			, "save pid[%d] succeed! pid file[%s]."
			, tmp_pid
			, file.c_str()
		);
		return csf_true;
	}

	return csf_true;
}