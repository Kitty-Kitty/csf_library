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
*Date: 01-7��-2018 18:45:44
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
 * ģ���ʼ��
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_module_factory::init(const csf_configure_manager* conf_mg) {

	return  csf_succeed;
}


/**
 * ģ������
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_module_factory::start(const csf_configure_manager* conf_mg) {

	return  csf_succeed;
}


/**
 * ģ��ֹͣ
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_module_factory::stop(const csf_configure_manager* conf_mg) {

	return  csf_succeed;
}


/**
* ����ģ������� ���أ��ǿձ�ʾ������ģ���ַ���ձ�ʾ����
*
* @param conf_mg    ��ʾģ�����������Ϣ
*/
csf_module * csf_module_factory::create(const csf_configure_manager* conf_mg) {

	csf_module					*tmp_module = csf_nullptr;


	if (!is_load()) {
		if (csf_false == init_handles(get_symbol_path())) {
			return  csf_nullptr;
		}
	}

	//����һ��ģ��
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
	//�����ɹ����������һ
	up_count();

	return tmp_module;
}

/**
 * ��ʾ���ض�̬��ģ�顣 ���أ��ǿգ�csf_null����ʾ�ɹ�����(csf_null)��ʾ����
 *
 * @param path    ��ʾ����ģ����ļ�·��
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
 * ж��ģ����
 *
 * @param symbol_handle    ��ʾ��Ҫж�صĶ�̬����
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
 * ���Ҷ�̬���еķ��ž��
 *
 * @param handle    ��ʾ��̬���ļ����
 * @param name    ��ʾ��Ҫ��ȡ�ķ�������
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
 * ��ʾ��ʼ��ģ��Ĵ��������پ���� ���أ�true��ʾ�ɹ���false��ʾ����
 *
 * @param path    ��ʾ����ģ����ļ�·��
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

	//�ж��Ƿ��Ѿ�����ģ��
	if (is_load()) {
		return csf_true;
	}
	else {
		//���δ���أ������ģ�飬����ȡ��̬����ط����ļ����
		tmp_handle = load(path);
		if (!tmp_handle) {
			csf_module_factory_log(error, csf_log_code_error,
				"load path[%s] error. return handle null.",
				path);
		}
		else {
			//���ö�̬����ط����ļ����
			set_symbol_handle(tmp_handle);

			//�Ӷ�̬���в�����Ҫ��create/destroy���������
			tmp_create_handle = find_symbol(get_symbol_handle(), csf_module_factory_create_handle_name);
			tmp_destroy_handle = find_symbol(get_symbol_handle(), csf_module_factory_destroy_handle_name);
			if (!tmp_create_handle || !tmp_destroy_handle) {
				csf_module_factory_log(error, csf_log_code_error,
					"find create_handle[%p] or destroy_handle[%p] null.",
					tmp_create_handle,
					tmp_destroy_handle);
			}
			else {
				//��������������(create/destroy)���
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
* ���ܣ�����ͷ�������Դ
*/
csf_void csf_module_factory::clear() {

	if (is_load()) {
		unload(get_symbol_handle());
	}
}