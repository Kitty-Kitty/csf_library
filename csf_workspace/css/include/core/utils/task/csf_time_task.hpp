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
*Description: Class(csf_time_task) 表示时间任务
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TIME_TASK_INCLUDED_)
#define CSF_TIME_TASK_INCLUDED_

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
				 * 表示时间任务
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:52
				 */
				class csf_time_task : public csf::core::utils::task::csf_task
				{

				public:
					csf_time_task();
					virtual ~csf_time_task();

					/**
					 * 表示处理接口，当只有is_process返回true后才能process。
					 */
					virtual csf_int32 process();
					/**
					 * 表示是否进行处理,如果is_process返回true，才能执行process。
					 */
					virtual csf_bool is_process();
					/**
					 * 判断是否需要删除，如果is_delete返回true则删除task。
					 */
					virtual csf_bool is_delete();
					/**
					 * 表示开始时间
					 */
					inline csf_uint64 get_begin() {

						return m_begin;
					}
					/**
					 * 表示开始时间
					 * 
					 * @param newVal
					 */
					inline void set_begin(csf_uint64 newVal) {

						m_begin = newVal;
					}
					/**
					 * 表示停止时间
					 */
					inline csf_uint64 get_end() {

						return m_end;
					}
					/**
					 * 表示停止时间
					 * 
					 * @param newVal
					 */
					inline void set_end(csf_uint64 newVal) {

						m_end = newVal;
					}

				private:
					/**
					 * 表示开始时间
					 */
					csf_uint64 m_begin = 0;
					/**
					 * 表示停止时间
					 */
					csf_uint64 m_end = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_TIME_TASK_INCLUDED_)
