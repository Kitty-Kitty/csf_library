﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_ipv6_url.hpp
*
*Version: 1.0
*
*Date: 13-3月-2019 17:52:25
*
*Description: Class(csf_ipv6_url) ipv6格式的url地址处理类，地址格式仅支持（[ip]:port）格式。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IPV6_URL_H_INCLUDED_)
#define CSF_IPV6_URL_H_INCLUDED_

#include "csf_ip_url.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			
			/************************************************************************/
			/* ipv6地址的间隔符号														*/
			/************************************************************************/
			#define csf_ipv6_url_spacer						':'
			/************************************************************************/
			/* ipv6地址的间隔符号的最少数量     										*/
			/************************************************************************/
			#define csf_ipv6_url_min_spacer_number			2
			/**
			 * ipv6格式的url地址处理类，地址格式仅支持（[ip]:port）格式。
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 13-3月-2019 17:52:25
			 */
			class csf_ipv6_url : public csf::modules::connect::csf_ip_url
			{

			public:
				csf_ipv6_url()
					:csf_ip_url(csf::modules::connect::csf_ip_url::csf_ip_type_v6) {

				}
				virtual ~csf_ipv6_url() {

				}

				/**
				 * 功能：
				 *    表示解析地址函数。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:
				 * 80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 * 
				 * 返回：
				 *    0  ：表示成功
				 *    非0：表示错误
				 * 
				 * @param url    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				virtual csf_int32 parse(const csf_string& url);
			protected:
				/**
				 * 功能：
				 *    对ip地址的格式合法性校验。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.
				 * 10。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 * 
				 * 返回：
				 *    true表示成功；
				 *    false表示失败；
				 * 
				 * @param ip    表示网络地址格式，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.
				 * 168.1.10:80
				 */
				virtual csf_bool check_ip(const csf_string& ip);

			};

		}

	}

}
#endif // !defined(CSF_IPV6_URL_H_INCLUDED_)
