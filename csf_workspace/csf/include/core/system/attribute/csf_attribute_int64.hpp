/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_int64.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:28
*
*Description: Class(csf_attribute_int64)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INT64_INCLUDED_)
#define CSF_ATTRIBUTE_INT64_INCLUDED_

#include "csf_attribute_number.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 表示长整形数据类型属性
				 * @author fz
				 * @version 1.0
				 * @created 05-7月-2018 20:09:28
				 */
				class csf_attribute_int64 : public csf::core::system::attribute::csf_attribute_number
				{

				public:
					inline explicit csf_attribute_int64()
						: csf::core::system::attribute::csf_attribute_number(csf_attribute_type_int64) {

					}
					virtual ~csf_attribute_int64() {

					}

					/**
					* 根据类型创建一个对象
					*
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int64(const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(type, boundary, ex){

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int64(const csf_string& name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(name, type, boundary, ex) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int64(const csf_char* name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(name, type, boundary, ex) {

					}
					/**
					* 根据属性路径、类型创建一个对象
					*
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int64(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null()) 
					
						: csf_attribute_number(items, type, boundary, ex) {

					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int64(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(name, items, type, boundary, ex) {

					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int64(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null()) 
					
						: csf_attribute_number(name, items, type, boundary, ex) {

					}


				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_INT64_INCLUDED_)
