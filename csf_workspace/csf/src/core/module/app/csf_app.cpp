/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_app.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 17:33:42
*
*Description: Class(csf_app)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_app.hpp"
#include "csf_app_bootloader.hpp"
#include "csf_container_convert.hpp"
#include "csf_attribute_default_value.hpp"


using csf::core::module::csf_app;



/**
* ģ���ʼ��
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_app::init(const csf_configure_manager* conf_mg) {

	csf_bool							tmp_bool_ret = csf_false;
	csf_string							tmp_string_ret = "";


	//���������ļ�����������Ϣ���浽configure_manager��
	tmp_bool_ret = init_configure_manager(get_config_mg(), get_root_configure_file());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	/************************************************************************/
	/* ����ǰ����Ŀ¼��Ҫ����������������Դ�����ȼ��������£�                 */
	/*		1������������ȡ��													*/
	/*		2�������ļ���ȡ��													*/
	/*		3����������ʱ�Դ��Ĳ�����											*/
	/* �����ȼ��Ķ�����Ҫ�Ƿ�����������ά������       						*/
	/************************************************************************/
	tmp_bool_ret = init_work_directory(get_config_mg());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}
	
	//����������־ϵͳ��Ϊ�����ṩ��־����
	tmp_bool_ret = init_logger(get_config_mg(), get_work_directory());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}
	
	//��ʼ��ʼ��ϵͳģ�顢�������������Ϣ
	tmp_bool_ret = get_config_mg().init();
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	//��ʼ��ʼ��ϵͳģ�鹤��������
	tmp_bool_ret = init_module_manager(get_config_mg());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

#if 0
	get_attribute_manager().add("time"
		, csf_attribute_time(csf_list<csf_string>({ "configures", "size" }) 
			, csf_attribute_time::csf_time_unit_s 
			, csf_attribute_boundary("(0, 10]")
			, csf_attribute_default_value<csf_attribute_time, csf_int32>(100)));;

	csf_int64 tmp_int64 = get_attribute_manager().get_value<csf_attribute_time>("time");

#endif

	return  csf_success;
}


/**
* ģ������
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_app::start(const csf_configure_manager* conf_mg) {

	csf_bool							tmp_bool_ret = csf_false;
	csf_string							tmp_string_ret = "";


	//ͨ��bootloader����app��Ҫ��ģ��
	tmp_bool_ret = init_bootloader(get_config_mg());
	if (csf_false == tmp_bool_ret) {
		return csf_failure;
	}

	return  csf_success;
}


/**
* ģ��ֹͣ
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_app::stop(const csf_configure_manager* conf_mg) {

	return  csf_success;
}


/**
* �ú�����Ҫ���ڳ�ʼ��app����־ϵͳ��
* ���أ�true��ʾ��ʼ����־ϵͳ�ɹ���false��ʾ��ʼ����־ϵͳʧ�ܡ�
*
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
* @param work_directory    ��ʾ����Ĭ�ϵĹ�����Ŀ¼��ַ
*/
csf_bool csf_app::init_logger(csf::core::system::csf_configure_manager& configure_manager, csf_string work_directory) {

	csf_int32					tmp_int32_ret = 0;


	//����logger�����ù�������ַ������־ϵͳҲ������������Ϣ
	get_logger().set_configure_manager(&get_config_mg());

	//������������˹�����Ŀ¼������Ҫ���õ���־ϵͳ��
	if (!work_directory.empty()) {
		get_logger().set_path(work_directory);
	}

	//�ȳ�ʼ����־ϵͳ���鿴�Ƿ��������
	tmp_int32_ret = get_logger().init(&get_config_mg());
	if (tmp_int32_ret) {
		csf_log_ex(critical, csf_log_code_critical, "init logger failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init logger succeed!");
	}

	//��ʼ����־ϵͳ�ɹ�����ʼ������־ϵͳ
	tmp_int32_ret = get_logger().start(&get_config_mg());
	if (tmp_int32_ret) {
		csf_log_ex(critical, csf_log_code_critical, "start logger failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "start logger succeed!");
	}

	return csf_true;
}


/**
* �ú�����Ҫ���ڳ�ʼ��app��ģ�������
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ�ܡ�
*
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app::init_module_manager(csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32					tmp_int_ret = csf_failure;


	//��ʼ��ģ�鹤����������Ϣ
	tmp_int_ret = get_module_manager().init(get_configure_manager());
	if (tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "module manager init failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "module manager init succeed!");
	}

	//����ģ�鹤����������Ϣ
	tmp_int_ret = get_module_manager().start(get_configure_manager());
	if (tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "module manager start failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "module manager start succeed!");
	}

	return csf_true;
}


/**
* ���ܣ��ú�����Ҫ���ڳ�ʼ��app��������������ģ��
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ�ܡ�
*
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app::init_bootloader(csf::core::system::csf_configure_manager& configure_manager) {

	csf_int32							tmp_int_ret = csf_failure;
	csf_app_bootloader					tmp_app_bootloader(
		(csf::core::module::csf_app*)this
		, (const csf_configure_manager*)&configure_manager);


	//ͨ��app�������򣬳�ʼ��app
	tmp_int_ret = tmp_app_bootloader.init(*this, configure_manager);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "app bootloader init failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "app bootloader init succeed!");
	}

	//ͨ��app������������app
	tmp_int_ret = tmp_app_bootloader.start(*this, configure_manager);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "app bootloader start failed!");
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "app bootloader start succeed!");
	}

	return csf_true;
}


/**
* ���ܣ��ú�����Ҫ���ڳ�ʼ��app�ĵ�ǰ����Ŀ¼
* ���أ�true��ʾ��ʼ���ɹ���false��ʾ��ʼ��ʧ�ܡ�
*
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_app::init_work_directory(csf::core::system::csf_configure_manager& configure_manager) {

	csf_string							tmp_string_ret = "";


	/************************************************************************/
	/* ����ǰ����Ŀ¼��Ҫ����������������Դ�����ȼ��������£�                 */
	/*		1������������ȡ��													*/
	/*		2�������ļ���ȡ��													*/
	/*		3����������ʱ�Դ��Ĳ�����											*/
	/* �����ȼ��Ķ�����Ҫ�Ƿ�����������ά������       						*/
	/************************************************************************/
	//��ȡϵͳ�Ĺ�����Ŀ¼��ַ�������õ���־ϵͳ��
	get_attribute_manager().add("work_directory"
		, csf_attribute_string(csf_list<csf_string>({ "configures", "work_directory" })));;

	tmp_string_ret = get_attribute_manager().get_value<csf_attribute_string>("work_directory");
	if (!tmp_string_ret.empty()) {
		set_work_directory(tmp_string_ret);
	}
	else {

	}

	csf_log_ex(notice, csf_log_code_notice
		, "app set work_direction[ \"%s\" ] succeed!"
		, get_work_directory().c_str());

	return csf_true;
}


/**
* ���ܣ������豸���Ʋ�ѯָ���豸��ַ
* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
*
* @param mid    ��ʾ�豸����
*/
csf_device* csf_app::find_device(const csf_string& mid) {

	csf_unordered_map<csf_string, csf_device*>::iterator			tmp_iter;


	if (mid.empty()) {
		return csf_false;
	}

	csf_shared_lock<decltype(m_devices_mutex)>			tmp_lock(m_devices_mutex);

	tmp_iter = get_devices().find(mid);
	if (tmp_iter != get_devices().end()) {
		return tmp_iter->second;
	}

	return  csf_nullptr;
}


/**
* ���ܣ������豸�������ָ���豸��ַ���豸�б���
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
*
* @param mid    ��ʾ�豸����
* @param device
*/
csf_bool csf_app::add_device(const csf_string& mid, const csf_device* device) {

	csf_device					*tmp_device = csf_nullptr;


	//У�����ݺϷ���
	if (!device || mid.empty()) {
		return csf_false;
	}

	//���Ҹ����Ƶ��豸�Ƿ����
	tmp_device = find_device(mid);
	if (tmp_device) {
		return csf_false;
	}
	
	csf_unqiue_lock<decltype(m_devices_mutex)>			tmp_lock(m_devices_mutex);

	//�豸��������������豸
	get_devices().insert(csf_unordered_map<csf_string, csf_device*>::value_type((csf_string&)mid, (csf_device*)device));

	return csf_true;
}


/**
* ���ܣ������豸����ɾ��ָ���豸��ַ
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
*
* @param mid    ��ʾ�豸����
*/
csf_bool csf_app::del_device(const csf_string& mid) {
	
	csf_unordered_map<csf_string, csf_device*>::iterator			tmp_iter;


	//У�����ݺϷ���
	if (mid.empty()) {
		return csf_false;
	}

	csf_unqiue_lock<decltype(m_devices_mutex)>			tmp_lock(m_devices_mutex);

	//�����豸����ɾ��
	tmp_iter = get_devices().find(mid);
	if (tmp_iter != get_devices().end()) {
		get_devices().erase(tmp_iter);
		return csf_true;
	}

	return csf_false;
}