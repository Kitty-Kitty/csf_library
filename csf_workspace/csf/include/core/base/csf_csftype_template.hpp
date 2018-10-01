/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csftype_template.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 06-7月-2018 17:15:59
*
*Description: Class(csf_csftype_template)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFTYPE_TEMPLATE_INCLUDED_)
#define CSF_CSFTYPE_TEMPLATE_INCLUDED_

#include "csf_csftype.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 主要用于构造csf_csftype的模板类型。该模板主要用于创建一个空对象作为为空的返回值，以减少指针的使用。
			 * @author f
			 * @version 1.0
			 * @created 06-7月-2018 17:15:59
			 */
			template <typename TypeName>
			class csf_csftype_template : public csf::core::base::csf_csftype
			{

			public:
				csf_csftype_template() {

				}

				virtual ~csf_csftype_template() {

				}

				/**
				* 表示定义的一个空对象,作为该类型数据的默认空值。为减少指针的使用，满足判断空提供默认值。
				*/
				csf_csftype_template& operator = (const csf_csftype_template& new_value) const {
					return (csf_csftype_template&)*this;
				}

				/**
				 * 表示判断是否为空。
				 * 返回：true表示为空；false表示不为空。
				 */
				inline virtual csf_bool is_null() {

					return csf_true;
				}
				/**
				 * 表示判断是否不为空。
				 * 返回：true表示不为空；false表示为空。
				 */
				inline virtual csf_bool not_null() {

					return csf_true;
				}
				/**
				 * 表示定义的一个空对象
				 */
				inline static const TypeName& get_null() {

					return m_null;
				}

			protected:
				/**
				 * 表示定义的一个空对象
				 * 
				 * @param new_value
				 */
				inline csf_void set_null(const TypeName& new_value) {

					m_null = new_value;
				}

			private:
				/**
				 * 表示定义的一个空对象,作为该类型数据的默认空值。为减少指针的使用，满足判断空提供默认值。
				 */
				static const TypeName m_null;				
			};

			//这里对静态null对象的初始化操作
			template<typename TypeName> const TypeName csf_csftype_template<TypeName>::m_null;
		}

	}

}
#endif // !defined(CSF_CSFTYPE_TEMPLATE_INCLUDED_)
