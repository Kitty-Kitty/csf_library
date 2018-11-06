/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_host.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:28
*
*Description: Class(css_host)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_host.hpp"

using css::core::css_host;


css_host::css_host()
	: m_type(css_device_type_none)
	, m_subtype(css_device_subtype_none)
	, m_name[128]({0, })
	, m_version[128]({0, })
	, m_status(css_device_status_none)
	, m_heartbeat_times(0)
	, m_heartbeat_interval(0) {

}



css_host::~css_host() {

}





/**
 * ��ʾ�豸id��Ϣ
 */
css::core::css_id css_host::get_id() {

	return m_id;
}


/**
 * ��ʾ�豸id��Ϣ
 * 
 * @param newVal
 */
void css_host::set_id(css::core::css_id newVal) {

	m_id = newVal;
}