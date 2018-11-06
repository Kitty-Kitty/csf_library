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
*Date: 07-10月-2018 16:50:25
*
*Description: Class(css_device) 表示cf_device抽象出来的css的设备内容
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
		 * 表示cf_device抽象出来的css的设备内容
		 * @author fangzhenmu@aliyun.com
		 * @version 1.0
		 * @created 07-10月-2018 16:50:25
		 */
		class css_device : public csf::core::module::csf_device, public css::core::css_device_interface
		{

		public:
			css_device();
			virtual ~css_device();

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
			 * 表示连接工厂管理器
			 */
			csf_connect_factory_manager& get_connect_factory_manager();
			/**
			 * 表示连接工厂管理器
			 * 
			 * @param newVal
			 */
			csf_void set_connect_factory_manager(csf_connect_factory_manager& newVal);
			/**
			 * 表示设备所拥有的主机信息
			 */
			inline css_host& get_host() {

				return m_host;
			}
			/**
			 * 表示设备所拥有的主机信息
			 * 
			 * @param newVal
			 */
			inline csf_void set_host(const css_host& newVal) {

				m_host = newVal;
			}
			/**
			 * 表示消息管理器
			 */
			inline csf_message_manager& get_message_manager() {

				return m_message_manager;
			}
			/**
			 * 表示消息管理器
			 * 
			 * @param newVal
			 */
			inline csf_void set_message_manager(const csf_message_manager& newVal) {

				m_message_manager = newVal;
			}
			/**
			 * 表示设备的线程管理器
			 */
			inline csf_thread_group& get_thread_group() {

				return m_thread_group;
			}
			/**
			 * 表示设备的线程管理器
			 * 
			 * @param newVal
			 */
			inline csf_void set_thread_group(csf_thread_group& newVal) {

				m_thread_group = newVal;
			}
			/**
			 * 表示请求队列内容
			 */
			inline csf_csfqueue<css_request*>& get_request_queue() {

				return m_request_queue;
			}
			/**
			 * 表示请求队列内容
			 * 
			 * @param newVal
			 */
			inline void set_request_queue(const csf_csfqueue<css_request*>& newVal) {

				m_request_queue = newVal;
			}
			/**
			 * 根据类型、回调函数和信息内容创建消息
			 * 
			 * @param type    表示消息类型
			 * @param callback    表示回调函数
			 * @param element    表示消息内容
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element);
			/**
			 * 表示发送一个message内容
			 * 
			 * @param message    表示添加的消息内容
			 */
			virtual csf_int32 post(const csf_message& message);
			/**
			 * 表示弹出消息内容
			 */
			virtual csf::core::system::message::csf_message pop();

		private:
			/**
			 * 表示监听的TCP连接
			 */
			csf::modules::connect::csf_tcp_connect m_listen_tcp_connect;
			/**
			 * 表示监听的UDP连接
			 */
			csf::modules::connect::csf_udp_connect m_listen_udp_connect;
			/**
			 * 表示请求队列内容
			 */
			csf_csfqueue<css_request*> m_request_queue;
			/**
			 * 表示消息管理器
			 * 
			 */
			csf::core::system::message::csf_message_manager m_message_manager;
			/**
			 * 表示设备所拥有的主机信息
			 * 
			 */
			css::core::css_host m_host;
			/**
			 * 表示设备的线程管理器
			 * 
			 */
			csf::core::utils::thread::csf_thread_group m_thread_group;
			/**
			 * 表示系统拥有的连接管理器
			 */
			csf::core::module::connect::csf_connect_factory_manager m_connect_factory_manager;

		};

	}

}
#endif // !defined(CSS_DEVICE_H_INCLUDED_)
