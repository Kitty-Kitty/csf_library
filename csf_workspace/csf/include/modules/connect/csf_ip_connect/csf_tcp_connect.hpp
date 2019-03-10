/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_tcp_connect.hpp
*
*Version: 1.0
*
*Date: 02-10月-2018 14:18:00
*
*Description: Class(csf_tcp_connect) 表示tcp连接
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_TCP_CONNECT_H_INCLUDED_)
#define CSF_TCP_CONNECT_H_INCLUDED_

#include "csf_ip_url.hpp"
#include "csf_stream_connect.hpp"
#include "csf_ip_connect_factory.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{

			/**
			 * 表示tcp连接
			 * @author f
			 * @version 1.0
			 * @created 02-10月-2018 14:18:00
			 */
			class csf_tcp_connect : public csf::modules::connect::csf_stream_connect
			{
			public:
				/**
				* 表示定义一个tcp网络连接智能指针
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_tcp_connect>				csf_tcp_connect_ptr;

			public:
				/**
				* 根据csf_ip_connect_factory创建一个网络套接字
				*
				* @param factory    表示创建网络套接字的工厂类对象
				*/
				inline explicit csf_tcp_connect(csf_ip_connect_factory& factory)
					: csf_stream_connect(factory, csf_connect::csf_connect_type_tcp)
					, m_socket(factory.get_io_service()) {

				}
				/**
				* 根据csf_ip_connect_factory创建一个网络套接字
				*
				* @param factory    表示创建网络套接字的工厂类对象
				*/
				inline explicit csf_tcp_connect(csf_ip_connect_factory* factory)
					: csf_stream_connect(*factory, csf_connect::csf_connect_type_tcp)
					, m_socket(factory->get_io_service()) {

				}
				/**
				* 根据csf_tco_connect创建一个网络套接字
				*
				* @param connect    表示创建已有的网络套接字对象
				*/
				inline explicit csf_tcp_connect(csf_tcp_connect* connect)
					: csf_stream_connect(*((csf_ip_connect_factory*)(connect->get_factory())), csf_connect::csf_connect_type_tcp)
					, m_socket(((csf_ip_connect_factory*)(connect->get_factory()))->get_io_service()) {
				}
				virtual ~csf_tcp_connect();
				/**
				* 模块初始化
				*
				* @param conf_mg    表示配置文件信息
				*/
				virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
				/**
				* 表示打开连接信息.
				* 返回：0表示成功；非0表示失败；
				*
				* @param url    表示连接地址
				*/
				virtual csf_int32 open(const csf_url& url);
				/**
				* 表示关闭连接.
				* 返回：0表示成功；非0表示失败；
				*/
				virtual csf_int32 close();
				/**
				* 模块启动
				*
				* @param conf_mg    表示配置文件信息
				*/
				virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
				/**
				* 表示设置连接的属性项目信息。
				* 返回：0表示成功；非0表示失败。
				*/
				virtual csf_int32 set_option();
				/**
				* 模块停止
				*
				* @param conf_mg    表示配置文件信息
				*/
				virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
				/**
				* 主要功能是：打开一个监听地址。
				* 返回：0表示成功；非0表示失败；
				*
				* @param url    表示需要监听的地址
				* @param callback    表示读取数据存在的指定缓存长度
				*/
				virtual csf_int32 listen(const csf_url& url, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：需要连接一个地址。
				* 返回：0表示成功；非0表示失败；
				*
				* @param url    表示读取数据存在的指定缓存长度
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 connect(const csf_url& url, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buf    表示内容的缓存地址
				* @param len    表示内容缓存的长度
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：写入csf_buffer内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要写入的csf_buffer内容
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_buffer& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：发送csf_csfstring内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param csfstr    表示csf_csfstring的内容
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_csfstring& csfstr, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：发送csf_csfstring内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param chain    表示csf_chain的内容
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_chain& chain, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要发送的内容缓存
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：写入csf_buffer内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要发送的内容缓存
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：发送csf_csfstring内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要发送的内容缓存
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：发送csf_csfstring内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要发送的内容缓存
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buf    表示读取数据存在的指定缓存地址
				*
				* @param len    表示读取数据存在的指定缓存长度
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buffer    表示读取数据存在的csf_buffer
				* @param len    表示读取数据存在的指定缓存长度
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param csfstr    表示读取数据存在的csf_csfstring
				* @param len    表示读取数据存在的指定缓存长度
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存链表中。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param chain    表示读取数据存在的csf_csfstring
				* @param len    表示读取数据存在的指定缓存长度
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buffer    表示读取数据存放的缓存对象
				*
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buffer    表示读取数据存在的缓存对象
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存位置。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buffer    表示读取数据存在的缓存对象
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：读取数据并存在指定缓存链表中。
				* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
				*
				* @param buffer    表示读取数据存在的缓存对象
				* @param callback    表示读取的回调函数
				*/
				//virtual csf_int32 read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：将连接信息格式化成字符串输出
				* 返回：连接信息字符串
				*/
				inline virtual csf_string to_string() {

					if (get_format().empty()) {
						set_format(
							"%s url[ local:%s -- remote:%s ]"
							, csf::core::module::connect::csf_connect::to_string().c_str()
							, get_local_url().get_url().c_str()
							, get_remote_url().get_url().c_str());
					}

					return get_format().to_string();
				}
				/**
				* 主要功能是：清空格式化字符串缓存空间
				* 返回：无
				*/
				inline virtual void flush_string() {

					get_format().memzero();
				}
			protected:
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buf    表示内容的缓存地址
				* @param len    表示内容缓存的长度
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 sync_write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buf    表示内容的缓存地址
				* @param len    表示内容缓存的长度
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 async_write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：同步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buf    表示内容的缓存地址
				* @param len    表示内容缓存的长度
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 sync_read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：异步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buf    表示内容的缓存地址
				* @param len    表示内容缓存的长度
				* @param callback    表示需要返回的回调函数
				*/
				//virtual csf_int32 async_read(csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 sync_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 async_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：同步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 sync_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：异步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 async_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 表示远程的主机地址
				*/
				virtual const csf_url& get_remote_url() const;
				/**
				* 表示本地的主机地址
				*/
				virtual const csf_url& get_local_url() const;
				/**
				* 表示网络连接套接字
				*/
				inline boost::asio::ip::tcp::socket& get_socket() const {

					return const_cast<boost::asio::ip::tcp::socket&>(m_socket);
				}
				/**
				* 表示当前的tcp监听确认对象
				*/
				inline boost::asio::ip::tcp::acceptor* get_acceptor() const {

					return m_acceptor;
				}
				/**
				* 表示当前的tcp监听确认对象
				*
				* @param newVal
				*/
				inline csf_void set_acceptor(boost::asio::ip::tcp::acceptor* newVal) {

					m_acceptor = newVal;
				}
				/**
				* 主要功能是：异步tcp监听的accept处理函数。
				* 返回：0表示成功；非0表示失败；
				*
				* @param callback    表示需要返回的回调函数
				*/
				csf::core::base::csf_int32 async_accept(const csf_connect_callback callback);
				/**
				* 主要功能是：异步tcp监听的accept回调处理函数。
				* 返回：无
				*
				* @param connect_ptr    表示当前网络通信连接对象
				* @param callback    表示需要返回的回调函数
				* @param ec    表示当前的错误信息
				*/
				csf_void accept_handle(csf_tcp_connect_ptr connect_ptr
					, const csf_connect_callback callback
					, boost::system::error_code ec);
				/**
				* 主要功能：
				*    表示socket连接对象
				* 返回：
				*    0：表示成功；
				*    非0：表示失败；
				*/
				virtual csf_int32 close_socket();
			private:
				/**
				* 主要功能是：处理异步写处理回调函数
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param buf		 表示内容的缓存地址
				* @param src_len	 表示需要被处理的源内容缓存的长度
				* @param callback    表示异常处理句柄信息
				* @param error_code  表示boost的错误信息
				* @param write_len   表示当前实际写的缓存长度
				*/
				// 				csf_bool async_write_callback(const csf_uchar* buf
				// 					, const csf_uint32 src_len
				// 					, const csf_connect_callback& callback
				// 					, const boost::system::error_code& error_code
				// 					, csf_uint32 write_len);
				/**
				* 主要功能是：处理异步读处理回调函数
				* 返回：0表示处理成功；非0表示处理失败
				*
				* @param buf		 表示内容的缓存地址
				* @param buf_len	 表示需要被处理的源内容缓存的长度
				* @param callback    表示异常处理句柄信息
				* @param error_code  表示boost的错误信息
				* @param read_len   表示当前实际写的缓存长度
				*/
				// 				csf_bool async_read_callback(csf_uchar* buf
				// 					, const csf_uint32 buf_len
				// 					, const csf_connect_callback& callback
				// 					, const boost::system::error_code& error_code
				// 					, csf_uint32 read_len);
				
			private:
				/**
				* 表示网络连接套接字
				*/
				boost::asio::ip::tcp::socket m_socket;
				/**
				* 表示当前的tcp监听确认对象
				*/
				boost::asio::ip::tcp::acceptor* m_acceptor;
				
			};
		}

	}

}
#endif // !defined(CSF_TCP_CONNECT_H_INCLUDED_)
