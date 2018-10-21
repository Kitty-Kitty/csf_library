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
*Date: 21-10月-2018 12:26:50
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
#include "csf_connect_buffer.hpp"
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
				* @updated 21-10月-2018 12:28:32
				*/
				class csf_connect_interface
				{
				public:
					/**
					* 表示读取char的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, const csf_uchar*
						, const csf_uint32
						, csf_connect_error&)> 	csf_char_read_callback;
					/**
					* 表示读取csf_buffer的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_buffer& buffer
						, const csf_uint32
						, csf_connect_error&)> 	csf_buffer_read_callback;
					/**
					* 表示读取csf_csfstring的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_csfstring& csfstr
						, const csf_uint32
						, csf_connect_error&)> 	csf_csfstr_read_callback;
					/**
					* 表示读取csf_chain的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_chain& chain
						, const csf_uint32
						, csf_connect_error&)> 	csf_chain_read_callback;
					/**
					* 表示读取char的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_uchar>&
						, csf_connect_error&)> 	csf_char_buffer_read_callback;
					/**
					* 表示读取csf_buffer的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_buffer>&
						, csf_connect_error&)> 	csf_buffer_buffer_read_callback;
					/**
					* 表示读取csf_csfstring的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_csfstring>& csfstr
						, csf_connect_error&)> 	csf_csfstr_buffer_read_callback;
					/**
					* 表示读取csf_chain的回调函数
					* @author f
					* @version 1.0
					* @created 01-10月-2018 12:54:37
					*/
					typedef csf_function<csf_int32(csf_connect*
						, csf_connect_buffer<csf_chain>& chain
						, csf_connect_error&)> 	csf_chain_buffer_read_callback;
				public:
					csf_connect_interface() {

					}

					virtual ~csf_connect_interface() {

					}
					/**
					* 表示异步读超时回调函数
					*/
					csf::core::module::connect::csf_connect_callback m_read_timeout_callback = csf_nullptr;
					/**
					* 表示异步写超时回调函数
					*/
					csf::core::module::connect::csf_connect_callback m_write_timeout_callback = csf_nullptr;

					/**
					* 主要功能是：表示打开连接信息，类似bind函数
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示连接地址
					*/
					virtual csf_int32 open(const csf_url& url) = 0;
					/**
					* 主要功能是：关闭连接.
					* 返回：0表示成功；非0表示失败；
					*/
					virtual csf_int32 close() = 0;
					/**
					* 主要功能是：设置连接的属性项目信息。
					* 返回：0表示成功；非0表示失败。
					*/
					virtual csf_int32 set_option() = 0;
					/**
					* 主要功能是：获取连接的属性项目信息。
					* 返回：0表示成功；非0表示失败。
					*/
					virtual csf_int32 get_option() = 0;
					/**
					* 主要功能是：设置读超时时间.
					* 返回：0表示成功；非0表示失败；
					*
					* @param timeout_ms    表示超时的时间数值，单位：毫秒（ms）
					* @param callback    表示超时回调函数。
					*/
					virtual csf_int32 set_read_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：设置写超时时间。
					* 返回：0表示成功；非0表示失败；
					*
					* @param timeout_ms    表示超时的时间数值，单位：毫秒（ms）
					* @param callback    表示超时回调函数。
					*/
					virtual csf_int32 set_write_timeout(const csf_uint32 timeout_ms, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：打开一个监听地址。
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示需要监听的地址
					* @param callback    表示读取数据存在的指定缓存长度
					*/
					virtual csf_int32 listen(const csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：需要连接一个地址。
					* 返回：0表示成功；非0表示失败；
					*
					* @param url    表示读取数据存在的指定缓存长度
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 connect(const csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入指定缓存的内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buf    表示内容的缓存地址
					* @param len    表示内容缓存的长度
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入csf_buffer内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要写入的csf_buffer内容
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_buffer& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param csfstr    表示csf_csfstring的内容
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_csfstring& csfstr, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param chain    表示csf_chain的内容
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_chain& chain, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入指定缓存的内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buf    表示内容的缓存地址
					* @param len    表示内容缓存的长度
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入csf_buffer内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要写入的csf_buffer内容
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param csfstr    表示csf_csfstring的内容
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param chain    表示csf_chain的内容
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入指定缓存的内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入csf_buffer内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入指定缓存的内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：写入csf_buffer内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：发送csf_csfstring内容。
					* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
					*
					* @param buffer    表示需要发送的内容缓存
					* @param url    表示需要发送数据的目的地址
					* @param callback    表示需要返回的回调函数
					*/
					virtual csf_int32 write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buf    表示读取数据存在的指定缓存地址
					*
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(const csf_uchar* buf, const csf_uint32 len, const csf_char_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buffer    表示读取数据存在的csf_buffer
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_buffer& buffer, const csf_uint32 len, const csf_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param csfstr    表示读取数据存在的csf_csfstring
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_csfstring& csfstr, const csf_uint32 len, const csf_csfstr_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存链表中。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param chain    表示读取数据存在的csf_csfstring
					* @param len    表示读取数据存在的指定缓存长度
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_chain& chain, const csf_uint32 len, const csf_chain_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buffer    表示读取数据存放的缓存对象
					*
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_uchar>& buffer, const csf_char_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buffer    表示读取数据存在的缓存对象
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_buffer>& buffer, const csf_buffer_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存位置。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buffer    表示读取数据存在的缓存对象
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_csfstring>& buffer, const csf_csfstr_buffer_read_callback& callback = csf_nullptr) = 0;
					/**
					* 主要功能是：读取数据并存在指定缓存链表中。
					* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
					*
					* @param buffer    表示读取数据存在的缓存对象
					* @param callback    表示读取的回调函数
					*/
					virtual csf_int32 read(csf_connect_buffer<csf_chain>& buffer, const csf_chain_buffer_read_callback& callback = csf_nullptr) = 0;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_INTERFACE_H_INCLUDED_)
