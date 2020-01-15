/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_stream_connect.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:49
*
*Description: Class(csf_stream_connect)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_STREAM_CONNECT_INCLUDED_)
#define CSF_STREAM_CONNECT_INCLUDED_

#include "csf_configure_manager.hpp"
#include "csf_url.hpp"
#include "csf_connect.hpp"
#include "csf_stream_connect_interface.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示流连接方式
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:49
				 */
				class csf_stream_connect : public csf::core::module::device::csf_connect, public csf::core::module::device::csf_stream_connect_interface
				{

				public:
					csf_stream_connect();
					virtual ~csf_stream_connect();

					inline csf::core::system::csf_configure_manager get_configure_manager() {

						return m_configure_manager;
					}
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
					 * 表示打开连接信息
					 * 
					 * @param url    表示连接地址
					 */
					virtual void open(csf::core::module::device::csf_url url);
					/**
					 * 表示关闭连接
					 */
					virtual csf::core::base::csf_uint32 close();
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
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * 模块停止
					 * 
					 * @param conf_mg    表示配置文件信息
					 */
					virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
					/**
					 * 表示连接的类型
					 */
					csf::core::module::device::csf_connect_type get_type();
					/**
					 * 表示写入指定缓存的内容
					 * 
					 * @param buffer    表示内容的缓存地址
					 * @param length    表示内容缓存的长度
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(csf_uchar* buffer, csf_uint32 length, csf_url& url, csf_connect_callback callback = csf_null);
					virtual void get_address();
					/**
					 * 表示连接的类型
					 * 
					 * @param newVal
					 */
					csf_int32 set_type(csf::core::module::device::csf_connect_type newVal);
					csf_url& get_remote_url();
					virtual void set_address();
					virtual void set_option();
					/**
					 * 
					 * @param newVal
					 */
					csf_int32 set_remote_url(csf_url& newVal);
					/**
					 * 表示本地的主机地址
					 */
					csf_url& get_local_url();
					virtual void get_option();
					/**
					 * 表示本地的主机地址
					 * 
					 * @param newVal
					 */
					csf_int32 set_local_url(csf_url& newVal);
					/**
					 * 表示写入csf_buffer内容
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(csf_buffer& buffer, csf_connect_callback callback = csf_null);
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(csf_csfstring& csfstr, csf_connect_callback callback = csf_null);
					/**
					 * 表示发送csf_csfstring内容
					 * 
					 * @param csfstr    表示csf_csfstring的内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(csf_csfstring& csfstr, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * 表示写入csf_buffer内容
					 * 
					 * @param buffer    表示需要写入的csf_buffer内容
					 * @param url    表示需要发送数据的目的地址
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(csf_buffer& buffer, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * 表示写入指定缓存的内容
					 * 
					 * @param buffer    表示内容的缓存地址
					 * @param length    表示内容缓存的长度
					 * @param callback    表示需要返回的回调函数
					 */
					virtual csf_int32 write(csf_uchar* buffer, csf_uint32 length, csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的指定缓存地址
					 * 
					 * @param length    表示读取数据存在的指定缓存长度
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(csf_uchar* buffer, csf_int32 length, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param url    表示发送数据的远端地址
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(csf_buffer& buffer, csf_url& url, csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的csf_buffer
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(csf_buffer& buffer, csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param buffer    表示读取数据存在的指定缓存地址
					 * 
					 * @param length    表示读取数据存在的指定缓存长度
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(csf_uchar* buffer, csf_int32 length, csf_connect_callback callback = csf_null);
					/**
					 * 表示读取数据并存在指定缓存位置
					 * 
					 * @param csfstr    表示读取数据存在的csf_csfstring
					 * @param callback    表示读取的回调函数
					 */
					virtual csf_int32 read(csf_csfstring& csfstr, csf_connect_callback callback = csf_null);

				};

			}

		}

	}

}
#endif // !defined(CSF_STREAM_CONNECT_INCLUDED_)
