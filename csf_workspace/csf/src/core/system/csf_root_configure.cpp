/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_root_configure.hpp
*
*Author: fangzhenmu@aliyun.com
*
*Version: 1.0
*
*Date: 14-7��-2018 11:29:48
*
*Description: Class(csf_root_configure) ��ʾϵͳ�ĸ������ļ�����ģ�飬��Ҫ�������ĸ������ļ����ݡ�
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_root_configure.hpp"
#include "csf_container_convert.hpp"

using csf::core::system::csf_root_configure;


/**
* ��ʾ�������ļ��ļ��б�ڵ��·����Ϣ��
*/
const csf_list<csf_string> csf_root_configure::m_configure_files_items = { "configures", "configure_files" };

/**
* ��ʾ�����ļ��������ַ�������.
*/
const csf_string csf_root_configure::m_configure_file_attribute[] = { "name", "file", "format" };





/**
 * �ú�����Ҫ���ڳ�ʼ��app�������ļ�����ȡ�����ļ��б����������Ϣ��
 * ���أ�true��ʾ��ʼ��������Ϣ�ɹ���false��ʾ��ʼ�������ļ�ʧ�ܡ�
 *
 * @param configure_manager    ��ʾ���������ļ���Ϣ����Ҫ�����Ŀ�����configure_manager
 * @param root_configure_file    ��ʾ��ǰapp�������ļ���Ϣ
 */
csf_bool csf_root_configure::init_configure_manager(csf::core::system::csf_configure_manager& configure_manager, csf_configure_file& root_configure_file) {

	csf_int32							tmp_int_ret = csf_failure;
	csf_element							tmp_element;
	csf_configure						tmp_configure;


	//����������ļ�Ϊ�գ����ʾ����ֱ�ӷ���
	if (root_configure_file.is_null()) {
		csf_log_ex(critical, csf_log_code_critical,
			"root configure file is null");
		return csf_false;
	}

	//�����������ļ�����
	tmp_int_ret = tmp_configure.set_configure_file(root_configure_file);
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(critical, csf_log_code_critical,
			"root configure file error. file[%s:%s].",
			root_configure_file.get_format().c_str(),
			root_configure_file.get_file_path().c_str());
		return csf_false;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice,
			"root configure file parse succeed. file[%s:%s].",
			root_configure_file.get_format().c_str(),
			root_configure_file.get_file_path().c_str());
	}

	//��������configure�����ļ�������ӵ�configure_manager��
	configure_manager.add(tmp_configure);

	//��ȡָ�������ļ��б�Ľڵ�
	tmp_element = tmp_configure.find_element(get_configure_files_items());
	if (tmp_element.is_null()) {
		csf_log_ex(critical, csf_log_code_critical,
			"root configure file format error. not found element[ %s ].",
			csf_container_convert<csf_list<csf_string>>(get_configure_files_items()).to_string().c_str());
		return csf_false;
	}

	//��ʾ���������ӽڵ����ݣ�������Ҫ�������ļ�����
	for (auto &tmp_file : tmp_element.get_children()) {

		if (tmp_file.is_null()) {
			continue;
		}

		//����һ��configure_file����Ϊ����һ�������ļ�
		csf_configure_file			tmp_item_file(
			tmp_file.find(m_configure_file_attribute[csf_root_configure_attribute_string_name]),
			tmp_file.find(m_configure_file_attribute[csf_root_configure_attribute_string_file]),
			tmp_file.find(m_configure_file_attribute[csf_root_configure_attribute_string_format])
		);

		if (tmp_item_file.is_null()) {
			continue;
		}

		//�����������ļ�����
		csf_configure				tmp_item_configure;

		tmp_int_ret = tmp_item_configure.set_configure_file(tmp_item_file);
		if (csf_failure == tmp_int_ret) {
			csf_log_ex(critical, csf_log_code_critical,
				"sub configure file error. file[%s:%s].",
				tmp_item_file.get_format().c_str(),
				tmp_item_file.get_file_path().c_str());
			continue;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"sub configure file parse succeed. file[%s:%s].",
				tmp_item_file.get_format().c_str(),
				tmp_item_file.get_file_path().c_str());
		}

		//��������configure�����ļ�������ӵ�configure_manager��
		configure_manager.add(tmp_item_configure);
	}

	return csf_true;
}