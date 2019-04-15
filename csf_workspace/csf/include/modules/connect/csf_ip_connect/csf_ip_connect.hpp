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
			/************************************************************************/
			/* 表示ip_connect的描述信息的缓存大小，数值默认为：128						*/
			/************************************************************************/
			#define csf_ip_connect_format_buffer_size							128
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
				inline explicit csf_ip_connect(csf_ip_connect_factory& factory, csf_connect_type type)
					: csf_connect(factory, type)
					, m_format(csf_ip_connect_format_buffer_size) {

				}
				virtual ~csf_ip_connect();
				/**
				* 表示远程的主机地址
				*
				* @param new_value    表示url字符串内容
				*/
				inline virtual csf_int32 set_remote_url(csf_string new_value) {

					return m_remote_url.parse(new_value);
					//m_remote_url = new_value;
					//return csf_succeed;
				}
				/**
				* 表示远程网络地址
				*
				* @param new_value    表示url字符串内容
				*/
				inline virtual csf_int32 set_remote_url(csf::core::module::connect::csf_url& new_value) {

					if (csf_false == csf_ip_url::is_valid_type(new_value)) {
						return csf_failure;
					}
					m_remote_url = (csf::modules::connect::csf_ip_url&)new_value;

					return csf_succeed;
				}
				/**
				* 表示本地的主机地址
				*
				* @param new_value    表示url字符串内容
				*/
				inline virtual csf_int32 set_local_url(csf_string new_value) {

					return m_local_url.parse(new_value);
					//m_local_url = new_value;
					//return csf_succeed;
				}
				/**
				* 表示本地网络地址
				*
				* @param new_value    表示url字符串内容
				*/
				inline virtual csf_int32 set_local_url(csf::core::module::connect::csf_url& new_value) {

					if (csf_false == csf_ip_url::is_valid_type(new_value)) {
						return csf_failure;
					}
					m_local_url = (csf::modules::connect::csf_ip_url&)new_value;

					return csf_succeed;
				}
				/**
				* 表示远程网络地址
				*/
				inline virtual const csf_url& get_remote_url() const {

					return m_remote_url;
				}
				/**
				* 表示本地网络地址
				*/
				inline virtual const csf_url& get_local_url() const {

					return m_local_url;
				}
				/**
				* 主要功能是：
				*    处理异步连接回调函数
				* 返回：
				*    0   ：表示成功；
				*    非0 ：表示失败
				*
				* @param connect    表示处理的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示boost的错误信息
				*/
				inline csf_int32 async_connect_callback(csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, const boost::system::error_code& error_code) {

					//更新一下本地的地址信息
					connect_ptr->get_local_url();

					//如果错误，则设置错误信息
					//正确与否都打印信息
					if (error_code) {
						set_error(csf_connect_error(error_code.value()
							, boost::system::system_error(error_code).what()));

						csf_log_ex(error, csf_log_code_error
							, "connect[url:%s] failed! %s."
							, connect_ptr->get_remote_url().get_url().c_str()
							, get_error().to_string().c_str());
					}
					else {
						csf_log_ex(notice, csf_log_code_notice
							, "connect %s succeed!"
							, connect_ptr->to_string().c_str());
					}

					return async_callback(connect_ptr
						, callback
						, csf_ip_connect_error(error_code));
				}
				/**
				* 主要功能是：写入csf_buffer内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要发送的内容缓存
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buffer    表示读取数据存在的缓存对象
				* @param callback    表示读取的回调函数
				*/
				virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
			protected:
				/**
				* 主要功能是：针对错误或异常的处理
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param connect_ptr    表示处理的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示异常信息内容
				*/
				inline csf_int32 async_callback(csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, csf_ip_connect_error error_code) {

					if (!connect_ptr
						|| csf_nullptr == callback) {

						if (error_code.get_code() > 0) {
							csf_log_ex(warning
								, csf_log_code_warning
								, "%s %s"
								, connect_ptr->to_string().c_str()
								, error_code.to_string().c_str());
						}
						return csf_failure;
					}
					else {
						return callback(connect_ptr, error_code);
					}

					return csf_succeed;
				}
				/**
				* 主要功能是：针对错误或异常的处理
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param connect_ptr    表示处理的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code    表示异常信息内容
				*/
				inline csf_int32 exception_callback(csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, csf_ip_connect_error error_code) {

					return async_callback(connect_ptr, callback, error_code);
				}
				/**
				* 主要功能是：处理异步写处理回调函数
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param buffer		 表示内容的缓存
				* @param connect_ptr 表示当前的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code  表示boost的错误信息
				* @param length		表示当前实际写的缓存长度
				*/
				csf_bool async_write_callback(csf_connect_buffer<csf_buffer>& buffer
					, csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 length);
				/**
				* 主要功能是：处理异步读处理回调函数
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param buffer		 表示内容的缓存
				* @param connect_ptr 表示当前的网络连接对象
				* @param callback    表示异常处理句柄信息
				* @param error_code  表示boost的错误信息
				* @param length   表示当前实际写的缓存长度
				*/
				csf_bool async_read_callback(csf_connect_buffer<csf_buffer>& buffer
					, csf_connect_ptr connect_ptr
					, const csf_connect_callback& callback
					, const boost::system::error_code& error_code
					, csf_uint32 length);
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 async_write(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* 主要功能是：异步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 async_read(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 sync_write(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* 主要功能是：同步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 sync_read(csf_connect_buffer<csf_buffer>& buffer
					, const csf_connect_callback& callback = csf_nullptr) {

					return 0;
				}
				/**
				* 表示连接信息的格式化字符串
				*/
				inline csf::core::base::csf_csfstring& get_format() {

					return m_format;
				}
				/**
				* 表示连接信息的格式化字符串
				*
				* @param new_value
				*/
				inline void set_format(const csf_char* fmt, ...) {

					va_list					tmp_marker;


					if (!fmt || csf_strlen(fmt) <= 0) {
						return ;
					}

					va_start(tmp_marker, fmt);

					get_format().format(fmt, tmp_marker);

					va_end(tmp_marker);

					return;
				}
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
				* 表示连接信息的格式化字符串
				*/
				csf::core::base::csf_csfstring m_format;

			};

		}

	}

}
#endif // !defined(CSF_IP_CONNNECT_H_INCLUDED_)
