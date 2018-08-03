/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_manager_interface.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7月-2018 19:09:43
*
*Description: Interface(csf_attribute_manager_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_MANAGER_INTERFACE_INCLUDED_)
#define CSF_ATTRIBUTE_MANAGER_INTERFACE_INCLUDED_

#include "csf_typedef.h"
#include "csf_attribute.hpp"

using namespace csf::core::base;
using namespace csf::core::system::attribute;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 定义属性管理器的操作接口，主要包括添、删、查、改等。
				 * @author fz
				 * @version 1.0
				 * @created 06-7月-2018 19:09:43
				 */
				class csf_attribute_manager_interface
				{

				public:
					csf_attribute_manager_interface() {

					}

					virtual ~csf_attribute_manager_interface() {

					}

					/**
					 * 函数功能为：向attribute_manager中添加一个属性。
					 * 注意：表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复，否则操作失败。
					 * 返回：true表示成功；false表示失败。
					 * 
					 * @param name    表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示添加的属性对象
					 */
					virtual csf_bool add(const csf_string& name, csf_attribute& attribute) =0;
					/**
					 * 函数功能为：向attribute_manager中添加一个属性。
					 * 注意：表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复，否则操作失败。
					 * 返回：true表示成功；false表示失败。
					 * 
					 * @param name    表示添加的属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示添加的属性对象
					 */
					virtual csf_bool add(const csf_char* name, csf_attribute& attribute) =0;
					/**
					 * 函数功能为：根据名称从attribute_manager中删除一个属性。
					 * 返回：true表示删除成功（不存在该名称属性默认返回成功）；false表示失败。
					 * 
					 * @param name    表示需要删除的属性名称
					 */
					virtual csf_bool del(const csf_string& name) =0;
					/**
					 * 函数功能为：根据名称从attribute_manager中删除一个属性。
					 * 返回：true表示删除成功（不存在该名称属性默认返回成功）；false表示失败。
					 * 
					 * @param name    表示需要删除的属性名称
					 */
					virtual csf_bool del(const csf_char* name) =0;
					/**
					 * 函数功能为：根据名称从attribute_manager中查询一个属性。
					 * 返回：一个属性对象。
					 * 
					 * @param name    表示属性名称
					 */
					virtual const csf_attribute& find(const csf_string& name) =0;
					/**
					 * 函数功能为：根据名称从attribute_manager中查询一个属性。
					 * 返回：一个属性对象。
					 * 
					 * @param name    表示需要的属性名称
					 */
					virtual const csf_attribute& find(const csf_char* name) =0;
					/**
					 * 函数功能为：更新attribute_manager中一个属性信息。
					 * 返回：true表示存在且更新成功；false表示不存在或失败。
					 * 
					 * @param name    表示属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示属性对象
					 */
					virtual csf_bool update(const csf_string& name, csf_attribute& attribute) =0;
					/**
					 * 函数功能为：更新attribute_manager中一个属性信息。
					 * 返回：true表示存在且更新成功；false表示不存在或失败。
					 * 
					 * @param name    表示属性名称，在一个attribute_manager中必须保证唯一不重复。
					 * @param attribute    表示属性对象
					 */
					virtual csf_bool update(const csf_char* name, csf_attribute& attribute) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_MANAGER_INTERFACE_INCLUDED_)
