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
*Date: 06-7��-2018 17:15:59
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
			 * ��Ҫ���ڹ���csf_csftype��ģ�����͡���ģ����Ҫ���ڴ���һ���ն�����ΪΪ�յķ���ֵ���Լ���ָ���ʹ�á�
			 * @author f
			 * @version 1.0
			 * @created 06-7��-2018 17:15:59
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
				* ��ʾ�����һ���ն���,��Ϊ���������ݵ�Ĭ�Ͽ�ֵ��Ϊ����ָ���ʹ�ã������жϿ��ṩĬ��ֵ��
				*/
				csf_csftype_template& operator = (const csf_csftype_template& new_value) const {
					return (csf_csftype_template&)*this;
				}

				/**
				 * ��ʾ�ж��Ƿ�Ϊ�ա�
				 * ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				 */
				inline virtual csf_bool is_null() {

					return csf_true;
				}
				/**
				 * ��ʾ�ж��Ƿ�Ϊ�ա�
				 * ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				 */
				inline virtual csf_bool not_null() {

					return csf_true;
				}
				/**
				 * ��ʾ�����һ���ն���
				 */
				inline static const TypeName& get_null() {

					return m_null;
				}

			protected:
				/**
				 * ��ʾ�����һ���ն���
				 * 
				 * @param new_value
				 */
				inline csf_void set_null(const TypeName& new_value) {

					m_null = new_value;
				}

			private:
				/**
				 * ��ʾ�����һ���ն���,��Ϊ���������ݵ�Ĭ�Ͽ�ֵ��Ϊ����ָ���ʹ�ã������жϿ��ṩĬ��ֵ��
				 */
				static const TypeName m_null;				
			};

			//����Ծ�̬null����ĳ�ʼ������
			template<typename TypeName> const TypeName csf_csftype_template<TypeName>::m_null;
		}

	}

}
#endif // !defined(CSF_CSFTYPE_TEMPLATE_INCLUDED_)
