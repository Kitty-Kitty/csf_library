/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message_interface.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:44
*
*Description: Interface(csf_message_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_INTERFACE_INCLUDED_)
#define CSF_MESSAGE_INTERFACE_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * ��ʾϵͳʹ�õ���Ϣ����ӿ�
				 * @author f
				 * @version 1.0
				 * @created 27-6��-2018 17:28:44
				 */
				class csf_message_interface
				{

				public:
					csf_message_interface() {

					}

					virtual ~csf_message_interface() {

					}

					/**
					 * ��ʾ����һ��message����
					 * 
					 * @param message    ��ʾ��ӵ���Ϣ����
					 */
					virtual csf_int32 post(const csf_message& message) =0;
					/**
					 * �������͡��ص���������Ϣ���ݴ�����Ϣ
					 * 
					 * @param type    ��ʾ��Ϣ����
					 * @param callback    ��ʾ�ص�����
					 * @param element    ��ʾ��Ϣ����
					 */
					virtual csf_int32 post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) =0;
					/**
					 * ��ʾ������Ϣ����
					 */
					virtual csf::core::system::message::csf_message pop() =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_INTERFACE_INCLUDED_)
