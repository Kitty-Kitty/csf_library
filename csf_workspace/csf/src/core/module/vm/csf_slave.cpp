/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_slave.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_slave)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_default.h"
#include "csf_slave.hpp"

using csf::core::module::csf_slave;


csf_slave::csf_slave()
	: m_name{0, }
	, m_pid(0)
	, m_app(csf_nullptr)
	, m_command{0, }
	, m_arguments{0, } {

}



csf_slave::~csf_slave() {

}


/**
 * 功能：
 *    伺服进程初始化，进行启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 */
csf::core::base::csf_int32 csf_slave::init() {

	return csf_succeed;
}


/**
 * 功能：
 *    伺服启动，进行伺服启动工作。表示伺服已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 */
csf::core::base::csf_int32 csf_slave::start() {

	return csf_succeed;
}


/**
 * 功能：
 *    伺服停止，进行伺服停止工作。释放伺服初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 */
csf::core::base::csf_int32 csf_slave::stop() {

	return csf_succeed;
}


/**
 * 功能：
 *    将slave信息转换为字符串
 * 返回：
 *    slave信息字符串
 */
csf_string csf_slave::to_string() {

	csf_char				tmp_buf[3072] = { 0, };


	csf_snprintf(tmp_buf
		, csf_sizeof(tmp_buf)
		, "slave[ app:%p  |  pid:%d  |  name:%s  | command:%s  |  arguments:%s ]"
		, get_app()
		, get_pid()
		, get_name().c_str()
		, get_command().c_str()
		, get_arguments().c_str()
	);

	return csf_string(tmp_buf);
}


/**
 * 功能：
 *    查询当前伺服进程是否正在运行。
 * 返回：
 *    true  ： 表示正在运行；
 *    false ： 表示不在运行
 */
csf_bool csf_slave::is_running() {

	return csf_true;
}

/**
* 功能：
*    表示当前是否需要父进程守护处理（如果返回true，则父进程会重新启动该进程）
* 返回：
*    true  ：  表示需要父进程进行守护处理（重新启动）
*    false ：  表示不需要守护处理
*/
csf_bool csf_slave::is_deamon() {

	return csf_false;
}