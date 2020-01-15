/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_string.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7月-2018 14:45:30
*
*Description: Class(csf_attribute_string)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_string.hpp"

using csf::core::system::attribute::csf_attribute_string;





/**
 * 表示处理csf_attribute属性操作。这里与csf_attribute中不同的是，这里添加一层process_attribute函数主要是为了实现异常（e
 * xception）的统一处理。当异常出现时，直接根据返回错误，调用异常处理函数。
 * 返回：true表示失败；false表示成功。
 * 
 * @param configure_manager    表示保存配置管理器对象
 * @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
 */
csf_bool csf_attribute_string::process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) {

	//调用基础库的初始化函数获取内容数值，主要是获取content数值
	if (csf_false == csf_attribute::init(configure_manager, alias)) {
		return csf_false;
	}

	set_value(get_content());

	return csf_true;
}