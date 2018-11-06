/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_exception.hpp
*
*Version: 1.0
*
*Date: 07-10ÔÂ-2018 16:50:27
*
*Description: Class(css_exception)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_exception.hpp"

using css::core::css_exception;


css_exception::css_exception()
	: m_status(css_status_none)
	, m_private_status(css_status_none)
	, m_channel_id(0)
	, m_time(0)
	, m_send_time(0)
	, m_description("")
	, m_play_session("")
	, m_media_id("")
	, m_session("") {

}



css_exception::~css_exception() {

}