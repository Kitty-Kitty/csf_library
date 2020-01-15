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