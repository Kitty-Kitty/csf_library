/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: csf_common_vm.hpp
*
*Version: 1.0
*
*Date: 15-1月-2020 18:46:53
*
*Description: Class(csf_common_vm)
*
*Others:
*
*History:
*
*******************************************************************************/

#include <boost/bind.hpp>
#include "sleep_time.hpp"
#include "csf_common_vm.hpp"
#include "csf_common_slave.hpp"
#include "csf_platform.hpp"

using csf::modules::vm::csf_common_vm;


csf_common_vm::csf_common_vm()
	: m_signals(m_ioctx) {

}



csf_common_vm::~csf_common_vm() {

}





/**
 * 功能：
 *    模块初始化，进行模块启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_common_vm::init(const csf_configure_manager * conf_mg) {

	csf_bool							tmp_bool_ret = csf_false;
	csf_string							tmp_string_ret = "";


	csf_log(notice, "init vm[%s]...", get_version().to_string().c_str());

	/************************************************************************/
	/* 程序当前工作目录主要有三个方面数据来源，优先级(1<2<3)依次如下：          */
	/*		1、环境变量获取；													*/
	/*		2、配置文件获取；													*/
	/*		3、程序运行时自带的参数；											*/
	/* 该优先级的定义主要是方便满足程序的维护需求       						*/
	/************************************************************************/
	tmp_bool_ret = init_work_directory();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//解析配置文件，将所有信息保存到configure_manager中
	//
	tmp_bool_ret = init_configure_manager(get_config_mg(), get_root_configure_file());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//表示保存当前app信息到指定文件中
	tmp_bool_ret = save_information();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//加载启动日志系统，为程序提供日志服务
// 	tmp_bool_ret = init_logger(get_config_mg(), get_work_directory());
// 	if (csf_false == tmp_bool_ret) {
// 		return csf_failure;
// 	}

	//初始化虚拟机的名称
	tmp_bool_ret = init_vm_name();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//设置虚拟机的pid
	set_vm_pid(csf::core::system::platform::csf_platform::get_pid());

	return csf_succeed;
}


/**
 * 功能：
 *    模块启动，进行模块启动工作。表示模块已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_common_vm::start(const csf_configure_manager * conf_mg) {


	csf_bool							tmp_bool_ret = csf_false;


	//加载启动日志系统，为程序提供日志服务
	tmp_bool_ret = init_logger(get_config_mg(), get_work_directory());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}
	//初始化虚拟机使用的共享内存空间
	tmp_bool_ret = init_shared_memory();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//启动信号处理函数
	tmp_bool_ret = start_signals_process();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//启动子进程守护处理线程
	tmp_bool_ret = start_deamon_thread_pool();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//启动子进程退出信号处理线程
	tmp_bool_ret = start_io_context_thread_pool();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//启动所有已经配置的虚拟机
	tmp_bool_ret = start_slaves();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	return 0;
}


/**
 * 功能：
 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_common_vm::stop(const csf_configure_manager * conf_mg) {

	csf_bool							tmp_bool_ret = csf_false;


	//停止子进程退出信号处理线程
	tmp_bool_ret = stop_io_context_thread_pool();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//停止子进程守护处理线程
	tmp_bool_ret = stop_deamon_thread_pool();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//停止所有已经配置的虚拟机
	tmp_bool_ret = stop_slaves();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//销毁共享内存
	get_sm().destroy();

	return 0;
}


/**
 * 功能：
 *    初始化共享内存资源
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败；
 */
csf_bool csf_common_vm::init_shared_memory() {


	csf_int32			tmp_int_ret = csf_failure;
	csf_uint32			tmp_size = csf_sizeof(csf_common_slave) * csf_ary_size(m_slaves) * 2;
	csf_char			tmp_buf[128] = { 0, };


	//生成共享内存的名称
	csf_snprintf(tmp_buf
		, csf_sizeof(tmp_buf)
		, "%s", get_name().c_str());

	//这里"csf_sizeof(csf_common_slave) * csf_ary_size(m_slaves) * 2"主要为了分配充足的共享空间，避免空间不足而错误
	tmp_int_ret = get_sm().create(tmp_buf, tmp_size);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(critical
			, csf_log_code_critical
			, "create share memory[%s : %d] failed!"
			, tmp_buf
			, tmp_size
		);
		return csf_false;
	}
	else {
		csf_log_ex(notice
			, csf_log_code_notice
			, "create share memory[%s : %d] succeed!"
			, tmp_buf
			, tmp_size
		);
	}

	return csf_true;
}


/**
 * 功能：
 *    启动指定的私服程序
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 *
 * @param element    表示当前需要启动的伺服信息
 */
csf_bool csf_common_vm::start_slave(csf_element& element) {


	if (element.is_null()) {
		return csf_false;
	}

	csf_string			tmp_name = element.find_child("name").get_content();
	csf_string			tmp_command = element.find_child("command").get_content();
	csf_string			tmp_arguments = element.find_child("arguments").get_content();
	csf_common_slave	*tmp_slave = csf_nullptr;


	//如果名称或指令为空，则表示配置错误
	if (tmp_name.empty() || tmp_command.empty()) {
		csf_log(error
			, "slave[ name:%s | command:%s ] is null error!"
			, tmp_name.c_str()
			, tmp_command.c_str()
		);
		return csf_false;
	}

	//创建slave内存对象
	tmp_slave = get_sm().create_object<csf_common_slave>(tmp_name);
	if (csf_nullptr == tmp_slave) {
		csf_log(error
			, "create slave[ name:%s | command:%s ] instance error!"
			, tmp_name.c_str()
			, tmp_command.c_str()
		);
		return csf_false;
	}
	else {
		insert_slave(tmp_slave);

		csf_log(notice
			, "create slave[ name:%s | command:%s ] instance succeed!"
			, tmp_name.c_str()
			, tmp_command.c_str()
		);
	}

	//设置slave对象数据
	tmp_slave->set_common_vm(this);
	tmp_slave->set_name(tmp_name);
	tmp_slave->set_command(tmp_command);
	tmp_slave->set_arguments(tmp_arguments);

	//运行slave对象
	return start_slave(tmp_slave);
}


/**
 * 功能：
 *    启动所有私服进程
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 */
csf_bool csf_common_vm::start_slaves() {

	csf_element			tmp_slave_elements = get_config_mg().find_element(
		csf_list<csf_string>({ "vm_configure", "slaves" }));


	//如果没有配置伺服进程，则打印一条信息
	if (tmp_slave_elements.is_null()) {
		csf_log(warning, "not found slaves to start.");
		return csf_true;
	}

	//循环启动所有伺服进程
	for (auto tmp_slave : tmp_slave_elements.get_children()) {
		start_slave(tmp_slave);
	}

	return csf_true;
}


#ifdef __linux__

/**
 * 功能：
 *    处理已经退出的进程队列中伺服对象，实现伺服进程的守护。
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 */
csf_bool csf_common_vm::deamon_slaves() {

	for (int i = 0; i < csf_ary_size(m_slaves); i++) {

		if (csf_nullptr == m_slaves[i]) {
			continue;
		}

		if (static_cast<csf_common_slave*>(m_slaves[i])->get_signal() <= 0) {
			continue;
		}
		
		//针对对象进行守护处理
		deamon_slave(m_slaves[i]);
	}	

	return csf_true;
}
#else
/**
 * 功能：
 *    处理已经退出的进程队列中伺服对象，实现伺服进程的守护。
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 */
csf_bool csf_common_vm::deamon_slaves() {

	csf_slave			*tmp_common_slave = csf_nullptr;


	while (get_deque().pop_front(tmp_common_slave)) {

		if (!tmp_common_slave) {
			break;
		}

		//针对对象进行守护处理
		deamon_slave(tmp_common_slave);
	}

	return csf_true;
}
#endif


/**
 * 功能：
 *    实现伺服进程的守护
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_common_vm::deamon_slave(csf_slave* slave) {

	//如果不需要守护重启，则退出
	if (csf_false == static_cast<csf_common_slave*>(slave)->is_deamon()) {
		csf_log(notice
			, "slave[%s] don't deamon to restart. %s"
			, slave->get_name().c_str()
			, slave->to_string().c_str()
		);
		return csf_true;
	}
	else {
		static_cast<csf_common_slave*>(slave)->destroy_child();
	}

	if (start_slave(slave)) {
		csf_log(notice
			, "restart slave[%s] succeed! %s"
			, slave->get_name().c_str()
			, slave->to_string().c_str()
		);
	}
	else {
		csf_log(error
			, "restart slave[%s] failed! %s"
			, slave->get_name().c_str()
			, slave->to_string().c_str()
		);
		return csf_false;
	}
	return csf_true;
}


/**
 * 功能：
 *    根据名称停止指定的私服程序
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 *
 * @param name    表示当前需要停止的伺服名称
 */
csf_bool csf_common_vm::stop_slave(csf_string& name) {

	return csf_vm::stop_slave(name);
}


/**
 * 功能：
 *    停止所有私服进程
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 */
csf_bool csf_common_vm::stop_slaves() {

	return csf_vm::stop_slaves();
}


/**
 * 功能：
 *    根据名称查找指定的私服信息
 * 返回：
 *    非null  ：  表示查找到的伺服对象；
 *      null  ：  表示不存在指定的伺服对象；
 *
 * @param name    表示伺服名称
 */
csf_slave* csf_common_vm::find_slave(csf_string& name) {

	return  csf_vm::find_slave(name);
}


/**
 * 功能：
 *    表示进程信号处理函数
 * 返回：
 *    无
 *
 * @param ec    表示错误码
 * @param signal    表示进程当前接收到的信号数值
 */
void csf_common_vm::signal_handler(boost::system::error_code ec, int signal) {

#ifdef __linux__
	csf_log(warning
		, "get signal[%d : %s] error_code[%d : %s]."
		, signal
		, strsignal(signal)
		, ec.value()
		, boost::system::system_error(ec).what()
	);
#else
	csf_log(warning
		, "get signal[%d] error_code[%d : %s]."
		, signal
		, ec.value()
		, boost::system::system_error(ec).what()
	);
	//deamon_slaves();
#endif

	switch (signal) {
	case SIGINT:
	{
		std::cout << "SIGNINT" << std::endl;
	}
	break;
	case SIGTERM:
	{
		std::cout << "SIGNTERM" << std::endl;
	}
	break;
#ifdef __linux__
	case SIGCHLD:
	{
		std::cout << "SIGCHLD" << std::endl;
#if 0
		static_cast<csf_common_slave*>(m_slaves[0])->destroy_child();

		for (int i = 0; i < csf_ary_size(m_slaves); i++) {
			if (m_slaves[i]) {
				static_cast<csf_common_slave*>(m_slaves[i])->destroy_child();
			}
		}

		//deamon_slaves();
		pid_t			tmp_pid = 0;
		int				stat = 0;
		//循环调用waitpid，尽量避免不出现僵尸进程而导致子进程不被重新创建问题
		while ((tmp_pid = waitpid(-1, &stat, WNOHANG)) > 0) {
			printf("child %d terminated\n", tmp_pid);
		}
#endif
	}
	break;
#endif
	default:
	{
	}
	break;
	}
}


/**
 * 功能：
 *    根据名称启动指定的私服程序
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param name    表示伺服名称
 */
csf_bool csf_common_vm::start_slave(csf_string& name) {

	return csf_vm::start_slave(name);
}


/**
 * 功能：
 *    启动指定的私服程序
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_common_vm::start_slave(csf_slave* slave) {

	csf_int32			tmp_int_return = csf_failure;


	if (csf_nullptr == slave) {
		return csf_false;
	}
	csf_common_slave	*tmp_common_slave = (csf_common_slave*)slave;


	//初始化伺服对象
	tmp_int_return = tmp_common_slave->init();
	if (csf_failure == tmp_int_return) {
		csf_log(error
			, "init slave failed! %s"
			, tmp_common_slave->to_string().c_str()
		);
		return csf_false;
	}
	else {
		csf_log(notice
			, "init slave succeed! %s"
			, tmp_common_slave->to_string().c_str()
		);
	}

	//运行伺服对象
	tmp_int_return = tmp_common_slave->start();
	if (csf_failure == tmp_int_return) {
		csf_log(error
			, "start slave failed! %s"
			, tmp_common_slave->to_string().c_str()
		);
		return csf_false;
	}
	else {
		csf_log(notice
			, "start slave succeed! %s"
			, tmp_common_slave->to_string().c_str()
		);
	}
	return csf_true;

#if 0
	if (csf_nullptr == slave) {
		return csf_false;
	}

	if (slave->get_pid() > 0) {
		//如果当前的进程正在运行
		boost::process::pid_t	tmp_pid = slave->get_pid();
		boost::process::child	tmp_child(tmp_pid);

		if (tmp_child.running()) {
			return csf_true;
		}
	}

	csf_char		tmp_exe_buf[3072] = { 0, };

	csf_snprintf(tmp_exe_buf
		, csf_sizeof(tmp_exe_buf)
		, "%s %s --name=%s --vm_pid=%d --vm_instance=0x%p "
		, slave->get_command().c_str()
		, slave->get_arguments().c_str()
		, slave->get_name().c_str()
		, csf::core::system::platform::csf_platform::get_pid()
		, this
	);

	boost::process::async_system(get_ioctx()
		, boost::bind(&csf_common_slave::exit_handler, (csf_common_slave*)slave, boost::placeholders::_1, boost::placeholders::_2)
		, csf_string(tmp_exe_buf)
	);

#if 0
	boost::asio::streambuf buffer;


	boost::process::child	tmp_child(
		std::string(tmp_exe_buf)
		, boost::process::std_out > buffer
		, slave->get_ioctx()
	);

	//slave->get_ioctx().run();
	if (tmp_child.running()) {
		slave->set_pid(tmp_child.id());

		csf_log(notice
			, "start %s succeed!"
			, slave->to_string().c_str()
		);
	}
	else {
		csf_log(error
			, "start %s failed!"
			, slave->to_string().c_str()
		);
	}
	//slave->get_ioctx().run();

#endif

#if 0
	boost::process::async_system(slave->get_ioctx()
		, boost::bind(&csf_slave::exit_handler, slave, boost::placeholders::_1, boost::placeholders::_2)
		, csf_string(tmp_exe_buf)
	);



	// 	boost::process::async_system(slave->get_ioctx()
	// 		, exit_handler
	// 		, tmp_exe_buf
	// 	);



	csf_char		tmp_arguments_buf[2048] = { 0, };

	csf_snprintf(tmp_arguments_buf
		, csf_sizeof(tmp_arguments_buf)
		, " %s --name=%s --vm_pid=%d --vm_instance=0x%p "
		, slave->get_arguments().c_str()
		, slave->get_name().c_str()
		, csf::core::system::platform::csf_platform::get_pid()
		, this
	);

	//创建child，准备启动子进程
	boost::process::child	tmp_child(
		boost::process::exe = slave->get_command()
		//, boost::process::args = { slave->get_arguments() }
		, boost::process::args = { tmp_arguments_buf }
	);



	if (tmp_child.running()) {
		slave->set_pid(tmp_child.id());

		csf_log(notice
			, "start %s succeed!"
			, slave->to_string().c_str()
		);
	}
	else {
		csf_log(error
			, "start %s failed!"
			, slave->to_string().c_str()
		);
	}
#endif


	//tmp_child.wait_until()
	//slave->set_child(tmp_child);
	//boost::process::child  tmp_ch = tmp_child;

	return csf_true;

#endif

}


/**
 * 功能：
 *    停止指定的私服程序
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_common_vm::stop_slave(csf_slave* slave) {

	csf_int32			tmp_int_return = csf_failure;


	if (csf_nullptr == slave) {
		return csf_false;
	}
	csf_common_slave	*tmp_common_slave = (csf_common_slave*)slave;


	//初始化伺服对象
	tmp_int_return = tmp_common_slave->stop();
	if (csf_failure == tmp_int_return) {
		csf_log(error
			, "stop slave failed! %s"
			, tmp_common_slave->to_string().c_str()
		);
		return csf_false;
	}
	else {
		csf_log(notice
			, "stop slave succeed! %s"
			, tmp_common_slave->to_string().c_str()
		);
	}

#if 0
	if (csf_nullptr == slave || !slave->get_pid()) {
		return csf_false;
	}

	boost::process::pid_t	tmp_pid = slave->get_pid();
	std::error_code			tmp_ec;
	boost::process::child	tmp_child(tmp_pid);

	if (!tmp_child.running(tmp_ec)) {

		csf_log(notice
			, "slave isn't running. %s"
			, slave->to_string().c_str()
		);
	}
	else {

		//停止指定进程
		tmp_child.terminate(tmp_ec);

		csf_log(notice
			, "slave stoped succeed. %s"
			, slave->to_string().c_str()
		);
	}
#endif

	return csf_true;
}


/**
 * 功能：
 *    插入指定的私服信息
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_common_vm::insert_slave(csf_slave* slave) {

	return csf_vm::insert_slave(slave);
}


/**
 * 功能：
 *    该函数主要用于启动信号处理
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_vm::start_signals_process() {


	// Construct a signal set registered for process termination.
	get_signals().add(SIGSEGV);
	get_signals().add(SIGINT);
	get_signals().add(SIGTERM);
	get_signals().add(SIGABRT);
#ifdef __linux__

	get_signals().add(SIGQUIT);
	get_signals().add(SIGILL);
	get_signals().add(SIGTRAP);
	//get_signals().add(SIGKILL);
	get_signals().add(SIGIOT);
	get_signals().add(SIGBUS);
	get_signals().add(SIGFPE);
	get_signals().add(SIGCHLD);

#endif

	// Start an asynchronous wait for one of the signals to occur.
	//get_signals().async_wait(boost::bind(&csf_common_vm::signal_handler, this, boost::placeholders::_1, boost::placeholders::_2));

	csf_log_ex(notice
		, csf_log_code_notice
		, "signal process succeed!"
	);

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于停止信号处理
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_vm::stop_signals_process() {

	get_signals().cancel();

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于处理子进程队列
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_void csf_common_vm::deamon_thread_process() {

	csf_slave			*tmp_common_slave = csf_nullptr;


	if (get_deque().size() <= 0) {
		//如果没有视频，则休眠等待
		//csf::core::utils::time::sleep_time::sleep_s(1);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else {
		if (get_deque().pop_front(tmp_common_slave)) {
			if (tmp_common_slave) {
				//针对对象进行守护处理
				deamon_slave(tmp_common_slave);
			}
		}
	}
}


/**
 * 功能：
 *    该函数主要用于启动守护处理线程池
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_vm::start_deamon_thread_pool() {

	//在线程组中运行2个线程，用于处理子进程的守护
	get_deamon_thread_pool().start(2, csf_bind(&csf_common_vm::deamon_thread_process, this));

	csf_log(notice
		, "start deamon thread pool[%d] succeed!"
		, get_deamon_thread_pool().get_thread_number());

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于停止守护处理线程池
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_vm::stop_deamon_thread_pool() {

	get_deamon_thread_pool().stop();

	csf_log(notice
		, "stop deamon thread pool[%d] succeed!"
		, get_deamon_thread_pool().get_thread_number());

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于启动处理子进程退出信号的线程池
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_vm::start_io_context_thread_pool() {

	//在线程组中运行2个线程，用于处理子进程退出信号
	get_io_context_thread_pool().start(2, csf_bind(&csf_common_vm::io_context_thread_process, this));

	csf_log(notice
		, "start io_context thread pool[%d] succeed!"
		, get_io_context_thread_pool().get_thread_number());

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于停止处理子进程退出信号的线程池
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_bool csf_common_vm::stop_io_context_thread_pool() {

	get_io_context_thread_pool().stop();

	csf_log(notice
		, "stop io_context thread pool[%d] succeed!"
		, get_io_context_thread_pool().get_thread_number());

	return csf_true;
}


/**
 * 功能：
 *    该函数主要用于处理子进程退出信号队列
 * 返回：
 *    true  :  表示成功；
 *    false :  表示失败。
 */
csf_void csf_common_vm::io_context_thread_process() {

	//重置io_context状态
	get_ioctx().reset();
	//添加信号处理事件
	get_signals().async_wait(boost::bind(&csf_common_vm::signal_handler, this, boost::placeholders::_1, boost::placeholders::_2));
	//启动服务
	get_ioctx().run();

	//start_signals_process();
}


/**
 * 功能：
 *    该函数主要用于初始化vm的名称
 * 返回：
 *    true  :  表示初始化成功；
 *    false :  表示初始化失败。
 */
csf_bool csf_common_vm::init_vm_name() {


	csf_string							tmp_string_ret = "";


	get_attribute_manager().add("name"
		, csf_attribute_string(csf_list<csf_string>({ "vm_configure", "name" })
			, csf_attribute_exception_critical()));

	//获取当前配置的工作目录地址
	tmp_string_ret = get_attribute_manager().get_value<csf_attribute_string>("name");
	if (!tmp_string_ret.empty()) {
		set_name(tmp_string_ret);
		csf_log(notice, "set vm[name:%s] succeed!", tmp_string_ret.c_str());
		return csf_true;
	}
	else {
		set_name("");
		csf_log(error, "set vm failed! not found name in configure files!");
	}

	return csf_false;
}