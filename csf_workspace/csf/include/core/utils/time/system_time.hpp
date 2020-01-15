/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: system_time.hpp
*
*Version: 1.0
*
*Date: 04-11月-2018 14:22:42
*
*Description: Class(system_time) 表示系统时间处理类内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(SYSTEM_TIME_H_INCLUDED_)
#define SYSTEM_TIME_H_INCLUDED_

#include "csf_base_include.h"
#include "time_maker.hpp"

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace time
			{
				/**
				 * 表示系统时间处理类内容
				 * @author f
				 * @version 1.0
				 * @created 04-11月-2018 14:22:42
				 */
				class system_time
				{

				public:
					system_time();
					virtual ~system_time();

					/**
					 * 表示时间生成器的时间精度，主要描述各种时间的生成精度，单位：毫秒（ms）
					 */
					inline static csf_uint64 get_time_resolution() {

						return time_maker::get_instance()->get_time_resolution();
					}
					/**
					 * 表示时间生成器的时间精度，主要描述各种时间的生成精度，单位：毫秒（ms）
					 * 
					 * @param new_value
					 */
					inline static void set_time_resolution(csf_uint64 new_value) {

						time_maker::get_instance()->set_time_resolution(new_value);
					}
					/**
					 * 表示系统维护的相对时间。因为该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的相对时间计时（如连接对象的超时、各种处理的超时计时），而不能
					 * 当作操作系统时间使用。单位：毫秒（ms）
					 */
					inline static csf_uint64 get_time() {

						return time_maker::get_instance()->get_time();
					}
					/**
					 * 表示系统维护的系统时间，通过实时获取系统时间而生成。该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的系统时间。单位：毫秒（ms）
					 */
					inline static csf_uint64 get_native_time() {

						return time_maker::get_instance()->get_native_time();
					}
					/**
					 * 表示系统的启动时间。该数值等于第一个time时间。所以time减去begin_time所得时间为系统到目前为止的运行总时间。单位：毫秒（ms）
					 */
					inline static csf_uint64 get_begin_time() {

						return time_maker::get_instance()->get_begin_time();
					}
					/**
					 * 主要功能是：获取当前的系统时间
					 * 返回：0表示成功；非0表示失败；
					 * 
					 * @param tv
					 * @param tz
					 */
					inline static csf_int32 gettimeofday(csf_timeval* tv, csf_timezone* tz) {

						return time_maker::csf_gettimeofday(tv, tz);
					}

				};

			}

		}

	}

}
#endif // !defined(SYSTEM_TIME_H_INCLUDED_)
