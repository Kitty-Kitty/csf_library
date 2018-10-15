/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device_io.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 17:33:47
*
*Description: Class(csf_device_io)��ʾ�豸io�ĳ���
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_IO_INCLUDED_)
#define CSF_DEVICE_IO_INCLUDED_

#include "csf_device_io_interface.hpp"
#include "csf_device_base.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾ�豸io�ĳ���
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 01-7��-2018 17:33:47
			 */
			class csf_device_io : public csf::core::module::csf_device_base, public csf::core::module::csf_device_io_interface
			{

			public:
				/**
				* ��ʾ�豸device_io������
				* @author f
				* @version 1.0
				* @created 12-7��-2018 16:40:16
				*/
				enum csf_device_io_type
				{
					/**
					* ��ʾ�豸��device_io��δ֪����
					*/
					csf_device_io_type_none = csf_module_type_device_io | 0x00000000,
					/**
					* ��ʾ�豸��device_io��ͨ����չ
					*/
					csf_device_io_type_general_extend = csf_device_io_type_none | 0x00010000
				};

				explicit csf_device_io()
					: m_device(csf_nullptr)
					, m_app(csf_nullptr) {

				}

				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				*/
				inline explicit csf_device_io(const csf_configure_manager * configure_manager)

					: csf_device_base(configure_manager, csf_module_type_device_io)
					, m_device(csf_nullptr)
					, m_app(csf_nullptr) {

				}

				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				* @param type    ��ʾģ�������
				*/
				inline explicit csf_device_io(const csf_configure_manager * configure_manager
					, const csf::core::module::csf_module::csf_module_type type) 
				
					: csf_device_base(configure_manager, type)
					, m_device(csf_nullptr)
					, m_app(csf_nullptr) {

				}


				inline virtual ~csf_device_io() {

				}

				/**
				 * ��ʾdevice_io������app��ַ
				 *
				 * @param new_value
				 */
				inline void set_app(const csf::core::module::csf_app* new_value) {
					m_app = (csf::core::module::csf_app*)new_value;
				}
				/**
				 * ��ʾ�豸io������device��ַ��Ϣ
				 */
				inline csf::core::module::csf_device* get_device() {

					return m_device;
				}
				/**
				 * ��ʾ�豸io������device��ַ��Ϣ
				 *
				 * @param new_value
				 */
				inline void set_device(const csf::core::module::csf_device* new_value) {

					m_device = (csf::core::module::csf_device*)new_value;
				}
				inline csf::core::module::csf_app* get_app() {

					return  m_app;
				}
				/**
				* ��Ҫ�����ǣ���ģ����Ϣ��ʽ�����ַ������
				* ���أ�ģ����Ϣ�ַ���
				*/
				inline virtual csf_string to_string() {

					return "";
				}
			private:
				/**
				 * ��ʾ�豸io������device��ַ��Ϣ
				 */
				csf::core::module::csf_device* m_device = csf_nullptr;
				/**
				 * ��ʾdevice_io������app��ַ
				 */
				csf::core::module::csf_app* m_app = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_DEVICE_IO_INCLUDED_)
