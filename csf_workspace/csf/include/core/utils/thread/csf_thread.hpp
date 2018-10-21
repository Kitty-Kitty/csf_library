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
					csf_thread();
					virtual ~csf_thread();
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
				private:
					/**
					* ��ʾ�߳�״̬��Ϣ
					*/
					csf_thread_status m_status = csf_thread_status_none;
				};
			}

		}

	}

}
#endif // !defined(CSF_THREAD_INCLUDED_)
