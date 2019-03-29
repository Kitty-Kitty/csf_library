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
*Date: 04-11��-2018 10:44:37
*
*Description: Class(csf_connect_timeout_manager) ��ʾ���ӳ�ʱ����������Ҫ�������ӵĳ�ʱ�������д�����̴����ǣ�1���������ӵĳ�ʱ��Ϣ���ж����Ƿ�ʱ��2�������ʱ����ó�ʱ�����������޳�ʱ��������ֱ�ӹر�ɾ�����ӣ�3��������γ�ʱ�������Ĭ�ϵĳ�ʱ����
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
				/* ��ʾĬ�ϵ����м��ʱ�䣬�ʹ����ȣ���λ�����루ms����Ĭ��Ϊ��400ms		*/
				/************************************************************************/
				#define csf_connect_timeout_process_idle_interval_ms		400		    //��ʾĬ�ϵ����м��ʱ�䣬�ʹ����ȣ���λ�����루ms����Ĭ��Ϊ��400ms
				/************************************************************************/
				/* ��ʾĬ�ϵĴ����߳�������Ĭ��Ϊ��2		                                */
				/************************************************************************/
				#define csf_connect_timeout_thread_number					2		    //��ʾĬ�ϵĴ����߳�������Ĭ��Ϊ��2
				/**
				 * ��ʾ���ӳ�ʱ����������Ҫ�������ӵĳ�ʱ�������д�����̴����ǣ�1���������ӵĳ�ʱ��Ϣ���ж����Ƿ�ʱ��2�������ʱ����ó�ʱ�����������޳�ʱ��������ֱ��
				 * �ر�ɾ�����ӣ�3��������γ�ʱ�������Ĭ�ϵĳ�ʱ����
				 * @author f
				 * @version 1.0
				 * @created 04-11��-2018 10:44:37
				 */
				class csf_connect_timeout_manager
				{
				public:
					/**
					* ��ʾ�����Ӷ���ķ�װ���Է��㳬ʱ����������
					* @author f
					* @version 1.0
					* @updated 04-11��-2018 17:47:03
					*/
					class csf_connect_wrapper : public std::enable_shared_from_this<csf_connect_wrapper>
					{
					public:
						/**
						*
						* @param connect_ptr    ��ʾ���Ӷ���
						* @param timeout    ��ʾ���ӳ�ʱ����
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
						* @param connect_wrapper    ��ʾ��Ҫ�����жϵ����ӷ�װ����
						*/
						inline csf_connect_wrapper& operator =(const csf_connect_wrapper& connect_wrapper) {

							set_timeout(connect_wrapper.get_timeout());
							set_connect_ptr(((csf_connect_wrapper&)connect_wrapper).get_connect_ptr());

							return *this;
						}
						/**
						*
						* @param connect_wrapper    ��ʾ��Ҫ�����жϵ����ӷ�װ����
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
						* @param connect_wrapper    ��ʾ��Ҫ�����жϵ����ӷ�װ����
						*/
						inline csf_bool operator !=(const csf_connect_wrapper& connect_wrapper) {

							if (*this == connect_wrapper) {
								return csf_false;
							}

							return csf_true;
						}
						/**
						* ��ʾ��ʱ��������
						*/
						inline csf_connect_timeout& get_timeout() const {

							return m_timeout;
						}
						/**
						* ��ʾ��ʱ��������
						*
						* @param newVal
						*/
						inline void set_timeout(csf_connect_timeout& newVal) {

							m_timeout = newVal;
						}
						/**
						* ��ʾ���Ӷ���
						*/
						inline csf_connect_ptr& get_connect_ptr() {

							return m_connect_ptr;
						}
						/**
						* ��ʾ���Ӷ���
						*
						* @param newVal
						*/
						inline void set_connect_ptr(csf_connect_ptr& newVal) {

							m_connect_ptr = newVal;
						}
					private:
						/**
						* ��ʾ��ʱ��������
						*/
						csf_connect_timeout& m_timeout;
						/**
						* ��ʾ���Ӷ���
						*/
						csf_connect_ptr m_connect_ptr;

					};
					/**
					* ��ʾ�����Ӷ���ķ�װ���Է��㳬ʱ��������������ָ��
					* @author fangzhenmu@aliyun.com
					* @version 1.0
					* @created 01-10��-2018 12:54:36
					*/
					typedef	csf_shared_ptr<csf_connect_wrapper>				csf_connect_wrapper_ptr;
				public:
					csf_connect_timeout_manager();
					virtual ~csf_connect_timeout_manager();
					/**
					* ��Ҫ�����ǣ���ʼ����ʱ����������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					virtual csf::core::base::csf_int32 init() {

						return csf_succeed;
					}
					/**
					* ��Ҫ�����ǣ����г�ʱ����������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param thread_number    ��ʾ��ʱ���Ӵ������������߳�����
					*/
					virtual csf::core::base::csf_int32 start(
						const csf_uint32 thread_number = csf_connect_timeout_thread_number) {

						return get_thread_pool().start(thread_number
							, csf_bind(&csf_connect_timeout_manager::expired_process_cycle, this));
					}
					/**
					* ��Ҫ�����ǣ�ֹͣ��ʱ����������
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					virtual csf::core::base::csf_int32 stop() {

						//ֹͣ�̳߳�
						get_thread_pool().stop();

						return clear();
					}
					/**
					* ��Ҫ�����ǣ��������������Ƴ�һ�����ڵ����Ӷ���
					* ���أ���null��ʾ�ɹ���ȡ���Ӷ���null��ʾ����
					*
					* @param time    ��ʾ��ǰ��ʱ���׼
					* @param connect_wrapper    ��ʾ��Ҫ��ӵ����ӹ����������Ӷ����װ
					*/
					inline csf_int32 insert(const csf_connect_timeout& timeout, const csf_connect_wrapper_ptr& connect_wrapper) {

						csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::iterator		tmp_iter;


						csf_unqiue_lock<decltype(m_collector_mutex)> tmp_lock(m_collector_mutex);

						tmp_iter = get_connect_collector().find(&(const_cast<csf_connect_timeout&>(timeout)));
						if (tmp_iter != get_connect_collector().end()) {
							//��ʾ�Ѿ����б��У�����Ҫ�����
							return csf_succeed;
						}

						//��ӵ���ѯ������
						get_connect_collector().insert(
							csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>::value_type(&(const_cast<csf_connect_timeout&>(timeout))
								, connect_wrapper));

						get_connect_queue().push_back(connect_wrapper);

						return csf_succeed;
					}
					/**
					 * ��Ҫ�����ǣ��������������Ƴ�һ�����ڵ����Ӷ���
					 * ���أ���null��ʾ�ɹ���ȡ���Ӷ���null��ʾ����
					 * 
					 * @param timeout    ��ʾ��ǰ�ĳ�ʱ��������
					 * @param connect_ptr    ��ʾ��Ҫ��ӵ����ӹ����������Ӷ���
					 */
					inline csf_int32 insert(const csf_connect_timeout& timeout, const csf_connect_ptr& connect_ptr) {

						return insert(timeout, csf_connect_wrapper_ptr(new csf_connect_wrapper(connect_ptr, (csf_connect_timeout&)timeout)));
					}
					/**
					* ��Ҫ�����ǣ��������������Ƴ�һ�������Ӷ��󣬸�ɾ������ֻ�ǽ���������Ϊ������ʱ��������ֱ�ӵ�ɾ��������������ɾ����Ҫ�ȴ���ʱ������ɡ�
					* ���أ�0��ʾ�ɹ���ȡ���Ӷ��󣻷�0��ʾ����
					*
					* @param timeout    ��ʾɾ���ĳ�ʱ����
					*/
					csf_int32 remove(csf_connect_timeout& timeout);
					/**
					 * ��ʾϵͳ�Ŀ����ߵȴ����ʱ�䣬��λ�����루ms��
					 */
					inline csf_uint64 get_idle_interval() const {

						return m_idle_interval;
					}
					/**
					 * ��ʾϵͳ�Ŀ����ߵȴ����ʱ�䣬��λ�����루ms��
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
					 * ��ʾ��ʱ�����̳߳أ�ͳһ����ʱ�������
					 */
					csf::core::utils::thread::csf_thread_pool m_thread_pool;
					/**
					* ��ʾ���ӹ����������ڴ������ӳ�ʱ������ݡ��ü�����Ҫ���ڲ�ѯ��Ϊ�˽����ͬ�����Ӷ������Ƶ����������⡣
					* connect_collector��Ҫ�����û��Ĳ���������ɾ���顢�ģ���
					* connect_queue���ϳ�������⣬����ȫ����ϵͳ���ݼȶ��ĳ�ʱ���ƴ�����ʱ�˾�ɾ������һ�������Ĵ�����̡�
					*/
					csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr> m_connect_collector;
					/**
					* ��ʾ���ӹ������Ĵ�����У���Ҫ���ڳ�ʱѭ���жϡ�
					* connect_collector��Ҫ�����û��Ĳ���������ɾ���顢�ģ���
					* connect_queue���ϳ�������⣬����ȫ����ϵͳ���ݼȶ��ĳ�ʱ���ƴ�����ʱ�˾�ɾ������һ�������Ĵ�����̡�
					*/
					csf_csfdeque<csf_connect_wrapper_ptr> m_connect_queue;
					/**
					 * ��ʾ���ӹ���������Ļ������
					 */
					csf::core::utils::thread::csf_shared_mutex m_collector_mutex;
					/**
					 * ��ʾϵͳ�Ŀ����ߵȴ����ʱ�䣬��λ�����루ms��
					 */
					csf_uint64 m_idle_interval = csf_connect_timeout_process_idle_interval_ms;
					/**
					 * ��ʾ��ʱ�����̳߳أ�ͳһ����ʱ�������
					 */
					inline csf::core::utils::thread::csf_thread_pool& get_thread_pool() {

						return m_thread_pool;
					}
					/**
					* ��ʾ���ӹ����������ڴ������ӳ�ʱ������ݡ��ü�����Ҫ���ڲ�ѯ��Ϊ�˽����ͬ�����Ӷ������Ƶ����������⡣
					* connect_collector��Ҫ�����û��Ĳ���������ɾ���顢�ģ���
					* connect_queue���ϳ�������⣬����ȫ����ϵͳ���ݼȶ��ĳ�ʱ���ƴ�����ʱ�˾�ɾ������һ�������Ĵ�����̡�
					*/
					inline csf_map<csf_connect_timeout*, csf_connect_wrapper_ptr>& get_connect_collector() {

						return m_connect_collector;
					}
					/**
					* ��ʾ���ӹ������Ĵ�����У���Ҫ���ڳ�ʱѭ���жϡ�
					* connect_collector��Ҫ�����û��Ĳ���������ɾ���顢�ģ���
					* connect_queue���ϳ�������⣬����ȫ����ϵͳ���ݼȶ��ĳ�ʱ���ƴ�����ʱ�˾�ɾ������һ�������Ĵ�����̡�
					*/
					inline csf_csfdeque<csf_connect_wrapper_ptr>& get_connect_queue() {

						return m_connect_queue;
					}
					/**
					* ��Ҫ�����ǣ�����������е��������Ӷ���
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
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
					* ��Ҫ�����ǣ���ʱ�̴߳������ӿ�
					* ���أ���
					*/
					csf_void expired_process_cycle();
					/**
					* ��Ҫ�����ǣ�
					*    ���ָ����connect_wrapper�����Ƿ�ʱ�Ĵ���
					* ���أ���
					*
					* @param wrapper    ��ʾ��ǰ��Ҫ���������Ӷ���
					*/
					csf_void process_connect_wrapper(csf_connect_wrapper_ptr& wrapper);
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_TIMEOUT_MANAGER_H_INCLUDED_)
