/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_null.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_null.hpp),表示各种类型数据的null值
*
*Others:
*
*History:
*******************************************************************************/


#if !defined(_CSF_NULL_H_)
#define _CSF_NULL_H_


#include <stdint.h>
#ifdef __cplusplus
#include <iostream>
#endif


#include "csf_typedef.h"
//#include "csf_attribute_exception_warning.hpp"


#ifdef __cplusplus
namespace csf
{
	namespace core
	{
#endif

		static const base::csf_string						csf_string_null("");
		//static const csf::core::system::attribute::csf_attribute_exception_warning			csf_attribute_exception_default;

#ifdef __cplusplus
	}
}
#endif


#endif // !defined(_CSF_NULL_H_)