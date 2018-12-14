/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: time_maker.hpp
*
*Version: 1.0
*
*Date: 04-11月-2018 10:45:10
*
*Description: Class(time_maker) 时间生成器，主要用于生成系统使用的时间，包括：实际时间、系统时间、运行时间等等；其中各种时间单位：毫秒（ms）。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(TIME_MAKER_H_INCLUDED_)
#define TIME_MAKER_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_thread.hpp"

#ifdef WIN32
#include <sysinfoapi.h>
typedef void						csf_timezone;
#else
#include <sys/time.h>
typedef struct timezone				csf_timezone;
#endif

namespace csf
{
	namespace core
	{
		namespace utils
		{
			namespace time
			{
				/************************************************************************/
				/* 表示时间生成器的处理精度，单位：毫秒（ms）。默认为：1000ms				*/
				/************************************************************************/
				#define csf_time_maker_resolution_ms		1000						//表示时间生成器的处理精度，单位：毫秒（ms）。默认为：1000ms
				/**
				 * 时间生成器，主要用于生成系统使用的时间，包括：实际时间、系统时间、运行时间等等；其中各种时间单位：毫秒（ms）。
				 * @author f
				 * @version 1.0
				 * @created 04-11月-2018 10:45:10
				 */
				class time_maker
				{
				public:

					/**
					* 表示time_maker的释放类，主要负责单例对象的delete释放。
					* @author f
					* @version 1.0
					* @created 04-11月-2018 14:22:43
					*/
					class time_maker_release
					{
					public:
						time_maker_release() {

						}
						virtual ~time_maker_release() {

							csf_unqiue_lock<decltype(time_maker::m_mutex)> tmp_lock(time_maker::m_mutex);

							if (csf_nullptr != time_maker::m_instance) {

								time_maker::m_instance->stop();
								delete time_maker::m_instance;
								time_maker::m_instance = csf_nullptr;
							}
						}
					};
				private:
					explicit time_maker()
						: m_time_resolution(csf_time_maker_resolution_ms)
						, m_time(0)
						, m_native_time(0)
						, m_begin_time(0)
						, m_time_thread(csf_nullptr) {

					}
					virtual ~time_maker() {

					}
					time_maker & operator=(const time_maker &) = delete;
					time_maker(const time_maker &) = delete;

				public:
					/**
					* 表示单例对象指针
					*/
					inline static time_maker* get_instance() {

						if (csf_nullptr != m_instance) {
							return m_instance;
						}

						{
							csf_unqiue_lock<decltype(m_mutex)> tmp_lock(m_mutex);

							if (csf_nullptr != m_instance) {
								return m_instance;
							}
							else {
								m_instance = new time_maker();
								m_instance->init();
								m_instance->start();

								return m_instance;
							}
						}

						return m_instance;
					}
					/**
					* 表示时间生成器的时间精度，主要描述各种时间的生成精度，单位：毫秒（ms）
					*/
					inline csf_uint64 get_time_resolution() const {

						return m_time_resolution;
					}
					/**
					* 表示时间生成器的时间精度，主要描述各种时间的生成精度，单位：毫秒（ms）
					* 如果时间数值为0，则表示采用默认时间精度
					*
					* @param newVal
					*/
					inline void set_time_resolution(csf_uint64 newVal) {

						if (0 == newVal) {
							m_time_resolution = csf_time_maker_resolution_ms;
						}
						else {
							m_time_resolution = newVal;
						}
					}
					/**
					* 表示系统维护的相对时间。因为该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的相对时间计时（如连接对象的超时、各种处理的超时计时），而不能
					* 当作操作系统时间使用。单位：毫秒（ms）
					*/
					inline csf_uint64 get_time() const {

						return m_time;
					}
					/**
					* 表示系统维护的系统时间，通过实时获取系统时间而生成。该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的系统时间。单位：毫秒（ms）
					*/
					inline csf_uint64 get_native_time() const {

						return m_native_time;
					}
					/**
					* 表示系统的启动时间。该数值等于第一个time时间。所以time减去begin_time所得时间为系统到目前为止的运行总时间。单位：毫秒（ms）
					*/
					inline csf_uint64 get_begin_time() const {

						return m_begin_time;
					}
					/**
					* 主要功能是：获取当前的系统时间
					* 返回：0表示成功；非0表示失败；
					*
					* @param tv
					* @param tz
					*/
					static csf_int32 csf_gettimeofday(struct timeval* tv, csf_timezone* tz) {
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
					* 主要功能是：获取当前的系统时间的毫秒数值，单位：毫秒（ms）
					* 返回：当前系统时间的毫秒数值
					*/
					inline static csf_uint64 gettimeofday_millsecond() {

						struct timeval			tmp_timeval = { 0, };

						csf_gettimeofday(&tmp_timeval, csf_nullptr);

						return ((csf_uint64)(tmp_timeval.tv_sec) * 1000) + (tmp_timeval.tv_usec / 1000);
					}
				private:
					/**
					* 表示时间生成器的时间精度，主要描述各种时间的生成精度，单位：毫秒（ms）
					*/
					csf_atomic_uint64 m_time_resolution{ 0 };
					/**
					* 表示系统维护的相对时间。因为该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的相对时间计时（如连接对象的超时、各种处理的超时计时），而不能
					* 当作操作系统时间使用。单位：毫秒（ms）
					*/
					csf_atomic_uint64 m_time{ 0 };
					/**
					* 表示系统维护的系统时间，通过实时获取系统时间而生成。该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的系统时间。单位：毫秒（ms）
					*/
					csf_atomic_uint64 m_native_time{ 0 };
					/**
					* 表示系统的启动时间。该数值等于第一个time时间。所以time减去begin_time所得时间为系统到目前为止的运行总时间。单位：毫秒（ms）
					*/
					csf_atomic_uint64 m_begin_time{ 0 };
					/**
					* 表示当前的时间处理线程，用于时间和生成处理
					*/
					csf::core::utils::thread::csf_thread *m_time_thread = csf_nullptr;
					/**
					* 表示单例对象指针
					*/
					static time_maker* m_instance;
					/**
					* 表示time_maker的内部释放对象
					*/
					time_maker_release m_instance_release;
					/**
					* 表示单例对象访问互斥量
					*/
					static csf::core::utils::thread::csf_shared_mutex m_mutex;
					/**
					* 表示线程对象访问互斥量
					*/
					csf::core::utils::thread::csf_shared_mutex m_thread_mutex;
					/**
					* 表示系统维护的相对时间。因为该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的相对时间计时（如连接对象的超时、各种处理的超时计时），而不能
					* 当作操作系统时间使用。
					*
					* @param newVal
					*/
					inline void set_time(csf_uint64 newVal) {

						m_time = newVal;
					}
					/**
					* 表示系统维护的系统时间，通过实时获取系统时间而生成。该时间与操作系统时间存在一定的时间差距，所以该时间仅用于不需要很高精度的系统时间。
					*
					* @param newVal
					*/
					inline void set_native_time(csf_uint64 newVal) {

						m_native_time = newVal;
					}
					/**
					* 表示系统的启动时间。该数值等于第一个time时间。所以time减去begin_time所得时间为系统到目前为止的运行总时间。
					*
					* @param newVal
					*/
					inline void set_begin_time(csf_uint64 newVal) {

						m_begin_time = newVal;
					}
					/**
					* 主要功能是：时间生成线程处理函数。
					* 主要处理过程为：1、获取本地时间，更新本地时间；2、将当前时间增加一个时间刻度；
					* 返回：无
					*/
					csf_void time_cycle();
					/**
					* 表示当前的时间处理线程，用于时间和生成处理
					*/
					inline csf::core::utils::thread::csf_thread* get_time_thread() {

						return m_time_thread;
					}
					/**
					* 表示当前的时间处理线程，用于时间和生成处理
					*
					* @param newVal
					*/
					inline void set_time_thread(csf::core::utils::thread::csf_thread* newVal) {
						m_time_thread = newVal;
					}
					/**
					* 主要功能是：初始化time_maker对象
					* 返回：0表示成功；非0表示失败；
					*/
					inline csf_int32 init() {

						set_begin_time(gettimeofday_millsecond());
						set_time(get_begin_time());
						set_native_time(get_begin_time());

						return csf_succeed;
					}
					/**
					* 主要功能是：启动time_maker对象
					* 返回：0表示成功；非0表示失败；
					*/
					inline csf_int32 start() {

						csf_unqiue_lock<decltype(m_thread_mutex)> tmp_lock(m_thread_mutex);

						set_time_thread(
							new csf::core::utils::thread::csf_thread(csf_bind(&time_maker::time_cycle, this)));

						return csf_succeed;
					}
					/**
					* 主要功能是：停止time_maker对象
					* 返回：0表示成功；非0表示失败；
					*/
					inline csf_int32 stop() {

						csf_unqiue_lock<decltype(m_thread_mutex)> tmp_lock(m_thread_mutex);

						if (csf_nullptr != get_time_thread()) {
							get_time_thread()->timed_join(m_time_resolution);
							delete get_time_thread();
							set_time_thread(csf_nullptr);
						}
						return csf_succeed;
					}
				};
				
			}

		}

	}

}
#endif // !defined(TIME_MAKER_H_INCLUDED_)
