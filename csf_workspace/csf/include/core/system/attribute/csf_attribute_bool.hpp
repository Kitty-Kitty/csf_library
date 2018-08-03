/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_bool.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:26
*
*Description: Class(csf_attribute_bool)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_BOOL_INCLUDED_)
#define CSF_ATTRIBUTE_BOOL_INCLUDED_

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
				 * ��ʾ�������͵���������
				 * @author fz
				 * @version 1.0
				 * @created 05-7��-2018 20:09:26
				 */
				class csf_attribute_bool : public csf::core::system::attribute::csf_attribute_template<csf_bool>
				{

				public:
					csf_attribute_bool();
					virtual ~csf_attribute_bool();

					/**
					 * �������ƺ����ʹ���һ������
					 * 
					 * @param name    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute_bool(const csf_string& name) 
						: csf_attribute_template<csf_bool>(name, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * �������ƺ����ʹ���һ������
					 * 
					 * @param name    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute_bool(const csf_char* name)
						: csf_attribute_template<csf_bool>(name, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 * 
					 * @param name    ��ʾ���Ե�����
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 * 
					 */
					inline explicit csf_attribute_bool(const csf_string& name, const csf_list<csf_string> items)
						: csf_attribute_template<csf_bool>(name, items, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 * 
					 * @param name    ��ʾ���Ե�����
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 * 
					 */
					inline explicit csf_attribute_bool(const csf_char* name, const csf_list<csf_string> items)
						: csf_attribute_template<csf_bool>(name, items, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 * 
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 * 
					 */
					inline explicit csf_attribute_bool(const csf_list<csf_string> items)
						: csf_attribute_template<csf_bool>(items, csf_attribute::csf_attribute_type_bool, csf_false) {

					}
					/**
					* ���������ǽ�csf_attribute������Ϣ��ʽ��
					*/
					inline csf_string to_string() {
						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf),
							"%s value[%s]",
							csf_attribute::to_string().c_str(),
							value_to_string().c_str());

						return tmp_buf;
					}
					/**
					* �������ܣ���csf_attribute��ֵ���ݸ�ʽ��Ϊ�ַ���
					*/
					inline csf_string value_to_string() {

						return m_value_string[get_value()];
					}
				private:
					/**
					* ��ʾ�����������ݵ��ַ�����ֵ
					*/
					static const csf_string m_value_string[];
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_BOOL_INCLUDED_)
