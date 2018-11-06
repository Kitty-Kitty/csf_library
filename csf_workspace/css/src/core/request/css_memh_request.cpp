/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_memh_request.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:29
*
*Description: Class(css_memh_request)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_memh_request.hpp"

using css::core::css_memh_request;


css_memh_request::css_memh_request()
	: m_memh(csf_null) {

}



css_memh_request::~css_memh_request() {

}





/**
 * ��ʾmemh�ṹ������
 */
gmp_gmph_memh_t* css_memh_request::get_memh() {

	return m_memh;
}


/**
 * ��ʾmemh�ṹ������
 * 
 * @param newVal
 */
void css_memh_request::set_memh(gmp_gmph_memh_t* newVal) {

	m_memh = newVal;
}