/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_linux_network.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Class(csf_linux_network) 表示描述linux的网络信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_LINUX_NETWORK_H_INCLUDED_)
#define CSF_LINUX_NETWORK_H_INCLUDED_

#include "csf_network.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 表示描述linux的网络信息
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:55
				 */
				class csf_linux_network : public csf::core::system::platform::csf_network
				{

				public:
					csf_linux_network();
					virtual ~csf_linux_network();

				};

			}

		}

	}

}
#endif // !defined(CSF_LINUX_NETWORK_H_INCLUDED_)
