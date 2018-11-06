/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_media_source.hpp
*
*Version: 1.0
*
*Date: 07-10ÔÂ-2018 16:50:29
*
*Description: Class(css_media_source)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_media_source.hpp"

using css::core::css_media_source;


css_media_source::css_media_source()
	: m_type(css_media_source_type_none)
	, m_subtype(css_media_source_subtype_none)
	, m_id("")
	, m_name("")
	, m_url("")
	, m_description("")
	, m_decode_url("")
	, m_parent("") {

}



css_media_source::~css_media_source() {

}