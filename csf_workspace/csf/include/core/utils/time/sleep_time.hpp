/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: sleep_time.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 18:12:40
*
*Description: Class(sleep_time) 表示系统休眠类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_SLEEP_TIME_H_INCLUDED_)
#define CSF_SLEEP_TIME_H_INCLUDED_

#include<stdio.h>
#if defined(__linux__)
#include <time.h>
#include <sys/time.h>
#endif
#if defined(WIN32)
#include <windows.h>
#endif

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace time
			{
				/**
				 * 表示系统休眠类
				 * @author f
				 * @version 1.0
				 * @created 07-12月-2019 18:12:40
				 */
				class sleep_time
				{

				public:
					sleep_time();
					virtual ~sleep_time();

					/**
					 * 功能：
					 *    表示纳秒级的休眠等待时间
					 * 返回：
					 *    无
					 * 
					 * @param s    表示当前休眠秒数
					 * @param ns    表示当前休眠纳秒数
					 */
					static void sleep_ns(unsigned int s, unsigned int ns);
					/**
					 * 功能：
					 *    表示纳秒级的休眠等待时间
					 * 返回：
					 *    无
					 * 
					 * @param ns    表示当前休眠纳秒数
					 */
					inline static void sleep_ns(unsigned int ns) {
						return sleep_ns(0, ns);
					}
					/**
					 * 功能：
					 *    表示毫秒级的休眠等待时间
					 * 返回：
					 *    无
					 * 
					 * @param ms    表示当前休眠毫秒数
					 */
					inline static void sleep_ms(unsigned int ms) {
						return sleep_ns(0, ms * 1000);
					}
					/**
					 * 功能：
					 *    表示秒级的休眠等待时间
					 * 返回：
					 *    无
					 * 
					 * @param s    表示当前休眠秒数
					 */
					static void sleep(unsigned int s) {
						#if defined(__linux__)
							sleep(s);
						#endif
						#if defined(WIN32)
							Sleep(s * 1000);
						#endif
					}

				};

			}

		}

	}

}
#endif // !defined(CSF_SLEEP_TIME_H_INCLUDED_)
