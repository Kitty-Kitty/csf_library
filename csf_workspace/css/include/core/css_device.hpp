/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_device.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:25
*
*Description: Class(css_device) ��ʾcf_device���������css���豸����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_DEVICE_H_INCLUDED_)
#define CSS_DEVICE_H_INCLUDED_

#include "csf_tcp_connect.hpp"
#include "csf_udp_connect.hpp"
#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "css_device_interface.hpp"
#include "csf_message_manager.hpp"
#include "csf_device.hpp"
#include "css_host.hpp"
#include "csf_thread_group.hpp"
#include "csf_connect_factory_manager.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾcf_device���������css���豸����
		 * @author fangzhenmu@aliyun.com
		 * @version 1.0
		 * @created 07-10��-2018 16:50:25
		 */
		class css_device : public csf::core::module::csf_device, public css::core::css_device_interface
		{

		public:
			css_device();
			virtual ~css_device();

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
			csf_void set_connect_factory_manager(csf_connect_factory_manager& newVal);
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
			inline csf_void set_host(const css_host& newVal) {

				m_host = newVal;
			}
			/**
			 * ��ʾ��Ϣ������
			 */
			inline csf_message_manager& get_message_manager() {

				return m_message_manager;
			}
			/**
			 * ��ʾ��Ϣ������
			 * 
			 * @param newVal
			 */
			inline csf_void set_message_manager(const csf_message_manager& newVal) {

				m_message_manager = newVal;
			}
			/**
			 * ��ʾ�豸���̹߳�����
			 */
			inline csf_thread_group& get_thread_group() {

				return m_thread_group;
			}
			/**
			 * ��ʾ�豸���̹߳�����
			 * 
			 * @param newVal
			 */
			inline csf_void set_thread_group(csf_thread_group& newVal) {

				m_thread_group = newVal;
			}
			/**
			 * ��ʾ�����������
			 */
			inline csf_csfqueue<css_request*>& get_request_queue() {

				return m_request_queue;
			}
			/**
			 * ��ʾ�����������
			 * 
			 * @param newVal
			 */
			inline void set_request_queue(const csf_csfqueue<css_request*>& newVal) {

				m_request_queue = newVal;
			}
			/**
			 * �������͡��ص���������Ϣ���ݴ�����Ϣ
			 * 
			 * @param type    ��ʾ��Ϣ����
			 * @param callback    ��ʾ�ص�����
			 * @param element    ��ʾ��Ϣ����
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element);
			/**
			 * ��ʾ����һ��message����
			 * 
			 * @param message    ��ʾ��ӵ���Ϣ����
			 */
			virtual csf_int32 post(const csf_message& message);
			/**
			 * ��ʾ������Ϣ����
			 */
			virtual csf::core::system::message::csf_message pop();

		private:
			/**
			 * ��ʾ������TCP����
			 */
			csf::modules::connect::csf_tcp_connect m_listen_tcp_connect;
			/**
			 * ��ʾ������UDP����
			 */
			csf::modules::connect::csf_udp_connect m_listen_udp_connect;
			/**
			 * ��ʾ�����������
			 */
			csf_csfqueue<css_request*> m_request_queue;
			/**
			 * ��ʾ��Ϣ������
			 * 
			 */
			csf::core::system::message::csf_message_manager m_message_manager;
			/**
			 * ��ʾ�豸��ӵ�е�������Ϣ
			 * 
			 */
			css::core::css_host m_host;
			/**
			 * ��ʾ�豸���̹߳�����
			 * 
			 */
			csf::core::utils::thread::csf_thread_group m_thread_group;
			/**
			 * ��ʾϵͳӵ�е����ӹ�����
			 */
			csf::core::module::connect::csf_connect_factory_manager m_connect_factory_manager;

		};

	}

}
#endif // !defined(CSS_DEVICE_H_INCLUDED_)
