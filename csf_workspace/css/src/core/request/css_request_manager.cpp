/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: css_request_manager.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:30
*
*Description: Class(css_request_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "css_request_manager.hpp"

using css::core::css_request_manager;


css_request_manager::css_request_manager() {

}



css_request_manager::~css_request_manager() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_request_manager::init(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_request_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 css_request_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�̴߳���������Ҫ�Ӷ����л�ȡ������д���
 */
csf_void css_request_manager::process() {

}