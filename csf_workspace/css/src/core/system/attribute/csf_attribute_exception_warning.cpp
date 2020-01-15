/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_exception_warning.hpp
*
*Author: Administrator
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:27
*
*Description: Class(csf_attribute_exception_warning)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_attribute_exception_warning.hpp"

using csf::core::system::attribute::csf_attribute_exception_warning;


csf_attribute_exception_warning::csf_attribute_exception_warning()
	: csf_attribute_exception([](csf_attribute& attr) {
	csf_log_ex(warning, csf_log_code_warning
		, "%s process exception."
		, attr.to_string().c_str());
	}) {

}



csf_attribute_exception_warning::~csf_attribute_exception_warning() {

}


csf_void csf_attribute_exception_warning::print_warning(csf::core::system::attribute::csf_attribute &attribute) {

}