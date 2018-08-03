/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_space_size.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7��-2018 10:47:28
*
*Description: Class(csf_attribute_space_size)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_space_size.hpp"
#include "csf_attribute_printf.h"

using csf::core::system::attribute::csf_attribute_space_size;


/**
* ��ʾ�ռ䵥λ���ƶ���
*/
const csf_unordered_map<csf_string, csf_attribute_space_size::csf_space_size_unit> csf_attribute_space_size::m_unit_name = {
	{ "none", csf_space_size_unit_none },
	{ "B", csf_space_size_unit_b },
	{ "KB", csf_space_size_unit_kb },
	{ "MB", csf_space_size_unit_mb },
	{ "GB", csf_space_size_unit_gb },
	{ "TB", csf_space_size_unit_tb },
	{ "PB", csf_space_size_unit_pb }
};
/**
* ��ʾ���ָ�ʽ���ݵ�˵��
*/
const csf_string csf_attribute_space_size::m_usage = "usage: number unit(B|KB|MB|GB|TB|PB) . for example: 100MB";
/**
 * �������н�����Ҫ�Ĳ�����
 * ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
 * 
 * @param content    ��ʾ��Ҫ������������Ϣ
 */
csf_bool csf_attribute_space_size::parse_parametes(const csf_string& content) {

	/**
	* ��ʾ�����ʽ�ͽ�ȡ�ַ���������ʽ
	*/
	std::regex					tmp_regex("(\\d+)(B|KB|MB|GB|TB|PB)");
	std::smatch					tmp_match_result;


	if (content.empty()) {
		return csf_false;
	}

	//ʹ��������ʽ�������ݽṹ����ȡ����
	if (!std::regex_match(content, tmp_match_result, tmp_regex)) {
		//������ʽƥ��ʧ�ܣ���ʾ���ݸ�ʽ����
		csf_attribute_log(warning, csf_log_code_warning
			, "content format error. %s"
			, get_usage().c_str());
		return csf_false;
	}
	else {
		//���match��ȡ�Ĳ���С�ڵ�����Ҫ�Ĳ������������ʾ����
		if (tmp_match_result.size() <= csf_attribute_space_size_parametes_size) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. parametes number[%d <= %d]. %s"
				, tmp_match_result.size()
				, csf_attribute_space_size_parametes_size
				, get_usage().c_str());
			return csf_false;
		}

		//��ȡ"100KB"��ʽ�����е�"100","KB"�����ַ��Ρ�
		//����tmp_match_result[1]��1����"100"��ֵ���ݣ�
		//����tmp_match_result[2]��2����"KB"�ĵ�λ���ݣ�
		if (!get_parametes(tmp_match_result[1].str(), tmp_match_result[2].str())) {
			csf_attribute_log(warning, csf_log_code_warning,
				, "content format error. get parametes failed. %s"
				, get_usage().c_str());
			return csf_false;
		}
	}
	return csf_true;
}


/**
 * ��ȡ��ֵ�͵�λ������ݡ�
 * ���أ�true��ʾ����ɹ���false��ʾ����ʧ�ܡ�
 * 
 * @param val    ��ʾ��Ҫ�������ֵ����
 * @param unit    ��ʾ����ֵ�ĵ�λ�ַ�
 */
csf_bool csf_attribute_space_size::get_parametes(const csf_string& val, const csf_string& unit) {

	csf_int64											tmp_value = 0;
	csf_int64											tmp_dest = 0;
	csf_attribute_space_size::csf_space_size_unit		tmp_unit = csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_none;


	//�������ݵĺϷ��ԡ����������ֵΪ�գ��򷵻ش���
	if (val.empty() || unit.empty()) {
		csf_attribute_log(warning, csf_log_code_warning,
			"value[%s] or unit[%s] is null.",
			val.c_str(),
			unit.c_str());
		return csf_false;
	}

	//���ַ�����ʱ�䵥λ��ʽת��Ϊ�������͵�λ
	tmp_unit = convert(unit);
	if (csf_attribute_space_size::csf_space_size_unit::csf_space_size_unit_none == tmp_unit) {
		csf_attribute_log(warning, csf_log_code_warning,
			"unit[%s] unknow.",
			unit.c_str());
		return csf_false;
	}

	//���ַ�������ת��Ϊint64��ʽ����ֵ
	tmp_value = csf_atoint64(val.c_str());
	if (tmp_value < 0) {
		csf_attribute_log(warning, csf_log_code_warning,
			"value[%s] convert failed.",
			val.c_str());
		return csf_false;
	}

	//��Դʱ�䵥λ����ת��ΪĿ�굥λʱ������
	if (csf_false == convert(tmp_dest, get_unit(), tmp_value, tmp_unit)) {
		csf_attribute_log(warning, csf_log_code_warning,
			"convert time format failed.");
		return csf_false;
	}
	else {
		//���ת���ɹ��򱣴�����
		set_value(tmp_dest);
	}

	return csf_true;
}


/**
 * ��ʾ����csf_attribute���Բ�����������csf_attribute_template�в�ͬ���ǣ��������һ��process_number������Ҫ��Ϊ��
 * ʵ�����ݱ߽��ͳһ����
 * ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
 * 
 * @param configure_manager    ��ʾ�������ù���������
 * @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
 */
csf_bool csf_attribute_space_size::process_number(const csf_configure_manager& configure_manager, const csf_string& alias) {

	csf_string					tmp_content = "";


	//���û�����ĳ�ʼ��������ȡ������ֵ����Ҫ�ǻ�ȡcontent��ֵ
	if (csf_false == csf_attribute::init(configure_manager, alias)) {
		return csf_false;
	}

	//ɾ�������е����пհ��ַ�
	tmp_content = shrink(get_content());
	if (tmp_content.empty()) {
		csf_attribute_log(warning, csf_log_code_warning,
			"content is null.");
		return csf_false;
	}

	//�����������ļ��ж�ȡ����������
	if (csf_false == parse_parametes(tmp_content)) {
		return csf_false;
	}

	return csf_true;
}