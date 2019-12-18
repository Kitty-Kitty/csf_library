/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_template.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:25
*
*Description: Class(csf_attribute_template)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_TEMPLATE_INCLUDED_)
#define CSF_ATTRIBUTE_TEMPLATE_INCLUDED_

#include "csf_attribute_exception.hpp"
#include "csf_attribute.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/************************************************************************/
				/* ������ֵ���ַ�����Ĭ�ϳ���                                                 */
				/************************************************************************/
				#define csf_attribute_string_default_length				128					// ������ֵ���ַ������Ĭ�ϳ���

				/**
				 * ��ʾ�̶����õ����������
				 * @author fz
				 * @version 1.0
				 * @created 05-7��-2018 20:09:25
				 */
				template <typename ValueType>
				class csf_attribute_template : public csf::core::system::attribute::csf_attribute
				{

				public:
// 					inline explicit csf_attribute_template() {
// 					}
					virtual ~csf_attribute_template() {

					}
// 					inline explicit csf_attribute_template(ValueType val)
// 						: m_value(val) {
// 					}
					/**
					* �������ʹ���һ������
					*
					* @param type    ��ʾ���Ե�����
					* @param ex    ��ʾ�����쳣��������
					*/
					inline explicit csf_attribute_template(const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(type)
						, m_exception(ex)
						, m_value(val){
					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param type    ��ʾ���Ե�����
					* @param ex    ��ʾ�����쳣��������
					*/
					inline explicit csf_attribute_template(const csf_string& name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param type    ��ʾ���Ե�����
					* @param ex    ��ʾ�����쳣��������
					*/
					inline explicit csf_attribute_template(const csf_char* name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param type    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param ex    ��ʾ�����쳣��������
					*/
					inline explicit csf_attribute_template(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(items, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param type    ��ʾ���Ե�����
					* @param ex    ��ʾ�����쳣��������
					*/
					inline explicit csf_attribute_template(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, items, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param type    ��ʾ���Ե�����
					* @param ex    ��ʾ�����쳣��������
					*/
					inline explicit csf_attribute_template(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, ValueType val
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute(name, items, type)
						, m_exception(ex)
						, m_value(val) {
					}
					/**
					 * ��ʾ�쳣����������������
					 */
					inline csf::core::system::attribute::csf_attribute_exception& get_exception() {

						return m_exception;
					}
					/**
					 * ��ʾ�쳣����������������
					 *
					 * @param newVal
					 */
					inline void set_exception(const csf::core::system::attribute::csf_attribute_exception& newVal) {

						m_exception = newVal;
					}
					/**
					 * ��ʾ��ǰ���Ե���ֵ���ݡ�
					 */
					inline ValueType get_value() {

						return m_value;
					}
					/**
					 * ��ʾ��ǰ���Ե���ֵ���ݡ�
					 *
					 * @param newVal    ��ʾ��Ҫ���õ�������ֵ
					 */
					inline void set_value(const ValueType newVal) {

						m_value = newVal;
					}
					/**
					* ��ʾȥ���ַ����еĿհ��ַ���
					* ���أ��ǿձ�ʾ�ɹ����ձ�ʾ�ɹ���
					*
					* @param str    ��ʾ��Ҫ���������ַ���
					*/
					inline const csf_string shrink(const csf_string& str) {

						return shrink(str.c_str());
					}
					/**
					* ��ʾȥ���ַ����еĿհ��ַ���
					* ���أ��ǿձ�ʾ�ɹ����ձ�ʾ�ɹ���
					*
					* @param buf    ��ʾ��Ҫ���������ַ���
					*/
					inline const csf_string shrink(const csf_char* buf) {

						csf_char					tmp_buf[csf_attribute_string_default_length] = { 0, };
						csf_char					*tmp_pos = (csf_char*)buf;
						csf_char					*tmp_dest = tmp_buf;


						if (!buf || csf_strlen(buf) <= 0 ||
							csf_strlen(buf) > csf_attribute_string_default_length) {
							return csf_string_null;
						}

						//�����޷�ʶ����ַ���������ʶ����ַ�
						while (*tmp_pos != '\0') {
							if (csf_char_no_space(*tmp_pos)) {
								*tmp_dest++ = *tmp_pos;
							}

							++tmp_pos;
						}

						return tmp_buf;
					}
					/**
					* �ú���ʵ���쳣���У��������쳣����ʱ�������쳣����ʵ���쳣������
					* ���أ�true��ʾ�쳣�����������ɹ���false��ʾ�쳣����������ʧ�ܡ�
					*/
					inline csf_bool exception_run() {

						return get_exception().run(*this);
					}
					/**
					* ��ʾ����csf_attribute���Բ�����
					* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					*
					* @param configure_manager    ��ʾ�������ù���������
					* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					*/
					inline virtual csf_bool process(const csf_configure_manager& configure_manager, const csf_string& alias) final {

						if (csf_false == process_attribute(configure_manager, alias)) {
							return exception_run();
						}
						else {
							return csf_true;
						}
					}
				protected:
					/**
					* ��ʾ����csf_attribute���Բ�����
					* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					*
					* @param configure_manager    ��ʾ�������ù���������
					* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					*/
					virtual csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) = 0;
				private:
					/**
					 * ��ʾ�쳣����������������
					 */
					csf::core::system::attribute::csf_attribute_exception m_exception;
					/**
					 * ��ʾ��ǰ���Ե���ֵ���ݡ�
					 */
					ValueType m_value;
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_TEMPLATE_INCLUDED_)