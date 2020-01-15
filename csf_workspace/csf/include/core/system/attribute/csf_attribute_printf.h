/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_attribute_printf.h
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/07/02
*
*Description: create (csf_attribute_printf.h)主要用于属性模块的日志打印
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CSF_ATTRIBUTE_PRINTF_H_
#define _CSF_ATTRIBUTE_PRINTF_H_



#include "csf_logger.hpp"


/**
* 表示定义一个模块管理器的日志接口
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _strlevel_	表示日志级别字符串,取值为"debug", "normal", "info", "notice", "warning", "error", "critical"
* @param _code_		表示日志错误码
* @param _fmt_		表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
* @param ...		表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
*/
#define csf_attribute_log(_strlevel_, _code_, _fmt_, ...)	do {		\
	_csf_log_write_ex(_strlevel_, _code_, "%s " _fmt_, 					\
		to_string().c_str(), ##__VA_ARGS__);							\
} while (0)


#endif //_CSF_ATTRIBUTE_PRINTF_H_


