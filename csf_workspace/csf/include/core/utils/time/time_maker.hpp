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
*Date: 04-11��-2018 10:45:10
*
*Description: Class(time_maker) ʱ������������Ҫ��������ϵͳʹ�õ�ʱ�䣬������ʵ��ʱ�䡢ϵͳʱ�䡢����ʱ��ȵȣ����и���ʱ�䵥λ�����루ms����
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
				/* ��ʾʱ���������Ĵ����ȣ���λ�����루ms����Ĭ��Ϊ��1000ms				*/
				/************************************************************************/
				#define csf_time_maker_resolution_ms		1000						//��ʾʱ���������Ĵ����ȣ���λ�����루ms����Ĭ��Ϊ��1000ms
				/**
				 * ʱ������������Ҫ��������ϵͳʹ�õ�ʱ�䣬������ʵ��ʱ�䡢ϵͳʱ�䡢����ʱ��ȵȣ����и���ʱ�䵥λ�����루ms����
				 * @author f
				 * @version 1.0
				 * @created 04-11��-2018 10:45:10
				 */
				class time_maker
				{
				public:

					/**
					* ��ʾtime_maker���ͷ��࣬��Ҫ�����������delete�ͷš�
					* @author f
					* @version 1.0
					* @created 04-11��-2018 14:22:43
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
					* ��ʾ��������ָ��
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
					* ��ʾʱ����������ʱ�侫�ȣ���Ҫ��������ʱ������ɾ��ȣ���λ�����루ms��
					*/
					inline csf_uint64 get_time_resolution() const {

						return m_time_resolution;
					}
					/**
					* ��ʾʱ����������ʱ�侫�ȣ���Ҫ��������ʱ������ɾ��ȣ���λ�����루ms��
					* ���ʱ����ֵΪ0�����ʾ����Ĭ��ʱ�侫��
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
					* ��ʾϵͳά�������ʱ�䡣��Ϊ��ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ����ʱ���ʱ�������Ӷ���ĳ�ʱ�����ִ���ĳ�ʱ��ʱ����������
					* ��������ϵͳʱ��ʹ�á���λ�����루ms��
					*/
					inline csf_uint64 get_time() const {

						return m_time;
					}
					/**
					* ��ʾϵͳά����ϵͳʱ�䣬ͨ��ʵʱ��ȡϵͳʱ������ɡ���ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ�ϵͳʱ�䡣��λ�����루ms��
					*/
					inline csf_uint64 get_native_time() const {

						return m_native_time;
					}
					/**
					* ��ʾϵͳ������ʱ�䡣����ֵ���ڵ�һ��timeʱ�䡣����time��ȥbegin_time����ʱ��Ϊϵͳ��ĿǰΪֹ��������ʱ�䡣��λ�����루ms��
					*/
					inline csf_uint64 get_begin_time() const {

						return m_begin_time;
					}
					/**
					* ��Ҫ�����ǣ���ȡ��ǰ��ϵͳʱ��
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
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
					* ��Ҫ�����ǣ���ȡ��ǰ��ϵͳʱ��ĺ�����ֵ����λ�����루ms��
					* ���أ���ǰϵͳʱ��ĺ�����ֵ
					*/
					inline static csf_uint64 gettimeofday_millsecond() {

						struct timeval			tmp_timeval = { 0, };

						csf_gettimeofday(&tmp_timeval, csf_nullptr);

						return ((csf_uint64)(tmp_timeval.tv_sec) * 1000) + (tmp_timeval.tv_usec / 1000);
					}
				private:
					/**
					* ��ʾʱ����������ʱ�侫�ȣ���Ҫ��������ʱ������ɾ��ȣ���λ�����루ms��
					*/
					csf_atomic_uint64 m_time_resolution{ 0 };
					/**
					* ��ʾϵͳά�������ʱ�䡣��Ϊ��ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ����ʱ���ʱ�������Ӷ���ĳ�ʱ�����ִ���ĳ�ʱ��ʱ����������
					* ��������ϵͳʱ��ʹ�á���λ�����루ms��
					*/
					csf_atomic_uint64 m_time{ 0 };
					/**
					* ��ʾϵͳά����ϵͳʱ�䣬ͨ��ʵʱ��ȡϵͳʱ������ɡ���ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ�ϵͳʱ�䡣��λ�����루ms��
					*/
					csf_atomic_uint64 m_native_time{ 0 };
					/**
					* ��ʾϵͳ������ʱ�䡣����ֵ���ڵ�һ��timeʱ�䡣����time��ȥbegin_time����ʱ��Ϊϵͳ��ĿǰΪֹ��������ʱ�䡣��λ�����루ms��
					*/
					csf_atomic_uint64 m_begin_time{ 0 };
					/**
					* ��ʾ��ǰ��ʱ�䴦���̣߳�����ʱ������ɴ���
					*/
					csf::core::utils::thread::csf_thread *m_time_thread = csf_nullptr;
					/**
					* ��ʾ��������ָ��
					*/
					static time_maker* m_instance;
					/**
					* ��ʾtime_maker���ڲ��ͷŶ���
					*/
					time_maker_release m_instance_release;
					/**
					* ��ʾ����������ʻ�����
					*/
					static csf::core::utils::thread::csf_shared_mutex m_mutex;
					/**
					* ��ʾ�̶߳�����ʻ�����
					*/
					csf::core::utils::thread::csf_shared_mutex m_thread_mutex;
					/**
					* ��ʾϵͳά�������ʱ�䡣��Ϊ��ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ����ʱ���ʱ�������Ӷ���ĳ�ʱ�����ִ���ĳ�ʱ��ʱ����������
					* ��������ϵͳʱ��ʹ�á�
					*
					* @param newVal
					*/
					inline void set_time(csf_uint64 newVal) {

						m_time = newVal;
					}
					/**
					* ��ʾϵͳά����ϵͳʱ�䣬ͨ��ʵʱ��ȡϵͳʱ������ɡ���ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ�ϵͳʱ�䡣
					*
					* @param newVal
					*/
					inline void set_native_time(csf_uint64 newVal) {

						m_native_time = newVal;
					}
					/**
					* ��ʾϵͳ������ʱ�䡣����ֵ���ڵ�һ��timeʱ�䡣����time��ȥbegin_time����ʱ��Ϊϵͳ��ĿǰΪֹ��������ʱ�䡣
					*
					* @param newVal
					*/
					inline void set_begin_time(csf_uint64 newVal) {

						m_begin_time = newVal;
					}
					/**
					* ��Ҫ�����ǣ�ʱ�������̴߳�������
					* ��Ҫ�������Ϊ��1����ȡ����ʱ�䣬���±���ʱ�䣻2������ǰʱ������һ��ʱ��̶ȣ�
					* ���أ���
					*/
					csf_void time_cycle();
					/**
					* ��ʾ��ǰ��ʱ�䴦���̣߳�����ʱ������ɴ���
					*/
					inline csf::core::utils::thread::csf_thread* get_time_thread() {

						return m_time_thread;
					}
					/**
					* ��ʾ��ǰ��ʱ�䴦���̣߳�����ʱ������ɴ���
					*
					* @param newVal
					*/
					inline void set_time_thread(csf::core::utils::thread::csf_thread* newVal) {
						m_time_thread = newVal;
					}
					/**
					* ��Ҫ�����ǣ���ʼ��time_maker����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					inline csf_int32 init() {

						set_begin_time(gettimeofday_millsecond());
						set_time(get_begin_time());
						set_native_time(get_begin_time());

						return csf_succeed;
					}
					/**
					* ��Ҫ�����ǣ�����time_maker����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
					*/
					inline csf_int32 start() {

						csf_unqiue_lock<decltype(m_thread_mutex)> tmp_lock(m_thread_mutex);

						set_time_thread(
							new csf::core::utils::thread::csf_thread(csf_bind(&time_maker::time_cycle, this)));

						return csf_succeed;
					}
					/**
					* ��Ҫ�����ǣ�ֹͣtime_maker����
					* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
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
