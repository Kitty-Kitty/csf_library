/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_bool.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:26
*
*Description: Class(csf_attribute_bool)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_BOOL_INCLUDED_)
#define CSF_ATTRIBUTE_BOOL_INCLUDED_

#include "csf_attribute_template.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 表示布尔类型的属性内容
				 * @author fz
				 * @version 1.0
				 * @created 05-7月-2018 20:09:26
				 */
				class csf_attribute_bool : public csf::core::system::attribute::csf_attribute_template<csf_bool>
				{

				public:
					csf_attribute_bool();
					virtual ~csf_attribute_bool();

					/**
					 * 根据名称和类型创建一个对象
					 * 
					 * @param name    表示属性的名称
					 */
					inline explicit csf_attribute_bool(const csf_string& name) 
						: csf_attribute_template<csf_bool>(name, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * 根据名称和类型创建一个对象
					 * 
					 * @param name    表示属性的名称
					 */
					inline explicit csf_attribute_bool(const csf_char* name)
						: csf_attribute_template<csf_bool>(name, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * 根据名称、属性路径、类型创建一个对象
					 * 
					 * @param name    表示属性的名称
					 * @param items    表示该属性所对应的配置文件节点位置
					 * 
					 */
					inline explicit csf_attribute_bool(const csf_string& name, const csf_list<csf_string> items)
						: csf_attribute_template<csf_bool>(name, items, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * 根据名称、属性路径、类型创建一个对象
					 * 
					 * @param name    表示属性的名称
					 * @param items    表示该属性所对应的配置文件节点位置
					 * 
					 */
					inline explicit csf_attribute_bool(const csf_char* name, const csf_list<csf_string> items)
						: csf_attribute_template<csf_bool>(name, items, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * 根据名称、属性路径、类型创建一个对象
					 * 
					 * @param items    表示该属性所对应的配置文件节点位置
					 * 
					 */
					inline explicit csf_attribute_bool(const csf_list<csf_string> items)
						: csf_attribute_template<csf_bool>(items, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					* 函数功能是将csf_attribute内容信息格式化
					*/
					inline csf_string to_string() {
						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf),
							"%s value[%s]",
							csf_attribute::to_string().c_str(),
							value_to_string().c_str());

						return tmp_buf;
					}
					/**
					* 函数功能：将csf_attribute数值内容格式化为字符串
					*/
					inline csf_string value_to_string() {

						return m_value_string[get_value()];
					}
				private:
					/**
					* 表示布尔类型数据的字符串数值
					*/
					static const csf_string m_value_string[];
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_BOOL_INCLUDED_)
