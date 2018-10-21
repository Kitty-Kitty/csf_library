/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_connect_timeout.hpp
*
*Version: 1.0
*
*Date: 21-10月-2018 13:54:44
*
*Description: Class(csf_connect_timeout)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_connect_timeout.hpp"

using csf::core::module::connect::csf_connect_timeout;


csf_connect_timeout::csf_connect_timeout()
	: m_time(0)
	, m_handle(csf_nullptr) {

}



csf_connect_timeout::~csf_connect_timeout() {

}





/**
 * 
 * @param time    表示当前超时的时间数值，单位为毫秒（ms）
 * 
 * @param handle    表示超时后的回调函数
 */
csf_connect_timeout::csf_connect_timeout(const csf_uint32 time
	, const csf::core::module::connect::csf_connect_callback handle)
	: m_time(time)
	, m_handle(handle) {

}