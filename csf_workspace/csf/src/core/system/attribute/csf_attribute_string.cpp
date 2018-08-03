/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_string.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7��-2018 14:45:30
*
*Description: Class(csf_attribute_string)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_string.hpp"

using csf::core::system::attribute::csf_attribute_string;





/**
 * ��ʾ����csf_attribute���Բ�����������csf_attribute�в�ͬ���ǣ��������һ��process_attribute������Ҫ��Ϊ��ʵ���쳣��e
 * xception����ͳһ�������쳣����ʱ��ֱ�Ӹ��ݷ��ش��󣬵����쳣��������
 * ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
 * 
 * @param configure_manager    ��ʾ�������ù���������
 * @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
 */
csf_bool csf_attribute_string::process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) {

	//���û�����ĳ�ʼ��������ȡ������ֵ����Ҫ�ǻ�ȡcontent��ֵ
	if (csf_false == csf_attribute::init(configure_manager, alias)) {
		return csf_false;
	}

	set_value(get_content());

	return csf_true;
}