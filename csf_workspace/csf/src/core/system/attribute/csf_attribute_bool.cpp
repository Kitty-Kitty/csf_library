/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_bool.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:26
*
*Description: Class(csf_attribute_bool)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_bool.hpp"

using csf::core::system::attribute::csf_attribute_bool;


csf_attribute_bool::csf_attribute_bool()
	: csf_attribute_template<csf_bool>(csf_attribute::csf_attribute_type_bool, csf_false) {

}



csf_attribute_bool::~csf_attribute_bool() {

}

/**
* 表示布尔为真类型数据的字符串数值
*/
const csf_string csf_attribute_bool::m_true_string = "true|yes";
/**
* 表示布尔为假类型数据的字符串数值
*/
const csf_string csf_attribute_bool::m_false_string = "false|no";


/**
* 表示处理csf_attribute属性操作。这里与csf_attribute中不同的是，这里添加一层process_attribute函数主要是为了实现异常（e
* xception）的统一处理。当异常出现时，直接根据返回错误，调用异常处理函数。
* 返回：true表示失败；false表示成功。
*
* @param configure_manager    表示保存配置管理器对象
* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
*/
csf_bool csf_attribute_bool::process_attribute(const csf_configure_manager& configure_manager
	, const csf_string& alias) {

	//调用基础库的初始化函数获取内容数值，主要是获取content数值
	if (csf_false == csf_attribute::init(configure_manager, alias)) {
		return csf_false;
	}

	//判断配置的字符是否在true字符串中，如果在则表示true
	if (m_true_string.find(get_content()) != m_true_string.npos) {
		set_value(csf_true);
		return csf_true;
	}

	//判断配置的字符是否在false字符串中，如果在则表示false
	if (m_false_string.find(get_content()) != m_false_string.npos) {
		set_value(csf_false);
		return csf_true;
	}

	return csf_false;
}