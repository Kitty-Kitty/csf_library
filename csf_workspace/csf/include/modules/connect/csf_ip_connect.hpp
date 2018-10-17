/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 15:10:39
*
*Description: Class(csf_ip_connect) 表示IP类型的连接类
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_CONNNECT_H_INCLUDED_)
#define CSF_IP_CONNNECT_H_INCLUDED_

#include "csf_ip_url.hpp"
#include "csf_connect.hpp"
#include "csf_ip_connect_factory.hpp"
#include "csf_ip_connect_error.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			* 表示离线定时器
			* @author f
			* @version 1.0
			* @updated 01-10月-2018 15:12:05
			*/
			typedef boost::asio::deadline_timer			csf_deadline_timer;
			/**
			 * 表示IP类型的连接类
			 * @author f
			 * @version 1.0
			 * @updated 01-10月-2018 15:12:05
			 */
			class csf_ip_connect : public csf::core::module::connect::csf_connect
			{

			public:
				/**
				* 根据csf_ip_connect_factory创建一个网络套接字
				*
				* @param factory    表示创建网络套接字的工厂类对象
				*/
				inline explicit csf_ip_connect(csf_ip_connect_factory& factory)
					: m_read_timer(factory.get_io_service())
					, m_write_timer(factory.get_io_service())
					, m_read_timeout(0)
					, m_write_timeout(0) {

				}
				virtual ~csf_ip_connect();

				/**
				 * 表示读超时时间，单位为毫秒。
				 */
				inline csf_uint32 get_read_timeout() {

					return m_read_timeout;
				}
				/**
				 * 表示读超时时间，单位为毫秒。
				 *
				 * @param newVal
				 */
				inline csf_void set_read_timeout(csf_uint32 newVal) {

					m_read_timeout = newVal;
				}
				/**
				 * 表示写超时时间，单位为毫秒。
				 */
				inline csf_uint32 get_write_timeout() {

					return m_write_timeout;
				}
				/**
				 * 表示写超时时间，单位为毫秒。
				 *
				 * @param newVal
				 */
				inline csf_void set_write_timeout(csf_uint32 newVal) {

					m_write_timeout = newVal;
				}
				/**
				 * 表示写超时时间，单位为毫秒。
				 *
				 * @param timeout_ms    表示超时数值，单位：毫秒(ms)
				 * @param callback    表示超时回调函数
				 */
				inline csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr) {

					m_write_timeout = timeout_ms;

					return 0;
				}
				/**
				 * 表示写超时时间，单位为毫秒。
				 *
				 * @param timeout_ms    表示超时数值，单位：毫秒(ms)
				 * @param callback    表示超时回调函数
				 */
				inline csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr) {

					m_read_timeout = timeout_ms;

					return 0;
				}
				virtual csf_url& get_remote_url();
				/**
				*
				* @param new_value
				*/
				virtual csf_int32 set_remote_url(csf_url& new_value);
				/**
				* 表示远程的主机地址
				*
				* @param newVal    表示url字符串内容
				*/
				inline virtual csf_int32 set_remote_url(csf_string newVal) {

					m_remote_url = newVal;

					return csf_success;
				}
				/**
				* 表示本地的主机地址
				*/
				virtual csf_url& get_local_url();
				/**
				* 表示本地的主机地址
				*
				* @param new_value
				*/
				virtual csf_int32 set_local_url(csf_url& new_value);
				/**
				* 表示本地的主机地址
				*
				* @param newVal    表示url字符串内容
				*/
				inline virtual csf_int32 set_local_url(csf_string newVal) {

					m_local_url = newVal;

					return csf_success;
				}
				/**
				 * 表示写入指定缓存的内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param buf    表示内容的缓存地址
				 * @param len    表示内容缓存的长度
				 * @param url    表示需要发送数据的目的地址
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示写入csf_buffer内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param buffer    表示需要写入的csf_buffer内容
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示发送csf_csfstring内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param csfstr    表示csf_csfstring的内容
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示发送csf_csfstring内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param chain    表示csf_chain的内容
				 * @param url    表示需要发送数据的目的地址
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示写入csf_buffer内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param buffer    表示需要写入的csf_buffer内容
				 * @param url    表示需要发送数据的目的地址
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示写入指定缓存的内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param buf    表示内容的缓存地址
				 * @param len    表示内容缓存的长度
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示发送csf_csfstring内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param csfstr    表示csf_csfstring的内容
				 * @param url    表示需要发送数据的目的地址
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示发送csf_csfstring内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param chain    表示csf_chain的内容
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);
				/**
				* 表示读超时定时器。
				*/
				inline csf_deadline_timer& get_read_timer() {

					return m_read_timer;
				}
				/**
				* 表示写超时定时器。
				*/
				inline csf_deadline_timer& get_write_timer() {

					return m_write_timer;
				}
			protected:
				/**
				* 主要功能是：针对错误或异常的处理
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param connect_ptr    表示处理的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示异常信息内容
				*/
				inline csf_int32 async_callback(csf_connect *connect
					, const csf_connect_callback& callback
					, const csf_ip_connect_error& error_code) {

					if (csf_nullptr == connect || csf_nullptr == callback) {
						return csf_failure;
					}
					else {
						return callback(connect, error_code);
					}
					return 0;
				}
				/**
				* 主要功能是：针对错误或异常的处理
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param connect_ptr    表示处理的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示异常信息内容
				*/
				inline csf_int32 exception_callback(csf_connect *connect
					, const csf_connect_callback& callback
					, csf_ip_connect_error& error_code) {

					return async_callback(connect, callback, error_code);
				}

				/**
				*
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示boost的错误信息
				* @param len    表示数据长度信息
				*/
				csf_bool csf_ip_connect::async_write_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len);
				/**
				*
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示boost的错误信息
				* @param len    表示数据长度信息
				*/
				csf_bool csf_ip_connect::async_read_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len);
			private:
				/**
				* 表示远程网络地址
				*/
				csf::modules::connect::csf_ip_url m_remote_url;
				/**
				* 表示本地网络地址
				*/
				csf::modules::connect::csf_ip_url m_local_url;
				/**
				 * 表示读超时定时器。
				 */
				csf_deadline_timer m_read_timer;
				/**
				 * 表示写超时定时器。
				 */
				csf_deadline_timer m_write_timer;
				/**
				 * 表示读超时时间，单位为毫秒。
				 */
				csf_uint32 m_read_timeout = 0;
				/**
				 * 表示写超时时间，单位为毫秒。
				 */
				csf_uint32 m_write_timeout = 0;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_H_INCLUDED_)
