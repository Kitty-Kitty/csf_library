/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_number.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7月-2018 20:09:28
*
*Description: Class(csf_attribute_number)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_number.hpp"
#include "csf_attribute_printf.h"
#include "csf_logger.hpp"


using csf::core::system::attribute::csf_attribute_number;

/**
* 表示处理csf_attribute属性操作。这里与csf_attribute中不同的是，这里添加一层process_attribute函数主要是为了实现异常（e
* xception）的统一处理。当异常出现时，直接根据返回错误，调用异常处理函数。
* 返回：true表示失败；false表示成功。
*
* @param configure_manager    表示保存配置管理器对象
* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
*/
csf_bool csf_attribute_number::process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) {

	//初始化解析边界核验
	if (get_boundary().not_null()) {
		if (!get_boundary().init()) {
			csf_attribute_log(warning, csf_log_code_warning
				, "boundary[%s] init failed! reason: %s"
				, get_boundary().get_boundary().c_str()
				, get_boundary().get_descripion().c_str());
			return csf_false;
		}
	}

	//表示解析数值内容
	if (csf_false == process_number(configure_manager, alias)) {
		return csf_false;
	}

	//核验数值的边界，判断是否在合法边界内
	if (get_boundary().not_null()) {
		if (!get_boundary().process(get_value())) {
			csf_attribute_log(warning, csf_log_code_warning
				, " value[%lld] mismatch boundary[ \"%s\" ] warning."
				, get_value()
				, get_boundary().get_boundary().c_str());
			return csf_false;
		}
	}
	return csf_true;
}
