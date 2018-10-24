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
#include "csf_ip_connect_timeout.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace modules
	{
		namespace connect
		{
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
					: m_read_timeout(factory.get_io_service())
					, m_write_timeout(factory.get_io_service()) {

				}
				virtual ~csf_ip_connect();
				/**
				* 主要功能是：设置读超时时间.
				* 返回：0表示成功；非0表示失败；
				*
				* @param timeout_ms    表示超时的时间数值，单位：毫秒（ms）
				* @param callback    表示超时回调函数。
				*/
				inline virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* 主要功能是：设置写超时时间。
				* 返回：0表示成功；非0表示失败；
				*
				* @param timeout_ms    表示超时的时间数值，单位：毫秒（ms）
				* @param callback    表示超时回调函数。
				*/
				inline virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* 表示写超时描述对象。
				*/
				inline csf::modules::connect::csf_ip_connect_timeout& get_write_timeout() {

					return m_write_timeout;
				}
				/**
				* 表示读超时超时描述对象。
				*/
				inline csf::modules::connect::csf_ip_connect_timeout& get_read_timeout() {

					return m_read_timeout;
				}
				/**
				* 表示远程网络地址
				*
				* @param newVal    表示url字符串内容
				*/
				inline void set_remote_url(csf::modules::connect::csf_ip_url& newVal) {

					m_remote_url = newVal;
				}
				/**
				* 表示本地网络地址
				*
				* @param newVal    表示url字符串内容
				*/
				inline void set_local_url(csf::modules::connect::csf_ip_url& newVal) {

					m_local_url = newVal;
				}
				/**
				* 表示远程网络地址
				*/
				inline virtual csf_url& get_remote_url() {

					return m_remote_url;
				}
				/**
				* 表示本地网络地址
				*/
				inline virtual csf_url& get_local_url() {

					return m_local_url;
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
					, csf_ip_connect_error& error_code) {

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
				* 主要功能是：处理异步写处理回调函数
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示boost的错误信息
				* @param len    表示数据长度信息
				*/
				inline csf_bool csf_ip_connect::async_write_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len) {

					async_callback(this, callback, csf_ip_connect_error(error_code));

					return csf_true;
				}
				/**
				* 主要功能是：处理异步读处理回调函数
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示boost的错误信息
				* @param len    表示数据长度信息
				*/
				inline csf_bool csf_ip_connect::async_read_callback(const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 len) {

					async_callback(this, callback, csf_ip_connect_error(error_code));

					return csf_true;
				}
			private:
				/**
				* 表示读超时超时描述对象。
				*/
				csf::modules::connect::csf_ip_connect_timeout m_read_timeout;
				/**
				* 表示写超时描述对象。
				*/
				csf::modules::connect::csf_ip_connect_timeout m_write_timeout;
				/**
				* 表示远程网络地址
				*/
				csf::modules::connect::csf_ip_url m_remote_url;
				/**
				* 表示本地网络地址
				*/
				csf::modules::connect::csf_ip_url m_local_url;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_H_INCLUDED_)
