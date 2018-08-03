/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_module_factory_printf.h
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/07/02
*
*Description: create (csf_module_factory_printf.h)��Ҫ����ģ�鹤����־��ӡ��ʽ����
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CSF_MODULE_FACTORY_PRINTF_H_
#define _CSF_MODULE_FACTORY_PRINTF_H_



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
#define csf_module_factory_log(_strlevel_, _code_, _fmt_, ...)	do {											\
	_csf_log_write_ex(_strlevel_, _code_, "module_factory[ 0x%x : %d : %s : %s ] " _fmt_, 								\
		this, get_count(), get_name().c_str(), get_symbol_path().c_str(), ##__VA_ARGS__);								\
} while (0)


#endif //_CSF_MODULE_FACTORY_PRINTF_H_


