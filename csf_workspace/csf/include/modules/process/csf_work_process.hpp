﻿/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: fangzhenmu@aliyun.com
*
*Author: fz
*
*Version: 1.0
*
*Date: 28-7月-2018 14:23:52
*
*Description: Class(csf_work_process) 表示工作进程内容，主要实现相关进程的处理
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_WORK_PROCESS_INCLUDED_)
#define CSF_WORK_PROCESS_INCLUDED_

#include "csf_process.hpp"

namespace csf
{
	namespace modules
	{
		namespace process
		{
			/**
			 * 表示工作进程内容，主要实现相关进程的处理
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 28-7月-2018 14:23:52
			 */
			class csf_work_process : public csf::core::module::device::csf_process
			{

			public:
				csf_work_process();
				virtual ~csf_work_process();

				cf_int32 init();
				cf_int32 start();
				cf_int32 stop();

			};

		}

	}

}
#endif // !defined(CSF_WORK_PROCESS_INCLUDED_)
