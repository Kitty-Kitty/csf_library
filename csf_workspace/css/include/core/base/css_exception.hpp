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
*Date: 07-10月-2018 16:50:27
*
*Description: Class(css_exception) 表示异常信息类
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
		 * 表示异常信息类
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:27
		 */
		class css_exception
		{

		public:
			/**
			 * 表示css的状态码
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:27
			 */
			enum css_status
			{
				/**
				 * 表示css未知状态信息
				 */
				m_css_status_none = 0x00000000
			};


			css_exception();
			virtual ~css_exception();

			/**
			 * 表示异常状态信息，<font color="#008000">表示状态码，多为公用状态码</font>
			 */
			inline css_status get_status() {

				return m_status;
			}
			/**
			 * 表示异常状态信息，<font color="#008000">表示状态码，多为公用状态码</font>
			 * 
			 * @param newVal
			 */
			inline void set_status(const css_status newVal) {

				m_status = newVal;
			}
			/**
			 * <font color="#008000">表示私有状态码，为平台自己的状态码</font>
			 */
			inline css_status get_private_status() {

				return m_private_status;
			}
			/**
			 * <font color="#008000">表示私有状态码，为平台自己的状态码</font>
			 * 
			 * @param newVal
			 */
			inline void set_private_status(const css_status newVal) {

				m_private_status = newVal;
			}
			/**
			 * <font color="#008000">媒体通道编码</font>
			 */
			inline csf_int32 get_channel_id() {

				return m_channel_id;
			}
			/**
			 * <font color="#008000">媒体通道编码</font>
			 * 
			 * @param newVal
			 */
			inline void set_channel_id(const csf_int32 newVal) {

				m_channel_id = newVal;
			}
			/**
			 * <font color="#008000">异常发生的当前时间</font>
			 */
			inline csf::core::base::csf_time get_time() {

				return m_time;
			}
			/**
			 * <font color="#008000">异常发生的当前时间</font>
			 * 
			 * @param newVal
			 */
			inline void set_time(const csf::core::base::csf_time newVal) {

				m_time = newVal;
			}
			/**
			 * <font color="#008000">异常发送时间</font>
			 */
			inline csf::core::base::csf_time get_send_time() {

				return m_send_time;
			}
			/**
			 * <font color="#008000">异常发送时间</font>
			 * 
			 * @param newVal
			 */
			inline void set_send_time(const csf::core::base::csf_time newVal) {

				m_send_time = newVal;
			}
			/**
			 * <font color="#008000">异常描述信息</font>
			 */
			inline csf_string& get_description() {

				return m_description;
			}
			/**
			 * <font color="#008000">异常描述信息</font>
			 * 
			 * @param newVal
			 */
			inline void set_description(const csf_char* newVal) {

				m_description = newVal;
			}
			/**
			 * <font color="#008000">表示播放会话ID，该ID表示一个会话</font>
			 */
			inline csf_string& get_play_session() {

				return m_play_session;
			}
			/**
			 * <font color="#008000">表示播放会话ID，该ID表示一个会话</font>
			 * 
			 * @param newVal
			 */
			inline void set_play_session(const csf_string& newVal) {

				m_play_session = newVal;
			}
			/**
			 * <font color="#008000">媒体编号ID</font>
			 */
			inline csf_string& get_media_id() {

				return m_media_id;
			}
			/**
			 * <font color="#008000">媒体编号ID</font>
			 * 
			 * @param newVal
			 */
			inline void set_media_id(const csf_char* newVal) {

				m_media_id = newVal;
			}
			/**
			 * <font color="#008000">当前的会话id</font>
			 */
			inline csf_string& get_session() {

				return m_session;
			}
			/**
			 * <font color="#008000">当前的会话id</font>
			 * 
			 * @param newVal
			 */
			inline void set_session(csf_string& newVal) {

				m_session = newVal;
			}
			/**
			 * <font color="#008000">当前的会话id</font>
			 * 
			 * @param newVal
			 */
			inline void set_session(csf_char* newVal) {

				m_session = newVal;
			}
			/**
			 * <font color="#008000">表示播放会话ID，该ID表示一个会话</font>
			 * 
			 * @param newVal
			 */
			inline void set_play_session(const csf_char* newVal) {

				m_play_session = newVal;
			}
			/**
			 * <font color="#008000">媒体编号ID</font>
			 * 
			 * @param newVal
			 */
			inline void set_media_id(const csf_string& newVal) {

				m_media_id = newVal;
			}
			/**
			 * <font color="#008000">异常描述信息</font>
			 * 
			 * @param newVal
			 */
			inline void set_description(const csf_string& newVal) {

				m_description = newVal;
			}

		private:
			/**
			 * 表示异常状态信息，<font color="#008000">表示状态码，多为公用状态码</font>
			 */
			css_status m_status = css_status_none;
			/**
			 * <font color="#008000">表示私有状态码，为平台自己的状态码</font>
			 */
			css_status m_private_status = css_status_none;
			/**
			 * <font color="#008000">媒体通道编码</font>
			 */
			csf_int32 m_channel_id = 0;
			/**
			 * <font color="#008000">异常发生的当前时间</font>
			 */
			csf::core::base::csf_time m_time = 0;
			/**
			 * <font color="#008000">异常发送时间</font>
			 */
			csf::core::base::csf_time m_send_time = 0;
			/**
			 * <font color="#008000">异常描述信息</font>
			 */
			csf_string m_description = "";
			/**
			 * <font color="#008000">表示播放会话ID，该ID表示一个会话</font>
			 */
			csf_string m_play_session = "";
			/**
			 * <font color="#008000">媒体编号ID</font>
			 */
			csf_string m_media_id = "";
			/**
			 * <font color="#008000">当前的会话id</font>
			 */
			csf_string m_session = "";

		};

	}

}
#endif // !defined(CSS_EXCEPTION_H_INCLUDED_)
