/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7月-2018 19:29:31
*
*Description: Class(csf_attribute_manager)表示模块的属性管理器，主要提供模块配置属性统一管理，包括增、删、查、改等。
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_manager.hpp"


using csf::core::system::attribute::csf_attribute_manager;


/**
* 函数功能为：根据名称从attribute_manager中删除一个属性。
* 返回：true表示删除成功（不存在该名称属性默认返回成功）；false表示失败。
*
* @param name    表示需要删除的属性名称
*/
csf_bool csf_attribute_manager::del(const csf_char* name) {

	csf_unordered_map<csf_string, csf_attribute*>::iterator		tmp_iter;

	//核验名称数据的合法性
	if (!name || csf_strlen(name) <= 0) {
		return csf_false;
	}

	//查询该名称属性是否已经存在，如果已经存在则返回失败
	tmp_iter = get_attributes().find(name);
	if (tmp_iter != get_attributes().end()) {

		//销毁对象，释放资源
		if (tmp_iter->second) {
			delete (tmp_iter->second);
		}
		get_attributes().erase(tmp_iter);
	}

	return csf_true;
}


/**
* 函数功能为：根据名称从attribute_manager中查询一个属性。
* 返回：一个属性对象。
*
* @param name    表示需要的属性名称
*/
const csf_attribute& csf_attribute_manager::find(const csf_char* name) {

	csf_unordered_map<csf_string, csf_attribute*>::iterator		tmp_iter;

	//核验名称数据的合法性
	if (!name || csf_strlen(name) <= 0) {
		return csf_attribute::get_null();
	}

	//查询该名称属性是否已经存在，如果已经存在则返回失败
	tmp_iter = get_attributes().find(name);
	if (tmp_iter != get_attributes().end()) {
		if (tmp_iter->second) {
			return *(tmp_iter->second);
		}
	}

	return csf_attribute::get_null();
}

/**
* 函数功能为：根据名称从attribute_manager中查询一个属性并返回属性内容。
* 返回：字符串内容。
*
* @param name    表示需要的属性名称
*/
csf_string csf_attribute_manager::get_content(const csf_char* name) {

	csf_attribute			&attr = (csf_attribute &)find(name);


	if (attr.not_null()) {
		return attr.get_content();
	}

	return csf_string_null;
}
