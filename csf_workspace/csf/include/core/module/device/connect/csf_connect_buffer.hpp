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
						: m_buffer(csf_nullptr)
						, m_length(0)
						, m_is_sync(csf_false)
						, m_is_free(csf_false) {

					}
					/**
					* 主要功能是：根据对应长度创建csf_connect_buffer
					* 返回：无
					*
					* @param len    表示需要发送的缓存长度
					*/
					inline explicit csf_connect_buffer(const csf_uint32 len)
						: csf_connect_buffer(new ValueType(len), len) {

					}
					/**
					* 主要功能是：根据buufer对象和对应长度创建csf_connect_buffer
					* 返回：无
					*
					* @param buffer    表示csf_connect_buffer的宿主对象地址
					* @param len    表示需要发送的缓存长度
					*/
					inline explicit csf_connect_buffer(ValueType* buffer, const csf_uint32 len)
						: m_buffer(buffer)
						, m_length(len)
						, m_is_sync(csf_false)
						, m_is_free(csf_false) {

					}

					virtual ~csf_connect_buffer() {

					}
					/**
					* 主要功能是：根据宿主缓存对象，设置buffer内容.
					* 返回：无
					*
					* @param newVal    表示csf_connect_buffer的宿主对象地址
					* @param len    表示需要发送的缓存长度
					*/
					inline void set_buffer(ValueType* newVal, const csf_uint32 len) {

						m_buffer = newVal;
						set_is_free(csf_false);
						set_length(len);
					}
					/**
					* 表示当前的缓存数据内容
					*/
					inline ValueType* get_buffer() {

						return m_buffer;
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
					inline void create(const csf_uint32 len) {

						m_buffer = new ValueType(len);
						set_is_free(csf_true);
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

				private:
					/**
					 * 表示是否采用同步的方式发送，false表示异步；true表示同步；默认为异步方式
					 */
					csf_bool m_is_sync = csf_false;
					/**
					 * 表示当前的缓存数据内容
					 */
					ValueType* m_buffer;
					/**
					 * 表示发送或接收的内容长度
					 */
					csf_uint32 m_length = 0;
					/**
					 * 表示是否在对象销毁时，释放内存。true表示需要释放；false表示不需要释放；默认为true，当为false时注意在其他地方显示释放，避免内存泄露。
					 */
					csf_bool m_is_free = csf_false;

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_BUFFER_H_INCLUDED_)
