/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:36
*
*Description: Class(csf_connect)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_INCLUDED_)
#define CSF_CONNECT_INCLUDED_

#include "csf_url.hpp"
#include "csf_configure_manager.hpp"
#include "csf_connect_interface.hpp"
#include "csf_connect_factory.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示通信库内容
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6月-2018 17:28:36
				 */
				class csf_connect : public csf::core::module::device::csf_connect_interface
				{

				public:
					csf_connect();
					virtual ~csf_connect();

					/**
					 * 表示通过factory创建一个connect
					 * 
					 * @param factory    表示需要创建connect的工厂类
					 */
					csf_void csf_connect(csf_connect_factory* factory);
					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
					/**
					 * 模块初始化
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 
					 * @param newVal
					 */
					inline csf_void set_configure_manager(csf::core::system::csf_configure_manager newVal) {

						m_configure_manager = newVal;
					}
					/**
					 * 模块启动
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示连接的类型
					 */
					inline csf::core::module::device::csf_connect_type get_type() {

						return m_type;
					}
					/**
					 * 表示连接的类型
					 * 
					 * @param newVal
					 */
					inline csf_int32 set_type(csf::core::module::device::csf_connect_type newVal) {

						m_type = newVal;
					}
					csf_url& get_remote_url();
					/**
					 * 
					 * @param newVal
					 */
					csf_int32 set_remote_url(csf_url& newVal);
					/**
					 * 表示本地的主机地址
					 */
					csf_url& get_local_url();
					/**
					 * 表示本地的主机地址
					 * 
					 * @param newVal
					 */
					csf_int32 set_local_url(csf_url& newVal);
					/**
					 * 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					 */
					inline csf_bool get_sync() {

						return m_sync;
					}
					/**
					 * 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					 * 
					 * @param newVal
					 */
					inline void set_sync(csf_bool newVal) {

						m_sync = newVal;
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
					 * @param newVal
					 */
					inline void set_status(csf_uint32 newVal) {

						m_status = newVal;
					}
					/**
					 * 表示创建connect的工厂类地址
					 */
					csf_connect_factory* get_factory();
					/**
					 * 表示创建connect的工厂类地址
					 * 
					 * @param newVal
					 */
					void set_factory(csf_connect_factory* newVal);
					csf_uint32 get_read_timeout();
					/**
					 * 
					 * @param newVal
					 */
					void set_read_timeout(csf_uint32 newVal);
					/**
					 * 表示写超时时间，单位为毫秒。
					 */
					csf_uint32 get_write_timeout();
					/**
					 * 表示写超时时间，单位为毫秒。
					 * 
					 * @param newVal
					 */
					void set_write_timeout(csf_uint32 newVal);
					/**
					 * 表示打开连接信息
					 * 
					 * @param url    表示连接地址
					 */
					virtual void open(const csf_url& url);
					/**
					 * 表示关闭连接
					 */
					virtual csf::core::base::csf_uint32 close();
					/**
					 * 表示读取数据并存在指定缓存链表中
					 * 
					 * @param chain    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示写入指定缓存的内容
					 * 
					 * @param buf    表示内容的缓存地址
					 * @param len    表示内容缓存的长度
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null);
					virtual void set_option();
					virtual void get_option();
					/**
					 * 表示写入csf_buffer内容
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_null);
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null);
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param chain    表示csf_chain的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示写入csf_buffer内容
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示写入指定缓存的内容
					 * 
					 * @param buf    表示内容的缓存地址
					 * @param len    表示内容缓存的长度
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buf    表示读取数据存在的指定缓存地址
					 * 
					 * @param len    表示读取数据存在的指定缓存长度
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buf    表示读取数据存在的指定缓存地址
					 * 
					 * @param len    表示读取数据存在的指定缓存长度
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null);
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示设置读超时时间
					 * 
					 * @param timeout_ms
					 * @param callback    表示超时回调函数。
					 */
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback);
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param chain    表示csf_chain的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_null);
					/**
					 * 表示设置写超时时间
					 * 
					 * @param timeout_ms
					 * @param callback    表示超时回调函数。
					 */
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存链表中
					 * 
					 * @param chain    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null);

				private:
					/**
					 * 表示连接的类型
					 */
					csf::core::module::device::csf_connect_type m_type = csf_connect_type_none;
					/**
					 * 表示远端的主机地址
					 */
					csf::core::module::device::csf_url m_remote_url;
					/**
					 * 表示本地的主机地址
					 */
					csf::core::module::device::csf_url m_local_url;
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
					csf_connect_factory* m_factory = csf_null;
					/**
					 * 表示读超时时间，单位为毫秒。
					 */
					csf_uint32 m_read_timeout = 0;
					/**
					 * 表示写超时时间，单位为毫秒。
					 */
					csf_uint32 m_write_timeout = 0;
					/**
					 * 表示读超时定时器。
					 */
					csf_deadline_timer m_read_timer;
					/**
					 * 表示写超时定时器。
					 */
					csf_deadline_timer m_write_timer;
					/**
					 * 表示连接的工厂对象
					 */
					csf::core::module::device::csf_connect_factory *m_connect_factory;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INCLUDED_)
