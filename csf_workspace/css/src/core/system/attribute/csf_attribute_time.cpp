/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_time.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:55:12
*
*Description: Class(csf_attribute_time)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_time.hpp"
#include "csf_attribute_printf.h"

using csf::core::system::attribute::csf_attribute_time;



/**
* ��ʾʱ�䵥λ���ƶ���
*/
const csf_unordered_map<csf_string, csf_attribute_time::csf_time_unit> csf_attribute_time::m_unit_name = {
	{ "none", csf_time_unit_none},
	{ "ns", csf_time_unit_ns},
	{ "us", csf_time_unit_us},
	{ "ms", csf_time_unit_ms},
	{ "s", csf_time_unit_s},
	{ "m", csf_time_unit_m},
	{ "h", csf_time_unit_h},
	{ "d", csf_time_unit_d}
};

/**
* ��ʾ���ָ�ʽ���ݵ�˵��
*/
const csf_string csf_attribute_time::m_usage = "usage: number unit(ns|us|ms|s|m|h|d) . for example: 10s";

/**
* �������н�����Ҫ�Ĳ�����
* ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
*
* @param content    ��ʾ��Ҫ������������Ϣ
*/
csf_bool csf_attribute_time::parse_parametes(const csf_string& content) {

	/**
	* ��ʾ�����ʽ�ͽ�ȡ�ַ���������ʽ
	*/
	std::regex					tmp_regex("(\\d+)(ns|us|ms|s|m|h|d)");
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
		if (tmp_match_result.size() <= csf_attribute_time_parametes_size) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. parametes number[%d <= %d]. %s"
				, tmp_match_result.size()
				, csf_attribute_time_parametes_size
				, get_usage().c_str());
			return csf_false;
		}

		//��ȡ"100s"��ʽ�����е�"100","s"�����ַ��Ρ�
		//����tmp_match_result[1]��1����"100"��ֵ���ݣ�
		//����tmp_match_result[2]��2����"s"�ĵ�λ���ݣ�
		if (!get_parametes(tmp_match_result[1].str(), tmp_match_result[2].str())) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. get parametes failed. %s"
				, get_usage().c_str());
			return csf_false;
		}
	}
	return csf_true;
}



/**
* ��ʾ����csf_attribute���Բ�����
* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
*
* @param configure_manager    ��ʾ�������ù���������
* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
*/
csf_bool csf_attribute_time::process_number(const csf_configure_manager& configure_manager, const csf_string& alias) {
	
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


/**
* ��ȡ��ֵ�͵�λ������ݡ�
* ���أ�true��ʾ����ɹ���false��ʾ����ʧ�ܡ�
*
* @param val    ��ʾ��Ҫ�������ֵ����
* @param unit    ��ʾ����ֵ�ĵ�λ�ַ�
*/
csf_bool csf_attribute_time::get_parametes(const csf_string& val, const csf_string& unit) {

	csf_int64									tmp_value = 0;
	csf_int64									tmp_dest = 0;
	csf_attribute_time::csf_time_unit			tmp_unit = csf_attribute_time::csf_time_unit::csf_time_unit_none;


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
	if (csf_attribute_time::csf_time_unit::csf_time_unit_none == tmp_unit) {
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