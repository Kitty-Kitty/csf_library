/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: test_connect_factory_manager.hpp
*
*Version: 1.0
*
*Date: 08-10��-2018 20:52:07
*
*Description: Class(test_connect_factory_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "test_connect_factory_manager.hpp"
#include "csf_connect_factory_manager.hpp"

using csf::example::test_connect_factory_manager;



test_connect_factory_manager::~test_connect_factory_manager() {

}





/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 test_connect_factory_manager::init(const csf_configure_manager * conf_mg) {

	csf_connect_factory_manager			cfm(conf_mg);
	csf_connect							*tmp_connect = csf_nullptr;
	csf_connect_error					tmp_error;


	if (csf_success != cfm.init(conf_mg, get_app())) {
		csf_log_ex(warning, csf_log_code_warning
			, "init connect factory manager failed!");
		return csf_failure;
	}

	cfm.add_handle("tcp_handle", csf_bind(&test_connect_factory_manager::tcp_handle, this, tmp_connect, tmp_error));
	cfm.add_handle("udp_handle", csf_bind(&test_connect_factory_manager::udp_handle, this, tmp_connect, tmp_error));

	if (csf_success != cfm.start(conf_mg, get_app())) {
		csf_log_ex(warning, csf_log_code_warning
			, "start connect factory manager failed!");
		return csf_failure;
	}


	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 test_connect_factory_manager::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 test_connect_factory_manager::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��Ҫ�����ǣ�tcp���������ؽӿ�
* ���أ�0��ʾ��������0��ʾ����
*
* @param connect    ��ʾ��ǰ���ڴ�������Ӷ���
* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
*/
csf::core::base::csf_int32 test_connect_factory_manager::tcp_handle(csf_connect* connect, csf_connect_error& connect_error) {

	//connect->write(csf_connect_buffer<csf_buffer>(new csf_buffer(), 123), csf_nullptr);
	return 0;
}


/**
* ��Ҫ�����ǣ�udp���������ؽӿ�
* ���أ�0��ʾ��������0��ʾ����
*
* @param connect    ��ʾ��ǰ���ڴ�������Ӷ���
* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
*/
csf::core::base::csf_int32 test_connect_factory_manager::udp_handle(csf_connect* connect, csf_connect_error& connect_error) {

	return 0;
}







/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* ��ʾģ���create �� destroy ������塣                                              */
/* ÿ����Ҫͨ��ģ�鹤��������ģ�鶼��Ҫ��Ӹú궨�塣                                    */
/* ����module_type��ʾ��ģ��������ƣ�����ʵ���˹��췽��Ϊ��                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(test_connect_factory_manager)