/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_tcp_connect.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:51
*
*Description: Class(csf_tcp_connect)
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
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示tcp连接
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:51
				 */
				class csf_tcp_connect : public csf::core::module::device::csf_stream_connect
				{

				public:
					csf_tcp_connect();
					virtual ~csf_tcp_connect();

				};

			}

		}

	}

}
#endif // !defined(CSF_TCP_CONNECT_INCLUDED_)
