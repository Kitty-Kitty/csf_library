/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: time_maker.hpp
*
*Version: 1.0
*
*Date: 04-11月-2018 10:45:10
*
*Description: Class(time_maker)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "time_maker.hpp"

using csf::core::utils::time_maker;




/**
* 主要功能是：时间生成线程处理函数。
* 主要处理过程为：1、获取本地时间，更新本地时间；2、将当前时间增加一个时间刻度；
* 返回：无
*/
csf_void time_maker::time_cycle() {

	set_native_time(gettimeofday_millsecond());
	csf_msleep((csf_uint32)m_time_resolution);
	set_time(get_time() + m_time_resolution);
}