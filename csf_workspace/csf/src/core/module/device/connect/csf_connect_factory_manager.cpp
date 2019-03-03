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
*Date: 01-10月-2018 12:54:38
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
* 主要功能是：初始化模块管理器
* 返回：0表示成功；非0表示失败；
*
* @param conf_mg    表示配置文件信息
* @param app    表示该模块所属的app对象地址
*/
csf::core::base::csf_int32 csf_connect_factory_manager::init(const csf_configure_manager * conf_mg, const csf_app* app) {

	//判断参数的合法性
	if (csf_nullptr == conf_mg || csf_nullptr == app) {
		csf_log_ex(warning, csf_log_code_warning
			, "invalid parameters confmg[%p] or app[%p] is null."
			, conf_mg
			, app);
		return csf_failure;
	}

	//设置各个参数信息
	set_app(app);
	set_configure_manager(conf_mg);

	return 0;
}


/**
* 主要功能是：启动模块管理器
* 返回：0表示成功；非0表示失败；
*
* @param conf_mg    表示配置文件信息
* @param app    表示该模块所属的app对象地址
*/
csf::core::base::csf_int32 csf_connect_factory_manager::start(const csf_configure_manager * conf_mg, const csf_app* app) {

	//判断参数的合法性
	if (csf_nullptr == conf_mg || csf_nullptr == app) {
		csf_log_ex(warning, csf_log_code_warning
			, "invalid parameters confmg[%p] or app[%p] is null."
			, conf_mg
			, app);
		return csf_failure;
	}

	//根据配置文件信息，创建所有连接工厂对象
	if (csf_false == create_connect_factories(*(const_cast<csf_app*>(app))
		, *(const_cast<csf_configure_manager*>(conf_mg)))) {
		csf_log_ex(warning, csf_log_code_warning
			, "create connect factories failed.");
		return csf_failure;
	}
	else {
		//设置各个参数信息
		set_app(app);
		set_configure_manager(conf_mg);

		csf_log_ex(notice, csf_log_code_notice
			, "create connect factories succeed.");

		return csf_succeed;
	}

	return csf_succeed;
}


/**
* 主要功能是：停止模块管理器
* 返回：0表示成功；非0表示失败；
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_connect_factory_manager::stop(const csf_configure_manager * conf_mg) {

	//销毁所有的连接对象
	for (auto &tmp_iter : get_connectes()) {
		if (m_null_connect_ptr != tmp_iter.second) {
			tmp_iter.second->close();
			tmp_iter.second->stop(conf_mg);
		}
	}
	//清空所有连接对象
	get_connectes().clear();

	if (csf_nullptr != get_app()) {
		//销毁所有连接工厂类对象
		for (auto &tmp_iter : get_factories()) {
			if (csf_nullptr != tmp_iter.second) {
				get_app()->get_module_manager().destory(tmp_iter.second);
			}
		}
		//清空所有连接工厂对象
		get_factories().clear();
	}

	//清空所有处理句柄
	get_handles().clear();

	return 0;
}


/**
* 主要功能是：创建所有的连接工厂类对象
* 返回：0表示成功；非0表示失败；
*
* @param app    表示所属的app信息
* @param configure_manager    表示解析配置文件信息后，需要保存的目标对象configure_manager
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
		//遍历所有子节点内容，添加设备
		for (auto &tmp_elem : tmp_element->get_children()) {

			//表示创建各个连接工厂类对象
			create_connect_factory(app, tmp_elem);
		}
	}

	return csf_true;
}


/**
* 主要功能是：创建一个连接工厂类对象
* 返回：0表示成功；非0表示失败；
*
* @param app    表示所属的app信息
* @param element    表示当前的device节点内容
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

	//判断当前是否为connect_factory节点，如果是则添加设备
	if (CSF_CONFIGURE_STRING(connect_factory) != element.get_name()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not element[%s] not [%s]"
			, element.get_name().c_str()
			, CSF_CONFIGURE_STRING(connect_factory));
		return csf_false;
	}

	//获取name属性信息，判断是否有该属性。如果没有则表示错误，而不需要创建。
	tmp_string_name = element.find_element(csf_list<csf_string>{"name"}).get_content();
	if (tmp_string_name.empty()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element[%s] is null"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"name"}).to_string().c_str());
		return csf_false;
	}

	//创建一个设备对象
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
			//创建网络连接工厂类对象成功
			csf_log_ex(notice, csf_log_code_notice
				, "create factory module[%p name:%s] succeed!"
				, tmp_device_base
				, tmp_string_name.c_str());
		}

		//启动运行网络连接对象
		if (!start_connect_factory(tmp_connect_factory)) {

			csf_log_ex(error, csf_log_code_error
				, "start factory module[%p name:%s] failed!"
				, tmp_device_base
				, tmp_string_name.c_str());

			app.get_module_manager().destory(tmp_device_base);

			return csf_false;
		}

		//根据配置的监听列表信息，创建监听对象
		if (!create_listen_list(app, *tmp_connect_factory, element)) {

			csf_log_ex(error, csf_log_code_error
				, "create listen list failed!");

			return csf_false;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice
				, "create listen list succeed!");
		}

		//将工厂对象添加到列表中
		add_factory(tmp_string_name, tmp_connect_factory);
		app.add_device(tmp_connect_factory->get_mid(), tmp_connect_factory);
	}

	return csf_true;
}


/**
* 主要功能是：启动网络连接工厂对象
* 返回：0表示成功；非0表示失败；
*
* @param connect_factory    表示网络连接工厂对象
*/
csf_bool csf_connect_factory_manager::start_connect_factory(csf_connect_factory* connect_factory) {

	csf_int32				tmp_int_ret = csf_failure;


	if (csf_nullptr == connect_factory) {
		return csf_false;
	}

	//初始化网络连接工厂类对象
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

	//启动网络连接工厂类对象
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
* 主要功能是：创建该连接工厂对象所包含的所有网络连接对象
* 返回：0表示成功；非0表示失败；
*
* @param app    表示所属的app信息
* @param factory    表示当前处理的连接工厂类对象
* @param element    表示当前的device节点内容
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
		//遍历所有子节点内容，添加连接监听对象
		for (auto &tmp_elem : tmp_element->get_children()) {

			//表示创建各个连接监听对象
			create_listen(app, factory, tmp_elem);
		}
	}

	return csf_true;
}


/**
* 主要功能是：创建一个连接类对象
* 返回：0表示成功；非0表示失败
*
* @param app    表示所属的app信息
* @param factory    表示当前处理的连接工厂类对象
* @param element    表示当前的device节点内容
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

	//判断当前是否为listen节点，如果是则添加连接监听对象
	if (CSF_CONFIGURE_STRING(listen) != element.get_name()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not element[%s] not [%s]"
			, element.get_name().c_str()
			, CSF_CONFIGURE_STRING(listen));
		return csf_false;
	}

	//获取name属性信息，判断是否有该属性。如果没有则表示错误，而不需要创建。
	tmp_string_name = element.find_element(csf_list<csf_string>{"name"}).get_content();
	if (tmp_string_name.empty()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element[%s] is null"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"name"}).to_string().c_str());
		return csf_false;
	}

	//获取handle属性信息，判断是否有该属性。如果没有则表示错误，而不需要创建。
	tmp_handle_name = element.find_element(csf_list<csf_string>{"handle"}).get_content();
	if (tmp_handle_name.empty()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element[%s] is null"
			, csf_container_convert<csf_list<csf_string>>(
				csf_list<csf_string>{"handle"}).to_string().c_str());
		return csf_false;
	}
	else {
		//从句柄列表中查询已经注册的操作句柄
		tmp_handle = find_handle(tmp_handle_name);
		if (csf_nullptr == tmp_handle) {

			csf_log_ex(warning, csf_log_code_warning
				, "listen[name:%s handle:%s] handle is null error."
				, tmp_string_name.c_str()
				, tmp_handle_name.c_str());

			return csf_false;
		}
	}

	//创建一个设备对象
	tmp_connect_ptr = create_connect(factory, element);
	if (tmp_connect_ptr == m_null_connect_ptr) {
		csf_log_ex(error, csf_log_code_error
			, "create connect[name:%s] failed!"
			, tmp_string_name.c_str());
		return csf_false;
	}
	else {
		add_connect(tmp_string_name, tmp_connect_ptr);

		//打开监听连接对象
		if (csf_succeed != listen_connect(tmp_connect_ptr, tmp_handle, element)) {

			//打开失败，则删除连接对象
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
* 主要功能是：创建一个连接类对象
* 返回：非m_null_connect_ptr表示成功；m_null_connect_ptr表示失败
*
* @param factory    表示当前处理的连接工厂类对象
* @param element    表示需要创建的连接对象配置信息
*/
csf_connect_ptr csf_connect_factory_manager::create_connect(csf_connect_factory& factory, const csf_element& element) {

	csf_connect_ptr						tmp_connect_ptr = m_null_connect_ptr;
	csf_element							*tmp_element = csf_nullptr;


	if (element.is_null()) {
		csf_log_ex(warning, csf_log_code_warning
			, "element is null");
		return csf_false;
	}

	//判断当前是否为listen节点，如果是则添加连接监听对象
	if (CSF_CONFIGURE_STRING(listen) != element.get_name()) {
		csf_log_ex(warning, csf_log_code_warning
			, "not element[%s] not [%s]"
			, element.get_name().c_str()
			, CSF_CONFIGURE_STRING(listen));
		return csf_false;
	}

	//根据csf_connect:connect_type连接类型名称，查询配置。根据查找到的类型创建连接对象
	for (auto &tmp_iter : csf_connect::get_connect_type_name()) {
		//查找是否存在对应的类型配置信息
		tmp_element = (csf_element*)&(element.find_element(csf_list<csf_string>{tmp_iter.second}));
		if (csf_nullptr == tmp_element || tmp_element->is_null()) {
			continue;
		}
		//根据对应类型创建指定的连接对象
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

		//设置连接的本地地址。主要有两个方面的考虑：1、校验url地址信息是否合法；2、保存解析出来的地址信息；
		if (tmp_connect_ptr->set_local_url(tmp_element->get_content())) {

			//如果设置失败，则销毁连接对象
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
* 主要功能是：表示监听一个连接类对象
* 返回：0表示成功；非0表示失败错误码
*
* @param connect    表示当前处理的连接工厂类对象
* @param handle    表示连接对象的回调句柄
* @param element    表示需要创建的连接对象配置信息
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