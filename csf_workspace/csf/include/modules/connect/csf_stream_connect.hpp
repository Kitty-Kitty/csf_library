/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Version: 1.0
*
*Date: 02-10月-2018 14:17:58
*
*Description: Class(csf_stream_connect) 表示通信库，流连接信息内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_STREAM_CONNECT_H_INCLUDED_)
#define CSF_STREAM_CONNECT_H_INCLUDED_

#include "csf_ip_connect.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/**
			 * 表示通信库，流连接信息内容
			 * @author fangzhenmu@aliyun.com
			 * @version 1.0
			 * @created 02-10月-2018 14:17:58
			 */
			class csf_stream_connect : public csf::modules::connect::csf_ip_connect
			{

			public:
				csf_stream_connect();
				virtual ~csf_stream_connect();

				/**
				 * 表示通过factory创建一个connect
				 * 
				 * @param factory    表示需要创建connect的工厂类
				 */
				inline explicit csf_stream_connect(csf_ip_connect_factory& factory)
					: csf_ip_connect(factory) {

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
				 * 表示设置读超时时间.
				 * 返回：0表示成功；非0表示失败；
				 * 
				 * @param timeout_ms
				 * @param callback    表示超时回调函数。
				 */
				virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr);
				/**
				 * 表示设置写超时时间。
				 * 返回：0表示成功；非0表示失败；
				 * 
				 * @param timeout_ms
				 * @param callback    表示超时回调函数。
				 */
				virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr);
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
				virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null);

			};

		}

	}

}
#endif // !defined(CSF_STREAM_CONNECT_H_INCLUDED_)
