/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_factory_manager.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 28-7��-2018 14:23:34
*
*Description: Class(csf_connect_factory_manager) ��ʾ���ӹ���������
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_connect_factory_manager.hpp"

using csf::core::module::connect::csf_connect_factory_manager;


csf_connect_factory_manager::csf_connect_factory_manager() {

}



csf_connect_factory_manager::~csf_connect_factory_manager() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_connect_factory_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}
