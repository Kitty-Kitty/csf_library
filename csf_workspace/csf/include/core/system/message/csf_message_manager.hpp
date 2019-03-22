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
*Date: 27-6月-2018 17:28:44
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
				 * 表示消息管理器
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:44
				 */
				class csf_message_manager : public csf::core::module::csf_manager, public csf::core::system::message::csf_message_interface
				{

				public:
					csf_message_manager();
					virtual ~csf_message_manager();
					csf::core::system::message::csf_message *m_csf_message;

					/**
					 * 表示添加回调函数
					 * 
					 * @param type    表示消息的类型
					 */
					csf_int32 add(const csf_message::csf_message_type type);
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
					virtual csf_int32 post(const csf_message& message);
					/**
					 * 表示添加回调函数
					 * 
					 * @param type    表示消息的类型
					 * @param callback    表示回调函数
					 */
					csf_int32 del(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_manager_callback callback);
					/**
					 * 根据类型、回调函数和信息内容创建消息
					 * 
					 * @param type    表示消息类型
					 * @param callback    表示回调函数
					 * @param element    表示消息内容
					 */
					virtual csf_int32 post(const csf_message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
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

				private:
					/**
					 * 表示回调函数列表
					 */
					csf_map<csf_message::csf_message_type, csf_message_manager_callback> m_callback_map;
					/**
					 * 表示接收到的消息保存的队列
					 */
					csf_queue<csf_message> m_queue;
					/**
					* 表示当前消息管理器的处理线程池
					*/
					csf::core::utils::thread::csf_thread_group m_thread_group;
					/**
					* 功能：
					*    表示处理消息的函数
					* 返回：
					*    无
					*/
					csf_void process();
					/**
					* 表示回调函数列表
					*/
					inline csf_map<csf_message::csf_message_type, csf_message_manager_callback>& get_callback_map() {

						return m_callback_map;
					}
					/**
					* 表示接收到的消息保存的队列
					*/
					inline csf_queue<csf_message>& get_queue() {

						return m_queue;
					}
					/**
					* 表示当前消息管理器的处理线程池
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
