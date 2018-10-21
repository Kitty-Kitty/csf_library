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
				/**
				 * 表示超时表述描述类型
				 * @author f
				 * @version 1.0
				 * @created 21-10月-2018 13:54:44
				 */
				class csf_connect_timeout
				{

				public:
					csf_connect_timeout();
					virtual ~csf_connect_timeout();

					/**
					 * 
					 * @param time    表示当前超时的时间数值，单位为毫秒（ms）
					 * 
					 * @param handle    表示超时后的回调函数
					 */
					csf_connect_timeout(const csf_uint32 time, const csf::core::module::connect::csf_connect_callback handle);
					/**
					 * 表示当前超时的时间数值，单位为毫秒（ms）
					 */
					inline csf_uint32 get_time() {

						return m_time;
					}
					/**
					 * 表示当前超时的时间数值，单位为毫秒（ms）
					 * 
					 * @param newVal
					 */
					inline void set_time(csf_uint32 newVal) {

						m_time = newVal;
					}
					/**
					 * 表示超时后的回调函数
					 */
					inline csf::core::module::connect::csf_connect_callback get_handle() {

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

				private:
					/**
					 * 表示当前超时的时间数值，单位为毫秒（ms）
					 */
					csf_uint32 m_time = 0;
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
