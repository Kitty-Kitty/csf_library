/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_bool.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:26
*
*Description: Class(csf_attribute_bool)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_bool.hpp"

using csf::core::system::attribute::csf_attribute_bool;


csf_attribute_bool::csf_attribute_bool()
	: csf_attribute_template<csf_bool>(csf_attribute::csf_attribute_type_bool, csf_false) {

}



csf_attribute_bool::~csf_attribute_bool() {

}

/**
* ��ʼ�������������ݵ��ַ�����ֵ
*/
const csf_string csf_attribute_bool::m_value_string[] = { "false", "true" };