/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_manager.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 06-7��-2018 19:29:31
*
*Description: Class(csf_attribute_manager)��ʾģ������Թ���������Ҫ�ṩģ����������ͳһ������������ɾ���顢�ĵȡ�
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_manager.hpp"


using csf::core::system::attribute::csf_attribute_manager;


/**
* ��������Ϊ���������ƴ�attribute_manager��ɾ��һ�����ԡ�
* ���أ�true��ʾɾ���ɹ��������ڸ���������Ĭ�Ϸ��سɹ�����false��ʾʧ�ܡ�
*
* @param name    ��ʾ��Ҫɾ������������
*/
csf_bool csf_attribute_manager::del(const csf_char* name) {

	csf_unordered_map<csf_string, csf_attribute*>::iterator		tmp_iter;

	//�����������ݵĺϷ���
	if (!name || csf_strlen(name) <= 0) {
		return csf_false;
	}

	//��ѯ�����������Ƿ��Ѿ����ڣ�����Ѿ������򷵻�ʧ��
	tmp_iter = get_attributes().find(name);
	if (tmp_iter != get_attributes().end()) {

		//���ٶ����ͷ���Դ
		if (tmp_iter->second) {
			delete (tmp_iter->second);
		}
		get_attributes().erase(tmp_iter);
	}

	return csf_true;
}


/**
* ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����ԡ�
* ���أ�һ�����Զ���
*
* @param name    ��ʾ��Ҫ����������
*/
const csf_attribute& csf_attribute_manager::find(const csf_char* name) {

	csf_unordered_map<csf_string, csf_attribute*>::iterator		tmp_iter;

	//�����������ݵĺϷ���
	if (!name || csf_strlen(name) <= 0) {
		return csf_attribute::get_null();
	}

	//��ѯ�����������Ƿ��Ѿ����ڣ�����Ѿ������򷵻�ʧ��
	tmp_iter = get_attributes().find(name);
	if (tmp_iter != get_attributes().end()) {
		if (tmp_iter->second) {
			return *(tmp_iter->second);
		}
	}

	return csf_attribute::get_null();
}

/**
* ��������Ϊ���������ƴ�attribute_manager�в�ѯһ�����Բ������������ݡ�
* ���أ��ַ������ݡ�
*
* @param name    ��ʾ��Ҫ����������
*/
csf_string csf_attribute_manager::get_content(const csf_char* name) {

	csf_attribute			&attr = (csf_attribute &)find(name);


	if (attr.not_null()) {

		return attr.get_content();
	}

	return csf_string_null;
}
