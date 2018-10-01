/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_url.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_url) 
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_URL_H_INCLUDED_)
#define CSF_IP_URL_H_INCLUDED_

#include "csf_url.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * @author f
			 * @version 1.0
			 * @created 01-10��-2018 12:54:43
			 */
			class csf_ip_url : public csf::core::module::connect::csf_url
			{

			public:
				csf_ip_url();
				virtual ~csf_ip_url();

				/**
				 * ��ʾIP��ַ�ַ���
				 */
				inline csf_string & get_ip() {

					return m_ip;
				}
				/**
				 * ��ʾIP��ַ�ַ���
				 * 
				 * @param new_value
				 */
				inline void set_ip(const csf_string& new_value) {

					m_ip = new_value;
				}
				/**
				 * ��ȡ�˿�����
				 */
				inline csf::core::base::csf_ushort get_port() {

					return m_port;
				}
				/**
				 * ���ö˿�����
				 * 
				 * @param new_value
				 */
				inline void set_port(const csf::core::base::csf_ushort new_value) {

					m_port = new_value;
				}
				/**
				 * ��ʾ������ַ����
				 * 
				 * @param url    ��ʾurl��ַ�ַ�������
				 */
				virtual csf_int32 parse(const csf_string& url);
				/**
				 * ��ʾIP��ַ�ַ���
				 * 
				 * @param new_value
				 */
				inline void set_ip(const csf_char* new_value) {

					m_ip = new_value;
				}
				/**
				 * ��ʾ������ַ����
				 * 
				 * @param url    ��ʾurl��ַ�ַ�������
				 */
				virtual csf_int32 parse(const csf_char* url);

			private:
				/**
				 * ��ʾIP��ַ�ַ���
				 */
				csf::core::base::csf_string m_ip = "";
				/**
				 * ��ʾ�����ַ�Ķ˿�����
				 */
				csf::core::base::csf_ushort m_port = 0;

			};

		}

	}

}
#endif // !defined(CSF_IP_URL_H_INCLUDED_)
