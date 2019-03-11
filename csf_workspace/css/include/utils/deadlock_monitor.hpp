/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: deadlock_monitor.hpp
*
*Version: 1.0
*
*Date: 11-3月-2019 16:00:20
*
*Description: Class(deadlock_monitor) 该类是死锁监控类，实际上是一个简单的计数器类。主要工作原理是：根据死锁持续恶化的特点进行判断计数，如果持续指定时间出现类似的现象，则认为确实出现死锁了。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(DEADLOCK_MONITOR_H_INCLUDED_)
#define DEADLOCK_MONITOR_H_INCLUDED_

#include<iostream>
#include <atomic>
#include <limits>


#ifdef WIN32
#include <Windows.h>
typedef void					dm_timezone;
/*
* Structure used in select() call, taken from the BSD file sys/time.h.
*/
typedef struct dm_timeval_s {
	long    tv_sec;         /* seconds */
	long    tv_usec;        /* and microseconds */
} dm_timeval;
#else
#include <sys/time.h>
typedef struct timeval			dm_timeval;
typedef struct timezone			dm_timezone;
#endif

namespace css
{
	namespace utils
	{
		/************************************************************************/
		/* 表示最小的时间间隔，单位：毫秒（ms）。默认为：1000ms				        */
		/************************************************************************/
		#define dm_min_step_time_ms		1000
		/************************************************************************/
		/* 表示最大的错误次数。相当于std::numeric_limits<int>::max()				*/
		/************************************************************************/
		#define dm_max_count			0x7FFFFFFF
		/************************************************************************/
		/* 表示最小的错误次数。                                   				*/
		/************************************************************************/
		#define dm_min_count			1
		/************************************************************************/
		/* 表示各种异常的最大尝试次数。                                   			*/
		/************************************************************************/
		#define dm_max_try_times		3

		/**
		 * 该类是死锁监控类，实际上是一个简单的计数器类。主要工作原理是：根据死锁持续恶化的特点进行判断计数，如果持续指定时间出现类似的现象，则认为确实出现死锁了。
		 * @author fangzhenmu
		 * @version 1.0
		 * @updated 11-3月-2019 16:02:26
		 */
		class deadlock_monitor
		{

		public:
			/**
			* 根据死锁检测的间隔时间和最长持续时间创建对象。其中间隔时间最小为1000ms，最长持续时间该大于等于间隔时间。
			*/
			inline explicit deadlock_monitor()
				: m_count(0)
				, m_max_count(dm_max_count)
				, m_previous_time(0)
				, m_step_time(dm_min_step_time_ms) {

			}
			/**
			* 根据死锁检测的间隔时间和最长持续时间创建对象。其中间隔时间最小为1000ms，最长持续时间该大于等于间隔时间。程序内部将默认将最长持续时间转化为最大次数处理，故
			* 存在最大一个间隔时间的精度误差。最大次数计算方式为:  最大次数 = (持续时间 + 间隔时间) / 间隔时间
			*
			* @param continue_time    表示持续出现错误的时间（单位：毫秒）。该数值应该大于间隔时间。
			* @param step_time    表示判断的时间间隔（单位：毫秒），默认和最小值为1000ms。
			*/
			inline explicit deadlock_monitor(const std::uint64_t continue_time
				, const std::uint64_t step_time = dm_min_step_time_ms)
				: m_count(0)
				, m_max_count(dm_max_count)
				, m_previous_time(0)
				, m_step_time(dm_min_step_time_ms) {

				if (!set_time(continue_time, step_time)) {
					throw "time value error!";
				}
			}
			virtual ~deadlock_monitor() {

			}
			/**
			 * 表示当前已经连接出现死锁的次数
			 */
			inline std::uint32_t get_count() {

				return m_count;
			}
			/**
			 * 表示最多允许出现的次数，如果count>=max_count表示确定出现死锁
			 */
			inline std::uint32_t get_max_count() {

				return m_max_count;
			}
			/**
			 * 表示最多允许出现的次数，如果count>=max_count表示确定出现死锁
			 *
			 * @param newVal    当前的最大次数，最小值为1，默认为无穷大（uint32的最大值）
			 */
			inline bool set_max_count(const std::uint32_t newVal = dm_max_count) {

				if (newVal < dm_min_count) {
					return false;
				}

				m_max_count = newVal;
				return true;
			}
			/**
			 * 表示每次计算的合法时间间隔（单位:毫秒 ms）。默认数值为1000ms。只有本次判断与上次判断的时间差值超过该数值时，才能被认定为合法判断。
			 */
			inline std::uint64_t get_step_time() {

				return m_step_time;
			}
			/**
			 * 主要功能：
			 *    设置死锁检测的间隔时间和最长持续时间。其中间隔时间最小为1000ms，最长持续时间该大于等于间隔时间。
			 *    程序内部将默认将最长持续时间转化为最大次数处理，故存在最大一个间隔时间的精度误差。
			 *    最大次数计算方式为:  最大次数 = (持续时间 + 间隔时间) / 间隔时间
			 * 返回：
			 *    true：表示成功；
			 *    false：表示失败；
			 *
			 * @param continue_time    表示持续出现错误的时间（单位：毫秒）。该数值应该大于间隔时间。
			 * @param step_time    表示判断的时间间隔（单位：毫秒），默认和最小值为1000ms。
			 */
			inline bool set_time(const std::uint64_t continue_time
				, const std::uint64_t step_time = dm_min_step_time_ms) {

				if (step_time < dm_min_step_time_ms) {
					return false;
				}
				else {
					reset();
					set_step_time(step_time);
					set_max_count((std::uint32_t)((continue_time + step_time) / step_time));
				}

				return true;
			}
			/**
			 * 主要功能：
			 *    获取当前的持续时间，由最大次数与间隔时间计算而得到。与set_time中设置的持续时间最大存在一个间隔时间的误差。
			 * 返回：
			 *    当前持续时间（单位：毫秒）
			 */
			inline std::uint64_t get_continue_time() {

				return (get_step_time() * get_max_count());
			}
			/**
			 * 主要功能：
			 *    判断是否已经死锁了。当错误次数大于等于最大错误数量时，将返回成功，否则返回失败。
			 * 返回：
			 *    true：表示死锁；
			 *    false：表示不死锁；
			 */
			inline bool is_deadlock() {

				if (get_count() >= get_max_count()) {
					return true;
				}
				return false;
			}
			/**
			 * 主要功能：
			 *
			 * 每次调用该方法时，就认为使用者已经认定程序不正常，基本确认死锁发生了。需要累加一次死锁错误，二次处理间隔大于间隔时间表示合法数值，累加成功。否则返回失败。
			 * 返回：
			 *    true：表示累加成功；
			 *    false：表示累加失败；
			 */
			inline bool count() {

				std::uint64_t			tmp_current_time = 0;


				//获取当前时间
				tmp_current_time = dm_gettime();

				//如果时间合法，则开始累加计数
				if (time_valid(tmp_current_time)) {
					set_count(get_count() + 1);
					set_previous_time(tmp_current_time);
					return true;
				}
				return false;
			}
			/**
			 * 主要功能：
			 *    重置当前已经累加的次数，重新累加。
			 *    该方法表示：使用者认为目前是程序是对的，之前的死锁判断都是瞬时的。所以不能满足作为依据，需要重新开始统计。
			 * 返回：
			 *    无；
			 */
			inline void reset() {

				set_count(0);
			}
		private:
			/**
			* 表示当前已经连接出现死锁的次数
			*
			* @param newVal
			*/
			inline void set_count(std::uint32_t newVal) {

				m_count = newVal;
			}
			/**
			* 表示上次出现死锁的时间（单位:毫秒 ms）。
			*/
			inline std::uint64_t get_previous_time() {

				return m_previous_time;
			}
			/**
			* 表示上次出现死锁的时间（单位:毫秒 ms）。
			*
			* @param newVal
			*/
			inline void set_previous_time(std::uint64_t newVal) {

				m_previous_time = newVal;
			}
			/**
			* 表示每次计算的合法时间间隔（单位:毫秒 ms）。默认数值为1000ms。只有本次判断与上次判断的时间差值超过该数值时，才能被认定为合法判断。
			*
			* @param newVal
			*/
			inline void set_step_time(std::uint64_t newVal) {

				m_step_time = newVal;
			}
			/**
			* 主要功能：
			*    获取当前的系统时间。linux下采用gettimeofday，windows单独实现了类似功能。
			* 返回：
			*    0：表示成功；
			*    1：表示失败；
			*
			* @param tv    表示获取用返回和当前时间
			* @param tz    表示当前的时区信息
			*/
			inline std::int32_t dm_gettimeofday(dm_timeval* tv, dm_timezone* tz = nullptr) {
			#ifdef WIN32
				FILETIME time;
				double   timed;

				GetSystemTimeAsFileTime(&time);

				// Apparently Win32 has units of 1e-7 sec (tenths of microsecs)
				// 4294967296 is 2^32, to shift high word over
				// 11644473600 is the number of seconds between
				// the Win32 epoch 1601-Jan-01 and the Unix epoch 1970-Jan-01
				// Tests found floating point to be 10x faster than 64bit int math.

				timed = ((time.dwHighDateTime * 4294967296e-7) - 11644473600.0) +
					(time.dwLowDateTime  * 1e-7);

				tv->tv_sec = (long)timed;
				tv->tv_usec = (long)((timed - tv->tv_sec) * 1e6);
			#else
				return gettimeofday(tv, tz);
			#endif
				return 0;
			}
			/**
			* 主要功能：
			*    获取当前的系统时间的毫秒数值
			* 返回：
			*    当前系统时间的毫秒数值
			*/
			inline std::uint64_t dm_gettime() {

				dm_timeval				tmp_val = { 0, };


				for (int i = 0; i < dm_max_try_times; i++) {
					if (dm_gettimeofday(&tmp_val)) {
						continue;
					}
					else {
						break;
					}
				}

				return (tmp_val.tv_sec * 1000ll + tmp_val.tv_usec / 1000);
			}
			/**
			* 主要功能：
			*    判断当前时间的合法性。如果当前时间与上一次时间差大于一个时间间隔则表示合法，否则表示非法
			* 返回：
			*    true：表示合法；
			*    false：表示非法；
			*
			* @param time    表示需要被校验的时间
			*/
			inline bool time_valid(const std::uint64_t time) {

				std::uint64_t			tmp_div_time = 0;


				//判断目前参数的合法性
				if (time <= 0 || get_step_time() <= 0) {
					return false;
				}

				//取出连续两次的绝对时间差
				tmp_div_time = time > get_previous_time() ? time - get_previous_time() : get_previous_time() - time;

				//如果与上次处理的时间差值大于间隔时间，则
				if (tmp_div_time >= get_step_time()) {
					return true;
				}
				return false;
			}
		private:
			/**
			 * 表示当前已经连接出现死锁的次数
			 */
			std::atomic<std::uint32_t> m_count{ 0 };
			/**
			 * 表示最多允许出现的次数。默认为最大值，表示永不死锁。如果count>=max_count表示确定出现死锁
			 */
			std::atomic<std::uint32_t> m_max_count{ dm_max_count };
			/**
			 * 表示上次出现死锁的时间（单位:毫秒 ms）。
			 */
			std::atomic<std::uint64_t> m_previous_time{ 0 };
			/**
			 * 表示每次计算的合法时间间隔（单位:毫秒 ms）。默认数值为1000ms。只有本次判断与上次判断的时间差值超过该数值时，才能被认定为合法判断。
			 */
			std::atomic<std::uint64_t> m_step_time{ dm_min_step_time_ms };

		};

	}

}
#endif // !defined(DEADLOCK_MONITOR_H_INCLUDED_)
