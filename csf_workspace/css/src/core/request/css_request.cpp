/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_request.hpp
*
*Version: 1.0
*
*Date: 07-10ÔÂ-2018 16:50:30
*
*Description: Class(css_request)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_request.hpp"

using css::core::css_request;


css_request::css_request()
	: m_description("")
	, m_type(css_request_type_none)
	, m_status(css_request_status_none) {

}



css_request::~css_request() {

}