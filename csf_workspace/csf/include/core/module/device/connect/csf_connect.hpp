﻿/*******************************************************************************
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

#include <memory>
#include "csf_url.hpp"
#include "csf_connect_timeout.hpp"
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
					, public std::enable_shared_from_this<csf_connect>
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
						* 表示未知状态，即初始状态
						*/
						csf_connect_status_none = 0x00000000,
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
					/**
					* 根据csf_ip_connect_factory创建一个网络套接字
					*
					* @param factory    表示创建网络套接字的工厂类对象
					*/
					/**
					* 根据csf_ip_connect_factory创建一个网络套接字
					*
					* @param factory    表示创建网络套接字的工厂类对象
					*/
					inline explicit csf_connect(csf_connect_factory& factory
						, csf_connect_type type)
						: csf_connect(&factory, type) {

					}
					/**
					 * 表示通过factory创建一个connect
					 *
					 * @param factory    表示需要创建connect的工厂类
					 */
					explicit csf_connect(csf_connect_factory* factory, csf_connect_type type);
					virtual ~csf_connect();
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
					/**
					* 主要功能是：根据类型获取类型名称
					* 返回：类型名称字符串；
					*
					* @param type    表示连接类型
					*/
					inline static csf_string get_type_name(const csf_connect::csf_connect_type type) {

						csf_map<csf_connect::csf_connect_type, csf_string>::const_iterator		tmp_iter;


						tmp_iter = get_connect_type_name().find(type);
						if (tmp_iter != get_connect_type_name().end()) {
							return tmp_iter->second;
						}
						else {
							csf_string("unknow");
						}
						return "";
					}
					inline virtual const csf_url& get_remote_url() const {
						return m_remote_url;
					}
					/**
					 *
					 * @param new_value
					 */
					inline virtual csf_int32 set_remote_url(csf_url& new_value) {

						m_remote_url = new_value;

						return csf_succeed;
					}
					/**
					* 表示远程的主机地址
					*
					* @param new_value    表示url字符串内容
					*/
					inline virtual csf_int32 set_remote_url(csf_string new_value) {

						//m_remote_url = new_value;

						return csf_succeed;
					}
					/**
					 * 表示本地的主机地址
					 */
					inline virtual const csf_url& get_local_url() const {

						return m_local_url;
					}
					/**
					 * 表示本地的主机地址
					 *
					 * @param new_value
					 */
					inline virtual csf_int32 set_local_url(csf_url& new_value) {

						m_local_url = new_value;

						return csf_succeed;
					}
					/**
					* 表示本地的主机地址
					*
					* @param new_value    表示url字符串内容
					*/
					inline virtual csf_int32 set_local_url(csf_string new_value) {

						//m_local_url = new_value;

						return csf_succeed;
					}
					/**
					 * 表示网络的状态信息
					 */
					inline csf_connect_status get_status() {

						return m_status;
					}
					/**
					 * 表示网络的状态信息
					 *
					 * @param new_value
					 */
					inline csf_void set_status(csf_connect_status new_value) {

						m_status = new_value;
					}
					/**
					 * 表示创建connect的工厂类地址
					 */
					inline csf_connect_factory* get_factory() {

						return m_factory;
					}
					/**
					 * 表示创建connect的工厂类地址
					 *
					 * @param new_value
					 */
					csf_void set_factory(csf_connect_factory* new_value) {

						m_factory = new_value;
					}
					/**
					* 表示网络连接类型名称映射表
					*/
					inline static const csf_map<csf_connect::csf_connect_type, csf_string>& get_connect_type_name() {

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
					* 主要功能是：设置读超时时间.
					* 返回：0表示成功；非0表示失败；
					*
					* @param timeout_ms    表示超时的时间数值，单位：毫秒（ms）
					* @param callback    表示超时回调函数。
					*/
					virtual csf_int32 set_read_timeout(const csf_uint64 timeout_ms, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：设置写超时时间。
					* 返回：0表示成功；非0表示失败；
					*
					* @param timeout_ms    表示超时的时间数值，单位：毫秒（ms）
					* @param callback    表示超时回调函数。
					*/
					virtual csf_int32 set_write_timeout(const csf_uint64 timeout_ms, const csf_connect_callback& callback = csf_nullptr);
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
					* 主要功能是：发送连接对象的写缓存(write_buffer)内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param callback    表示需要返回的回调函数
					*/
					//inline virtual csf_int32 write(const csf_connect_callback& callback = csf_nullptr) {
					//	return write(get_write_buffer(), callback);
					//}
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
					* @param buf    表示内容的缓存地址
					* @param len    表示内容缓存的长度
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：写入csf_buffer内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要写入的csf_buffer内容
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param csfstr    表示csf_csfstring的内容
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param chain    表示csf_chain的内容
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
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
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
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
					* 主要功能是：写入指定缓存的内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：写入csf_buffer内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					//virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr);
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buf    表示读取数据存在的指定缓存地址
					*
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					//virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr);
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
					virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr);
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
					* 表示异步读超时对象
					*/
					inline virtual csf::core::module::connect::csf_connect_timeout& get_read_timeout() {

						return m_read_timeout;
					}
					/**
					* 表示异步写超时对象
					*/
					inline virtual csf::core::module::connect::csf_connect_timeout& get_write_timeout() {

						return m_write_timeout;
					}
					/**
					* 表示读取数据的缓存空间信息
					*/
					inline csf_connect_buffer<csf_buffer>& get_read_buffer() {

						return m_read_buffer;
					}
					/**
					* 表示读取数据的缓存空间信息
					*
					* @param new_value
					*/
					inline void set_read_buffer(csf_connect_buffer<csf_buffer>& new_value) {

						m_read_buffer = new_value;
					}
					/**
					* 表示写数据的缓存空间信息
					*/
					inline csf_connect_buffer<csf_buffer>& get_write_buffer() {

						return m_write_buffer;
					}
					/**
					* 表示写数据的缓存空间信息
					*
					* @param new_value
					*/
					inline void set_write_buffer(csf_connect_buffer<csf_buffer>& new_value) {

						m_write_buffer = new_value;
					}
					/**
					* 表示当前连接对象的接收回调函数
					*/
					inline csf::core::module::connect::csf_connect_callback& get_read_handle() {

						return m_read_handle;
					}
					/**
					* 表示当前连接对象的接收回调函数
					*
					* @param new_value
					*/
					inline void set_read_handle(csf::core::module::connect::csf_connect_callback new_value) {

						m_read_handle = new_value;
					}
					/**
					* 表示当前连接对象的发送回调函数
					*/
					inline csf::core::module::connect::csf_connect_callback& get_write_handle() {

						return m_write_handle;
					}
					/**
					* 表示当前连接对象的发送回调函数
					*
					* @param new_value
					*/
					inline void set_write_handle(csf::core::module::connect::csf_connect_callback new_value) {

						m_write_handle = new_value;
					}
					/**
					* 主要功能是：将连接信息格式化成字符串输出
					* 返回：连接信息字符串
					*/
					inline virtual csf_string to_string() {

						//if (csf_strlen(m_format) <= 0) {
						if ('\0' == m_format[0]) {

							csf_snprintf(m_format
								, csf_sizeof(m_format)
								, "connect[%p type:%s ]"
								, this
								, get_type_name(get_type()).c_str());
						}

						return csf_string(m_format);
					}
					/**
					* 主要功能是：刷新格式化字符串缓存空间
					* 返回：无
					*/
					inline virtual void flush_string() {

						csf_memset(m_format, 0, csf_sizeof(m_format));
					}
					/**
					* 保存该连接的当前异常信息
					*/
					inline csf::core::module::connect::csf_connect_error& get_error() {

						return m_error;
					}
					/**
					* 保存该连接的当前异常信息
					*
					* @param new_value
					*/
					inline void set_error(csf::core::module::connect::csf_connect_error new_value) {

						m_error = new_value;
					}
					/**
					* 功能：
					*    表示连接是否已经打开，打开返回true，不打开返回false。
					* 返回：
					*    true ：表示打开状态；
					*    false：表示关闭状态；
					*/
					inline virtual csf_bool is_open() {

						return csf_false;
					}
				protected:
					/**
					* 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					*/
					inline csf_bool get_is_sync() {

						return m_is_sync;
					}
					/**
					* 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					*
					* @param new_value
					*/
					inline void set_is_sync(csf_bool new_value) {

						m_is_sync = new_value;
					}
					/**
					* 表示填满标志位，设备该标识位来强制接收数据时是否填充满后返回。当sync=true表示接收数据时，需要收取足够多的数据后才返回。这是一种收发性能的优化处理机制，
					* 可以提高部分网络应用的性能。
					*/
					inline csf_bool get_is_filled() {

						return m_is_filled;
					}
					/**
					* 表示填满标志位，设备该标识位来强制接收数据时是否填充满后返回。当sync=true表示接收数据时，需要收取足够多的数据后才返回。这是一种收发性能的优化处理机制，
					* 可以提高部分网络应用的性能。
					*
					* @param new_value
					*/
					inline void set_is_filled(csf_bool new_value) {

						m_is_filled = new_value;
					}
					/**
					* 表示异步写超时对象
					*
					* @param new_value
					*/
					inline virtual void set_write_timeout(csf::core::module::connect::csf_connect_timeout& new_value) {

						m_write_timeout = new_value;
					}
					/**
					* 表示异步读超时对象
					*
					* @param new_value
					*/
					inline virtual void set_read_timeout(csf::core::module::connect::csf_connect_timeout& new_value) {

						m_read_timeout = new_value;
					}
					/**
					* 主要功能是：更新异步写超时对象
					* 返回：0表示成功；非0表示失败；
					*/
					virtual void flush_write_timeout();
					/**
					* 主要功能是：更新异步读超时对象
					* 返回：0表示成功；非0表示失败；
					*/
					virtual void flush_read_timeout();
					/**
					* 主要功能是：连接超时处理函数句柄
					* 返回：0表示成功；非0表示失败；
					*
					* @param connect_ptr    表示连接对象
					* @param connect_error    表示连接错误信息
					*/
					csf::core::base::csf_int32 timeout_handle(csf_connect_ptr connect_ptr, csf_connect_error connect_error);
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
					* 表示异步读超时对象
					*/
					csf::core::module::connect::csf_connect_timeout m_read_timeout;
					/**
					* 表示异步写超时对象
					*/
					csf::core::module::connect::csf_connect_timeout m_write_timeout;
					/**
					* 表示读取数据的缓存空间信息
					*/
					csf_connect_buffer<csf_buffer> m_read_buffer;
					/**
					* 表示写数据的缓存空间信息
					*/
					csf_connect_buffer<csf_buffer> m_write_buffer;
					/**
					* 表示当前连接对象的接收回调函数
					*/
					csf::core::module::connect::csf_connect_callback m_read_handle = csf_nullptr;
					/**
					* 表示当前连接对象的发送回调函数
					*/
					csf::core::module::connect::csf_connect_callback m_write_handle = csf_nullptr;
					/**
					* 表示同步标志位，设备该标识位来强制通信采用同步发送。当sync=true表示采用同步方式发送。
					*/
					csf_atomic_bool m_is_sync{ csf_false };
					/**
					* 表示填满标志位，设备该标识位来强制接收数据时是否填充满后返回。当sync=true表示接收数据时，需要收取足够多的数据后才返回。这是一种收发性能的优化处理机制，
					* 可以提高部分网络应用的性能。
					*/
					csf_atomic_bool m_is_filled{ csf_false };
					/**
					 * 表示网络的状态信息
					 */
					csf_connect_status m_status = csf_connect_status_none;
					/**
					 * 表示创建connect的工厂类地址
					 */
					csf_connect_factory* m_factory = csf_nullptr;
					/**
					 * 表示配置文件管理器
					 */
					csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
					/**
					* 表示连接信息的格式化字符串
					*/
					csf_char m_format[64] = { 0, };
					/**
					* 保存该连接的当前异常信息
					*/
					csf::core::module::connect::csf_connect_error m_error;
					/**
					* 表示网络连接类型名称映射表
					*/
					static const csf_map<csf_connect::csf_connect_type, csf_string> m_connect_type_name;

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
