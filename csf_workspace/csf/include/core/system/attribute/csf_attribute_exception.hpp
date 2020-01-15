/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_exception.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:26
*
*Description: Class(csf_attribute_exception)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_EXCEPTION_INCLUDED_)
#define CSF_ATTRIBUTE_EXCEPTION_INCLUDED_

#include "csf_stdbind.hpp"
#include "csf_csftype_template.hpp"
#include "csf_attribute.hpp"
#include "csf_attribute_boundary.hpp"
#include "csf_logger.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				//表示异常处理回调函数
				typedef csf_function<csf_void(csf_attribute&)>	csf_attribute_exception_callback;

				//表示attribute exception字符串格式化缓存的默认长度
				#define csf_attribute_exception_string_length					256

				/**
				 * 表示属性解析异常的处理方式
				 * @author Administrator
				 * @version 1.0
				 * @created 05-7月-2018 20:09:26
				 */
				class csf_attribute_exception : public csf::core::base::csf_csftype_template<csf_attribute_exception>
				{

				public:
					inline explicit csf_attribute_exception()
						: m_callback(csf_nullptr) {

					}
					/**
					*
					* @param callback    表示异常回调函数
					*
					*/
					inline explicit csf_attribute_exception(const csf::core::system::attribute::csf_attribute_exception_callback callback) 
						: m_callback(callback) {
					}
					virtual ~csf_attribute_exception() {

					}

					/**
					* 表示异常回调函数
					*/
					inline csf::core::system::attribute::csf_attribute_exception_callback& get_callback() {

						return m_callback;
					}
					/**
					* 表示异常回调函数
					*
					* @param new_value
					*/
					inline void set_callback(const csf::core::system::attribute::csf_attribute_exception_callback& new_value) {

						m_callback = new_value;
					}
					/**
					* 表示判断是否为空。
					* 返回：true表示为空；false表示不为空。
					*/
					inline virtual csf_bool is_null() {

						if (csf_nullptr == get_callback()) {
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
					* 表示执行异常处理操作。
					* 返回：true表示执行成功；false表示执行失败。
					*
					* @param attribute    表示需要被处理的属性对象
					*/
					inline csf_bool run(const csf_attribute& attribute) {

						//如果回调函数不为空，则表示可以运行回调函数
						if (is_null()) {
							return csf_false;
						}
						else {
							get_callback()((csf_attribute&)attribute);
						}

						return csf_true;
					}
					/**
					* 表示异常的默认处理对象
					*/
					inline static const csf_attribute_exception& get_default() {

						return m_default;
					}
				private:
					/**
					 * 表示异常回调函数
					 */
					csf::core::system::attribute::csf_attribute_exception_callback m_callback = csf_nullptr;
					/**
					* 表示异常的默认处理对象
					*/
					static const csf_attribute_exception m_default;
				};
			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_EXCEPTION_INCLUDED_)
