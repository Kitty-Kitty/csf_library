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
*Date: 07-10月-2018 16:50:28
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
 * 解析id。
 * 返回：true表示成功；false表示失败。
 * 
 * @param id    表示需要被解析的id
 */
csf_bool css_id::parse(const csf_string& id) {

	return csf_true;
}


/**
 * 解析id。
 * 返回：true表示成功；false表示失败。
 * 
 * @param id    表示需要被解析的id
 */
csf_bool css_id::parse(const csf_char* id) {

	return csf_true;
}


/**
 * 表示创建css_id
 * 
 * @param parameters    表示实际的id参数列表
 * @param guid    表示id的guid数据
 */
csf_bool css_id::make(const csf_vertor<csf_int32>& parameters, csf_string& guid) {

	return csf_true;
}


/**
 * 表示创建css_id
 * 
 * @param parameters    表示实际的id参数列表
 * @param guid    表示id的guid数据
 */
csf_bool css_id::make(const csf_vertor<csf_int32>& parameters, csf_char* guid) {

	return csf_true;
}


/**
 * 表示创建css_id
 * 
 * @param parameters    表示实际的id参数列表
 */
csf_bool css_id::make(const csf_vertor<csf_int32>& parameters) {

	return csf_true;
}


/**
 * 解析id。
 * 返回：true表示成功；false表示失败。
 * 
 * @param id    表示需要被解析的id
 */
css_id& css_id::operator =(const csf_char* id) {

	return  csf_nullptr;
}


/**
 * 解析id。
 * 返回：true表示成功；false表示失败。
 * 
 * @param id    表示需要被解析的id
 */
css_id& css_id::operator =(const csf_string& id) {

	return  csf_nullptr;
}