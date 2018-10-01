/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_deadline_timer.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:40
*
*Description: Class(csf_deadline_timer) 表示截止期限定时器，用于网络收发超时定时器。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DEADLINE_TIMER_H_INCLUDED_)
#define CSF_DEADLINE_TIMER_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 表示截止期限定时器，用于网络收发超时定时器。
				 * @author f
				 * @version 1.0
				 * @created 01-10月-2018 12:54:40
				 */
				class csf_deadline_timer
				{

				public:
					csf_deadline_timer();
					virtual ~csf_deadline_timer();

				};

			}

		}

	}

}
#endif // !defined(CSF_DEADLINE_TIMER_H_INCLUDED_)
