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
*Date: 29-7月-2018 15:13:09
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
	namespace modules
	{
		namespace connect
		{
			/**
			 * @author f
			 * @version 1.0
			 * @created 29-7月-2018 15:13:09
			 */
			class csf_ip_url : public csf::core::module::connect::csf_url
			{

			public:
				inline explicit csf_ip_url()
					: csf_url(csf_url_type_ip)
					, m_ip("")
					, m_port(0) {

				}

				inline virtual ~csf_ip_url() {

				}

				/**
				 * 表示IP地址字符串
				 */
				inline csf_string & get_ip() {

					return m_ip;
				}
				/**
				 * 表示IP地址字符串
				 * 
				 * @param newVal
				 */
				inline void set_ip(const csf_string& newVal) {

					m_ip = newVal;
				}
				/**
				 * 获取端口数据
				 */
				inline csf::core::base::csf_ushort get_port() {

					return m_port;
				}
				/**
				 * 设置端口数据
				 * 
				 * @param newVal
				 */
				inline void set_port(const csf::core::base::csf_ushort newVal) {

					m_port = newVal;
				}
				/**
				 * 表示解析地址函数
				 * 
				 * @param url    表示url地址字符串数据
				 */
				virtual csf_int32 parse(const csf_string& url);
				/**
				 * 表示IP地址字符串
				 * 
				 * @param newVal
				 */
				inline void set_ip(const csf_char* newVal) {

					m_ip = newVal;
				}
				/**
				 * 表示解析地址函数
				 * 
				 * @param url    表示url地址字符串数据
				 */
				virtual csf_int32 parse(const csf_char* url);

			private:
				/**
				 * 表示IP地址字符串
				 */
				csf::core::base::csf_string m_ip = "";
				/**
				 * 表示网络地址的端口数据
				 */
				csf::core::base::csf_ushort m_port = 0;

			};

		}

	}

}
#endif // !defined(CSF_IP_URL_INCLUDED_)
