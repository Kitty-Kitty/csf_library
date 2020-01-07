/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:44
*
*Description: Class(csf_message_manager)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_MANAGER_INCLUDED_)
#define CSF_MESSAGE_MANAGER_INCLUDED_

#include "csf_thread_group.hpp"
#include "csf_message_manager_callback.hpp"
#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "csf_message_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * ��ʾ��Ϣ������
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:44
				 */
				class csf_message_manager : public csf::core::system::message::csf_message_interface
				{

				public:
					csf_message_manager();
					virtual ~csf_message_manager();
					csf::core::system::message::csf_message *m_csf_message;

					/**
					 * ��ʾ��ӻص�����
					 * 
					 * @param type    ��ʾ��Ϣ������
					 */
					csf_int32 add(const csf::core::system::message::csf_message_type type);
					/**
					 * ��ʾ���ù�����
					 */
					inline csf_configure_manager* get_configure_manager() {

						return m_configure_manager;
					}
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
					virtual csf_int32 post(const csf_message& message);
					/**
					 * ��ʾ��ӻص�����
					 * 
					 * @param type    ��ʾ��Ϣ������
					 * @param callback    ��ʾ�ص�����
					 */
					csf_int32 del(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_manager_callback callback);
					/**
					 * �������͡��ص���������Ϣ���ݴ�����Ϣ
					 * 
					 * @param type    ��ʾ��Ϣ����
					 * @param callback    ��ʾ�ص�����
					 * @param element    ��ʾ��Ϣ����
					 */
					virtual csf_int32 post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
					/**
					 * ��ʾ���ù�����
					 * 
					 * @param newVal
					 */
					inline csf_void set_configure_manager(const csf_configure_manager* newVal) {

						m_configure_manager = newVal;
					}
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
					 * ��ʾ���յ�����Ϣ����Ķ���
					 */
					csf_queue<csf_message>& get_queue();
					/**
					 * ��ʾ���յ�����Ϣ����Ķ���
					 * 
					 * @param newVal
					 */
					csf_void set_queue(const csf_queue<csf_message>& newVal);
					csf_void process();

				private:
					/**
					 * ��ʾ�ص������б�
					 */
					csf_map<csf_message_type, csf_message_manager_callback> m_callback_map;
					/**
					 * ��ʾ���յ�����Ϣ����Ķ���
					 */
					csf_queue<csf_message> m_queue;
					csf::core::utils::thread::csf_thread_group m_thread_group;

					csf_thread_group& get_thread_group();
					/**
					 * 
					 * @param newVal
					 */
					csf_void set_thread_group(csf::core::utils::thread::csf_thread_group newVal);

				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_MANAGER_INCLUDED_)
