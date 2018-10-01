/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7��-2018 13:21:34
*
*Description: Class(csf_configure)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONFIGURE_INCLUDED_)
#define CSF_CONFIGURE_INCLUDED_

#include "csf_configure_interface.hpp"
#include "csf_configure_parser.hpp"
#include "csf_csftype_template.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * �������������ļ���������Ϣ
			 * @author fz
			 * @version 1.0
			 * @created 01-7��-2018 13:21:34
			 */
			class csf_configure : public csf::core::system::csf_configure_interface, public csf::core::base::csf_csftype_template<csf_configure>
			{

			public:
				inline explicit csf_configure() {

				}
				/**
				 * ����configure_file���ݴ���һ��csf_cofigure�������
				 * 
				 * @param configure_file    ��Ҫ������configureΪconfigure_file�������ĵ�����
				 */
				inline explicit csf_configure(csf_configure_file& configure_file) {
					if (csf_failure == set_configure_file(configure_file)) {
						throw csf_nullptr;
					}
				}
				inline virtual ~csf_configure() {

				}
				/**
				 * ��ʾ�����ļ�ת�����csf_element����
				 */
				inline csf_element& get_element() {

					return m_element;
				}
				/**
				 * ָ���������ļ���Ϣ
				 */
				inline csf_configure_file& get_configure_file() {

					return m_configure_file;
				}
				/**
				 * ָ���������ļ���Ϣ��������Ҫ�����õ������ļ����н������� �����ɹ�����0����������Ϊ����
				 * 
				 * @param new_value    new_value
				 */
				inline csf_int32 set_configure_file(csf_configure_file& new_value) {

					csf_configure_parser				tmp_config_parse;


					//����configure_file���ļ�����
					if (csf_failure == tmp_config_parse.parse(get_element(), new_value)) {
						return csf_failure;
					}

					m_configure_file = new_value;
					return csf_success;
				}
				/**
				* ��ʾ����items����·������һ��element��
				* ���أ���null��ʾ����items����·���Ľڵ㣻null��ʾû�в��ҵ�����·���Ľڵ㣻
				*
				* @param items    items����·��
				*/
				inline virtual const csf_element& find_element(const csf_list<csf_string>& items) {

					return  get_element().find_element(items);
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline virtual csf_bool is_null() {

					return get_element().is_null();
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				*/
				inline virtual csf_bool not_null() {

					return !is_null();
				}
			private:
				/**
				 * ָ���������ļ���Ϣ
				 */
				csf::core::system::csf_configure_file m_configure_file;
				/**
				 * ��ʾ�����ļ�ת�����csf_element����
				 */
				csf::core::system::csf_element m_element;

				/**
				 * ��ʾ�����ļ�ת�����csf_element����
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_element(csf_element& new_value) {

					m_element = new_value;
				}

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_INCLUDED_)
