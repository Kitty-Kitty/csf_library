/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_url.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:43
*
*Description: Class(csf_ip_url)
*
*Others:
*
*History:
*
*******************************************************************************/

#include <regex>
#include "csf_ip_url.hpp"

using csf::modules::connect::csf_ip_url;


csf_ip_url::csf_ip_url()
	: csf_url(csf_url::csf_url_type::csf_url_type_ip)
	, m_ip("")
	, m_port(0) {

}



csf_ip_url::~csf_ip_url() {

}





/**
 * 表示解析地址函数
 *
 * @param url    表示url地址字符串数据
 */
csf_int32 csf_ip_url::parse(const csf_string& url) {

	/**
	* 表示核验格式和截取字符串正则表达式
	*/
	std::regex					tmp_regex("(\\w+):([0-9]{0,5})");
	std::smatch					tmp_match_result;
	int							tmp_port = 0;


	if (url.empty()) {
		return csf_failure;
	}

	//使用正则表达式核验数据结构和提取参数
	if (!std::regex_match(url, tmp_match_result, tmp_regex)) {
		//正则表达式匹配失败，表示数据格式错误
		return csf_failure;
	}

	//如果match提取的参数小于等于需要的参数个数，则表示错误
	if (tmp_match_result.size() <= csf_ip_url_parametes_size) {
		return csf_failure;
	}
	else {
		//校验端口的合法性
		tmp_port = atoi(tmp_match_result[2].str().c_str());
		if (tmp_port > csf_max_ushort || tmp_port < 0) {
			return csf_failure;
		}
		set_port(tmp_port);

		//校验ip地址的合法性
		if (!check_ip(tmp_match_result[1].str())) {
			return csf_failure;
		}
		else {
			set_ip(tmp_match_result[1].str());
		}

		return csf_success;
	}

	return csf_failure;
}


/**
* 主要功能是：对ip地址的格式合法性校验
* 返回：true表示成功；false表示失败；
*
* @param ip    表示网络地址格式
*/
csf_bool csf_ip_url::check_ip(const csf_string& ip) {

	std::regex					tmp_pattern("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");

	if (!std::regex_match(ip, tmp_pattern)) {
		return csf_false;
	}

	return csf_true;
}


/**
* 主要功能是：对port数值合法性校验
* 返回：true表示成功；false表示失败；
*
* @param port    表示网络端口
*/
csf_bool csf_ip_url::check_port(const csf_string& port) {

	int							tmp_int = 0;
	std::regex					tmp_pattern("[0-9]{0,5}");

	if (!std::regex_match(port, tmp_pattern)) {
		return csf_false;
	}
	else {
		//校验端口的合法性
		tmp_int = atoi(port.c_str());
		if (tmp_int >= 0 && tmp_int <= csf_max_ushort) {
			return csf_true;
		}
	}

	return csf_false;
}
