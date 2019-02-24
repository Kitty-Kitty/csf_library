/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: test_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 08-10月-2018 20:52:07
*
*Description: Class(test_connect_factory_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "test_connect_factory_manager.hpp"
#include "csf_connect_factory_manager.hpp"

using csf::example::test_connect_factory_manager;



test_connect_factory_manager::~test_connect_factory_manager() {

}





/**
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 test_connect_factory_manager::init(
	const csf_configure_manager * conf_mg) {

	csf_connect_factory_manager			cfm(conf_mg);


	//表示调用app的接口，初始化模块的日志功能，满足模块的日志记录功能
	if (get_app()) {
		get_app()->init_module_logger();
	}

	if (csf_succeed != cfm.init(conf_mg, get_app())) {
		csf_log_ex(warning, csf_log_code_warning
			, "init connect factory manager failed!");
		return csf_failure;
	}

	cfm.add_handle("tcp_handle", csf_bind(&test_connect_factory_manager::tcp_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2));


	cfm.add_handle("udp_handle", csf_bind(&test_connect_factory_manager::udp_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2));

	if (csf_succeed != cfm.start(conf_mg, get_app())) {
		csf_log_ex(warning, csf_log_code_warning
			, "start connect factory manager failed!");
		return csf_failure;
	}


	return 0;
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 test_connect_factory_manager::start(
	const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 test_connect_factory_manager::stop(
	const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* 主要功能是：tcp监听处理返回接口
* 返回：0表示正常；非0表示错误
*
* @param connect_ptr    表示当前正在处理的连接对象
* @param connect_error    表示当前处理的异常信息
*/
csf::core::base::csf_int32 test_connect_factory_manager::tcp_handle(
	csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error) {

	connect_ptr->get_read_buffer().create(1024);

	set_read_function(csf_bind(&test_connect_factory_manager::read_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2
		, std::ref(connect_ptr->get_read_buffer())));

// 	connect_ptr->read(std::ref(connect_ptr->get_read_buffer())
// 		, csf_bind(&test_connect_factory_manager::read_handle
// 			, this
// 			, connect_ptr
// 			, std::ref(connect_ptr->get_read_buffer())
// 			, std::placeholders::_1));

	connect_ptr->read(std::ref(connect_ptr->get_read_buffer()), get_read_function());

	return 0;
}


/**
* 主要功能是：udp监听处理返回接口
* 返回：0表示正常；非0表示错误
*
* @param connect_ptr    表示当前正在处理的连接对象
* @param connect_error    表示当前处理的异常信息
*/
csf::core::base::csf_int32 test_connect_factory_manager::udp_handle(
	csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error) {

	return 0;
}


/**
* 主要功能是：tcp读数据返回函数
* 返回：大于等于0表示成功；小于0表示错误
*
* @param connect_ptr    表示当前正在处理的连接对象
* @param connect_buffer
* @param connect_error    表示当前处理的异常信息
*/
csf::core::base::csf_int32 test_connect_factory_manager::read_handle(
	csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error
	, csf_connect_buffer<csf_buffer>& connect_buffer
	) {

	return 0;
}


/**
* 主要功能是：tcp读数据返回函数
* 返回：大于等于0表示成功；小于0表示错误
*
* @param connect_ptr    表示当前正在处理的连接对象
* @param connect_buffer
* @param connect_error    表示当前处理的异常信息
*/
csf::core::base::csf_int32 test_connect_factory_manager::tcp_read_handle(csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error
	, csf_int32 len)
{

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
CSF_MODULE_SYMBOY_DEFINE(test_connect_factory_manager)