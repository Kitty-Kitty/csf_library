/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_network.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:46
*
*Description: Class(csf_network)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_network.hpp"

using csf::core::system::platform::csf_network;


csf_network::csf_network() {

}



csf_network::~csf_network() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_network::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_network::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 
 * @param type
 */
csf::core::base::csf_void csf_network::csf_module(csf::core::module::csf_module_type type) {

}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_network::stop(const csf_configure_manager * conf_mg) {

	return 0;
}