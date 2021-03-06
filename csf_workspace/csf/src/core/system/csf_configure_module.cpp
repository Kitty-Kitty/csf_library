/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_configure_module.hpp
*
*Version: 1.0
*
*Date: 04-10月-2018 19:44:08
*
*Description: Class(csf_configure_module)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_configure_module.hpp"
#include "csf_device_base.hpp"
#include "csf_app.hpp"
#include "csf_device.hpp"
#include "csf_device_io.hpp"


using csf::core::system::csf_configure_module;


csf_configure_module::csf_configure_module() {

}



csf_configure_module::~csf_configure_module() {

}





/**
* 主要功能是：通过配置信息创建一个基础模块对象
* 返回：非null表示模块对象地址；null表示失败；
*
* @param app    表示针对指定app创建模块对象
* @param module_manager    表示模块管理器对象信息
* @param element    表示模块的配置信息。
*
* 模块配置信息结构如下：
* <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* <module>
*        <!--***表示模块对应的模块名称信息***-->
*        <name>csf_connection</name>
*        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
*        <mid>02000000-0000001</mid>
*        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
*        <configure>
*                <!--表示线程数量-->
*                <thread_number>4</thread_number>
*        </configure>
* </module>
*
*
*/
csf::core::module::csf_device_base* csf_configure_module::create_module(
	csf_app* app
	, csf::core::module::csf_module_manager& module_manager
	, const csf::core::system::csf_element& element) {

	csf_device_base				*tmp_device_base = csf_nullptr;
	csf_int32					tmp_int_return = 0;
	csf_string					tmp_string_name = "";
	csf_string					tmp_string_mid = "";
	csf_string					tmp_string_root_configure_name = "";
	csf::core::system::csf_element	*tmp_element = const_cast<csf::core::system::csf_element*>(&element);


	if (element.is_null()) {
		return csf_nullptr;
	}

	//判断当前是否为device节点，如果是则添加设备
	tmp_string_name = element.find_element(csf_list<csf_string>{"module", "name"}).get_content();
	tmp_string_mid = element.find_element(csf_list<csf_string>{"module", "mid"}).get_content();
	tmp_string_root_configure_name = element.find_element(csf_list<csf_string>{"module", "configure", "root_configure_name"}).get_content();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {

		csf_log_ex(error, csf_log_code_error
			, "module[name:\"%s\"] or mid[\"%s\"] is null!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());

		return csf_nullptr;
	}

	//根据名称创建模块对象
	tmp_device_base = dynamic_cast<csf_device_base*>(module_manager.create(tmp_string_name));
	if (!tmp_device_base) {
		csf_log_ex(error, csf_log_code_error
			, "create module[name:\"%s\" mid:\"%s\"] failed!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());
		return csf_nullptr;
	}
	else {
		
		//添加设备到设备列表中
		tmp_device_base->set_name(tmp_string_name);
		tmp_device_base->set_mid(tmp_string_mid);
		tmp_device_base->set_root_configure_name(tmp_string_root_configure_name);
		tmp_device_base->set_parent(app);
		
		//设置device设备的app对象
		if (csf_device_base::is_device(tmp_device_base->get_type())) {
			dynamic_cast<csf_device*>(tmp_device_base)->set_app(app);
		}
		else {
			//设置device_io设备的app对象
			if (csf_device_base::is_device_io(tmp_device_base->get_type())) {
				dynamic_cast<csf_device_io*>(tmp_device_base)->set_app(app);
			}
		}
		
		if (element.find_element(csf_list<csf_string>{"module", "configure"}).is_null()) {

			csf_log_ex(notice, csf_log_code_notice
				, "create module[%p name:\"%s\" mid:\"%s\"] succeed!"
				, tmp_device_base
				, tmp_string_name.c_str()
				, tmp_string_mid.c_str());
		}
		else {

			//根据"root_configure_name"指定的名称，获取配置根配置项信息
			if (tmp_device_base->update_root_configure_by_name(tmp_string_root_configure_name)) {
				tmp_element = tmp_device_base->get_attribute_manager().get_root_element();
			}
			else {
				tmp_element = const_cast<csf::core::system::csf_element*>(&element);
			}
			
			csf_log(notice, "configure module[%s]...", tmp_device_base->get_version().to_string().c_str());
			//配置模块的信息
			tmp_int_return = tmp_device_base->configure(*tmp_element);
			if (tmp_int_return) {
				csf_log_ex(error, csf_log_code_error
					, "create module[%p name:\"%s\" mid:\"%s\"] succeed! reason:[%d] configure failed!"
					, tmp_device_base
					, tmp_string_name.c_str()
					, tmp_string_mid.c_str()
					, tmp_int_return);

				csf_log(error, "configure module[%s] failed!", tmp_device_base->get_version().to_string().c_str());

				module_manager.destroy(tmp_device_base);

				return csf_nullptr;
			}
			else {
				csf_log_ex(notice, csf_log_code_notice
					, "create module[%p name:\"%s\" mid:\"%s\"] and configure succeed!"
					, tmp_device_base
					, tmp_string_name.c_str()
					, tmp_string_mid.c_str());

				csf_log(notice, "configure module[%s] succeed!", tmp_device_base->get_version().to_string().c_str());
			}
		}		
	}

	return  tmp_device_base;
}


/**
 * 功能：
 *    销毁一个模块对象
 * 返回：
 *    0  ：  表示成功；
 *   非0 ：  表示失败；
 *
 * @param module_manager    表示模块管理器对象信息
 * @param module    表示模块对象
 */
csf_int32 csf_configure_module::destroy_module(csf::core::module::csf_module_manager& module_manager, csf_module * module) {

	csf_int32					tmp_int_return = 0;


	//根据名称创建模块对象
	csf_log(notice, "destroy %s ...", module->to_string().c_str());

	tmp_int_return = module_manager.destroy(module);
	if (csf_failure == tmp_int_return) {
		csf_log_ex(error, csf_log_code_error
			, "destroy module[%p] failed!"
			, module);
		return csf_failure;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "destroy module[%p] succeed!"
			, module);
		return csf_succeed;
	}

	return csf_succeed;
}