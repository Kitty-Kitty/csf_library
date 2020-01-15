/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:26
*
*Description: Class(csf_attribute)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute.hpp"
#include "csf_element.hpp"
#include "csf_attribute_printf.h"


using csf::core::system::attribute::csf_attribute;




/**
* 表示初始化csf_attribute。
* 返回：true表示失败；false表示成功。
*
* @param configure_manager    表示保存配置管理器对象
* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
*/
csf_bool csf_attribute::init(const csf_configure_manager& configure_manager, const csf_string& alias) {

	return csf_true;
	//return process(configure_manager, alias);
}


/**
* 表示从配置管理器中获取配置项内容。
* 返回：true表示获取到指定配置项数值；false表示没有获取到配置项数值。
*
* @param configure_manager    表示保存配置管理器对象
* @param items    表示配置项的路径信息
*/
csf_bool csf_attribute::get_configure(csf_configure_manager& configure_manager, csf_list<csf_string>& items) {

	csf_element					*tmp_element = csf_nullptr;


	//从配置管理器查找符合路径的属性数值，并判断数值是否为空
	//数据不存在或为空都返回错误
	tmp_element = (csf_element*)&(configure_manager.find_element(items));
	if (tmp_element->is_null()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"not found element.");
		return csf_false;
	}

	if (tmp_element->get_content().empty()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"element content is null.");
		//return csf_false;
	}
	else {
		set_content(tmp_element->get_content());
	}

	return csf_true;
}


/**
* 表示从配置管理器中获取配置项内容。
* 返回：true表示获取到指定配置项数值；false表示没有获取到配置项数值。
*
* @param configure_manager    表示保存配置管理器对象
*/
csf_bool csf_attribute::get_configure(csf_configure_manager& configure_manager) {

	//判断items是否为空，如果为空，则采用名称作为items项
	if (get_items().empty()) {
		if (get_name().empty()) {
			csf_attribute_log(warning, csf_logger_level_warning,
				"items and name is null.");
			return csf_false;
		}
		else {
			get_items().push_back(get_name());
		}
	}

	//根据items获取配置项字符数值
	return get_configure(configure_manager, get_items());
}


/**
* 表示从配置管理器中获取配置项内容。
* 返回：true表示获取到指定配置项数值；false表示没有获取到配置项数值。
*
* @param element    表示保存配置的属性对象
* @param items    表示配置项的路径信息
*/
csf_bool csf_attribute::get_configure(csf_element& element, csf_list<csf_string>& items) {

	csf_element				*tmp_element = csf_nullptr;


	if (element.is_null() || items.empty()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"element or items is null.");
		return csf_false;
	}

	//循环遍历所有列表，查找符合路径需求的节点
	tmp_element = (csf_element*)&(element.find_element(items));
	if (tmp_element->is_null()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"not found element.");
		return csf_false;
	}

	if (tmp_element->get_content().empty()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"element content is null.");
		//return csf_false;
	}
	else {
		set_content(tmp_element->get_content());
	}

	return csf_true;
}