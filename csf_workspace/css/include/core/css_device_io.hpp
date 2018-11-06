/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: css_device_io.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:26
*
*Description: Class(css_device_io) 表示由cf_device集成的类，主要满足css使用
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_DEVICE_IO_H_INCLUDED_)
#define CSS_DEVICE_IO_H_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "csf_device_io.hpp"
#include "css_device_io_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示由cf_device集成的类，主要满足css使用
		 * @author fz
		 * @version 1.0
		 * @created 07-10月-2018 16:50:26
		 */
		class css_device_io : public csf::core::module::csf_device_io, public css::core::css_device_io_interface
		{

		public:
			css_device_io();
			virtual ~css_device_io();

			/**
			 * 模块初始化
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 表示发送一个message内容
			 * 
			 * @param message    表示添加的消息内容
			 */
			virtual csf_int32 post(csf_message& message);
			/**
			 * 根据类型、回调函数和信息内容创建消息
			 * 
			 * @param type    表示消息类型
			 * @param callback    表示回调函数
			 * @param element    表示消息内容
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element);
			/**
			 * 模块启动
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 表示弹出消息内容
			 */
			virtual csf::core::system::message::csf_message pop();
			/**
			 * 模块停止
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 表示发送一个message内容
			 * 
			 * @param message    表示添加的消息内容
			 */
			virtual csf_int32 post(const csf_message& message);
			/**
			 * 根据类型、回调函数和信息内容创建消息
			 * 
			 * @param type    表示消息类型
			 * @param callback    表示回调函数
			 * @param element    表示消息内容
			 */
			virtual csf_int32 post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
			/**
			 * 表示弹出消息内容
			 */
			virtual csf::core::system::message::csf_message pop();

		};

	}

}
#endif // !defined(CSS_DEVICE_IO_H_INCLUDED_)
