/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_element.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6��-2018 8:49:48
*
*Description: Class(csf_element)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_element.hpp"

using csf::core::system::csf_element;


/**
* ��ʾ����һ��element
* ���أ���null��ʾ�ɹ���null��ʾʧ�ܡ�
*
* @param name    ��ʾ��Ҫ���ҵ�element����
*/
const csf_element& csf_element::find_element(const csf_string& name) {

	csf_element						*tmp_element = csf_nullptr;


	//��ʾ�Ȳ�ѯ�ӽ��
	tmp_element = (csf_element*)&find_child(name);
	if (tmp_element->not_null()) {

		return *tmp_element;
	}

	//����ģ���б鲼�����Ӷ���
	for (csf_element &tmp_iter : get_children()) {

		tmp_element = (csf_element*)&tmp_iter.find_element(name);
		if (tmp_element->not_null()) {
			return *tmp_element;
		}
	}
	return get_null();
}


/**
* ��ʾ����items����·������һ��element��
* ���أ���null��ʾ����items����·���Ľڵ㣻null��ʾû�в��ҵ�����·���Ľڵ㣻
*
* @param items    items����·��
*/
const csf_element& csf_element::find_element(const csf_list<csf_string>& items) {

	csf_element						*tmp_element = this;


	//������������·��Ϊ�գ���ֱ�ӷ��ؿ�
	if (items.empty()) {
		return get_null();
	}

	//��������·������������·���Ľڵ����
	for (csf_string &tmp_item : (csf_list<csf_string>&)items) {
		tmp_element = (csf_element*)&(tmp_element->find_element(tmp_item));
		if (tmp_element->is_null()) {
			return get_null();
		}
	}

	if (tmp_element->not_null()) {
		return *tmp_element;
	}

	return get_null();
}