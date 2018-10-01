/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7��-2018 16:49:58
*
*Description: Class(csf_module_factory_manager)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_FACTORY_MANAGER_INCLUDED_)
#define CSF_MODULE_FACTORY_MANAGER_INCLUDED_


#include "csf_manager.hpp"
#include "csf_module_factory_manager_interface.hpp"
#include "csf_module_factory.hpp"


class csf_module_manager;


namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾģ�鴴������������
			 * @author fz
			 * @version 1.0
			 * @created 01-7��-2018 16:49:58
			 */
			class csf_module_factory_manager : public csf::core::module::csf_manager, public csf::core::module::csf_module_factory_manager_interface
			{

			public:
				inline explicit csf_module_factory_manager()
					: m_module_manager(csf_nullptr) {

				}
				inline virtual ~csf_module_factory_manager() {
					clear();
				}

				/**
				* ����������Ϣ��������������
				*
				* @param configure_manager    ��ʾ������Ϣ
				* @param module_manager    ��ʾģ���ܹ�������ַ
				*/
				inline explicit csf_module_factory_manager(const csf_configure_manager * configure_manager
					, const csf_void* module_manager)

					: csf_manager(configure_manager)
					, m_module_manager((csf_module_manager*)module_manager) {

				}
				/**
				 * ģ���ʼ��
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ģ������
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				 * ģ��ֹͣ
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
				/**
				* ����ģ�������
				* ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				*
				* @param name    ��ʾ��Ҫ������ģ������
				*/
				virtual csf_module * create(const csf_string& name);
				/**
				* ����ģ�������
				* ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				*
				* @param name    ��ʾ��Ҫ������ģ������
				*/
				inline virtual csf_module * create(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return csf_nullptr;
					}

					return create(csf_string(name));
				}
				/**
				 * ����ģ�������
				 * ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				 *
				 * @param type    ��ʾ��Ҫ������ģ������
				 */
				virtual csf_module * create(const csf_module::csf_module_type type);
				/**
				* ����ģ�������
				* ���أ�0��ʾ��ȷ��<0��ʾ�����룻
				*
				* @param module    ��ʾ��Ҫ���ٵ�ģ���ַ
				*/
				virtual csf_int32 destory(const csf_module * module);
				/**
				* ��ʾģ�鹤���Ĵ洢�б�
				*/
				inline csf_unordered_map<csf_string, csf_module_factory*>& get_module_factories() {

					return m_module_factories;
				}
				/**
				* ���ܣ�����ģ�����Ʋ���ģ�鹤��
				*
				* @param name    ģ������
				*/
				csf_module_factory* find(const csf_string& name);
				/**
				* ���ܣ�����ģ�����Ʋ���ģ�鹤��
				*
				* @param name    ģ������
				*/
				inline csf_module_factory* find(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return csf_nullptr;
					}
					return find(csf_string(name));
				}
				/**
				* ���ܣ�����ģ�����Ͳ���ģ�鹤��
				*
				* @param type    ģ������
				*/
				csf_module_factory* find(const csf_module::csf_module_type type);
				/**
				* ���ܣ����ٹ����������е�������Դ����Ҫ���Ѿ�������ģ�鹤���б�
				*/
				csf_void clear();
			protected:
				/**
				* ���ܣ�����ģ������ƴ���һ��ģ�鹤������
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param name    ��ʾģ�������
				*/
				csf_module_factory* create_module_factory(const csf_string& name);
				/**
				* ���ܣ�����ģ������ƴ���һ��ģ�鹤������
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param name    ��ʾģ�������
				*/
				inline csf_module_factory* create_module_factory(const csf_char* name) {

					if (!name || csf_strlen(name) <= 0) {
						return csf_nullptr;
					}

					return create_module_factory(csf_string(name));
				}
				/**
				* ���ܣ�����ģ���������Ϣ����һ��ģ�鹤������
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param module_configure    ��ʾģ���������Ϣ
				*/
				inline csf_module_factory* create_module_factory(const csf_module_configure& module_configure) {

					return  create_module_factory(((csf_module_configure&)module_configure).get_name());
				}
			private:
				/**
				 * ��ʾģ�鹤��������������ģ�������
				 */
				csf_module_manager *m_module_manager = csf_nullptr;
				/**
				* ��ʾģ�鹤���Ĵ洢�б�
				*/
				csf_unordered_map<csf_string, csf_module_factory*> m_module_factories;
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex m_mutex;
				/**
				* ��ʾģ�鹤���Ĵ洢�б�
				*
				* @param new_value
				*/
				inline csf_void set_module_factories(csf_unordered_map<csf_string, csf_module_factory*>& new_value) {

					m_module_factories = new_value;
				}
			};

		}

	}

}
#endif // !defined(CSF_MODULE_FACTORY_MANAGER_INCLUDED_)
