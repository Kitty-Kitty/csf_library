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
*Date: 19-7月-2018 20:11:52
*
*Description: Class(csf_times_task) 表示指定次数的任务，用于记录次数
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TIMES_TASK_INCLUDED_)
#define CSF_TIMES_TASK_INCLUDED_

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
				 * 表示指定次数的任务，用于记录次数
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:52
				 */
				class csf_times_task : public csf::core::utils::task::csf_task
				{

				public:
					csf_times_task();
					virtual ~csf_times_task();

					inline csf_uint32 get_times() {

						return m_times;
					}
					/**
					 * 表示处理接口，当只有is_process返回true后才能process。
					 */
					virtual csf_int32 process();
					/**
					 * 表示是否进行处理,如果is_process返回true，才能执行process。
					 */
					virtual csf_bool is_process();
					/**
					 * 
					 * @param newVal
					 */
					inline void set_times(csf_uint32 newVal) {

						m_times = newVal;
					}
					/**
					 * 表示当前已经运行的次数计数
					 */
					inline csf_uint32 get_sequence() {

						return m_sequence;
					}
					/**
					 * 判断是否需要删除，如果is_delete返回true则删除task。
					 */
					virtual csf_bool is_delete();
					/**
					 * 表示当前已经运行的次数计数
					 * 
					 * @param newVal
					 */
					inline void set_sequence(csf_uint32 newVal) {

						m_sequence = newVal;
					}

				private:
					/**
					 * 表示当前已经运行的次数计数
					 */
					csf_uint32 m_sequence = 0;
					/**
					 * 表示最大的运行次数
					 */
					csf_uint32 m_times = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_TIMES_TASK_INCLUDED_)
