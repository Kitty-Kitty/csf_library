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
*Date: 20-7��-2018 17:41:40
*
*Description: Class(csf_app_bootloader) ��ʾϵͳ�������е�app���������ļ������������������ļ�����������app��ҪĬ�����е�device������ģ����Ҫ���ص�device_io���ݡ�
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_app_bootloader.hpp"


using csf::core::system::csf_app_bootloader;


const csf_list<csf_string> csf_app_bootloader::m_configure_files_items = { "app_configure", "app" };


/**
* �ú�����Ҫ���ڳ�ʼ��app��
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param app    ��ʾĿ��app����
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app_bootloader::init(csf::core::module::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_bool							tmp_bool_ret = csf_false;


	//�������������ļ��е������豸ģ���б�
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

	//��ʼ����Ҫ�������豸ģ���б�
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
 * �ú�����Ҫ���ڳ�ʼ��app��
 * ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
 *
 * @param app    ��ʾĿ��app����
 * @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
 */
csf_bool csf_app_bootloader::start(csf::core::module::csf_app& app
	, csf::core::system::csf_configure_manager& configure_manager) {

	csf_bool							tmp_bool_ret = csf_false;


	//������Ҫ�������豸ģ���б�
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
 * �ú�����Ҫ���ڳ�ʼ��app��
 * ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
 *
 * @param app    ��ʾĿ��app����
 */
csf_bool csf_app_bootloader::stop(csf::core::module::csf_app& app) {

	csf_bool							tmp_bool_ret = csf_false;


	//������Ҫ�������豸ģ���б�
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
* ���ܣ��ú�����Ҫ���������ļ����ݴ���app�����������豸ģ�顣
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param app    ��ʾĿ��app����
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
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
* ���ܣ��ú�����Ҫ���������ļ����ݴ���һ���豸ģ�顣
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param app    ��ʾĿ��app����
* @param element    ��ʾ��ǰ��device�ڵ�����
*/
csf_bool csf_app_bootloader::create_device(csf::core::module::csf_app& app
	, csf_element& element) {

	if (element.is_null()) {
		return csf_false;
	}

	//�жϵ�ǰ�Ƿ�Ϊdevice�ڵ㣬�����������豸
	if (CSF_CONFIGURE_STRING(device) == element.get_name()) {

		return add_device(app, element);
	}

	//���������ӽڵ����ݣ�����豸
	for (auto &tmp_elem : element.get_children()) {

		//���������һ��ģ��������˳�������
		//��������������Ҫ��֤����ģ�鶼�ɹ���������
// 		if (csf_false == create_device(app, tmp_elem)) {
// 			return csf_false;
// 		}
		create_device(app, tmp_elem);
	}

	return csf_true;
}


/**
* ���ܣ��ú�����Ҫ���������ļ����ݴ���app�������������豸ģ�顣
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param device    ��ʾ������device�豸��Ϣ
* @param element    ��ʾ��ǰ��device�ڵ�����
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
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
* ���ܣ��ú�����Ҫ���������ļ����ݴ���һ�����豸ģ�顣
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param device    ��ʾ������device�豸��Ϣ
* @param element    ��ʾ��ǰ��device�ڵ�����
*/
csf_bool csf_app_bootloader::create_device_io(csf::core::module::csf_device& device, csf_element& element) {

	if (element.is_null()) {
		return csf_false;
	}

	//�жϵ�ǰ�Ƿ�Ϊdevice�ڵ㣬�����������豸
	if (CSF_CONFIGURE_STRING(device_io) == element.get_name()) {
		return add_device_io(device, element);
	}

	return csf_true;
}


/**
* �ú�����Ҫ�������һ���豸��app�С�
* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
*
* @param app    ��ʾĿ��app����
* @param element    ��ʾģ��������Ϣ
*/
csf_bool csf_app_bootloader::add_device(csf::core::module::csf_app& app, csf_element& element) {

	csf_module					*tmp_module = csf_nullptr;
	csf_string					tmp_string_name = "";
	csf_string					tmp_string_mid = "";


	if (element.is_null()) {
		return csf_false;
	}

	//�жϵ�ǰ�Ƿ�Ϊdevice�ڵ㣬�����������豸
	tmp_string_name = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "name"}))).get_content();
	tmp_string_mid = ((csf_element&)(element.find_element(csf_list<csf_string>{"module", "mid"}))).get_content();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {

		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: module[name:\"%s\"] or mid[\"%s\"] is null!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());

		return csf_false;
	}

	//�������ƴ���ģ�����
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

	//У���ģ���Ƿ�Ϊdeviceģ��������������ӣ����������ģ���Ǵ���ģ����٣�
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

		//�����豸��app����
		((csf::core::module::csf_device*)tmp_module)->set_app(&app);

		//����豸��app�豸�б���
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
* �ú�����Ҫ�������һ���豸��app�С�
* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
*
* @param app    ��ʾĿ��app����
* @param name    ��ʾģ������
* @param mid    ��ʾģ�鴴���Ķ���ΨһID
*/
csf_bool csf_app_bootloader::add_device(csf::core::module::csf_app& app
	, const csf_string& name
	, const csf_string& mid) {

	csf_module					*tmp_module = csf_nullptr;


	//�������ݵĺϷ���
	if (name.empty() && mid.empty()) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: module[name:\"%s\"] or mid[\"%s\"] is null!"
			, name.c_str()
			, mid.c_str());
		return csf_false;
	}

	//�������ƴ���ģ�����
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

	//У���ģ���Ƿ�Ϊdeviceģ��������������ӣ����������ģ���Ǵ���ģ����٣�
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

		//����豸���豸�б���
		return add_device(app, mid, (csf::core::module::csf_device*)tmp_module);
	}

	return csf_true;
}


/**
* �ú�����Ҫ�������һ���豸��app�С�
* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
*
* @param app    ��ʾĿ��app����
* @param mid    ��ʾģ�鴴���Ķ���ΨһID
* @param device    ��ʾ����ӵ��豸��ַ
*/
csf_bool csf_app_bootloader::add_device(csf::core::module::csf_app& app
	, const csf_string& mid
	, const csf::core::module::csf_device* device) {


	if (mid.empty() || !device) {
		return csf_false;
	}

	//����豸���豸�б���

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
* ���ܣ��ú�����Ҫ���ڴ���һ���豸����
* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܡ�
*
* @param app    ��ʾĿ��aap����
* @param name    ��ʾģ������
*/
csf::core::module::csf_module* csf_app_bootloader::create_module(csf::core::module::csf_app& app
	, const csf_string& name) {

	csf_module					*tmp_module = csf_nullptr;


	//�������ݵĺϷ���
	if (name.empty()) {
		csf_log_ex(error, csf_log_code_error
			, "add device failed! reason: name[\"%s\"] is null!"
			, name.c_str());
		return csf_nullptr;
	}

	//�������ƴ���ģ�����
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

	//У���ģ���Ƿ�Ϊdeviceģ��������������ӣ����������ģ���Ǵ���ģ����٣�
	if (!csf_device_base::is_device(tmp_module->get_type())) {
		csf_log_ex(error, csf_log_code_error
			, "add device module[name:\"%s\"] failed! reason: module type[%d] faile!"
			, name.c_str()
			, tmp_module->get_type());

		app.get_module_manager().destory(tmp_module);

		return csf_nullptr;
	}
	else {

		//����豸���豸�б���

		((csf_device_base*)tmp_module)->set_parent(&app);

		return tmp_module;
	}

	return csf_nullptr;
}


/**
* �ú�����Ҫ�������һ���豸��device�С�
* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
*
* @param device    ��ʾĿ��device����
* @param element    ��ʾģ��������Ϣ
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

		//����豸��������ɹ�����������豸
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
* �ú�����Ҫ�������һ���豸��device�С�
* ���أ�true��ʾ��ӳɹ���false��ʾ���ʧ�ܡ�
*
* @param device    ��ʾĿ��aap����
* @param mid    ��ʾģ�鴴���Ķ���ΨһID
* @param device_io    ��ʾ����ӵ��豸��ַ
*/
csf_bool csf_app_bootloader::add_device_io(csf::core::module::csf_device& device
	, const csf_string& mid
	, const csf::core::module::csf_device_io* device_io) {

	if (!device_io || mid.empty()) {
		return csf_false;
	}
	//����豸���豸�б���

	((csf::core::module::csf_device_io*)device_io)->set_mid(mid);
	((csf::core::module::csf_device_io*)device_io)->set_app(get_app());
	((csf::core::module::csf_device_io*)device_io)->set_device(&device);

	return device.add_device_io(mid, device_io);
}


/**
* ���ܣ��ú�����ʼ��app�е������豸��
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param app    ��ʾ������app��Ϣ
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app_bootloader::init_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//���α����豸����ʼ���豸
	for (auto &tmp_iter : app.get_devices()) {

		if (!tmp_iter.second) {
			continue;
		}

		//��ʼ��ʼ���豸
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
* ���ܣ��ú�������app�е������豸��
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param app    ��ʾ������app��Ϣ
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app_bootloader::start_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//���α����豸����ʼ���豸
	for (auto &tmp_iter : app.get_devices()) {

		if (!tmp_iter.second) {
			continue;
		}

		//�����豸
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
* ���ܣ��ú���ֹͣapp�е������豸��
* ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
*
* @param app    ��ʾ������app��Ϣ
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app_bootloader::stop_devices(csf_app& app, csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//���α����豸����ʼ���豸
	for (auto &tmp_iter : app.get_devices()) {

		if (!tmp_iter.second) {
			continue;
		}

		//ֹͣ�豸
		tmp_int_ret = tmp_iter.second->stop(&configure_manager);
		if (csf_failure == tmp_int_ret) {

			return csf_false;
		}
		else {

		}
	}

	return csf_true;
}