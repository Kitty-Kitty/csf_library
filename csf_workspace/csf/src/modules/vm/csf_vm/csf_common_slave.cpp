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

#include "csf_logger.hpp"
#include "csf_common_slave.hpp"

using csf::modules::vm::csf_common_slave;


csf_common_slave::csf_common_slave() {

}



csf_common_slave::~csf_common_slave() {

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
 *    表示进程退出时调用的函数
 * 返回：
 *    无
 * 
 * @param ec    表示错误码
 * @param rc    表示进程退出后的返回码
 */
void csf_common_slave::exit_handler(boost::system::error_code ec, int rc) {
	csf_log(warning
		, "process exit warning. return[%d] error_code[%d] : %s . %s"
		, rc
		, ec.value()
		, boost::system::system_error(ec).what()
		, to_string().c_str()
	);
}