/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_root_configure.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 14-7月-2018 11:29:48
*
*Description: Class(csf_root_configure) 表示系统的根配置文件处理模块，主要处理程序的根配置文件内容。
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_root_configure.hpp"
#include "csf_container_convert.hpp"

using csf::core::system::csf_root_configure;


/**
* 表示主配置文件文件列表节点的路径信息。
*/
const csf_list<csf_string> csf_root_configure::m_configure_files_items = { "configures", "configure_files" };

/**
* 表示配置文件的属性字符串定义.
*/
const csf_string csf_root_configure::m_configure_file_attribute[] = { "name", "file", "format" };





/**
 * 该函数主要用于初始化app的配置文件，获取配置文件中保存的属性信息。
 * 返回：true表示初始化配置信息成功；false表示初始化配置文件失败。
 *
 * @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
 * @param root_configure_file    表示当前app根配置文件信息
 */
csf_bool csf_root_configure::init_configure_manager(csf::core::system::csf_configure_manager& configure_manager, csf_configure_file& root_configure_file) {

	csf_int32							tmp_int_ret = csf_failure;
	csf_element							tmp_element;
	csf_configure						tmp_configure;


	//如果根配置文件为空，则表示错误直接返回
	if (root_configure_file.is_null()) {
		csf_log_ex(critical, csf_log_code_critical,
			"root configure file is null");
		return csf_false;
	}

	//解析根配置文件内容
	tmp_int_ret = tmp_configure.set_configure_file(root_configure_file);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(critical, csf_log_code_critical,
			"root configure file error. file[%s:%s].",
			root_configure_file.get_format().c_str(),
			root_configure_file.get_file_path().c_str());
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice,
			"root configure file parse succeed. file[%s:%s].",
			root_configure_file.get_format().c_str(),
			root_configure_file.get_file_path().c_str());
	}

	//将解析的configure配置文件内容添加到configure_manager中
	configure_manager.add(tmp_configure);

	//获取指定配置文件列表的节点
	tmp_element = tmp_configure.find_element(get_configure_files_items());
	if (tmp_element.is_null()) {
		csf_log_ex(critical, csf_log_code_critical,
			"root configure file format error. not found element[ %s ].",
			csf_container_convert<csf_list<csf_string>>(get_configure_files_items()).to_string().c_str());
		return csf_false;
	}

	//表示遍历所有子节点内容，解析需要的配置文件内容
	for (auto &tmp_file : tmp_element.get_children()) {

		if (tmp_file.is_null()) {
			continue;
		}

		//创建一个configure_file对象，为处理一个配置文件
		csf_configure_file			tmp_item_file(
			tmp_file.find(m_configure_file_attribute[csf_root_configure_attribute_string_name]),
			tmp_file.find(m_configure_file_attribute[csf_root_configure_attribute_string_file]),
			tmp_file.find(m_configure_file_attribute[csf_root_configure_attribute_string_format])
		);

		if (tmp_item_file.is_null()) {
			continue;
		}

		//解析子配置文件内容
		csf_configure				tmp_item_configure;

		tmp_int_ret = tmp_item_configure.set_configure_file(tmp_item_file);
		if (csf_failure == tmp_int_ret) {
			csf_log_ex(critical, csf_log_code_critical,
				"sub configure file error. file[%s:%s].",
				tmp_item_file.get_format().c_str(),
				tmp_item_file.get_file_path().c_str());
			continue;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"sub configure file parse succeed. file[%s:%s].",
				tmp_item_file.get_format().c_str(),
				tmp_item_file.get_file_path().c_str());
		}

		//将解析的configure配置文件内容添加到configure_manager中
		configure_manager.add(tmp_item_configure);
	}

	return csf_true;
}