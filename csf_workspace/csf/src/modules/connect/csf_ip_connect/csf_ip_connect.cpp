/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 15:10:39
*
*Description: Class(csf_ip_connect)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connect.hpp"

using csf::modules::connect::csf_ip_connect;


csf_ip_connect::~csf_ip_connect() {

}


/**
* 主要功能是：写入csf_buffer内容。
* 返回：小于等于0表示失败；大于0表示成功写入的数据长度；
*
* @param buffer    表示需要发送的内容缓存
* @param callback    表示需要返回的回调函数
*/
csf_int32 csf_ip_connect::write(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//先判断数据的合法性，之后再处理
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_invalid_parametes, "data is null"));
		return csf_failure;
	}

	//如果buffer中写长度大小没有设置（buffer.get_length()为0），则根据宿主的空间大小自动设置数据
	//这样处理主要为减少收发操作时的使用成本，用户不用记得必须调用buffer.set_length()函数。但底层的自动处理，同时引入了程序的不确定性。
	//发送默认长度为宿主容器中数据的长度
	//接收默认长度为宿主容器中空闲空间的长度
	if (buffer.get_length() <= 0 && buffer.length() > 0) {
		buffer.set_length(buffer.length());
	}

	//根据csf_connect_buffer的标志位来判断异步与同步
	if (buffer.get_is_sync()) {
		//return sync_write(buffer.get_buffer(), buffer.get_length(), callback);
		return sync_write(buffer, callback);
	}
	else {
		//return async_write(buffer.get_buffer(), buffer.get_length(), callback);
		return async_write(buffer, callback);
	}
	return 0;
}


/**
* 主要功能是：读取数据并存在指定缓存位置。
* 返回：小于等于0表示失败；大于0表示成功读取的数据长度；
*
* @param buffer    表示读取数据存在的缓存对象
* @param callback    表示读取的回调函数
*/
csf_int32 csf_ip_connect::read(csf_connect_buffer<csf_buffer>& buffer, const csf_connect_callback& callback) {

	//先判断数据的合法性，之后再处理
	if (!buffer.is_valid()) {
		exception_callback(shared_from_this()
			, callback
			, csf_ip_connect_error(csf_connect_error::csf_connect_code_not_enough_space
				, "not enough storage available"));
		return csf_failure;
	}

	//如果接收长度为空（buffer.get_length()为0），则表示采用宿主容器的空闲空间大小。
	//这样处理主要为减少收发操作时的使用成本，用户不用记得必须调用buffer.set_length()函数。但底层的自动处理，同时引入了程序的不确定性。
	//发送默认长度为宿主容器中数据的长度
	//接收默认长度为宿主容器中空闲空间的长度
	if (buffer.get_length() <= 0 && buffer.avail() > 0) {
		buffer.set_length(buffer.avail());
	}

	//更新filled标志位
	set_is_filled(buffer.get_is_filled());

	//根据csf_connect_buffer的标志位和回调函数是否为空来判断异步与同步
	if (buffer.get_is_sync() || csf_nullptr == callback) {
		//return sync_read(buffer.get_buffer(), buffer.get_length(), callback);
		return sync_read(buffer, callback);
	}
	else {
		//return async_read(buffer.get_buffer(), buffer.get_length(), callback);
		return async_read(buffer, callback);
	}
	return 0;
}


/**
* 主要功能是：处理异步写处理回调函数
* 返回：0表示处理成功；非0表示处理失败
*
* @param buffer		 表示内容的缓存
* @param connect_ptr 表示当前的网络连接对象
* @param callback    表示异常处理句柄信息
* @param error_code  表示boost的错误信息
* @param length		表示当前实际写的缓存长度
*/
csf_bool csf_ip_connect::async_write_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {


	//如果处理错误，则按照错误处理
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	//如果已经发送完成所有数据，则正常回调返回
	if (length >= buffer.get_length()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//如果没有发送完全，还有部分数据，则更新缓存信息继续发送
		buffer.get_container()->set_pos(buffer.get_container()->get_pos() + length);
		buffer.set_length(buffer.get_length() - length);

		async_write(std::ref(buffer), callback);
	}

	return csf_true;
}


/**
* 主要功能是：处理异步读处理回调函数
* 返回：0表示处理成功；非0表示处理失败
*
* @param buffer		 表示内容的缓存
* @param connect_ptr 表示当前的网络连接对象
* @param callback    表示异常处理句柄信息
* @param error_code  表示boost的错误信息
* @param length   表示当前实际写的缓存长度
*/
csf_bool csf_ip_connect::async_read_callback(csf_connect_buffer<csf_buffer>& buffer
	, csf_connect_ptr connect_ptr
	, const csf_connect_callback& callback
	, const boost::system::error_code& error_code
	, csf_uint32 length) {

	//如果处理错误，则按照错误处理
	if (error_code) {
		exception_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_false;
	}

	if (length > 0) {
		//如果接收到数据，则移动buffer中的缓存游标，方便下一次接收
		buffer.get_container()->set_last(buffer.get_container()->get_last() + length);
		buffer.set_length(buffer.get_length() - length);
	}

	//如果需要接收所有数据，则继续接收，直到完整接收完全
	if (csf_false == buffer.get_is_filled()) {
		async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
		return csf_true;
	}
	else {
		//如果已经发送完成所有数据，则正常回调返回
		if (length >= buffer.get_length()) {
			async_callback(shared_from_this(), callback, csf_ip_connect_error(error_code));
			return csf_true;
		}
		else {
			async_read(std::ref(buffer), callback);
		}
	}

	return csf_true;
}
