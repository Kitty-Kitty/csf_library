/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:43
*
*Description: Class(csf_manager)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_manager.hpp"

using csf::core::module::csf_manager;


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}