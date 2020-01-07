/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device_base.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:40
*
*Description: Class(csf_device_base)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_device_base.hpp"

using csf::core::module::csf_device_base;



/**
* ���ܣ�
*    ���ݸ���������������ø����ýڵ�
* ���أ�
*    true  �� ��ʾ�ɹ���
*    false �� ��ʾʧ�ܣ�
*
* @param root_configure_name    ��ʾ���ڵ�����
*/
csf_bool csf_device_base::update_root_configure_by_name(csf_string root_configure_name) {

	csf::core::system::csf_element	*tmp_element = csf_nullptr;


	if (root_configure_name.empty()) {
		return csf_false;
	}

	tmp_element = const_cast<csf::core::system::csf_element*>(
		&(get_configure_manager()->find_element(
			csf_list<csf_string>{root_configure_name})));
	if (!tmp_element || tmp_element->is_null()) {
		return csf_false;
	}
	else {
		get_attribute_manager().set_root_element(tmp_element);
		return csf_true;
	}

	return csf_false;
}

