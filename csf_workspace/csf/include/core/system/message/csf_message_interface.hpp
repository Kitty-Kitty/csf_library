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
*Date: 27-6月-2018 17:28:44
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
				 * 表示系统使用的消息处理接口
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:44
				 */
				class csf_message_interface
				{

				public:
					csf_message_interface() {

					}

					virtual ~csf_message_interface() {

					}

					/**
					 * 表示发送一个message内容
					 * 
					 * @param message    表示添加的消息内容
					 */
					virtual csf_int32 post(const csf_message& message) =0;
					/**
					 * 根据类型、回调函数和信息内容创建消息
					 * 
					 * @param type    表示消息类型
					 * @param callback    表示回调函数
					 * @param element    表示消息内容
					 */
					virtual csf_int32 post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element) =0;
					/**
					 * 表示弹出消息内容
					 */
					virtual csf::core::system::message::csf_message pop() =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_INTERFACE_INCLUDED_)
