/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_host.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:27
*
*Description: Class(css_host) 表示css设备主机信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_HOST_H_INCLUDED_)
#define CSS_HOST_H_INCLUDED_

#include "css_id.hpp"
#include "css_information.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示css设备主机信息
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:27
		 */
		class css_host
		{

		public:
			/**
			 * 表示设备的类型
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:27
			 */
			enum css_device_type
			{
				/**
				 * 表示未知的设备类型
				 */
				m_css_device_type_none = 0x00000001
			};

			/**
			 * 表示设备的子设备类型
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:27
			 */
			enum css_device_subtype
			{
				/**
				 * 表示未知的设备类型
				 */
				m_css_device_subtype_none = 0x00000001
			};

			/**
			 * 表示设备的状态信息
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:27
			 */
			enum css_device_status
			{
				/**
				 * 表示未知的设备状态
				 */
				m_css_device_status_none = 0x00000001
			};


			css_host();
			virtual ~css_host();

			/**
			 * 表示设备类型
			 */
			inline css_device_type get_type() {

				return m_type;
			}
			/**
			 * 表示设备类型
			 * 
			 * @param newVal
			 */
			inline void set_type(const css_device_type newVal) {

				m_type = newVal;
			}
			/**
			 * 表示子设备类型
			 */
			inline css_device_subtype get_subtype() {

				return m_subtype;
			}
			/**
			 * 表示子设备类型
			 * 
			 * @param newVal
			 */
			inline void set_subtype(const css_device_subtype newVal) {

				m_subtype = newVal;
			}
			/**
			 * 表示设备id信息
			 */
			inline csf_char* get_id() {

				return m_id[128];
			}
			/**
			 * 表示设备id信息
			 * 
			 * @param newVal
			 */
			inline void set_id(const csf_char* newVal) {

				m_id[128] = newVal;
			}
			/**
			 * 表示设备的名称
			 */
			inline csf_char* get_name() {

				return m_name[128];
			}
			/**
			 * 表示设备的名称
			 * 
			 * @param newVal
			 */
			inline void set_name(const csf_char* newVal) {

				m_name[128] = newVal;
			}
			/**
			 * 表示设备的版本信息
			 */
			inline csf_char* get_version() {

				return m_version[128];
			}
			/**
			 * 表示设备的版本信息
			 * 
			 * @param newVal
			 */
			inline void set_version(const csf_char* newVal) {

				m_version[128] = newVal;
			}
			/**
			 * 表示设备的状态码
			 */
			inline css::core::css_device_status get_status() {

				return m_status;
			}
			/**
			 * 表示设备的状态码
			 * 
			 * @param newVal
			 */
			inline void set_status(const css::core::css_device_status newVal) {

				m_status = newVal;
			}
			/**
			 * 表示设备所使用的网络设备列表
			 */
			inline csf_list<css_interface>& get_interfaces() {

				return m_interfaces;
			}
			/**
			 * 表示设备所使用的网络设备列表
			 * 
			 * @param newVal
			 */
			inline void set_interfaces(const csf_list<css_interface>& newVal) {

				m_interfaces = newVal;
			}
			/**
			 * 表示设备id信息
			 */
			css::core::css_id get_id();
			/**
			 * 表示设备id信息
			 * 
			 * @param newVal
			 */
			void set_id(css::core::css_id newVal);
			/**
			 * 表示心跳次数
			 */
			inline csf_int32 get_heartbeat_times() {

				return m_heartbeat_times;
			}
			/**
			 * 表示心跳次数
			 * 
			 * @param newVal
			 */
			inline void set_heartbeat_times(const csf_int32 newVal) {

				m_heartbeat_times = newVal;
			}
			/**
			 * 表示每次心跳的间隔时间
			 */
			inline csf_int32 get_heartbeat_interval() {

				return m_heartbeat_interval;
			}
			/**
			 * 表示每次心跳的间隔时间
			 * 
			 * @param newVal
			 */
			inline void set_heartbeat_interval(const csf_int32 newVal) {

				m_heartbeat_interval = newVal;
			}
			/**
			 * 表示设备信息结构
			 */
			inline css_information& get_information() {

				return m_information;
			}
			/**
			 * 表示设备信息结构
			 * 
			 * @param newVal
			 */
			inline void set_information(const css_information& newVal) {

				m_information = newVal;
			}

		private:
			/**
			 * 表示设备类型
			 */
			css_device_type m_type = css_device_type_none;
			/**
			 * 表示子设备类型
			 */
			css_device_subtype m_subtype = css_device_subtype_none;
			/**
			 * 表示设备的名称
			 */
			csf_char m_name[128] = {0, };
			/**
			 * 表示设备的版本信息
			 */
			csf_char m_version[128] = {0, };
			/**
			 * 表示设备的状态码
			 */
			css::core::css_device_status m_status = css_device_status_none;
			/**
			 * 表示心跳次数
			 */
			csf_int32 m_heartbeat_times = 0;
			/**
			 * 表示设备所使用的网络设备列表
			 */
			csf_list<css_interface> m_interfaces;
			/**
			 * 表示每次心跳的间隔时间
			 */
			csf_int32 m_heartbeat_interval = 0;
			/**
			 * 表示设备的id信息
			 */
			css::core::css_id m_id;
			/**
			 * 表示设备信息结构
			 * 
			 */
			css::core::css_information m_information;

		};

	}

}
#endif // !defined(CSS_HOST_H_INCLUDED_)
