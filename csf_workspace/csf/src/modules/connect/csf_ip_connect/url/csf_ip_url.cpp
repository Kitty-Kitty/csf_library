/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_url.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_url)
*
*Others:
*
*History:
*
*******************************************************************************/

#include <regex>
#include "csf_ip_url.hpp"

using csf::modules::connect::csf_ip_url;


csf_ip_url::csf_ip_url()
	: csf_url(csf_url::csf_url_type::csf_url_type_ip)
	, m_ip("")
	, m_port(0) {

}



csf_ip_url::~csf_ip_url() {

}





/**
 * ��ʾ������ַ����
 *
 * @param url    ��ʾurl��ַ�ַ�������
 */
csf_int32 csf_ip_url::parse(const csf_string& url) {

	/**
	* ��ʾ�����ʽ�ͽ�ȡ�ַ����������ʽ
	*/
	//std::regex					tmp_regex("(\\w+):([0-9]{0,5})");
	std::regex					tmp_regex("(\\d+.\\d+.\\d+.\\d+):([0-9]{0,5})");
	std::smatch					tmp_match_result;
	int							tmp_port = 0;


	if (url.empty()) {
		return csf_failure;
	}

	//ʹ���������ʽ�������ݽṹ����ȡ����
	if (!std::regex_match(url, tmp_match_result, tmp_regex)) {
		//�������ʽƥ��ʧ�ܣ���ʾ���ݸ�ʽ����
		return csf_failure;
	}

	//���match��ȡ�Ĳ���С�ڵ�����Ҫ�Ĳ������������ʾ����
	if (tmp_match_result.size() <= csf_ip_url_parametes_size) {
		return csf_failure;
	}
	else {
		//У��˿ڵĺϷ���
		tmp_port = atoi(tmp_match_result[2].str().c_str());
		if (!check_port(tmp_port)) {
			return csf_failure;
		}

		//У��ip��ַ�ĺϷ���
		if (!check_ip(tmp_match_result[1].str())) {
			return csf_failure;
		}
		else {
			set_ip(tmp_match_result[1].str());
		}

		set_port(tmp_port);

		return csf_success;
	}

	return csf_failure;
}


/**
* ��Ҫ�����ǣ�����ip�Ͷ˿ں�����url��Ϣ
* ���أ�0��ʾ�ɹ�����0��ʾ����
*
* @param ip    ��ʾip�ַ������ݣ���ַ��ʽΪ��xxx.xxx.xxx.xxxxt������:192.168.1.10
* @param port    ��ʾ�˿�����
*/
csf_int32 csf_ip_url::set_url(const csf_string& ip, const csf_ushort port) {

	if (check_ip(ip) && check_port(port)) {
		set_ip(ip);
		set_port(port);

		csf_char			tmp_buf[csf_ip_url_buffer_size] = { 0, };

		csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
			, "%s:%d"
			, ip.c_str()
			, port);
		set_url(tmp_buf);

		return csf_success;
	}
	return csf_failure;
}


/**
* ��Ҫ�����ǣ���ip��ַ�ĸ�ʽ�Ϸ���У��
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
*
* @param ip    ��ʾ�����ַ��ʽ
*/
csf_bool csf_ip_url::check_ip(const csf_string& ip) {

	std::regex					tmp_pattern("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");

	if (!std::regex_match(ip, tmp_pattern)) {
		return csf_false;
	}

	return csf_true;
}


/**
* ��Ҫ�����ǣ���port��ֵ�Ϸ���У��
* ���أ�true��ʾ�ɹ���false��ʾʧ�ܣ�
*
* @param port    ��ʾ����˿�
*/
csf_bool csf_ip_url::check_port(const csf_string& port) {

	int							tmp_int = 0;
	std::regex					tmp_pattern("[0-9]{0,5}");

	if (!std::regex_match(port, tmp_pattern)) {
		return csf_false;
	}
	else {
		//У��˿ڵĺϷ���
		tmp_int = atoi(port.c_str());
		if (tmp_int >= 0 && tmp_int <= csf_max_ushort) {
			return csf_true;
		}
	}

	return csf_false;
}