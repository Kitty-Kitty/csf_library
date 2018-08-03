/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_number.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:28
*
*Description: Class(csf_attribute_number)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_attribute_number.hpp"
#include "csf_attribute_printf.h"
#include "csf_logger.hpp"


using csf::core::system::attribute::csf_attribute_number;

/**
* ��ʾ����csf_attribute���Բ�����������csf_attribute�в�ͬ���ǣ��������һ��process_attribute������Ҫ��Ϊ��ʵ���쳣��e
* xception����ͳһ�������쳣����ʱ��ֱ�Ӹ��ݷ��ش��󣬵����쳣��������
* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
*
* @param configure_manager    ��ʾ�������ù���������
* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
*/
csf_bool csf_attribute_number::process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) {

	//��ʼ�������߽����
	if (get_boundary().not_null()) {
		if (!get_boundary().init()) {
			csf_attribute_log(warning, csf_log_code_warning
				, "boundary[%s] init failed! reason: %s"
				, get_boundary().get_boundary().c_str()
				, get_boundary().get_descripion().c_str());
			return csf_false;
		}
	}

	//��ʾ������ֵ����
	if (csf_false == process_number(configure_manager, alias)) {
		return csf_false;
	}

	//������ֵ�ı߽磬�ж��Ƿ��ںϷ��߽���
	if (get_boundary().not_null()) {
		if (!get_boundary().process(get_value())) {
			csf_attribute_log(warning, csf_log_code_warning
				, " value[%lld] mismatch boundary[ \"%s\" ] warning."
				, get_value()
				, get_boundary().get_boundary().c_str());
			return csf_false;
		}
	}
	return csf_true;
}
