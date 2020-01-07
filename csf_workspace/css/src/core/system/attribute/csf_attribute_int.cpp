/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_int.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7��-2018 11:09:59
*
*Description: Class(csf_attribute_int)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_int.hpp"
#include "csf_attribute_printf.h"

using csf::core::system::attribute::csf_attribute_int;



/**
 * �������н�����Ҫ�Ĳ�����
 * ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
 * 
 * @param content    ��ʾ��Ҫ������������Ϣ
 */
csf_bool csf_attribute_int::parse_parametes(const csf_string& content) {

	/**
	* ��ʾ�����ʽ�ͽ�ȡ�ַ���������ʽ
	*/
	std::regex					tmp_regex("(\\d+)");
	std::smatch					tmp_match_result;
	csf_int32					tmp_value = 0;


	if (content.empty()) {
		return csf_false;
	}

	//ʹ��������ʽ�������ݽṹ����ȡ����
	if (!std::regex_match(content, tmp_match_result, tmp_regex)) {
		//������ʽƥ��ʧ�ܣ���ʾ���ݸ�ʽ����
		csf_attribute_log(warning, csf_log_code_warning
			, "content format error.");
		return csf_false;
	}
	else {
		//���match��ȡ�Ĳ���С�ڵ�����Ҫ�Ĳ������������ʾ����
		if (tmp_match_result.size() <= csf_attribute_int_parametes_size) {
			csf_attribute_log(warning, csf_log_code_warning
				, "content format error. parametes number[%d <= %d]. %s"
				, tmp_match_result.size()
				, csf_attribute_int_parametes_size);
			return csf_false;
		}

		//���ַ�������ת��Ϊint32��ʽ����ֵ
		tmp_value = csf_atoint32(tmp_match_result[1].str().c_str());
		if (tmp_value < 0) {
			csf_attribute_log(warning, csf_log_code_warning,
				"value[%s] convert failed.",
				tmp_match_result[1].str().c_str());
			return csf_false;
		}
		else {
			set_value(tmp_value);
		}
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
csf_bool csf_attribute_int::process_number(const csf_configure_manager& configure_manager, const csf_string& alias) {

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