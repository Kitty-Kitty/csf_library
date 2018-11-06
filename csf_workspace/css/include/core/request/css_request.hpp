/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_request.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:30
*
*Description: Class(css_request) 表示css系统请求内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_REQUEST_H_INCLUDED_)
#define CSS_REQUEST_H_INCLUDED_

#include "csf_connect.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示css系统请求内容
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:30
		 */
		class css_request
		{

		public:
			/**
			 * 表示请求类型
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:30
			 */
			enum css_request_type
			{
				/**
				 * 表示未知的请求类型
				 */
				css_request_type_none = 0x00000000,
				/**
				 * 表示semh请求类型
				 */
				css_request_type_semh = 0x00000001,
				/**
				 * 表示ptp请求类型
				 */
				css_request_type_ptp = 0x00000001
			};

			/**
			 * 表示请求的状态
			 * @author f
			 * @version 1.0
			 * @created 07-10月-2018 16:50:30
			 */
			enum css_request_status
			{
				/**
				 * 表示未知的状态
				 */
				css_request_status_none = 0x00000000
			};


			css_request();
			virtual ~css_request();

			/**
			 * 表示请求连接信息
			 */
			inline csf_connect* get_connect() {

				return m_connect;
			}
			/**
			 * 表示请求连接信息
			 * 
			 * @param newVal
			 */
			inline csf_void set_connect(const csf_connect* newVal) {

				m_connect = (csf_connect*)newVal;
			}
			/**
			 * 表示请求的描述信息
			 */
			inline csf_string& get_description() {

				return m_description;
			}
			/**
			 * 表示请求的描述信息
			 * 
			 * @param newVal
			 */
			inline csf_void set_description(const csf_string& newVal) {

				m_description = newVal;
			}
			/**
			 * 表示请求的描述信息
			 * 
			 * @param newVal
			 */
			inline csf_void set_description(const csf_char* newVal) {

				m_description = newVal;
			}
			/**
			 * 表示请求的类型
			 */
			inline css::core::css_request::css_request_type get_type() {

				return m_type;
			}
			/**
			 * 表示请求的类型
			 * 
			 * @param newVal
			 */
			inline void set_type(const css::core::css_request::css_request_type newVal) {

				m_type = newVal;
			}
			/**
			 * 表示请求的状态
			 */
			inline css_request_status get_status() {

				return m_status;
			}
			/**
			 * 表示请求的状态
			 * 
			 * @param newVal
			 */
			inline void set_status(const css_request_status newVal) {

				m_status = newVal;
			}

		private:
			/**
			 * 表示请求的描述信息
			 */
			csf_string m_description = "";
			/**
			 * 表示请求的类型
			 */
			css::core::css_request::css_request_type m_type = css_request_type_none;
			/**
			 * 表示请求的状态
			 */
			css_request_status m_status = css_request_status_none;
			/**
			 * 表示网络连接描述信息
			 */
			csf::core::module::connect::csf_connect *m_connect;

		};

	}

}
#endif // !defined(CSS_REQUEST_H_INCLUDED_)
