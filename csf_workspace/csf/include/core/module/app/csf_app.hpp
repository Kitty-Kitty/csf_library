/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_app.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 17:33:42
*
*Description: Class(csf_app)��ʾӦ�ó���ĵĳ���ģ��app����һ��app��ʾһ��Ӧ�ó���
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_APP_INCLUDED_)
#define CSF_APP_INCLUDED_

#include "csf_time.hpp"
#include "csf_module_manager.hpp"
#include "csf_vm.hpp"
#include "csf_app_interface.hpp"
#include "csf_logger.hpp"
#include "csf_device_base.hpp"
#include "csf_root_configure.hpp"
#include "csf_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			* ��ʾ��ǰapp�ĸ������ļ��ı���
			*/
			#define CSF_APP_ROOT_CONFIGURE_FILE_NAME_STRING				"_root_configure_file_"

			/**
			 * ��ʾӦ�ó���ĵĳ���ģ��app����һ��app��ʾһ��Ӧ�ó���
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7��-2018 17:33:42
			 */
			class csf_app : public csf::core::module::csf_device_base, public csf::core::module::csf_app_interface
			{

			public:
				/**
				* ��ʾappģ�������
				* @author f
				* @version 1.0
				* @created 12-7��-2018 16:38:04
				*/
				enum csf_app_type
				{
					/**
					* ��ʾδ֪��app����
					*/
					csf_app_type_none = csf_module_type_app | 0x00000000,
					/**
					* ��ʾͨ��app����չ�������ڵ�������չ��
					*/
					csf_app_type_general_extend = csf_app_type_none | 0x00010000
				};

				inline explicit csf_app()
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg) {

				}

				inline virtual ~csf_app() {

				}

				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				*/
				inline explicit csf_app(const csf_configure_manager * configure_manager)
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg) {

				}
				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				* @param type    ��ʾģ�������
				*/
				inline explicit csf_app(const csf_configure_manager * configure_manager, const csf_module::csf_module_type type)
					: csf_device_base(&m_config_mg, type)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg) {

				}
				/**
				* ���ݸ������ļ���Ϣ����һ��app
				*
				* @param root_configure_file    ��ʾ��ǰapp�������ļ���Ϣ
				*/
				inline explicit csf_app(csf_configure_file& root_configure_file)
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg)
					, m_root_configure_file(root_configure_file) {

				}
				/**
				* ���ݸ������ļ���Ϣ����һ��app
				*
				* @param path    ��ʾ��ǰapp�������ļ����ļ�·��
				* @param format    ��ʾ�������ļ����ļ���ʽ
				*/
				inline explicit csf_app(const csf_char* path, const csf_char* format)
					: csf_device_base(&m_config_mg, csf_module_type_app)
					, m_work_directory("")
					, m_logger(&m_config_mg, "")
					, m_module_manager(&m_config_mg)
					, m_root_configure_file(CSF_APP_ROOT_CONFIGURE_FILE_NAME_STRING, path, format) {

				}
				/**
				* ���ݸ������ļ���Ϣ����һ��app
				*
				* @param path    ��ʾ��ǰapp�������ļ����ļ�·��
				* @param format    ��ʾ�������ļ����ļ���ʽ
				*/
				inline explicit csf_app(csf_string& path, csf_string& format)
					: csf_app(path.c_str(), format.c_str()) {

				}

				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback) {

					return 0;
				}
				/**
				* ģ���ʼ��
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr);
				/**
				* ģ������
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr);
				/**
				* ģ��ֹͣ
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr);
				/**
				* ��ʾ��־ϵͳ
				*/
				inline csf_logger& get_logger() {

					return m_logger;
				}
				/**
				* ��ʾapp����ά�ֵ�ʱ��
				*/
				inline csf::core::base::csf_time get_app_time() {

					return m_app_time;
				}
				/**
				* ��ʾ��ʱ��ȡ��ϵͳʱ��
				*/
				inline csf::core::base::csf_time get_system_time() {

					return m_system_time;
				}
				/**
				* ��ʾapp������ʱ��
				*/
				inline csf::core::base::csf_time get_start_time() {

					return m_start_time;
				}
				/**
				* ��ʾ��ǰ�Ĺ���Ŀ¼��ַ
				*/
				inline csf_string& get_work_directory() {

					return m_work_directory;
				}
				/**
				* ��ʾϵͳapp��ӵ�е�device�б�����device������app��������app����Դ��
				*/
				inline csf_unordered_map<csf_string, csf_device*>& get_devices() {

					return m_devices;
				}
				/**
				* ��ʾϵͳ�ܵ����ù�������һ��ϵͳ��������һ�������ù�����
				*/
				inline csf::core::system::csf_configure_manager& get_config_mg() {

					return m_config_mg;
				}
				/**
				* ��ʾapp�ĸ������ļ���Ϣ����Ҫ����app�ĸ��������ļ���Ϣ��
				*/
				inline csf_configure_file& get_root_configure_file() {

					return m_root_configure_file;
				}
				/**
				* ��ʾģ�鹤��������
				*/
				inline csf::core::module::csf_module_manager& get_module_manager() {

					return m_module_manager;
				}
				/**
				* ���ܣ������豸���Ʋ�ѯָ���豸��ַ
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸����
				*/
				csf_device* find_device(const csf_string& mid);
				/**
				* ���ܣ������豸���Ʋ�ѯָ���豸��ַ
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸����
				*/
				inline csf_device* find_device(const char* mid) {

					if (!mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return  find_device(csf_string(mid));
				}
				/**
				* ���ܣ������豸�������ָ���豸��ַ���豸�б���
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸����
				* @param device
				*/
				csf_bool add_device(const csf_string& mid, const csf_device* device);
				/**
				* ���ܣ������豸�������ָ���豸��ַ���豸�б���
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸����
				* @param device
				*/
				inline csf_bool add_device(const csf_char* mid, const csf_device* device) {

					if (!device || !mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return  add_device(csf_string(mid), device);
				}
				/**
				* ���ܣ������豸����ɾ��ָ���豸��ַ
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸����
				*/
				csf_bool del_device(const csf_string& mid);
				/**
				* ���ܣ������豸����ɾ��ָ���豸��ַ
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸����
				*/
				inline csf_bool del_device(const csf_char* mid) {

					if (!mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return del_device(csf_string(mid));
				}
				/**
				* ��Ҫ�����ǣ���ģ����Ϣ��ʽ�����ַ������
				* ���أ�ģ����Ϣ�ַ���
				*/
				inline virtual csf_string to_string() {

					return "";
				}
			protected:
				/**
				* ��ʾapp����ά�ֵ�ʱ��
				*
				* @param new_value
				*/
				inline void set_app_time(csf::core::base::csf_time new_value) {

					m_app_time = new_value;
				}
				/**
				* ��ʾ��ʱ��ȡ��ϵͳʱ��
				*
				* @param new_value
				*/
				inline void set_system_time(csf::core::base::csf_time new_value) {

					m_system_time = new_value;
				}
				/**
				* ��ʾapp������ʱ��
				*
				* @param new_value
				*/
				inline void set_start_time(csf::core::base::csf_time new_value) {

					m_start_time = new_value;
				}
				/**
				* ��ʾ��ǰ�Ĺ���Ŀ¼��ַ
				*
				* @param new_value
				*/
				inline void set_work_directory(csf_string& new_value) {

					m_work_directory = new_value;
				}
				/**
				* ��ʾϵͳapp��ӵ�е�device�б�����device������app��������app����Դ��
				*
				* @param new_value
				*/
				inline void set_devices(csf_unordered_map<csf_string, csf_device*>& new_value) {

					m_devices = new_value;
				}
				/**
				* ��ʾϵͳ�ܵ����ù�������һ��ϵͳ��������һ�������ù�����
				*
				* @param new_value
				*/
				inline void set_config_mg(const csf::core::system::csf_configure_manager& new_value) {

					m_config_mg = new_value;
				}
				/**
				* �ú�����Ҫ���ڳ�ʼ��app�������ļ�����ȡ�����ļ��б����������Ϣ��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				* @param root_configure_file    ��ʾ��ǰapp�������ļ���Ϣ
				*/
				inline csf_bool init_configure_manager(csf::core::system::csf_configure_manager& configure_manager,
					csf_configure_file& root_configure_file) {

					if (!csf_root_configure().init_configure_manager(configure_manager, root_configure_file)) {
						csf_log_ex(critical, csf_log_code_critical, "init configure manager failed!");
						return csf_false;
					}
					else {
						csf_log_ex(notice, csf_log_code_notice, "init configure manager succeed!");
						return csf_true;
					}

					return csf_false;
				}
				/**
				* ��ʾapp�ĸ������ļ���Ϣ����Ҫ����app�ĸ��������ļ���Ϣ��
				*
				* @param new_value
				*/
				inline csf_void set_root_configure_file(csf_configure_file& new_value) {

					m_root_configure_file = new_value;
				}
				/**
				* �ú�����Ҫ���ڳ�ʼ��app����־ϵͳ��
				* ���أ�true��ʾ��ʼ����־ϵͳ�ɹ���false��ʾ��ʼ����־ϵͳʧ�ܡ�
				*
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				* @param work_directory    ��ʾ����Ĭ�ϵĹ�����Ŀ¼��ַ
				*/
				csf_bool init_logger(csf::core::system::csf_configure_manager& configure_manager, csf_string work_directory = "");
				/**
				* �ú�����Ҫ���ڳ�ʼ��app��ģ�������
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ�ܡ�
				*
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool init_module_manager(csf::core::system::csf_configure_manager& configure_manager);
				/**
				* ���ܣ��ú�����Ҫ���ڳ�ʼ��app��������������ģ��
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ�ܡ�
				*
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool init_bootloader(csf::core::system::csf_configure_manager& configure_manager);
				/**
				* ���ܣ��ú�����Ҫ���ڳ�ʼ��app�ĵ�ǰ����Ŀ¼
				* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ�ܡ�
				*
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool init_work_directory(csf::core::system::csf_configure_manager& configure_manager);

			private:
				/**
				 * ��ʾapp������ʱ��
				 */
				csf::core::base::csf_time m_start_time;
				/**
				 * ��ʾapp����ά�ֵ�ʱ��
				 */
				csf::core::base::csf_time m_app_time;
				/**
				 * ��ʾ��ʱ��ȡ��ϵͳʱ��
				 */
				csf::core::base::csf_time m_system_time;
				/**
				 * ��ʾ��ǰ�Ĺ���Ŀ¼��ַ
				 */
				csf_string m_work_directory = "";
				/**
				 * ��ʾϵͳapp��ӵ�е�device�б�����device������app��������app����Դ��
				 */
				csf_unordered_map<csf_string, csf_device*> m_devices;
				/**
				* ��ʾϵͳ�ܵ����ù�������һ��ϵͳ��������һ�������ù�����
				*/
				csf::core::system::csf_configure_manager m_config_mg;
				/**
				 * ��ʾϵͳ��ģ���������һ��ϵͳ������һ��ģ�������
				 */
				csf::core::module::csf_module_manager m_module_manager;
				/**
				 * ��ʾϵͳ���������
				 */
				csf::core::module::csf_vm *m_vm = csf_nullptr;
				/**
				 * ϵͳ��־ϵͳ
				 */
				csf::core::system::csf_logger m_logger;
				/**
				* ��ʾapp�ĸ������ļ���Ϣ����Ҫ����app�ĸ��������ļ���Ϣ��
				*/
				csf_configure_file m_root_configure_file;
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex m_devices_mutex;
			};

		}

	}

}
#endif // !defined(CSF_APP_INCLUDED_)
