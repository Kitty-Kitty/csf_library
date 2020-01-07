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