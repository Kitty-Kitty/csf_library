/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_udp_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:55
*
*Description: Class(csf_udp_connect) 表示udp连接
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_UDP_CONNECT_H_INCLUDED_)
#define CSF_UDP_CONNECT_H_INCLUDED_

#include "csf_dgram_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示udp连接
			 * @author f
			 * @version 1.0
			 * @created 01-10月-2018 12:54:55
			 */
			class csf_udp_connect : public csf::modules::connect::csf_dgram_connect
			{

			public:
				csf_udp_connect();
				virtual ~csf_udp_connect();

			};

		}

	}

}
#endif // !defined(CSF_UDP_CONNECT_H_INCLUDED_)
