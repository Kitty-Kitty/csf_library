/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_return.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:31
*
*Description: Class(css_return) 表示css返回信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_RETURN_H_INCLUDED_)
#define CSS_RETURN_H_INCLUDED_

#include "css_id.hpp"

namespace css
{
	namespace core
	{
		/**
		 * 表示css返回信息
		 * @author f
		 * @version 1.0
		 * @created 07-10月-2018 16:50:31
		 */
		class css_return
		{

		public:
			css_return();
			virtual ~css_return();

			/**
			 * 表示css返回的host设备id
			 */
			inline csf_string get_host_id() {

				return m_host_id;
			}
			/**
			 * <font color="#008000">表示错误的原因</font>
			 */
			inline csf_string get_reason() {

				return m_reason;
			}
			/**
			 * <font color="#008000">表示错误的原因</font>
			 * 
			 * @param newVal
			 */
			inline void set_reason(const csf_string newVal) {

				m_reason = newVal;
			}
			/**
			 * <font color="#008000">表示设备的状态编码</font>
			 */
			inline csf_int32 get_status() {

				return m_status;
			}
			/**
			 * <font color="#008000">表示设备的状态编码</font>
			 * 
			 * @param newVal
			 */
			inline void set_status(const csf_int32 newVal) {

				m_status = newVal;
			}
			/**
			 * 表示css返回的host设备id
			 */
			inline css::core::css_id get_id() {

				return m_id;
			}
			/**
			 * 表示css返回的host设备id
			 * 
			 * @param newVal
			 */
			inline void set_id(css_id& newVal) {

				m_id = newVal;
			}
			/**
			 * 表示css返回的host设备id
			 * 
			 * @param newVal
			 */
			inline void set_id(csf_string& newVal) {

				m_id = newVal;
			}
			/**
			 * 表示css返回的host设备id
			 * 
			 * @param newVal
			 */
			inline void set_id(csf_char* newVal) {

				m_id = newVal;
			}

		private:
			/**
			 * <font color="#008000">表示错误的原因</font>
			 */
			csf_string m_reason = "";
			/**
			 * <font color="#008000">表示设备的状态编码</font>
			 */
			csf_int32 m_status = 0;
			/**
			 * 表示设备的id信息
			 */
			css::core::css_id m_id;

		};

	}

}
#endif // !defined(CSS_RETURN_H_INCLUDED_)
