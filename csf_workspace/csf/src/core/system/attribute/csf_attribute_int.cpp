/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_int.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7月-2018 11:09:59
*
*Description: Class(csf_attribute_int)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_int.hpp"
#include "csf_attribute_printf.h"

using csf::core::system::attribute::csf_attribute_int;



/**
 * 从内容中解析需要的参数。
 * 返回：ture表示解析成功；false表示解析失败。
 * 
 * @param content    表示需要解析的内容信息
 */
csf_bool csf_attribute_int::parse_parametes(const csf_string& content) {

	/**
	* 表示核验格式和截取字符串正则表达式
	*/
	std::regex					tmp_regex("(\\d+)");
	std::smatch					tmp_match_result;
	csf_int32					tmp_value = 0;


	if (content.empty()) {
		return csf_false;
	}

	//使用正则表达式核验数据结构和提取参数
	if (!std::regex_match(content, tmp_match_result, tmp_regex)) {
		//正则表达式匹配失败，表示数据格式错误
		csf_attribute_log(warning, csf_log_code_warning
			, "content format error.");
		return csf_false;
	}
	else {
		//如果match提取的参数小于等于需要的参数个数，则表示错误
		if (tmp_match_result.size() <= csf_attribute_int_parametes_size) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. parametes number[%d <= %d]. %s"
				, tmp_match_result.size()
				, csf_attribute_int_parametes_size);
			return csf_false;
		}

		//将字符串数字转换为int32格式的数值
		tmp_value = csf_atoint32(tmp_match_result[1].str().c_str());
		if (tmp_value < 0) {
			csf_attribute_log(warning, csf_log_code_warning,
				"value[%s] convert failed.",
				tmp_match_result[1].str().c_str());
			return csf_false;
		}
		else {
			set_value(tmp_value);
		}
	}
	return csf_true;
}


/**
 * 表示处理csf_attribute属性操作。这里与csf_attribute_template中不同的是，这里添加一层process_number函数主要是为了
 * 实现数据边界的统一处理。
 * 返回：true表示失败；false表示成功。
 * 
 * @param configure_manager    表示保存配置管理器对象
 * @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
 */
csf_bool csf_attribute_int::process_number(const csf_configure_manager& configure_manager, const csf_string& alias) {

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