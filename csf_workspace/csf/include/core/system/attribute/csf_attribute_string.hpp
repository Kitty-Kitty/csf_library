/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_string.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7��-2018 14:45:30
*
*Description: Class(csf_attribute_string)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_STRING_INCLUDED_)
#define CSF_ATTRIBUTE_STRING_INCLUDED_

#include "csf_attribute_exception.hpp"
#include "csf_attribute_template.hpp"
//#include "csf_null.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * ��ʾ�ַ��������͡�
				 * @author fz
				 * @version 1.0
				 * @created 11-7��-2018 14:45:30
				 */
				class csf_attribute_string : public csf::core::system::attribute::csf_attribute_template<csf_string>
				{

				public:
					inline explicit csf_attribute_string()
						: csf_attribute_template<csf_string>(csf_attribute_type_string, csf_string_null) {
					}

					virtual ~csf_attribute_string() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_string(const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(csf_attribute_type_string, csf_string_null, ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_string(const csf_string& name
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_string(name.c_str(), ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_string(const csf_char* name
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(name, csf_attribute_type_string, csf_string_null, ex) {

					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_string(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(items, csf_attribute_type_string, csf_string_null, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_string(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_string(name.c_str(), items, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_string(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_string>(name, items, csf_attribute_type_string, csf_string_null, ex) {

					}

				protected:
					/**
					 * ��ʾ����csf_attribute���Բ�����������csf_attribute�в�ͬ���ǣ��������һ��process_attribute������Ҫ��Ϊ��ʵ���쳣��e
					 * xception����ͳһ�������쳣����ʱ��ֱ�Ӹ��ݷ��ش��󣬵����쳣��������
					 * ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					 * 
					 * @param configure_manager    ��ʾ�������ù���������
					 * @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					 */
					csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias);

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_STRING_INCLUDED_)
