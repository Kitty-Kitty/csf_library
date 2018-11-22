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



/**
* 表示当前系统中每条日志的最大长度
*/
#ifndef CSF_LOGGER_MAX_ERROR_STRING
#define CSF_LOGGER_MAX_ERROR_STRING						102400
#endif


#ifdef WIN32

#define csf_static_thread_local			static thread_local

#else

#if defined(HAVE___ATTRIBUTE__) && defined(HAVE_TLS)
#define ATTR_INITIAL_EXEC __attribute__ ((tls_model ("initial-exec")))
//#define csf_static_thread_local			static __thread
#define csf_static_thread_local			static thread_local
#else
#define ATTR_INITIAL_EXEC
//#warning "disable TLS."
#define csf_static_thread_local			
#endif

#endif


/**
* 表示定义一个写日志函数
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _level_	表示日志级别,取值为csf_logger_level类型
* @param _code_		表示日志错误码
* @param _string_	表示日志错误信息
*/
#define	BOOST_LOG_WRITE(_level_, _code_, _string_)		do {							\
	boost::log::sources::severity_logger<csf_logger_level> slg;							\
	slg.add_attribute("Code", boost::log::attributes::constant<int>(_code_));			\
	slg.add_attribute("TimeStamp", boost::log::attributes::local_clock());				\
	slg.add_attribute("ThreadID", boost::log::attributes::current_thread_id());			\
	BOOST_LOG_SEV(slg, _level_) << _string_;											\
} while (0)																				\


/**
* 表示定义一个写日志函数,同时添加判断日志级别
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
* @param _level_	表示日志级别,取值为csf_logger_level类型
* @param _code_		表示日志错误码
* @param _string_	表示日志错误信息
*/
#define	BOOST_LOG_WRITE_EX(_level_, _code_, _string_)	do {							\
	if(_level_ >= csf::core::system::csf_logger::get_level()) {							\
		BOOST_LOG_WRITE(_level_, _code_, _string_);										\
	}																					\
} while (0)																				\


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
	static void _csf_log_write(int _level_, int _code_, char *_fmt_, ...) {

		if (_level_ >= csf::core::system::csf_logger::get_level()) {

			csf_static_thread_local char		_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING] = { 0, };
			csf_static_thread_local size_t		_tmp_size_ = 0;
			csf_static_thread_local char*		_tmp_buf_point_ = NULL;
			csf_static_thread_local bool		_tmp_is_free = false;
			va_list								_tmp_marker_;


			va_start(_tmp_marker_, _fmt_);

			//这里对日志的频繁分配内存做优化。
			//1、如果已经分配的内存够用，则用已经分配的。（实现需求的内存长度小与固定已有的内存长度，则采用固定内存;）
			//2、如果已经分配的内存不够用，则重新分配，并释放
			_tmp_size_ = csf_vscprintf(_fmt_, _tmp_marker_);
			if (_tmp_size_ < sizeof(_tmp_buf_)) {
				_tmp_buf_point_ = _tmp_buf_;
				//将末尾的一个字节清0，表示字符结束
				_tmp_buf_point_[_tmp_size_ - 1] = '\0';
				_tmp_size_ = sizeof(_tmp_buf_);
				_tmp_is_free = false;
			}
			else {
				_tmp_buf_point_ = (char*)malloc(_tmp_size_);
				//将末尾的一个字节清0，表示字符结束
				_tmp_buf_point_[_tmp_size_ - 1] = '\0';
				_tmp_is_free = true;
			}

			if (csf_vsnprintf(_tmp_buf_point_, _tmp_size_, _fmt_, _tmp_marker_) < 0) {
				_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING - 2] = '.';
				_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING - 3] = '.';
				_tmp_buf_[CSF_LOGGER_MAX_ERROR_STRING - 4] = '.';
			}
			va_end(_tmp_marker_);
			//printf("%s\r\n", _tmp_buf_);
			BOOST_LOG_WRITE((csf_logger_level)_level_, (csf_log_code)_code_, _tmp_buf_point_);

			if (_tmp_is_free) {
				free(_tmp_buf_point_);
				_tmp_buf_point_ = NULL;
			}
		}
	}

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


