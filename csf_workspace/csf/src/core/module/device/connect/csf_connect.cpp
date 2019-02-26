/*******************************************************************************
*
*Copyright: fangzhenmu@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: csf_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:37
*
*Description: Class(csf_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_connect.hpp"
#include "csf_connect_factory.hpp"
#include "system_time.hpp"

using namespace csf::core::module::connect;
using csf::core::module::connect::csf_connect;

/**
* 表示网络连接类型映射表
*/
const csf_map<csf_connect::csf_connect_type, csf_string> csf_connect::m_connect_type_name = {
	{ csf_connect::csf_connect_type::csf_connect_type_none, "none"},
	{ csf_connect::csf_connect_type::csf_connect_type_tcp, "tcp" },
	{ csf_connect::csf_connect_type::csf_connect_type_udp, "udp" },
	{ csf_connect::csf_connect_type::csf_connect_type_multicast, "multicast" },
	{ csf_connect::csf_connect_type::csf_connect_type_broadcast, "broadcast" }
};


csf_connect::csf_connect()
	: m_type(csf_connect_type_none)
	, m_is_sync(csf_false)
	, m_is_filled(csf_false)
	, m_status(csf_connect_status_none)
	, m_factory(csf_nullptr)
	, m_configure_manager(csf_nullptr)
	, m_format{ 0, }  {

}


/**
* 表示通过factory创建一个connect
*
* @param factory    表示需要创建connect的工厂类
*/
csf_connect::csf_connect(csf_connect_factory* factory, csf_connect_type type)
	: m_type(type)
	, m_is_sync(csf_false)
	, m_is_filled(csf_false)
	, m_status(csf_connect_status_none)
	, m_factory(factory)
	, m_configure_manager(factory->get_configure_manager())
	, m_format{ 0, } {

}


csf_connect::~csf_connect() {

	//销毁连接时，需要清空缓存内容
	get_read_buffer().clear();
	get_write_buffer().clear();
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_connect::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示打开连接信息.
 * 返回：0表示成功；非0表示失败；
 * 
 * @param url    表示连接地址
 */
csf_int32 csf_connect::open(const csf_url& url) {

	return 0;
}


/**
 * 表示关闭连接.
 * 返回：0表示成功；非0表示失败；
 */
csf_int32 csf_connect::close() {

	//设置读写超时
	get_read_timeout().set_expired();
	get_write_timeout().set_expired();

	return csf_succeed;
}


/**
 * 表示设置连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_connect::set_option() {

	return 0;
}


/**
 * 表示获取连接的属性项目信息。
 * 返回：0表示成功；非0表示失败。
 */
csf_int32 csf_connect::get_option() {

	return 0;
}


/**
* 主要功能是：设置读超时时间.
* 返回：0表示成功；非0表示失败；
*
* @param timeout_ms		表示超时的时间数值，单位：毫秒（ms）
* @param callback    表示超时回调函数。
*/
csf_int32 csf_connect::set_read_timeout(const csf_uint64 timeout_ms, const csf_connect_callback& callback) {

	get_read_timeout().set_time(csf::core::utils::time::system_time::get_time());
	get_read_timeout().set_timeout(timeout_ms);
	if (csf_nullptr == callback) {
		get_read_timeout().set_handle(
			csf_bind(&csf_connect::timeout_handle
				, this
				, std::placeholders::_1
				, std::placeholders::_2));
	}
	else {
		get_read_timeout().set_handle(callback);
	}
	
	get_factory()->get_timeout_manager().insert(get_read_timeout(), shared_from_this());

	return csf_succeed;
}


/**
* 主要功能是：设置写超时时间。
* 返回：0表示成功；非0表示失败；
*
* @param timeout_ms		表示超时的时间数值，单位：毫秒（ms）
* @param callback    表示超时回调函数。
*/
csf_int32 csf_connect::set_write_timeout(const csf_uint64 timeout_ms, const csf_connect_callback& callback) {

	get_write_timeout().set_time(csf::core::utils::time::system_time::get_time());
	get_write_timeout().set_timeout(timeout_ms);
	if (csf_nullptr == callback) {
		get_write_timeout().set_handle(
			csf_bind(&csf_connect::timeout_handle
				, this
				, std::placeholders::_1
				, std::placeholders::_2));
	}
	else {
		get_write_timeout().set_handle(callback);
	}
	get_factory()->get_timeout_manager().insert(get_write_timeout(), shared_from_this());

	return 0;
}


/**
* 主要功能是：更新异步写超时对象
* 返回：0表示成功；非0表示失败；
*/
inline void csf_connect::flush_write_timeout() {
	get_write_timeout().set_time(csf::core::utils::time::system_time::get_time());
}


/**
* 主要功能是：更新异步读超时对象
* 返回：0表示成功；非0表示失败；
*/
inline void csf_connect::flush_read_timeout() {
	get_read_timeout().set_time(csf::core::utils::time::system_time::get_time());
}


/**
* 主要功能是：打开一个监听地址。
* 返回：0表示成功；非0表示失败；
*
* @param url    表示需要监听的地址
* @param callback    表示读取数据存在的指定缓存长度
*/
csf_int32 csf_connect::listen(const csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：需要连接一个地址。
* 返回：0表示成功；非0表示失败；
*
* @param url    表示读取数据存在的指定缓存长度
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_connect::connect(const csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_buffer& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_csfstring& csfstr, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_chain& chain, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buf    表示内容的缓存地址
* @param len    表示内容缓存的长度
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(const csf_uchar* buf, const csf_uint32 len, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要写入的csf_buffer内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_buffer& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param csfstr    表示csf_csfstring的内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_csfstring& csfstr, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param chain    表示csf_chain的内容
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_chain& chain, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入指定缓存的内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_uchar>& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_connect::write(csf_connect_buffer<csf_buffer>& buffer, csf_url& url, const csf_connect_callback& callback) {

	return 0;
}


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_csfstring>& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：发送csf_csfstring内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param url    表示需要发送数据的目的地址
* @param callback    表示需要返回的回调函数
*/
// csf_int32 csf_connect::write(csf_connect_buffer<csf_chain>& buffer, csf_url& url, const csf_connect_callback& callback) {
// 
// 	return 0;
// }


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buf    表示读取数据存在的指定缓存地址
*
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(const csf_uchar* buf, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的csf_buffer
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(csf_buffer& buffer, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param csfstr    表示读取数据存在的csf_csfstring
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(csf_csfstring& csfstr, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param chain    表示读取数据存在的csf_csfstring
* @param len    表示读取数据存在的指定缓存长度
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(csf_chain& chain, const csf_uint32 len, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存放的缓存对象
*
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(csf_connect_buffer<csf_uchar>& buffer, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
csf_int32 csf_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {
	return 0;
}



/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(csf_connect_buffer<csf_csfstring>& buffer, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：读取数据并存在指定缓存链表中。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
// csf_int32 csf_connect::read(csf_connect_buffer<csf_chain>& buffer, const csf_connect_callback& callback) {
// 	return 0;
// }



/**
* 主要功能是：连接超时处理函数句柄
* 返回：0表示成功；非0表示失败；
*
* @param connect_ptr    表示连接对象
* @param connect_error    表示连接错误信息
*/
csf::core::base::csf_int32 csf_connect::timeout_handle(csf_connect_ptr connect_ptr, csf_connect_error connect_error) {

	connect_ptr->close();
	get_factory()->remove(connect_ptr);

	csf_log_ex(info
		, csf_log_code_info
		, "connect[%p] timeout."
		, connect_ptr.get());

	return 0;
}
