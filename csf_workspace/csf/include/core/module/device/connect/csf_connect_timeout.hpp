/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_timeout.hpp
*
*Version: 1.0
*
*Date: 21-10月-2018 13:54:44
*
*Description: Class(csf_connect_timeout) 表示超时表述描述类型
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_TIMEOUT_H_INCLUDED_)
#define CSF_CONNECT_TIMEOUT_H_INCLUDED_

#include "csf_base_include.h"

#include "csf_connect_callback.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/************************************************************************/
				/* 表示默认的超时时间，单位：毫秒（ms）。默认为：5000ms						*/
				/************************************************************************/
				#define csf_connect_timeout_default_ms						5000		//表示默认的超时时间，单位：毫秒（ms）。默认为：5000ms
				/**
				 * 表示超时表述描述类型
				 * @author f
				 * @version 1.0
				 * @created 21-10月-2018 13:54:44
				 */
				class csf_connect_timeout
				{

				public:
					inline explicit csf_connect_timeout()
						: m_time(0)
						, m_timeout(csf_connect_timeout_default_ms)
						, m_handle(csf_nullptr) {

					}
					/**
					*
					* @param time    表示当前超时的时间数值，单位为毫秒（ms）
					*
					* @param handle    表示超时后的回调函数
					*/
					inline explicit csf_connect_timeout(const csf_uint64 time
						, const csf::core::module::connect::csf_connect_callback handle)
						: m_time(time)
						, m_timeout(csf_connect_timeout_default_ms)
						, m_handle(handle) {
					}
					/**
					* 主要功能是：通过时间、超时时间和回调函数创建一个超时对象
					*
					* @param time    表示当前超时的时间数值，单位为毫秒（ms）
					*
					* @param timeout
					* @param handle    表示超时后的回调函数
					*/
					inline explicit csf_connect_timeout(const csf_uint64 time
						, csf_uint64 timeout
						, const csf::core::module::connect::csf_connect_callback handle)
						: m_time(time)
						, m_timeout(timeout)
						, m_handle(handle) {

					}
					inline virtual ~csf_connect_timeout() {

					}
					/**
					* 主要功能是：timeout对象的赋值操作
					* 返回：timeout对象
					*
					* @param timeout    表示需要被赋值的timeout对象
					*/
					inline csf_connect_timeout& operator = (csf_connect_timeout& timeout) {

						set_time(timeout.get_time());
						set_timeout(timeout.get_timeout());
						set_handle(timeout.get_handle());

						return *this;
					}
					/**
					* 主要功能是：timeout对象是否相同
					* 返回：true表示相同；false表示不相同；
					*
					* @param timeout    表示需要被赋值的timeout对象
					*/
					inline csf_bool operator ==(csf_connect_timeout & timeout) {

						if (get_time() == timeout.get_time()
							&& get_timeout() == timeout.get_timeout()) {

							return csf_true;
						}

						return csf_false;
					}
					/**
					* 主要功能是：timeout对象是否相同
					* 返回：true表示相同；false表示不相同；
					*
					* @param timeout    表示需要被赋值的timeout对象
					*/
					inline csf_bool operator !=(csf_connect_timeout & timeout) {

						if (*this == timeout) {
							return csf_false;
						}
						return csf_true;
					}
					/**
					 * 表示当前超时的时间数值，单位为毫秒（ms）
					 */
					inline csf_uint64 get_time() const {

						return m_time;
					}
					/**
					 * 表示当前超时的时间数值，单位为毫秒（ms）
					 *
					 * @param newVal
					 */
					inline void set_time(csf_uint64 newVal) {

						m_time = newVal;
					}
					/**
					 * 表示超时后的回调函数
					 */
					inline csf::core::module::connect::csf_connect_callback get_handle() const {

						return m_handle;
					}
					/**
					 * 表示超时后的回调函数
					 *
					 * @param newVal
					 */
					inline void set_handle(csf::core::module::connect::csf_connect_callback newVal) {

						m_handle = newVal;
					}
					/**
					* 表示当前超时的时间数值，单位为毫秒（ms）
					*/
					inline csf_uint64 get_timeout() const {

						return m_timeout;
					}
					/**
					* 表示当前超时的时间数值，单位为毫秒（ms）
					*
					* @param newVal
					*/
					inline void set_timeout(csf_uint64 newVal) {

						m_timeout = newVal;
					}
					/**
					* 主要功能是：设置永不超期，处理过程是设置一个超长时间。
					* 返回：无
					*/
					inline void set_forever() {

						set_timeout(csf_min_uint64);
					}
					/**
					* 主要功能是：设置立即超期，处理过程是设置一个较小的时间，保证超期。
					* 返回：无
					*/
					inline void set_expired() {

						set_time(csf_dec_abs(get_time(), get_timeout()));
					}
					/**
					* 主要功能是：判断连接是否已经超时
					* 返回：true表示已经超时；false表示没有超时；
					*
					* @param time
					* 表示用于校验的当前时间基准。该时间与connect_timeout中的time进行计算，所得数值与timeout数值比较，来判断决定是否超时。
					*/
					inline csf_bool is_expired(const csf_uint64& time) const {

						if (expired_time(time) >= get_timeout()) {

							return csf_true;
						}

						return csf_false;
					}
					
				protected:
					/**
					* 主要功能是：表示用当前时间基准与connect_timeout中的time进行计算，所得数值即为返回数值。
					* 返回：超时时间差值
					*
					* @param time    表示用于校验的当前时间基准。该时间与connect_timeout中的time进行计算，所得数值即为返回数值。
					*/
					inline csf_uint64 expired_time(const csf_uint64& time) const {

						return csf_dec_abs(time, get_time());
					}
				private:
					/**
					 * 表示当前的时间数值，单位为毫秒（ms）
					 */
					csf_atomic_uint64 m_time;
					/**
					* 表示当前超时的时间数值，单位为毫秒（ms）
					*/
					csf_atomic_uint64 m_timeout;
					/**
					 * 表示超时后的回调函数
					 */
					csf::core::module::connect::csf_connect_callback m_handle = csf_nullptr;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_TIMEOUT_H_INCLUDED_)
