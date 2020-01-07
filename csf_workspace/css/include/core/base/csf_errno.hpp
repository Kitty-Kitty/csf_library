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
*Date: 27-6��-2018 17:28:41
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
			 * ��ʾcsfϵͳ�Ĵ����룬�ô����뽫����ϵͳ��errno���ݡ�
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:41
			 */
			enum csf_errno
			{
				/**
				 * ��ʾδ֪�Ĵ���Ҳ��ϵͳ����Ŀ�ʼ��š�
				 */
				csf_errno_none = 0x80010000
			};

		}

	}

}
#endif // !defined(CSF_ERRNO_INCLUDED_)
