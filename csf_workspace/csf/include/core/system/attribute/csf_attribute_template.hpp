/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_template.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:25
*
*Description: Class(csf_attribute_template)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_TEMPLATE_INCLUDED_)
#define CSF_ATTRIBUTE_TEMPLATE_INCLUDED_

#include "csf_attribute_printf.h"
#include "csf_attribute_exception.hpp"
#include "csf_attribute.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/************************************************************************/
				/* 属性数值的字符缓存默认长度                                                 */
				/************************************************************************/
				#define csf_attribute_string_default_length				128					// 属性数值的字符缓存的默认长度

				/**
				 * 表示程度设置的配置项基类
				 * @author fz
				 * @version 1.0
				 * @created 05-7月-2018 20:09:25
				 */
				template <typename ValueType>
				class csf_attribute_template : public csf::core::system::attribute::csf_attribute
				{

				public:
// 					inline explicit csf_attribute_template() {
// 					}
					virtual ~csf_attribute_template() {

					}
// 					inline explicit csf_attribute_template(ValueType val)
// 						: m_value(val) {
// 					}
					/**
					* 根据类型创建一个对象
					*
					* @param type    表示属性的类型
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_template(const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param type    表示属性的类型
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_template(const csf_string& name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param type    表示属性的类型
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_template(const csf_char* name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* 根据属性路径、类型创建一个对象
					*
					* @param type    表示属性的类型
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_template(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(items, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param type    表示属性的类型
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_template(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, items, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param type    表示属性的类型
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_template(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, items, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					 * 表示异常处理处理对象内容
					 */
					inline csf::core::system::attribute::csf_attribute_exception& get_exception() {

						return m_exception;
					}
					/**
					 * 表示异常处理处理对象内容
					 *
					 * @param new_value
					 */
					inline void set_exception(const csf::core::system::attribute::csf_attribute_exception& new_value) {

						m_exception = new_value;
					}
					/**
					 * 表示当前属性的数值内容。
					 */
					inline ValueType get_value() {

						return m_value;
					}
					/**
					 * 表示当前属性的数值内容。
					 *
					 * @param new_value    表示需要设置的属性数值
					 */
					inline void set_value(const ValueType new_value) {

						m_value = new_value;
					}
					/**
					* 表示去除字符串中的空白字符。
					* 返回：非空表示成功；空表示成功；
					*
					* @param str    表示需要被处理的字符串
					*/
					inline const csf_string shrink(const csf_string& str) {

						return shrink(str.c_str());
					}
					/**
					* 表示去除字符串中的空白字符。
					* 返回：非空表示成功；空表示成功；
					*
					* @param buf    表示需要被处理的字符串
					*/
					inline const csf_string shrink(const csf_char* buf) {

						csf_char					tmp_buf[csf_attribute_string_default_length] = { 0, };
						csf_char					*tmp_pos = (csf_char*)buf;
						csf_char					*tmp_dest = tmp_buf;


						if (!buf || csf_strlen(buf) <= 0 ||
							csf_strlen(buf) > csf_attribute_string_default_length) {
							return csf_string_null;
						}

						//处理无法识别的字符，保留可识别的字符
						while (*tmp_pos != '\0') {
							if (csf_char_no_space(*tmp_pos)) {
								*tmp_dest++ = *tmp_pos;
							}

							++tmp_pos;
						}

						return tmp_buf;
					}
					/**
					* 该函数实现异常运行，即属性异常出现时，调用异常对象实现异常处理。
					* 返回：true表示异常处理对象处理成功；false表示异常处理对象处理失败。
					*/
					inline virtual csf_bool exception_run() {

						return get_exception().run(*this);
					}
					/**
					* 表示处理csf_attribute属性操作。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					inline virtual csf_bool process(const csf_configure_manager& configure_manager
						, const csf_string& alias) final {

						//如果属性自己的名称为空，则要采用该别名作为属性名称
						if (get_name().empty()) {
							if (alias.empty()) {
								csf_attribute_log(warning, csf_logger_level_warning,
									"items and alias is null.");
								return csf_false;
							}
							else {
								set_name(alias);
							}
						}

						//从配置管理中获取配置项数值
						if (!get_configure((csf_configure_manager&)configure_manager)) {
							csf_attribute_log(warning, csf_logger_level_warning,
								"get attribute[%s] content from configure_manager[%p] error."
								, alias.c_str()
								, &configure_manager);
							return csf_false;
						}

						return process_attribute(configure_manager, alias);
					}
					/**
					* 表示处理csf_attribute属性操作。主要为满足不同子类的多态现实。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					* @param root_items    表示属性管理器中根路径信息
					*/
					inline virtual csf_bool process(const csf_configure_manager& configure_manager
						, const csf_string& alias
						, const csf_list<csf_string> root_items) final {

						if (!root_items.empty()) {
							set_items(root_items, get_items());
						}

						return process(configure_manager, alias);
					}
					/**
					* 表示处理csf_attribute属性操作。主要为满足不同子类的多态现实。
					* 返回：true表示失败；false表示成功。
					*
					* @param element    表示配置项的根节点对象。该配置信息优先与"csf_configure_manager*
					* m_configure_manager"配置信息。如果配置了该对象，则优先采用该信息。所有配置项都出该对象中获取
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					* @param root_items    表示属性管理器中根路径信息
					*/
					inline virtual csf_bool process(const csf_element& element
						, const csf_string& alias
						, csf_list<csf_string> root_items = csf_list<csf_string>()) final {

						if (!root_items.empty()) {
							set_items(root_items, get_items());
						}

						//如果属性自己的名称为空，则要采用该别名作为属性名称
						if (get_name().empty()) {
							if (alias.empty()) {
								csf_attribute_log(warning, csf_logger_level_warning,
									"items and alias is null.");
								return csf_false;
							}
							else {
								set_name(alias);
							}
						}

						//从配置管理中获取配置项数值
						if (!get_configure((csf_element&)element, get_items())) {
							csf_attribute_log(warning, csf_logger_level_warning,
								"get attribute[%s] content from element[%p] error."
								, alias.c_str()
								, &element);
							return csf_false;
						}

						if (csf_false == process_attribute(element, alias)) {
							return exception_run();
						}
						else {
							return csf_true;
						}
					}
				protected:
					/**
					* 表示处理csf_attribute属性操作。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					virtual csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) = 0;
					/**
					* 表示处理csf_attribute属性操作。这里与csf_attribute中不同的是，这里添加一层process_attribute函数主要是为了实现异常（e
					* xception）的统一处理。当异常出现时，直接根据返回错误，调用异常处理函数。
					* 返回：true表示失败；false表示成功。
					*
					* @param element    表示保存配置对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					virtual csf_bool process_attribute(const csf_element& element, const csf_string& alias) = 0;
				private:
					/**
					 * 表示异常处理处理对象内容
					 */
					csf::core::system::attribute::csf_attribute_exception m_exception;
					/**
					 * 表示当前属性的数值内容。
					 */
					ValueType m_value;
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_TEMPLATE_INCLUDED_)
