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
*Date: 19-7��-2018 20:11:52
*
*Description: Class(csf_thread_group) ��ʾ�߳��������
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
				 * ��ʾ�߳��������
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:52
				 */
				class csf_thread_group
				{

				public:
					inline explicit csf_thread_group() {

					}

					virtual ~csf_thread_group() {

					}

					/**
					* ��Ҫ�����ǣ���ȡ�߳����е��߳�����
					* ���أ���ǰ�߳����а������߳�����
					*/
					inline csf_uint32 size() {

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						return (csf_uint32)get_threads().size();
					}
					/**
					* ��Ҫ�����ǣ���ǰ�߳��Ƿ����߳����С�
					* ���أ�true��ʾ�Ѿ������߳����У�false��ʾ�����ڡ�
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
					* ��Ҫ�����ǣ�ָ���߳��Ƿ����߳����С�
					* ���أ�true��ʾ�Ѿ������߳����У�false��ʾ�����ڡ�
					*
					* @param thrd    ��ʾ��Ҫ�����ҵ��߳�
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
					* ��Ҫ�����ǣ����߳����д���һ���߳�
					* ���أ���null��ʾ��ǰ�̶߳���ָ�룻null��ʾ����
					*
					* @param func    �߳�ִ�к���
					*/
					template<typename TheadFunction>
					csf_thread* create_thread(TheadFunction func) {

						boost::csbl::unique_ptr<csf_thread> new_thread(new csf_thread(func));
						add_thread(new_thread.get());

						return new_thread.release();
					}
					/**
					* ��Ҫ�����ǣ����ָ���̵߳��߳����С�
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param thrd    ��ʾ��Ҫ��������߳�
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
					* ��Ҫ�����ǣ�ɾ��ָ���̵߳��߳����С�
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param thrd    ��ʾ��Ҫ��������߳�
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
					* ��Ҫ�����ǣ��ȴ������߳̽���
					* ���أ���
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
					* ��Ҫ�����ǣ��ȴ������߳̽���������ȴ���ʱ��ǿ����ֹ��
					* ���أ���
					*
					* @param timeout_ms    ��ʾ�ȴ���ʱʱ�䣬��λ���롣
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
					* ��Ҫ�����ǣ�ǿ����ֹ�����߳�
					* ���أ���
					*/
					inline csf_void interrupt_all() {

						csf_shared_lock<decltype(m_mutex)> tmp_lock(m_mutex);

						for (auto &iter : get_threads()) {
							iter->interrupt();
						}
					}
				protected:
					/**
					* ��Ҫ�����ǣ���ȡ������̼߳���
					* ���أ���ǰ���߳��б�
					*/
					inline csf_set<csf_thread*>& get_threads() {

						return m_threads;
					}
				private:
					/**
					* ��ʾ������̼߳���
					*/
					csf_set<csf_thread*> m_threads;
					/**
					* ��ʾ���ڶ��̰߳�ȫ�Ļ�����
					*/
					csf_shared_mutex m_mutex;

				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_GROUP_INCLUDED_)
