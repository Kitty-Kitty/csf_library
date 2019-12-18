/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7月-2018 19:29:31
*
*Description: Class(csf_attribute_manager) 表示模块的属性管理器，主要提供模块配置属性统一管理，包括增、删、查、改等。
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_MANAGER_INCLUDED_)
#define CSF_ATTRIBUTE_MANAGER_INCLUDED_

#include "csf_attribute_manager_interface.hpp"
#include "csf_manager.hpp"
#include "csf_attribute_bool.hpp"
#include "csf_attribute_string.hpp"
#include "csf_attribute_int.hpp"
#include "csf_attribute_space_size.hpp"
#include "csf_attribute_time.hpp"
#include "csf_logger.hpp"


namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 表示模块的属性管理器
				 * @author Administrator
				 * @version 1.0
				 * @created 06-7月-2018 19:29:31
				 */
				class csf_attribute_manager : public csf::core::module::csf_manager, public csf::core::system::attribute::csf_attribute_manager_interface
				{

				public:
					inline explicit csf_attribute_manager()
						: m_configure_manager(csf_nullptr) {

					}

					virtual ~csf_attribute_manager() {
						clear();
					}

					/**
					 * 表创建的时候赋值配置管理器
					 *
					 * @param configure_manager    表示配置管理器地址
					 */
					inline explicit csf_attribute_manager(const csf_configure_manager* configure_manager)
						: m_configure_manager((csf_configure_manager*)configure_manager) {

					}
					/**
					 * 函数功能为：向attribute_manager中添加一个属性。
					 * 注意：表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复，否则操作失败。
					 * 返回：true表示成功；false表示失败。
					 *
					 * @param name    表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示添加的属性对象
					 */
					template <class AttributeType>
					inline csf_bool add(const csf_string& name, AttributeType& attribute) {

						if (name.empty()) {
							return csf_false;
						}

						return add(name.c_str(), attribute);
					}
					/**
					 * 函数功能为：向attribute_manager中添加一个属性。
					 * 注意：表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复，否则操作失败。
					 * 返回：true表示成功；false表示失败。
					 *
					 * @param name    表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示添加的属性对象
					 */
					template <class AttributeType>
					csf_bool add(const csf_char* name, AttributeType& attribute) {

						AttributeType			*tmp_new = csf_nullptr;


						//核验名称数据的合法性
						if (!name || csf_strlen(name) <= 0 || attribute.is_null()) {
							csf_log_ex(warning, csf_log_code_warning
								, "add attribute failed. reason: attribute/name is null!");
							return csf_false;
						}

						//查询该名称属性是否已经存在，如果已经存在则返回失败
						if (((csf_attribute&)find(name)).not_null()) {
							csf_log_ex(warning, csf_log_code_warning
								, "add name[ \"%s\" ] %s failed. reason: attribute existed!"
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}

						//如果数值为空，则需要重新获取属性数值
						if (attribute.get_content().empty()) {
							if (!get_configure_manager()) {
								csf_log_ex(warning, csf_log_code_warning
									, "add name[ \"%s\" ] %s failed. reason: configure manager is null!"
									, name
									, attribute.to_string().c_str());
								return csf_false;
							}

							if (!attribute.process(*get_configure_manager(), name)) {
								csf_log_ex(warning, csf_log_code_warning
									, "add name[ \"%s\" ] %s failed. reason: attribute process failed!"
									, name
									, attribute.to_string().c_str());
								return csf_false;
							}
						}

						//创建一个新能对象，并将属性信息更新到属性列表中
						tmp_new = new AttributeType(attribute);
						if (!tmp_new) {
							csf_log_ex(warning, csf_log_code_warning
								, "add name[ \"%s\" ] %s failed. reason: new a instance failed!"
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}
						else {
							get_attributes().insert(csf_unordered_map<csf_string, csf_attribute*>::value_type(name, tmp_new));

							csf_log_ex(notice, csf_log_code_notice
								, "add name[ \"%s\" ] %s succeed."
								, name
								, attribute.to_string().c_str());
						}

						return csf_true;
					}

					/**
					* 函数功能为：向attribute_manager中添加一个属性。
					* 注意：表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复，否则操作失败。
					* 返回：true表示成功；false表示失败。
					*
					* @param name    表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复。
					* @param attribute    表示添加的属性对象
					*/
					virtual csf_bool add(const csf_string& name, csf_attribute& attribute) {
						return add(name.c_str(), attribute);
					}
					/**
					* 函数功能为：向attribute_manager中添加一个属性。
					* 注意：表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复，否则操作失败。
					* 返回：true表示成功；false表示失败。
					*
					* @param name    表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复。
					* @param attribute    表示添加的属性对象
					*/
					virtual csf_bool add(const csf_char* name, csf_attribute& attribute) {
						return add<csf_attribute>(name, attribute);
					}
					/**
					 * 函数功能为：根据名称从attribute_manager中删除一个属性。
					 * 返回：true表示删除成功（不存在该名称属性默认返回成功）；false表示失败。
					 *
					 * @param name    表示需要删除的属性名称
					 */
					inline virtual csf_bool del(const csf_string& name) {

						if (name.empty()) {
							return csf_false;
						}

						return del(name.c_str());
					}
					/**
					 * 函数功能为：根据名称从attribute_manager中删除一个属性。
					 * 返回：true表示删除成功（不存在该名称属性默认返回成功）；false表示失败。
					 *
					 * @param name    表示需要删除的属性名称
					 */
					virtual csf_bool del(const csf_char* name);
					/**
					 * 表示该属性管理器使用的配置管理器对象地址。
					 */
					inline csf_configure_manager* get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * 函数功能为：根据名称从attribute_manager中查询一个属性。
					 * 返回：一个属性对象。
					 *
					 * @param name    表示属性名称
					 */
					inline virtual const csf_attribute& find(const csf_string& name) {

						if (name.empty()) {
							return csf_attribute::get_null();
						}

						return find(name.c_str());
					}
					/**
					 * 表示该属性管理器使用的配置管理器对象地址。
					 *
					 * @param newVal    表示配置管理器地址
					 */
					inline void set_configure_manager(const csf_configure_manager* newVal) {

						m_configure_manager = (csf_configure_manager*)newVal;
					}
					/**
					 * 函数功能为：根据名称从attribute_manager中查询一个属性。
					 * 返回：一个属性对象。
					 *
					 * @param name    表示需要的属性名称
					 */
					const csf_attribute& find(const csf_char* name);
					/**
					 * 函数功能为：更新attribute_manager中一个属性信息。
					 * 返回：true表示存在且更新成功；false表示不存在或失败。
					 *
					 * @param name    表示属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示属性对象
					 */
					template <class AttributeType>
					inline csf_bool update(const csf_string& name, AttributeType& attribute) {

						if (name.empty()) {
							return csf_false;
						}

						return update(name.c_str(), attribute);
					}
					/**
					 * 函数功能为：更新attribute_manager中一个属性信息。
					 * 返回：true表示存在且更新成功；false表示不存在或失败。
					 *
					 * @param name    表示属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示属性对象
					 */
					template <class AttributeType>
					csf_bool update(const csf_char* name, AttributeType& attribute) {

						csf_unordered_map<csf_string, csf_attribute*>::iterator		tmp_iter;


						//核验名称数据的合法性
						if (!name || csf_strlen(name) <= 0) {
							csf_log_ex(warning, csf_log_code_warning
								, "add attribute failed. attribute/name is null!");
							return csf_false;
						}

						//查询该名称属性是否已经存在，如果已经存在则返回失败
						tmp_iter = get_attributes().find(name);
						if (tmp_iter == get_attributes().end()) {
							csf_log_ex(warning, csf_log_code_warning
								, "update name[ \"%s\" ] %s failed. not found attribute."
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}

						if (tmp_iter->second) {
							delete tmp_iter->second;
							tmp_iter->second = csf_nullptr;
							get_attributes().erase(tmp_iter);
						}

						if (!add(name, attribute)) {
							csf_log_ex(warning, csf_log_code_warning
								, "update name[ \"%s\" ] %s failed. add attribute failed."
								, name
								, attribute.to_string().c_str());
							return csf_false;
						}

						csf_log_ex(notice, csf_log_code_notice
							, "update name[ \"%s\" ] %s succeed."
							, name
							, attribute.to_string().c_str());
						return csf_true;
					}
					/**
					* 函数功能为：更新attribute_manager中一个属性信息。
					* 返回：true表示存在且更新成功；false表示不存在或失败。
					*
					* @param name    表示属性名称，在一个attribute_manager中必须保证唯一不重复。
					* @param attribute    表示属性对象
					*/
					virtual csf_bool update(const csf_string& name, csf_attribute& attribute) {
						return update(name.c_str(), attribute);
					}
					/**
					* 函数功能为：更新attribute_manager中一个属性信息。
					* 返回：true表示存在且更新成功；false表示不存在或失败。
					*
					* @param name    表示属性名称，在一个attribute_manager中必须保证唯一不重复。
					* @param attribute    表示属性对象
					*/
					virtual csf_bool update(const csf_char* name, csf_attribute& attribute) {
						return update<csf_attribute>(name, attribute);
					}
					/**
					* 函数功能为：根据名称从attribute_manager获取一个属性数值。
					* 该函数直接返回一个指定类型数值，如果属性不存在则返回默认空值。空值列表：bool[false]，string[""]，int[0]，time[0]，space_
					* size[0]。
					*
					* 返回：返回指定属性的数值
					*
					* @param name    表示属性名称
					*/
					template <class AttributeType>
					inline auto get_value(const csf_string& name) {
						return get_value<AttributeType, ValueType>(name.c_str());
					}
					/**
					* 函数功能为：根据名称从attribute_manager获取一个属性数值。
					* 该函数直接返回一个指定类型数值，如果属性不存在则返回默认空值。空值列表：bool[false]，string[""]，int[0]，time[0]，space_
					* size[0]。
					*
					* 返回：返回指定属性的数值
					*
					* @param name    表示属性名称
					*/
					template <class AttributeType>
					inline auto get_value(const csf_char* name) {

						csf_attribute			&attr = (csf_attribute &)find(name);


						if (attr.is_null()) {

							//创建一个指定类型的空对象返回默认数据
							static AttributeType			tmp_ret(name);
							return tmp_ret.get_value();
						}
						else {
							return get_value<AttributeType>(attr);
						}
					}
					/**
					* 函数功能为：根据attribute获取一个属性数值。
					* 该函数直接返回一个指定类型数值，如果属性不存在则返回默认空值。空值列表：bool[false]，string[""]，int[0]，time[0]，space_
					* size[0]。
					*
					* 返回：返回指定属性的数值
					*
					* @param attribute    表示属性对象
					*/
					template <class AttributeType>
					inline auto get_value(csf_attribute& attribute) {
						return ((AttributeType&)attribute).get_value();
					}
					/**
					* 函数功能为：根据名称从attribute_manager获取一个属性数值保存在val引用中。
					*
					* 返回：true表示获取成功；false表示获取失败，其中不存在该数值也返回失败。
					*
					* @param val    表示获取到的属性数值保存在val引用中
					* @param name    表示属性名称
					*/
					template <class AttributeType, typename ValueType>
					inline csf_bool get_value(ValueType& val, const csf_string& name) {

						return get_value<AttributeType, ValueType>(val, name.c_str());
					}
					/**
					* 函数功能为：根据名称从attribute_manager获取一个属性数值保存在val引用中。
					*
					* 返回：true表示获取成功；false表示获取失败，其中不存在该数值也返回失败。
					*
					* @param val    表示获取到的属性数值保存在val引用中
					* @param name    表示属性名称
					*/
					template <class AttributeType, typename ValueType>
					inline csf_bool get_value(ValueType& val, const csf_char* name) {

						csf_attribute			&attr = find(name);


						if (attr.is_null()) {
							return csf_false;
						}
						else {
							val = ((AttributeType&)attr).get_value();
						}
						return csf_true;
					}
					/**
					* 函数功能为：根据名称从attribute_manager中查询一个属性并返回属性内容。
					* 返回：字符串内容。
					*
					* @param name    表示需要的属性名称
					*/
					virtual csf_string get_content(const csf_char* name);
					/**
					* 函数功能为：根据名称从attribute_manager中查询一个属性并返回属性内容。
					* 返回：字符串内容。
					*
					* @param name    表示需要的属性名称
					*/
					inline virtual csf_string get_content(const csf_string& name) {

						return get_content(name.c_str());
					}
					/**
					* 表示清空配置管理器中的所有内容。
					* 返回：true表示处理成功；false表示处理失败
					*/
					inline csf_bool clear() {

						for (auto &tmp_attribute : get_attributes()) {
							if (tmp_attribute.second) {
								delete tmp_attribute.second;
								tmp_attribute.second = csf_nullptr;
							}
						}

						get_attributes().clear();

						return csf_true;
					}
				protected:
					/**
					 * 表示配置的属性列表，方便查找各个属性内容
					 */
					inline csf_unordered_map<csf_string, csf_attribute*>& get_attributes() {

						return m_attributes;
					}

				private:
					/**
					 * 表示配置的属性列表，方便查找各个属性内容
					 */
					csf_unordered_map<csf_string, csf_attribute*> m_attributes;
					/**
					 * 表示该属性管理器使用的配置管理器对象地址。
					 */
					csf_configure_manager* m_configure_manager = csf_nullptr;

					/**
					 * 表示配置的属性列表，方便查找各个属性内容
					 *
					 * @param newVal
					 */
					inline void set_attributes(csf_unordered_map<csf_string, csf_attribute*>& newVal) {

						m_attributes = newVal;
					}
				};
			}
		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_MANAGER_INCLUDED_)
