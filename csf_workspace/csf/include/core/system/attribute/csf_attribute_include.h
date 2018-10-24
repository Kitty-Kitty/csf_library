/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_include.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7月-2018 19:29:31
*
*Description: Class(csf_attribute_include) 表示属性相关内容的统一头文件，其中包含各种必须头文件内容
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INCLUDED_INCLUDED_)
#define CSF_ATTRIBUTE_INCLUDED_INCLUDED_



#include "csf_attribute_manager.hpp"
#include "csf_attribute_exception_include.h"


/**
* 表示属性名称定义
*/
#define CSF_ATTRIBUTE_NAME(name)							#name

using namespace csf::core::system;
using namespace csf::core::system::attribute;


#endif // !defined(CSF_ATTRIBUTE_INCLUDED_INCLUDED_)