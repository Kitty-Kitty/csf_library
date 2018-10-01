/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_url.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:56
*
*Description: Class(csf_url) url��ַ��Ϣ�Ļ�������Ϣ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_URL_H_INCLUDED_)
#define CSF_URL_H_INCLUDED_

#include "csf_base_include.h"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * url��ַ��Ϣ�Ļ�������Ϣ
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:56
				 */
				class csf_url
				{

				public:
					/**
					 * ��ʾurl����
					 * @author f
					 * @version 1.0
					 * @created 01-10��-2018 12:54:56
					 */
					typedef enum csf_url_type_enum
					{
						/**
						 * ��ʾ�յ�ַ
						 */
						csf_url_type_none = 0,
						/**
						 * ��ʾIP��ַ
						 */
						csf_url_type_ip,
						/**
						 * ��ʾ���ڵ�ַ
						 */
						csf_url_type_serial
					} csf_url_type;


					csf_url();
					virtual ~csf_url();

					/**
					 * 
					 * @param type    ��ʾ���ӵ�ַ����
					 */
					inline explicit csf_url(csf::core::module::connect::csf_url::csf_url_type type) {

					}
					/**
					 * ��ʾurl��ַ��������Ϣ
					 */
					inline csf::core::module::connect::csf_url::csf_url_type get_type() {

						return m_type;
					}
					/**
					 * ��ʾ������ַ����
					 * 
					 * @param url    ��ʾurl��ַ�ַ�������
					 */
					inline virtual csf_int32 parse(csf_string& url) {

						return 0;
					}
					/**
					 * ��ʾurl�������ַ�������
					 */
					inline csf_string & get_url() {

						return m_url;
					}
					/**
					 * ��ʾurl�������ַ�������
					 * 
					 * @param new_value
					 */
					inline csf_void set_url(csf_string& new_value) {

						m_url = new_value;
					}
					/**
					 * ��ʾurl�������ַ�������
					 * 
					 * @param new_value
					 */
					inline csf_void set_url(csf_char* new_value) {

						m_url = new_value;
					}
					/**
					 * ��ʾ������ַ����
					 * 
					 * @param url    ��ʾurl��ַ�ַ�������
					 */
					inline virtual csf_int32 parse(csf_char* url) {

						return 0;
					}

				protected:
					/**
					 * ��ʾurl��ַ��������Ϣ
					 * 
					 * @param new_value
					 */
					inline csf_void set_type(csf::core::module::connect::csf_url::csf_url_type new_value) {

						m_type = new_value;
					}

				private:
					/**
					 * ��ʾurl�������ַ�������
					 */
					csf::core::base::csf_string m_url = "";
					/**
					 * ��ʾurl��ַ��������Ϣ
					 */
					csf::core::module::connect::csf_url::csf_url_type m_type = csf_url_type_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_URL_H_INCLUDED_)
