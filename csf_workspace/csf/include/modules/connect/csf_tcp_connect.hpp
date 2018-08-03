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
*Date: 29-7��-2018 15:13:20
*
*Description: Class(csf_tcp_connect) ��ʾtcp����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TCP_CONNECT_INCLUDED_)
#define CSF_TCP_CONNECT_INCLUDED_

#include "csf_stream_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * ��ʾtcp����
			 * @author f
			 * @version 1.0
			 * @created 29-7��-2018 15:13:20
			 */
			class csf_tcp_connect : public csf::modules::connect::csf_stream_connect
			{

			public:
				csf_tcp_connect();
				virtual ~csf_tcp_connect();

			};

		}

	}

}
#endif // !defined(CSF_TCP_CONNECT_INCLUDED_)
