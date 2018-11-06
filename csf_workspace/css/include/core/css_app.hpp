/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_app.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:25
*
*Description: Class(css_app) 云拼接服务器类实现
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_APP_H_INCLUDED_)
#define CSS_APP_H_INCLUDED_

#include "csf_message_manager.hpp"
#include "csf_app.hpp"
#include "css_server_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 云拼接服务器类实现
		 * @author fangzhenmu@aliyun.com
		 * @version 1.0
		 * @created 07-10月-2018 16:50:25
		 */
		class css_app : public csf::core::module::csf_app, public css::core::css_server_interface
		{

		public:
			css_app();
			virtual ~css_app();

			/**
			 * 表示配置管理器
			 */
			inline csf_configure_manager* get_configure_manager() {

				return m_configure_manager;
			}
			/**
			 * 模块初始化
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 表示配置管理器
			 * 
			 * @param newVal
			 */
			inline csf::core::base::csf_void set_configure_manager(csf_configure_manager* newVal) {

				m_configure_manager = newVal;
			}
			/**
			 * 模块启动
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * 模块停止
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
			csf_message_manager& get_message_manager();
			/**
			 * 
			 * @param newVal
			 */
			void set_message_manager(csf::core::system::message::csf_message_manager newVal);
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
			 * 表示弹出消息内容
			 */
			virtual csf::core::system::message::csf_message pop();
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

		private:
			/**
			 * 表示消息管理器
			 */
			csf::core::system::message::csf_message_manager m_message_manager;

		};

	}

}
#endif // !defined(CSS_APP_H_INCLUDED_)
