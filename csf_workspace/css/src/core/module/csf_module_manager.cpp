/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_manager.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 01-7��-2018 19:12:21
*
*Description: Class(csf_module_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_module_manager.hpp"



/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf::core::module::csf_module_manager::init(const csf_configure_manager * conf_mg) {

	set_configure_manager(conf_mg);

	return csf_success;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf::core::module::csf_module_manager::start(const csf_configure_manager * conf_mg) {

	csf_int32					tmp_int_ret = csf_failure;


	set_configure_manager(conf_mg);

	//��ʼ��ģ�鹤��������
	tmp_int_ret = get_module_factory_manager().init(conf_mg);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error, "init factory manager failed!");
		return csf_failure;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "init factory manager succeed!");
	}

	//����ģ�鹤��������
	tmp_int_ret = get_module_factory_manager().start(conf_mg);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error, "start factory manager failed!");
		return csf_failure;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice, "start factory manager succeed!");
	}

	return csf_success;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf::core::module::csf_module_manager::stop(const csf_configure_manager * conf_mg) {

	return csf_success;
}


/**
* ���ܣ����ģ������б��е�����ģ�����
*/
csf_void csf::core::module::csf_module_manager::clear() {

	csf_unqiue_lock<decltype(m_mutex)>			tmp_lock(m_mutex);

	for (auto &tmp_iter : get_modules()) {
		if (tmp_iter) {
			get_module_factory_manager().destory(tmp_iter);
		}
	}

	get_modules().clear();
}
