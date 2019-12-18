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
*Date: 27-6月-2018 17:28:45
*
*Description: Class(csf_module_factory_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_module_factory_manager.hpp"


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf::core::module::csf_module_factory_manager::init(const csf_configure_manager * conf_mg) {

	set_configure_manager(conf_mg);
	return csf_success;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf::core::module::csf_module_factory_manager::start(const csf_configure_manager * conf_mg) {

	set_configure_manager(conf_mg);
	return csf_success;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf::core::module::csf_module_factory_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* 创建模块操作。
* 返回：非空表示创建的模块地址；空表示错误；
*
* @param name    表示需要创建的模块名称
*/
csf_module * csf::core::module::csf_module_factory_manager::create(const csf_string& name) {

	csf_module_factory				*tmp_module_factory = csf_nullptr;


	//如果对应的模块工厂已经创建，则直接调用模块工厂创建模块对象
	//如果没有创建则重新创建模块工厂，并插入工厂管理列表中
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
			//这里将新创建的模块工厂，插入到模块工厂管理器中，以方便相同模块的创建
			get_module_factories().insert(csf_unordered_map<csf_string, csf_module_factory*>::value_type(name, tmp_module_factory));
		}
	}

	return tmp_module_factory->create(get_configure_manager());
}


/**
 * 创建模块操作。
 * 返回：非空表示创建的模块地址；空表示错误；
 * 
 * @param type    表示需要创建的模块类型
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
* 销毁模块操作。
* 返回：0表示正确；<0表示错误码；
*
* @param module    表示需要销毁的模块地址
*/
csf_int32 csf::core::module::csf_module_factory_manager::destory(const csf_module * module) {

	csf_unordered_map<csf_string, csf_module_factory*>::iterator				tmp_iter;


	//校验输入数据的合法性
	if (!module || ((csf_module*)module)->get_name().empty()) {
		return csf_failure;
	}

	csf_shared_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//查找模块工厂，销毁模块对象
	tmp_iter = get_module_factories().find(((csf_module*)module)->get_name());
	if (tmp_iter != get_module_factories().end()) {
		if (tmp_iter->second) {
			return tmp_iter->second->destory(module);
		}
	}

	return csf_failure;
}


/**
* 功能：根据模块名称查找模块工厂
*
* @param name    模块名称
*/
csf_module_factory* csf::core::module::csf_module_factory_manager::find(const csf_string& name) {

	csf_unordered_map<csf_string, csf_module_factory*>::iterator				tmp_iter;


	//校验输入数据的合法性
	if (name.empty()) {
		return csf_nullptr;
	}

	csf_shared_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//查找模块工厂对象
	tmp_iter = get_module_factories().find(name);
	if (tmp_iter != get_module_factories().end()) {
		if (tmp_iter->second) {
			return tmp_iter->second;
		}
	}

	return csf_nullptr;
}


/**
* 功能：根据模块类型查找模块工厂
*
* @param type    模块类型
*/
csf_module_factory* csf::core::module::csf_module_factory_manager::find(const csf::core::module::csf_module::csf_module_type type) {

	//校验输入数据的合法性
	if (csf::core::module::csf_module::csf_module_type::csf_module_type_none == type) {
		return csf_nullptr;
	}

	csf_shared_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//查找模块工厂对象
	for (auto &tmp_iter : get_module_factories()) {
		if (tmp_iter.second && type == tmp_iter.second->get_type()) {
			return tmp_iter.second;
		}
	}

	return csf_nullptr;
}


/**
* 功能：根据模块的名称创建一个模块工厂对象
* 返回：非空表示成功；空表示失败；
*
* @param name    表示模块的名称
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
* 功能：销毁工厂管理器中的所有资源，主要是已经创建的模块工厂列表。
* 返回：true表示成功；false表示失败；
*/
csf_void csf::core::module::csf_module_factory_manager::clear() {

	csf_unqiue_lock<decltype(m_mutex)>				tmp_lock(m_mutex);

	//查找模块工厂对象
	for (auto &tmp_iter : get_module_factories()) {
		if (tmp_iter.second) {
			delete tmp_iter.second;
			tmp_iter.second = csf_nullptr;
		}
	}

	get_module_factories().clear();
}
