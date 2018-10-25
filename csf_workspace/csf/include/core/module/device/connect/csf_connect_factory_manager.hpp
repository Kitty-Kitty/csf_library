/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:37
*
*Description: Class(csf_connect_factory_manager) ��ʾ���ӹ���������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
#define CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_

#include "csf_connect.hpp"
#include "csf_connect_factory.hpp"
#include "csf_connect_factory_manager_interface.hpp"
#include "csf_manager.hpp"
#include "csf_app.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * ��ʾ���ӹ���������
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:37
				 */
				class csf_connect_factory_manager : public csf::core::module::csf_manager
					, public csf::core::module::connect::csf_connect_factory_manager_interface
				{

				public:
					inline explicit csf_connect_factory_manager()
						: m_app(csf_nullptr) {

					}

					inline virtual ~csf_connect_factory_manager() {

					}
					/**
					* �������ù���������һ���������
					*
					* @param configure_manager    ��ʾ���ù�������ַ��Ϣ
					*/
					inline explicit csf_connect_factory_manager(const csf_configure_manager* configure_manager)
						: csf_manager(configure_manager)
						, m_app(csf_nullptr) {

					}
					/**
					* �������ù���������һ���������
					*
					* @param configure_manager    ��ʾ���ù�������ַ��Ϣ
					* @param app    ��ʾ��ģ��������app�����ַ
					*/
					inline explicit csf_connect_factory_manager(const csf_configure_manager* configure_manager
						, const csf_app* app)
						: csf_manager(configure_manager)
						, m_app((csf_app*)app) {

					}
					/**
					* ��Ҫ�����ǣ���ʼ��ģ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param conf_mg    ��ʾ�����ļ���Ϣ
					* @param app    ��ʾ��ģ��������app�����ַ
					*/
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg, const csf_app* app);
					/**
					* ��Ҫ�����ǣ�����ģ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param conf_mg    ��ʾ�����ļ���Ϣ
					* @param app    ��ʾ��ģ��������app�����ַ
					*/
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg, const csf_app* app);
					/**
					* ��Ҫ�����ǣ�ֹͣģ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param conf_mg    ��ʾ�����ļ���Ϣ
					*/
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					* ��Ҫ�����ǣ��������е����ӹ��������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param app    ��ʾ������app��Ϣ
					* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
					*/
					csf_bool create_connect_factories(csf_app& app, csf_configure_manager& configure_manager);
					/**
					* ��Ҫ�����ǣ�����һ�����ӹ��������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param app    ��ʾ������app��Ϣ
					* @param element    ��ʾ��ǰ��device�ڵ�����
					*/
					csf_bool create_connect_factory(csf_app& app, csf_element& element);
					/**
					* ��Ҫ�����ǣ������������ӹ�������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param connect_factory    ��ʾ�������ӹ�������
					*/
					csf_bool start_connect_factory(csf_connect_factory* connect_factory);
					/**
					* ��Ҫ�����ǣ����������ӹ��������������������������Ӷ���
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param app    ��ʾ������app��Ϣ
					* @param factory    ��ʾ��ǰ��������ӹ��������
					* @param element    ��ʾ��ǰ��device�ڵ�����
					*/
					csf_bool create_listen_list(csf_app& app, csf_connect_factory& factory, csf_element& element);
					/**
					* ��Ҫ�����ǣ�����һ�����������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ��
					*
					* @param app    ��ʾ������app��Ϣ
					* @param factory    ��ʾ��ǰ��������ӹ��������
					* @param element    ��ʾ��ǰ��device�ڵ�����
					*/
					csf_bool create_listen(csf_app& app, csf_connect_factory& factory, csf_element& element);
					/**
					* ��ʾ��ģ��������app�����ַ
					*/
					inline csf_app* get_app() {

						return m_app;
					}
					/**
					* ��ʾ��ģ��������app�����ַ
					*
					* @param newVal
					*/
					inline void set_app(const csf_app* newVal) {

						m_app = (csf_app*)newVal;
					}
					/**
					* ��ʾ���ӹ�������������Ķ����б�
					*/
					inline csf_unordered_map<csf_string, csf_connect_factory*>& get_factories() {

						return m_factories;
					}
					/**
					* ��ʾͨ�������ļ����������Ӷ��󱣴�Ķ����б�
					*/
					inline csf_unordered_map<csf_string, csf_connect_ptr>& get_connectes() {

						return m_connectes;
					}
					/**
					* ��ʾע����Ҫʹ�õĴ�����
					*/
					inline csf_unordered_map<csf_string, csf_connect_callback>& get_handles() {

						return m_handles;
					}
					/**
					* ��Ҫ�����ǣ������ӹ����б������һ�����ӹ��������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*
					* @param name    ��ʾ���ӹ������������
					* @param factory    ��ʾ���ӹ��������ָ��
					*/
					inline csf_bool add_factory(csf_string name, csf_connect_factory* factory) {

						get_factories()[name] = factory;

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ��������ƴ����ӹ����б��в���һ�����ӹ��������
					* ���أ���null��ʾ�ɹ���null��ʾʧ�ܣ�
					*
					* @param name    ��ʾ���ӹ������������
					*/
					inline csf_connect_factory* find_factory(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_factory*>::iterator tmp_iter;


						tmp_iter = get_factories().find(name);
						if (tmp_iter == get_factories().end()) {
							return csf_nullptr;
						}
						else {
							return tmp_iter->second;
						}
						return  csf_nullptr;
					}
					/**
					* ��Ҫ�����ǣ��������ƴ����ӹ����б���ɾ��һ�����ӹ��������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*
					* @param name    ��ʾ���ӹ������������
					*/
					inline csf_bool remove_factory(csf_string name) {

						csf_connect_factory			*tmp_factory = csf_nullptr;
						csf_unordered_map<csf_string, csf_connect_factory*>::iterator tmp_iter;


						tmp_iter = get_factories().find(name);
						if (tmp_iter == get_factories().end()) {
							return csf_false;
						}
						else {
							tmp_factory = tmp_iter->second;
							get_factories().erase(tmp_iter);
							get_app()->get_module_manager().destory(tmp_factory);
						}
							
						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ������ӹ����б���ɾ���������ӹ��������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*/
					inline csf_bool clear_factory() {

						for (auto tmp_iter : get_factories()) {
							if (csf_nullptr != tmp_iter.second) {
								get_app()->get_module_manager().destory(tmp_iter.second);
							}
						}

						get_factories().clear();

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ�����һ�����������
					* ���أ���m_null_connect_ptr��ʾ�ɹ���m_null_connect_ptr��ʾʧ��
					*
					* @param factory    ��ʾ��ǰ��������ӹ��������
					* @param element    ��ʾ��Ҫ���������Ӷ���������Ϣ
					*/
					csf_connect_ptr create_connect(csf_connect_factory& factory, csf_element& element);
					/**
					* ��Ҫ�����ǣ���ʾ����һ�����������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܴ�����
					*
					* @param connect    ��ʾ��ǰ��������ӹ��������
					* @param handle    ��ʾ���Ӷ���Ļص����
					* @param element    ��ʾ��Ҫ���������Ӷ���������Ϣ
					*/
					csf::core::base::csf_int32 listen_connect(csf_connect_ptr& connect
						, csf_connect_callback handle
						, csf_element& element);
					/**
					* ��Ҫ�����ǣ��������б������һ�����������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*
					* @param name    ��ʾ�������������
					* @param connect_ptr    ��ʾ���������ָ��
					*/
					inline csf_bool add_connect(csf_string name, csf_connect_ptr connect_ptr) {

						get_connectes()[name] = connect_ptr;

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ��������ƴ������б��в���һ�����������
					* ���أ���null��ʾ�ɹ���null��ʾʧ�ܣ�
					*
					* @param name    ��ʾ�������������
					*/
					inline csf_connect_ptr find_connect(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_ptr>::iterator tmp_iter;


						tmp_iter = get_connectes().find(name);
						if (tmp_iter == get_connectes().end()) {
							return m_null_connect_ptr;
						}
						else {
							return tmp_iter->second;
						}
						return m_null_connect_ptr;
					}
					/**
					* ��Ҫ�����ǣ��������ƴ������б���ɾ��һ�����������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*
					* @param name    ��ʾ�������������
					*/
					inline csf_bool remove_connect(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_ptr>::iterator tmp_iter;


						tmp_iter = get_connectes().find(name);
						if (tmp_iter == get_connectes().end()) {
							return csf_false;
						}
						else {
							get_connectes().erase(tmp_iter);
						}

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ��������б���ɾ���������������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*/
					inline csf_bool clear_connect() {

						get_connectes().clear();

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ������б������һ�����
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*
					* @param name    ��ʾ�������
					* @param handle    ��ʾ���ָ��
					*/
					inline csf_bool add_handle(csf_string name, csf_connect_callback handle) {

						get_handles()[name] = handle;

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ��������ƴӾ���б��в���һ�����
					* ���أ���null��ʾ�ɹ���null��ʾʧ�ܣ�
					*
					* @param name    ��ʾ�������
					*/
					inline csf_connect_callback find_handle(csf_string name) {


						csf_unordered_map<csf_string, csf_connect_callback>::iterator tmp_iter;


						tmp_iter = get_handles().find(name);
						if (tmp_iter == get_handles().end()) {
							return csf_nullptr;
						}
						else {
							return tmp_iter->second;
						}

						return  csf_nullptr;
					}
					/**
					* ��Ҫ�����ǣ��������ƴӾ���б���ɾ��һ�����
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*
					* @param name    ��ʾ�������
					*/
					inline csf_bool remove_handle(csf_string name) {

						csf_unordered_map<csf_string, csf_connect_callback>::iterator tmp_iter;


						tmp_iter = get_handles().find(name);
						if (tmp_iter == get_handles().end()) {
							return csf_false;
						}
						else {
							get_handles().erase(tmp_iter);
						}

						return csf_true;
					}
					/**
					* ��Ҫ�����ǣ��Ӿ���б���ɾ�����о��
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
					*/
					inline csf_bool clear_handle() {

						get_handles().clear();

						return csf_true;
					}
				private:
					/**
					* ��ʾ��ģ��������app�����ַ
					*/
					csf_app* m_app = csf_nullptr;
					/**
					* ��ʾ���ӹ�������������Ķ����б�
					*/
					csf_unordered_map<csf_string, csf_connect_factory*> m_factories;
					/**
					* ��ʾͨ�������ļ����������Ӷ��󱣴�Ķ����б�
					*/
					csf_unordered_map<csf_string, csf_connect_ptr> m_connectes;
					/**
					* ��ʾע����Ҫʹ�õĴ�����
					*/
					csf_unordered_map<csf_string, csf_connect_callback> m_handles;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_FACTORY_MANAGER_H_INCLUDED_)
