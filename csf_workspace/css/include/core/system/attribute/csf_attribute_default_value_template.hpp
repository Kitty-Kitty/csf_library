/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_default_value_template.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 08-7月-2018 22:21:47
*
*Description: Class(csf_attribute_default_value_template)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_DEFAULT_VALUE_TEMPLATE_INCLUDED_)
#define CSF_ATTRIBUTE_DEFAULT_VALUE_TEMPLATE_INCLUDED_

#include "csf_attribute_exception_warning.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * 表示异常发生未获取属性值时，采用默认的数值代替。
				 * @author Administrator
				 * @version 1.0
				 * @updated 08-7月-2018 22:25:17
				 */
				template <typename ValueType>
				class csf_attribute_default_value_template : public csf::core::system::attribute::csf_attribute_exception_warning
				{

				public:
					csf_attribute_default_value_template(ValueType value) 
						: csf_attribute_exception([&value](csf_attribute& attr) {attr.set_va})
						, m_value(value) {

					}
					virtual ~csf_attribute_default_value_template() {

					}

					/**
					 * 表示默认的数值类型
					 */
					inline ValueType& get_value() {

						return m_value;
					}
					/**
					 * 表示默认的数值类型
					 * 
					 * @param newVal    表示默认的数值
					 */
					inline csf_void set_value(const ValueType& newVal) {

						m_value = newVal;
					}

				private:
					/**
					 * 表示默认的数值类型
					 */
					ValueType m_value;

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_DEFAULT_VALUE_TEMPLATE_INCLUDED_)
