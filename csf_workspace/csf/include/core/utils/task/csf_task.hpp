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
*Date: 19-7月-2018 20:11:50
*
*Description: Class(csf_task) 表示定时任务
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_TASK_INCLUDED_)
#define CSF_TASK_INCLUDED_

#include "csf_task_callback.hpp"
#include "csf_task_delete_callback.hpp"
#include "csf_task_interface.hpp"
#include "csf_task_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace task
			{
				/**
				 * 表示定时任务
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:50
				 */
				class csf_task : public csf::core::utils::task::csf_task_interface
				{

				public:
					/**
					 * 表示定时器的状态值
					 * @author f
					 * @version 1.0
					 * @created 19-7月-2018 20:11:50
					 */
					enum csf_task_status
					{
						/**
						 * 表示未知的任务状态值
						 */
						csf_task_status_none = 0x00000000,
						/**
						 * 表示初始的任务状态值
						 */
						csf_task_status_init = 0x00010000,
						/**
						 * 表示开始的任务状态值
						 */
						csf_task_status_start = 0x00020000,
						/**
						 * 表示停止的任务状态值
						 */
						csf_task_status_stop = 0x00040000
					};

					/**
					 * 表示任务的类型
					 * @author f
					 * @version 1.0
					 * @created 19-7月-2018 20:11:50
					 */
					enum csf_task_type
					{
						/**
						 * 表示未知的任务状态值
						 */
						csf_task_type_none = 0x00000000,
						/**
						 * 表示只执行一次的任务状态值
						 */
						csf_task_type_once = 0x00010000,
						/**
						 * 表示循环执行的任务，该任务将无限循环下去
						 */
						csf_task_type_loop = 0x00020000,
						/**
						 * 表示一个无限循环任务，这个任务在返回错误时，就会被删除
						 */
						csf_task_type_loop_broken = csf_task_type_loop | 0x00000100,
						/**
						 * 表示指定次数的任务，用于记录次数
						 */
						csf_task_type_times = 0x00040000,
						/**
						 * 表示根据时间的任务
						 */
						csf_task_type_time = 0x00080000
					};


					csf_task();
					virtual ~csf_task();

					/**
					 * 根据task的类型和类型创建一个任务
					 * 
					 * @param manager    表示任务管理器的地址
					 * @param type    表示类型数值
					 * @param offset    表示任务间隔时间
					 * @param interval    任务执行的间隔时间
					 * @param callback    任务的执行回调函数
					 * @param delete_callback    任务删除的执行回调函数
					 */
					csf_task(const csf_task_manager* manager, const csf_task_type type, const csf_time offset, const csf_time interval, const csf_task_callback callback, const csf_task_delete_callback delete_callback = csf_null);
					/**
					 * 表示任务的类型数值
					 */
					inline csf_task_type get_type() {

						return m_type;
					}
					/**
					 * 表示任务的类型数值
					 * 
					 * @param new_value
					 */
					inline void set_type(const csf_task_type new_value) {

						m_type = new_value;
					}
					/**
					 * 表示任务的状态数值
					 */
					inline csf::core::utils::task::csf_task::csf_task_status get_status() {

						return m_status;
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
					 * 表示任务的状态数值
					 * 
					 * @param new_value
					 */
					inline void set_status(const csf::core::utils::task::csf_task::csf_task_status new_value) {

						m_status = new_value;
					}
					/**
					 * 表示任务的回调函数
					 */
					inline csf::core::utils::task::csf_task_callback get_callback() {

						return m_callback;
					}
					/**
					 * 判断是否需要删除，如果is_delete返回true则删除task。
					 */
					virtual csf_bool is_delete();
					/**
					 * 表示任务的回调函数
					 * 
					 * @param new_value
					 */
					inline void set_callback(const csf::core::utils::task::csf_task_callback new_value) {

						m_callback = new_value;
					}
					/**
					 * 表示任务删除后的回调函数
					 */
					inline csf::core::utils::task::csf_task_delete_callback get_delete_callback() {

						return m_delete_callback;
					}
					/**
					 * 表示任务删除后的回调函数
					 * 
					 * @param new_value
					 */
					inline void set_delete_callback(const csf::core::utils::task::csf_task_delete_callback new_value) {

						m_delete_callback = new_value;
					}
					/**
					 * 表示当前的时间关键数值，即当前时间
					 */
					inline csf_uint64 get_time() {

						return m_time;
					}
					/**
					 * 表示当前的时间关键数值，即当前时间
					 * 
					 * @param new_value
					 */
					inline void set_time(const csf_uint64 new_value) {

						m_time = new_value;
					}
					/**
					 * 表示第一次执行的偏移时间
					 */
					inline csf_uint64 get_offset() {

						return m_offset;
					}
					/**
					 * 表示第一次执行的偏移时间
					 * 
					 * @param new_value
					 */
					inline void set_offset(const csf_uint64 new_value) {

						m_offset = new_value;
					}
					/**
					 * 指向一个任务对象
					 * 
					 * @param new_value
					 */
					inline void set_task(const csf_task* new_value) {

						m_task = new_value;
					}
					/**
					 * 指向一个装饰者对象
					 */
					inline csf_task* get_decorator() {

						return m_decorator;
					}
					/**
					 * 表示任务的执行间隔时间
					 */
					inline csf_uint64 get_interval() {

						return m_interval;
					}
					/**
					 * 指向一个装饰者对象
					 * 
					 * @param new_value
					 */
					inline void set_decorator(const csf_task* new_value) {

						m_decorator = new_value;
					}
					/**
					 * 表示任务的执行间隔时间
					 * 
					 * @param new_value
					 */
					inline void set_interval(const csf_uint64 new_value) {

						m_interval = new_value;
					}
					/**
					 * 表示任务所属的任务管理器
					 */
					csf_task_manager* get_task_manager();
					/**
					 * 表示任务所属的任务管理器
					 * 
					 * @param new_value
					 */
					void set_task_manager(const csf_task_manager* new_value);
					/**
					 * 表示处理接口，当只有is_delete返回true后才能process_delete。
					 */
					virtual csf_int32 process_delete();

				private:
					/**
					 * 表示任务的类型数值
					 */
					csf_task_type m_type = csf_task_type_none;
					/**
					 * 表示任务的状态数值
					 */
					csf::core::utils::task::csf_task::csf_task_status m_status = csf_task_status_none;
					/**
					 * 表示任务的回调函数
					 */
					csf::core::utils::task::csf_task_callback m_callback = csf_null;
					/**
					 * 表示任务删除后的回调函数
					 */
					csf::core::utils::task::csf_task_delete_callback m_delete_callback = csf_null;
					/**
					 * 表示当前的时间关键数值，即当前时间，单位毫秒
					 */
					csf_uint64 m_time = 0;
					/**
					 * 表示第一次执行的偏移时间，单位毫秒
					 */
					csf_uint64 m_offset = 0;
					/**
					 * 指向一个装饰者对象
					 */
					csf_task* m_decorator = csf_null;
					/**
					 * 表示任务的执行间隔时间，单位毫秒
					 */
					csf_uint64 m_interval = 0;
					/**
					 * 表示任务所属的任务管理器
					 */
					csf_task_manager* m_task_manager = csf_null;
					/**
					 * 表示所属的任务管理器
					 */
					csf::core::utils::task::csf_task_manager *m_task_manager;

				};

			}

		}

	}

}
#endif // !defined(CSF_TASK_INCLUDED_)
