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
*Date: 08-7��-2018 22:21:47
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
				* ��ʾ�쳣����δ��ȡ����ֵʱ������Ĭ�ϵ���ֵ���档
				* @author Administrator
				* @version 1.0
				* @updated 08-7��-2018 22:25:17
				*/
				template <typename ValueType>
				class csf_attribute_default_value_template : public csf::core::system::attribute::csf_attribute_exception_warning
				{

				public:
					csf_attribute_default_value_template(ValueType val, const csf::core::system::attribute::csf_attribute_exception_callback callback)
						: csf_attribute_exception(callback)
						, m_value(val) {

					}
					virtual ~csf_attribute_default_value_template() {

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
					* @param newVal    ��ʾĬ�ϵ���ֵ
					*/
					inline csf_void set_value(const ValueType& newVal) {

						m_value = newVal;
					}

				private:
					/**
					* ��ʾĬ�ϵ���ֵ����
					*/
					ValueType m_value;
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_DEFAULT_VALUE_TEMPLATE_INCLUDED_)