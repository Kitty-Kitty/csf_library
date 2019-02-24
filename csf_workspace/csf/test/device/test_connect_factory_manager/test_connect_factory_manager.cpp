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
csf::core::base::csf_int32 test_connect_factory_manager::init(
	const csf_configure_manager * conf_mg) {

	csf_connect_factory_manager			cfm(conf_mg);


	//��ʾ����app�Ľӿڣ���ʼ��ģ�����־���ܣ�����ģ�����־��¼����
	if (get_app()) {
		get_app()->init_module_logger();
	}

	if (csf_succeed != cfm.init(conf_mg, get_app())) {
		csf_log_ex(warning, csf_log_code_warning
			, "init connect factory manager failed!");
		return csf_failure;
	}

	cfm.add_handle("tcp_handle", csf_bind(&test_connect_factory_manager::tcp_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2));


	cfm.add_handle("udp_handle", csf_bind(&test_connect_factory_manager::udp_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2));

	if (csf_succeed != cfm.start(conf_mg, get_app())) {
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
csf::core::base::csf_int32 test_connect_factory_manager::start(
	const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 test_connect_factory_manager::stop(
	const csf_configure_manager * conf_mg) {

	return 0;
}


/**
* ��Ҫ�����ǣ�tcp���������ؽӿ�
* ���أ�0��ʾ��������0��ʾ����
*
* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
*/
csf::core::base::csf_int32 test_connect_factory_manager::tcp_handle(
	csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error) {

	connect_ptr->get_read_buffer().create(1024);

	set_read_function(csf_bind(&test_connect_factory_manager::read_handle
		, this
		, std::placeholders::_1
		, std::placeholders::_2
		, std::ref(connect_ptr->get_read_buffer())));

// 	connect_ptr->read(std::ref(connect_ptr->get_read_buffer())
// 		, csf_bind(&test_connect_factory_manager::read_handle
// 			, this
// 			, connect_ptr
// 			, std::ref(connect_ptr->get_read_buffer())
// 			, std::placeholders::_1));

	connect_ptr->read(std::ref(connect_ptr->get_read_buffer()), get_read_function());

	return 0;
}


/**
* ��Ҫ�����ǣ�udp���������ؽӿ�
* ���أ�0��ʾ��������0��ʾ����
*
* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
*/
csf::core::base::csf_int32 test_connect_factory_manager::udp_handle(
	csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error) {

	return 0;
}


/**
* ��Ҫ�����ǣ�tcp�����ݷ��غ���
* ���أ����ڵ���0��ʾ�ɹ���С��0��ʾ����
*
* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
* @param connect_buffer
* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
*/
csf::core::base::csf_int32 test_connect_factory_manager::read_handle(
	csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error
	, csf_connect_buffer<csf_buffer>& connect_buffer
	) {

	return 0;
}


/**
* ��Ҫ�����ǣ�tcp�����ݷ��غ���
* ���أ����ڵ���0��ʾ�ɹ���С��0��ʾ����
*
* @param connect_ptr    ��ʾ��ǰ���ڴ�������Ӷ���
* @param connect_buffer
* @param connect_error    ��ʾ��ǰ������쳣��Ϣ
*/
csf::core::base::csf_int32 test_connect_factory_manager::tcp_read_handle(csf_connect_ptr connect_ptr
	, csf_connect_error& connect_error
	, csf_int32 len)
{

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