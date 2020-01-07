/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_boundary.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 04-7��-2018 22:13:15
*
*Description: Class(csf_attribute_boundary)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_logger.hpp"
#include "csf_attribute_boundary.hpp"

using csf::core::system::attribute::csf_attribute_boundary;



/**
* ��ʾ���ø������Ŵ�����Ӧ�Ĳ�����
* @author fz
* @version 1.0
* @created 04-7��-2018 22:13:15
*/
std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>> _functions = {
	//����()�������߲������������:(-n, 100)
	{ "()", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower < val && val < upper) {
				return csf_true;
			}
			return csf_false;
		}
	},
	//����[)�����������:[0, 100)
	{ "[)", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower <= val && val < upper) {
				return csf_true;
			}
			return csf_false;
		}
	},
	//����(]�����������:(0, 100]
	{ "(]", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower < val && val <= upper) {
				return csf_true;
			}
			return csf_false;
		}
	},
	//����[]�����������:[0, 100]
	{ "[]", [&](const csf_int64 val, const csf_int64 lower, const csf_int64 upper) -> csf_bool {
			if (lower <= val && val <= upper) {
				return csf_true;
			}
			return csf_false;
		}
	}
};

const std::map < std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>> csf_attribute_boundary::m_functions = _functions;

/**
* ��ʾboundary��ʹ��˵��
* @author fz
* @version 1.0
* @created 04-7��-2018 22:13:15
*/
const csf_string csf_attribute_boundary::m_usage = "usage: (lower_boundary, upper_boundary] . for example: (0, 100] or (-n, 100]";

/**
* ��ʾ���������ַ�������У�����
* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
*
* @param boundary    �����ַ������������Ʊ�ʾ��
* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
*/
csf_bool csf_attribute_boundary::parse(const csf_char* boundary) {

	csf_char					tmp_buf[csf_boundary_string_default_length] = { 0, };
	csf_char					*tmp_pos = (csf_char*)boundary;
	csf_char					*tmp_dest = tmp_buf;
	std::unordered_set<csf_char>::iterator			tmp_iter;


	if (!boundary || csf_strlen(boundary) <= 0 ||
		csf_strlen(boundary) > csf_boundary_string_default_length) {
		return csf_false;
	}

	//�����޷�ʶ����ַ���������ʶ����ַ�
	while (*tmp_pos != '\0') {
		if (!csf_char_no_space(*tmp_pos)) {
			++tmp_pos;
			continue;
		}
		*tmp_dest++ = *tmp_pos++;
	}

	//�ж����ݳ���Ϊ0����ʾû�п��ܵĺϷ��ַ�������ֱ�ӷ��ش���
	if (csf_strlen(tmp_buf) <= 0) {
		return csf_false;
	}

	//������ֵ�����ַ�����
	return parse_parametes(tmp_buf);
}

/**
* ��ʾ���������ַ�������У�����
* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
*
* @param boundary    �����ַ������������Ʊ�ʾ��
* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
*
*/
csf_bool csf_attribute_boundary::parse_parametes(const csf_string boundary) {

	/**
	* ��ʾ�����ʽ�ͽ�ȡ�ַ���������ʽ
	*/
	std::regex					tmp_regex("(\\(|\\[)(-n|\\d+),(n|\\+n|\\d+)(\\)|\\])");
	std::smatch					tmp_match_result;


	//ʹ��������ʽ�������ݽṹ����ȡ����
	if (!std::regex_match(boundary, tmp_match_result, tmp_regex)) {
		//������ʽƥ��ʧ�ܣ���ʾ���ݸ�ʽ����
		set_error(csf_errno_none,
			"bounary[%s] format error. %s",
			boundary.c_str(),
			get_usage().c_str());
		return csf_false;
	}
	else {
		//���match��ȡ�Ĳ���С�ڵ�����Ҫ�Ĳ������������ʾ����
		if (tmp_match_result.size() <= csf_boundary_parametes_size) {
			set_error(csf_errno_none,
				"bounary[%s] format error. reason: parametes number[%d <= %d]. %s",
				boundary.c_str(),
				tmp_match_result.size(),
				csf_boundary_parametes_size,
				get_usage().c_str());
			return csf_false;
		}

		//��ȡ"(-n, 100]"��ʽ�����е�"(]"�����ַ���
		//����tmp_match_result[1]��1����"("��λ�ñ�ţ�
		//����tmp_match_result[4]��4����"]"��λ�ñ�ţ�
		if (!get_function(tmp_match_result[1].str() + tmp_match_result[4].str())) {
			set_error(csf_errno_none,
				"bounary[%s] format error. reason: not found function. %s",
				boundary.c_str(),
				get_usage().c_str());
			return csf_false;
		}

		//��ȡ"(-n, 100]"��ʽ�����е�"-n","100"�����ַ��Ρ�
		//����tmp_match_result[2]��1����"-n"��λ�ñ�ţ�
		//����tmp_match_result[3]��4����"100"��λ�ñ�ţ�
		if (!get_parametes(tmp_match_result[2].str(), tmp_match_result[3].str())) {
// 			set_error(csf_errno_none,
// 				"bounary[%s] format error. reason: get paramentes failed. %s",
// 				boundary.c_str(),
// 				get_usage().c_str());
			return csf_false;
		}
	}
	return csf_true;
}

/**
* ���ݴ������ֵ�߽������ַ�����ȡ���ݡ�����-nת��Ϊint64����Сֵ��+nת��Ϊint64�����ֵ��
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
*
* @param lower	��ֵ����Сֵ
* @param upper	��ֵ�����ֵ
*/
csf_bool csf_attribute_boundary::get_parametes(const csf_string& lower, const csf_string& upper) {

	//�ж��Ƿ�Ϊ��Сֵ��������ǣ��������ֵ
	if (!lower.empty() && lower != std::string("-n")) {
		set_lower_bound(csf_atoint64(lower.c_str()));
	}
	else {
		set_lower_bound(csf_min_int64);
	}

	//�ж��Ƿ�Ϊ���ֵ��������ǣ��������ֵ
	if (!upper.empty() && upper != std::string("n") && upper != std::string("+n")) {
		set_upper_bound(csf_atoint64(upper.c_str()));
	}
	else {
		set_upper_bound(csf_max_int64);
	}

	//У�������߽�ֵ����ֵ��С
	if (get_lower_bound() > get_upper_bound()) {

		set_error(csf_errno_none
			, "bounary[%s] format error. reason: lower_bound[%lld] > upper_bound[%lld]."
			, get_boundary().c_str()
			, get_lower_bound()
			, get_upper_bound());

		return csf_false;
	}

	return csf_true;
}