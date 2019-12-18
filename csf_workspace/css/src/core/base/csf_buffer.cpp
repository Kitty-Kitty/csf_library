/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_buffer.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6ÔÂ-2018 21:50:41
*
*Description: Class(csf_buffer)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_buffer.hpp"

using csf::core::base::csf_buffer;


csf_buffer::csf_buffer()
	: m_start(csf_null)
	, m_end(csf_null)
	, m_pos(csf_null)
	, m_last(csf_null) {

}



csf_buffer::~csf_buffer() {

}