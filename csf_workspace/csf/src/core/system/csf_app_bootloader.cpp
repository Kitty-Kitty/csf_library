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
csf_bool csf_app_bootloader::init(csf::core::module::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_bool							tmp_bool_ret = csf_false;


	//创建引导配置文件中的所有设备模块列表
	tmp_bool_ret = create_devices(app, configure_manager);
	if (csf_false == tmp_bool_ret) {
		csf_log_ex(error, csf_log_code_error
			, "create_devices() failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create_devices() succeed!");
	}

	//初始化需要引导的设备模块列表
	tmp_bool_ret = init_devices(app, configure_manager);
	if (csf_false == tmp_bool_ret) {
		csf_log_ex(error, csf_log_code_error
			, "init_devices() failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "init_devices() succeed!");
	}

	return csf_true;
}


/**
 * 该函数主要用于初始化app。
 * 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
 *
 * @param app    表示目标app对象
 * @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
 */
csf_bool csf_app_bootloader::start(csf::core::module::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_bool							tmp_bool_ret = csf_false;


	//启动需要引导的设备模块列表
	tmp_bool_ret = start_devices(app, configure_manager);
	if (csf_false == tmp_bool_ret) {
		csf_log_ex(error, csf_log_code_error
			, "start_devices() failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "start_devices() succeed!");
	}

	return csf_true;
}


/**
 * 该函数主要用于初始化app。
 * 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
 *
 * @param app    表示目标app对象
 */
csf_bool csf_app_bootloader::stop(csf::core::module::csf_app& app) {

	csf_bool							tmp_bool_ret = csf_false;


	//启动需要引导的设备模块列表
	tmp_bool_ret = start_devices(app, *get_configure_manager());
	if (csf_false == tmp_bool_ret) {
		csf_log_ex(error, csf_log_code_error
			, "start_devices() failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "start_devices() succeed!");
	}

	return csf_true;
}


/**
* 功能：该函数主要根据引导文件内容创建app的所属所有设备模块。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示目标app对象
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::create_devices(csf::core::module::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_element				*tmp_element = csf_nullptr;


	tmp_element = (csf_element *)&(configure_manager.find_element(csf_list<csf_string>{"device_configure", "devices"}));
	if (tmp_element->is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not found element[%s]"
			, csf_container_convert<csf_list<csf_string>>(csf_list<csf_string>{"device_configure", "devices"}).to_string().c_str());
		return csf_true;
	}
	else {
		return create_device(app, *tmp_element);
	}

	return csf_true;
}


/**
* 功能：该函数主要根据引导文件内容创建一个设备模块。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示目标app对象
* @param element    表示当前的device节点内容
*/
csf_bool csf_app_bootloader::create_device(csf::core::module::csf_app& app
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

		//其中如果有一个模块错误，则退出启动。
		//启动引导程序需要保证所以模块都成功才能运行
// 		if (csf_false == create_device(app, tmp_elem)) {
// 			return csf_false;
// 		}
		create_device(app, tmp_elem);
	}

	return csf_true;
}


/**
* 功能：该函数主要根据引导文件内容创建app的所属所有子设备模块。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param device    表示所属的device设备信息
* @param element    表示当前的device节点内容
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::create_device_ioes(csf::core::module::csf_device& device
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
		return csf_true;
	}
	else {
		for (auto &tmp_elem : tmp_element->get_children()) {
			if (tmp_elem.not_null()) {
				create_device_io(device, tmp_elem);
			}
		}
	}

	return csf_true;
}


/**
* 功能：该函数主要根据引导文件内容创建一个子设备模块。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param device    表示所属的device设备信息
* @param element    表示当前的device节点内容
*/
csf_bool csf_app_bootloader::create_device_io(csf::core::module::csf_device& device, csf_element& element) {

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
csf_bool csf_app_bootloader::add_device(csf::core::module::csf_app& app, csf_element& element) {

	csf_module					*tmp_module = csf_nullptr;
	csf_string					tmp_string_name = "";
	csf_string					tmp_string_mid = "";


	if (element.is_null()) {
		return csf_false;
	}

	//判断当前是否为device节点，如果是则添加设备
	tmp_string_name = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "name"}))).get_content();
	tmp_string_mid = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "mid"}))).get_content();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {

		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: module[name:\"%s\"] or mid[\"%s\"] is null!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());

		return csf_false;
	}

	//根据名称创建模块对象
	tmp_module = app.get_module_manager().create(tmp_string_name);
	if (!tmp_module) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: create module[name:\"%s\"] mid[\"%s\"] failed!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create module[name:\"%s\"] mid[\"%s\"] succeed!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());
	}

	//校验该模块是否为device模块对象。如果是则添加；如果不是则模块是错误的，销毁；
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name:\"%s\"] mid[\"%s\"] failed! reason: module type[%d] faile!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str()
			, tmp_module->get_type());

		app.get_module_manager().destory(tmp_module);

		return csf_false;
	}
	else {

		//设置设备的app属性
		((csf::core::module::csf_device*)tmp_module)->set_app(&app);

		//添加设备到app设备列表中
		if (!add_device(app, tmp_string_mid, (csf::core::module::csf_device*)tmp_module)) {

			app.get_module_manager().destory(tmp_module);

			return csf_false;
		}
		else {
			return create_device_ioes(*((csf::core::module::csf_device*)tmp_module), element, app.get_config_mg());
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
csf_bool csf_app_bootloader::add_device(csf::core::module::csf_app& app
	, const csf_string& name
	, const csf_string& mid) {

	csf_module					*tmp_module = csf_nullptr;


	//核验数据的合法性
	if (name.empty() && mid.empty()) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: module[name:\"%s\"] or mid[\"%s\"] is null!"
			, name.c_str()
			, mid.c_str());
		return csf_false;
	}

	//根据名称创建模块对象
	tmp_module = app.get_module_manager().create(name);
	if (!tmp_module) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: create module[name:\"%s\"] mid[\"%s\"] failed!"
			, name.c_str()
			, mid.c_str());
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create module[name:\"%s\"] mid[\"%s\"] succeed!"
			, name.c_str()
			, mid.c_str());
	}

	//校验该模块是否为device模块对象。如果是则添加；如果不是则模块是错误的，销毁；
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name:\"%s\"] mid[\"%s\"] failed! reason: module type[%d] faile!"
			, name.c_str()
			, mid.c_str()
			, tmp_module->get_type());

		app.get_module_manager().destory(tmp_module);

		return csf_false;
	}
	else {

		//添加设备到设备列表中
		return add_device(app, mid, (csf::core::module::csf_device*)tmp_module);
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
csf_bool csf_app_bootloader::add_device(csf::core::module::csf_app& app
	, const csf_string& mid
	, const csf::core::module::csf_device* device) {


	if (mid.empty() || !device) {
		return csf_false;
	}

	//添加设备到设备列表中

	((csf::core::module::csf_device*)device)->set_mid(mid);
	((csf::core::module::csf_device*)device)->set_parent(&app);

	if (!app.add_device(mid, device)) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name:\"%s\"] mid[\"%s\"] failed!"
			, ((csf::core::module::csf_device*)device)->get_name().c_str()
			, mid.c_str());

		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "add device module[name:\"%s\"] mid[\"%s\"] succeed!"
			, ((csf::core::module::csf_device*)device)->get_name().c_str()
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
csf::core::module::csf_module* csf_app_bootloader::create_module(csf::core::module::csf_app& app
	, const csf_string& name) {

	csf_module					*tmp_module = csf_nullptr;


	//核验数据的合法性
	if (name.empty()) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: name[\"%s\"] is null!"
			, name.c_str());
		return csf_nullptr;
	}

	//根据名称创建模块对象
	tmp_module = app.get_module_manager().create(name);
	if (!tmp_module) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: create module[name:\"%s\"] failed!"
			, name.c_str());
		return csf_nullptr;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "create module[name:\"%s\"] succeed!"
			, name.c_str());
	}

	//校验该模块是否为device模块对象。如果是则添加；如果不是则模块是错误的，销毁；
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name:\"%s\"] failed! reason: module type[%d] faile!"
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
csf_bool csf_app_bootloader::add_device_io(csf::core::module::csf_device& device
	, csf_element& element) {

	csf_string										tmp_string_name = "";
	csf_string										tmp_string_mid = "";
	csf::core::module::csf_device_io		*tmp_device_io = csf_nullptr;


	if (element.is_null()) {
		return csf_false;
	}

	tmp_string_name = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "name"}))).get_content();
	tmp_string_mid = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "mid"}))).get_content();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {

		csf_log_ex(error, csf_log_code_error
			, "add device_io failed! reason: module[name:\"%s\"] or mid[\"%s\"] is null!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());

		return csf_false;
	}
	else {
		tmp_device_io = create_device_io(device, tmp_string_name);
		if (!tmp_device_io) {
			return csf_false;
		}
		else {
			tmp_device_io->set_device(&device);
			tmp_device_io->set_parent(&device);
			tmp_device_io->set_app(device.get_app());
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
csf_bool csf_app_bootloader::add_device_io(csf::core::module::csf_device& device
	, const csf_string& mid
	, const csf::core::module::csf_device_io* device_io) {

	if (!device_io || mid.empty()) {
		return csf_false;
	}
	//添加设备到设备列表中

	((csf::core::module::csf_device_io*)device_io)->set_mid(mid);
	((csf::core::module::csf_device_io*)device_io)->set_app(get_app());
	((csf::core::module::csf_device_io*)device_io)->set_device(&device);

	return device.add_device_io(mid, device_io);
}


/**
* 功能：该函数初始化app中的所有设备。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示所属的app信息
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::init_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//依次遍历设备，初始化设备
	for (auto &tmp_iter : app.get_devices()) {

		if (!tmp_iter.second) {
			continue;
		}

		//开始初始化设备
		tmp_int_ret = tmp_iter.second->init(&configure_manager);
		if (csf_failure == tmp_int_ret) {

			return csf_false;
		}
		else {

		}
	}

	return csf_true;
}


/**
* 功能：该函数启动app中的所有设备。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示所属的app信息
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::start_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//依次遍历设备，初始化设备
	for (auto &tmp_iter : app.get_devices()) {

		if (!tmp_iter.second) {
			continue;
		}

		//启动设备
		tmp_int_ret = tmp_iter.second->start(&configure_manager);
		if (csf_failure == tmp_int_ret) {

			return csf_false;
		}
		else {

		}
	}

	return csf_true;
}


/**
* 功能：该函数停止app中的所有设备。
* 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
*
* @param app    表示所属的app信息
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
*/
csf_bool csf_app_bootloader::stop_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//依次遍历设备，初始化设备
	for (auto &tmp_iter : app.get_devices()) {

		if (!tmp_iter.second) {
			continue;
		}

		//停止设备
		tmp_int_ret = tmp_iter.second->stop(&configure_manager);
		if (csf_failure == tmp_int_ret) {

			return csf_false;
		}
		else {

		}
	}

	return csf_true;
}