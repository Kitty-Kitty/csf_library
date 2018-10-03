/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:26
*
*Description: Class(csf_attribute)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute.hpp"
#include "csf_element.hpp"
#include "csf_attribute_printf.h"


using csf::core::system::attribute::csf_attribute;




/**
* ��ʾ��ʼ��csf_attribute��
* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
*
* @param configure_manager    ��ʾ�������ù���������
* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
*/
csf_bool csf_attribute::init(const csf_configure_manager& configure_manager, const csf_string& alias) {

	return csf_true;
	//return process(configure_manager, alias);
}


/**
* ��ʾ�����ù������л�ȡ���������ݡ�
* ���أ�true��ʾ��ȡ��ָ����������ֵ��false��ʾû�л�ȡ����������ֵ��
*
* @param configure_manager    ��ʾ�������ù���������
* @param items    ��ʾ�������·����Ϣ
*/
csf_bool csf_attribute::get_configure(csf_configure_manager& configure_manager, csf_list<csf_string>& items) {

	csf_element					*tmp_element = csf_nullptr;


	//�����ù��������ҷ���·����������ֵ�����ж���ֵ�Ƿ�Ϊ��
	//���ݲ����ڻ�Ϊ�ն����ش���
	tmp_element = (csf_element*)&(configure_manager.find_element(items));
	if (tmp_element->is_null()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"not found element.");
		return csf_false;
	}

	if (tmp_element->get_content().empty()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"element content is null.");
		//return csf_false;
	}
	else {
		set_content(tmp_element->get_content());
	}

	return csf_true;
}


/**
* ��ʾ�����ù������л�ȡ���������ݡ�
* ���أ�true��ʾ��ȡ��ָ����������ֵ��false��ʾû�л�ȡ����������ֵ��
*
* @param configure_manager    ��ʾ�������ù���������
*/
csf_bool csf_attribute::get_configure(csf_configure_manager& configure_manager) {

	//�ж�items�Ƿ�Ϊ�գ����Ϊ�գ������������Ϊitems��
	if (get_items().empty()) {
		if (get_name().empty()) {
			csf_attribute_log(warning, csf_logger_level_warning,
				"items and name is null.");
			return csf_false;
		}
		else {
			get_items().push_back(get_name());
		}
	}

	//����items��ȡ�������ַ���ֵ
	return get_configure(configure_manager, get_items());
}


/**
* ��ʾ�����ù������л�ȡ���������ݡ�
* ���أ�true��ʾ��ȡ��ָ����������ֵ��false��ʾû�л�ȡ����������ֵ��
*
* @param element    ��ʾ�������õ����Զ���
* @param items    ��ʾ�������·����Ϣ
*/
csf_bool csf_attribute::get_configure(csf_element& element, csf_list<csf_string>& items) {

	csf_element				*tmp_element = csf_nullptr;


	if (element.is_null() || items.empty()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"element or items is null.");
		return csf_false;
	}

	//ѭ�����������б����ҷ���·������Ľڵ�
	tmp_element = (csf_element*)&(element.find_element(items));
	if (tmp_element->is_null()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"not found element.");
		return csf_false;
	}

	if (tmp_element->get_content().empty()) {
		csf_attribute_log(warning, csf_logger_level_warning,
			"element content is null.");
		//return csf_false;
	}
	else {
		set_content(tmp_element->get_content());
	}

	return csf_true;
}