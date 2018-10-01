/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_tcp_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:54
*
*Description: Class(csf_tcp_connect) 表示tcp连接
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_TCP_CONNECT_H_INCLUDED_)
#define CSF_TCP_CONNECT_H_INCLUDED_

#include "csf_stream_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示tcp连接
			 * @author f
			 * @version 1.0
			 * @created 01-10月-2018 12:54:54
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
#endif // !defined(CSF_TCP_CONNECT_H_INCLUDED_)
