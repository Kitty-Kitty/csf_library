/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:43
*
*Description: Class(csf_ip_connect_factory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_ip_connect_factory.hpp"
#include "csf_tcp_connect.hpp"
#include "csf_udp_connect.hpp"


using csf::modules::connect::csf_ip_connect_factory;


csf_ip_connect_factory::csf_ip_connect_factory() {

// 	get_version().set_version(
// 		csf_version
// 		, CSF_VER
// 		, 
// 	);
}



csf_ip_connect_factory::~csf_ip_connect_factory() {

}





/**
 * 表示根据连接类型创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type) {

	csf_connect					*tmp_connect = csf_nullptr;

	if (type & csf_connect::csf_connect_type::csf_connect_type_tcp) {
		tmp_connect = new csf_tcp_connect(*this);
	}
	else if (type & csf_connect::csf_connect_type::csf_connect_type_udp) {
		tmp_connect = new csf_udp_connect(*this);
	}
	else {
		return m_null_connect_ptr;
	}

	csf_connect_ptr tmp_connect_ptr(tmp_connect);

	get_connect_collector().insert(tmp_connect, tmp_connect_ptr);

	return tmp_connect_ptr;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_ip_connect_factory::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示根据连接类型、本地地址创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 * @param local_url    表示连接打开的本地地址
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url) {

	csf_connect_ptr					tmp_connect_ptr = create(type);

	if (tmp_connect_ptr == m_null_connect_ptr) {
		return m_null_connect_ptr;
	}
	else {
		if (tmp_connect_ptr->set_local_url((csf_url&)local_url)) {
			get_connect_collector().remove(tmp_connect_ptr.get());
			return m_null_connect_ptr;
		}
	}
	
	return  tmp_connect_ptr;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_ip_connect_factory::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示根据连接类型、本地地址、远程地址创建一个连接。成功返回非0，失败返回0。
 * 
 * @param type    表示连接类型
 * @param local_url    表示连接打开的本地地址
 * @param remote_url    表示连接打开的远程地址
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	csf_connect_ptr					tmp_connect_ptr = create(type, local_url);

	if (tmp_connect_ptr == m_null_connect_ptr) {
		return m_null_connect_ptr;
	}
	else {
		if (tmp_connect_ptr->set_remote_url((csf_url&)remote_url)) {
			get_connect_collector().remove(tmp_connect_ptr.get());
			return m_null_connect_ptr;
		}
	}

	return  tmp_connect_ptr;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_ip_connect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * 表示设备的添加操作
 * 
 * @param element    表示设备添加操作
 * @param callback    表示设备操作的回调函数
 */
csf_int32 csf_ip_connect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* 表示模块的create 和 destroy 句柄定义。                                              */
/* 每个需要通过模块工厂创建的模块都需要添加该宏定义。                                    */
/* 其中module_type表示该模块的类名称，该类实现了构造方法为：                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(csf_ip_connect_factory)