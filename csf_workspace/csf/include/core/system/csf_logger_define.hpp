/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_logger_define.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/07/02
*
*Description: create (csf_logger_define.hpp)主要保存日志打印的各种接口函数
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CSF_LOGGER_DEFINE_H_
#define _CSF_LOGGER_DEFINE_H_



#ifdef __cplusplus
extern "C" {
#endif
	#ifdef __linux__
		static int _vscprintf(const char *format, va_list pargs)
		{
			int				tmp_ret = 0;
			va_list			tmp_argcopy;


			va_copy(tmp_argcopy, pargs);
			tmp_ret = vsnprintf(NULL, 0, format, tmp_argcopy);
			va_end(tmp_argcopy);
			return tmp_ret;
		}
	#endif

	/**
	* 表示定义一个printf写日志函数,同时添加判断日志级别
	* @author f
	* @version 1.0
	* @created 01-7月-2018 20:38:59
	* @param _level_	表示日志级别,取值为csf_logger_level类型
	* @param _code_	表示日志错误码
	* @param _fmt_	表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
	* @param ...	表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
	*/
	#define _csf_log_write(_level_, _code_, _fmt_, ...)		csf::core::system::csf_logger::write(_level_, _code_, _fmt_, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif


/**
* 表示定义一个printf写日志函数,同时添加判断日志级别
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _strlevel_	表示日志级别字符串,取值为"debug", "normal", "info", "notice", "warning", "error", "critical"
* @param _code_		表示日志错误码
* @param _fmt_		表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
* @param ...		表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
*/
#define _csf_log_write_ex(_strlevel_, _code_, _fmt_, ...)	do {{							\
	_csf_log_write(csf_logger_level_##_strlevel_, _code_, "func[%s:%d] " _fmt_,				\
 						__FUNCTION__, __LINE__, ##__VA_ARGS__);								\
}} while (0)																				\


/**
* 表示定义一个通用的日志接口
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _strlevel_	表示日志级别字符串,取值为"debug", "normal", "info", "notice", "warning", "error", "critical"
* @param _code_		表示日志错误码
* @param _fmt_		表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
* @param ...		表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
*/
#define csf_log_ex(_strlevel_, _code_, _fmt_, ...)		_csf_log_write_ex(_strlevel_, _code_, _fmt_, ##__VA_ARGS__)


/**
* 表示定义一个简单通用的日志接口
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _strlevel_	表示日志级别字符串,取值为"debug", "normal", "info", "notice", "warning", "error", "critical"
* @param _fmt_		表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
* @param ...		表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
*/
#define csf_log(_strlevel_, _fmt_, ...)		_csf_log_write_ex(_strlevel_, csf_log_code_##_strlevel_, _fmt_, ##__VA_ARGS__)


#ifdef USED_LOG_XXX
/**
* 表示定义一个各种类型的日志
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _code_		表示日志错误码
* @param _fmt_		表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
* @param ...		表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
*/

#define _csf_log_debug(_code_, _fmt_, ...)		_csf_log_write_ex(debug, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_normal(_code_, _fmt_, ...)		_csf_log_write_ex(normal, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_info(_code_, _fmt_, ...)		_csf_log_write_ex(info, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_notice(_code_, _fmt_, ...)		_csf_log_write_ex(notice, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_warn(_code_, _fmt_, ...)		_csf_log_write_ex(warning, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_error(_code_, _fmt_, ...)		_csf_log_write_ex(error, _code_, _fmt_, ##__VA_ARGS__)

#define _csf_log_critical(_code_, _fmt_, ...)	_csf_log_write_ex(critical, _code_, _fmt_, ##__VA_ARGS__)



/**
* 表示定义一个各种类型的日志
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _code_		表示日志错误码
* @param _fmt_		表示日志格式化字符串，类型printf("_fmt_", args)中的_fmt_字符串
* @param ...		表示日志格式化参数列表，类型printf("_fmt_", args)中的args列表
*/
#define csf_log_debug(_fmt_, ...)				_csf_log_debug(csf_log_code_debug, _fmt_, ...)		

#define csf_log_normal(_fmt_, ...)				_csf_log_normal(csf_log_code_normal, _fmt_, ...)		

#define csf_log_info(_fmt_, ...)				_csf_log_info(csf_log_code_info, _fmt_, ...)		

#define csf_log_notice(_fmt_, ...)				_csf_log_notice(csf_log_code_notice, _fmt_, ...)		

#define csf_log_warn(_fmt_, ...)				_csf_log_warn(csf_log_code_warning, _fmt_, ...)		

#define csf_log_error(_fmt_, ...)				_csf_log_error(csf_log_code_error, _fmt_, ...)		

#define csf_log_critical(_fmt_, ...)			_csf_log_critical(csf_log_code_critical, _fmt_, ...)	


#endif //USED_LOG_XXX


#endif //_CSF_LOGGER_DEFINE_H_


