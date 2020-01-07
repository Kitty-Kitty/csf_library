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
					inline explicit csf_attribute_bool(const csf_string& name
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
						: csf_attribute_template<csf_bool>(name, csf_attribute::csf_attribute_type_bool, csf_false, ex) {

					}
					/**
					 * �������ƺ����ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute_bool(const csf_char* name
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
						: csf_attribute_template<csf_bool>(name, csf_attribute::csf_attribute_type_bool, csf_false, ex) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 *
					 */
					inline explicit csf_attribute_bool(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
						: csf_attribute_template<csf_bool>(name, items, csf_attribute::csf_attribute_type_bool, csf_false, ex) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 *
					 */
					inline explicit csf_attribute_bool(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
						: csf_attribute_template<csf_bool>(name, items, csf_attribute::csf_attribute_type_bool, csf_false, ex) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 *
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 *
					 */
					inline explicit csf_attribute_bool(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
						: csf_attribute_template<csf_bool>(items, csf_attribute::csf_attribute_type_bool, csf_false, ex) {

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

						if (get_value()) {
							return get_true_string();
						}
						else {
							return get_false_string();
						}
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
					virtual csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias);
					/**
					* ��ʾ����csf_attribute���Բ�����������csf_attribute�в�ͬ���ǣ��������һ��process_attribute������Ҫ��Ϊ��ʵ���쳣��e
					* xception����ͳһ�������쳣����ʱ��ֱ�Ӹ��ݷ��ش��󣬵����쳣��������
					* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					*
					* @param element    ��ʾ�������ö���
					* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					*/
					inline virtual csf_bool process_attribute(const csf_element& element, const csf_string& alias) final {
						return process_attribute(csf_configure_manager(), alias);
					}
				private:
					/**
					* ��ʾ����Ϊ���������ݵ��ַ�����ֵ
					*/
					inline csf_string get_false_string() {
						return m_false_string;
					}
					/**
					* ��ʾ����Ϊ���������ݵ��ַ�����ֵ
					*/
					inline csf_string get_true_string() {
						return m_true_string;
					}
				private:
					/**
					* ��ʾ����Ϊ���������ݵ��ַ�����ֵ
					*/
					static const csf_string m_true_string;
					/**
					* ��ʾ����Ϊ���������ݵ��ַ�����ֵ
					*/
					static const csf_string m_false_string;

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_BOOL_INCLUDED_)
