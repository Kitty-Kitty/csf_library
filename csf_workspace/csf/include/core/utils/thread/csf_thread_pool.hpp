/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_thread_pool.hpp
*
*Version: 1.0
*
*Date: 21-10月-2018 16:52:04
*
*Description: Class(csf_thread_pool) 表示线程池描述类型，包含线程组及其他相关内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_THREAD_POOL_H_INCLUDED_)
#define CSF_THREAD_POOL_H_INCLUDED_

#include "csf_thread_group.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				/************************************************************************/
				/* 默认的线程个数														*/
				/************************************************************************/
				#define csf_thread_pool_default_thread_number			2				//表示默认的线程个数
				/************************************************************************/
				/* 默认的最大失败次数														*/
				/************************************************************************/
				#define csf_thread_pool_max_failure_times				30				//表示默认的最大失败次数
				/************************************************************************/
				/* 默认的创建线程间隔时间，单位：毫秒（ms） 								*/
				/************************************************************************/
				#define csf_thread_pool_create_thread_interval_ms		100				//表示默认的创建线程间隔时间，单位：毫秒（ms）
				/**
				 * 表示线程池描述类型，包含线程组及其他相关内容
				 * @author f
				 * @version 1.0
				 * @updated 21-10月-2018 16:53:55
				 */
				class csf_thread_pool
				{

				public:
					csf_thread_pool();
					virtual ~csf_thread_pool();
					/**
					* 主要功能是：启动线程池
					* 返回：0表示成功；非0表示失败；
					*
					* @param func    表示各个线程的运行函数
					*/
					template<typename TheadFunction>
					csf_int32 start(TheadFunction func) {

						csf_thread				*tmp_thread = csf_nullptr;
						csf_int32				tmp_thread_number = 0;
						csf_uint32				tmp_failure_times = 0;
						csf_int32				i = 0;


						//判断线程数量的合法性
						if (get_thread_number() <= 0) {
							return csf_failure;
						}

						//创建各个线程对象
						while (csf_true) {

							tmp_thread = get_group().create_thread(func);
							if (csf_nullptr == tmp_thread) {
								//如果创建线程失败，则等待一段时间后，再尝试创建
								csf_msleep(csf_thread_pool_create_thread_interval_ms);

								//如果错误超过了最大次数，则直接返回错误
								if (++tmp_failure_times >= get_max_failure_times()) {
									get_group().timed_join_all(csf_thread_pool_create_thread_interval_ms);
									return csf_failure;
								}

								continue;
							}
							
							if (++tmp_thread_number == get_thread_number()) {
								break;
							}
						}

						return csf_true;
					}
					/**
					* 主要功能是：启动线程池，同时指定线程数量
					* 返回：0表示成功；非0表示失败；
					*
					* @param thread_number    表示需要创建的线程数量
					* @param func    表示各个线程的运行函数
					*/
					template<typename TheadFunction>
					inline csf_int32 start(const csf_uint32 thread_number, TheadFunction func) {

						if (thread_number <= 0) {
							return csf_failure;
						}

						set_thread_number(thread_number);

						return start(func);
					}
					/**
					* 主要功能是：停止线程池
					* 返回：0表示成功；非0表示失败；
					*/
					inline csf_int32 stop() {

						get_group().join_all();
						get_group().clear();

						return 0;
					}
					/**
					* 主要功能是：表示在指定的时间内，停止线程池
					* 返回：0表示成功；非0表示失败；
					*
					* @param timeout_ms    表示等待超时时间，单位毫秒
					*/
					inline csf_int32 stop(const csf_uint64 timeout_ms) {

						if (timeout_ms <= 0) {
							return -1;
						}

						get_group().timed_join_all(timeout_ms);

						return 0;
					}
					/**
					* 表示线程池的线程数量，默认为2
					*/
					inline csf_uint32 get_thread_number() {

						return m_thread_number;
					}
					/**
					* 表示线程池的线程数量，默认为2
					*
					* @param new_value
					*/
					inline void set_thread_number(csf_uint32 new_value) {

						m_thread_number = new_value;
					}
					/**
					* 表示最大失败次数
					*/
					inline csf_uint32 get_max_failure_times() {

						return m_max_failure_times;
					}
					/**
					* 表示最大失败次数
					*
					* @param new_value
					*/
					inline void set_max_failure_times(csf_uint32 new_value) {

						m_max_failure_times = new_value;
					}
				protected:
					/**
					* 表示线程组对象，用于保存各个线程信息
					*/
					inline csf::core::utils::thread::csf_thread_group& get_group() {

						return m_group;
					}
					
				private:
					/**
					 * 表示线程组对象，用于保存各个线程信息
					 */
					csf::core::utils::thread::csf_thread_group m_group;
					/**
					* 表示线程池的线程数量，默认为2
					*/
					csf_uint32 m_thread_number = csf_thread_pool_default_thread_number;
					/**
					* 表示最大失败次数
					*/
					csf_uint32 m_max_failure_times = csf_thread_pool_max_failure_times;
				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_POOL_H_INCLUDED_)
