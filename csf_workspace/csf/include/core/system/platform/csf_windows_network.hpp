/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_windows_network.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:56
*
*Description: Class(csf_windows_network) 表示windows网络信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_WINDOWS_NETWORK_H_INCLUDED_)
#define CSF_WINDOWS_NETWORK_H_INCLUDED_

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
				 * 表示windows网络信息
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:56
				 */
				class csf_windows_network : public csf::core::system::platform::csf_network
				{

				public:
					csf_windows_network();
					virtual ~csf_windows_network();

				};

			}

		}

	}

}
#endif // !defined(CSF_WINDOWS_NETWORK_H_INCLUDED_)
