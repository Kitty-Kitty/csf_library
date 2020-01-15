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
*Description: Class(csf_thread_group) 表示线程组管理器
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_THREAD_GROUP_INCLUDED_)
#define CSF_THREAD_GROUP_INCLUDED_

#include <set>
#include "csf_typedef.h"
#include "csf_stdcollector.hpp"
#include "csf_mutex.hpp"

using namespace csf::core::base;

class csf_thread;

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace thread
			{
				/**
				 * 表示线程组管理器
				 * @author f
				 * @version 1.0
				 * @created 19-7月-2018 20:11:52
				 */
				class csf_thread_group
				{

				public:
					csf_thread_group();
					virtual ~csf_thread_group();

					/**
					 * 表示保存的线程集合
					 */
					inline csf_set<csf_thread*>& get_threads() {

						return m_threads;
					}
					/**
					 * 表示保存的线程集合
					 * 
					 * @param newVal
					 */
					inline csf_void set_threads(const csf_set<csf_thread*>& newVal) {

						m_threads = newVal;
					}
					/**
					 * 表示获取线程组中的线程数量
					 */
					inline csf_uint32 size() {

						return 0;
					}
					/**
					 * 表示当前线程是否在线程组中。
					 * 返回：true表示已经存在线程组中；false表示不存在。
					 */
					inline csf_bool is_this_thread_in() {

						return csf_true;
					}
					/**
					 * 表示指定线程是否在线程组中。
					 * 返回：true表示已经存在线程组中；false表示不存在。
					 * 
					 * @param thrd    表示需要被查找的线程
					 */
					inline csf_bool is_thread_in(const csf_thread* thrd) {

						return csf_true;
					}
					/**
					 * 
					 * @param func    线程执行函数
					 */
					template <typename F>
					csf_thread* create_thread(F func) {
						return csf_nullptr;
					}
					/**
					 * 表示添加指定线程到线程组中。
					 * 返回：true表示成功；false表示失败。
					 * 
					 * @param thrd    表示需要被处理的线程
					 */
					inline csf_bool add_thread(const csf_thread* thrd) {

						return csf_true;
					}
					/**
					 * 表示删除指定线程到线程组中。
					 * 返回：true表示成功；false表示失败。
					 * 
					 * @param thrd    表示需要被处理的线程
					 */
					inline csf_bool remove_thread(const csf_thread* thrd) {

						return csf_true;
					}
					/**
					 * 等待所有线程结束
					 */
					inline csf_void join_all() {

					}
					/**
					 * 等待所有线程结束，如果等待超时则强制终止。
					 * 
					 * @param timeout    表示等待超时时间，单位毫秒。
					 */
					inline csf_void timed_join_all(const csf_uint64 timeout) {

					}
					/**
					 * 强制终止所有线程
					 */
					inline csf_void interrupt_all() {

					}

				private:
					/**
					 * 表示保存的线程集合
					 */
					csf_set<csf_thread*> m_threads;
					/**
					 * 表示用于多线程安全的互斥量
					 */
					csf::core::utils::thread::csf_mutex m_mtx;

				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_GROUP_INCLUDED_)
