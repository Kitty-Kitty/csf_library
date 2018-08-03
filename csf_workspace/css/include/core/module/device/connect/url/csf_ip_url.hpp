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
*Date: 11-7��-2018 22:36:10
*
*Description: Class(csf_ip_url) 
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_IP_URL_INCLUDED_)
#define CSF_IP_URL_INCLUDED_

#include "csf_url.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * @author f
				 * @version 1.0
				 * @created 11-7��-2018 22:36:10
				 */
				class csf_ip_url : public csf_url
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
					 * @param newVal
					 */
					inline void set_ip(const csf_string& newVal) {

						m_ip = newVal;
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
					 * @param newVal
					 */
					inline void set_port(const csf::core::base::csf_ushort newVal) {

						m_port = newVal;
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
					 * @param newVal
					 */
					inline void set_ip(const csf_char* newVal) {

						m_ip = newVal;
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

}
#endif // !defined(CSF_IP_URL_INCLUDED_)
