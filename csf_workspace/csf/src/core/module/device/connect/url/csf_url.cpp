/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_url.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 28-7月-2018 14:23:51
*
*Description: Class(csf_url) url地址信息的基础类信息
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_url.hpp"

using csf::core::module::connect::csf_url;


csf_url::csf_url()
	: m_url("")
	, m_type(csf_url_type_none) {

}



csf_url::~csf_url() {

}