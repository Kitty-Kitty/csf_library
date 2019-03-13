/*******************************************************************************
*
*Copyright: fangzhenmu
*
*Author: fangzhenmu
*
*File name: csf_ipv6_url.hpp
*
*Version: 1.0
*
*Date: 13-3月-2019 17:52:25
*
*Description: Class(csf_ipv6_url)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ipv6_url.hpp"

using csf::modules::connect::csf_ipv6_url;


csf_ipv6_url::csf_ipv6_url() {

}



csf_ipv6_url::~csf_ipv6_url() {

}





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
csf_int32 csf_ipv6_url::parse(const csf_string& url) {

	return 0;
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
csf_bool csf_ipv6_url::check_ip(const csf_string& ip) {

	return csf_true;
}