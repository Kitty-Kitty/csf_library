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
*Date: 01-10月-2018 12:54:43
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
			 * @created 01-10月-2018 12:54:43
			 */
			class csf_ip_url : public csf::core::module::connect::csf_url
			{

			public:
				csf_ip_url();
				virtual ~csf_ip_url();

				/**
				 * 表示IP地址字符串
				 */
				inline csf_string & get_ip() {

					return m_ip;
				}
				/**
				 * 表示IP地址字符串
				 * 
				 * @param new_value
				 */
				inline void set_ip(const csf_string& new_value) {

					m_ip = new_value;
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
				 * @param new_value
				 */
				inline void set_port(const csf::core::base::csf_ushort new_value) {

					m_port = new_value;
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
				 * @param new_value
				 */
				inline void set_ip(const csf_char* new_value) {

					m_ip = new_value;
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
#endif // !defined(CSF_IP_URL_H_INCLUDED_)
