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
*Date: 19-7��-2018 20:11:51
*
*Description: Class(csf_thread) ��ʾ�߳���
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
				* ��ʾ�߳���
				* @author f
				* @version 1.0
				* @created 21-10��-2018 20:23:45
				*/
				class csf_thread : public boost::thread
				{
				public:
					/**
					* ��ʾ�߳����е��û��������
					* @author f
					* @version 1.0
					* @created 01-10��-2018 12:54:37
					*/
					typedef csf_function<csf_void()> 	csf_thread_start_handle;
					/**
					* ��ʾ�߳�״̬�б�
					* @author f
					* @version 1.0
					* @updated 21-10��-2018 22:31:00
					*/
					typedef enum csf_thread_status_enum
					{
						/**
						* ��ʾ�߳�δ��ʼ��״̬
						*/
						csf_thread_status_none = 0x00,
						/**
						* ��ʾ�̳߳�ʼ��״̬
						*/
						csf_thread_status_init = 0x01,
						/**
						* ��ʾ�߳�����״̬
						*/
						csf_thread_status_start = 0x02,
						/**
						* ��ʾ�߳�ֹͣ״̬
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
					* ��Ҫ�����ǣ�ֹͣ�߳�
					* ���أ���
					*/
					inline csf_int32 stop() {

						set_status(csf_thread_status_stop);

						return 0;
					}
					/**
					* ��Ҫ�����ǣ��ȴ��߳��˳�
					* ���أ���
					*/
					inline void join() {
						if (stop()) {
							boost::thread::join();
						}
					}
					/**
					* ��Ҫ�����ǣ����̡߳��жϡ�ֹͣ
					* ���أ���
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
					* @param timeout_ms    ��ʾ��ʱ�ĵȴ���ֹ
					*/
					inline bool timed_join(const csf_uint64 timeout_ms) {

						if (stop()) {
							return boost::thread::timed_join(boost::posix_time::millisec(timeout_ms));
						}
						return true;
					}
				private:
					/**
					* ��ʾ�߳�״̬��Ϣ
					*/
					csf_thread_status m_status = csf_thread_status_none;
					/**
					* ��ʾ�߳�״̬��Ϣ
					*/
					inline csf_thread_status get_status() {

						return m_status;
					}
					/**
					* ��ʾ�߳�״̬��Ϣ
					*
					* @param newVal
					*/
					inline void set_status(csf_thread_status newVal) {

						m_status = newVal;
					}
					/**
					* ��Ҫ�����ǣ����������߳�
					* ���أ���
					*
					* @param func    ��ʾ�̵߳����к���
					*/
					void start(csf_thread_start_handle func) {

						set_status(csf_thread_status_start);
						cycle(func);
					}
					/**
					* ��Ҫ�����ǣ��߳����е�ѭ������
					* ���أ���
					*
					* @param func    ��ʾ�̵߳����к���
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
