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

#include "csf_manager.hpp"
#include "csf_thread_group.hpp"
#include "csf_message_manager_callback.hpp"
#include "csf_message.hpp"
#include "csf_message_interface.hpp"

using namespace csf::core::system::message;

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
				class csf_message_manager : public csf::core::module::csf_manager, public csf::core::system::message::csf_message_interface
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
					csf_int32 add(const csf_message::csf_message_type type);
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
					csf_int32 del(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_manager_callback callback);
					/**
					 * �������͡��ص���������Ϣ���ݴ�����Ϣ
					 * 
					 * @param type    ��ʾ��Ϣ����
					 * @param callback    ��ʾ�ص�����
					 * @param element    ��ʾ��Ϣ����
					 */
					virtual csf_int32 post(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
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

				private:
					/**
					 * ��ʾ�ص������б�
					 */
					csf_map<csf_message::csf_message_type, csf_message_manager_callback> m_callback_map;
					/**
					 * ��ʾ���յ�����Ϣ����Ķ���
					 */
					csf_queue<csf_message> m_queue;
					/**
					* ��ʾ��ǰ��Ϣ�������Ĵ����̳߳�
					*/
					csf::core::utils::thread::csf_thread_group m_thread_group;
					/**
					* ���ܣ�
					*    ��ʾ������Ϣ�ĺ���
					* ���أ�
					*    ��
					*/
					csf_void process();
					/**
					* ��ʾ�ص������б�
					*/
					inline csf_map<csf_message::csf_message_type, csf_message_manager_callback>& get_callback_map() {

						return m_callback_map;
					}
					/**
					* ��ʾ���յ�����Ϣ����Ķ���
					*/
					inline csf_queue<csf_message>& get_queue() {

						return m_queue;
					}
					/**
					* ��ʾ��ǰ��Ϣ�������Ĵ����̳߳�
					*/
					inline csf::core::utils::thread::csf_thread_group& get_thread_group() {

						return m_thread_group;
					}
				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_MANAGER_INCLUDED_)
