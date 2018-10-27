/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: fangzhenmu@aliyun.com
*
*Author: fz
*
*Version: 1.0
*
*Date: 20-7��-2018 17:41:40
*
*Description: Class(csf_app_bootloader) ��ʾϵͳ�������е�app���������ļ������������������ļ�����������app��ҪĬ�����е�device������ģ����Ҫ���ص�device_io���ݡ�
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_APP_BOOTLOADER_INCLUDED_)
#define CSF_APP_BOOTLOADER_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_app.hpp"
#include "csf_device.hpp"
#include "csf_device_io.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��ʾϵͳ�������е�app���������ļ������������������ļ�����������app��ҪĬ�����е�device������ģ����Ҫ���ص�device_io���ݡ�
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 20-7��-2018 17:41:40
			 */
			class csf_app_bootloader
			{

			public:
				inline explicit csf_app_bootloader()
					: m_configure_manager(csf_nullptr)
					, m_app(csf_nullptr) {

				}

				inline virtual ~csf_app_bootloader() {

				}

				/**
				 * ���ݸ������ļ���Ϣ����һ��app
				 * 
				 * @param app    ��ʾĿ��app����
				 * @param configure_manager    �����ļ���������ַ��Ϣ
				 * 
				 */
				inline explicit csf_app_bootloader(csf::core::module::csf_app* app
					, const csf_configure_manager* configure_manager)

					: m_configure_manager((csf_configure_manager*) configure_manager)
					, m_app(app) {

				}
				/**
				 * ��ʾ�����ļ���������ַ��Ϣ
				 */
				inline csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * ��ʾ�����ļ���������ַ��Ϣ
				 * 
				 * @param new_value    �����ļ���������ַ��Ϣ
				 */
				inline void set_configure_manager(const csf_configure_manager* new_value) {

					m_configure_manager = (csf_configure_manager*)new_value;
				}
				/**
				 * ��ʾ��ǰ��app_configure�ļ����õ�app����
				 */
				inline csf::core::module::csf_app* get_app() {

					return m_app;
				}
				/**
				* �ú�����Ҫ���ڳ�ʼ��app��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool init(csf::core::module::csf_app& app
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				 * �ú�����Ҫ���ڳ�ʼ��app��
				 * ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				 * 
				 * @param app    ��ʾĿ��app����
				 * @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				 */
				csf_bool start(csf::core::module::csf_app& app
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* �ú�����Ҫ���ڳ�ʼ��app��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����
				*/
				csf_bool stop(csf::core::module::csf_app& app);
				/**
				* ���ܣ��ú�����Ҫ���������ļ����ݴ���app�����������豸ģ�顣
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����    ��ʾ������app��Ϣ
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool create_devices(csf::core::module::csf_app& app
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* ���ܣ��ú�����Ҫ���������ļ����ݴ���һ���豸ģ�顣
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����
				* @param element    ��ʾ��ǰ��device�ڵ�����
				*/
				csf_bool create_device(csf::core::module::csf_app& app
					, const csf_element& element);
				/**
				* ���ܣ��ú�����Ҫ���������ļ����ݴ���app�������������豸ģ�顣
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param device    ��ʾ������device�豸��Ϣ
				* @param element    ��ʾ��ǰ��device�ڵ�����
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool create_device_ioes(csf::core::module::csf_device& device
					, const csf_element& element
					, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* ���ܣ��ú�����Ҫ���������ļ����ݴ���һ�����豸ģ�顣
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param device    ��ʾ������device�豸��Ϣ
				* @param element    ��ʾ��ǰ��device�ڵ�����
				*/
				csf_bool create_device_io(csf::core::module::csf_device& device
					, const csf_element& element);
				/**
				 * ��ʾ��ǰ��app_configure�ļ����õ�app����
				 * 
				 * @param new_value    ��ʾ��ǰ��app_configure�ļ����õ�app����
				 * 
				 */
				inline void set_app(const csf::core::module::csf_app* new_value) {

					m_app = (csf::core::module::csf_app*)new_value;
				}
			protected:
				/**
				 * ��ʾ�������ļ��ļ��б�ڵ��·����Ϣ��
				 */
				inline const csf_list<csf_string>& get_configure_files_items() {

					return m_configure_files_items;
				}
				/**
				* �ú�����Ҫ�������һ���豸��app�С�
				* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����
				* @param element    ��ʾģ��������Ϣ
				*/
				csf_bool add_device(csf::core::module::csf_app& app, const csf_element& element);
				/**
				* �ú�����Ҫ�������һ���豸��app�С�
				* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����
				* @param device    ��ʾ����ӵ��豸��ַ
				*/
				csf_bool add_device(csf::core::module::csf_app& app
					, const csf::core::module::csf_device* device);
				/**
				* ���ܣ��ú�����Ҫ���ڴ���һ���豸����
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܡ�
				*
				* @param app    ��ʾĿ��aap����
				* @param name    ��ʾģ������
				*/
				csf::core::module::csf_module* create_module(csf::core::module::csf_app& app
					, const csf_string& name);
				/**
				* ���ܣ��ú�����Ҫ���ڴ���һ���豸����
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܡ�
				*
				* @param app    ��ʾĿ��app����
				* @param name    ��ʾģ������
				*/
				inline csf::core::module::csf_device* create_device(csf::core::module::csf_app& app
					, const csf_string& name) {

					csf::core::module::csf_device			*tmp_device = csf_nullptr;


					tmp_device = dynamic_cast<csf::core::module::csf_device*>(create_module(app, name));
					if (tmp_device) {
						tmp_device->set_app(&app);
					}
					return tmp_device;
				}
				/**
				* ���ܣ��ú�����Ҫ���ڴ���һ���豸����
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܡ�
				*
				* @param device    ��ʾĿ��device����
				* @param name    ��ʾģ������
				*/
				inline csf::core::module::csf_device_io* create_device_io(csf::core::module::csf_device& device
					, const csf_string& name) {

					csf::core::module::csf_device_io			*tmp_device_io = csf_nullptr;


					tmp_device_io = dynamic_cast<csf::core::module::csf_device_io*>(create_module(*get_app(), name));
					if (tmp_device_io) {
						tmp_device_io->set_app(device.get_app());
						tmp_device_io->set_device(&device);
					}
					return tmp_device_io;
				}
				/**
				* �ú�����Ҫ�������һ���豸��device�С�
				* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
				*
				* @param device    ��ʾĿ��device����
				* @param element    ��ʾģ��������Ϣ
				*/
				csf_bool add_device_io(csf::core::module::csf_device& device
					, const csf_element& element);
				/**
				* �ú�����Ҫ�������һ���豸��device�С�
				* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
				*
				* @param device    ��ʾĿ��aap����
				* @param mid    ��ʾģ�鴴���Ķ���ΨһID
				* @param device_io    ��ʾ����ӵ��豸��ַ
				*/
				csf_bool add_device_io(csf::core::module::csf_device& device
					, const csf::core::module::csf_device_io* device_io);
				/**
				* ���ܣ��ú�����ʼ��app�е������豸��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾ������app��Ϣ
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool init_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* ���ܣ��ú�������app�е������豸��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾ������app��Ϣ
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool start_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager);
				/**
				* ���ܣ��ú���ֹͣapp�е������豸��
				* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
				*
				* @param app    ��ʾ������app��Ϣ
				* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
				*/
				csf_bool stop_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager);
			private:
				/**
				 * ��ʾ�����ļ���������ַ��Ϣ
				 */
				csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				 * ��ʾ��ǰ��app_configure�ļ����õ�app����
				 */
				csf::core::module::csf_app* m_app = csf_nullptr;
				/**
				 * ��ʾ�������ļ��ļ��б�ڵ��·����Ϣ��
				 */
				static const csf_list<csf_string> m_configure_files_items;

			};

		}

	}

}
#endif // !defined(CSF_APP_BOOTLOADER_INCLUDED_)
