/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_windows_platform.hpp
*
*Version: 1.0
*
*Date: 07-1月-2020 13:49:56
*
*Description: Class(csf_windows_platform) 表示windows系统描述信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_WINDOWS_PLATFORM_H_INCLUDED_)
#define CSF_WINDOWS_PLATFORM_H_INCLUDED_

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
				 * 表示windows系统描述信息
				 * @author f
				 * @version 1.0
				 * @created 07-1月-2020 13:49:56
				 */
				class csf_windows_platform : public csf::core::system::platform::csf_platform
				{

				public:
					csf_windows_platform();
					virtual ~csf_windows_platform();

				};

			}

		}

	}

}
#endif // !defined(CSF_WINDOWS_PLATFORM_H_INCLUDED_)
