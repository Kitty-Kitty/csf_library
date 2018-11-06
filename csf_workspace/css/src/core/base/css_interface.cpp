/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_interface.hpp
*
*Version: 1.0
*
*Date: 07-10ÔÂ-2018 16:50:29
*
*Description: Class(css_interface)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_interface.hpp"

using css::core::css_interface;


css_interface::css_interface()
	: m_tcp_port(0)
	, m_udp_port(0)
	, m_used(csf_false)
	, m_tcp_update_port(0) {

}



css_interface::~css_interface() {

}