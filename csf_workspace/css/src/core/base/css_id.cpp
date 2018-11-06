/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_id.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:28
*
*Description: Class(css_id)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_id.hpp"

using css::core::css_id;


css_id::css_id()
	: m_value("")
	, m_guid("") {

}



css_id::~css_id() {

}





/**
 * ����id��
 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
 * 
 * @param id    ��ʾ��Ҫ��������id
 */
csf_bool css_id::parse(const csf_string& id) {

	return csf_true;
}


/**
 * ����id��
 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
 * 
 * @param id    ��ʾ��Ҫ��������id
 */
csf_bool css_id::parse(const csf_char* id) {

	return csf_true;
}


/**
 * ��ʾ����css_id
 * 
 * @param parameters    ��ʾʵ�ʵ�id�����б�
 * @param guid    ��ʾid��guid����
 */
csf_bool css_id::make(const csf_vertor<csf_int32>& parameters, csf_string& guid) {

	return csf_true;
}


/**
 * ��ʾ����css_id
 * 
 * @param parameters    ��ʾʵ�ʵ�id�����б�
 * @param guid    ��ʾid��guid����
 */
csf_bool css_id::make(const csf_vertor<csf_int32>& parameters, csf_char* guid) {

	return csf_true;
}


/**
 * ��ʾ����css_id
 * 
 * @param parameters    ��ʾʵ�ʵ�id�����б�
 */
csf_bool css_id::make(const csf_vertor<csf_int32>& parameters) {

	return csf_true;
}


/**
 * ����id��
 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
 * 
 * @param id    ��ʾ��Ҫ��������id
 */
css_id& css_id::operator =(const csf_char* id) {

	return  csf_nullptr;
}


/**
 * ����id��
 * ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
 * 
 * @param id    ��ʾ��Ҫ��������id
 */
css_id& css_id::operator =(const csf_string& id) {

	return  csf_nullptr;
}