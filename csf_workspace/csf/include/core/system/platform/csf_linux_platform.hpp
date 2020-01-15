/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_linux_platform.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:55
*
*Description: Class(csf_linux_platform) 表示linux系统描述
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_LINUX_PLATFORM_H_INCLUDED_)
#define CSF_LINUX_PLATFORM_H_INCLUDED_

#include "csf_platform.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace platform
			{
				/**
				 * 表示linux系统描述
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:55
				 */
				class csf_linux_platform : public csf::core::system::platform::csf_platform
				{

				public:
					csf_linux_platform();
					virtual ~csf_linux_platform();

				};

			}

		}

	}

}
#endif // !defined(CSF_LINUX_PLATFORM_H_INCLUDED_)
