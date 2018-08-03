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
*Date: 19-7��-2018 20:11:47
*
*Description: Class(csf_once_task) ��ʾִֻ��һ�ε�����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ONCE_TASK_INCLUDED_)
#define CSF_ONCE_TASK_INCLUDED_

#include "csf_times_task.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾִֻ��һ�ε�����
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:47
				 */
				class csf_once_task : public csf::core::utils::task::csf_times_task
				{

				public:
					csf_once_task();
					virtual ~csf_once_task();

				};

			}

		}

	}

}
#endif // !defined(CSF_ONCE_TASK_INCLUDED_)
