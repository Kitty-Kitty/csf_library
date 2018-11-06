/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: css_update.hpp
*
*Version: 1.0
*
*Date: 07-10ÔÂ-2018 16:50:32
*
*Description: Class(css_update)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_update.hpp"

using css::core::css_update;


css_update::css_update()
	: m_device_type(css_device_type_none)
	, m_packet_type(css_packet_type_none)
	, m_file_data(csf_null)
	, m_is_update_conf_file(csf_false)
	, m_is_update_data_file(csf_false)
	, m_version(0)
	, m_version_addtion(0)
	, m_time(0)
	, m_device_id("")
	, m_packet_name("")
	, m_serial_master("")
	, m_serial_slave("")
	, m_platform_hardware("")
	, m_platform_software("")
	, m_change_log("") {

}



css_update::~css_update() {

}