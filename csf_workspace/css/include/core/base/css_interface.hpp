/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_interface.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:28
*
*Description: Class(css_interface) 表示网络配置信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_INTERFACE_H_INCLUDED_)
#define CSS_INTERFACE_H_INCLUDED_

namespace css
{
	namespace core
	{
		/**
		 * 表示网络配置信息
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:28
		 */
		class css_interface
		{

		public:
			css_interface();
			virtual ~css_interface();

			/**
			 * <font color="#008000">表示tcp端口号</font>
			 */
			inline csf_int32 get_tcp_port() {

				return m_tcp_port;
			}
			/**
			 * <font color="#008000">表示tcp端口号</font>
			 * 
			 * @param newVal
			 */
			inline void set_tcp_port(const csf_int32 newVal) {

				m_tcp_port = newVal;
			}
			/**
			 * <font color="#008000">表示udp端口号</font>
			 */
			inline csf_int32 get_udp_port() {

				return m_udp_port;
			}
			/**
			 * <font color="#008000">表示udp端口号</font>
			 * 
			 * @param newVal
			 */
			inline void set_udp_port(const csf_int32 newVal) {

				m_udp_port = newVal;
			}
			/**
			 * <font color="#008000">表示是否使用</font>
			 */
			inline csf_bool get_used() {

				return m_used;
			}
			/**
			 * <font color="#008000">表示是否使用</font>
			 * 
			 * @param newVal
			 */
			inline void set_used(const csf_bool newVal) {

				m_used = newVal;
			}
			/**
			 * <font color="#008000">表示网卡ip地址</font>
			 */
			inline csf_char* get_ip() {

				return m_ip[128];
			}
			/**
			 * <font color="#008000">表示网卡ip地址</font>
			 * 
			 * @param newVal
			 */
			inline void set_ip(const csf_char* newVal) {

				m_ip[128] = newVal;
			}
			/**
			 * <font color="#008000">表示网卡设备名称</font>
			 */
			inline csf_char* get_name() {

				return m_name[128];
			}
			/**
			 * <font color="#008000">表示网卡设备名称</font>
			 * 
			 * @param newVal
			 */
			inline void set_name(const csf_char* newVal) {

				m_name[128] = newVal;
			}
			/**
			 * 表示TCP程序更新监听端口
			 */
			inline csf_int32 get_tcp_update_port() {

				return m_tcp_update_port;
			}
			/**
			 * 表示TCP程序更新监听端口
			 * 
			 * @param newVal
			 */
			inline void set_tcp_update_port(const csf_int32 newVal) {

				m_tcp_update_port = newVal;
			}

		private:
			/**
			 * <font color="#008000">表示tcp端口号</font>
			 */
			csf_int32 m_tcp_port = 0;
			/**
			 * <font color="#008000">表示udp端口号</font>
			 */
			csf_int32 m_udp_port = 0;
			/**
			 * <font color="#008000">表示是否使用</font>
			 */
			csf_bool m_used = csf_false;
			/**
			 * <font color="#008000">表示网卡ip地址</font>
			 */
			csf_char m_ip[128];
			/**
			 * <font color="#008000">表示网卡设备名称</font>
			 */
			csf_char m_name[128];
			/**
			 * 表示TCP程序更新监听端口
			 */
			csf_int32 m_tcp_update_port = 0;

		};

	}

}
#endif // !defined(CSS_INTERFACE_H_INCLUDED_)
