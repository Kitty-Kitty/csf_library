/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fz
*
*File name: device_media.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:34
*
*Description: Class(device_media) 表示媒体设备
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(DEVICE_MEDIA_H_INCLUDED_)
#define DEVICE_MEDIA_H_INCLUDED_

#include "csf_message_callback.hpp"
#include "csf_message.hpp"
#include "css_device.hpp"

namespace css
{
	namespace modules
	{
		namespace media_server
		{
			namespace device_media
			{
				/**
				 * 表示媒体设备
				 * @author fz
				 * @version 1.0
				 * @created 07-10月-2018 16:50:34
				 */
				class device_media : public css::core::css_device
				{

				public:
					device_media();
					virtual ~device_media();

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
					void set_connect_factory_manager(csf_connect_factory_manager& newVal);
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
					inline void set_host(const css_host& newVal) {

						m_host = newVal;
					}

				};

			}

		}

	}

}
#endif // !defined(DEVICE_MEDIA_H_INCLUDED_)
