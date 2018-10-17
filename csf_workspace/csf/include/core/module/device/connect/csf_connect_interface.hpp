/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_connect_interface.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:38
*
*Description: Interface(csf_connect_interface) 表示网络通信库操作接口内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_INTERFACE_H_INCLUDED_)
#define CSF_CONNECT_INTERFACE_H_INCLUDED_

#include "csf_base_include.h"
#include "csf_connect_callback.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 表示网络通信库操作接口内容
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 01-10月-2018 12:54:38
				 */
				class csf_connect_interface
				{

				public:
					csf_connect_interface() {

					}

					virtual ~csf_connect_interface() {

					}
					/**
					 * 表示异步读回调函数
					 */
					csf::core::module::connect::csf_connect_callback m_read_callback = csf_nullptr;
					/**
					 * 表示异步写回调函数
					 */
					csf::core::module::connect::csf_connect_callback m_write_callback = csf_nullptr;
					/**
					 * 表示异步读超时回调函数
					 */
					csf::core::module::connect::csf_connect_callback m_read_timeout_callback = csf_nullptr;
					/**
					 * 表示异步写超时回调函数
					 */
					csf::core::module::connect::csf_connect_callback m_write_timeout_callback = csf_nullptr;

					/**
					 * 表示打开连接信息.
					 * 返回：0表示成功；非0表示失败；
					 * 
					 * @param url    表示连接地址
					 */
					virtual csf_int32 open(const csf_url& url) =0;
					/**
					 * 表示关闭连接.
					 * 返回：0表示成功；非0表示失败；
					 */
					virtual csf_int32 close() =0;
					/**
					 * 表示设置连接的属性项目信息。
					 * 返回：0表示成功；非0表示失败。
					 */
					virtual csf_int32 set_option() =0;
					/**
					 * 表示获取连接的属性项目信息。
					 * 返回：0表示成功；非0表示失败。
					 */
					virtual csf_int32 get_option() =0;
					/**
					 * 表示设置读超时时间.
					 * 返回：0表示成功；非0表示失败；
					 * 
					 * @param timeout_ms
					 * @param callback    表示超时回调函数。
					 */
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示设置写超时时间。
					 * 返回：0表示成功；非0表示失败；
					 * 
					 * @param timeout_ms
					 * @param callback    表示超时回调函数。
					 */
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					* 主要功能是：打开一个监听地址。
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示需要监听的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 listen(const csf_url& url, const csf_connect_callback callback = csf_nullptr) = 0;
					/**
					* 主要功能是：需要连接一个地址。
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示需要监听的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 connect(const csf_url& url, const csf_connect_callback callback = csf_nullptr) = 0;
					/**
					 * 表示写入指定缓存的内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param buf    表示内容的缓存地址
					 * @param len    表示内容缓存的长度
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示写入csf_buffer内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示发送csf_csfstring内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示发送csf_csfstring内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param chain    表示csf_chain的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示写入csf_buffer内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示写入指定缓存的内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param buf    表示内容的缓存地址
					 * @param len    表示内容缓存的长度
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示发送csf_csfstring内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					 * 表示发送csf_csfstring内容。
					 * 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					 * 
					 * @param chain    表示csf_chain的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_nullptr) =0;
					/**
					* 表示读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buf    表示读取数据存在的指定缓存地址
					*
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr) = 0;
					/**
					* 表示读取数据并存在指定缓存链表中。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param chain    表示读取数据存在的csf_csfstring
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(const csf_chain& chain, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr) = 0;
					/**
					* 表示读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buffer    表示读取数据存在的csf_buffer
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(const csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr) = 0;
					/**
					* 表示读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param csfstr    表示读取数据存在的csf_csfstring
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback callback = csf_nullptr) = 0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INTERFACE_H_INCLUDED_)
