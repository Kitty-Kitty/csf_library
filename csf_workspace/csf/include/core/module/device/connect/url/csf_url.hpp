/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 28-7��-2018 14:23:50
*
*Description: Class(csf_url) url��ַ��Ϣ�Ļ�������Ϣ
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_URL_INCLUDED_)
#define CSF_URL_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

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
				 * @created 28-7��-2018 14:23:50
				 */
				class csf_url
				{

				public:
					/**
					 * ��ʾurl����
					 * @author f
					 * @version 1.0
					 * @created 28-7��-2018 14:23:50
					 */
					enum csf_url_type
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
					};


					csf_url();
					virtual ~csf_url();

					/**
					 * 
					 * @param type    ��ʾ���ӵ�ַ����
					 */
					inline explicit csf_url(csf_url_type type) {

					}
					/**
					 * ��ʾurl��ַ��������Ϣ
					 */
					inline csf_url_type get_type() {

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
					 * @param newVal
					 */
					inline csf_void set_url(csf_string& newVal) {

						m_url = newVal;
					}
					/**
					 * ��ʾurl�������ַ�������
					 * 
					 * @param newVal
					 */
					inline csf_void set_url(csf_char* newVal) {

						m_url = newVal;
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
					 * @param newVal
					 */
					inline csf_void set_type(csf_url_type newVal) {

						m_type = newVal;
					}

				private:
					/**
					 * ��ʾurl�������ַ�������
					 */
					csf::core::base::csf_string m_url = "";
					/**
					 * ��ʾurl��ַ��������Ϣ
					 */
					csf_url_type m_type = csf_url_type_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_URL_INCLUDED_)
