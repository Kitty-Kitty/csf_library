/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_windows_platform.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:54
*
*Description: Class(csf_windows_platform)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_windows_platform.hpp"

using csf::core::system::platform::csf_windows_platform;


csf_windows_platform::csf_windows_platform() {

}



csf_windows_platform::~csf_windows_platform() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_windows_platform::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_windows_platform::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_windows_platform::stop(const csf_configure_manager * conf_mg) {

	return 0;
}