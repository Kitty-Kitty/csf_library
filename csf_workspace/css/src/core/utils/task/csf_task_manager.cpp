/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:51
*
*Description: Class(csf_task_manager) ��ʾ���������
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_task_manager.hpp"

using csf::core::utils::task::csf_task_manager;


csf_task_manager::csf_task_manager()
	: m_configure_manager(csf_null)
	, m_status(csf_task_status_none) {

}



csf_task_manager::~csf_task_manager() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_task_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_task_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_task_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}