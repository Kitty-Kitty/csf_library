/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_interface.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Interface(csf_connect_interface)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_INTERFACE_INCLUDED_)
#define CSF_CONNECT_INTERFACE_INCLUDED_

#include "csf_connect_callback.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示网络通信库操作接口内容
				 * @author fangzhenmu@aliyun.com
				 * @version 1.0
				 * @created 27-6月-2018 17:28:38
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
					csf::core::module::device::csf_connect_callback m_read_callback = csf_null;
					/**
					 * 表示异步写回调函数
					 */
					csf::core::module::device::csf_connect_callback m_write_callback = csf_null;
					/**
					 * 表示异步读超时回调函数
					 */
					csf::core::module::device::csf_connect_callback m_read_timeout_callback = csf_null;
					/**
					 * 表示异步写超时回调函数
					 */
					csf::core::module::device::csf_connect_callback m_write_timeout_callback = csf_null;

					/**
					 * 表示打开连接信息
					 * 
					 * @param url    表示连接地址
					 */
					virtual void open(const csf_url& url) =0;
					/**
					 * 表示关闭连接
					 */
					virtual csf::core::base::csf_uint32 close() =0;
					/**
					 * 表示读取数据并存在指定缓存链表中
					 * 
					 * @param chain    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示写入指定缓存的内容
					 * 
					 * @param buf    表示内容的缓存地址
					 * @param len    表示内容缓存的长度
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					virtual void set_option() =0;
					virtual void get_option() =0;
					/**
					 * 表示写入csf_buffer内容
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param chain    表示csf_chain的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示写入csf_buffer内容
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示写入指定缓存的内容
					 * 
					 * @param buf    表示内容的缓存地址
					 * @param len    表示内容缓存的长度
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buf    表示读取数据存在的指定缓存地址
					 * 
					 * @param len    表示读取数据存在的指定缓存长度
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_buffer& buffer, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buf    表示读取数据存在的指定缓存地址
					 * 
					 * @param len    表示读取数据存在的指定缓存长度
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示设置读超时时间
					 * 
					 * @param timeout_ms
					 * @param callback    表示超时回调函数。
					 */
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) =0;
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示设置写超时时间
					 * 
					 * @param timeout_ms
					 * @param callback    表示超时回调函数。
					 */
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback callback) =0;
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param chain    表示csf_chain的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(const csf_chain& chain, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_csfstring& csfstr, const csf_url& url, const csf_connect_callback callback = csf_null) =0;
					/**
					 * 表示读取数据并存在指定缓存链表中
					 * 
					 * @param chain    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(const csf_chain& chain, const csf_connect_callback callback = csf_null) =0;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INTERFACE_INCLUDED_)
