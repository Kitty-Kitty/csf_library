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
*Description: Class(csf_thread) 表示线程类
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_THREAD_INCLUDED_)
#define CSF_THREAD_INCLUDED_

#include "csf_base_include.h"
#include "csf_stdbind.hpp"
#include "csf_logger.hpp"
#include <boost/thread.hpp>

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				/**
				* 表示线程类
				* @author f
				* @version 1.0
				* @created 21-10月-2018 20:23:45
				*/
				class csf_thread : public boost::thread
				{
				public:
					/**
					* 表示线程运行的用户函数句柄
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_void()> 	csf_thread_start_handle;
					/**
					* 表示线程状态列表
					* @author f
					* @version 1.0
					* @updated 21-10月-2018 22:31:00
					*/
					typedef enum csf_thread_status_enum
					{
						/**
						* 表示线程未初始化状态
						*/
						csf_thread_status_none = 0x00,
						/**
						* 表示线程初始化状态
						*/
						csf_thread_status_init = 0x01,
						/**
						* 表示线程运行状态
						*/
						csf_thread_status_start = 0x02,
						/**
						* 表示线程停止状态
						*/
						csf_thread_status_stop = 0x04					
					} csf_thread_status;
				public:
					template<typename TheadFunction>
					csf_thread(TheadFunction func)
						: m_status(csf_thread::csf_thread_status::csf_thread_status_none)
						, boost::thread(boost::bind(&csf_thread::start, this, func)) {

					}
					virtual ~csf_thread() {
						join();
					}
					/**
					* 主要功能是：停止线程
					* 返回：无
					*/
					inline csf_int32 stop() {

						set_status(csf_thread_status_stop);

						return 0;
					}
					/**
					* 主要功能是：等待线程退出
					* 返回：无
					*/
					inline void join() {
						if (stop()) {
							boost::thread::join();
						}
					}
					/**
					* 主要功能是：让线程“中断”停止
					* 返回：无
					*/
					inline void interrupt() {
						if (stop()) {
#if defined BOOST_THREAD_PROVIDES_INTERRUPTIONS
							boost::thread::interrupt();
#endif
						}
					}
					/**
					*
					* @param timeout_ms    表示定时的等待终止
					*/
					inline bool timed_join(const csf_uint64 timeout_ms) {

						if (stop()) {
							return boost::thread::timed_join(boost::posix_time::millisec(timeout_ms));
						}
						return true;
					}
				private:
					/**
					* 表示线程状态信息
					*/
					csf_thread_status m_status = csf_thread_status_none;
					/**
					* 表示线程状态信息
					*/
					inline csf_thread_status get_status() {

						return m_status;
					}
					/**
					* 表示线程状态信息
					*
					* @param newVal
					*/
					inline void set_status(csf_thread_status newVal) {

						m_status = newVal;
					}
					/**
					* 主要功能是：启动运行线程
					* 返回：无
					*
					* @param func    表示线程的运行函数
					*/
					void start(csf_thread_start_handle func) {

						set_status(csf_thread_status_start);
						cycle(func);
					}
					/**
					* 主要功能是：线程运行的循环函数
					* 返回：无
					*
					* @param func    表示线程的运行函数
					*/
					template<typename TheadFunction>
					inline void cycle(TheadFunction func) {
						while (csf_true) {
							if (csf_thread_status_start == m_status) {
								try {
									func();
								}
								catch (std::exception &e) {
									csf_log_ex(error
										, csf_log_code_error
										, "thread[0x%x] exception[%s]"
										, this
										, e.what());
								}
							}
						}
					}
				};
			}

		}

	}

}
#endif // !defined(CSF_THREAD_INCLUDED_)
