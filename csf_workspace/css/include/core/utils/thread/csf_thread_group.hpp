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
				 * ��ʾ�߳��������
				 * @author f
				 * @version 1.0
				 * @created 19-7��-2018 20:11:52
				 */
				class csf_thread_group
				{

				public:
					csf_thread_group();
					virtual ~csf_thread_group();

					/**
					 * ��ʾ������̼߳���
					 */
					inline csf_set<csf_thread*>& get_threads() {

						return m_threads;
					}
					/**
					 * ��ʾ������̼߳���
					 * 
					 * @param newVal
					 */
					inline csf_void set_threads(const csf_set<csf_thread*>& newVal) {

						m_threads = newVal;
					}
					/**
					 * ��ʾ��ȡ�߳����е��߳�����
					 */
					inline csf_uint32 size() {

						return 0;
					}
					/**
					 * ��ʾ��ǰ�߳��Ƿ����߳����С�
					 * ���أ�true��ʾ�Ѿ������߳����У�false��ʾ�����ڡ�
					 */
					inline csf_bool is_this_thread_in() {

						return csf_true;
					}
					/**
					 * ��ʾָ���߳��Ƿ����߳����С�
					 * ���أ�true��ʾ�Ѿ������߳����У�false��ʾ�����ڡ�
					 * 
					 * @param thrd    ��ʾ��Ҫ�����ҵ��߳�
					 */
					inline csf_bool is_thread_in(const csf_thread* thrd) {

						return csf_true;
					}
					/**
					 * 
					 * @param func    �߳�ִ�к���
					 */
					template <typename F>
					csf_thread* create_thread(F func) {
						return csf_nullptr;
					}
					/**
					 * ��ʾ���ָ���̵߳��߳����С�
					 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					 * 
					 * @param thrd    ��ʾ��Ҫ��������߳�
					 */
					inline csf_bool add_thread(const csf_thread* thrd) {

						return csf_true;
					}
					/**
					 * ��ʾɾ��ָ���̵߳��߳����С�
					 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					 * 
					 * @param thrd    ��ʾ��Ҫ��������߳�
					 */
					inline csf_bool remove_thread(const csf_thread* thrd) {

						return csf_true;
					}
					/**
					 * �ȴ������߳̽���
					 */
					inline csf_void join_all() {

					}
					/**
					 * �ȴ������߳̽���������ȴ���ʱ��ǿ����ֹ��
					 * 
					 * @param timeout    ��ʾ�ȴ���ʱʱ�䣬��λ���롣
					 */
					inline csf_void timed_join_all(const csf_uint64 timeout) {

					}
					/**
					 * ǿ����ֹ�����߳�
					 */
					inline csf_void interrupt_all() {

					}

				private:
					/**
					 * ��ʾ������̼߳���
					 */
					csf_set<csf_thread*> m_threads;
					/**
					 * ��ʾ���ڶ��̰߳�ȫ�Ļ�����
					 */
					csf::core::utils::thread::csf_mutex m_mtx;

				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_GROUP_INCLUDED_)
