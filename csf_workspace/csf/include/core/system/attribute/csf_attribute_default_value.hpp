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
*Date: 08-7��-2018 22:21:47
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
				 * ��ʾ�쳣����δ��ȡ����ֵʱ������Ĭ�ϵ���ֵ���档
				 * @author Administrator
				 * @version 1.0
				 * @created 08-7��-2018 22:21:47
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
					* ��ʾĬ�ϵ���ֵ����
					*/
					inline ValueType& get_value() {

						return m_value;
					}
					/**
					* ��ʾĬ�ϵ���ֵ����
					*
					* @param new_value    ��ʾĬ�ϵ���ֵ
					*/
					inline csf_void set_value(const ValueType& new_value) {

						m_value = new_value;
					}

				private:
					/**
					* ��ʾĬ�ϵ���ֵ����
					*/
					ValueType m_value;
				};

#if 0

				/**
				* ��ʾcsf_attribute_bool��ʹ�õ�Ĭ��ֵ���͡�
				* @author Administrator
				* @version 1.0
				* @created 08-7��-2018 22:21:47
				*/
				template <csf_attribute_bool>
				class csf_attribute_default_value<csf_attribute_bool, csf_bool>
				{

				};

				/**
				* ��ʾcsf_attribute_string��ʹ�õ�Ĭ��ֵ���͡�
				* @author Administrator
				* @version 1.0
				* @created 08-7��-2018 22:21:47
				*/
				template <csf_attribute_string>
				class csf_attribute_default_value<csf_attribute_string, csf_string>
				{

				};

				/**
				* ��ʾcsf_attribute_int��ʹ�õ�Ĭ��ֵ���͡�
				* @author Administrator
				* @version 1.0
				* @created 08-7��-2018 22:21:47
				*/
				template <csf_attribute_int>
				class csf_attribute_default_value<csf_attribute_int, csf_int32>
				{

				};

				/**
				* ��ʾcsf_attribute_time��ʹ�õ�Ĭ��ֵ���͡�
				* @author Administrator
				* @version 1.0
				* @created 08-7��-2018 22:21:47
				*/
				template <csf_attribute_time>
				class csf_attribute_default_value<csf_attribute_time, csf_int64>
				{

				};

				/**
				* ��ʾcsf_attribute_space_size��ʹ�õ�Ĭ��ֵ���͡�
				* @author Administrator
				* @version 1.0
				* @created 08-7��-2018 22:21:47
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
