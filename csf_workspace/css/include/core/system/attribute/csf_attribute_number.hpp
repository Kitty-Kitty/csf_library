/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_number.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:28
*
*Description: Class(csf_attribute_number)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_NUMBER_INCLUDED_)
#define CSF_ATTRIBUTE_NUMBER_INCLUDED_

#include "csf_attribute_boundary.hpp"
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
				 * 表示数据类型属性
				 * @author fz
				 * @version 1.0
				 * @created 05-7月-2018 20:09:28
				 */
				class csf_attribute_number : public csf::core::system::attribute::csf_attribute_template<csf_int64>
				{

				public:
					inline explicit csf_attribute_number() 
						: csf_attribute_template<csf_int64>(csf_attribute::csf_attribute_type_int64, 0){

					}
					virtual ~csf_attribute_number() {

					}

					/**
					* 根据类型创建一个对象
					*
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_number(const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(type, 0, ex)
						, m_boundary(boundary) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_number(const csf_string& name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, type, 0, ex)
						, m_boundary(boundary) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param type    表示属性的类型
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_number(const csf_char* name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, type, 0, ex)
						, m_boundary(boundary) {

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
					inline explicit csf_attribute_number(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(items, type, 0, ex)
						, m_boundary(boundary) {

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
					inline explicit csf_attribute_number(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, items, type, 0, ex)
						, m_boundary(boundary) {

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
					inline explicit csf_attribute_number(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, items, type, 0, ex)
						, m_boundary(boundary) {

					}
					/**
					 * 表示模块数据阈值核验对象
					 */
					inline csf::core::system::attribute::csf_attribute_boundary& get_boundary() {

						return m_boundary;
					}
					/**
					 * 表示模块数据阈值核验对象
					 *
					 * @param newVal    表示需要设置的阈值内容
					 */
					inline csf_void set_boundary(csf::core::system::attribute::csf_attribute_boundary& newVal) {

						m_boundary = newVal;
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
					virtual csf_bool process_number(const csf_configure_manager& configure_manager, const csf_string& alias) = 0;
					/**
					* 表示处理csf_attribute属性操作。这里与csf_attribute中不同的是，这里添加一层process_attribute函数主要是为了实现异常（e
					* xception）的统一处理。当异常出现时，直接根据返回错误，调用异常处理函数。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					virtual csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) final;
				private:
					/**
					 * 表示模块数据阈值核验对象
					 */
					csf::core::system::attribute::csf_attribute_boundary m_boundary;

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_NUMBER_INCLUDED_)
