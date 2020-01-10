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


