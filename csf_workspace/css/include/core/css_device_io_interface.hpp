/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_device_io_interface.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:27
*
*Description: Interface(css_device_io_interface) 表示css_device_io的操作接口内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_DEVICE_IO_INTERFACE_H_INCLUDED_)
#define CSS_DEVICE_IO_INTERFACE_H_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "csf_message_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示css_device_io的操作接口内容
		 * @author fangzhenmu@aliyun.com
		 * @version 1.0
		 * @created 07-10月-2018 16:50:27
		 */
		class css_device_io_interface : public csf::core::system::message::csf_message_interface
		{

		public:
			css_device_io_interface() {

			}

			virtual ~css_device_io_interface() {

			}

			/**
			 * 表示发送一个message内容
			 * 
			 * @param message    表示添加的消息内容
			 */
			virtual csf_int32 post(csf_message& message) =0;
			/**
			 * 根据类型、回调函数和信息内容创建消息
			 * 
			 * @param type    表示消息类型
			 * @param callback    表示回调函数
			 * @param element    表示消息内容
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element) =0;
			/**
			 * 表示弹出消息内容
			 */
			virtual csf::core::system::message::csf_message pop() =0;

		};

	}

}
#endif // !defined(CSS_DEVICE_IO_INTERFACE_H_INCLUDED_)
