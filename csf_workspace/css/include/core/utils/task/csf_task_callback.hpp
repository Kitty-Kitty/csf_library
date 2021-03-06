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
*Description: Class(csf_task_callback) 表示任务的处理回调函数
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_CALLBACK_INCLUDED_)
#define CSF_TASK_CALLBACK_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * 表示任务的处理回调函数
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:51
				 */
				class csf_task_callback
				{

				public:
					csf_task_callback();
					virtual ~csf_task_callback();

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_CALLBACK_INCLUDED_)
