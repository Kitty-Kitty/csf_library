/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_bool.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:26
*
*Description: Class(csf_attribute_bool)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_bool.hpp"

using csf::core::system::attribute::csf_attribute_bool;


csf_attribute_bool::csf_attribute_bool()
	: csf_attribute_template<csf_bool>(csf_attribute::csf_attribute_type_bool, csf_false) {

}



csf_attribute_bool::~csf_attribute_bool() {

}

/**
* ��ʾ����Ϊ���������ݵ��ַ�����ֵ
*/
const csf_string csf_attribute_bool::m_true_string = "true|yes";
/**
* ��ʾ����Ϊ���������ݵ��ַ�����ֵ
*/
const csf_string csf_attribute_bool::m_false_string = "false|no";


/**
* ��ʾ����csf_attribute���Բ�����������csf_attribute�в�ͬ���ǣ��������һ��process_attribute������Ҫ��Ϊ��ʵ���쳣��e
* xception����ͳһ�������쳣����ʱ��ֱ�Ӹ��ݷ��ش��󣬵����쳣��������
* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
*
* @param configure_manager    ��ʾ�������ù���������
* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
*/
csf_bool csf_attribute_bool::process_attribute(const csf_configure_manager& configure_manager
	, const csf_string& alias) {

	//���û�����ĳ�ʼ��������ȡ������ֵ����Ҫ�ǻ�ȡcontent��ֵ
	if (csf_false == csf_attribute::init(configure_manager, alias)) {
		return csf_false;
	}

	//�ж����õ��ַ��Ƿ���true�ַ����У���������ʾtrue
	if (m_true_string.find(get_content()) != m_true_string.npos) {
		set_value(csf_true);
		return csf_true;
	}

	//�ж����õ��ַ��Ƿ���false�ַ����У���������ʾfalse
	if (m_false_string.find(get_content()) != m_false_string.npos) {
		set_value(csf_false);
		return csf_true;
	}

	return csf_false;
}