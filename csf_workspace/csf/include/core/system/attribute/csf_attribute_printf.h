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
*Description: create (csf_attribute_printf.h)��Ҫ��������ģ�����־��ӡ
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CSF_ATTRIBUTE_PRINTF_H_
#define _CSF_ATTRIBUTE_PRINTF_H_



#include "csf_logger.hpp"


/**
* ��ʾ����һ��ģ�����������־�ӿ�
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
* @param _strlevel_	��ʾ��־�����ַ���,ȡֵΪ"debug", "normal", "info", "notice", "warning", "error", "critical"
* @param _code_		��ʾ��־������
* @param _fmt_		��ʾ��־��ʽ���ַ���������printf("_fmt_", args)�е�_fmt_�ַ���
* @param ...		��ʾ��־��ʽ�������б�����printf("_fmt_", args)�е�args�б�
*/
#define csf_attribute_log(_strlevel_, _code_, _fmt_, ...)	do {		\
	_csf_log_write_ex(_strlevel_, _code_, "%s " _fmt_, 					\
		to_string().c_str(), ##__VA_ARGS__);							\
} while (0)


#endif //_CSF_ATTRIBUTE_PRINTF_H_


