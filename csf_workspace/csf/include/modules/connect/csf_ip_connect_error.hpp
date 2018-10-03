/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect_error.hpp
*
*Version: 1.0
*
*Date: 02-10月-2018 18:50:10
*
*Description: Class(csf_ip_connect_error) 表示ip_connect的错误信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_ERROR_H_INCLUDED_)
#define CSF_IP_CONNNECT_ERROR_H_INCLUDED_

#include "csf_boost_asio.hpp"
#include "csf_connect_error.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示ip_connect的错误信息
			 * @author f
			 * @version 1.0
			 * @created 02-10月-2018 18:50:10
			 */
			class csf_ip_connect_error : public csf::core::module::connect::csf_connect_error
			{

			public:
				inline explicit csf_ip_connect_error() {

				}
				virtual ~csf_ip_connect_error() {

				}

				/**
				 * 
				 * @param boost_error    表示boost error_code错误
				 */
				inline explicit csf_ip_connect_error(const boost::system::error_code& boost_error) {
					set_error_code(boost_error);
				}
				/**
				 * 
				 * @param boost_error    表示boost error_code错误
				 */
				inline csf_void set_error_code(const boost::system::error_code& boost_error) {
					set_error(boost_error.value(), boost::system::system_error(boost_error).what());
				}

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_ERROR_H_INCLUDED_)
