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
*Date: 05-7��-2018 20:09:26
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
				//��ʾ�쳣����ص�����
				typedef csf_function<csf_void(csf_attribute&)>	csf_attribute_exception_callback;

				//��ʾattribute exception�ַ�����ʽ�������Ĭ�ϳ���
				#define csf_attribute_exception_string_length					256

				/**
				 * ��ʾ���Խ����쳣�Ĵ���ʽ
				 * @author Administrator
				 * @version 1.0
				 * @created 05-7��-2018 20:09:26
				 */
				class csf_attribute_exception : public csf::core::base::csf_csftype_template<csf_attribute_exception>
				{

				public:
					inline explicit csf_attribute_exception()
						: m_callback(csf_nullptr) {

					}
					/**
					*
					* @param callback    ��ʾ�쳣�ص�����
					*
					*/
					inline explicit csf_attribute_exception(const csf::core::system::attribute::csf_attribute_exception_callback callback) 
						: m_callback(callback) {
					}
					virtual ~csf_attribute_exception() {

					}

					/**
					* ��ʾ�쳣�ص�����
					*/
					inline csf::core::system::attribute::csf_attribute_exception_callback& get_callback() {

						return m_callback;
					}
					/**
					* ��ʾ�쳣�ص�����
					*
					* @param newVal
					*/
					inline void set_callback(const csf::core::system::attribute::csf_attribute_exception_callback& newVal) {

						m_callback = newVal;
					}
					/**
					* ��ʾ�ж��Ƿ�Ϊ�ա�
					* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
					*/
					inline virtual csf_bool is_null() {

						if (csf_nullptr == get_callback()) {
							return csf_true;
						}
						return csf_false;
					}
					/**
					* ��ʾ�ж��Ƿ�Ϊ�ա�
					* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
					*/
					inline virtual csf_bool not_null() {

						return !is_null();
					}

					/**
					* ��ʾִ���쳣���������
					* ���أ�true��ʾִ�гɹ���false��ʾִ��ʧ�ܡ�
					*
					* @param attribute    ��ʾ��Ҫ����������Զ���
					*/
					inline csf_bool run(const csf_attribute& attribute) {

						//����ص�������Ϊ�գ����ʾ�������лص�����
						if (is_null()) {
							return csf_false;
						}
						else {
							get_callback()((csf_attribute&)attribute);
						}

						return csf_true;
					}
					/**
					* ��ʾ�쳣��Ĭ�ϴ������
					*/
					inline static const csf_attribute_exception& get_default() {

						return m_default;
					}
				private:
					/**
					 * ��ʾ�쳣�ص�����
					 */
					csf::core::system::attribute::csf_attribute_exception_callback m_callback = csf_nullptr;
					/**
					* ��ʾ�쳣��Ĭ�ϴ������
					*/
					static const csf_attribute_exception m_default;
				};
			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_EXCEPTION_INCLUDED_)
