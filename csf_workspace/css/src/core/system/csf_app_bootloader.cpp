/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_app_bootloader.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 20-7月-2018 17:41:40
*
*Description: Class(csf_app_bootloader) 表示系统启动运行的app程序配置文件处理。类似启动引导文件，用于描述app需要默认运行的device及各个模块需要加载的device_io内容。
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_app_bootloader.hpp"


using csf::core::system::csf_app_bootloader;


const csf_list<csf_string> csf_app_bootloader::m_configure_files_items = { "app_configure", "app" };


/**
* 该函数主要用于初始化app。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示目标app对象
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::init(csf::core::module::app::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	return csf_true;
}


/**
 * 该函数主要用于初始化app。
 * 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
 *
 * @param app    表示目标app对象
 * @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
 */
csf_bool csf_app_bootloader::start(csf::core::module::app::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	return csf_true;
}


/**
 * 该函数主要用于初始化app。
 * 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
 *
 * @param app    表示目标app对象
 */
csf_bool csf_app_bootloader::stop(csf::core::module::app::csf_app& app) {

	return csf_true;
}


/**
* 该函数主要用于初始化app。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示目标app对象
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::init_devices(csf::core::module::app::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_element				*tmp_element = csf_nullptr;


	tmp_element = (csf_element *)&(configure_manager.find_element(csf_list<csf_string>{"device_configure", "devices"}));
	if (tmp_element->is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not found element[%s]"
			, csf_container_convert<csf_list<csf_string>>(csf_list<csf_string>{"device_configure", "devices"}).to_string().c_str());
		return csf_false;
	}
	else {
		return init_device(app, *tmp_element);
	}

	return csf_true;
}


/**
* 该函数主要用于初始化app。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示目标app对象
* @param element    表示当前的device节点内容
*/
csf_bool csf_app_bootloader::init_device(csf::core::module::app::csf_app& app
	, csf_element& element) {

	if (element.is_null()) {
		return csf_false;
	}

	//判断当前是否为device节点，如果是则添加设备
	if (CSF_CONFIGURE_STRING(device) == element.get_name()) {

		return add_device(app, element);
	}

	//遍历所有子节点内容，添加设备
	for (auto &tmp_elem : element.get_children()) {
		init_device(app, tmp_elem);
	}

	return csf_true;
}


/**
* 该函数主要用于初始化app。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param device    表示所属的device设备信息
* @param element    表示当前的device节点内容
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::init_device_ioes(csf::core::module::device::csf_device& device
	, csf_element& element
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_element				*tmp_element = csf_nullptr;


	tmp_element = (csf_element *)&(configure_manager.find_element(
		csf_list<csf_string>{"device_io_configure", "device_ioes"}));
	if (tmp_element->is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not found element[%s]"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"device_io_configure", "device_ioes"}).to_string().c_str());
		return csf_false;
	}
	else {
		for (auto &tmp_elem : tmp_element->get_children()) {
			if (tmp_elem.not_null()) {
				init_device_io(device, tmp_elem);
			}
		}
	}

	return csf_true;
}


/**
* 该函数主要用于初始化app。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param device    表示所属的device设备信息
* @param element    表示当前的device节点内容
*/
csf_bool csf_app_bootloader::init_device_io(csf::core::module::device::csf_device& device, csf_element& element) {

	if (element.is_null()) {
		return csf_false;
	}

	//判断当前是否为device节点，如果是则添加设备
	if (CSF_CONFIGURE_STRING(device_io) == element.get_name()) {
		return add_device_io(device, element);
	}

	return csf_true;
}


/**
* 该函数主要用于添加一个设备到app中。
* 返回：true表示添加成功；false表示添加失败。
*
* @param app    表示目标app对象
* @param element    表示模块配置信息
*/
csf_bool csf_app_bootloader::add_device(csf::core::module::app::csf_app& app, csf_element& element) {

	csf_module					*tmp_module = csf_nullptr;
	csf_string					tmp_string_name = "";
	csf_string					tmp_string_mid = "";


	if (element.is_null()) {
		return csf_false;
	}

	//判断当前是否为device节点，如果是则添加设备
	tmp_string_name = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "name"}))).get_name();
	tmp_string_mid = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "mid"}))).get_name();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {
		return csf_false;
	}

	//根据名称创建模块对象
	tmp_module = app.get_module_manager().create(tmp_string_name);
	if (!tmp_module) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: create module[name: %s] mid[%s] failed!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create module[name: %s] mid[%s] succeed!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());
	}

	//校验该模块是否为device模块对象。如果是则添加；如果不是则模块是错误的，销毁；
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name: %s] mid[%s] failed! reason: module type[%d] faile!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str()
			, tmp_module->get_type());

		app.get_module_manager().destory(tmp_module);

		return csf_false;
	}
	else {

		//添加设备到app设备列表中
		if (!add_device(app, tmp_string_mid, (csf::core::module::device::csf_device*)tmp_module)) {

			app.get_module_manager().destory(tmp_module);

			return csf_false;
		}
		else {
			return init_device_ioes(*((csf::core::module::device::csf_device*)tmp_module), element, app.get_config_mg());
		}
	}

	return csf_true;
}


/**
* 该函数主要用于添加一个设备到app中。
* 返回：true表示添加成功；false表示添加失败。
*
* @param app    表示目标app对象
* @param name    表示模块名称
* @param mid    表示模块创建的对象唯一ID
*/
csf_bool csf_app_bootloader::add_device(csf::core::module::app::csf_app& app
	, const csf_string& name
	, const csf_string& mid) {

	csf_module					*tmp_module = csf_nullptr;


	//核验数据的合法性
	if (name.empty() && mid.empty()) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: name[%s] or mid[%s] is null!"
			, name.c_str()
			, mid.c_str());
		return csf_false;
	}

	//根据名称创建模块对象
	tmp_module = app.get_module_manager().create(name);
	if (!tmp_module) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: create module[name: %s] mid[%s] failed!"
			, name.c_str()
			, mid.c_str());
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create module[name: %s] mid[%s] succeed!"
			, name.c_str()
			, mid.c_str());
	}

	//校验该模块是否为device模块对象。如果是则添加；如果不是则模块是错误的，销毁；
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name: %s] mid[%s] failed! reason: module type[%d] faile!"
			, name.c_str()
			, mid.c_str()
			, tmp_module->get_type());

		app.get_module_manager().destory(tmp_module);

		return csf_false;
	}
	else {

		//添加设备到设备列表中
		return add_device(app, mid, (csf::core::module::device::csf_device*)tmp_module);
	}

	return csf_true;
}


/**
* 该函数主要用于添加一个设备到app中。
* 返回：true表示添加成功；false表示添加失败。
*
* @param app    表示目标app对象
* @param mid    表示模块创建的对象唯一ID
* @param device    表示需添加的设备地址
*/
csf_bool csf_app_bootloader::add_device(csf::core::module::app::csf_app& app
	, const csf_string& mid
	, const csf::core::module::device::csf_device* device) {


	if (mid.empty() || !device) {
		return csf_false;
	}

	//添加设备到设备列表中

	((csf::core::module::device::csf_device*)device)->set_mid(mid);
	((csf::core::module::device::csf_device*)device)->set_parent(&app);

	if (!app.add_device(mid, (csf_void*)device)) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name: %s] mid[%s] failed!"
			, ((csf::core::module::device::csf_device*)device)->get_name().c_str()
			, mid.c_str());

		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "add device module[name: %s] mid[%s] succeed!"
			, ((csf::core::module::device::csf_device*)device)->get_name().c_str()
			, mid.c_str());

		return csf_true;
	}

	return csf_true;
}


/**
* 功能：该函数主要用于创建一个设备对象。
* 返回：非空表示成功；空表示失败。
*
* @param app    表示目标aap对象
* @param name    表示模块名称
*/
csf::core::module::csf_module* csf_app_bootloader::create_module(csf::core::module::app::csf_app& app
	, const csf_string& name) {

	csf_module					*tmp_module = csf_nullptr;


	//核验数据的合法性
	if (name.empty()) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: name[%s] is null!"
			, name.c_str());
		return csf_nullptr;
	}

	//根据名称创建模块对象
	tmp_module = app.get_module_manager().create(name);
	if (!tmp_module) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: create module[name: %s] failed!"
			, name.c_str());
		return csf_nullptr;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create module[name: %s] succeed!"
			, name.c_str());
	}

	//校验该模块是否为device模块对象。如果是则添加；如果不是则模块是错误的，销毁；
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name: %s] failed! reason: module type[%d] faile!"
			, name.c_str()
			, tmp_module->get_type());

		app.get_module_manager().destory(tmp_module);

		return csf_nullptr;
	}
	else {

		//添加设备到设备列表中

		((csf_device_base*)tmp_module)->set_parent(&app);

		return tmp_module;
	}

	return csf_nullptr;
}


/**
* 该函数主要用于添加一个设备到device中。
* 返回：true表示添加成功；false表示添加失败。
*
* @param device    表示目标device对象
* @param element    表示模块配置信息
*/
csf_bool csf_app_bootloader::add_device_io(csf::core::module::device::csf_device& device
	, csf_element& element) {

	csf_string										tmp_string_name = "";
	csf_string										tmp_string_mid = "";
	csf::core::module::device_io::csf_device_io		*tmp_device_io = csf_nullptr;


	if (element.is_null()) {
		return csf_false;
	}

	tmp_string_name = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "name"}))).get_name();
	tmp_string_mid = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "mid"}))).get_name();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {
		return csf_false;
	}
	else {
		tmp_device_io = create_device_io(device, tmp_string_name);
		if (!tmp_device_io) {
			return csf_false;
		}

		//添加设备对象，如果成功则添加其子设备
		if (!add_device_io(device, tmp_string_mid, tmp_device_io)) {
			return csf_false;
		}
		else {
			return csf_true;
		}
	}

	return csf_false;
}


/**
* 该函数主要用于添加一个设备到device中。
* 返回：true表示添加成功；false表示添加失败。
*
* @param device    表示目标aap对象
* @param mid    表示模块创建的对象唯一ID
* @param device_io    表示需添加的设备地址
*/
csf_bool csf_app_bootloader::add_device_io(csf::core::module::device::csf_device& device
	, const csf_string& mid
	, const csf::core::module::device_io::csf_device_io* device_io) {

	if (!device_io || mid.empty()) {
		return csf_false;
	}
	//添加设备到设备列表中

	((csf::core::module::device_io::csf_device_io*)device_io)->set_mid(mid);
	((csf::core::module::device_io::csf_device_io*)device_io)->set_app(get_app());
	((csf::core::module::device_io::csf_device_io*)device_io)->set_device(&device);

	return device.add_device_io(mid, device_io);
}