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
*Date: 13-3月-2019 16:56:49
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


/**
 * 功能：
 *    表示解析地址函数。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:
 * 80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
 * 
 * 返回：
 *    0  ：表示成功
 *    非0：表示错误
 * 
 * @param url    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
 * 80和192.168.1.10:80
 */
csf_int32 csf_ip_url::parse(const csf_string& url) {


	/**
	* 表示核验格式和截取字符串正则表达式
	*/
	//std::regex					tmp_regex("(\\w+):([0-9]{0,5})");
	std::regex					tmp_regex("(\\d+.\\d+.\\d+.\\d+):([0-9]{0,5})");
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
		if (!check_port(tmp_port)) {
			return csf_failure;
		}

		//校验ip地址的合法性
		if (!check_ip(tmp_match_result[1].str())) {
			return csf_failure;
		}
		else {
			set_ip(tmp_match_result[1].str());
		}

		set_port(tmp_port);

		return csf_url::parse(url);
	}

	return csf_failure;
}


/**
 * 功能：
 *    对ip地址的格式合法性校验。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.
 * 10。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
 * 
 * 返回：
 *    true表示成功；
 *    false表示失败；
 * 
 * @param ip    表示网络地址格式，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.
 * 168.1.10:80
 */
csf_bool csf_ip_url::check_ip(const csf_string& ip) {

	std::regex			tmp_pattern("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");

	if (!std::regex_match(ip, tmp_pattern)) {
		return csf_false;
	}

	return csf_true;
}


/**
 * 功能：
 *    对port数值合法性校验
 * 返回：
 *    true表示成功；
 *    false表示失败；
 * 
 * @param port    表示需要被校验的数值
 */
csf_bool csf_ip_url::check_port(const csf_string& port) {

	int							tmp_int = 0;
	std::regex					tmp_pattern("[0-9]{0,5}");

	if (!std::regex_match(port, tmp_pattern)) {
		return csf_false;
	}
	else {
		//校验端口的合法性
		return check_port(atoi(port.c_str()));
	}

	return csf_false;
}


/**
 * 主要功能是：根据ip和端口号设置url信息
 * 返回：0表示成功；非0表示错误
 * 
 * @param ip    表示ip字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.
 * 168.1.10:80
 * @param port    表示端口数据
 */
csf_int32 csf_ip_url::set_url(const csf_string& ip, const csf_ushort port) {


	if (check_ip(ip) && check_port(port)) {
		set_ip(ip);
		set_port(port);

		csf_char			tmp_buf[csf_ip_url_buffer_size] = { 0, };

		csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
			, "%s:%d"
			, ip.c_str()
			, port);
		set_url(tmp_buf);

		return csf_succeed;
	}
	return csf_failure;
}

