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

#include "csf_ip_url.hpp"

using csf::modules::connect::csf_ip_url;


csf_ip_url::csf_ip_url()
	: m_ip("")
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

	return 0;
}


/**
 * 表示解析地址函数
 * 
 * @param url    表示url地址字符串数据
 */
csf_int32 csf_ip_url::parse(const csf_char* url) {

	return 0;
}