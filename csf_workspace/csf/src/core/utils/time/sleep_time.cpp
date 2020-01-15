/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: sleep_time.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 18:12:40
*
*Description: Class(sleep_time)
*
*Others:
*
*History:
*
*******************************************************************************/
#include <errno.h>
#include "sleep_time.hpp"

using csf::core::utils::time::sleep_time;


sleep_time::sleep_time() {

}



sleep_time::~sleep_time() {

}





/**
 * 功能：
 *    表示纳秒级的休眠等待时间
 * 返回：
 *    无
 * 
 * @param s    表示当前休眠秒数
 * @param ns    表示当前休眠纳秒数
 */
void sleep_time::sleep_ns(unsigned int s, unsigned int ns) {

#if defined(__linux__)

	struct timespec requested, remaining;

	requested.tv_sec = s;
	requested.tv_nsec = ns;

	while (nanosleep(&requested, &remaining) == -1)
		if (errno == EINTR)
			requested = remaining;
		else {
			break;
		}

#else
	Sleep(s * 1000 + ns / 1000);
#endif
}

