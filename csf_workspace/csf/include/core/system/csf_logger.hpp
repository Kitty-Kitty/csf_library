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
*Date: 01-7��-2018 20:38:59
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
* ��ʾ��־�Ĵ�������Ϣ
* @author fz
* @version 1.0
* @created 02-7��-2018 16:50:37
*/
typedef enum
{
	/**
	* ��ʾ����δ֪������
	*/
	csf_log_code_debug = 0,
	/**
	* ��ʾͨ�ô�����
	*/
	csf_log_code_normal = 10,
	/**
	* ��ʾ��Ϣ������
	*/
	csf_log_code_info = 100,
	/**
	* ��ʾ֪ͨ�������ش�����
	*/
	csf_log_code_notice = 200,
	/**
	* ��ʾ�����ظ澯������
	*/
	csf_log_code_warning = 300,
	/**
	* ��ʾ���ش��������
	*/
	csf_log_code_error = 400,
	/**
	* ��ʾ����������
	*/
	csf_log_code_critical = 500
} csf_log_code;


/**
* ��ʾ��־���������б�
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
*/
typedef enum
{
	/**
	* ��ʾ��־��debug����
	*/
	csf_logger_level_debug = 0x00000000,
	/**
	* ��ʾ��־��normal����
	*/
	csf_logger_level_normal,
	/**
	* ��ʾ��־��info����
	*/
	csf_logger_level_info,
	/**
	* ��ʾ��־��notice����
	*/
	csf_logger_level_notice,
	/**
	* ��ʾ��־��warning����
	*/
	csf_logger_level_warning,
	/**
	* ��ʾ��־��error����
	*/
	csf_logger_level_error,
	/**
	* ��ʾ��־��critical����
	*/
	csf_logger_level_critical
} csf_logger_level;


//�����Ӧ���ַ�������ʾ��־��ʽ�еġ���־����
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

//#define BOOST_LOG_DYN_LINK
//#define BOOST_LOG_USE_COMPILER_TLS
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, boost::log::sources::severity_logger_mt<csf_logger_level>)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity, "Severity", csf_logger_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_scope, "Scope", boost::log::attributes::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_code, "Code", int)

/**
* ��ʾ����һ��д��־����
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
* @param _level_	��ʾ��־����,ȡֵΪcsf_logger_level����
* @param _code_		��ʾ��־������
* @param _string_	��ʾ��־������Ϣ
*/
#define	BOOST_LOG_WRITE(_level_, _code_, _string_)		do {							\
	boost::log::sources::severity_logger<csf_logger_level> slg;							\
	slg.add_attribute("Code", boost::log::attributes::constant<int>(_code_));			\
	slg.add_attribute("TimeStamp", boost::log::attributes::local_clock());				\
	slg.add_attribute("ThreadID", boost::log::attributes::current_thread_id());			\
	BOOST_LOG_SEV(slg, _level_) << _string_;											\
} while (0)																				\


/**
* ��ʾ����һ��д��־����,ͬʱ����ж���־����
* @author f
* @version 1.0
* @created 01-7��-2018 20:38:59
* @param _level_	��ʾ��־����,ȡֵΪcsf_logger_level����
* @param _code_		��ʾ��־������
* @param _string_	��ʾ��־������Ϣ
*/
#define	BOOST_LOG_WRITE_EX(_level_, _code_, _string_)	do {							\
	if(_level_ >= csf::core::system::csf_logger::get_level()) {							\
		BOOST_LOG_WRITE(_level_, _code_, _string_);										\
	}																					\
} while (0)																				\


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
			* ��ʾlogger���������ƶ���
			*/
			#define CSF_LOGGER_ATTRIBUTE_NAME(name)							"_csf_logger_attribute_"#name
			/**
			* ��ʾlogger��Ŀ¼����
			*/
#ifdef WIN32
			#define CSF_LOGGER_DIRECTORY_NAME								"log\\"
#else
			#define CSF_LOGGER_DIRECTORY_NAME								"log/"
#endif
			
			/**
			 * ��ʾ��־ϵͳ����
			 * @author f
			 * @version 1.0
			 * @created 01-7��-2018 20:38:59
			 */
			class csf_logger : public csf::core::module::csf_interface
			{

			public:
				csf_logger();
				virtual ~csf_logger();

				/**
				* ��ʾ���������ļ�������־ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�
				* @param path    ��ʾ��־�ļ��������Ŀ¼·��
				*/
				explicit csf_logger(const csf_configure_manager* configure_manager, const csf_string path = "");
				/**
				 * ��ʾ�����ļ���ַ
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * ģ���ʼ��
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ��ʾ�����ļ���ַ
				 *
				 * @param new_value
				 */
				csf_void set_configure_manager(const csf_configure_manager* new_value);
				/**
				 * ģ������
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ģ��ֹͣ
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ��ʾ��־�ļ��Ļع���С
				 */
				inline csf_uint64 get_rotation_size() {

					return m_rotation_size;
				}
				/**
				 * ��ʾ��־�ļ��Ļع���С
				 *
				 * @param new_value
				 */
				inline csf_void set_rotation_size(const csf_uint64 new_value) {

					m_rotation_size = new_value;
				}
				/**
				 * ��ʾ���̴洢������С
				 */
				inline csf_uint64 get_stored_max_size() {

					return m_stored_max_size;
				}
				/**
				 * ��ʾ���̴洢������С
				 *
				 * @param new_value
				 */
				inline csf_void set_stored_max_size(const csf_uint64 new_value) {

					m_stored_max_size = new_value;
				}
				/**
				 * ��ʾ���̵���С�ռ��С
				 */
				inline csf_uint64 get_disk_min_free_size() {

					return m_disk_min_free_size;
				}
				/**
				 * ��ʾ���̵���С�ռ��С
				 *
				 * @param new_value
				 */
				inline csf_void set_disk_min_free_size(const csf_uint64 new_value) {

					m_disk_min_free_size = new_value;
				}
				/**
				* ��ʾ��ǰϵͳ����־����Ĭ��notice����
				*/
				inline static csf_logger_level get_level() {

					return m_level;
				}
				/**
				* ��ʾ��ǰϵͳ����־����Ĭ��notice����
				*
				* @param new_value    ��ʾ���õ�ϵͳ��־����
				*/
				inline static void set_level(csf_logger_level new_value) {

					m_level = new_value;
				}
				/**
				* ��ʾ��־�ļ������Ŀ¼
				*/
				inline csf_string& get_path() {

					return m_path;
				}
				/**
				* ��ʾ��־�ļ������Ŀ¼
				*
				* @param new_value
				*/
				inline csf_void set_path(const csf_string& new_value) {

					m_path = new_value;
				}
				/**
				* ��ʾ��־�ļ�����ʽ
				*/
				inline csf_string& get_file_name_format() {

					return m_file_name_format;
				}
				/**
				* ��ʾ��־�ļ�����ʽ
				*
				* @param new_value
				*/
				inline csf_void set_file_name_format(const csf_string& new_value) {

					m_file_name_format = new_value;
				}
				/**
				* ���Թ���������־����ģ����Ҫ��������������
				*/
				inline csf_void* get_attribute_manager() {

					return m_attribute_manager;
				}
				/**
				* ��ʾ����̨���
				*/
				inline boost::shared_ptr<text_sink> get_text_sink_ptr() {

					return m_text_sink_ptr;
				}
				/**
				* ��ʾ�ļ����
				*/
				inline boost::shared_ptr<file_sink> get_file_sink_ptr() {

					return m_file_sink_ptr;
				}
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
				static void write(int _level_, int _code_, char *_fmt_, ...);
			protected:
				/**
				* ��ʾ��־�����Ӧ�������б����ݡ�
				*/
				inline const csf_unordered_map<csf_string, csf_logger_level>& get_level_name() {

					return m_level_name;
				}
				/**
				* ��ʾͨ����־����������ַ�����ȡ��Ӧ�����ּ���
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
				*
				* @param level    ��ʾת���󷵻ص���־������ֵ
				* @param name    ��ʾ��Ҫ��ת������־��������
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
				 * ��ʾ�����ļ���ַ
				 */
				csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				 * ��ʾ��־�ļ������Ŀ¼
				 */
				csf_string m_path = "";
				/**
				 * ��ʾ��־�ļ��Ļع���С
				 */
				csf_uint64 m_rotation_size = 0;
				/**
				 * ��ʾ���̴洢������С
				 */
				csf_uint64 m_stored_max_size = 0;
				/**
				 * ��ʾ���̵���С�ռ��С
				 */
				csf_uint64 m_disk_min_free_size = 0;
				/**
				* ��ʾ��ǰϵͳ����־����Ĭ��notice����
				*/
				static csf_logger_level m_level;
				/**
				* ��ʾ����̨���
				*/
				boost::shared_ptr<text_sink> m_text_sink_ptr;
				/**
				* ��ʾ�ļ����
				*/
				boost::shared_ptr<file_sink> m_file_sink_ptr;
				/**
				* ��ʾ��־�ļ�����ʽ
				*/
				csf_string m_file_name_format = "";
				/**
				* ��־ģ����Ҫ����һ�����Թ��������洢��־ģ����Ҫ��������������
				*/
				csf_void* m_attribute_manager;
				/**
				* ��ʾ��־�����Ӧ�������б����ݡ�
				*/
				static const csf_unordered_map<csf_string, csf_logger_level> m_level_name;
				/**
				* ��ʾ����̨���
				*
				* @param new_value
				*/
				inline csf_void set_text_sink_ptr(const boost::shared_ptr<text_sink> new_value) {

					m_text_sink_ptr = new_value;
				}
				/**
				* ��ʾ�ļ����
				*
				* @param new_value
				*/
				inline csf_void set_file_sink_ptr(const boost::shared_ptr<file_sink> new_value) {

					m_file_sink_ptr = new_value;
				}
				/**
				* ���Թ���������־����ģ����Ҫ��������������
				*
				* @param new_value
				*/
				inline csf_void set_attribute_manager(csf_void* new_value) {

					m_attribute_manager = new_value;
				}
			};

		}

	}

}

#include "csf_logger_define.hpp"


#endif // !defined(CSF_LOGGER_INCLUDED_)
