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
*Date: 29-7月-2018 11:04:52
*
*Description: Class(csf_deadline_timer) 表示截止期限定时器，用于网络收发超时定时器。
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEADLINE_TIMER_INCLUDED_)
#define CSF_DEADLINE_TIMER_INCLUDED_

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
				 * @created 29-7月-2018 11:04:52
				 */
				class csf_deadline_timer
				{

				public:
					csf_deadline_timer() {

					}
					virtual ~csf_deadline_timer() {

					}

				};

			}

		}

	}

}
#endif // !defined(CSF_DEADLINE_TIMER_INCLUDED_)
