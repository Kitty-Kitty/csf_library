/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_linux_platform.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:42
*
*Description: Class(csf_linux_platform)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_linux_platform.hpp"

using csf::core::system::platform::csf_linux_platform;


csf_linux_platform::csf_linux_platform() {

}



csf_linux_platform::~csf_linux_platform() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_linux_platform::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_linux_platform::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_linux_platform::stop(const csf_configure_manager * conf_mg) {

	return 0;
}