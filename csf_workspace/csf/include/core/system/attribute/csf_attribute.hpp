/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:26
*
*Description: Class(csf_attribute)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INCLUDED_)
#define CSF_ATTRIBUTE_INCLUDED_

#include <list>
#include "csf_typedef.h"
#include "csf_stdcollector.hpp"
#include "csf_csftype_template.hpp"
#include "csf_configure_manager.hpp"
#include "csf_container_convert.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				//表示attribute字符串格式化缓存的默认长度
				#define csf_attribute_string_length					256

				/**
				 * 表示程度设置的配置项基类
				 * @author fz
				 * @version 1.0
				 * @created 05-7月-2018 20:09:26
				 */
				class csf_attribute : public csf::core::base::csf_csftype_template<csf_attribute>
				{

				public:
					/**
					* 表示配置属性的类型
					* @author Administrator
					* @version 1.0
					* @created 09-7月-2018 15:16:58
					*/
					enum csf_attribute_type
					{
						/**
						* 表示未知的属性类型
						*/
						csf_attribute_type_none = 0x00000001,
						/**
						* 表示布尔数据类型
						*/
						csf_attribute_type_bool = 0x00000002,
						/**
						* 表示整形数据类型
						*/
						csf_attribute_type_int = 0x00000004,
						/**
						* 表示长整形数据类型
						*/
						csf_attribute_type_int64 = 0x00000008,
						/**
						* 表示时间类型
						*/
						csf_attribute_type_time = 0x00000010,
						/**
						* 表示空间类型
						*/
						csf_attribute_type_space_size = 0x00000020,
						/**
						* 表示字符串类型
						*/
						csf_attribute_type_string = 0x00000040
					};
					inline explicit csf_attribute()
						: m_name("")
						, m_type(csf_attribute_type_none)
						, m_content("") {
					}
					virtual ~csf_attribute() {

					}

					/**
					* 根据类型创建一个对象
					*
					* @param type    表示属性的类型
					*/
					inline explicit csf_attribute(const csf_attribute::csf_attribute_type type)
						: m_name("")
						, m_type(type)
						, m_content("") {

					}
					/**
					 * 根据名称和类型创建一个对象
					 *
					 * @param name    表示属性的名称
					 * @param type    表示属性的类型
					 */
					inline explicit csf_attribute(const csf_string& name, const csf_attribute::csf_attribute_type type)
						: csf_attribute(name.c_str(), type) {

					}
					/**
					 * 根据名称和类型创建一个对象
					 *
					 * @param name    表示属性的名称
					 * @param type    表示属性的类型
					 */
					inline explicit csf_attribute(const csf_char* name, const csf_attribute::csf_attribute_type type)
						: m_name(name)
						, m_type(type)
						, m_content("") {

					}
					/**
					* 根据属性路径、类型创建一个对象
					*
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param type    表示属性的类型
					*/
					inline explicit csf_attribute(const csf_list<csf_string> items, const csf_attribute::csf_attribute_type type)
						: m_name("")
						, m_type(type)
						, m_items(items) {

					}

					/**
					 * 根据名称、属性路径、类型创建一个对象
					 *
					 * @param name    表示属性的名称
					 * @param items    表示该属性所对应的配置文件节点位置
					 *
					 * @param type    表示属性的类型
					 */
					inline explicit csf_attribute(const csf_string& name, const csf_list<csf_string> items, const csf_attribute::csf_attribute_type type)
						: csf_attribute(name.c_str(), items, type) {

					}
					/**
					 * 根据名称、属性路径、类型创建一个对象
					 *
					 * @param name    表示属性的名称
					 * @param items    表示该属性所对应的配置文件节点位置
					 *
					 * @param type    表示属性的类型
					 */
					inline explicit csf_attribute(const csf_char* name, const csf_list<csf_string> items, const csf_attribute::csf_attribute_type type)
						: m_name(name)
						, m_type(type)
						, m_items(items) {

					}
					/**
					 * 表示属性类型描述信息
					 */
					inline csf_attribute_type get_type() {

						return m_type;
					}
					/**
					 * 表示属性名称信息
					 */
					inline csf_string& get_name() {

						return m_name;
					}
					/**
					 * 表示属性名称信息
					 *
					 * @param new_value
					 */
					inline void set_name(const csf_string& new_value) {

						m_name = new_value;
					}
					/**
					 * 表示属性名称信息
					 *
					 * @param new_value
					 */
					inline void set_name(csf_char* new_value) {

						m_name = new_value;
					}
					/**
					 * 表示判断是否为空。
					 * 返回：true表示为空；false表示不为空。
					 */
					inline virtual csf_bool is_null() {

						if (csf_attribute_type_none == get_type()) {
							return csf_true;
						}
						return csf_false;
					}
					/**
					 * 表示判断是否不为空。
					 * 返回：true表示不为空；false表示为空。
					 */
					inline virtual csf_bool not_null() {

						return !is_null();
					}
					/**
					* 表示从配置管理器中获取配置项内容。
					* 返回：true表示获取到指定配置项数值；false表示没有获取到配置项数值。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param items    表示配置项的路径信息
					*/
					csf_bool get_configure(csf_configure_manager& configure_manager, csf_list<csf_string>& items);

					/**
					* 表示从配置管理器中获取配置项内容。
					* 返回：true表示获取到指定配置项数值；false表示没有获取到配置项数值。
					*
					* @param configure_manager    表示保存配置管理器对象
					*/
					csf_bool get_configure(csf_configure_manager& configure_manager);
					/**
					* 表示从配置管理器中获取配置项内容。
					* 返回：true表示获取到指定配置项数值；false表示没有获取到配置项数值。
					*
					* @param element    表示保存配置的属性对象
					* @param items    表示配置项的路径信息
					*/
					csf_bool get_configure(csf_element& element, csf_list<csf_string>& items);
					/**
					* 表示从配置文件中读取的数值。
					*/
					inline csf_string& get_content() {

						return m_content;
					}

					/**
					* 函数功能是将csf_attribute内容信息格式化
					*/
					inline csf_string to_string() {

						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf),
							"attribute[ type:%d  name:\"%s\"  items:%s  content:\"%s\" ]",
							get_type(),
							get_name().c_str(),
							items_to_string().c_str(),
							get_content().c_str());

						return tmp_buf;
					}
					/**
					* 表示处理csf_attribute属性操作。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					virtual csf_bool process(const csf_configure_manager& configure_manager
						, const csf_string& alias) {
						return csf_false;
					};
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
						, const csf_list<csf_string> root_items) {

						return csf_true;
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
						, csf_list<csf_string> root_items = std::list<csf_string>()) {

						return csf_true;
					}

					/**
					* 该函数实现异常运行，即属性异常出现时，调用异常对象实现异常处理。
					* 返回：true表示异常处理对象处理成功；false表示异常处理对象处理失败。
					*/
					inline virtual csf_bool exception_run() {

						return csf_false;
					}
				protected:
					/**
					* 表示初始化csf_attribute。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					csf_bool virtual init(const csf_configure_manager& configure_manager, const csf_string& alias) final;
					/**
					* 表示该属性所对应的配置文件节点位置
					*/
					inline csf_list<csf_string>& get_items() {

						return m_items;
					}
					/**
					* 表示该属性所对应的配置文件节点位置
					*
					* @param new_value
					*/
					inline void set_items(const csf_list<csf_string>& new_value) {

						m_items = new_value;
					}
					/**
					* 表示该属性所对应的配置文件节点位置
					*
					* @param root_items    表示属性管理器中根路径信息
					* @param items
					*/
					inline csf_void set_items(const csf_list<csf_string>& root_items
						, const csf_list<csf_string>& items) {

						csf_list<csf_string>			tmp_items = root_items;

						for (csf_string& tmp_item : (csf_list<csf_string>&)items) {
							tmp_items.push_back(tmp_item);
						}

						set_items(tmp_items);
					}
					/**
					* 函数功能是将items列表中的字符串格式化为："{a, b, c}"。
					*/
					inline csf_string items_to_string() {
						return csf_container_convert<csf_list<csf_string>>(get_items()).to_string();
					}
					/**
					* 表示属性类型描述信息
					*
					* @param new_value
					*/
					inline void set_type(const csf_attribute_type new_value) {

						m_type = new_value;
					}
					/**
					* 表示从配置文件中读取的数值。
					*
					* @param new_value
					*/
					inline csf_void set_content(const csf_string& new_value) {

						m_content = new_value;
					}
					/**
					* 表示从配置文件中读取的数值。
					*
					* @param new_value
					*/
					inline csf_void set_content(const csf_char* new_value) {

						m_content = new_value;
					}
				private:
					/**
					 * 表示属性名称信息
					 */
					csf_string m_name = "";
					/**
					 * 表示属性类型描述信息
					 */
					csf_attribute_type m_type = csf_attribute_type_none;
					/**
					 * 表示该属性所对应的配置文件节点位置
					 */
					csf_list<csf_string> m_items;
					/**
					* 表示从配置文件中读取的数值。
					*/
					csf_string m_content = "";
					
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_INCLUDED_)
