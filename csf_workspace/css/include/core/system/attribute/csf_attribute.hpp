/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:26
*
*Description: Class(csf_attribute)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INCLUDED_)
#define CSF_ATTRIBUTE_INCLUDED_

#include <list>
#include "csf_typedef.h"
#include "csf_stdcollector.hpp"
#include "csf_csftype_template.hpp"
#include "csf_configure_manager.hpp"
#include "csf_container_convert.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				//��ʾattribute�ַ�����ʽ�������Ĭ�ϳ���
				#define csf_attribute_string_length					256

				/**
				 * ��ʾ�̶����õ����������
				 * @author fz
				 * @version 1.0
				 * @created 05-7��-2018 20:09:26
				 */
				class csf_attribute : public csf::core::base::csf_csftype_template<csf_attribute>
				{

				public:
					/**
					* ��ʾ�������Ե�����
					* @author Administrator
					* @version 1.0
					* @created 09-7��-2018 15:16:58
					*/
					enum csf_attribute_type
					{
						/**
						* ��ʾδ֪����������
						*/
						csf_attribute_type_none = 0x00000001,
						/**
						* ��ʾ������������
						*/
						csf_attribute_type_bool = 0x00000002,
						/**
						* ��ʾ������������
						*/
						csf_attribute_type_int = 0x00000004,
						/**
						* ��ʾ��������������
						*/
						csf_attribute_type_int64 = 0x00000008,
						/**
						* ��ʾʱ������
						*/
						csf_attribute_type_time = 0x00000010,
						/**
						* ��ʾ�ռ�����
						*/
						csf_attribute_type_space_size = 0x00000020,
						/**
						* ��ʾ�ַ�������
						*/
						csf_attribute_type_string = 0x00000040
					};
					inline explicit csf_attribute()
						: m_name("")
						, m_type(csf_attribute_type_none)
						, m_content("") {
					}
					virtual ~csf_attribute() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param type    ��ʾ���Ե�����
					*/
					inline explicit csf_attribute(const csf_attribute::csf_attribute_type type)
						: m_name("")
						, m_type(type)
						, m_content("") {

					}
					/**
					 * �������ƺ����ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 * @param type    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute(const csf_string& name, const csf_attribute::csf_attribute_type type)
						: csf_attribute(name.c_str(), type) {

					}
					/**
					 * �������ƺ����ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 * @param type    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute(const csf_char* name, const csf_attribute::csf_attribute_type type)
						: m_name(name)
						, m_type(type)
						, m_content("") {

					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param type    ��ʾ���Ե�����
					*/
					inline explicit csf_attribute(const csf_list<csf_string> items, const csf_attribute::csf_attribute_type type)
						: m_name("")
						, m_type(type)
						, m_items(items) {

					}

					/**
					 * �������ơ�����·�������ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 *
					 * @param type    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute(const csf_string& name, const csf_list<csf_string> items, const csf_attribute::csf_attribute_type type)
						: csf_attribute(name.c_str(), items, type) {

					}
					/**
					 * �������ơ�����·�������ʹ���һ������
					 *
					 * @param name    ��ʾ���Ե�����
					 * @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 *
					 * @param type    ��ʾ���Ե�����
					 */
					inline explicit csf_attribute(const csf_char* name, const csf_list<csf_string> items, const csf_attribute::csf_attribute_type type)
						: m_name(name)
						, m_type(type)
						, m_items(items) {

					}
					/**
					 * ��ʾ��������������Ϣ
					 */
					inline csf_attribute_type get_type() {

						return m_type;
					}
					/**
					 * ��ʾ����������Ϣ
					 */
					inline csf_string& get_name() {

						return m_name;
					}
					/**
					 * ��ʾ����������Ϣ
					 *
					 * @param newVal
					 */
					inline void set_name(const csf_string& newVal) {

						m_name = newVal;
					}
					/**
					 * ��ʾ����������Ϣ
					 *
					 * @param newVal
					 */
					inline void set_name(csf_char* newVal) {

						m_name = newVal;
					}
					/**
					 * ��ʾ�ж��Ƿ�Ϊ�ա�
					 * ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
					 */
					inline virtual csf_bool is_null() {

						if (csf_attribute_type_none == get_type()) {
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
					* ��ʾ�����ù������л�ȡ���������ݡ�
					* ���أ�true��ʾ��ȡ��ָ����������ֵ��false��ʾû�л�ȡ����������ֵ��
					*
					* @param configure_manager    ��ʾ�������ù���������
					* @param items    ��ʾ�������·����Ϣ
					*/
					csf_bool get_configure(csf_configure_manager& configure_manager, csf_list<csf_string>& items);

					/**
					* ��ʾ�����ù������л�ȡ���������ݡ�
					* ���أ�true��ʾ��ȡ��ָ����������ֵ��false��ʾû�л�ȡ����������ֵ��
					*
					* @param configure_manager    ��ʾ�������ù���������
					*/
					csf_bool get_configure(csf_configure_manager& configure_manager);
					/**
					* ��ʾ�������ļ��ж�ȡ����ֵ��
					*/
					inline csf_string& get_content() {

						return m_content;
					}

					/**
					* ���������ǽ�csf_attribute������Ϣ��ʽ��
					*/
					inline csf_string to_string() {

						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf),
							"attribute[ type:%d  name:\"%s\"  items:%s  content:\"%s\" ]",
							get_type(),
							get_name().c_str(),
							items_to_string().c_str(),
							get_content().c_str());

						return tmp_buf;
					}
					/**
					* ��ʾ����csf_attribute���Բ�����
					* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					*
					* @param configure_manager    ��ʾ�������ù���������
					* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					*/
					virtual csf_bool process(const csf_configure_manager& configure_manager, const csf_string& alias) {
						return csf_false;
					};
				protected:
					/**
					* ��ʾ��ʼ��csf_attribute��
					* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					*
					* @param configure_manager    ��ʾ�������ù���������
					* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					*/
					csf_bool virtual init(const csf_configure_manager& configure_manager, const csf_string& alias) final;

				private:
					/**
					 * ��ʾ����������Ϣ
					 */
					csf_string m_name = "";
					/**
					 * ��ʾ��������������Ϣ
					 */
					csf_attribute_type m_type = csf_attribute_type_none;
					/**
					 * ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 */
					csf_list<csf_string> m_items;
					/**
					* ��ʾ�������ļ��ж�ȡ����ֵ��
					*/
					csf_string m_content = "";

					/**
					 * ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 */
					inline csf_list<csf_string>& get_items() {

						return m_items;
					}
					/**
					 * ��ʾ����������Ӧ�������ļ��ڵ�λ��
					 *
					 * @param newVal
					 */
					inline void set_items(const csf_list<csf_string>& newVal) {

						m_items = newVal;
					}
					/**
					* ���������ǽ�items�б��е��ַ�����ʽ��Ϊ��"{a, b, c}"��
					*/
					inline csf_string items_to_string() {
						return csf_container_convert<csf_list<csf_string>>(get_items()).to_string();
					}
					/**
					 * ��ʾ��������������Ϣ
					 *
					 * @param newVal
					 */
					inline void set_type(const csf_attribute_type newVal) {

						m_type = newVal;
					}
					/**
					* ��ʾ�������ļ��ж�ȡ����ֵ��
					*
					* @param newVal
					*/
					inline csf_void set_content(const csf_string& newVal) {

						m_content = newVal;
					}
					/**
					* ��ʾ�������ļ��ж�ȡ����ֵ��
					*
					* @param newVal
					*/
					inline csf_void set_content(const csf_char* newVal) {

						m_content = newVal;
					}
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_INCLUDED_)