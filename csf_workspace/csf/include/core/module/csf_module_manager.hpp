/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_manager.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 19:12:21
*
*Description: Class(csf_module_manager)��ʾģ�����������
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_MANAGER_INCLUDED_)
#define CSF_MODULE_MANAGER_INCLUDED_

#include <set>
#include "csf_module_manager_interface.hpp"
#include "csf_manager.hpp"
#include "csf_module_factory_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾģ�����������
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7��-2018 19:12:21
			 */
			class csf_module_manager : public csf::core::module::csf_manager, public csf::core::module::csf_module_manager_interface
			{

			public:
				inline explicit csf_module_manager()
					: m_module_factory_manager(csf_nullptr, this) {

				}

				inline virtual ~csf_module_manager() {
					clear();
				}

				/**
				* ����������Ϣ��������
				*
				* @param conf_mg    ��ʾ��������Ϣ
				*/
				inline explicit csf_module_manager(const csf_configure_manager * configure_manager)
					: csf_manager(configure_manager)
					, m_module_factory_manager(configure_manager, this) {

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
				inline virtual csf_module * create(const csf_string& name) {

					csf_module						*tmp_module = csf_nullptr;


					tmp_module = get_module_factory_manager().create(name);
					if (tmp_module) {
						add(tmp_module);
					}
					return tmp_module;
				}
				/**
				 * ����ģ�������
				 * ���أ�0��ʾ��ȷ��<0��ʾ�����룻
				 *
				 * @param module    ��ʾ��Ҫ���ٵ�ģ���ַ
				 */
				inline virtual csf_int32 destory(const csf_module * module) {

					csf_int32					tmp_int_ret = csf_failure;


					tmp_int_ret = get_module_factory_manager().destory(module);
					if (csf_succeed == tmp_int_ret) {
						del(module);
					}
					return tmp_int_ret;
				}
				/**
				 * ����ģ�������
				 * ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
				 *
				 * @param name    ��ʾ��Ҫ������ģ������
				 */
				inline virtual csf_module * create(const csf_char* name) {

					if (!name || csf_strlen(name)) {
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
				inline virtual csf_module * create(const csf_module::csf_module_type type) {
					csf_module						*tmp_module = csf_nullptr;


					tmp_module = get_module_factory_manager().create(type);
					if (tmp_module) {
						add(tmp_module);
					}
					return tmp_module;
				}
				/**
				* ���ܣ����ģ������б��е�����ģ�����
				*/
				csf_void clear();
			protected:
				/**
				* ģ��������а���һ��ģ�鹤��������
				*/
				inline csf::core::module::csf_module_factory_manager& get_module_factory_manager() {

					return m_module_factory_manager;
				}
				/**
				* ��ʾ���ڱ�������ͨ��ģ�������������ģ�����
				*/
				inline csf_set<csf_module*>& get_modules() {

					return m_modules;
				}
				/**
				* ���ܣ����һ���Ѿ�������ģ�����ģ������б�
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param module    ��ʾģ�����
				*/
				inline csf_bool add(const csf_module* module) {

					csf_unqiue_lock<decltype(m_mutex)>			tmp_lock(m_mutex);

					get_modules().insert((csf_module*)module);

					return csf_true;
				}
				/**
				* ���ܣ���ģ������б���ɾ��ģ�����
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param module    ��ʾģ�����
				*/
				inline csf_bool del(const csf_module* module) {

					csf_set<csf_module*>::iterator				tmp_iter;


					csf_unqiue_lock<decltype(m_mutex)>			tmp_lock(m_mutex);

					tmp_iter = get_modules().find((csf_module*)module);
					if (tmp_iter != get_modules().end()) {
						get_modules().erase(tmp_iter);
					}

					return csf_true;
				}

			private:
				/**
				* ģ��������а���һ��ģ�鹤��������
				*/
				csf::core::module::csf_module_factory_manager m_module_factory_manager;
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex m_mutex;
				/**
				* ��ʾ���ڱ�������ͨ��ģ�������������ģ�����
				*/
				csf_set<csf_module*> m_modules;
			};

		}

	}

}
#endif // !defined(CSF_MODULE_MANAGER_INCLUDED_)
