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
*Description: Interface(csf_task_interface) 表示任务的操作接口
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_INTERFACE_INCLUDED_)
#define CSF_TASK_INTERFACE_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * 表示任务的操作接口
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:51
				 */
				class csf_task_interface
				{

				public:
					csf_task_interface() {

					}

					virtual ~csf_task_interface() {

					}

					/**
					 * 表示处理接口，当只有is_process返回true后才能process。
					 */
					virtual csf_int32 process() =0;
					/**
					 * 表示是否进行处理,如果is_process返回true，才能执行process。
					 */
					virtual csf_bool is_process() =0;
					/**
					 * 表示处理接口，当只有is_delete返回true后才能process_delete。
					 */
					virtual csf_int32 process_delete() =0;
					/**
					 * 判断是否需要删除，如果is_delete返回true则删除task。
					 */
					virtual csf_bool is_delete() =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_INTERFACE_INCLUDED_)
