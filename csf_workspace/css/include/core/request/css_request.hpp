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
*Date: 07-10��-2018 16:50:30
*
*Description: Class(css_request) ��ʾcssϵͳ��������
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
		 * ��ʾcssϵͳ��������
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:30
		 */
		class css_request
		{

		public:
			/**
			 * ��ʾ��������
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:30
			 */
			enum css_request_type
			{
				/**
				 * ��ʾδ֪����������
				 */
				css_request_type_none = 0x00000000,
				/**
				 * ��ʾsemh��������
				 */
				css_request_type_semh = 0x00000001,
				/**
				 * ��ʾptp��������
				 */
				css_request_type_ptp = 0x00000001
			};

			/**
			 * ��ʾ�����״̬
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:30
			 */
			enum css_request_status
			{
				/**
				 * ��ʾδ֪��״̬
				 */
				css_request_status_none = 0x00000000
			};


			css_request();
			virtual ~css_request();

			/**
			 * ��ʾ����������Ϣ
			 */
			inline csf_connect* get_connect() {

				return m_connect;
			}
			/**
			 * ��ʾ����������Ϣ
			 * 
			 * @param newVal
			 */
			inline csf_void set_connect(const csf_connect* newVal) {

				m_connect = (csf_connect*)newVal;
			}
			/**
			 * ��ʾ�����������Ϣ
			 */
			inline csf_string& get_description() {

				return m_description;
			}
			/**
			 * ��ʾ�����������Ϣ
			 * 
			 * @param newVal
			 */
			inline csf_void set_description(const csf_string& newVal) {

				m_description = newVal;
			}
			/**
			 * ��ʾ�����������Ϣ
			 * 
			 * @param newVal
			 */
			inline csf_void set_description(const csf_char* newVal) {

				m_description = newVal;
			}
			/**
			 * ��ʾ���������
			 */
			inline css::core::css_request::css_request_type get_type() {

				return m_type;
			}
			/**
			 * ��ʾ���������
			 * 
			 * @param newVal
			 */
			inline void set_type(const css::core::css_request::css_request_type newVal) {

				m_type = newVal;
			}
			/**
			 * ��ʾ�����״̬
			 */
			inline css_request_status get_status() {

				return m_status;
			}
			/**
			 * ��ʾ�����״̬
			 * 
			 * @param newVal
			 */
			inline void set_status(const css_request_status newVal) {

				m_status = newVal;
			}

		private:
			/**
			 * ��ʾ�����������Ϣ
			 */
			csf_string m_description = "";
			/**
			 * ��ʾ���������
			 */
			css::core::css_request::css_request_type m_type = css_request_type_none;
			/**
			 * ��ʾ�����״̬
			 */
			css_request_status m_status = css_request_status_none;
			/**
			 * ��ʾ��������������Ϣ
			 */
			csf::core::module::connect::csf_connect *m_connect;

		};

	}

}
#endif // !defined(CSS_REQUEST_H_INCLUDED_)
