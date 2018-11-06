/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_information.hpp
*
*Version: 1.0
*
*Date: 07-10ÔÂ-2018 16:50:28
*
*Description: Class(css_information)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_information.hpp"

using css::core::css_information;


css_information::css_information()
	: m_limit_disk(0)
	, m_limit_memory(0)
	, m_limit_cpu(0)
	, m_limit_bandwidth(0)
	, m_limit_connect(0)
	, m_current_disk(0)
	, m_current_memory(0)
	, m_current_cpu(0)
	, m_current_bandwidth(0)
	, m_current_connect(0) {

}



css_information::~css_information() {

}