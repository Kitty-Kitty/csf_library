/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_int.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7月-2018 11:09:59
*
*Description: Class(csf_attribute_int)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INT_INCLUDED_)
#define CSF_ATTRIBUTE_INT_INCLUDED_

#include "csf_attribute_exception.hpp"
#include "csf_attribute_number.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/************************************************************************/
				/* 需要提取的参数个数														*/
				/************************************************************************/
				#define csf_attribute_int_parametes_size						1		//表示需要提取的参数个数
				/**
				 * 表示整形数据类型。
				 * @author fz
				 * @version 1.0
				 * @created 11-7月-2018 11:09:59
				 */
				class csf_attribute_int : public csf::core::system::attribute::csf_attribute_number
				{

				public:
					inline explicit csf_attribute_int()
						: csf_attribute_number(csf_attribute_type_int) {
					}

					virtual ~csf_attribute_int() {

					}

					/**
					* 根据类型创建一个对象
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int(const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(csf_attribute_type_int, boundary, ex) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int(const csf_string& name
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int(name.c_str(), boundary, ex) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int(const csf_char* name
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(name, csf_attribute_type_int, boundary, ex) {

					}
					/**
					* 根据属性路径、类型创建一个对象
					*
					* @param items    表示该属性所对应的配置文件节点位置
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_int(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(items, csf_attribute_type_int, boundary, ex) {

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
					inline explicit csf_attribute_int(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int(name.c_str(), items, boundary, ex) {

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
					inline explicit csf_attribute_int(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(name, items, csf_attribute_type_int, boundary, ex) {

					}
					/**
					 * 从内容中解析需要的参数。
					 * 返回：ture表示解析成功；false表示解析失败。
					 * 
					 * @param content    表示需要解析的内容信息
					 */
					inline csf_bool parse_parametes(const csf_char* content) {

						return csf_true;
					}
					/**
					 * 从内容中解析需要的参数。
					 * 返回：ture表示解析成功；false表示解析失败。
					 * 
					 * @param content    表示需要解析的内容信息
					 */
					csf_bool parse_parametes(const csf_string& content);
					/**
					 * 函数功能是将csf_attribute内容信息格式化
					 */
					inline csf_string to_string() {

						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
							, "%s value[ %lld ]"
							, csf_attribute::to_string().c_str()
							, get_value()
						);

						return tmp_buf;
					}

				protected:
					/**
					 * 表示处理csf_attribute属性操作。这里与csf_attribute_template中不同的是，这里添加一层process_number函数主要是为了
					 * 实现数据边界的统一处理。
					 * 返回：true表示失败；false表示成功。
					 * 
					 * @param configure_manager    表示保存配置管理器对象
					 * @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					 */
					virtual csf_bool process_number(const csf_configure_manager& configure_manager, const csf_string& alias);

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_INT_INCLUDED_)
