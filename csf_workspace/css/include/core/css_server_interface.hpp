/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_server_interface.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:32
*
*Description: Interface(css_server_interface) ��ʾcss_server�����ӿ�����
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SERVER_INTERFACE_H_INCLUDED_)
#define CSS_SERVER_INTERFACE_H_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "csf_message_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾcss_server�����ӿ�����
		 * @author fangzhenmu@aliyun.com
		 * @version 1.0
		 * @created 07-10��-2018 16:50:32
		 */
		class css_server_interface : public csf::core::system::message::csf_message_interface
		{

		public:
			css_server_interface() {

			}

			virtual ~css_server_interface() {

			}

			/**
			 * ��ʾ����һ��message����
			 * 
			 * @param message    ��ʾ��ӵ���Ϣ����
			 */
			virtual csf_int32 post(csf_message& message) =0;
			/**
			 * �������͡��ص���������Ϣ���ݴ�����Ϣ
			 * 
			 * @param type    ��ʾ��Ϣ����
			 * @param callback    ��ʾ�ص�����
			 * @param element    ��ʾ��Ϣ����
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) =0;
			/**
			 * ��ʾ������Ϣ����
			 */
			virtual csf::core::system::message::csf_message pop() =0;

		};

	}

}
#endif // !defined(CSS_SERVER_INTERFACE_H_INCLUDED_)
