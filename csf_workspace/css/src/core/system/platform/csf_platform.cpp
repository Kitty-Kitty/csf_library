/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_platform.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:47
*
*Description: Class(csf_platform)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_platform.hpp"

using csf::core::system::platform::csf_platform;


csf_platform::csf_platform() {

}



csf_platform::~csf_platform() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_platform::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_platform::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 
 * @param type
 */
csf::core::base::csf_void csf_platform::csf_module(csf::core::module::csf_module_type type) {

}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_platform::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ�������
 * 
 * @param new_value
 */
csf::core::base::csf_void csf_platform::set_type(csf::core::module::csf_module_type new_value) {

	m_type = newVal;
}