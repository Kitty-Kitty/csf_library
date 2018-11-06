/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_semh_request.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:31
*
*Description: Class(css_semh_request)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_semh_request.hpp"

using css::core::css_semh_request;


css_semh_request::css_semh_request()
	: m_semh(csf_null)
	, m_gmf(csf_null) {

}



css_semh_request::~css_semh_request() {

}





/**
 * ��ʾsemh�ṹ������
 */
gmp_gmph_semh_t* css_semh_request::get_semh() {

	return m_semh;
}


/**
 * ��ʾsemh�ṹ������
 * 
 * @param newVal
 */
void css_semh_request::set_semh(gmp_gmph_semh_t* newVal) {

	m_semh = newVal;
}


/**
 * ��ʾgmf�ṹ������
 */
gmp_gmf_t* css_semh_request::get_gmf() {

	return m_gmf;
}


/**
 * ��ʾgmf�ṹ������
 * 
 * @param newVal
 */
void css_semh_request::set_gmf(gmp_gmf_t* newVal) {

	m_gmf = newVal;
}