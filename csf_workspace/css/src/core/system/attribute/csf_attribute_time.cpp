/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_time.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:55:12
*
*Description: Class(csf_attribute_time)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_time.hpp"
#include "csf_attribute_printf.h"

using csf::core::system::attribute::csf_attribute_time;



/**
* 表示时间单位名称定义
*/
const csf_unordered_map<csf_string, csf_attribute_time::csf_time_unit> csf_attribute_time::m_unit_name = {
	{ "none", csf_time_unit_none},
	{ "ns", csf_time_unit_ns},
	{ "us", csf_time_unit_us},
	{ "ms", csf_time_unit_ms},
	{ "s", csf_time_unit_s},
	{ "m", csf_time_unit_m},
	{ "h", csf_time_unit_h},
	{ "d", csf_time_unit_d}
};

/**
* 表示该种格式数据的说明
*/
const csf_string csf_attribute_time::m_usage = "usage: number unit(ns|us|ms|s|m|h|d) . for example: 10s";

/**
* 从内容中解析需要的参数。
* 返回：ture表示解析成功；false表示解析失败。
*
* @param content    表示需要解析的内容信息
*/
csf_bool csf_attribute_time::parse_parametes(const csf_string& content) {

	/**
	* 表示核验格式和截取字符串正则表达式
	*/
	std::regex					tmp_regex("(\\d+)(ns|us|ms|s|m|h|d)");
	std::smatch					tmp_match_result;
	

	if (content.empty()) {
		return csf_false;
	}

	//使用正则表达式核验数据结构和提取参数
	if (!std::regex_match(content, tmp_match_result, tmp_regex)) {
		//正则表达式匹配失败，表示数据格式错误
		csf_attribute_log(warning, csf_log_code_warning
			, "content format error. %s"
			, get_usage().c_str());
		return csf_false;
	}
	else {
		//如果match提取的参数小于等于需要的参数个数，则表示错误
		if (tmp_match_result.size() <= csf_attribute_time_parametes_size) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. parametes number[%d <= %d]. %s"
				, tmp_match_result.size()
				, csf_attribute_time_parametes_size
				, get_usage().c_str());
			return csf_false;
		}

		//获取"100s"格式数据中的"100","s"两个字符段。
		//其中tmp_match_result[1]的1就是"100"数值内容；
		//其中tmp_match_result[2]的2就是"s"的单位内容；
		if (!get_parametes(tmp_match_result[1].str(), tmp_match_result[2].str())) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. get parametes failed. %s"
				, get_usage().c_str());
			return csf_false;
		}
	}
	return csf_true;
}



/**
* 表示处理csf_attribute属性操作。
* 返回：true表示失败；false表示成功。
*
* @param configure_manager    表示保存配置管理器对象
* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
*/
csf_bool csf_attribute_time::process_number(const csf_configure_manager& configure_manager, const csf_string& alias) {
	
	csf_string					tmp_content = "";
	
	
	//调用基础库的初始化函数获取内容数值，主要是获取content数值
	if (csf_false == csf_attribute::init(configure_manager, alias)) {
		return csf_false;
	}

	//删除内容中的所有空白字符
	tmp_content = shrink(get_content());
	if (tmp_content.empty()) {
		csf_attribute_log(warning, csf_log_code_warning,
			"content is null.");
		return csf_false;
	}

	//解析从配置文件中读取的属性数据
	if (csf_false == parse_parametes(tmp_content)) {
		return csf_false;
	}

	return csf_true;
}


/**
* 获取数值和单位相关内容。
* 返回：true表示处理成功；false表示处理失败。
*
* @param val    表示需要处理的数值内容
* @param unit    表示该数值的单位字符
*/
csf_bool csf_attribute_time::get_parametes(const csf_string& val, const csf_string& unit) {

	csf_int64									tmp_value = 0;
	csf_int64									tmp_dest = 0;
	csf_attribute_time::csf_time_unit			tmp_unit = csf_attribute_time::csf_time_unit::csf_time_unit_none;


	//核验数据的合法性。如果参数数值为空，则返回错误
	if (val.empty() || unit.empty()) {
		csf_attribute_log(warning, csf_log_code_warning,
			"value[%s] or unit[%s] is null.",
			val.c_str(),
			unit.c_str());
		return csf_false;
	}

	//将字符串的时间单位格式转换为数字类型单位
	tmp_unit = convert(unit);
	if (csf_attribute_time::csf_time_unit::csf_time_unit_none == tmp_unit) {
		csf_attribute_log(warning, csf_log_code_warning,
			"unit[%s] unknow.",
			unit.c_str());
		return csf_false;
	}
	
	//将字符串数字转换为int64格式的数值
	tmp_value = csf_atoint64(val.c_str());
	if (tmp_value < 0) {
		csf_attribute_log(warning, csf_log_code_warning,
			"value[%s] convert failed.",
			val.c_str());
		return csf_false;
	}

	//将源时间单位数据转换为目标单位时间数据
	if (csf_false == convert(tmp_dest, get_unit(), tmp_value, tmp_unit)) {
		csf_attribute_log(warning, csf_log_code_warning,
			"convert time format failed.");
		return csf_false;
	}
	else {
		//如果转换成功则保存数据
		set_value(tmp_dest);
	}

	return csf_true;
}