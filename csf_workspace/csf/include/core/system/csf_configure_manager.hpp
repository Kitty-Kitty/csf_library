/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7��-2018 17:41:45
*
*Description: Class(csf_configure_manager)��ʾϵͳ�������õĹ�����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONFIGURE_MANAGER_INCLUDED_)
#define CSF_CONFIGURE_MANAGER_INCLUDED_

#include "csf_measure_configure.hpp"
#include "csf_module_configure.hpp"
#include "csf_configure.hpp"

using namespace csf::core::module;

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			* ��ʾģ�������ļ��ַ�������
			*/
			#define CSF_CONFIGURE_STRING(str)									#str
			/**
			 * ��ʾϵͳ�������õĹ�����
			 * @author fz
			 * @version 1.0
			 * @created 01-7��-2018 17:41:45
			 */
			class csf_configure_manager
			{

			public:
				csf_configure_manager();
				virtual ~csf_configure_manager();
				/**
				* ���ܣ���ʼ�����ù������е�����������Ϣ����Ҫָģ��������Ϣ������������Ϣ��������
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
				*/
				csf_bool init();
				/**
				 * ���һ��csf_configure��configure_manager�С�����configure_manager����ӵ�ʱ����Ҫ����name���жϸ������ļ��Ƿ�
				 * �Ѿ���configure_manager�С�
				 * ���з���0��ʾ�ɹ���������ʾʧ�ܡ�
				 *
				 * @param configure    ��ʾ��Ҫ����ӵ�csf_configure����
				 */
				inline csf_int32 add(const csf_configure& configure) {

					if (((csf_configure&)configure).get_configure_file().get_name().empty()) {
						return csf_failure;
					}

					//��csf_configure��ӵ��б���
					m_configures[((csf_configure&)configure).get_configure_file().get_name()] = configure;
					return csf_success;
				}
				/**
				 * ���һ��csf_configure_file��configure_manager�С�����configure_manager������configure_fileδ��
				 * �����ļ����������csf_configure_file��Ҫ�ȴ���һ��csf_configure�������ӵ�configure_manager�С�
				 * ���з���0��ʾ�ɹ���������ʾʧ�ܡ�
				 *
				 * @param configure_file    ��ʾ��Ҫ����ӵ�csf_configure_file����
				 */
				inline csf_int32 add(const csf_configure_file& configure_file) {

					if (((csf_configure_file&)configure_file).get_name().empty()) {
						return csf_failure;
					}

					return add(csf_configure((csf_configure_file&)configure_file));
				}
				/**
				 * ��ʾ��configure_manager��ɾ��һ��csf_configure�������ɾ����Ҫ�Ǹ��������ļ�������name����ɾ����
				 * ���з���0��ʾ�ɹ���������ʾʧ�ܡ�
				 *
				 * @param configure    ��ʾ��Ҫ��ɾ����csf_configure����
				 */
				inline csf_int32 del(const csf_configure& configure) {

					return del(((csf_configure&)configure).get_configure_file());
				}
				/**
				 * ��configure_manager��ɾ��csf_configure_fileָ���������ļ��������ɾ����Ҫ�Ǹ��������ļ�������name����ɾ����
				 *
				 * ���з���0��ʾ�ɹ���������ʾʧ�ܡ�
				 *
				 * @param configure_file    ��ʾ��Ҫ��ɾ��һ��csf_configure_file����ָ���������ļ���
				 */
				inline csf_int32 del(const csf_configure_file& configure_file) {

					if (((csf_configure_file&)configure_file).get_name().empty()) {
						return csf_failure;
					}

					//��ʾ����configure����ɾ�������ļ���Ϣ
					get_configures().erase(((csf_configure_file&)configure_file).get_name());
					return csf_success;
				}
				/**
				* ��ʾ����items����·������һ��element��
				* ���أ���null��ʾ����items����·���Ľڵ㣻null��ʾû�в��ҵ�����·���Ľڵ㣻
				*
				* @param items    items����·��
				*/
				virtual const csf_element& find_element(const csf_list<csf_string>& items);
				/**
				* ��ʾϵͳ����������Ŀ����
				*/
				inline csf::core::system::csf_measure_configure& get_measure_configure() {

					return m_measure_configure;
				}
				/**
				* ��ʾϵͳ����������Ŀ����
				*
				* @param new_value
				*/
				inline void set_measure_configure(csf::core::system::csf_measure_configure& new_value) {

					m_measure_configure = new_value;
				}
				/**
				* ���ܣ�����ģ�����Ʋ�ѯģ��������Ϣ
				* ���أ��ǿն����ʾ�ɹ����Ƕ����ʾʧ�ܣ�
				*
				* @param name    ��ʾģ�������
				*/
				const csf_module_configure& find_module_configure(const csf_string& name);
				/**
				* ���ܣ�����ģ�����Ʋ�ѯģ��������Ϣ
				* ���أ��ǿն����ʾ�ɹ����Ƕ����ʾʧ�ܣ�
				*
				* @param name    ��ʾģ�������
				*/
				inline const csf_module_configure& find_module_configure(const csf_char* name) {

					if (!name || csf_strlen(name)) {
						return csf_module_configure::get_null();
					}
					return find_module_configure(csf_string(name));
				}

			protected:
				/**
				* ���ܣ���ʼ��ģ�����ù�����
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
				*
				* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
				* @param configures    ��ʾ��ǰ�Ѿ������������ļ���Ϣ
				*/
				csf_bool init_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
					, csf_map<csf_string, csf_configure>& configures);
				/**
				* ���ܣ���ʼ���������ù�����
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
				*
				* @param measure_configure    ��ʾ����󱣴������ģ��������Ϣ
				* @param configures    ��ʾ��ǰ�Ѿ������������ļ���Ϣ
				*/
				csf_bool init_measure_configure(csf_measure_configure& measure_configure
					, csf_map<csf_string, csf_configure>& configures);
				/**
				* ���ܣ���ģ�����ù����������һ��ģ��������Ϣ��ͬʱ������Ϣ�µ�������ģ����Ϣ
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
				*
				* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
				* @param module_element    ��ʾ��ǰ��ȡ����ģ����Ϣ
				*/
				csf_bool add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures, const csf_element& module_element);
				/**
				* ���ܣ���ģ�����ù����������һ��ģ��������Ϣ
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
				*
				* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
				* @param module_element    ��ʾ��ǰ��ȡ����ģ����Ϣ
				*/
				csf_bool add_module_configure(csf_map<csf_string, csf_module_configure>& module_configures, const csf_element& module_element);
				/**
				* ���ܣ���ģ�����ù����������һ��ģ��������Ϣ��ͬʱ������Ϣ�µ�������ģ����Ϣ
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
				*
				* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
				* @param items    ��ʾ��ǰģ����Ϣ·��
				*/
				csf_bool add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures, const csf_list<csf_string>& items);
				/**
				* ��ʾ�����ļ���Ϣ�б�
				*/
				inline csf_map<csf_string, csf_configure>& get_configures() {

					return m_configures;
				}
				/**
				* ��ʾ�����ļ���Ϣ�б�
				*
				* @param new_value
				*/
				inline csf_void set_configures(csf_map<csf_string, csf_configure>& new_value) {

					m_configures = new_value;
				}
				/**
				* ��ʾģ�����ù�����
				*/
				inline csf_map<csf_string, csf_module_configure>& get_module_configures() {

					return m_module_configures;
				}
				/**
				* ��ʾģ�����ù�����
				*
				* @param new_value
				*/
				inline csf_void set_module_configures(csf_map<csf_string, csf_module_configure>& new_value) {

					m_module_configures = new_value;
				}
			private:
				/**
				 * ��ʾ�����ļ���Ϣ�б�
				 */
				csf_map<csf_string, csf_configure> m_configures;
				/**
				 * ��ʾģ�����ù�����
				 */
				csf_map<csf_string, csf_module_configure> m_module_configures;
				/**
				 * ��ʾ��������������Ϣ
				 */
				csf::core::system::csf_measure_configure m_measure_configure;
			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_MANAGER_INCLUDED_)
