/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect_timeout.hpp
*
*Version: 1.0
*
*Date: 21-10月-2018 14:31:55
*
*Description: Class(csf_ip_connect_timeout) 表示ip_connect的超时对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNECT_TIMEOUT_H_INCLUDED_)
#define CSF_IP_CONNECT_TIMEOUT_H_INCLUDED_

#include "csf_boost_asio.hpp"
#include "csf_connect_timeout.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示ip_connect的超时对象
			 * @author f
			 * @version 1.0
			 * @created 21-10月-2018 14:31:55
			 */
			class csf_ip_connect_timeout : public csf::core::module::connect::csf_connect_timeout
			{
			public:
				/**
				* 表示离线定时器
				* @author f
				* @version 1.0
				* @updated 01-10月-2018 15:12:05
				*/
				typedef boost::asio::deadline_timer			csf_deadline_timer;
			public:
				virtual ~csf_ip_connect_timeout() {

				}
				/**
				* 主要功能是：根据io_service创建一个timeout对象
				* 返回：无
				*
				* @param io_service    表示boost的io_service对象
				*/
				inline explicit csf_ip_connect_timeout(boost::asio::io_service& io_service)
					: m_deadline_timer(io_service) {

				}
				/**
				* 主要功能是：根据io_service和基体信息创建一个timeout对象
				* 返回：无
				*
				* @param io_service    表示boost的io_service对象
				* @param time    表示当前超时的时间数值，单位为毫秒（ms）
				*
				* @param handle    表示超时后的回调函数
				*/
				inline explicit csf_ip_connect_timeout(boost::asio::io_service& io_service
					, const csf_uint32 time
					, const csf::core::module::connect::csf_connect_callback handle)
					: csf_connect_timeout(time, handle)
					, m_deadline_timer(io_service) {

				}
				/**
				* 表示超时定时器对象
				*/
				inline csf_deadline_timer& get_deadline_timer() {

					return m_deadline_timer;
				}

			private:
				/**
				 * 表示超时定时器对象
				 */
				csf_deadline_timer m_deadline_timer;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNECT_TIMEOUT_H_INCLUDED_)
