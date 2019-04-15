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
*Date: 21-10��-2018 16:52:04
*
*Description: Class(csf_thread_pool) ��ʾ�̳߳��������ͣ������߳��鼰�����������
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
				/* Ĭ�ϵ��̸߳���														*/
				/************************************************************************/
				#define csf_thread_pool_default_thread_number			2				//��ʾĬ�ϵ��̸߳���
				/************************************************************************/
				/* Ĭ�ϵ����ʧ�ܴ���														*/
				/************************************************************************/
				#define csf_thread_pool_max_failure_times				30				//��ʾĬ�ϵ����ʧ�ܴ���
				/************************************************************************/
				/* Ĭ�ϵĴ����̼߳��ʱ�䣬��λ�����루ms�� 								*/
				/************************************************************************/
				#define csf_thread_pool_create_thread_interval_ms		100				//��ʾĬ�ϵĴ����̼߳��ʱ�䣬��λ�����루ms��
				/**
				 * ��ʾ�̳߳��������ͣ������߳��鼰�����������
				 * @author f
				 * @version 1.0
				 * @updated 21-10��-2018 16:53:55
				 */
				class csf_thread_pool
				{

				public:
					csf_thread_pool();
					virtual ~csf_thread_pool();
					/**
					* ��Ҫ�����ǣ������̳߳�
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param func    ��ʾ�����̵߳����к���
					*/
					template<typename TheadFunction>
					csf_int32 start(TheadFunction func) {

						csf_thread				*tmp_thread = csf_nullptr;
						csf_int32				tmp_thread_number = 0;
						csf_uint32				tmp_failure_times = 0;
						csf_int32				i = 0;


						//�ж��߳������ĺϷ���
						if (get_thread_number() <= 0) {
							return csf_failure;
						}

						//���������̶߳���
						while (csf_true) {

							tmp_thread = get_group().create_thread(func);
							if (csf_nullptr == tmp_thread) {
								//��������߳�ʧ�ܣ���ȴ�һ��ʱ����ٳ��Դ���
								csf_msleep(csf_thread_pool_create_thread_interval_ms);

								//������󳬹�������������ֱ�ӷ��ش���
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
					* ��Ҫ�����ǣ������̳߳أ�ͬʱָ���߳�����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param thread_number    ��ʾ��Ҫ�������߳�����
					* @param func    ��ʾ�����̵߳����к���
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
					* ��Ҫ�����ǣ�ֹͣ�̳߳�
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					inline csf_int32 stop() {

						get_group().join_all();
						get_group().clear();

						return 0;
					}
					/**
					* ��Ҫ�����ǣ���ʾ��ָ����ʱ���ڣ�ֹͣ�̳߳�
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*
					* @param timeout_ms    ��ʾ�ȴ���ʱʱ�䣬��λ����
					*/
					inline csf_int32 stop(const csf_uint64 timeout_ms) {

						if (timeout_ms <= 0) {
							return -1;
						}

						get_group().timed_join_all(timeout_ms);

						return 0;
					}
					/**
					* ��ʾ�̳߳ص��߳�������Ĭ��Ϊ2
					*/
					inline csf_uint32 get_thread_number() {

						return m_thread_number;
					}
					/**
					* ��ʾ�̳߳ص��߳�������Ĭ��Ϊ2
					*
					* @param new_value
					*/
					inline void set_thread_number(csf_uint32 new_value) {

						m_thread_number = new_value;
					}
					/**
					* ��ʾ���ʧ�ܴ���
					*/
					inline csf_uint32 get_max_failure_times() {

						return m_max_failure_times;
					}
					/**
					* ��ʾ���ʧ�ܴ���
					*
					* @param new_value
					*/
					inline void set_max_failure_times(csf_uint32 new_value) {

						m_max_failure_times = new_value;
					}
				protected:
					/**
					* ��ʾ�߳���������ڱ�������߳���Ϣ
					*/
					inline csf::core::utils::thread::csf_thread_group& get_group() {

						return m_group;
					}
					
				private:
					/**
					 * ��ʾ�߳���������ڱ�������߳���Ϣ
					 */
					csf::core::utils::thread::csf_thread_group m_group;
					/**
					* ��ʾ�̳߳ص��߳�������Ĭ��Ϊ2
					*/
					csf_uint32 m_thread_number = csf_thread_pool_default_thread_number;
					/**
					* ��ʾ���ʧ�ܴ���
					*/
					csf_uint32 m_max_failure_times = csf_thread_pool_max_failure_times;
				};

			}

		}

	}

}
#endif // !defined(CSF_THREAD_POOL_H_INCLUDED_)
