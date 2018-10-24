/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_serial_url.hpp
*
*Version: 1.0
*
*Date: 01-10ÔÂ-2018 12:54:52
*
*Description: Class(csf_serial_url)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_serial_url.hpp"

using csf::modules::connect::csf_serial_url;


csf_serial_url::csf_serial_url()
	: m_baud_rate(0)
	, m_character_size(0)
	, m_flow_control(csf_serial_flow_control_type_none)
	, m_dev("")
	, m_parity(csf_serial_parity_type_none)
	, m_stop_bits(csf_serial_stop_bits_type_none)
	, m_port(0) {

}



csf_serial_url::~csf_serial_url() {

}