/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_app_option.hpp
*
*Version: 1.0
*
*Date: 06-12月-2019 13:11:25
*
*Description: Class(csf_app_option)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_app_option.hpp"

using csf::core::module::csf_app_option;


/**
* 功能：
*    解析程序运行参数信息
* 返回：
*    true：表示设置成功；
*    false：表示设置失败；
*
* @param argc    表示参数的个数
* @param argv    表示参数内容
*/
bool csf_app_option::get_option(int argc, char** argv) {

	variables_map		tmp_vm;
	csf_bool			tmp_boot_ret = false;


	if (argc <= 1 && !isconfigured()) {

		std::cout << "usage  : app [OPTION]... [VAR=VALUE]..." << std::endl << std::endl;
		std::cout << "example: app -f /etc/csf_configs.xml -t xml" << std::endl << std::endl;

		help(tmp_vm, "");
		return false;
	}

	//(1) store: 存储分析结果  (2) command_line_parser: 分析器
	store(command_line_parser(argc, argv).options(get_description()).run(), tmp_vm);
	//更新存储器 tmp_vm
	notify(tmp_vm);

	//遍历所有配置项处理函数
	for (auto tmp_function : get_function_map()) {
		if (tmp_vm.count(tmp_function.first)) {
			tmp_function.second(tmp_vm, tmp_function.first);
		}
	}

	//设置当前app的配置文件
	if (tmp_vm.count("file") && tmp_vm.count("format")) {
		tmp_boot_ret = configure(tmp_vm["file"].as<std::string>()
			, tmp_vm["format"].as<std::string>());
	}

	return tmp_boot_ret;
}


/**
* 功能：
*    表示app是否已经配置完成
* 返回：
*    true：表示设置成功；
*    false：表示未设置成功；
*/
bool csf_app_option::isconfigured() {

	if (get_app().get_root_configure_file().is_null()) {
		return false;
	}
	return true;
}


/**
 * 功能：
 *    打印app使用参数提示信息
 * 返回：
 *    无
 *
 * @param vm    表示当前的参数列表
 * @param key    表示当前参数的名称
 */
void csf_app_option::help(variables_map& vm, std::string key) {

	std::cout << get_app().get_version().get_strver() << std::endl;
	std::cout << get_description() << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "example: " << get_app().get_name() << " -f /etc/csf_configs.xml -t xml" << std::endl;
	exit(0);
}


/**
 * 功能：
 *    打印app版本号信息
 * 返回：
 *    无
 *
 * @param vm    表示当前的参数列表
 * @param key    表示当前参数的名称
 */
void csf_app_option::version(variables_map& vm, std::string key) {

	//printf("%s\r\n", get_app().to_string().c_str());
	std::cout << get_app().get_version().get_strver();
	std::cout << "   (" << get_app().get_version().get_build() << ")" << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << get_app().get_version().to_string() << std::endl;
	exit(0);
}


/**
 * 功能：
 *    设置当前app的名称
 * 返回：
 *    无
 *
 * @param vm    表示当前的参数列表
 * @param key    表示当前参数的名称
 */
void csf_app_option::name(variables_map& vm, std::string key) {
	get_app().set_name(vm[key].as<std::string>());
}


/**
 * 功能：
 *    设置当前app所属的vm对象
 * 返回：
 *    无
 *
 * @param vm    表示当前的参数列表
 * @param key    表示当前参数的名称
 */
void csf_app_option::vm_pid(variables_map& vm, std::string key) {
	get_app().set_vm_pid(vm[key].as<std::uint32_t>());
}


/**
 * 功能：
 *    设置当前app所属的vm对象地址指针
 * 返回：
 *    无
 *
 * @param vm    表示当前的参数列表
 * @param key    表示当前参数的名称
 */
void csf_app_option::vm_instance(variables_map& vm, std::string key) {
	get_app().set_vm(reinterpret_cast<csf_vm*>(vm[key].as<std::uint64_t>()));
	//get_app().set_vm(vm[key].as<csf_vm*>());
}


/**
 * 
 * @param file    表示app需要的根配置文件
 * @param fmt    表示配置文件的格式
 */
bool csf_app_option::configure(std::string file, std::string fmt) {

	get_app().get_root_configure_file().set_name(CSF_APP_ROOT_CONFIGURE_FILE_NAME_STRING);
	get_app().get_root_configure_file().set_file_path(file);
	get_app().get_root_configure_file().set_format(fmt);

	return true;
}


/**
* 功能：
*    表示添加程序参数信息
* 返回：
*    无
*/
void csf_app_option::add_options() {

	get_description().add_options()
		("help,h", "display this help and exit")
		("version,v", "display version information and exit")
		("file,f", value<std::string>(), "configure file")
		("format,t", value<std::string>()->default_value("xml"), "configure file format")
		("vm_pid,p", value<std::uint32_t>()->default_value(0), "vm pid")
		("vm_instance,i", value<std::uint64_t>()->default_value(0), "vm instance point")
		("name,n", value<std::string>()->default_value(""), "app name")
		;

	//将处理函数添加到列表中
	get_function_map().insert(std::make_pair("help"
		, std::bind(&csf_app_option::help, this, std::placeholders::_1, std::placeholders::_2)));
	get_function_map().insert(std::make_pair("version"
		, std::bind(&csf_app_option::version, this, std::placeholders::_1, std::placeholders::_2)));
	get_function_map().insert(std::make_pair("vm_pid"
		, std::bind(&csf_app_option::vm_pid, this, std::placeholders::_1, std::placeholders::_2)));
	get_function_map().insert(std::make_pair("vm_instance"
		, std::bind(&csf_app_option::vm_instance, this, std::placeholders::_1, std::placeholders::_2)));
	get_function_map().insert(std::make_pair("name"
		, std::bind(&csf_app_option::name, this, std::placeholders::_1, std::placeholders::_2)));
}
