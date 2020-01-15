/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_logger.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 01-7月-2018 20:38:59
*
*Description: Class(csf_logger)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_LOGGER_INCLUDED_)
#define CSF_LOGGER_INCLUDED_

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>  
#include <boost/log/support/date_time.hpp>
#include <boost/thread/thread.hpp>
#include "csf_interface.hpp"


/**
* 表示日志的错误码信息
* @author fz
* @version 1.0
* @created 02-7月-2018 16:50:37
*/
typedef enum
{
	/**
	* 表示调试未知错误码
	*/
	csf_log_code_debug = 0,
	/**
	* 表示通用错误码
	*/
	csf_log_code_normal = 10,
	/**
	* 表示消息错误码
	*/
	csf_log_code_info = 100,
	/**
	* 表示通知但不严重错误码
	*/
	csf_log_code_notice = 200,
	/**
	* 表示较严重告警错误码
	*/
	csf_log_code_warning = 300,
	/**
	* 表示严重错误错误码
	*/
	csf_log_code_error = 400,
	/**
	* 表示崩溃错误码
	*/
	csf_log_code_critical = 500
} csf_log_code;


/**
* 表示日志级别类型列表
* @author f
* @version 1.0
* @created 01-7月-2018 20:38:59
*/
typedef enum
{
	/**
	* 表示日志的debug级别
	*/
	csf_logger_level_debug = 0x00000000,
	/**
	* 表示日志的normal级别
	*/
	csf_logger_level_normal,
	/**
	* 表示日志的info级别
	*/
	csf_logger_level_info,
	/**
	* 表示日志的notice级别
	*/
	csf_logger_level_notice,
	/**
	* 表示日志的warning级别
	*/
	csf_logger_level_warning,
	/**
	* 表示日志的error级别
	*/
	csf_logger_level_error,
	/**
	* 表示日志的critical级别
	*/
	csf_logger_level_critical
} csf_logger_level;

//级别对应的字符串，表示日志格式中的“日志级别”
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& stream, csf_logger_level _level_) {

	static const char* const _string_[] = {
		"debug", "normal", "info", "notice", "warning", "error", "critical" };

	if (static_cast<std::size_t>(_level_) < (sizeof(_string_) / sizeof(*_string_))) {
		stream << _string_[_level_];
	}
	else {
		stream << static_cast<int>(_level_);
	}

	return stream;
}


BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, boost::log::sources::severity_logger_mt<csf_logger_level>)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity, "Severity", csf_logger_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_scope, "Scope", boost::log::attributes::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_code, "Code", int)


#if (BOOST_VERSION == 105500)
#include <boost/utility/empty_deleter.hpp>
typedef boost::empty_deleter			csf_null_deleter;
#else
#include <boost/core/null_deleter.hpp>
typedef boost::null_deleter				csf_null_deleter;
#endif
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend>	text_sink;
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend>		file_sink;


namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			* 表示logger的属性名称定义
			*/
			#define CSF_LOGGER_ATTRIBUTE_NAME(name)							"_csf_logger_attribute_"#name
			/**
			* 表示logger的目录名称
			*/
#ifdef WIN32
			#define CSF_LOGGER_DIRECTORY_NAME								"log\\"
#else
			#define CSF_LOGGER_DIRECTORY_NAME								"log/"
#endif
			
			/**
			 * 表示日志系统内容
			 * @author f
			 * @version 1.0
			 * @created 01-7月-2018 20:38:59
			 */
			class csf_logger : public csf::core::module::csf_interface
			{

			public:
				csf_logger();
				virtual ~csf_logger();

				/**
				* 表示根据配置文件创建日志模块
				*
				* @param configure_manager    表示配置文件
				* @param path    表示日志文件保存的主目录路径
				*/
				explicit csf_logger(const csf_configure_manager* configure_manager, const csf_string path = "");
				/**
				 * 表示配置文件地址
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * 模块初始化
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 表示配置文件地址
				 *
				 * @param newVal
				 */
				csf_void set_configure_manager(const csf_configure_manager* newVal);
				/**
				 * 模块启动
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 模块停止
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * 表示日志文件的回滚大小
				 */
				inline csf_uint64 get_rotation_size() {

					return m_rotation_size;
				}
				/**
				 * 表示日志文件的回滚大小
				 *
				 * @param newVal
				 */
				inline csf_void set_rotation_size(const csf_uint64 newVal) {

					m_rotation_size = newVal;
				}
				/**
				 * 表示磁盘存储的最大大小
				 */
				inline csf_uint64 get_stored_max_size() {

					return m_stored_max_size;
				}
				/**
				 * 表示磁盘存储的最大大小
				 *
				 * @param newVal
				 */
				inline csf_void set_stored_max_size(const csf_uint64 newVal) {

					m_stored_max_size = newVal;
				}
				/**
				 * 表示磁盘的最小空间大小
				 */
				inline csf_uint64 get_drive_min_free_size() {

					return m_drive_min_free_size;
				}
				/**
				 * 表示磁盘的最小空间大小
				 *
				 * @param newVal
				 */
				inline csf_void set_drive_min_free_size(const csf_uint64 newVal) {

					m_drive_min_free_size = newVal;
				}
				/**
				* 表示当前系统的日志级别，默认notice级别
				*/
				inline static csf_logger_level get_level() {

					return m_level;
				}
				/**
				* 表示当前系统的日志级别，默认notice级别
				*
				* @param newVal    表示配置的系统日志级别
				*/
				inline static void set_level(csf_logger_level newVal) {

					m_level = newVal;
				}
				/**
				* 表示日志文件保存的目录
				*/
				inline csf_string& get_path() {

					return m_path;
				}
				/**
				* 表示日志文件保存的目录
				*
				* @param newVal
				*/
				inline csf_void set_path(const csf_string& newVal) {

					m_path = newVal;
				}
				/**
				* 表示日志文件名格式
				*/
				inline csf_string& get_file_name_format() {

					return m_file_name_format;
				}
				/**
				* 表示日志文件名格式
				*
				* @param newVal
				*/
				inline csf_void set_file_name_format(const csf_string& newVal) {

					m_file_name_format = newVal;
				}
				/**
				* 属性管理器，日志保存模块需要的配置属性内容
				*/
				inline csf_void* get_attribute_manager() {

					return m_attribute_manager;
				}
			protected:
				/**
				* 表示日志级别对应的名称列表内容。
				*/
				inline const csf_unordered_map<csf_string, csf_logger_level>& get_level_name() {

					return m_level_name;
				}
				/**
				* 表示通过日志级别的名称字符串获取对应的数字级别。
				* 返回：true表示成功；false表示失败。
				*
				* @param level    表示转换后返回的日志级别数值
				* @param name    表示需要被转换的日志级别名称
				*/
				inline csf_bool convert(csf_logger_level& level, const csf_string name) {

					csf_unordered_map<csf_string, csf_logger_level>::iterator			tmp_iter;


					tmp_iter = const_cast<csf_unordered_map<csf_string, csf_logger_level>&>(get_level_name()).find(name);
					if (tmp_iter != get_level_name().end()) {
						level = tmp_iter->second;
						return csf_true;
					}

					return csf_false;
				}

			private:
				/**
				 * 表示配置文件地址
				 */
				csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				 * 表示日志文件保存的目录
				 */
				csf_string m_path = "";
				/**
				 * 表示日志文件的回滚大小
				 */
				csf_uint64 m_rotation_size = 0;
				/**
				 * 表示磁盘存储的最大大小
				 */
				csf_uint64 m_stored_max_size = 0;
				/**
				 * 表示磁盘的最小空间大小
				 */
				csf_uint64 m_drive_min_free_size = 0;
				/**
				* 表示当前系统的日志级别，默认notice级别
				*/
				static csf_logger_level m_level;
				/**
				* 表示控制台输出
				*/
				boost::shared_ptr<text_sink> m_text_sink_ptr;
				/**
				* 表示文件输出
				*/
				boost::shared_ptr<file_sink> m_file_sink_ptr;
				/**
				* 表示日志文件名格式
				*/
				csf_string m_file_name_format = "";
				/**
				* 日志模块需要包含一个属性管理器，存储日志模块需要的配置属性内容
				*/
				csf_void* m_attribute_manager;
				/**
				* 表示日志级别对应的名称列表内容。
				*/
				static const csf_unordered_map<csf_string, csf_logger_level> m_level_name;
				/**
				* 表示控制台输出
				*/
				inline boost::shared_ptr<text_sink> get_text_sink_ptr() {

					return m_text_sink_ptr;
				}
				/**
				* 表示控制台输出
				*
				* @param newVal
				*/
				inline csf_void set_text_sink_ptr(const boost::shared_ptr<text_sink> newVal) {

					m_text_sink_ptr = newVal;
				}
				/**
				* 表示文件输出
				*/
				inline boost::shared_ptr<file_sink> get_file_sink_ptr() {

					return m_file_sink_ptr;
				}
				/**
				* 表示文件输出
				*
				* @param newVal
				*/
				inline csf_void set_file_sink_ptr(const boost::shared_ptr<file_sink> newVal) {

					m_file_sink_ptr = newVal;
				}
				/**
				* 属性管理器，日志保存模块需要的配置属性内容
				*
				* @param newVal
				*/
				inline csf_void set_attribute_manager(csf_void* newVal) {

					m_attribute_manager = newVal;
				}
			};

		}

	}

}

#include "csf_logger_define.h"


#endif // !defined(CSF_LOGGER_INCLUDED_)
