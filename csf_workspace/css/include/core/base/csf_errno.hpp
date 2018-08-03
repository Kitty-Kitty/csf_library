/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_errno.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:41
*
*Description: Enumeration(csf_errno)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ERRNO_INCLUDED_)
#define CSF_ERRNO_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf系统的错误码，该错误码将兼容系统的errno内容。
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:41
			 */
			enum csf_errno
			{
				/**
				 * 表示未知的错误，也是系统错误的开始编号。
				 */
				csf_errno_none = 0x80010000
			};

		}

	}

}
#endif // !defined(CSF_ERRNO_INCLUDED_)
