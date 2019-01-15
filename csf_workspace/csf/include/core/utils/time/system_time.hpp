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
*Date: 04-11��-2018 14:22:42
*
*Description: Class(system_time) ��ʾϵͳʱ�䴦��������
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
				 * ��ʾϵͳʱ�䴦��������
				 * @author f
				 * @version 1.0
				 * @created 04-11��-2018 14:22:42
				 */
				class system_time
				{

				public:
					system_time();
					virtual ~system_time();

					/**
					 * ��ʾʱ����������ʱ�侫�ȣ���Ҫ��������ʱ������ɾ��ȣ���λ�����루ms��
					 */
					inline static csf_uint64 get_time_resolution() {

						return time_maker::get_instance()->get_time_resolution();
					}
					/**
					 * ��ʾʱ����������ʱ�侫�ȣ���Ҫ��������ʱ������ɾ��ȣ���λ�����루ms��
					 * 
					 * @param newVal
					 */
					inline static void set_time_resolution(csf_uint64 newVal) {

						time_maker::get_instance()->set_time_resolution(newVal);
					}
					/**
					 * ��ʾϵͳά�������ʱ�䡣��Ϊ��ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ����ʱ���ʱ�������Ӷ���ĳ�ʱ�����ִ���ĳ�ʱ��ʱ����������
					 * ��������ϵͳʱ��ʹ�á���λ�����루ms��
					 */
					inline static csf_uint64 get_time() {

						return time_maker::get_instance()->get_time();
					}
					/**
					 * ��ʾϵͳά����ϵͳʱ�䣬ͨ��ʵʱ��ȡϵͳʱ������ɡ���ʱ�������ϵͳʱ�����һ����ʱ���࣬���Ը�ʱ������ڲ���Ҫ�ܸ߾��ȵ�ϵͳʱ�䡣��λ�����루ms��
					 */
					inline static csf_uint64 get_native_time() {

						return time_maker::get_instance()->get_native_time();
					}
					/**
					 * ��ʾϵͳ������ʱ�䡣����ֵ���ڵ�һ��timeʱ�䡣����time��ȥbegin_time����ʱ��Ϊϵͳ��ĿǰΪֹ��������ʱ�䡣��λ�����루ms��
					 */
					inline static csf_uint64 get_begin_time() {

						return time_maker::get_instance()->get_begin_time();
					}
					/**
					 * ��Ҫ�����ǣ���ȡ��ǰ��ϵͳʱ��
					 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
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
