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
*Date: 29-7��-2018 15:13:21
*
*Description: Class(csf_udp_connect) ��ʾudp����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_UDP_CONNECT_INCLUDED_)
#define CSF_UDP_CONNECT_INCLUDED_

#include "csf_dgram_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾudp����
			 * @author f
			 * @version 1.0
			 * @created 29-7��-2018 15:13:21
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
#endif // !defined(CSF_UDP_CONNECT_INCLUDED_)
