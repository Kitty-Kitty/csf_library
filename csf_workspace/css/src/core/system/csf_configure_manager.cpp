/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7��-2018 17:41:45
*
*Description: Class(csf_configure_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_configure_manager.hpp"
#include "csf_attribute_include.h"


using csf::core::system::csf_configure_manager;


csf_configure_manager::csf_configure_manager() {

}



csf_configure_manager::~csf_configure_manager() {

}

/**
* ��ʾ����items����·������һ��element��
* ���أ���null��ʾ����items����·���Ľڵ㣻null��ʾû�в��ҵ�����·���Ľڵ㣻
*
* @param items    items����·��
*/
const csf_element& csf_configure_manager::find_element(const csf_list<csf_string>& items) {

	csf_element				*tmp_element = csf_nullptr;


	//ѭ�����������б����ҷ���·������Ľڵ�
	for (auto &tmp_configure : get_configures()) {
		tmp_element = (csf_element*)&(tmp_configure.second.find_element(items));
		if (tmp_element->not_null()) {
			return *tmp_element;
		}
	}

	return csf_element::get_null();
}



/**
* ���ܣ���ʼ�����ù������е�����������Ϣ����Ҫָģ��������Ϣ������������Ϣ��������
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
*/
csf_bool csf_configure_manager::init() {

	csf_bool					tmp_bool_ret = csf_false;


	//�ж�������Ϣ�б�ĺϷ��ԣ����Ϊ����ֱ�ӷ��ش���
	if (get_configures().empty()) {
		csf_log_ex(error, csf_log_code_error, "configures is null");
		return csf_false;
	}

	//��ʼ��ʼ��ģ�����ù�������Ϣ
	tmp_bool_ret = init_module_configures(get_module_configures(), get_configures());
	if (!tmp_bool_ret) {
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init module configures succeed!");
	}

	//��ʼ��ʼ���������ù�������Ϣ
	tmp_bool_ret = init_measure_configure(get_measure_configure(), get_configures());
	if (!tmp_bool_ret) {
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init measure configure succeed!");
	}

	return csf_true;
}


/**
* ���ܣ���ʼ��ģ�����ù�����
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
*
* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
* @param configures    ��ʾ��ǰ�Ѿ������������ļ���Ϣ
*/
csf_bool csf_configure_manager::init_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
	, csf_map<csf_string, csf_configure>& configures) {

	csf_bool						tmp_bool_ret = csf_false;


	//��ʼ��ʼ��ģ�����ò�������
	tmp_bool_ret = add_module_configures(get_module_configures(), csf_list<csf_string>{CSF_CONFIGURE_STRING(modules_configure)});
	if (!tmp_bool_ret) {
		csf_log_ex(warning, csf_log_code_warning, "add module configures failed!");
		return csf_false;
	}

	return csf_true;
}


/**
* ���ܣ���ʼ���������ù�����
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
*
* @param measure_configure    ��ʾ����󱣴������ģ��������Ϣ
* @param configures    ��ʾ��ǰ�Ѿ������������ļ���Ϣ
*/
csf_bool csf_configure_manager::init_measure_configure(csf_measure_configure& measure_configure
	, csf_map<csf_string, csf_configure>& configures) {


	csf_attribute_manager					tm_attribute_manager(this);


	tm_attribute_manager.add(CSF_CONFIGURE_STRING(device_measure)
		, csf_attribute_int(csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(device_io_measure)
		, csf_attribute_int(csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(client_measure)
		, csf_attribute_int(csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(time_resolution)
		, csf_attribute_time(csf_attribute_time::csf_time_unit_ms
			, csf_attribute_boundary("(0, n)")));

	tm_attribute_manager.add(CSF_CONFIGURE_STRING(timer_resolution)
		, csf_attribute_time(csf_attribute_time::csf_time_unit_ms
			, csf_attribute_boundary("(0, n)")));

	measure_configure.set_device_limit((csf_int32)tm_attribute_manager.get_value<csf_attribute_int>(CSF_CONFIGURE_STRING(device_measure)));
	measure_configure.set_device_io_limit((csf_int32)tm_attribute_manager.get_value<csf_attribute_int>(CSF_CONFIGURE_STRING(device_io_measure)));
	measure_configure.set_connect_limit((csf_int32)tm_attribute_manager.get_value<csf_attribute_int>(CSF_CONFIGURE_STRING(client_measure)));
	measure_configure.set_time_resolution((csf_int32)tm_attribute_manager.get_value<csf_attribute_time>(CSF_CONFIGURE_STRING(time_resolution)));
	measure_configure.set_timer_resolution((csf_int32)tm_attribute_manager.get_value<csf_attribute_time>(CSF_CONFIGURE_STRING(timer_resolution)));

	csf_log_ex(notice, csf_log_code_notice
		, "%s"
		, measure_configure.to_string().c_str());

	return csf_true;
}


/**
* ���ܣ���ģ�����ù����������һ��ģ��������Ϣ��ͬʱ������Ϣ�µ�������ģ����Ϣ
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
*
* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
* @param module_element    ��ʾ��ǰ��ȡ����ģ����Ϣ
*/
csf_bool csf_configure_manager::add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
	, csf_element& module_element) {

	csf_element						*tmp_element_ret = &module_element;


	//���ж��Լ��Ƿ�Ϊģ��ڵ㣬����������
	if (tmp_element_ret->is_null()) {
		return csf_false;
	}
	else {
		if (CSF_CONFIGURE_STRING(module) == tmp_element_ret->get_name()) {
			return add_module_configure(module_configures, *tmp_element_ret);
		}
	}

	//���������ӽڵ�����
	for (auto &tmp_element : tmp_element_ret->get_children()) {
		add_module_configures(module_configures, tmp_element);
	}

	return csf_true;
}


/**
* ���ܣ���ģ�����ù����������һ��ģ��������Ϣ
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
*
* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
* @param module_element    ��ʾ��ǰ��ȡ����ģ����Ϣ
*/
csf_bool csf_configure_manager::add_module_configure(csf_map<csf_string, csf_module_configure>& module_configures
	, csf_element& module_element) {

	csf_string						tmp_string_name = "";
	csf_string						tmp_string_file = "";


	//У�����ݵĺϷ��ԣ�û����������뵽ģ���б���
	if (module_element.is_null()) {
		return csf_false;
	}

	tmp_string_name = module_element.find("name");
	tmp_string_file = module_element.find("file");

	if (tmp_string_name.empty() || tmp_string_file.empty()) {
		return csf_false;
	}

	module_configures.insert(
		csf_map<csf_string, csf_module_configure>::value_type(tmp_string_name
			, csf_module_configure(tmp_string_name, tmp_string_file)));

	csf_log_ex(notice, csf_log_code_notice
		, "add module_configure[name: %s  file: %s] succeed!"
		, tmp_string_name.c_str()
		, tmp_string_file.c_str());

	return csf_true;
}


/**
* ���ܣ���ģ�����ù����������һ��ģ��������Ϣ��ͬʱ������Ϣ�µ�������ģ����Ϣ
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ��
*
* @param module_configures    ��ʾ����󱣴������ģ��������Ϣ
* @param items    ��ʾ��ǰģ����Ϣ·��
*/
csf_bool csf_configure_manager::add_module_configures(csf_map<csf_string, csf_module_configure>& module_configures
	, const csf_list<csf_string>& items) {

	csf_element						*tmp_element_ret = csf_nullptr;


	tmp_element_ret = (csf_element *)&find_element(items);
	if (tmp_element_ret->is_null()) {
		return csf_false;
	}
	else {
		return add_module_configures(module_configures, *tmp_element_ret);
	}
	return csf_false;
}



/**
* ���ܣ�����ģ�����Ʋ�ѯģ��������Ϣ
* ���أ��ǿն����ʾ�ɹ����Ƕ����ʾʧ�ܣ�
*
* @param name    ��ʾģ�������
*/
const csf_module_configure& csf_configure_manager::find_module_configure(const csf_string& name) {

	csf_map<csf_string, csf_module_configure>::iterator				tmp_iter;


	//����Ĳ�ѯ�����̰߳�ȫ��ԭ����ϵͳ��ģ��������Ϣ��ϵͳ������͹̶�����
	tmp_iter = get_module_configures().find(name);
	if (tmp_iter != get_module_configures().end()) {
		return tmp_iter->second;
	}

	return csf_module_configure::get_null();
}