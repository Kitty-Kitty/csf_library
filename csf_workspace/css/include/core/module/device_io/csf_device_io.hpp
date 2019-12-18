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
*Description: Class(csf_device_io)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_IO_INCLUDED_)
#define CSF_DEVICE_IO_INCLUDED_

#include "csf_device_io_interface.hpp"
#include "csf_device_base.hpp"
#include "csf_device.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device_io
			{
				/**
				 * ��ʾ�豸io�ĳ���
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 01-7��-2018 17:33:47
				 */
				class csf_device_io : public csf::core::module::csf_device_base, public csf::core::module::device_io::csf_device_io_interface
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

					virtual~csf_device_io() {

					}

					/**
					 * ��ʾdevice_io������app��ַ
					 * 
					 * @param newVal
					 */
					inline void set_app(const csf::core::module::app::csf_app* newVal) {
						m_app = (csf::core::module::app::csf_app*)newVal;
					}
					/**
					 * ��ʾ�豸io������device��ַ��Ϣ
					 */
					inline csf::core::module::device::csf_device* get_device() {

						return m_device;
					}
					/**
					 * ��ʾ�豸io������device��ַ��Ϣ
					 * 
					 * @param newVal
					 */
					inline void set_device(const csf::core::module::device::csf_device* newVal) {

						m_device = (csf::core::module::device::csf_device*)newVal;
					}
					inline csf_app* get_app() {

						return  m_app;
					}

				private:
					/**
					 * ��ʾ�豸io������device��ַ��Ϣ
					 */
					csf::core::module::device::csf_device* m_device = csf_nullptr;
					/**
					 * ��ʾdevice_io������app��ַ
					 */
					csf::core::module::app::csf_app* m_app = csf_nullptr;

				};

			}

		}

	}

}
#endif // !defined(CSF_DEVICE_IO_INCLUDED_)