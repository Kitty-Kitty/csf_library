/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_common_slave.hpp
*
*Version: 1.0
*
*Date: 15-1月-2020 18:46:53
*
*Description: Class(csf_common_slave)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_default.h"
#include "csf_logger.hpp"
#include "csf_common_slave.hpp"

using csf::modules::vm::csf_common_slave;


csf_common_slave::csf_common_slave()
	: m_signal(0) {

}



csf_common_slave::~csf_common_slave() {
	stop();
}


/**
 * 功能：
 *    伺服进程初始化，进行启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 */
csf::core::base::csf_int32 csf_common_slave::init() {

	set_signal(0);

	return csf_slave::init();
}


/**
 * 功能：
 *    伺服启动，进行伺服启动工作。表示伺服已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 */
csf::core::base::csf_int32 csf_common_slave::start() {

	set_signal(0);

	if (is_running()) {
		return csf_succeed;
	}

	csf_char		tmp_exe_buf[3072] = { 0, };

	csf_snprintf(tmp_exe_buf
		, csf_sizeof(tmp_exe_buf)
		, "%s %s --name=%s --vm_pid=%d --vm_instance=0x%p "
		, get_command().c_str()
		, get_arguments().c_str()
		, get_name().c_str()
		, get_common_vm()->get_vm_pid()
		, this
	);

	set_child(new boost::process::child(
		csf_string(tmp_exe_buf),
		//boost::process::std_in.close(),
		//boost::process::std_err.close(),
		//boost::process::std_out.close(),
		get_common_vm()->get_ioctx(),
		boost::process::on_exit(boost::bind(&csf_common_slave::exit_handler, this, boost::placeholders::_1, boost::placeholders::_2))
	));
	
	if (is_running()) {
		set_pid(get_child()->id());

		csf_log(notice
			, "start slave[%s : %d] succeed! %s"
			, get_name().c_str()
			, get_pid()
			, to_string().c_str()
		);
	}
	else {
		csf_log(error
			, "start slave[%s : %d] failed! %s"
			, get_name().c_str()
			, get_pid()
			, to_string().c_str()
		);
		destroy_child();
	}

#if 0
	boost::process::async_system(get_common_vm()->get_ioctx()
		, boost::bind(&csf_common_slave::exit_handler, this, boost::placeholders::_1, boost::placeholders::_2)
		, csf_string(tmp_exe_buf)
	);
#endif

	return csf_succeed;
}


/**
 * 功能：
 *    伺服停止，进行伺服停止工作。释放伺服初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 */
csf::core::base::csf_int32 csf_common_slave::stop() {

	csf_bool				tmp_boot_return = csf_true;


	tmp_boot_return = is_running();
	if (csf_false == tmp_boot_return) {
		//表示进程当前不在运行
		csf_log(notice
			, "slave[pid:%d | name:%s] isn't running. %s"
			, get_pid()
			, get_name().c_str()
			, to_string().c_str()
		);
		set_signal(0);
		return csf_succeed;
	}

	if (get_child()) {
		std::error_code			tmp_ec;

		//如果指定pid进程在运行，则停止处理
		get_child()->terminate(tmp_ec);
		if (!tmp_ec) {
			//表示当前进程停止成功
			csf_log(notice
				, "slave[pid:%d | name:%s] terminate succeed. %s"
				, get_pid()
				, get_name().c_str()
				, to_string().c_str()
			);
			set_signal(0);
			//return csf_succeed;
		}
		else {
			//表示当前进程停止失败
			csf_log(error
				, "slave[pid:%d | name:%s] terminate faild. error_code[%d : %s]. %s"
				, get_pid()
				, get_name().c_str()
				, tmp_ec.value()
				, tmp_ec.message().c_str()
				, to_string().c_str()
			);
			//return csf_failure;
		}
		destroy_child();
	}

	return csf_succeed;
}


/**
 * 功能：
 *    将slave信息转换为字符串
 * 返回：
 *    slave信息字符串
 */
csf_string csf_common_slave::to_string() {

	return csf_slave::to_string();
}


/**
 * 功能：
 *    查询当前伺服进程是否正在运行。
 * 返回：
 *    true  ： 表示正在运行；
 *    false ： 表示不在运行
 */
csf_bool csf_common_slave::is_running() {

	if (csf_nullptr == get_child()) {
		return csf_false;
	}
	
	if (get_child()->running()) {
		return csf_true;
	}
	else {
		return csf_false;
	}

	return csf_false;
}


/**
* 功能：
*    表示当前是否需要父进程守护处理（如果返回true，则父进程会重新启动该进程）
* 返回：
*    true  ：  表示需要父进程进行守护处理（重新启动）
*    false ：  表示不需要守护处理
*/
csf_bool csf_common_slave::is_deamon() {

	if (is_running()) {
		return csf_false;
	}

#ifdef __linux__
	//如果程序由于段错误
	switch (get_signal())
	{
	case SIGILL:			//4  /* Illegal instruction (ANSI).  */  建立CORE文件，非法指令
	case SIGTRAP:			//5  /* Trace trap (POSIX).  */          建立CORE文件, 跟踪自陷
	case SIGIOT:			//6  /* IOT trap (4.2 BSD).  */          建立CORE文件,执行I/O自陷
	case SIGBUS:			//7  /* BUS error (4.2 BSD).  */         建立CORE文件,总线错误
	case SIGFPE:			//8  /* Floating-point exception (ANSI).  */   建立CORE文件,浮点异常
	case SIGSEGV:			//11 /* Segmentation violation (ANSI).  */     建立CORE文件,段非法错误
	{
		return csf_true;
	}
	break;
	default:
	{
		return csf_false;
	}
	break;
	}
#else
	return csf_true;
#endif

	return csf_false;
}


/**
 * 功能：
 *    表示进程退出时调用的函数
 * 返回：
 *    无
 *
 * @param signal    表示进程退出时接收到信号类型
 * @param ec    表示错误码
 */
void csf_common_slave::exit_handler(int signal, const std::error_code& ec) {

	//保存伺服进程接收到的信号
	set_signal(signal);

	//将程序退出添加到vm的处理队列中
	if (get_common_vm()) {
		get_common_vm()->add_exit_slave(this);
	}
	destroy_child();

#ifdef __linux__
	csf_log(warning
		, "process exit warning. signal[%d : %s] error_code[%d : %s] . %s"
		, signal
		, strsignal(signal)
		, ec.value()
		, ec.message().c_str()
		, to_string().c_str()
	);
#else
	csf_log(warning
		, "process exit warning. signal[%d] error_code[%d : %s] . %s"
		, signal
		, ec.value()
		, ec.message().c_str()
		, to_string().c_str()
	);
#endif
}


/**
 * 表示销毁已经创建的child对象
 */
csf_void csf_common_slave::destroy_child() {

	if (get_child()) {
		//get_child()->terminate();
		//get_child()->wait();
		get_child()->exit_code();
		delete get_child();
		set_child(csf_nullptr);
	}
}