/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_buffer.hpp
*
*Version: 1.0
*
*Date: 20-10月-2018 21:30:24
*
*Description: Class(csf_connect_buffer) 为方便实现各种网络操作而定义的该结构，主要为网络连接发送接收而使用buffer信息。
该数据结构主要是对unsigned char*、csf_buffer、csf_csfstring、csf_chain等原来类型，针对网络发送需求的特殊封闭。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_BUFFER_H_INCLUDED_)
#define CSF_CONNECT_BUFFER_H_INCLUDED_

#include "csf_typedef.h"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 为方便实现各种网络操作而定义的该结构，主要为网络连接发送接收而使用buffer信息。
				 * 该数据结构主要是对unsigned char*、csf_buffer、csf_csfstring、csf_chain等原来类型，针对网络发送需求的特殊封闭。
				 * @author f
				 * @version 1.0
				 * @created 20-10月-2018 21:30:24
				 */
				template<typename ValueType = csf_buffer>
				class csf_connect_buffer
				{

				public:
					inline explicit csf_connect_buffer()
						: m_container(csf_nullptr)
						, m_length(0)
						, m_is_sync(csf_false)
						, m_is_free(csf_false)
						, m_is_filled(csf_false) {

					}
					/**
					* 主要功能是：根据对应长度创建csf_connect_buffer
					* 返回：无
					*
					* @param len    表示需要发送的缓存长度
					*/
					inline explicit csf_connect_buffer(const csf_uint32 len)
						: csf_connect_buffer(new ValueType(len), len) {
						m_is_free(csf_true);

					}
					/**
					* 主要功能是：根据buufer对象和对应长度创建csf_connect_buffer
					* 返回：无
					*
					* @param buffer    表示csf_connect_buffer的宿主对象地址
					* @param len    表示需要发送的缓存长度
					*/
					inline explicit csf_connect_buffer(ValueType* buffer, const csf_uint32 len)
						: m_container(buffer)
						, m_length(len)
						, m_is_sync(csf_false)
						, m_is_free(csf_false)
						, m_is_filled(csf_false) {

					}

					virtual ~csf_connect_buffer() {

						destroy();
					}
					/**
					* 表示csf_connect_buffer所包含的实际需要被操作的宿主容器对象，例如:csf_buffer、csf_csfstring对象等
					*
					* @param newVal
					*/
					inline void set_container(ValueType* newVal) {

						if (csf_nullptr != newVal) {
							set_container(newVal, newVal->length());
						}
					}
					/**
					* 表示csf_connect_buffer所包含的实际需要被操作的宿主容器对象，例如:csf_buffer、csf_csfstring对象等
					*
					* @param newVal    表示csf_connect_buffer的宿主对象地址
					* @param len    表示需要发送的缓存长度
					*/
					inline void set_container(ValueType* newVal, const csf_uint32 len) {

						m_container = newVal;
						set_is_free(csf_false);
						set_length(len);
					}
					/**
					* 表示csf_connect_buffer所包含的实际需要被操作的宿主容器对象，例如:csf_buffer、csf_csfstring对象等
					*/
					inline ValueType* get_container() {

						return m_container;
					}
					/**
					* 表示当前的缓存数据内容
					*/
					inline csf_uchar* get_buffer() {

						if (csf_nullptr != get_container()) {
							return get_container()->get_buffer();
						}
						return csf_nullptr;
					}
					/**
					 * 表示是否采用同步的方式发送，false表示异步；true表示同步；默认为异步方式
					 *
					 * @param newVal    表示是否采用同步的方式发送，false表示异步；true表示同步；
					 */
					inline void set_is_sync(const csf_bool newVal) {

						m_is_sync = newVal;
					}
					/**
					 * 表示是否采用同步的方式发送，false表示异步；true表示同步；默认为异步方式
					 */
					inline csf_bool get_is_sync() {

						return m_is_sync;
					}
					/**
					 * 表示发送或接收的内容长度
					 *
					 * @param newVal    表示需要发送的数据长度
					 */
					inline void set_length(const csf_uint32 newVal) {

						m_length = newVal;
					}
					/**
					* 表示发送或接收的内容长度
					*/
					inline csf_uint32 get_length() {

						return m_length;
					}
					/**
					 * 主要功能是：根据数据长度创建一个宿主对象
					 * 返回：无
					 *
					 * @param len    表示需要发送的缓存长度
					 */
					inline csf_int32 create(const csf_uint32 len) {

						if (get_buffer()) {
							return csf_failure;
						}
						set_container(new ValueType(len));
						set_is_free(csf_true);
						set_length(len);
						return csf_succeed;
					}
					/**
					 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
					 */
					inline csf_bool get_is_free() {

						return m_is_free;
					}
					/**
					 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
					 *
					 * @param newVal
					 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
					 *
					 */
					inline void set_is_free(const csf_bool newVal) {

						m_is_free = newVal;
					}
					/**
					* 主要功能是：清空所有缓存空间数据；
					* 返回：无
					*/
					inline csf_void clear() {

						set_length(0);
						set_is_sync(csf_false);
						set_is_free(csf_false);
						set_is_filled(csf_false);
						if (csf_nullptr != get_container()) {
							return get_container()->clear();
						}
					}
					/**
					* 主要功能是：根据对象是否为空，长度是否为空，判断当前的csf_connect_buffer是否合法；
					* 返回：对象不为空，长度不为0则返回true；其他情况返回false
					*/
					inline csf_bool is_valid() {

						if (csf_nullptr == get_buffer()
							|| length() <= 0) {

							return csf_false;
						}
						return csf_true;
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
					* @param newVal
					*/
					inline void set_is_filled(csf_bool newVal) {

						m_is_filled = newVal;
					}
					/**
					* 表示获取buffer总缓存长度
					*/
					inline csf_uint32 size() {

						if (csf_nullptr != get_container()) {
							return get_container()->size();
						}
						return 0;
					}
					/**
					* 表示获取buffer未使用的空间长度
					*/
					inline csf_uint32 avail() {

						if (csf_nullptr != get_container()) {
							return get_container()->avail();
						}
						return 0;
					}

					/**
					* 表示当前实际已经使用的缓存的长度
					*/
					inline csf_uint32 length() {

						if (csf_nullptr != get_container()) {
							return get_container()->length();
						}
						return 0;
					}
					/**
					* 将内存数据添加到buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
					*
					* @param buf    表示数据内存的起始地址
					* @param len    表示内存数据的长度
					*/
					inline csf_int32 cat(const csf_uchar* buf, const csf_uint32 len) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(buf, len);
						}
						return 0;
					}
					/**
					* 表示buffer是否为空，为空返回true,否则返回false。长度为0或null都为空，返回true。
					*/
					inline csf_bool empty() {

						if (csf_nullptr != get_container()) {
							return get_container()->empty();
						}
						return csf_true;
					}
					/**
					* 表示将csf_string插入到csf_buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
					*
					* @param str    表示标准字符内容
					*/
					inline csf_int32 cat(const csf_string& str) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(str);
						}
						return 0;
					}
					/**
					* 表示将一个char*字符串插入到buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
					*
					* @param buf    表示插入char*内容
					*/
					inline csf_int32 cat(const csf_char* buf) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(buf);
						}
						return 0;
					}
					/**
					* 表示将csf_buffer插入到csf_buffer中。 返回：>=0表示实际添加的字符数量；<0表示错误码；
					*
					* @param buffer    表示需要添加的buffer内容
					*/
					inline csf_int32 cat(csf_buffer& buffer) {

						if (csf_nullptr != get_container()) {
							return get_container()->cat(buffer);
						}
						return 0;
					}
//				protected:
					/**
					* 表示释放buffer中的start指定的内存，并将buffer清空为null
					*/
					inline csf_void destroy() {

						if (get_is_free() && get_container()) {
							delete get_container();
							set_is_free(csf_false);
							set_container(csf_nullptr);
						}
					}
				private:
					/**
					* 表示实际用于接收和发送的缓存长度
					*
					* @param newVal
					*/
					inline void set_size(csf_uint32 newVal) {

						m_size = newVal;
					}
					/**
					* 表示实际用于接收和发送的缓存长度
					*/
					inline csf_uint32 get_size() {

						return m_size;
					}
				private:
					/**
					 * 表示是否采用同步的方式发送，false表示异步；true表示同步；默认为异步方式
					 */
					csf_bool m_is_sync = csf_false;
					/**
					* 表示csf_connect_buffer所包含的实际需要被操作的宿主容器对象，例如:csf_buffer、csf_csfstring对象等
					*/
					ValueType* m_container;
					/**
					* 表示发送或接收的内容长度
					*/
					csf_uint32 m_length = 0;
					/**
					* 表示实际用于接收和发送的缓存长度
					*/
					csf_uint32 m_size = 0;
					/**
					 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
					 */
					csf_bool m_is_free = csf_false;
					/**
					* 表示填满标志位，设备该标识位来强制接收数据时是否填充满后返回。当sync=true表示接收数据时，需要收取足够多的数据后才返回。这是一种收发性能的优化处理机制，
					* 可以提高部分网络应用的性能。
					*/
					csf_bool m_is_filled = csf_false;
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_BUFFER_H_INCLUDED_)
