/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_ms_information.hpp
*
*Version: 1.0
*
*Date: 07-10月-2018 16:50:30
*
*Description: Class(css_ms_information) 表示媒体服务器的信息内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_MS_INFORMATION_H_INCLUDED_)
#define CSS_MS_INFORMATION_H_INCLUDED_

#include "csf_ip_url.hpp"
#include "css_information.hpp"

namespace css
{
	namespace modules
	{
		namespace media_server
		{
			namespace base
			{
				/**
				 * 表示媒体服务器的信息内容
				 * @author f
				 * @version 1.0
				 * @created 07-10月-2018 16:50:30
				 */
				class css_ms_information : public css::core::css_information
				{

				public:
					css_ms_information();
					virtual ~css_ms_information();

					/**
					 * 表示组播地址信息
					 */
					inline csf::modules::connect::csf_ip_url get_multicast_url() {

						return m_multicast_url;
					}
					/**
					 * 表示组播地址信息
					 * 
					 * @param newVal
					 */
					inline void set_multicast_url(const csf_ip_url& newVal) {

						m_multicast_url = newVal;
					}

				private:
					/**
					 * 表示组播地址信息
					 */
					csf::modules::connect::csf_ip_url m_multicast_url;

				};

			}

		}

	}

}
#endif // !defined(CSS_MS_INFORMATION_H_INCLUDED_)
