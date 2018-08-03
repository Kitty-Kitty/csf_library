/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 17:33:44
*
*Description: Class(csf_device)��ʾ�豸����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_INCLUDED_)
#define CSF_DEVICE_INCLUDED_

#include "csf_device_interface.hpp"
#include "csf_device_base.hpp"
#include "csf_logger.hpp"
#include "csf_mutex.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾ�豸����
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7��-2018 17:33:44
			 */
			class csf_device : public csf::core::module::csf_device_base, public csf::core::module::csf_device_interface
			{

			public:
				/**
				* ��ʾ�豸������
				* @author f
				* @version 1.0
				* @created 12-7��-2018 16:39:10
				*/
				enum csf_device_type
				{
					/**
					* ��ʾδ֪���豸����
					*/
					csf_device_type_none = csf_module_type_device | 0x00000000,
					/**
					* ��ʾ���������豸
					*/
					csf_device_type_connect = csf_module_type_device | 0x00010000,
					/**
					* ��ʾ���ݿ��豸
					*/
					csf_device_type_database = csf_module_type_device | 0x00020000,
					/**
					* ��ʾ���̴����豸
					*/
					csf_device_type_process = csf_module_type_device | 0x00040000,
					/**
					* ��ʾ���������豸��չ�����ڵ���������
					*/
					csf_device_type_connect_extend = csf_device_type_connect | 0x00000001,
					/**
					* ��ʾ���ݿ��豸��չ�����ڵ���������
					*/
					csf_device_type_database_extend = csf_device_type_database | 0x00000001,
					/**
					* ��ʾ�����豸��չ�����ڵ���������
					*/
					csf_device_type_process_extend = csf_device_type_process | 0x00000001
				};

				inline explicit csf_device()
					: m_app(csf_nullptr) {

				}

				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				*/
				inline explicit csf_device(const csf_configure_manager * configure_manager)

					: csf_device_base(configure_manager, csf_module_type_device)
					, m_app(csf_nullptr) {

				}

				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				* @param type    ��ʾģ�������
				*/
				inline explicit csf_device(const csf_configure_manager * configure_manager
					, const csf::core::module::csf_device::csf_device_type type)
				
					: csf_device_base(configure_manager, (csf::core::module::csf_module::csf_module_type)type)
					, m_app(csf_nullptr) {

				}

				inline virtual ~csf_device() {

				}

				/**
				 * ��ʾdevice������app�豸��ַ
				 */
				inline csf_app* get_app() {

					return m_app;
				}
				/**
				 * ��ʾdevice������app�豸��ַ
				 *
				 * @param newVal
				 */
				inline csf_void set_app(const csf_app* newVal) {

					m_app = (csf_app*)newVal;
				}
				/**
				* ��ʾ�豸��ӵ�е�device_io�����ַ
				*/
				inline csf_unordered_map<csf_string, csf_device_io*>& get_device_ioes() {

					return m_device_ioes;
				}
				/**
				* ���ܣ�����ģ���mid����һ���豸����
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸��ģ����
				*/
				csf_device_io* find_device_io(const csf_string& mid);
				/**
				* ���ܣ�����ģ���mid����һ���豸����
				* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸��ģ����
				*/
				inline csf_device_io* find_device_io(const csf_char* mid) {

					if (!mid || csf_strlen(mid) <= 0) {
						return csf_nullptr;
					}

					return  find_device_io(csf_string(mid));
				}
				/**
				* ���ܣ�����ģ���mid��device�в���һ���豸����
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸��ģ����
				* @param device_io    ��ʾdevice_ioģ������ַ
				*/
				csf_bool add_device_io(const csf_string& mid, const csf_device_io* device_io);
				/**
				* ���ܣ�����ģ���mid��device�в���һ���豸����
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸��ģ����
				* @param device_io    ��ʾdevice_ioģ������ַ
				*/
				inline csf_bool add_device_io(const csf_char* mid, const csf_device_io* device_io) {

					if (!mid || !device_io || csf_strlen(mid) <= 0) {
						return csf_false;
					}

					return add_device_io(csf_string(mid), device_io);
				}
				/**
				* ���ܣ�����ģ���mid���豸�б���ɾ��һ���豸����
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸��ģ����
				*/
				csf_bool del_device_io(const csf_string& mid);
				/**
				* ���ܣ�����ģ���mid���豸�б���ɾ��һ���豸����
				* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
				*
				* @param mid    ��ʾ�豸��ģ����
				*/
				inline csf_bool del_device_io(const csf_char* mid) {

					if (!mid || csf_strlen(mid)) {
						return csf_false;
					}

					return del_device_io(csf_string(mid));
				}
			private:
				/**
				 * ��ʾdevice������app�豸��ַ
				 */
				csf_app* m_app = csf_nullptr;
				/**
				* ��ʾ�豸��ӵ�е�device_io�����ַ
				*/
				csf_unordered_map<csf_string, csf_device_io*> m_device_ioes;
				/**
				* ��ʾ�̰߳�ȫʹ�õĻ���������
				*/
				csf_shared_mutex m_device_ioes_mutex;
			};

		}

	}

}
#endif // !defined(CSF_DEVICE_INCLUDED_)
