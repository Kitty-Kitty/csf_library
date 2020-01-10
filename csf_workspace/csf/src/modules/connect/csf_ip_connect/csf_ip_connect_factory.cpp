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

#include "csf_attribute_include.h"
#include "csf_ip_connect_factory.hpp"
#include "csf_tcp_connect.hpp"
#include "csf_udp_connect.hpp"
#include "csf_app.hpp"


using csf::modules::connect::csf_ip_connect_factory;


csf_ip_connect_factory::csf_ip_connect_factory()
	: m_idle_interval(csf_ip_connect_factory_timer_interval_ms)
	, m_connect_limit(csf_ip_connect_factory_connect_limit)
	, m_connect_timeout(csf_connect_timeout_default_ms) {

 	set_version(
 		csf_connect_version
 		, CSF_CONNECT_VER
		, CSF_CONNECT_VAR
 		, "general ip connect factory"
 	);
}



csf_ip_connect_factory::~csf_ip_connect_factory() {

}



/**
* 主要功能是：主要实现模块的配置信息处理接口。
* 返回：0表示成功；非0表示失败；
*
* @param element    表示模块的配置信息
*
* 常用的配置信息保存结构为：
* <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* <module>
*        <!--***表示模块对应的模块名称信息***-->
*        <name>csf_connection</name>
*        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
*        <mid>02000000-0000001</mid>
*        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
*        <configure>
*                <!--表示线程数量-->
*                <thread_number>4</thread_number>
*        </configure>
* </module>
*/
csf_int32 csf_ip_connect_factory::configure(const csf_element& element) {

	//根配置信息
	get_attribute_manager().set_root_element(&element);

	//表示连接工厂所需要创建的线程数量，数值默认为：2
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(thread_number)
		, csf_attribute_int(std::list<csf_string>{ "thread_number" }
		, csf_attribute_boundary("[2, n)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(csf_ip_connect_factory_thread_number)));
	//表示连接超时管理器需要创建的线程数量，数值默认为：2
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(timeout_manager_thread_number)
		, csf_attribute_int(std::list<csf_string>{ "timeout_manager_thread_number" }
		, csf_attribute_boundary("[1, n)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(csf_ip_connect_factory_thread_number)));
	//表示连接工厂所能接收的最大连接数，数值默认为：1024
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(connect_limit)
		, csf_attribute_int(std::list<csf_string>{ "connect_limit" }
		, csf_attribute_boundary("[1, 65535]")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(csf_ip_connect_factory_connect_limit)));
	//表示连接的超时时间，数值默认为：5s
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(connect_timeout)
		, csf_attribute_time(std::list<csf_string>{ "connect_timeout" }
		, csf_attribute_time::csf_time_unit_ms
		, csf_attribute_boundary("[10, n)")
		, csf_attribute_default_value<csf_attribute_time, csf_int64>(csf_connect_timeout_default_ms)));
	//表示定时器时间间隔，数值默认为：500ms
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(idle_interval)
		, csf_attribute_time(std::list<csf_string>{ "idle_interval" }
		, csf_attribute_time::csf_time_unit_ms
		, csf_attribute_boundary("[10, n)")
		, csf_attribute_default_value<csf_attribute_time, csf_int64>(csf_ip_connect_factory_timer_interval_ms)));

	//表示连接工厂所能接收的最大连接数，数值默认为：1024
	set_connect_limit((csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(connect_limit)));

	//表示连接的超时时间，单位：毫秒（ms）
	set_connect_timeout(get_attribute_manager().get_value<csf_attribute_time>(CSF_ATTRIBUTE_NAME(connect_timeout)));

	//更新系统的空闲间隔时间，单位：毫秒（ms）
	set_idle_interval(get_attribute_manager().get_value<csf_attribute_time>(CSF_ATTRIBUTE_NAME(idle_interval)));


	return 0;
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
		tmp_connect = new csf_udp_connect(*this, type);
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

	csf_int32				tmp_int_ret = csf_failure;


	//更新配置项内容
	tmp_int_ret = csf_device_base::configure(conf_mg, std::list<csf_string>{ CSF_CONNECT_VAR });
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "configure failed!");
		return csf_failure;
	}

	return csf_connect_factory::init(conf_mg);
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
		if (tmp_connect_ptr->set_local_url(const_cast<csf_url&>(local_url))) {
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

	csf_int32				tmp_int_ret = csf_failure;


	//更新配置项内容
	tmp_int_ret = csf_device_base::configure(conf_mg, std::list<csf_string>{ CSF_CONNECT_VAR });
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "configure failed!");
		return csf_failure;
	}

	//启动超时管理器
	tmp_int_ret = csf_connect_factory::get_timeout_manager().start(
		(csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(timeout_manager_thread_number)));
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "start timeout manager failed!");
		return csf_failure;
	}

	//启动处理线程池
	tmp_int_ret = start_thread_pool();
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "start thread pool failed!");
		return csf_failure;
	}

	return csf_succeed;
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
		if (tmp_connect_ptr->set_remote_url(const_cast<csf_url&>(remote_url))) {
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


/**
* 主要功能是：启动线程池
* 返回：无
*/
csf_int32 csf_ip_connect_factory::start_thread_pool() {

	csf_int32				tmp_int_ret = csf_failure;

	
	//启动线程池，准备进行网络连接处理
	tmp_int_ret = get_thread_pool().start(
		(csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number))
		, csf_bind(&csf_ip_connect_factory::run_io_service, this));

	if (csf_failure == tmp_int_ret) {

		csf_log_ex(error, csf_log_code_error
			, "start thread pool failed! thread_number[%d], idle_interval[%d ms]."
			, (csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number))
			, (csf_int32)get_idle_interval());

		return csf_failure;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "start thread pool succeed! thread_number[%d], idle_interval[%d ms]."
			, (csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number))
			, (csf_int32)get_idle_interval());
	}

	return csf_succeed;
}


/**
* 主要功能是：线程池启动的io_service任务
* 返回：无
*/
csf_void csf_ip_connect_factory::run_io_service() {

	try	{

		get_io_service().run();

		csf_msleep((csf_uint32)get_idle_interval());
	}
	catch (boost::exception& e)	{
		csf_log_ex(error, csf_log_code_error
			, "io_service run() failed! reason:[%s -- %s]."
			, boost::current_exception_diagnostic_information().c_str()
			, boost::diagnostic_information(e).c_str());

		//get_thread_pool().stop();
	}
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