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

	csf_device					*tmp_device = csf_nullptr;
	csf_connect_factory			*tmp_factory = csf_nullptr;
	csf_connect_ptr				tmp_connect;


	//查找指定的连接管理器对象
	tmp_device = get_app()->find_device(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(connect_factory)));
	if (csf_nullptr == tmp_device) {
		csf_log_ex(error
			, csf_log_code_error
			, "not found connect factory[%s]"
			, get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(connect_factory)).c_str());
		return csf_failure;
	}

	//设置连接管理器
	tmp_factory = dynamic_cast<csf_connect_factory*>(tmp_device);
	set_connect_factory(tmp_factory);

	//创建需要的连接
	tmp_connect = tmp_factory->create(csf_connect::csf_connect_type_tcp);
	if (!tmp_connect) {
		csf_log_ex(error
			, csf_log_code_error
			, "create connect failed!");
		return csf_failure;
	}

	if (csf_failure == tmp_connect->set_remote_url(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(center)))) {

		csf_log_ex(error
			, csf_log_code_error
			, "url[%s] failed!"
			, get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(center)).c_str());

		return csf_failure;
	}
	else {
		if (csf_failure == tmp_connect->connect(tmp_connect->get_remote_url())) {
			return csf_failure;
		}
		else {
			csf_log_ex(notice
				, csf_log_code_notice
				, "connect [%s] succeed!"
				, tmp_connect->get_remote_url().get_url().c_str());

			tmp_connect->get_write_buffer().create(1024);

			csf_string			tmp_string = "hello world! I'm client!";

			tmp_connect->get_write_buffer().clear();
			tmp_connect->get_write_buffer().cat(tmp_string);
			//connect_ptr->get_write_buffer().set_length(tmp_string.length());
			tmp_connect->write(std::ref(tmp_connect->get_write_buffer()));

			tmp_connect->close();
		}
	}

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
	connect_ptr->get_write_buffer().create(1024);

	connect_ptr->set_read_handle(csf_bind(&test_connect_factory_manager::read_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2
		, std::ref(connect_ptr->get_read_buffer())));
// 	set_read_function(csf_bind(&test_connect_factory_manager::read_handle
// 		, this
// 		, std::placeholders::_1
// 		, std::placeholders::_2
// 		, std::ref(connect_ptr->get_read_buffer())));

	// 	connect_ptr->read(std::ref(connect_ptr->get_read_buffer())
	// 		, csf_bind(&test_connect_factory_manager::read_handle
	// 			, this
	// 			, connect_ptr
	// 			, std::ref(connect_ptr->get_read_buffer())
	// 			, std::placeholders::_1));

	connect_ptr->read(std::ref(connect_ptr->get_read_buffer()), connect_ptr->get_read_handle());

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

	connect_ptr->get_read_buffer().create(1024);
	connect_ptr->get_write_buffer().create(1024);

	connect_ptr->set_read_handle(csf_bind(&test_connect_factory_manager::read_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2
		, std::ref(connect_ptr->get_read_buffer())));

// 	set_read_function(csf_bind(&test_connect_factory_manager::read_handle
// 		, this
// 		, std::placeholders::_1
// 		, std::placeholders::_2
// 		, std::ref(connect_ptr->get_read_buffer())));

	// 	connect_ptr->read(std::ref(connect_ptr->get_read_buffer())
	// 		, csf_bind(&test_connect_factory_manager::read_handle
	// 			, this
	// 			, connect_ptr
	// 			, std::ref(connect_ptr->get_read_buffer())
	// 			, std::placeholders::_1));

	connect_ptr->read(std::ref(connect_ptr->get_read_buffer()), connect_ptr->get_read_handle());

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

	csf_string			tmp_string = "hello world!";


	if (connect_error.get_code()) {
		connect_ptr->close();
		return 0;
	}

	csf_log_ex(info, csf_log_code_info
		, "get data length[%d]"
		, connect_buffer.length());

	if (csf_connect::csf_connect_type_tcp == connect_ptr->get_type()) {
		connect_ptr->get_write_buffer().clear();
		connect_ptr->get_write_buffer().cat(tmp_string);
		//connect_ptr->get_write_buffer().set_length(tmp_string.length());
		connect_ptr->write(std::ref(connect_ptr->get_write_buffer()));
	}

	connect_buffer.clear();
	//connect_buffer.set_length(connect_buffer.size());
	connect_ptr->read(std::ref(connect_buffer), connect_ptr->get_read_handle());

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
csf_int32 test_connect_factory_manager::configure(const csf_element& element) {

	//根配置信息
	get_attribute_manager().set_root_element(&element);

	//表示该模块使用的连接管理器配置
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(connect_factory)
		, csf_attribute_string(std::list<csf_string>{ "connect_factory", "mid" }
	, csf_attribute_exception_critical()));

	//表示连接中心的地址
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(center)
		, csf_attribute_string(std::list<csf_string>{ "center" }
	, csf_attribute_exception_critical()));

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