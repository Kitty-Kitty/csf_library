/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_string.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7月-2018 14:45:30
*
*Description: Class(csf_attribute_string)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_STRING_INCLUDED_)
#define CSF_ATTRIBUTE_STRING_INCLUDED_

#include "csf_attribute_exception.hpp"
#include "csf_attribute_template.hpp"
//#include "csf_null.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 表示字符串性类型。
				 * @author fz
				 * @version 1.0
				 * @created 11-7月-2018 14:45:30
				 */
				class csf_attribute_string : public csf::core::system::attribute::csf_attribute_template<csf_string>
				{

				public:
					inline explicit csf_attribute_string()
						: csf_attribute_template<csf_string>(csf_attribute_type_string, csf_string_null) {
					}

					virtual ~csf_attribute_string() {

					}

					/**
					* 根据类型创建一个对象
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_string(const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(csf_attribute_type_string, csf_string_null, ex) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_string(const csf_string& name
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_string(name.c_str(), ex) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_string(const csf_char* name
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(name, csf_attribute_type_string, csf_string_null, ex) {

					}
					/**
					* 根据属性路径、类型创建一个对象
					*
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_string(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(items, csf_attribute_type_string, csf_string_null, ex) {

					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_string(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_string(name.c_str(), items, ex) {

					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_string(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(name, items, csf_attribute_type_string, csf_string_null, ex) {

					}

				protected:
					/**
					 * 表示处理csf_attribute属性操作。这里与csf_attribute中不同的是，这里添加一层process_attribute函数主要是为了实现异常（e
					 * xception）的统一处理。当异常出现时，直接根据返回错误，调用异常处理函数。
					 * 返回：true表示失败；false表示成功。
					 * 
					 * @param configure_manager    表示保存配置管理器对象
					 * @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					 */
					csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias);

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_STRING_INCLUDED_)
