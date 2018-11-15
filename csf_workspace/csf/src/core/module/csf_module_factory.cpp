/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_factory.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 18:45:44
*
*Description: Class(csf_module_factory)
*
*Others:
*
*History:
*******************************************************************************/

#ifdef WIN32
#include <windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#else
#endif

#include "csf_module_factory_printf.h"
#include "csf_module_factory.hpp"

using csf::core::module::csf_module_factory;




/**
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_module_factory::init(const csf_configure_manager* conf_mg) {

	return  csf_succeed;
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_module_factory::start(const csf_configure_manager* conf_mg) {

	return  csf_succeed;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_module_factory::stop(const csf_configure_manager* conf_mg) {

	return  csf_succeed;
}


/**
* 创建模块操作。 返回：非空表示创建的模块地址；空表示错误；
*
* @param conf_mg    表示模块的配置项信息
*/
csf_module * csf_module_factory::create(const csf_configure_manager* conf_mg) {

	csf_module					*tmp_module = csf_nullptr;


	if (!is_load()) {
		if (csf_false == init_handles(get_symbol_path())) {
			return  csf_nullptr;
		}
	}

	//创建一个模块
	tmp_module = get_create_handle()(conf_mg);
	if (!tmp_module) {
		csf_module_factory_log(error, csf_log_code_error, "create module error.");
		return csf_nullptr;
	}
	else {
		set_type(tmp_module->get_type());

		csf_module_factory_log(normal, csf_log_code_normal
			, "create module[%p] succeed."
			, tmp_module);
	}
	//创建成功，则计数加一
	up_count();

	return tmp_module;
}

/**
 * 表示加载动态库模块。 返回：非空（csf_null）表示成功；空(csf_null)表示错误；
 *
 * @param path    表示加载模块的文件路径
 */
csf_void* csf_module_factory::load(const csf_char* path) {

	csf_void					*tmp_ret_handle = csf_nullptr;


	if (!path || csf_strlen(path) <= 0) {
		csf_module_factory_log(error, csf_log_code_error, "path[null]");
		return csf_nullptr;
	}

#if defined(__linux__)
	//tmp_ret_handle = dlopen(pc_cv_stoc(path), RTLD_LAZY | RTLD_GLOBAL);
#if !defined(PLATEFORM_HISIV)
	tmp_ret_handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL | RTLD_DEEPBIND);
#else
	tmp_ret_handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif
	if (!tmp_ret_handle) {
		csf_module_factory_log(error, csf_log_code_error, 
			"dlopen() path[%s] error. reason:%s", path, dlerror());
		return csf_nullptr;
	}
	else {
		csf_module_factory_log(normal, csf_log_code_normal
			, "dlopen() path[%s] succeed."
			, path);
	}

#endif

#ifdef WIN32

	tmp_ret_handle = LoadLibrary(path);
	if (!tmp_ret_handle) {

		DWORD				dwErrorCode = GetLastError();
		const DWORD			dwSize = CSF_MODULE_FACTORY_MAX_ERROR_STRING;
		TCHAR				tcBuffer[dwSize] = { 0, };

		if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			dwErrorCode,
			0,
			tcBuffer,
			dwSize,
			0))	{
			csf_module_factory_log(error, csf_log_code_error,
				"LoadLibrary() path[%s] error. reason:[%d] %s", 
				path, dwErrorCode, tcBuffer);
		}
		else {
			csf_module_factory_log(error, csf_log_code_error,
				"LoadLibrary() path[%s] error. reason:[%d] FormatMessage() failed.", 
				path, dwErrorCode);
		}
		return csf_nullptr;
	}
	else {
		csf_module_factory_log(normal, csf_log_code_normal
			, "LoadLibrary() path[%s] succeed."
			, path);
	}

#endif

	return  tmp_ret_handle;
}


/**
 * 卸载模块句柄
 *
 * @param symbol_handle    表示需要卸载的动态库句柄
 */
csf::core::base::csf_void csf_module_factory::unload(const csf_void* symbol_handle) {

	csf_unqiue_lock<decltype(m_mutex)>					tmp_lock(m_mutex);

	if (is_load()) {
#if defined(__linux__)
		dlclose(get_symbol_handle());
#endif

#ifdef WIN32
		FreeLibrary(HMODULE(get_symbol_handle()));
#endif
		set_create_handle(csf_nullptr);
		set_destroy_handle(csf_nullptr);
		set_symbol_handle(csf_nullptr);

		csf_module_factory_log(normal, csf_log_code_normal
			, "unload succeed.");
	}

}


/**
 * 查找动态库中的符号句柄
 *
 * @param handle    表示动态库文件句柄
 * @param name    表示需要获取的符号名称
 */
csf_void* csf_module_factory::find_symbol(const csf_void* handle, const csf_char* name) {

	csf_void				*tmp_ret_handle = csf_nullptr;


	if (!handle || !name) {
		return csf_nullptr;
	}

#if defined(__linux__)
	tmp_ret_handle = dlsym(get_symbol_handle(), name);
	if (!tmp_ret_handle) {
		csf_module_factory_log(error, csf_log_code_error,
			"dlsym() error. reason:%s", dlerror());
		return csf_nullptr;
	}
	else {
		csf_module_factory_log(normal, csf_log_code_normal,
			"dlsym() succeed.");
	}
#endif

#ifdef WIN32
	tmp_ret_handle = GetProcAddress(HMODULE(get_symbol_handle()), name);
	if (!tmp_ret_handle) {
		DWORD				dwErrorCode = GetLastError();
		const DWORD			dwSize = CSF_MODULE_FACTORY_MAX_ERROR_STRING;
		TCHAR				tcBuffer[dwSize] = {0, };

		if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			dwErrorCode,
			0,
			tcBuffer,
			dwSize,
			0)) {
			csf_module_factory_log(error, csf_log_code_error,
				"GetProcAddress() error. reason:[%d] %s",
				dwErrorCode, tcBuffer);
		}
		else {
			csf_module_factory_log(error, csf_log_code_error,
				"GetProcAddress() error. reason:[%d] FormatMessage() failed.",
				dwErrorCode);
		}
		return csf_nullptr;
	}
	else {
		csf_module_factory_log(normal, csf_log_code_normal,
			"GetProcAddress() succeed.");
	}
#endif

	return  tmp_ret_handle;
}


/**
 * 表示初始化模块的创建和销毁句柄。 返回：true表示成功；false表示错误；
 *
 * @param path    表示加载模块的文件路径
 */
csf_bool csf_module_factory::init_handles(const csf_char* path) {

	csf_void					*tmp_handle = csf_nullptr;
	csf_void					*tmp_create_handle = csf_nullptr;
	csf_void					*tmp_destroy_handle = csf_nullptr;


	if (!path || csf_strlen(path) <= 0) {
		csf_module_factory_log(error, csf_log_code_error, "path[null]");
		return csf_false;
	}

	csf_unqiue_lock<decltype(m_mutex)>					tmp_lock(m_mutex);

	//判断是否已经加载模块
	if (is_load()) {
		return csf_true;
	}
	else {
		//如果未加载，则加载模块，并获取动态库加载返回文件句柄
		tmp_handle = load(path);
		if (!tmp_handle) {
			csf_module_factory_log(error, csf_log_code_error,
				"load path[%s] error. return handle null.",
				path);
		}
		else {
			//配置动态库加载返回文件句柄
			set_symbol_handle(tmp_handle);

			//从动态库中查找需要的create/destroy操作符句柄
			tmp_create_handle = find_symbol(get_symbol_handle(), csf_module_factory_create_handle_name);
			tmp_destroy_handle = find_symbol(get_symbol_handle(), csf_module_factory_destroy_handle_name);
			if (!tmp_create_handle || !tmp_destroy_handle) {
				csf_module_factory_log(error, csf_log_code_error,
					"find create_handle[%p] or destroy_handle[%p] null.",
					tmp_create_handle,
					tmp_destroy_handle);
			}
			else {
				//配置两个操作符(create/destroy)句柄
				set_create_handle((csf::core::module::csf_module_create_handle)tmp_create_handle);
				set_destroy_handle((csf::core::module::csf_module_destroy_handle)tmp_destroy_handle);

				csf_module_factory_log(normal, csf_log_code_normal,
					"find create_handle[%p] or destroy_handle[%p] succeed.",
					tmp_create_handle,
					tmp_destroy_handle);

				return csf_true;
			}
		}
	}	

	return csf_false;
}



/**
* 功能：清空释放所有资源
*/
csf_void csf_module_factory::clear() {

	if (is_load()) {
		unload(get_symbol_handle());
	}
}