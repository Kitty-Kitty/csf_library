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
					csf_thread();
					virtual ~csf_thread();
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
				private:
					/**
					* 表示线程状态信息
					*/
					csf_thread_status m_status = csf_thread_status_none;
				};
			}

		}

	}

}
#endif // !defined(CSF_THREAD_INCLUDED_)
