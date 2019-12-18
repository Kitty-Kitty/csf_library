/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_directory_monitor.hpp
*
*Version: 1.0
*
*Date: 12-12月-2019 22:03:18
*
*Description: Class(csf_directory_monitor)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_directory_monitor.hpp"

using csf::modules::process::csf_directory_monitor;


csf_directory_monitor::~csf_directory_monitor() {

}


/**
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_directory_monitor::init(const csf_configure_manager * conf_mg) {

	//初始化监控事件对应的处理函数
	init_function();

	return 0;
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_directory_monitor::start(const csf_configure_manager * conf_mg) {

	csf_bool		tmp_bool_ret = csf_false;


	//如果需要监控的目录不存在，则先创建目录
	tmp_bool_ret = create_directory();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "create_directory() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "create_directory() succeed!");
	}

	//初始化文件管理器对象
	tmp_bool_ret = init_files_manager();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "init_files_manager() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "init_files_manager() succeed!");
	}

	//启动文件管理器对象
	tmp_bool_ret = start_files_manager();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "start_files_manager() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start_files_manager() succeed!");
	}

	//真正启动目录监控
	tmp_bool_ret = start_monitor();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "start_monitor() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start_monitor() succeed!");
	}

	return csf_succeed;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_directory_monitor::stop(const csf_configure_manager * conf_mg) {

	csf_bool		tmp_bool_ret = csf_false;


	//停止目录监控
	tmp_bool_ret = stop_monitor();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "stop_monitor() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "stop_monitor() succeed!");
	}

	//停止文件管理器对象
	tmp_bool_ret = stop_files_manager();
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "stop_files_manager() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "stop_files_manager() succeed!");
	}

	return csf_succeed;
}


/**
* * 主要功能是：主要实现模块的配置信息处理接口。
* * 返回：0表示成功；非0表示失败；
* *
* * @param element    表示模块的配置信息
* *
* * 常用的配置信息保存结构为：
* * <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* * <module>
* *        <!--***表示模块对应的模块名称信息***-->
* *        <name>csf_connection</name>
* *        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
* *        <mid>02000000-0000001</mid>
* *        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
* *        <configure>
* *                <!--表示线程数量-->
* *                <thread_number>4</thread_number>
* *        </configure>
* * </module>
*
*/
csf_int32 csf_directory_monitor::configure(const csf_element& element) {

	//根配置信息
	get_attribute_manager().set_root_element(&element);


	//表示需要监控的目录
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(directory)
		, csf_attribute_string(std::list<csf_string>{ "directory"}
	, csf_attribute_exception_critical()));

	//被监控的文件扩展名（取值如:mp4、txt、log等）
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(extension)
		, csf_attribute_string(std::list<csf_string>{ "extension"}
	, csf_attribute_exception_critical()));

	//表示单文件回滚大小，每次释放空间时需要释放的空间大小。
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(rotation_size)
		, csf_attribute_space_size(std::list<csf_string>{ "rotation_size" }
	, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
		, csf_attribute_boundary("(0, n)")
		, csf_attribute_exception_critical()));

	//表示目录中所有文件占用磁盘最大大小。
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(stored_max_size)
		, csf_attribute_space_size(std::list<csf_string>{ "stored_max_size" }
	, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
		, csf_attribute_boundary("(1024, n)")
		, csf_attribute_exception_critical()));

	//表示磁盘空间最小多大的时候才能往目录中保存文件。
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(disk_min_free_size)
		, csf_attribute_space_size(std::list<csf_string>{ "disk_min_free_size" }
	, csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_b
		, csf_attribute_boundary("(1024, n)")
		, csf_attribute_exception_critical()));

	//表示处理目录状态变化的线程数量，数值默认为：1
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(thread_number)
		, csf_attribute_int(std::list<csf_string>{ "thread_number" }
	, csf_attribute_boundary("[1, n)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(1)));

	//表示需要实时循环监测文件系统的时间间隔，即每次监测的时间间隔。
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(rotation_interval)
		, csf_attribute_time(std::list<csf_string>{ "rotation_interval" }
		, csf_attribute_time::csf_time_unit_s
		, csf_attribute_boundary("[1, n)")
		, csf_attribute_default_value<csf_attribute_time, csf_int64>(10)));

	//表示单个文件更新操作时，需要实时更新状态的间隔时间
	//
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(modify_update_interval)
		, csf_attribute_time(std::list<csf_string>{ "modify_update_interval" }
		, csf_attribute_time::csf_time_unit_ms
		, csf_attribute_boundary("[1000, n)")
		, csf_attribute_default_value<csf_attribute_time, csf_int64>(10000)));

	return csf_succeed;
}


/**
* 功能：
*    初始目录监控事件所对应的处理函数
* 返回：
*    无
*/
void csf_directory_monitor::init_function() {
	//处理未知消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::null
			, csf_bind(&csf_directory_monitor::event_null
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
	//处理文件添加消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::added
			, csf_bind(&csf_directory_monitor::event_added
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
	//处理文件删除消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::removed
			, csf_bind(&csf_directory_monitor::event_removed
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
	//处理文件修改消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::modified
			, csf_bind(&csf_directory_monitor::event_modified
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
	//处理修改文件名称消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::renamed_old_name
			, csf_bind(&csf_directory_monitor::event_renamed_old_name
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
	//处理修改文件名称消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::renamed_new_name
			, csf_bind(&csf_directory_monitor::event_renamed_new_name
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
	//处理文件扫描消息
	get_function_map().insert(
		std::make_pair(boost::asio::dir_monitor_event::recursive_rescan
			, csf_bind(&csf_directory_monitor::event_recursive_rescan
				, this
				, std::placeholders::_1
				, std::placeholders::_2
				, std::placeholders::_3)));
}


/**
* 功能：
*    创建需要监控的目录
* 返回：
*    true  ： 表示成功
*    false ： 表示失败
*/
bool csf_directory_monitor::create_directory() {

	std::string		tmp_path = get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(directory));


	//如果目录已经存在，则直接返回正确
	if (boost::filesystem::is_directory(tmp_path)) {
		csf_log(notice
			, "monitor directory[%s] is exist."
			, tmp_path.c_str()
		);
		return true;
	}

	//如果目录不存在，则重新创建目录
	try {
		if (boost::filesystem::create_directories(tmp_path)) {
			csf_log(notice
				, "create monitor directory[%s] succeed."
				, tmp_path.c_str()
			);
			return true;
		}
		else {
			csf_log(error
				, "create monitor directory[%s] failed!"
				, tmp_path.c_str()
			);
			return false;
		}
	}
	catch (boost::filesystem::filesystem_error e) {
		csf_log(error
			, "create monitor directory[%s] failed! error_code[ %d ]: %s."
			, tmp_path.c_str()
			, e.code()
			, e.what()
		);
		return false;
	}

	return false;
}


/**
* 功能：
*    启动目录监控处理
* 返回：
*    无
*/
bool csf_directory_monitor::start_monitor() {

	std::string		tmp_path = get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(directory));


	get_dm().add_directory(tmp_path);
	//  	get_dm().async_monitor(csf_bind(&csf_directory_monitor::event_process
	//  		, this
	//  		, get_dm()
	//  		, std::placeholders::_1
	//  		, std::placeholders::_2));

	get_dm().async_monitor([&](const boost::system::error_code &ec, const boost::asio::dir_monitor_event &ev) {
		event_process(get_dm(), ec, ev);
	});
	csf_log(notice
		, "start async monitor directory[%s] succeed."
		, tmp_path.c_str()
	);

	return start_thread_pool();
}


/**
* 功能：
*    启动线程组，进行监控处理
* 返回：
*    无
*/
bool csf_directory_monitor::start_thread_pool() {

	csf_int32			tmp_int_ret = csf_failure;
	csf_int32			tmp_thread_number = get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number));


	//启动线程池中的线程组
	tmp_int_ret = get_thread_pool().start(tmp_thread_number
		, csf_bind(&csf_directory_monitor::thread_process, this));
	if (csf_failure == tmp_int_ret) {
		csf_log(error
			, "start thread pool[%d] failed!"
			, tmp_thread_number
		);
		return csf_false;
	}
	else {
		csf_log(notice
			, "start thread pool[%d] succeed!"
			, tmp_thread_number
		);
		return csf_true;
	}

	return csf_true;
}


/**
* 功能：
*    表示线程处理函数
* 返回：
*    无
*/
void csf_directory_monitor::thread_process() {
	get_io_service().run();
}


/**
* 功能：
*    停止线程组，停止监控处理
* 返回：
*    无
*/
bool csf_directory_monitor::stop_thread_pool() {

	csf_int32			tmp_int_ret = csf_failure;


	//启动线程池中的线程组
	tmp_int_ret = get_thread_pool().stop();
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "stop thread pool failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "stop thread pool succeed!");
		return csf_true;
	}

	return csf_true;
}


/**
* 功能：
*    停止目录监控处理
* 返回：
*    无
*/
bool csf_directory_monitor::stop_monitor() {

	get_io_service().reset();
	get_io_service().stop();

	return stop_thread_pool();
}


/**
* 功能：
*    初始化文件管理器对象
* 返回：
*    无
*/
bool csf_directory_monitor::init_files_manager() {

	csf_bool			tmp_bool_ret = csf_false;


	tmp_bool_ret = get_files_manager().set_content(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(directory))
		, get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(extension)));
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "files manager set_content() failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "files manager set_content() succeed!");
	}

	tmp_bool_ret = get_files_manager().set_space(
		get_attribute_manager().get_value<csf_attribute_space_size>(CSF_ATTRIBUTE_NAME(rotation_size))
		, get_attribute_manager().get_value<csf_attribute_space_size>(CSF_ATTRIBUTE_NAME(stored_max_size))
		, get_attribute_manager().get_value<csf_attribute_space_size>(CSF_ATTRIBUTE_NAME(disk_min_free_size))
	);
	if (csf_false == tmp_bool_ret) {
		csf_log(error, "files manager set_space() failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "files manager set_space() succeed!");
	}

	get_files_manager().set_modify_update_time(
		get_attribute_manager().get_value<csf_attribute_time>(CSF_ATTRIBUTE_NAME(modify_update_interval))
	);

	return csf_true;
}


/**
* 功能：
*    启动文件管理器对象
* 返回：
*    无
*/
bool csf_directory_monitor::start_files_manager() {

	csf_int32			tmp_int_ret = csf_failure;


	//初始化文件管理对象
	tmp_int_ret = get_files_manager().init();
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "init files manager failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "init files manager succeed!");
	}

	//启动文件管理对象
	tmp_int_ret = get_files_manager().start();
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "start files manager failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "start files manager succeed!");
	}

	return csf_true;
}


/**
* 功能：
*    停止文件管理器对象
* 返回：
*    无
*/
bool csf_directory_monitor::stop_files_manager() {

	csf_int32			tmp_int_ret = csf_failure;


	//停止文件管理对象
	tmp_int_ret = get_files_manager().stop();
	if (csf_failure == tmp_int_ret) {
		csf_log(error, "stop files manager failed!");
		return csf_false;
	}
	else {
		csf_log(notice, "stop files manager succeed!");
	}

	return csf_true;
}


/**
* 功能：
*    表示事件消息处理的主要函数
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_process(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {

	//判断处理错误
	if (ec) {
		csf_log(error, "error_code[ %d ]: %s"
			, ec.value()
			, ec.message().c_str());
		return;
	}

	//从事件处理列表中查找需要的处理函数
	auto tmp_function = get_function_map().find(ev.type);
	if (tmp_function != get_function_map().end()) {

		if (boost::asio::dir_monitor_event::event_type::modified != ev.type) {
			csf_log(notice
				, "get process event. [event: %s | file: %s]"
				, ev.type_cstr()
				, ev.path.string().c_str()
			);
		}

		tmp_function->second(dm, ec, ev);		
	}
	else {
		csf_log(error
			, "event[%d] not found process function!"
			, ev.type);
	}

	get_dm().async_monitor([&](const boost::system::error_code &ec, const boost::asio::dir_monitor_event &ev) {
		event_process(get_dm(), ec, ev);
	});
}


/**
* 功能：
*    处理文件添加消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_added(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {
	// 	csf_log(notice, "%s"
	// 		, ev.type_cstr());
		// 	boost::filesystem::last_write_time();
		// 	boost::filesystem::file_size();
		//std::cout << ev << std::endl;
// 	csf_log(notice
// 		, "get process event. [event: %s | file: %s]"
// 		, ev.type_cstr()
// 		, ev.path.string().c_str()
// 	);
	get_files_manager().add(ev.path.string());
}


/**
* 功能：
*    处理未知消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_null(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {
	csf_log(warning, "get uknow event [%s]."
		, ev.type_cstr());
}


/**
* 功能：
*    处理文件删除消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_removed(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {
	get_files_manager().remove(ev.path.string());
}


/**
* 功能：
*    处理文件修改消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_modified(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {

	get_files_manager().modify(ev.path.string());
}


/**
* 功能：
*    处理修改文件名称消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_renamed_old_name(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {

	get_files_manager().rename(ev.path.string());
}


/**
* 功能：
*    处理修改文件名称消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_renamed_new_name(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {

	get_files_manager().rename(ev.path.string());
}


/**
* 功能：
*    处理文件扫描消息
* 返回：
*    无
*
* @param dm    表示当前的监控对象
* @param ec    表示当前的系统错误对象
* @param ev    表示当前目录监控事件类型
*/
void csf_directory_monitor::event_recursive_rescan(boost::asio::dir_monitor& dm, const boost::system::error_code& ec, const boost::asio::dir_monitor_event& ev) {
	csf_log(warning, "get recursive rescan event [%s]. don't process!"
		, ev.type_cstr());
}




/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* 表示模块的create 和 destroy 句柄定义。                                              */
/* 每个需要通过模块工厂创建的模块都需要添加该宏定义。                                    */
/* 其中module_type表示该模块的类名称，该类实现了构造方法为：                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(csf_directory_monitor)