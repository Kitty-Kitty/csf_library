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
*Date: 07-10��-2018 16:50:31
*
*Description: Class(css_return) ��ʾcss������Ϣ
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
		 * ��ʾcss������Ϣ
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:31
		 */
		class css_return
		{

		public:
			css_return();
			virtual ~css_return();

			/**
			 * ��ʾcss���ص�host�豸id
			 */
			inline csf_string get_host_id() {

				return m_host_id;
			}
			/**
			 * <font color="#008000">��ʾ�����ԭ��</font>
			 */
			inline csf_string get_reason() {

				return m_reason;
			}
			/**
			 * <font color="#008000">��ʾ�����ԭ��</font>
			 * 
			 * @param newVal
			 */
			inline void set_reason(const csf_string newVal) {

				m_reason = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�豸��״̬����</font>
			 */
			inline csf_int32 get_status() {

				return m_status;
			}
			/**
			 * <font color="#008000">��ʾ�豸��״̬����</font>
			 * 
			 * @param newVal
			 */
			inline void set_status(const csf_int32 newVal) {

				m_status = newVal;
			}
			/**
			 * ��ʾcss���ص�host�豸id
			 */
			inline css::core::css_id get_id() {

				return m_id;
			}
			/**
			 * ��ʾcss���ص�host�豸id
			 * 
			 * @param newVal
			 */
			inline void set_id(css_id& newVal) {

				m_id = newVal;
			}
			/**
			 * ��ʾcss���ص�host�豸id
			 * 
			 * @param newVal
			 */
			inline void set_id(csf_string& newVal) {

				m_id = newVal;
			}
			/**
			 * ��ʾcss���ص�host�豸id
			 * 
			 * @param newVal
			 */
			inline void set_id(csf_char* newVal) {

				m_id = newVal;
			}

		private:
			/**
			 * <font color="#008000">��ʾ�����ԭ��</font>
			 */
			csf_string m_reason = "";
			/**
			 * <font color="#008000">��ʾ�豸��״̬����</font>
			 */
			csf_int32 m_status = 0;
			/**
			 * ��ʾ�豸��id��Ϣ
			 */
			css::core::css_id m_id;

		};

	}

}
#endif // !defined(CSS_RETURN_H_INCLUDED_)
