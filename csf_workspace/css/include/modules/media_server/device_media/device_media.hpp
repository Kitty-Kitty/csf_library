/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: device_media.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:34
*
*Description: Class(device_media) ��ʾý���豸
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(DEVICE_MEDIA_H_INCLUDED_)
#define DEVICE_MEDIA_H_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "css_device.hpp"

namespace css
{
	namespace modules
	{
		namespace media_server
		{
			namespace device_media
			{
				/**
				 * ��ʾý���豸
				 * @author fz
				 * @version 1.0
				 * @created 07-10��-2018 16:50:34
				 */
				class device_media : public css::core::css_device
				{

				public:
					device_media();
					virtual ~device_media();

					/**
					 * ģ���ʼ��
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ����һ��message����
					 * 
					 * @param message    ��ʾ��ӵ���Ϣ����
					 */
					virtual csf_int32 post(csf_message& message);
					/**
					 * �������͡��ص���������Ϣ���ݴ�����Ϣ
					 * 
					 * @param type    ��ʾ��Ϣ����
					 * @param callback    ��ʾ�ص�����
					 * @param element    ��ʾ��Ϣ����
					 */
					virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element);
					/**
					 * ģ������
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ������Ϣ����
					 */
					virtual csf::core::system::message::csf_message pop();
					/**
					 * ģ��ֹͣ
					 * 
					 * @param conf_mg    ��ʾ�����ļ���Ϣ
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * ��ʾ���ӹ���������
					 */
					csf_connect_factory_manager& get_connect_factory_manager();
					/**
					 * ��ʾ���ӹ���������
					 * 
					 * @param newVal
					 */
					void set_connect_factory_manager(csf_connect_factory_manager& newVal);
					/**
					 * ��ʾ�豸��ӵ�е�������Ϣ
					 */
					inline css_host& get_host() {

						return m_host;
					}
					/**
					 * ��ʾ�豸��ӵ�е�������Ϣ
					 * 
					 * @param newVal
					 */
					inline void set_host(const css_host& newVal) {

						m_host = newVal;
					}

				};

			}

		}

	}

}
#endif // !defined(DEVICE_MEDIA_H_INCLUDED_)
