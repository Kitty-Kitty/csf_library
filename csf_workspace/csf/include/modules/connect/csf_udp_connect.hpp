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
*Date: 02-10月-2018 14:18:02
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

#include "csf_dgram_connect.hpp"
#include "csf_ip_connect_factory.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示udp连接
			 * @author f
			 * @version 1.0
			 * @created 02-10月-2018 14:18:02
			 */
			class csf_udp_connect : public csf::modules::connect::csf_dgram_connect
			{
			public:
				/**
				* 表示定义一个tcp网络连接智能指针
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				typedef	csf_shared_ptr<csf_udp_connect>				csf_udp_connect_ptr;

			public:
				/**
				* 根据csf_ip_connect_factory创建一个网络套接字
				*
				* @param factory    表示创建网络套接字的工厂类对象
				*/
				inline explicit csf_udp_connect(csf_ip_connect_factory& factory)
					: csf_dgram_connect(factory)
					, m_socket(factory.get_io_service()) {

				}
				virtual ~csf_udp_connect();

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
				* 表示远程的主机地址
				*/
				inline virtual csf_url& get_remote_url() {

					return csf_ip_connect::get_remote_url();
				}
				/**
				* 表示本地的主机地址
				*/
				inline virtual csf_url& get_local_url() {

					return csf_ip_connect::get_local_url();
				}
			protected:
				/**
				* 表示网络连接套接字
				*/
				inline boost::asio::ip::udp::socket& get_socket() {

					return m_socket;
				}
			private:
				/**
				* 表示网络连接套接字
				*/
				boost::asio::ip::udp::socket m_socket;
			};
		}

	}

}
#endif // !defined(CSF_UDP_CONNECT_H_INCLUDED_)
