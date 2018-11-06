/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_exception.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:27
*
*Description: Class(css_exception) ��ʾ�쳣��Ϣ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_EXCEPTION_H_INCLUDED_)
#define CSS_EXCEPTION_H_INCLUDED_

#include "csf_time.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾ�쳣��Ϣ��
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:27
		 */
		class css_exception
		{

		public:
			/**
			 * ��ʾcss��״̬��
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:27
			 */
			enum css_status
			{
				/**
				 * ��ʾcssδ֪״̬��Ϣ
				 */
				m_css_status_none = 0x00000000
			};


			css_exception();
			virtual ~css_exception();

			/**
			 * ��ʾ�쳣״̬��Ϣ��<font color="#008000">��ʾ״̬�룬��Ϊ����״̬��</font>
			 */
			inline css_status get_status() {

				return m_status;
			}
			/**
			 * ��ʾ�쳣״̬��Ϣ��<font color="#008000">��ʾ״̬�룬��Ϊ����״̬��</font>
			 * 
			 * @param newVal
			 */
			inline void set_status(const css_status newVal) {

				m_status = newVal;
			}
			/**
			 * <font color="#008000">��ʾ˽��״̬�룬Ϊƽ̨�Լ���״̬��</font>
			 */
			inline css_status get_private_status() {

				return m_private_status;
			}
			/**
			 * <font color="#008000">��ʾ˽��״̬�룬Ϊƽ̨�Լ���״̬��</font>
			 * 
			 * @param newVal
			 */
			inline void set_private_status(const css_status newVal) {

				m_private_status = newVal;
			}
			/**
			 * <font color="#008000">ý��ͨ������</font>
			 */
			inline csf_int32 get_channel_id() {

				return m_channel_id;
			}
			/**
			 * <font color="#008000">ý��ͨ������</font>
			 * 
			 * @param newVal
			 */
			inline void set_channel_id(const csf_int32 newVal) {

				m_channel_id = newVal;
			}
			/**
			 * <font color="#008000">�쳣�����ĵ�ǰʱ��</font>
			 */
			inline csf::core::base::csf_time get_time() {

				return m_time;
			}
			/**
			 * <font color="#008000">�쳣�����ĵ�ǰʱ��</font>
			 * 
			 * @param newVal
			 */
			inline void set_time(const csf::core::base::csf_time newVal) {

				m_time = newVal;
			}
			/**
			 * <font color="#008000">�쳣����ʱ��</font>
			 */
			inline csf::core::base::csf_time get_send_time() {

				return m_send_time;
			}
			/**
			 * <font color="#008000">�쳣����ʱ��</font>
			 * 
			 * @param newVal
			 */
			inline void set_send_time(const csf::core::base::csf_time newVal) {

				m_send_time = newVal;
			}
			/**
			 * <font color="#008000">�쳣������Ϣ</font>
			 */
			inline csf_string& get_description() {

				return m_description;
			}
			/**
			 * <font color="#008000">�쳣������Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline void set_description(const csf_char* newVal) {

				m_description = newVal;
			}
			/**
			 * <font color="#008000">��ʾ���ŻỰID����ID��ʾһ���Ự</font>
			 */
			inline csf_string& get_play_session() {

				return m_play_session;
			}
			/**
			 * <font color="#008000">��ʾ���ŻỰID����ID��ʾһ���Ự</font>
			 * 
			 * @param newVal
			 */
			inline void set_play_session(const csf_string& newVal) {

				m_play_session = newVal;
			}
			/**
			 * <font color="#008000">ý����ID</font>
			 */
			inline csf_string& get_media_id() {

				return m_media_id;
			}
			/**
			 * <font color="#008000">ý����ID</font>
			 * 
			 * @param newVal
			 */
			inline void set_media_id(const csf_char* newVal) {

				m_media_id = newVal;
			}
			/**
			 * <font color="#008000">��ǰ�ĻỰid</font>
			 */
			inline csf_string& get_session() {

				return m_session;
			}
			/**
			 * <font color="#008000">��ǰ�ĻỰid</font>
			 * 
			 * @param newVal
			 */
			inline void set_session(csf_string& newVal) {

				m_session = newVal;
			}
			/**
			 * <font color="#008000">��ǰ�ĻỰid</font>
			 * 
			 * @param newVal
			 */
			inline void set_session(csf_char* newVal) {

				m_session = newVal;
			}
			/**
			 * <font color="#008000">��ʾ���ŻỰID����ID��ʾһ���Ự</font>
			 * 
			 * @param newVal
			 */
			inline void set_play_session(const csf_char* newVal) {

				m_play_session = newVal;
			}
			/**
			 * <font color="#008000">ý����ID</font>
			 * 
			 * @param newVal
			 */
			inline void set_media_id(const csf_string& newVal) {

				m_media_id = newVal;
			}
			/**
			 * <font color="#008000">�쳣������Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline void set_description(const csf_string& newVal) {

				m_description = newVal;
			}

		private:
			/**
			 * ��ʾ�쳣״̬��Ϣ��<font color="#008000">��ʾ״̬�룬��Ϊ����״̬��</font>
			 */
			css_status m_status = css_status_none;
			/**
			 * <font color="#008000">��ʾ˽��״̬�룬Ϊƽ̨�Լ���״̬��</font>
			 */
			css_status m_private_status = css_status_none;
			/**
			 * <font color="#008000">ý��ͨ������</font>
			 */
			csf_int32 m_channel_id = 0;
			/**
			 * <font color="#008000">�쳣�����ĵ�ǰʱ��</font>
			 */
			csf::core::base::csf_time m_time = 0;
			/**
			 * <font color="#008000">�쳣����ʱ��</font>
			 */
			csf::core::base::csf_time m_send_time = 0;
			/**
			 * <font color="#008000">�쳣������Ϣ</font>
			 */
			csf_string m_description = "";
			/**
			 * <font color="#008000">��ʾ���ŻỰID����ID��ʾһ���Ự</font>
			 */
			csf_string m_play_session = "";
			/**
			 * <font color="#008000">ý����ID</font>
			 */
			csf_string m_media_id = "";
			/**
			 * <font color="#008000">��ǰ�ĻỰid</font>
			 */
			csf_string m_session = "";

		};

	}

}
#endif // !defined(CSS_EXCEPTION_H_INCLUDED_)
