/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_udp_connect.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:53
*
*Description: Class(csf_udp_connect)
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
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示udp连接
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:53
				 */
				class csf_udp_connect : public csf::core::module::device::csf_dgram_connect
				{

				public:
					csf_udp_connect();
					virtual ~csf_udp_connect();

				};

			}

		}

	}

}
#endif // !defined(CSF_UDP_CONNECT_INCLUDED_)
