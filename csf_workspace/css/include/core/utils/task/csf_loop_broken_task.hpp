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
*Date: 19-7��-2018 20:11:42
*
*Description: Class(csf_loop_broken_task) ��ʾһ������ѭ��������������ڷ��ش���ʱ���ͻᱻɾ��
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_LOOP_BROKEN_TASK_INCLUDED_)
#define CSF_LOOP_BROKEN_TASK_INCLUDED_

#include "csf_loop_task.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * ��ʾһ������ѭ��������������ڷ��ش���ʱ���ͻᱻɾ��
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:42
				 */
				class csf_loop_broken_task : public csf::core::utils::task::csf_loop_task
				{

				public:
					csf_loop_broken_task();
					virtual ~csf_loop_broken_task();

				};

			}

		}

	}

}
#endif // !defined(CSF_LOOP_BROKEN_TASK_INCLUDED_)
