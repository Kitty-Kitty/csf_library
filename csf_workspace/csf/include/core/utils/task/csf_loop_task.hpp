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
*Date: 19-7月-2018 20:11:42
*
*Description: Class(csf_loop_task) 表示一个循环任务，这个任务将无即循环下去
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_LOOP_TASK_INCLUDED_)
#define CSF_LOOP_TASK_INCLUDED_

#include "csf_task.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * 表示一个循环任务，这个任务将无即循环下去
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:42
				 */
				class csf_loop_task : public csf::core::utils::task::csf_task
				{

				public:
					csf_loop_task();
					virtual ~csf_loop_task();

				};

			}

		}

	}

}
#endif // !defined(CSF_LOOP_TASK_INCLUDED_)
