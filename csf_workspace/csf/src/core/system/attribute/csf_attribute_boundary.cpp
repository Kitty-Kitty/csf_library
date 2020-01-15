/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_boundary.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 04-7月-2018 22:13:15
*
*Description: Class(csf_attribute_boundary)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_attribute_boundary.hpp"

using csf::core::system::attribute::csf_attribute_boundary;



/**
* 表示配置各个符号代表及对应的操作符
* @author fz
* @version 1.0
* @created 04-7月-2018 22:13:15
*/
std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>> _functions = {
	//处理“()”的两边不等情况，例如:(-n, 100)
	{ "()", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower < val && val < upper) {
				return csf_true;
			}
			return csf_false;
		}
	},
	//处理“[)”情况，例如:[0, 100)
	{ "[)", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower <= val && val < upper) {
				return csf_true;
			}
			return csf_false;
		}
	},
	//处理“(]”情况，例如:(0, 100]
	{ "(]", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower < val && val <= upper) {
				return csf_true;
			}
			return csf_false;
		}
	},
	//处理“[]”情况，例如:[0, 100]
	{ "[]", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower <= val && val <= upper) {
				return csf_true;
			}
			return csf_false;
		}
	}
};

const std::map < std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>> csf_attribute_boundary::m_functions = _functions;

/**
* 表示boundary的使用说明
* @author fz
* @version 1.0
* @created 04-7月-2018 22:13:15
*/
const csf_string csf_attribute_boundary::m_usage = "usage: (lower_boundary, upper_boundary] . for example: (0, 100] or (-n, 100]";

/**
* 表示根据限制字符串创建校验对象。
* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
*
* @param boundary    其中字符串描述的限制表示。
* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
*/
csf_bool csf_attribute_boundary::parse(const csf_char* boundary) {

	csf_char					tmp_buf[csf_boundary_string_default_length] = { 0, };
	csf_char					*tmp_pos = (csf_char*)boundary;
	csf_char					*tmp_dest = tmp_buf;
	std::unordered_set<csf_char>::iterator			tmp_iter;


	if (!boundary || csf_strlen(boundary) <= 0 ||
		csf_strlen(boundary) > csf_boundary_string_default_length) {
		return csf_false;
	}

	//处理无法识别的字符，保留可识别的字符
	while (*tmp_pos != '\0') {
		if (!csf_char_no_space(*tmp_pos)) {
			++tmp_pos;
			continue;
		}
		*tmp_dest++ = *tmp_pos++;
	}

	//判断数据长度为0，表示没有可能的合法字符串，则直接返回错误
	if (csf_strlen(tmp_buf) <= 0) {
		return csf_false;
	}

	//处理阈值限制字符内容
	return parse_parametes(tmp_buf);
}

/**
* 表示根据限制字符串创建校验对象。
* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
* 返回：true表示成功；false表示失败。
*
* @param boundary    其中字符串描述的限制表示。
* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
*
*/
csf_bool csf_attribute_boundary::parse_parametes(const csf_string boundary) {

	/**
	* 表示核验格式和截取字符串正则表达式
	*/
	std::regex					tmp_regex("(\\(|\\[)(-n|\\d+),(n|\\+n|\\d+)(\\)|\\])");
	std::smatch					tmp_match_result;


	//使用正则表达式核验数据结构和提取参数
	if (!std::regex_match(boundary, tmp_match_result, tmp_regex)) {
		//正则表达式匹配失败，表示数据格式错误
		set_error(csf_errno_none,
			"bounary[%s] format error. %s",
			boundary.c_str(),
			get_usage().c_str());
		return csf_false;
	}
	else {
		//如果match提取的参数小于等于需要的参数个数，则表示错误
		if (tmp_match_result.size() <= csf_boundary_parametes_size) {
			set_error(csf_errno_none,
				"bounary[%s] format error. reason: parametes number[%d <= %d]. %s",
				boundary.c_str(),
				tmp_match_result.size(),
				csf_boundary_parametes_size,
				get_usage().c_str());
			return csf_false;
		}

		//获取"(-n, 100]"格式数据中的"(]"两个字符。
		//其中tmp_match_result[1]的1就是"("的位置编号；
		//其中tmp_match_result[4]的4就是"]"的位置编号；
		if (!get_function(tmp_match_result[1].str() + tmp_match_result[4].str())) {
			set_error(csf_errno_none,
				"bounary[%s] format error. reason: not found function. %s",
				boundary.c_str(),
				get_usage().c_str());
			return csf_false;
		}

		//获取"(-n, 100]"格式数据中的"-n","100"两个字符段。
		//其中tmp_match_result[2]的1就是"-n"的位置编号；
		//其中tmp_match_result[3]的4就是"100"的位置编号；
		if (!get_parametes(tmp_match_result[2].str(), tmp_match_result[3].str())) {
// 			set_error(csf_errno_none,
// 				"bounary[%s] format error. reason: get paramentes failed. %s",
// 				boundary.c_str(),
// 				get_usage().c_str());
			return csf_false;
		}
	}
	return csf_true;
}

/**
* 根据传入的阈值边界数据字符串提取数据。其中-n转化为int64的最小值；+n转化为int64的最大值。
* 返回：true表示成功；false表示失败。
*
* @param lower	阈值的最小值
* @param upper	阈值的最大值
*/
csf_bool csf_attribute_boundary::get_parametes(const csf_string& lower, const csf_string& upper) {

	//判断是否为最小值，如果不是，则计算数值
	if (!lower.empty() && lower != std::string("-n")) {
		set_lower_bound(csf_atoint64(lower.c_str()));
	}
	else {
		set_lower_bound(csf_min_int64);
	}

	//判断是否为最大值，如果不是，则计算数值
	if (!upper.empty() && upper != std::string("n") && upper != std::string("+n")) {
		set_upper_bound(csf_atoint64(upper.c_str()));
	}
	else {
		set_upper_bound(csf_max_int64);
	}

	//校验两个边界值的数值大小
	if (get_lower_bound() > get_upper_bound()) {

		set_error(csf_errno_none
			, "bounary[%s] format error. reason: lower_bound[%lld] > upper_bound[%lld]."
			, get_boundary().c_str()
			, get_lower_bound()
			, get_upper_bound());

		return csf_false;
	}

	return csf_true;
}