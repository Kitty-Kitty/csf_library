/*******************************************************************************
*
*Copyright:fz
*
*File name: vdu_logger_define.h
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/07/02
*
*Description: create (vdu_logger_define.h)��Ҫ������־��ӡ�ĸ��ֽӿں���
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _VDU_LOGGER_DEFINE_H_
#define _VDU_LOGGER_DEFINE_H_

#include "csf_logger.hpp"

#if 0


#include <stdio.h>
#include <stdarg.h>

#define _CSF_LOGGER_DEFINE_H_

/**
* ��ʾ��ǰϵͳ��ÿ����־����󳤶�
*/
#ifndef CSF_LOGGER_MAX_ERROR_STRING
#define CSF_LOGGER_MAX_ERROR_STRING						102400
#endif



/**
* ��ʾ����һ��ͨ�õ���־�ӿ�
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
* @param _strlevel_	��ʾ��־�����ַ���,ȡֵΪ"debug", "normal", "info", "notice", "warning", "error", "critical"
* @param _code_		��ʾ��־������
* @param _fmt_		��ʾ��־��ʽ���ַ���������printf("_fmt_", args)�е�_fmt_�ַ���
* @param ...		��ʾ��־��ʽ�������б�����printf("_fmt_", args)�е�args�б�
*/
#define csf_log_ex(_strlevel_, _code_, _fmt_, ...)		_csf_log_##_strlevel_(_code_, "<%s:%d>"_fmt_, #_strlevel_, _code_, ##__VA_ARGS__)

/**
* ��ʾ����һ���������͵���־
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
* @param _code_		��ʾ��־������
* @param _fmt_		��ʾ��־��ʽ���ַ���������printf("_fmt_", args)�е�_fmt_�ַ���
* @param ...		��ʾ��־��ʽ�������б�����printf("_fmt_", args)�е�args�б�
*/

#define _csf_log_debug(_code_, _fmt_, ...)		_csf_log_write_ex(debug, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_normal(_code_, _fmt_, ...)		_csf_log_write_ex(normal, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_info(_code_, _fmt_, ...)		_csf_log_write_ex(info, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_notice(_code_, _fmt_, ...)		_csf_log_write_ex(notice, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_warn(_code_, _fmt_, ...)		_csf_log_write_ex(warning, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_error(_code_, _fmt_, ...)		_csf_log_write_ex(error, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_critical(_code_, _fmt_, ...)	_csf_log_write_ex(critical, _code_, _fmt_, ##__VA_ARGS__)


/**
* ��ʾ��ǰʹ�õ���־����
*/
static int csf_log_level = 0;

/**
* ��ʾ����һ��printfд��־����,ͬʱ����ж���־����
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
* @param _level_	��ʾ��־����,ȡֵΪcsf_logger_level����
* @param _code_	��ʾ��־������
* @param _fmt_	��ʾ��־��ʽ���ַ���������printf("_fmt_", args)�е�_fmt_�ַ���
* @param ...	��ʾ��־��ʽ�������б�����printf("_fmt_", args)�е�args�б�
*/
static void _csf_log_write_ex(int _level_, int _code_, char *_fmt_, ...) {
	if (_level_ >= csf_log_level) {
		char				_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING] = { 0, };
		va_list				_tmp_marker_;

		va_start(_tmp_marker_, _fmt_);
		if (_vsnprintf(_tmp_buf_, sizeof(_tmp_buf_), _fmt_, _tmp_marker_) < 0) {
			_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING - 2] = '.';
			_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING - 3] = '.';
			_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING - 4] = '.';
		}
		va_end(_tmp_marker_);
		printf("%s\r\n", _tmp_buf_);
	}
}



#endif



#endif //_VDU_LOGGER_DEFINE_H_


