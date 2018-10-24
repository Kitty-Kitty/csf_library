/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_default_value.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 08-7月-2018 22:21:47
*
*Description: Class(csf_attribute_default_value)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_DEFAULT_VALUE_INCLUDED_)
#define CSF_ATTRIBUTE_DEFAULT_VALUE_INCLUDED_

#include "csf_attribute_exception_warning.hpp"
#include "csf_attribute_bool.hpp"
#include "csf_attribute_string.hpp"
#include "csf_attribute_int.hpp"
#include "csf_attribute_time.hpp"
#include "csf_attribute_space_size.hpp"

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
				 * @created 08-7月-2018 22:21:47
				 */
				template <class AttributeType, typename ValueType>
				class csf_attribute_default_value : public csf::core::system::attribute::csf_attribute_exception_warning
				{

				public:
					csf_attribute_default_value(ValueType val) 
						: csf::core::system::attribute::csf_attribute_exception_warning(
							[val](csf_attribute& attri) {

						((AttributeType&)attri).set_value(val); 
						csf_log_ex(warning, csf_log_code_warning
							, "%s used default value succeed."
							, ((AttributeType&)attri).to_string().c_str());

						}) {

					}
					virtual ~csf_attribute_default_value() {

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
					* @param new_value    表示默认的数值
					*/
					inline csf_void set_value(const ValueType& new_value) {

						m_value = new_value;
					}

				private:
					/**
					* 表示默认的数值类型
					*/
					ValueType m_value;
				};

#if 0

				/**
				* 表示csf_attribute_bool所使用的默认值类型。
				* @author Administrator
				* @version 1.0
				* @created 08-7月-2018 22:21:47
				*/
				template <csf_attribute_bool>
				class csf_attribute_default_value<csf_attribute_bool, csf_bool>
				{

				};

				/**
				* 表示csf_attribute_string所使用的默认值类型。
				* @author Administrator
				* @version 1.0
				* @created 08-7月-2018 22:21:47
				*/
				template <csf_attribute_string>
				class csf_attribute_default_value<csf_attribute_string, csf_string>
				{

				};

				/**
				* 表示csf_attribute_int所使用的默认值类型。
				* @author Administrator
				* @version 1.0
				* @created 08-7月-2018 22:21:47
				*/
				template <csf_attribute_int>
				class csf_attribute_default_value<csf_attribute_int, csf_int32>
				{

				};

				/**
				* 表示csf_attribute_time所使用的默认值类型。
				* @author Administrator
				* @version 1.0
				* @created 08-7月-2018 22:21:47
				*/
				template <csf_attribute_time>
				class csf_attribute_default_value<csf_attribute_time, csf_int64>
				{

				};

				/**
				* 表示csf_attribute_space_size所使用的默认值类型。
				* @author Administrator
				* @version 1.0
				* @created 08-7月-2018 22:21:47
				*/
				template <csf_attribute_space_size>
				class csf_attribute_default_value<csf_attribute_space_size, csf_int64>
				{

				};

#endif

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_DEFAULT_VALUE_INCLUDED_)
