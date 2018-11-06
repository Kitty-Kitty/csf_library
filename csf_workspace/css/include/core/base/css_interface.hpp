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
*Date: 07-10��-2018 16:50:28
*
*Description: Class(css_interface) ��ʾ����������Ϣ
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
		 * ��ʾ����������Ϣ
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:28
		 */
		class css_interface
		{

		public:
			css_interface();
			virtual ~css_interface();

			/**
			 * <font color="#008000">��ʾtcp�˿ں�</font>
			 */
			inline csf_int32 get_tcp_port() {

				return m_tcp_port;
			}
			/**
			 * <font color="#008000">��ʾtcp�˿ں�</font>
			 * 
			 * @param newVal
			 */
			inline void set_tcp_port(const csf_int32 newVal) {

				m_tcp_port = newVal;
			}
			/**
			 * <font color="#008000">��ʾudp�˿ں�</font>
			 */
			inline csf_int32 get_udp_port() {

				return m_udp_port;
			}
			/**
			 * <font color="#008000">��ʾudp�˿ں�</font>
			 * 
			 * @param newVal
			 */
			inline void set_udp_port(const csf_int32 newVal) {

				m_udp_port = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�Ƿ�ʹ��</font>
			 */
			inline csf_bool get_used() {

				return m_used;
			}
			/**
			 * <font color="#008000">��ʾ�Ƿ�ʹ��</font>
			 * 
			 * @param newVal
			 */
			inline void set_used(const csf_bool newVal) {

				m_used = newVal;
			}
			/**
			 * <font color="#008000">��ʾ����ip��ַ</font>
			 */
			inline csf_char* get_ip() {

				return m_ip[128];
			}
			/**
			 * <font color="#008000">��ʾ����ip��ַ</font>
			 * 
			 * @param newVal
			 */
			inline void set_ip(const csf_char* newVal) {

				m_ip[128] = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�����豸����</font>
			 */
			inline csf_char* get_name() {

				return m_name[128];
			}
			/**
			 * <font color="#008000">��ʾ�����豸����</font>
			 * 
			 * @param newVal
			 */
			inline void set_name(const csf_char* newVal) {

				m_name[128] = newVal;
			}
			/**
			 * ��ʾTCP������¼����˿�
			 */
			inline csf_int32 get_tcp_update_port() {

				return m_tcp_update_port;
			}
			/**
			 * ��ʾTCP������¼����˿�
			 * 
			 * @param newVal
			 */
			inline void set_tcp_update_port(const csf_int32 newVal) {

				m_tcp_update_port = newVal;
			}

		private:
			/**
			 * <font color="#008000">��ʾtcp�˿ں�</font>
			 */
			csf_int32 m_tcp_port = 0;
			/**
			 * <font color="#008000">��ʾudp�˿ں�</font>
			 */
			csf_int32 m_udp_port = 0;
			/**
			 * <font color="#008000">��ʾ�Ƿ�ʹ��</font>
			 */
			csf_bool m_used = csf_false;
			/**
			 * <font color="#008000">��ʾ����ip��ַ</font>
			 */
			csf_char m_ip[128];
			/**
			 * <font color="#008000">��ʾ�����豸����</font>
			 */
			csf_char m_name[128];
			/**
			 * ��ʾTCP������¼����˿�
			 */
			csf_int32 m_tcp_update_port = 0;

		};

	}

}
#endif // !defined(CSS_INTERFACE_H_INCLUDED_)
