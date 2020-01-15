/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 19-7月-2018 20:11:51
*
*Description: Class(csf_thread) 表示线程类
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_THREAD_INCLUDED_)
#define CSF_THREAD_INCLUDED_

#include "csf_thread_group.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				/**
				 * 表示线程类
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:51
				 */
				class csf_thread
				{

				public:
					csf_thread();
					virtual ~csf_thread();

				private:
					/**
					 * 表示线程管理池
					 */
					csf::core::utils::thread::csf_thread_group *m_thread_group;

				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_INCLUDED_)
