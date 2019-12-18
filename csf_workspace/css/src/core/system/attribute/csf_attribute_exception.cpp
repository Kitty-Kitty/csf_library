/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_exception.hpp
*
*Author: Administrator
*
*Version: 1.0
*
*Date: 05-7ÔÂ-2018 20:09:27
*
*Description: Class(csf_attribute_exception)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_attribute_exception.hpp"
//#include "csf_attribute_exception_warning.hpp"


using namespace csf::core::system::attribute;
using csf::core::system::attribute::csf_attribute_exception;



//const csf_attribute_exception csf_attribute_exception::m_default = csf_attribute_exception_warning();
const csf_attribute_exception csf_attribute_exception::m_default([](csf_attribute& attr) {
	csf_log_ex(warning, csf_log_code_warning
		, "%s process exception."
		, attr.to_string().c_str());
});