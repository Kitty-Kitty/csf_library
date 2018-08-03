/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task_type.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:51
*
*Description: Enumeration(csf_task_type)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_TYPE_INCLUDED_)
#define CSF_TASK_TYPE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * 表示任务的类型
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:51
				 */
				enum csf_task_type
				{
					/**
					 * 表示未知的任务状态值
					 */
					m_csf_task_type_none = 0x00000000,
					/**
					 * 表示只执行一次的任务状态值
					 */
					m_csf_task_type_once = 0x00010000,
					/**
					 * 表示循环执行的任务，该任务将无限循环下去
					 */
					m_csf_task_type_loop = 0x00020000,
					/**
					 * 表示一个无限循环任务，这个任务在返回错误时，就会被删除
					 */
					m_csf_task_type_loop_broken = csf_task_type_loop | 0x00000100,
					/**
					 * 表示指定次数的任务，用于记录次数
					 */
					m_csf_task_type_times = 0x00040000,
					/**
					 * 表示根据时间的任务
					 */
					m_csf_task_type_time = 0x00080000
				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_TYPE_INCLUDED_)
