/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_udp_connect.hpp
*
*Version: 1.0
*
*Date: 25-2月-2019 19:09:09
*
*Description: Class(csf_udp_connect) 表示udp连接
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_UDP_CONNECT_H_INCLUDED_)
#define CSF_UDP_CONNECT_H_INCLUDED_

#include "csf_ip_connect_factory.hpp"

#include "csf_dgram_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/************************************************************************/
			/* 表示udp包的有效生命跳数，数值默认为：64						*/
			/************************************************************************/
			#define csf_udp_connect_default_tll							64

			/**
			 * 表示udp连接
			 * @author f
			 * @version 1.0
			 * @updated 09-3月-2019 13:23:44
			 */
			class csf_udp_connect : public csf::modules::connect::csf_dgram_connect
			{

			public:
				virtual ~csf_udp_connect();

				/**
				 * 根据csf_ip_connect_factory创建一个网络套接字
				 *
				 * @param factory    表示创建网络套接字的工厂类对象
				 */
				inline explicit csf_udp_connect(csf_ip_connect_factory& factory)
					: csf_udp_connect(factory, csf_connect::csf_connect_type_udp) {

				}
				/**
				* 根据csf_ip_connect_factory创建一个网络套接字
				*
				* @param factory    表示创建网络套接字的工厂类对象
				* @param type    表示当前的具体连接类型
				*/
				inline explicit csf_udp_connect(csf_ip_connect_factory& factory
					, const csf_connect_type type)
					: csf_dgram_connect(factory, type)
					, m_socket(factory.get_io_service()) {

				}
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
				 * 表示获取连接的属性项目信息。
				 * 返回：0表示成功；非0表示失败。
				 */
				virtual csf_int32 get_option();
				/**
				 * 主要功能是：需要连接一个地址。
				 * 返回：0表示成功；非0表示失败；
				 *
				 * @param url    表示读取数据存在的指定缓存长度
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 connect(const csf_url& url, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：打开一个监听地址。
				* 返回：0表示成功；非0表示失败；
				*
				* @param url    表示需要监听的地址
				* @param callback    表示读取数据存在的指定缓存长度
				*/
				virtual csf_int32 listen(const csf_url& url, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示需要发送的内容缓存
				* @param url    表示需要发送数据的目的地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer
					, csf_url& url
					, const csf_connect_callback& callback = csf_nullptr);
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
				/**
				* 功能：
				*    表示连接是否已经打开，打开返回true，不打开返回false。
				* 返回：
				*    true ：表示打开状态；
				*    false：表示关闭状态；
				*/
				inline virtual csf_bool is_open() {

					return get_socket().is_open();
				}
			protected:
				/**
				 * 表示网络连接套接字
				 */
				inline boost::asio::ip::udp::socket& get_socket() const {

					return const_cast<boost::asio::ip::udp::socket&>(m_socket);
				}
				/**
				* 表示写入指定缓存的内容。
				* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 sync_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				* 主要功能是：同步读取数据，并放入指定缓存。
				* 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				*
				* @param buffer    表示内容的缓存地址
				* @param callback    表示需要返回的回调函数
				*/
				virtual csf_int32 sync_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				 * 表示写入指定缓存的内容。
				 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
				 *
				 * @param buffer    表示内容的缓存地址
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 async_write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				 * 主要功能是：异步读取数据，并放入指定缓存。
				 * 返回：小于等于0表示失败；大于0表示成功读入的数据长度；
				 *
				 * @param buffer    表示内容的缓存地址
				 * @param callback    表示需要返回的回调函数
				 */
				virtual csf_int32 async_read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
				/**
				 * 主要功能：
				 *    表示socket连接对象
				 * 返回：
				 *    0：表示成功；
				 *    非0：表示失败；
				 */
				virtual csf_int32 close_socket();
				/**
				* 表示远程的主机地址
				*/
				virtual const csf_url& get_remote_url() const;
				/**
				* 表示本地的主机地址
				*/
				virtual const csf_url& get_local_url() const;
			private:
				/**
				* 表示数据接收的地址
				*/
				inline boost::asio::ip::udp::endpoint& get_receive_endpoint() {

					return m_receive_endpoint;
				}
				/**
				* 表示数据接收的地址
				*
				* @param newVal
				*/
				inline void set_receive_endpoint(boost::asio::ip::udp::endpoint& newVal) {

					m_receive_endpoint = newVal;
				}
				/**
				* 表示数据发送的地址
				*/
				inline boost::asio::ip::udp::endpoint& get_send_endpoint() {

					return m_send_endpoint;
				}
				/**
				* 表示数据发送的地址
				*
				* @param newVal
				*/
				inline void set_send_endpoint(boost::asio::ip::udp::endpoint& newVal) {

					m_send_endpoint = newVal;
				}
				/**
				* 主要功能是：
				*    创建一个地址监听用的endpoint。不同的类型包括单播、组播、广播
				* 返回：
				*    一个endpoint对象
				*
				* @param url    表示当前的ip url地址信息
				*/
				boost::asio::ip::udp::endpoint csf_udp_connect::listen_endpoint(csf::modules::connect::csf_ip_url& url);
				/**
				* 主要功能是：
				*    在socket打开之后设置选项
				* 返回：
				*    true ：表示设置成功；
				*    false：表示设置失败；
				*
				* @param url    表示当前的ip url地址信息
				*/
				csf_bool set_option_after_open(csf::modules::connect::csf_ip_url& url);
				/**
				* 主要功能是：
				*    在socket绑定之后设置选项
				* 返回：
				*    true ：表示设置成功；
				*    false：表示设置失败；
				*
				* @param url    表示当前的ip url地址信息
				*/
				csf_bool set_option_after_bind(csf::modules::connect::csf_ip_url& url);
			private:
				/**
				 * 表示网络连接套接字
				 */
				boost::asio::ip::udp::socket m_socket;
				/**
				* 表示数据发送的地址
				*/
				boost::asio::ip::udp::endpoint m_send_endpoint;
				/**
				* 表示数据接收的地址
				*/
				boost::asio::ip::udp::endpoint m_receive_endpoint;

			};

		}

	}

}
#endif // !defined(CSF_UDP_CONNECT_H_INCLUDED_)
