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

