/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_configure_module.hpp
*
*Version: 1.0
*
*Date: 04-10��-2018 19:44:08
*
*Description: Class(csf_configure_module)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_configure_module.hpp"
#include "csf_device_base.hpp"
#include "csf_app.hpp"
#include "csf_device.hpp"
#include "csf_device_io.hpp"


using csf::core::system::csf_configure_module;


csf_configure_module::csf_configure_module() {

}



csf_configure_module::~csf_configure_module() {

}





/**
* ��Ҫ�����ǣ�ͨ��������Ϣ����һ������ģ�����
* ���أ���null��ʾģ������ַ��null��ʾʧ�ܣ�
*
* @param app    ��ʾ���ָ��app����ģ�����
* @param module_manager    ��ʾģ�������������Ϣ
* @param element    ��ʾģ���������Ϣ��
*
* ģ��������Ϣ�ṹ���£�
* <!--***�ò�������ģ��������Ϣ���Ǳ������õ���������***-->
* <module>
*        <!--***��ʾģ���Ӧ��ģ��������Ϣ***-->
*        <name>csf_connection</name>
*        <!--***��ʾ���豸ģ���Ψһ��ʶ�ַ��������ַ�������ӦС�ڵ���64�ֽ�***-->
*        <mid>02000000-0000001</mid>
*        <!--��ʾ��ģ���������Ϣ����Ҫ��ģ���configure�ӿڴ�����ģ���������������ģ��Ӧ��ģ��ȷ��-->
*        <configure>
*                <!--��ʾ�߳�����-->
*                <thread_number>4</thread_number>
*        </configure>
* </module>
*
*
*/
csf::core::module::csf_device_base* csf_configure_module::create_module(
	csf_app* app
	, csf::core::module::csf_module_manager& module_manager
	, const csf::core::system::csf_element& element) {

	csf_device_base				*tmp_device_base = csf_nullptr;
	csf_int32					tmp_int_return = 0;
	csf_string					tmp_string_name = "";
	csf_string					tmp_string_mid = "";


	if (element.is_null()) {
		return csf_nullptr;
	}

	//�жϵ�ǰ�Ƿ�Ϊdevice�ڵ㣬�����������豸
	tmp_string_name = element.find_element(csf_list<csf_string>{"module", "name"}).get_content();
	tmp_string_mid = element.find_element(csf_list<csf_string>{"module", "mid"}).get_content();

	if (tmp_string_name.empty() || tmp_string_mid.empty()) {

		csf_log_ex(error, csf_log_code_error
			, "module[name:\"%s\"] or mid[\"%s\"] is null!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());

		return csf_nullptr;
	}

	//�������ƴ���ģ�����
	tmp_device_base = dynamic_cast<csf_device_base*>(module_manager.create(tmp_string_name));
	if (!tmp_device_base) {
		csf_log_ex(error, csf_log_code_error
			, "create module[name:\"%s\" mid:\"%s\"] failed!"
			, tmp_string_name.c_str()
			, tmp_string_mid.c_str());
		return csf_nullptr;
	}
	else {
		//����豸���豸�б���
		tmp_device_base->set_name(tmp_string_name);
		tmp_device_base->set_mid(tmp_string_mid);

		tmp_device_base->set_parent(app);

		//����device�豸��app����
		if (csf_device_base::is_device(tmp_device_base->get_type())) {
			((csf_device*)(tmp_device_base))->set_app(app);
		}

		//����device_io�豸��app����
		if (csf_device_base::is_device_io(tmp_device_base->get_type())) {
			((csf_device_io*)(tmp_device_base))->set_app(app);
		}

		if (element.find_element(csf_list<csf_string>{"module", "configure"}).is_null()) {

			csf_log_ex(notice, csf_log_code_notice
				, "create module[%p name:\"%s\" mid:\"%s\"] succeed!"
				, tmp_device_base
				, tmp_string_name.c_str()
				, tmp_string_mid.c_str());
		}
		else {
			
			tmp_int_return = tmp_device_base->configure(element);
			if (tmp_int_return) {

				csf_log_ex(error, csf_log_code_error
					, "create module[%p name:\"%s\" mid:\"%s\"] succeed! reason:[%d] configure failed!"
					, tmp_device_base
					, tmp_string_name.c_str()
					, tmp_string_mid.c_str()
					, tmp_int_return);

				module_manager.destory(tmp_device_base);

				return csf_nullptr;
			}
			else {
				csf_log_ex(notice, csf_log_code_notice
					, "create module[%p name:\"%s\" mid:\"%s\"] and configure succeed!"
					, tmp_device_base
					, tmp_string_name.c_str()
					, tmp_string_mid.c_str());
			}
		}		
	}

	return  tmp_device_base;
}