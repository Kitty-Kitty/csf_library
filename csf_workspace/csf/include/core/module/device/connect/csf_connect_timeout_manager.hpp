/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_timeout_manager.hpp
*
*Version: 1.0
*
*Date: 04-11月-2018 10:44:37
*
*Description: Class(csf_connect_timeout_manager) 表示连接超时管理器，主要用于连接的超时处理。其中处理过程大致是：1、调用连接的超时信息，判断是是否超时；2、如果超时则调用超时处理函数处理，无超时处理函数则直接关闭删除连接；3、连续多次超时，则采用默认的超时处理；
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_TIMEOUT_MANAGER_H_INCLUDED_)
#define CSF_CONNECT_TIMEOUT_MANAGER_H_INCLUDED_

#include "csf_connect.hpp"
#include "csf_thread_pool.hpp"
#include "csf_shared_mutex.hpp"
#include "csf_csfdeque.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/************************************************************************/
				/* 表示默认的休闲间隔时间，和处理精度，单位：毫秒（ms）。默认为：400ms		*/
				/************************************************************************/
				#define csf_connect_timeout_process_idle_interval_ms		400		    //表示默认的休闲间隔时间，和处理精度，单位：毫秒（ms）。默认为：400ms
				/************************************************************************/
				/* 表示默认的处理线程数量。默认为：2		                                */
				/************************************************************************/
				#define csf_connect_timeout_thread_number					2		    //表示默认的处理线程数量。默认为：2
				/**
				 * 表示连接超时管理器，主要用于连接的超时处理。其中处理过程大致是：1、调用连接的超时信息，判断是是否超时；2、如果超时则调用超时处理函数处理，无超时处理函数则直接
				 * 关闭删除连接；3、连续多次超时，则采用默认的超时处理；
				 * @author f
				 * @version 1.0
				 * @created 04-11月-2018 10:44:37
				 */
				class csf_connect_timeout_manager
				{
				public:
					/**
					* 表示对连接对象的封装，以方便超时管理器处理
					* @author f
					* @version 1.0
					* @updated 04-11月-2018 17:47:03
					*/
					class csf_connect_wrapper : public std::enable_shared_from_this<csf_connect_wrapper>
					{
					public:
						/**
						*
						* @param connect_ptr    表示连接对象
						* @param timeout    表示连接超时对象
						*/
						inline explicit csf_connect_wrapper(const csf_connect_ptr& connect_ptr
							, const csf_connect_timeout& timeout)
							: m_connect_ptr(connect_ptr)
							, m_timeout((csf_connect_timeout&)timeout) {

						}
						virtual ~csf_connect_wrapper() {

						}
						/**
						*
						* @param connect_wrapper    表示需要进行判断的连接封装对象
						*/
						inline csf_connect_wrapper& operator =(const csf_connect_wrapper& connect_wrapper) {

							set_timeout(connect_wrapper.get_timeout());
							set_connect_ptr(((csf_connect_wrapper&)connect_wrapper).get_connect_ptr());

							return *this;
						}
						/**
						*
						* @param connect_wrapper    表示需要进行判断的连接封装对象
						*/
						inline csf_bool operator ==(const csf_connect_wrapper& connect_wrapper) {

							if (get_timeout() == connect_wrapper.get_timeout()
								&& get_connect_ptr() == ((csf_connect_wrapper&)connect_wrapper).get_connect_ptr()) {
								return csf_true;
							}

							return csf_false;
						}
						/**
						*
						* @param connect_wrapper    表示需要进行判断的连接封装对象
						*/
						inline csf_bool operator !=(const csf_connect_wrapper& connect_wrapper) {

							if (*this == connect_wrapper) {
								return csf_false;
							}

							return csf_true;
						}
						/**
						* 表示超时对象引用
						*/
						inline csf_connect_timeout& get_timeout() const {

							return m_timeout;
						}
						/**
						* 表示超时对象引用
						*
						* @param newVal
						*/
						inline void set_timeout(csf_connect_timeout& newVal) {

							m_timeout = newVal;
						}
						/**
						* 表示连接对象
						*/
						inline csf_connect_ptr& get_connect_ptr() {

							return m_connect_ptr;
						}
						/**
						* 表示连接对象
						*
						* @param newVal
						*/
						inline void set_connect_ptr(csf_connect_ptr& newVal) {

							m_connect_ptr = newVal;
						}
					private:
						/**
						* 表示超时对象引用
						*/
						csf_connect_timeout& m_timeout;
						/**
						* 表示连接对象
						*/
						csf_connect_ptr m_connect_ptr;

					};
					/**
					* 表示对连接对象的封装，以方便超时管理器处理智能指针
					* @author fangzhenmu@aliyun.com
					* @version 1.0
					* @created 01-10月-2018 12:54:36
					*/
					typedef	csf_shared_ptr<csf_connect_wrapper>				csf_connect_wrapper_ptr;
				public:
					csf_connect_timeout_manager();
					virtual ~csf_connect_timeout_manager();
					/**
					* 主要功能是：初始化超时管理器对象
					* 返回：0表示成功；非0表示失败；
					*/
					virtual csf::core::base::csf_int32 init() {

						return csf_succeed;
					}
					/**
					* 主要功能是：运行超时管理器对象
					* 返回：0表示成功；非0表示失败；
					*
					* @param thread_number    表示超时连接处理器启动的线程数量
					*/
					virtual csf::core::base::csf_int32 start(
						const csf_uint32 thread_number = csf_connect_timeout_thread_number) {

						return get_thread_pool().start(thread_number
							, csf_bind(&csf_connect_timeout_manager::expired_process_cycle, this));
					}
					/**
					* 主要功能是：停止超时管理器对象
					* 返回：0表示成功；非0表示失败；
					*/
					virtual csf::core::base::csf_int32 stop() {

						//停止线程池
						get_thread_pool().stop();

						return clear();
					}
					/**
					* 主要功能是：从连接容器中移除一个过期的连接对象
					* 返回：非null表示成功获取连接对象；null表示错误；
					*
					* @param time    表示当前的时间基准
					* @param connect_wrapper    表示需要添加到连接管理器的连接对象封装
					*/
					inline csf_int32 insert(const csf_connect_timeout& timeout, const csf_connect_wrapper_ptr& connect_wrapper) {

						csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::iterator		tmp_iter;


						csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

						tmp_iter = get_connect_collector().find(&(const_cast<csf_connect_timeout&>(timeout)));
						if (tmp_iter != get_connect_collector().end()) {
							//表示已经在列表中，不需要再添加
							return csf_succeed;
						}

						//添加到查询队列中
						get_connect_collector().insert(
							csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::value_type(&(const_cast<csf_connect_timeout&>(timeout))
								, connect_wrapper));

						get_connect_queue().push_back(connect_wrapper);

						return csf_succeed;
					}
					/**
					 * 主要功能是：从连接容器中移除一个过期的连接对象
					 * 返回：非null表示成功获取连接对象；null表示错误；
					 * 
					 * @param timeout    表示当前的超时对象内容
					 * @param connect_ptr    表示需要添加到连接管理器的连接对象
					 */
					inline csf_int32 insert(const csf_connect_timeout& timeout, const csf_connect_ptr& connect_ptr) {

						return insert(timeout, csf_connect_wrapper_ptr(new csf_connect_wrapper(connect_ptr, (csf_connect_timeout&)timeout)));
					}
					/**
					* 主要功能是：从连接容器中移除一个的连接对象，该删除操作只是将连接设置为立即超时，而不是直接的删除操作。真正的删除需要等待超时处理完成。
					* 返回：0表示成功获取连接对象；非0表示错误；
					*
					* @param timeout    表示删除的超时对象
					*/
					csf_int32 remove(csf_connect_timeout& timeout);
					/**
					 * 表示系统的空休眠等待间隔时间，单位：毫秒（ms）
					 */
					inline csf_uint64 get_idle_interval() const {

						return m_idle_interval;
					}
					/**
					 * 表示系统的空休眠等待间隔时间，单位：毫秒（ms）
					 * 
					 * @param newVal
					 */
					inline csf_void set_idle_interval(csf_uint64 newVal) {

						if (0 != newVal) {
							m_idle_interval = newVal;
						}
					}

				private:
					/**
					 * 表示超时处理线程池，统一处理超时相关事务。
					 */
					csf::core::utils::thread::csf_thread_pool m_thread_pool;
					/**
					* 表示连接管理器，用于处理连接超时相关内容。该集合主要用于查询，为了解决相同的连接对象可能频繁插入的问题。
					* connect_collector主要面向用户的操作（增、删、查、改）。
					* connect_queue集合除了添加外，其他全部由系统根据既定的超时机制处理，超时了就删除，是一种自主的处理过程。
					*/
					csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr> m_connect_collector;
					/**
					* 表示连接管理器的处理队列，主要用于超时循环判断。
					* connect_collector主要面向用户的操作（增、删、查、改）。
					* connect_queue集合除了添加外，其他全部由系统根据既定的超时机制处理，超时了就删除，是一种自主的处理过程。
					*/
					csf_csfdeque<csf_connect_wrapper_ptr> m_connect_queue;
					/**
					 * 表示连接管理器处理的互斥变量
					 */
					csf::core::utils::thread::csf_shared_mutex m_collector_mutex;
					/**
					 * 表示系统的空休眠等待间隔时间，单位：毫秒（ms）
					 */
					csf_uint64 m_idle_interval = csf_connect_timeout_process_idle_interval_ms;
					/**
					 * 表示超时处理线程池，统一处理超时相关事务。
					 */
					inline csf::core::utils::thread::csf_thread_pool& get_thread_pool() {

						return m_thread_pool;
					}
					/**
					* 表示连接管理器，用于处理连接超时相关内容。该集合主要用于查询，为了解决相同的连接对象可能频繁插入的问题。
					* connect_collector主要面向用户的操作（增、删、查、改）。
					* connect_queue集合除了添加外，其他全部由系统根据既定的超时机制处理，超时了就删除，是一种自主的处理过程。
					*/
					inline csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>& get_connect_collector() {

						return m_connect_collector;
					}
					/**
					* 表示连接管理器的处理队列，主要用于超时循环判断。
					* connect_collector主要面向用户的操作（增、删、查、改）。
					* connect_queue集合除了添加外，其他全部由系统根据既定的超时机制处理，超时了就删除，是一种自主的处理过程。
					*/
					inline csf_csfdeque<csf_connect_wrapper_ptr>& get_connect_queue() {

						return m_connect_queue;
					}
					/**
					* 主要功能是：清除管理器中的所有连接对象
					* 返回：0表示成功；非0表示失败；
					*/
					inline csf::core::base::csf_int32 clear() {

						csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::iterator		tmp_iter;


						{
							csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

							for (tmp_iter = get_connect_collector().begin()
								; tmp_iter != get_connect_collector().end()
								; tmp_iter++) {

								tmp_iter->second->get_connect_ptr()->close();
							}

							get_connect_collector().clear();
						}

						return csf_succeed;
					}
					/**
					* 主要功能是：超时线程处理函数接口
					* 返回：无
					*/
					csf_void expired_process_cycle();
					/**
					* 主要功能是：
					*    针对指定的connect_wrapper进行是否超时的处理
					* 返回：无
					*
					* @param wrapper    表示当前需要被处理连接对象
					*/
					csf_void process_connect_wrapper(csf_connect_wrapper_ptr& wrapper);
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_TIMEOUT_MANAGER_H_INCLUDED_)
