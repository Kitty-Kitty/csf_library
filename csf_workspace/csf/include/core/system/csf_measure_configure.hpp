/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_measure_configure.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 01-7月-2018 12:10:40
*
*Description: Class(csf_measure_configure)表示系统性能配置项
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MEASURE_CONFIGURE_INCLUDED_)
#define CSF_MEASURE_CONFIGURE_INCLUDED_


#include "csf_typedef.h"
#include "csf_default.h"
#include "csf_stddef.h"

using namespace csf::core::base;


namespace csf
{
	namespace core
	{
		namespace system
		{
			//表示measure_configure字符串格式化缓存的默认长度
			#define csf_measure_configure_string_length					256

			/**
			 * 表示系统性能配置项
			 * @author f
			 * @version 1.0
			 * @created 01-7月-2018 12:10:40
			 */
			class csf_measure_configure
			{

			public:
				inline explicit csf_measure_configure()
				    : m_device_limit(csf_default_device_limit)
					, m_device_io_limit(csf_default_device_io_limit)
					, m_timer_resolution(csf_default_timer_resolution)
					, m_connect_limit(csf_default_connect_limit)
					, m_time_resolution(csf_default_time_resolution)
				 {

				}
				inline virtual ~csf_measure_configure() {

				}
				/**
				 * 表示设备device的最大数量
				 */
				inline csf_uint32 get_device_limit() {

					return m_device_limit;
				}
				/**
				 * 表示设备device的最大数量
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_device_limit(const csf_uint32 new_value) {

					m_device_limit = new_value;
				}
				/**
				 * 表示设备device_io的最大数量
				 */
				inline csf_uint32 get_device_io_limit() {

					return m_device_io_limit;
				}
				/**
				 * 表示设备device_io的最大数量
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_device_io_limit(const csf_uint32 new_value) {

					m_device_io_limit = new_value;
				}
				/**
				 * 表示定时器的时间精度，就是定时器每一次查询的间隔
				 */
				inline csf_uint64 get_timer_resolution() {

					return m_timer_resolution;
				}
				/**
				 * 表示定时器的时间精度，就是定时器每一次查询的间隔
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_timer_resolution(const csf_uint64 new_value) {

					m_timer_resolution = new_value;
				}
				/**
				 * 表示系统时间的时间精度，主要是用于系统自身维护的时间内容
				 */
				inline csf_uint64 get_time_resolution() {

					return m_time_resolution;
				}
				/**
				 * 表示系统时间的时间精度，主要是用于系统自身维护的时间内容
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_time_resolution(const csf_uint64 new_value) {

					m_time_resolution = new_value;
				}
				/**
				 * 表示连接的极限数据
				 */
				inline csf_uint32 get_connect_limit() {

					return m_connect_limit;
				}
				/**
				 * 表示连接的极限数据
				 * 
				 * @param new_value
				 */
				inline csf_void set_connect_limit(const csf_uint32 new_value) {

					m_connect_limit = new_value;
				}
				/**
				* 表示将负载信息格式化输出
				*/
				inline csf_string to_string() {

					csf_char				tmp_buf[csf_measure_configure_string_length] = { 0, };

					csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
						, "measure_configure[device_measure:%d  device_io_measure:%d  connect_measure:%d time_resolution:%lld ms  timer_resolution: %lld ms]."
						, m_device_limit
						, m_device_io_limit
						, m_connect_limit
						, m_time_resolution
						, m_timer_resolution
					);

					return tmp_buf;
				}
			private:
				/**
				 * 表示设备device的最大数量
				 */
				csf_uint32 m_device_limit = csf_default_device_limit;
				/**
				 * 表示设备device_io的最大数量
				 */
				csf_uint32 m_device_io_limit = csf_default_device_io_limit;
				/**
				 * 表示定时器的时间精度，就是定时器每一次查询的间隔，单位：毫秒。
				 */
				csf_uint64 m_timer_resolution = csf_default_timer_resolution;
				/**
				 * 表示连接的极限数据
				 */
				csf_uint32 m_connect_limit = csf_default_connect_limit;
				/**
				 * 表示系统时间的时间精度，主要是用于系统自身维护的时间内容，单位：毫秒。
				 */
				csf_uint64 m_time_resolution = csf_default_time_resolution;

			};

		}

	}

}
#endif // !defined(CSF_MEASURE_CONFIGURE_INCLUDED_)
