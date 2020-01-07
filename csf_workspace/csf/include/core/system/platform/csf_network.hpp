/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_network.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Class(csf_network) 表示描述网络信息类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_NETWORK_H_INCLUDED_)
#define CSF_NETWORK_H_INCLUDED_

#include "csf_network_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 表示描述网络信息类
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:55
				 */
				class csf_network : public csf::core::system::platform::csf_network_interface
				{

				public:
					csf_network();
					virtual ~csf_network();

				};

			}

		}

	}

}
#endif // !defined(CSF_NETWORK_H_INCLUDED_)
