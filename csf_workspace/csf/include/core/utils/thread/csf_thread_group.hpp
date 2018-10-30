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
#include "csf_thread.hpp"
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/config/abi_prefix.hpp>


using namespace csf::core::base;


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
					inline explicit csf_thread_group() {

					}

					virtual ~csf_thread_group() {

					}

					/**
					* 主要功能是：获取线程组中的线程数量
					* 返回：当前线程组中包含的线程数量
					*/
					inline csf_uint32 size() {

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						return (csf_uint32)get_threads().size();
					}
					/**
					* 主要功能是：当前线程是否在线程组中。
					* 返回：true表示已经存在线程组中；false表示不存在。
					*/
					csf_bool is_this_thread_in() {

						boost::thread::id id = boost::this_thread::get_id();

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						for (auto &iter : get_threads()) {
							if (iter->get_id() == id) {
								return csf_true;
							}
						}

						return csf_false;
					}
					/**
					* 主要功能是：指定线程是否在线程组中。
					* 返回：true表示已经存在线程组中；false表示不存在。
					*
					* @param thrd    表示需要被查找的线程
					*/
					csf_bool is_thread_in(csf_thread* thrd) {

						if (csf_nullptr == thrd) {
							return csf_false;
						}

						csf_set<csf_thread*>::iterator	tmp_iter;

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);
						
						tmp_iter = get_threads().find(thrd);
						if (tmp_iter != get_threads().end()) {
							return csf_true;
						}

						return csf_false;
					}
					/**
					* 主要功能是：在线程组中创建一个线程
					* 返回：非null表示当前线程对象指针；null表示错误
					*
					* @param func    线程执行函数
					*/
					template<typename TheadFunction>
					csf_thread* create_thread(TheadFunction func) {

						boost::csbl::unique_ptr<csf_thread> new_thread(new csf_thread(func));
						add_thread(new_thread.get());

						return new_thread.release();
					}
					/**
					* 主要功能是：添加指定线程到线程组中。
					* 返回：true表示成功；false表示失败。
					*
					* @param thrd    表示需要被处理的线程
					*/
					inline csf_bool add_thread(csf_thread* thrd) {

						if (csf_nullptr == thrd) {
							return csf_false;
						}

						BOOST_THREAD_ASSERT_PRECONDITION(!is_thread_in(thrd),
							thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur),
								"boost::pc_thread_group_ex: trying to add a duplicated boost::thread")
						);

						csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						get_threads().insert(thrd);

						return csf_true;
					}
					/**
					* 主要功能是：删除指定线程到线程组中。
					* 返回：true表示成功；false表示失败。
					*
					* @param thrd    表示需要被处理的线程
					*/
					inline csf_bool remove_thread(csf_thread* thrd) {

						if (csf_nullptr == thrd) {
							return csf_false;
						}

						csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						get_threads().erase(thrd);

						return csf_true;
					}
					/**
					* 主要功能是：等待所有线程结束
					* 返回：无
					*/
					csf_void join_all() {

						BOOST_THREAD_ASSERT_PRECONDITION(!is_this_thread_in(),
							thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur),
								"boost::pc_thread_group_ex: trying joining itself"));

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						for (auto &iter : get_threads()) {
							if (iter->joinable()) {
								iter->join();
							}
						}
					}
					/**
					* 主要功能是：等待所有线程结束，如果等待超时则强制终止。
					* 返回：无
					*
					* @param timeout_ms    表示等待超时时间，单位毫秒。
					*/
					csf_void timed_join_all(const csf_uint64 timeout_ms) {

						BOOST_THREAD_ASSERT_PRECONDITION(!is_this_thread_in(),
							thread_resource_error(static_cast<int>(system::errc::resource_deadlock_would_occur),
								"boost::pc_thread_group_ex: trying joining itself"));

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						for (auto &iter : get_threads()) {
							if (iter->joinable()) {
								if (!iter->timed_join(timeout_ms)) {
									iter->interrupt();
								}
							}
						}
					}
					/**
					* 主要功能是：强制终止所有线程
					* 返回：无
					*/
					inline csf_void interrupt_all() {

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						for (auto &iter : get_threads()) {
							iter->interrupt();
						}
					}
				protected:
					/**
					* 主要功能是：获取保存的线程集合
					* 返回：当前的线程列表
					*/
					inline csf_set<csf_thread*>& get_threads() {

						return m_threads;
					}
				private:
					/**
					* 表示保存的线程集合
					*/
					csf_set<csf_thread*> m_threads;
					/**
					* 表示用于多线程安全的互斥量
					*/
					csf_shared_mutex m_mutex;

				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_GROUP_INCLUDED_)
