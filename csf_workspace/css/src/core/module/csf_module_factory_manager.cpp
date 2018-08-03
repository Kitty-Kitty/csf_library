/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:45
*
*Description: Class(csf_module_factory_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_module_factory_manager.hpp"


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf::core::module::csf_module_factory_manager::init(const csf_configure_manager * conf_mg) {

	set_configure_manager(conf_mg);
	return csf_success;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf::core::module::csf_module_factory_manager::start(const csf_configure_manager * conf_mg) {

	set_configure_manager(conf_mg);
	return csf_success;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf::core::module::csf_module_factory_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ����ģ�������
* ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
*
* @param name    ��ʾ��Ҫ������ģ������
*/
csf_module * csf::core::module::csf_module_factory_manager::create(const csf_string& name) {

	csf_module_factory				*tmp_module_factory = csf_nullptr;


	//�����Ӧ��ģ�鹤���Ѿ���������ֱ�ӵ���ģ�鹤������ģ�����
	//���û�д��������´���ģ�鹤���������빤�������б���
	tmp_module_factory = find(name);
	if (!tmp_module_factory) {
		csf_unqiue_lock<decltype(m_mutex)>			tmp_lock(m_mutex);

		tmp_module_factory = create_module_factory(name);
		if (!tmp_module_factory) {
			csf_log_ex(error, csf_log_code_error
				, "create moudle[name: %s] failed! reason: create module_factory[name: %s] failed!"
				, name.c_str()
				, name.c_str());
			return csf_nullptr;
		}
		else {
			//���ｫ�´�����ģ�鹤�������뵽ģ�鹤���������У��Է�����ͬģ��Ĵ���
			get_module_factories().insert(csf_unordered_map<csf_string, csf_module_factory*>::value_type(name, tmp_module_factory));
		}
	}

	return tmp_module_factory->create(get_configure_manager());
}


/**
 * ����ģ�������
 * ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
 * 
 * @param type    ��ʾ��Ҫ������ģ������
 */
csf_module * csf::core::module::csf_module_factory_manager::create(const csf_module::csf_module_type type) {

	csf_module_factory				*tmp_module_factory = csf_nullptr;


	tmp_module_factory = find(type);
	if (!tmp_module_factory) {
		csf_log_ex(error, csf_log_code_error
			, "create moudle[type: %d] failed! reason: find module_factory[type: %d] failed!"
			, type
			, type);
		return csf_nullptr;
	}
	else {
		return tmp_module_factory->create(get_configure_manager());
	}
	return csf_nullptr;
}


/**
* ����ģ�������
* ���أ�0��ʾ��ȷ��<0��ʾ�����룻
*
* @param module    ��ʾ��Ҫ���ٵ�ģ���ַ
*/
csf_int32 csf::core::module::csf_module_factory_manager::destory(const csf_module * module) {

	csf_unordered_map<csf_string, csf_module_factory*>::iterator				tmp_iter;


	//У���������ݵĺϷ���
	if (!module || ((csf_module*)module)->get_name().empty()) {
		return csf_failure;
	}

	csf_shared_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//����ģ�鹤��������ģ�����
	tmp_iter = get_module_factories().find(((csf_module*)module)->get_name());
	if (tmp_iter != get_module_factories().end()) {
		if (tmp_iter->second) {
			return tmp_iter->second->destory(module);
		}
	}

	return csf_failure;
}


/**
* ���ܣ�����ģ�����Ʋ���ģ�鹤��
*
* @param name    ģ������
*/
csf_module_factory* csf::core::module::csf_module_factory_manager::find(const csf_string& name) {

	csf_unordered_map<csf_string, csf_module_factory*>::iterator				tmp_iter;


	//У���������ݵĺϷ���
	if (name.empty()) {
		return csf_nullptr;
	}

	csf_shared_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//����ģ�鹤������
	tmp_iter = get_module_factories().find(name);
	if (tmp_iter != get_module_factories().end()) {
		if (tmp_iter->second) {
			return tmp_iter->second;
		}
	}

	return csf_nullptr;
}


/**
* ���ܣ�����ģ�����Ͳ���ģ�鹤��
*
* @param type    ģ������
*/
csf_module_factory* csf::core::module::csf_module_factory_manager::find(const csf::core::module::csf_module::csf_module_type type) {

	//У���������ݵĺϷ���
	if (csf::core::module::csf_module::csf_module_type::csf_module_type_none == type) {
		return csf_nullptr;
	}

	csf_shared_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//����ģ�鹤������
	for (auto &tmp_iter : get_module_factories()) {
		if (tmp_iter.second && type == tmp_iter.second->get_type()) {
			return tmp_iter.second;
		}
	}

	return csf_nullptr;
}


/**
* ���ܣ�����ģ������ƴ���һ��ģ�鹤������
* ���أ��ǿձ�ʾ�ɹ����ձ�ʾʧ�ܣ�
*
* @param name    ��ʾģ�������
*/
csf_module_factory* csf::core::module::csf_module_factory_manager::create_module_factory(const csf_string& name) {

	const csf_module_configure		&tmp_module_configure = get_configure_manager()->find_module_configure(name);


	if (((csf_module_configure&)tmp_module_configure).is_null()) {
		csf_log_ex(error, csf_log_code_error
			, "create module_factory[name: %s] failed! reason: not found module_configure[name: %s]."
			, name.c_str()
			, name.c_str());
		return csf_nullptr;
	}
	else {
		return new csf_module_factory(this, get_configure_manager(), tmp_module_configure);
	}

	return  NULL;
}


/**
* ���ܣ����ٹ����������е�������Դ����Ҫ���Ѿ�������ģ�鹤���б�
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
*/
csf_void csf::core::module::csf_module_factory_manager::clear() {

	csf_unqiue_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//����ģ�鹤������
	for (auto &tmp_iter : get_module_factories()) {
		if (tmp_iter.second) {
			delete tmp_iter.second;
			tmp_iter.second = csf_nullptr;
		}
	}

	get_module_factories().clear();
}
