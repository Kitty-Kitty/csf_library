/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:36
*
*Description: Class(csf_connect) 表示通信库，网络连接信息内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_H_INCLUDED_)
#define CSF_CONNECT_H_INCLUDED_

#include "csf_stdcplusplus.hpp"
#include "csf_url.hpp"
#include "csf_connect_interface.hpp"
#include "csf_configure_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 表示通信库，网络连接信息内容
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 01-10月-2018 12:54:36
				 */
				class csf_connect : public csf::core::module::connect::csf_connect_interface
				{

				public:
					/**
					 * 表示连接的类型
					 * @author f
					 * @version 1.0
					 * @created 01-10月-2018 12:54:36
					 */
					typedef enum csf_connect_type_enum
					{
						/**
						* 表示未知的连接类型
						*/
						csf_connect_type_none = 0x00000000,
						/**
						* 表示TCP连接类型
						*/
						csf_connect_type_tcp = 0x00000200,
						/**
						* 表示UDP连接类型
						*/
						csf_connect_type_udp = 0x00000400,
						/**
						* 表示组播连接类型
						*/
						csf_connect_type_multicast = 0x00000402,
						/**
						* 表示广播连接类型
						*/
						csf_connect_type_broadcast = 0x00000404
					} csf_connect_type;

					/**
					 * 表示当前的连接状态
					 * @author f
					 * @version 1.0
					 * @created 01-10月-2018 12:54:36
					 */
					typedef enum csf_connect_status_enum
					{
						/**
						 * 表示打开关闭标识位。标识位为1表示打开；标识位为0表示关闭；
						 */
						csf_connect_status_open = 0x00000001,
						/**
						 * 表示同步标识位。当标识位为1表示同步；标识位为0表示异步。默认为0异步方式。
						 */
						csf_connect_status_sync = 0x00000002,
						/**
						 * 表示使用读超时标识位，设置为1表示使用，0表示不使用。
						 */
						csf_connect_status_use_read_timeout = 0x00000004,
						/**
						 * 表示使用写超时标识位，设置为1表示使用，0表示不使用。
						 */
						csf_connect_status_use_write_timeout = 0x00000008,
						/**
						 * 表示读超时标识位，设置为1表示读超时，0表示正常。
						 */
						csf_connect_status_read_deadline = 0x00000010,
						/**
						 * 表示写超时标识位，设置为1表示写超时，0表示正常。
						 */
						csf_connect_status_write_deadline = 0x00000020
					} csf_connect_status;


					csf_connect();
					virtual ~csf_connect();

					/**
					 * 表示通过factory创建一个connect
					 * 
					 * @param factory    表示需要创建connect的工厂类
					 */
					inline explicit csf_connect(csf_connect_factory* factory) {

					}
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_nullptr);
					/**
					 * 表示连接的类型
					 */
					inline csf_connect::csf_connect_type get_type() {

						return m_type;
					}
					/**
					 * 表示连接的类型
					 * 
					 * @param new_value
					 */
					inline csf_int32 set_type(csf_connect::csf_connect_type new_value) {

						m_type = new_value;
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

						//m_remote_url = newVal;
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

						//m_local_url = newVal;

						return csf_success;
					}
					/**
					 * 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					 */
					inline csf_bool get_sync() {

						return m_sync;
					}
					/**
					 * 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					 * 
					 * @param new_value
					 */
					inline csf_void set_sync(csf_bool new_value) {

						m_sync = new_value;
					}
					/**
					 * 表示网络的状态信息
					 */
					inline csf_uint32 get_status() {

						return m_status;
					}
					/**
					 * 表示网络的状态信息
					 * 
					 * @param new_value
					 */
					inline csf_void set_status(csf_uint32 new_value) {

						m_status = new_value;
					}
					/**
					 * 表示创建connect的工厂类地址
					 */
					csf_connect_factory* get_factory();
					/**
					 * 表示创建connect的工厂类地址
					 * 
					 * @param new_value
					 */
					csf_void set_factory(csf_connect_factory* new_value);
					/**
					* 表示网络连接类型名称映射表
					*/
					inline static const csf_unordered_map<csf_connect::csf_connect_type, csf_string>& get_connect_type_name() {

						return m_connect_type_name;
					}
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
					 * 表示设置连接的属性项目信息。
					 * 返回：0表示成功；非0表示失败。
					 */
					virtual csf_int32 set_option();
					/**
					 * 表示获取连接的属性项目信息。
					 * 返回：0表示成功；非0表示失败。
					 */
					virtual csf_int32 get_option();
					/**
					* 主要功能是：打开一个监听地址。
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示需要监听的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 listen(const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					* 主要功能是：需要连接一个地址。
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示需要监听的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 connect(const csf_url& url, const csf_connect_callback callback = csf_nullptr);
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
					 * 表示读取数据并存在指定缓存位置。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param buf    表示读取数据存在的指定缓存地址
					 * 
					 * @param len    表示读取数据存在的指定缓存长度
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存链表中。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param chain    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存位置。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存位置。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存位置。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param buf    表示读取数据存在的指定缓存地址
					 * 
					 * @param len    表示读取数据存在的指定缓存长度
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存位置。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存位置。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr);
					/**
					 * 表示读取数据并存在指定缓存链表中。
					 * 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					 * 
					 * @param chain    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr);

				private:
					/**
					 * 表示连接的类型
					 */
					csf_connect::csf_connect_type m_type = csf_connect_type_none;
					/**
					 * 表示远端的主机地址
					 */
					csf::core::module::connect::csf_url m_remote_url;
					/**
					 * 表示本地的主机地址
					 */
					csf::core::module::connect::csf_url m_local_url;
					/**
					 * 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					 */
					csf_bool m_sync = csf_false;
					/**
					 * 表示网络的状态信息
					 */
					csf_uint32 m_status = 0;
					/**
					 * 表示创建connect的工厂类地址
					 */
					csf_connect_factory* m_factory = csf_nullptr;
					/**
					 * 表示配置文件管理器
					 */
					csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
					/**
					 * 表示连接的工厂对象
					 */
					csf::core::module::connect::csf_connect_factory *m_connect_factory = csf_nullptr;
					/**
					* 表示网络连接类型名称映射表
					*/
					static const csf_unordered_map<csf_connect::csf_connect_type, csf_string> m_connect_type_name;

				};

				/**
				* 表示一个空的网络连接智能指针
				* @author fangzhenmu@aliyun.com
				* @version 1.0
				* @created 01-10月-2018 12:54:36
				*/
				static	csf_connect_ptr							m_null_connect_ptr;
			}

		}

	}

}
#endif // !defined(CSF_CONNECT_H_INCLUDED_)
