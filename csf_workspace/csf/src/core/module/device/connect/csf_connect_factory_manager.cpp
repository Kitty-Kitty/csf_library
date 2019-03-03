/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:38
*
*Description: Class(csf_connect_factory_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_configure_module.hpp"
#include "csf_connect_factory_manager.hpp"

using csf::core::module::connect::csf_connect_factory_manager;


/**
* ��Ҫ�����ǣ���ʼ��ģ�������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
* @param app    ��ʾ��ģ��������app�����ַ
*/
csf::core::base::csf_int32 csf_connect_factory_manager::init(const csf_configure_manager * conf_mg, const csf_app* app) {

	//�жϲ����ĺϷ���
	if (csf_nullptr == conf_mg || csf_nullptr == app) {
		csf_log_ex(warning, csf_log_code_warning
			, "invalid parameters confmg[%p] or app[%p] is null."
			, conf_mg
			, app);
		return csf_failure;
	}

	//���ø���������Ϣ
	set_app(app);
	set_configure_manager(conf_mg);

	return 0;
}


/**
* ��Ҫ�����ǣ�����ģ�������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
* @param app    ��ʾ��ģ��������app�����ַ
*/
csf::core::base::csf_int32 csf_connect_factory_manager::start(const csf_configure_manager * conf_mg, const csf_app* app) {

	//�жϲ����ĺϷ���
	if (csf_nullptr == conf_mg || csf_nullptr == app) {
		csf_log_ex(warning, csf_log_code_warning
			, "invalid parameters confmg[%p] or app[%p] is null."
			, conf_mg
			, app);
		return csf_failure;
	}

	//���������ļ���Ϣ�������������ӹ�������
	if (csf_false == create_connect_factories(*(const_cast<csf_app*>(app))
		, *(const_cast<csf_configure_manager*>(conf_mg)))) {
		csf_log_ex(warning, csf_log_code_warning
			, "create connect factories failed.");
		return csf_failure;
	}
	else {
		//���ø���������Ϣ
		set_app(app);
		set_configure_manager(conf_mg);

		csf_log_ex(notice, csf_log_code_notice
			, "create connect factories succeed.");

		return csf_succeed;
	}

	return csf_succeed;
}


/**
* ��Ҫ�����ǣ�ֹͣģ�������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 csf_connect_factory_manager::stop(const csf_configure_manager * conf_mg) {

	//�������е����Ӷ���
	for (auto &tmp_iter : get_connectes()) {
		if (m_null_connect_ptr != tmp_iter.second) {
			tmp_iter.second->close();
			tmp_iter.second->stop(conf_mg);
		}
	}
	//����������Ӷ���
	get_connectes().clear();

	if (csf_nullptr != get_app()) {
		//�����������ӹ��������
		for (auto &tmp_iter : get_factories()) {
			if (csf_nullptr != tmp_iter.second) {
				get_app()->get_module_manager().destory(tmp_iter.second);
			}
		}
		//����������ӹ�������
		get_factories().clear();
	}

	//������д�����
	get_handles().clear();

	return 0;
}


/**
* ��Ҫ�����ǣ��������е����ӹ��������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param app    ��ʾ������app��Ϣ
* @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
*/
csf_bool csf_connect_factory_manager::create_connect_factories(csf_app& app, csf_configure_manager& configure_manager) {

	csf_element				*tmp_element = csf_nullptr;


	tmp_element = (csf_element *)&(configure_manager.find_element(
		csf_list<csf_string>{"connect_configure", "connect_factory_manager"}));
	if (tmp_element->is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not found element[%s]"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"connect_configure", "connect_factory_manager"}).to_string().c_str());
		return csf_true;
	}
	else {
		//���������ӽڵ����ݣ�����豸
		for (auto &tmp_elem : tmp_element->get_children()) {

			//��ʾ�����������ӹ��������
			create_connect_factory(app, tmp_elem);
		}
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ�����һ�����ӹ��������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param app    ��ʾ������app��Ϣ
* @param element    ��ʾ��ǰ��device�ڵ�����
*/
csf_bool csf_connect_factory_manager::create_connect_factory(csf_app& app, const csf_element& element) {

	csf_device_base				*tmp_device_base = csf_nullptr;
	csf_connect_factory			*tmp_connect_factory = csf_nullptr;
	csf_string					tmp_string_name = "";


	if (element.is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element is null");
		return csf_false;
	}

	//�жϵ�ǰ�Ƿ�Ϊconnect_factory�ڵ㣬�����������豸
	if (CSF_CONFIGURE_STRING(connect_factory) != element.get_name()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not element[%s] not [%s]"
			, element.get_name().c_str()
			, CSF_CONFIGURE_STRING(connect_factory));
		return csf_false;
	}

	//��ȡname������Ϣ���ж��Ƿ��и����ԡ����û�����ʾ���󣬶�����Ҫ������
	tmp_string_name = element.find_element(csf_list<csf_string>{"name"}).get_content();
	if (tmp_string_name.empty()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element[%s] is null"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"name"}).to_string().c_str());
		return csf_false;
	}

	//����һ���豸����
	tmp_device_base = csf_configure_module::create_module(&app, app.get_module_manager(), element);
	if (csf_nullptr == tmp_device_base) {
		csf_log_ex(error, csf_log_code_error
			, "create factory module[name:%s] failed!"
			, tmp_string_name.c_str());
		return csf_false;
	}
	else {
		tmp_connect_factory = dynamic_cast<csf_connect_factory*>(tmp_device_base);
		if (!tmp_connect_factory || !csf_device_base::is_device(tmp_device_base->get_type())) {
			csf_log_ex(error, csf_log_code_error
				, "create factory module[name:%s] failed! not \"csf_connect_factory\" module."
				, tmp_string_name.c_str());
			return csf_false;
		}
		else {
			//�����������ӹ��������ɹ�
			csf_log_ex(notice, csf_log_code_notice
				, "create factory module[%p name:%s] succeed!"
				, tmp_device_base
				, tmp_string_name.c_str());
		}

		//���������������Ӷ���
		if (!start_connect_factory(tmp_connect_factory)) {

			csf_log_ex(error, csf_log_code_error
				, "start factory module[%p name:%s] failed!"
				, tmp_device_base
				, tmp_string_name.c_str());

			app.get_module_manager().destory(tmp_device_base);

			return csf_false;
		}

		//�������õļ����б���Ϣ��������������
		if (!create_listen_list(app, *tmp_connect_factory, element)) {

			csf_log_ex(error, csf_log_code_error
				, "create listen list failed!");

			return csf_false;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice
				, "create listen list succeed!");
		}

		//������������ӵ��б���
		add_factory(tmp_string_name, tmp_connect_factory);
		app.add_device(tmp_connect_factory->get_mid(), tmp_connect_factory);
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ������������ӹ�������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param connect_factory    ��ʾ�������ӹ�������
*/
csf_bool csf_connect_factory_manager::start_connect_factory(csf_connect_factory* connect_factory) {

	csf_int32				tmp_int_ret = csf_failure;


	if (csf_nullptr == connect_factory) {
		return csf_false;
	}

	//��ʼ���������ӹ��������
	tmp_int_ret = connect_factory->init(get_configure_manager());
	if (csf_failure == tmp_int_ret) {

		csf_log_ex(error, csf_log_code_error
			, "init connect factory %s failed!"
			, connect_factory->to_string().c_str());

		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "init connect factory %s succeed!"
			, connect_factory->to_string().c_str());
	}

	//�����������ӹ��������
	tmp_int_ret = connect_factory->start(get_configure_manager());
	if (csf_failure == tmp_int_ret) {

		csf_log_ex(error, csf_log_code_error
			, "start connect factory %s failed!"
			, connect_factory->to_string().c_str());

		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "start connect factory %s succeed!"
			, connect_factory->to_string().c_str());
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ����������ӹ��������������������������Ӷ���
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param app    ��ʾ������app��Ϣ
* @param factory    ��ʾ��ǰ��������ӹ��������
* @param element    ��ʾ��ǰ��device�ڵ�����
*/
csf_bool csf_connect_factory_manager::create_listen_list(csf_app& app
	, csf_connect_factory& factory
	, const csf_element& element) {

	csf_element				*tmp_element = csf_nullptr;


	tmp_element = (csf_element *)&(element.find_element(csf_list<csf_string>{"listen_list"}));
	if (tmp_element->is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not found element[%s]"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"listen_list"}).to_string().c_str());
		return csf_true;
	}
	else {
		//���������ӽڵ����ݣ�������Ӽ�������
		for (auto &tmp_elem : tmp_element->get_children()) {

			//��ʾ�����������Ӽ�������
			create_listen(app, factory, tmp_elem);
		}
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ�����һ�����������
* ���أ�0��ʾ�ɹ�����0��ʾʧ��
*
* @param app    ��ʾ������app��Ϣ
* @param factory    ��ʾ��ǰ��������ӹ��������
* @param element    ��ʾ��ǰ��device�ڵ�����
*/
csf_bool csf_connect_factory_manager::create_listen(csf_app& app, csf_connect_factory& factory, const csf_element& element) {

	csf_connect_ptr				tmp_connect_ptr = m_null_connect_ptr;
	csf_connect_callback		tmp_handle = csf_nullptr;
	csf_string					tmp_handle_name = "";
	csf_string					tmp_string_name = "";


	if (element.is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element is null");
		return csf_false;
	}

	//�жϵ�ǰ�Ƿ�Ϊlisten�ڵ㣬�������������Ӽ�������
	if (CSF_CONFIGURE_STRING(listen) != element.get_name()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not element[%s] not [%s]"
			, element.get_name().c_str()
			, CSF_CONFIGURE_STRING(listen));
		return csf_false;
	}

	//��ȡname������Ϣ���ж��Ƿ��и����ԡ����û�����ʾ���󣬶�����Ҫ������
	tmp_string_name = element.find_element(csf_list<csf_string>{"name"}).get_content();
	if (tmp_string_name.empty()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element[%s] is null"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"name"}).to_string().c_str());
		return csf_false;
	}

	//��ȡhandle������Ϣ���ж��Ƿ��и����ԡ����û�����ʾ���󣬶�����Ҫ������
	tmp_handle_name = element.find_element(csf_list<csf_string>{"handle"}).get_content();
	if (tmp_handle_name.empty()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element[%s] is null"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"handle"}).to_string().c_str());
		return csf_false;
	}
	else {
		//�Ӿ���б��в�ѯ�Ѿ�ע��Ĳ������
		tmp_handle = find_handle(tmp_handle_name);
		if (csf_nullptr == tmp_handle) {

			csf_log_ex(warning, csf_log_code_warning
				, "listen[name:%s handle:%s] handle is null error."
				, tmp_string_name.c_str()
				, tmp_handle_name.c_str());

			return csf_false;
		}
	}

	//����һ���豸����
	tmp_connect_ptr = create_connect(factory, element);
	if (tmp_connect_ptr == m_null_connect_ptr) {
		csf_log_ex(error, csf_log_code_error
			, "create connect[name:%s] failed!"
			, tmp_string_name.c_str());
		return csf_false;
	}
	else {
		add_connect(tmp_string_name, tmp_connect_ptr);

		//�򿪼������Ӷ���
		if (csf_succeed != listen_connect(tmp_connect_ptr, tmp_handle, element)) {

			//��ʧ�ܣ���ɾ�����Ӷ���
			remove_connect(tmp_string_name);

			csf_log_ex(error, csf_log_code_error
				, "listen connect[name:%s] failed!"
				, tmp_string_name.c_str());

			return csf_false;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice
				, "listen connect[name:%s] succeed!"
				, tmp_string_name.c_str());
		}
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ�����һ�����������
* ���أ���m_null_connect_ptr��ʾ�ɹ���m_null_connect_ptr��ʾʧ��
*
* @param factory    ��ʾ��ǰ��������ӹ��������
* @param element    ��ʾ��Ҫ���������Ӷ���������Ϣ
*/
csf_connect_ptr csf_connect_factory_manager::create_connect(csf_connect_factory& factory, const csf_element& element) {

	csf_connect_ptr						tmp_connect_ptr = m_null_connect_ptr;
	csf_element							*tmp_element = csf_nullptr;


	if (element.is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element is null");
		return csf_false;
	}

	//�жϵ�ǰ�Ƿ�Ϊlisten�ڵ㣬�������������Ӽ�������
	if (CSF_CONFIGURE_STRING(listen) != element.get_name()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not element[%s] not [%s]"
			, element.get_name().c_str()
			, CSF_CONFIGURE_STRING(listen));
		return csf_false;
	}

	//����csf_connect:connect_type�����������ƣ���ѯ���á����ݲ��ҵ������ʹ������Ӷ���
	for (auto &tmp_iter : csf_connect::get_connect_type_name()) {
		//�����Ƿ���ڶ�Ӧ������������Ϣ
		tmp_element = (csf_element*)&(element.find_element(csf_list<csf_string>{tmp_iter.second}));
		if (csf_nullptr == tmp_element || tmp_element->is_null()) {
			continue;
		}
		//���ݶ�Ӧ���ʹ���ָ�������Ӷ���
		tmp_connect_ptr = factory.create(tmp_iter.first);
		if (tmp_connect_ptr == m_null_connect_ptr) {

			csf_log_ex(error, csf_log_code_error
				, "create connect[type:%d type_name:%s url:%s] failed!"
				, tmp_iter.first
				, tmp_iter.second.c_str()
				, tmp_element->get_content().c_str());

			return m_null_connect_ptr;
		}
		else {
			tmp_connect_ptr->set_factory(&factory);

			csf_log_ex(notice, csf_log_code_notice
				, "create connect[%p type:%d type_name:%s url:%s] succeed!"
				, &tmp_connect_ptr
				, tmp_iter.first
				, tmp_iter.second.c_str()
				, tmp_element->get_content().c_str());
		}

		//�������ӵı��ص�ַ����Ҫ����������Ŀ��ǣ�1��У��url��ַ��Ϣ�Ƿ�Ϸ���2��������������ĵ�ַ��Ϣ��
		if (tmp_connect_ptr->set_local_url(tmp_element->get_content())) {

			//�������ʧ�ܣ����������Ӷ���
			factory.destroy(tmp_connect_ptr);

			csf_log_ex(error, csf_log_code_error
				, "create connect[type:%d type_name:%s url:%s] failed! reason:set_local_url() failed!"
				, tmp_iter.first
				, tmp_iter.second.c_str()
				, tmp_element->get_content().c_str());

			return m_null_connect_ptr;
		}

		return tmp_connect_ptr;
	}

	csf_log_ex(error, csf_log_code_error
		, "create connect failed! reason:not find connect by type!");

	return m_null_connect_ptr;
}


/**
* ��Ҫ�����ǣ���ʾ����һ�����������
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܴ�����
*
* @param connect    ��ʾ��ǰ��������ӹ��������
* @param handle    ��ʾ���Ӷ���Ļص����
* @param element    ��ʾ��Ҫ���������Ӷ���������Ϣ
*/
csf::core::base::csf_int32 csf_connect_factory_manager::listen_connect(csf_connect_ptr& connect
	, csf_connect_callback handle
	, const csf_element& element) {

	csf_int32			tmp_int_value = 0;


	tmp_int_value = connect->listen(connect->get_local_url(), handle);
	if (tmp_int_value) {

		csf_log_ex(error, csf_log_code_error
			, "listen connect[%p url:%s] failed!"
			, &connect
			, connect->get_local_url().get_url().c_str());

		return tmp_int_value;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "listen connect[%p url:%s] succeed!"
			, &connect
			, connect->get_local_url().get_url().c_str());
	}

	return csf_succeed;
}