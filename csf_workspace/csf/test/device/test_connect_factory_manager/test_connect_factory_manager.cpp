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

	csf_device					*tmp_device = csf_nullptr;
	csf_connect_factory			*tmp_factory = csf_nullptr;
	csf_connect_ptr				tmp_connect;


	//����ָ�������ӹ���������
	tmp_device = get_app()->find_device(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(connect_factory)));
	if (csf_nullptr == tmp_device) {
		csf_log_ex(error
			, csf_log_code_error
			, "not found connect factory[%s]"
			, get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(connect_factory)).c_str());
		return csf_failure;
	}

	//�������ӹ�����
	tmp_factory = dynamic_cast<csf_connect_factory*>(tmp_device);
	set_connect_factory(tmp_factory);

	//������Ҫ������
	tmp_connect = tmp_factory->create(csf_connect::csf_connect_type_tcp);
	if (!tmp_connect) {
		csf_log_ex(error
			, csf_log_code_error
			, "create connect failed!");
		return csf_failure;
	}

	if (csf_failure == tmp_connect->set_remote_url(
		get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(center)))) {

		csf_log_ex(error
			, csf_log_code_error
			, "url[%s] failed!"
			, get_attribute_manager().get_value<csf_attribute_string>(CSF_ATTRIBUTE_NAME(center)).c_str());

		return csf_failure;
	}
	else {
		if (csf_failure == tmp_connect->connect(tmp_connect->get_remote_url())) {
			return csf_failure;
		}
		else {
			csf_log_ex(notice
				, csf_log_code_notice
				, "connect [%s] succeed!"
				, tmp_connect->get_remote_url().get_url().c_str());

			tmp_connect->get_write_buffer().create(1024);

			csf_string			tmp_string = "hello world! i'm client!";

			tmp_connect->get_write_buffer().clear();
			tmp_connect->get_write_buffer().cat(tmp_string);
			//connect_ptr->get_write_buffer().set_length(tmp_string.length());
			tmp_connect->write(std::ref(tmp_connect->get_write_buffer()));

			tmp_connect->close();
		}
	}

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
	connect_ptr->get_write_buffer().create(1024);

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

	csf_string			tmp_string = "hello world!";


	if (connect_error.get_code()) {
		connect_ptr->close();
		return 0;
	}

	csf_log_ex(info, csf_log_code_info
		, "get data length[%d]"
		, connect_buffer.length());

	connect_ptr->get_write_buffer().clear();
	connect_ptr->get_write_buffer().cat(tmp_string);
	//connect_ptr->get_write_buffer().set_length(tmp_string.length());
	connect_ptr->write(std::ref(connect_ptr->get_write_buffer()));

	connect_buffer.clear();
	//connect_buffer.set_length(connect_buffer.size());
	connect_ptr->read(std::ref(connect_buffer), get_read_function());

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


/**
* ��Ҫ�����ǣ���Ҫʵ��ģ���������Ϣ����ӿڡ�
* ���أ�0��ʾ�ɹ�����0��ʾʧ�ܣ�
*
* @param element    ��ʾģ���������Ϣ
*
* ���õ�������Ϣ����ṹΪ��
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
*/
csf_int32 test_connect_factory_manager::configure(const csf_element& element) {

	//��������Ϣ
	get_attribute_manager().set_root_element(&element);

	//��ʾ��ģ��ʹ�õ����ӹ���������
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(connect_factory)
		, csf_attribute_string(std::list<csf_string>{ "connect_factory", "mid" }
	, csf_attribute_exception_critical()));

	//��ʾ�������ĵĵ�ַ
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(center)
		, csf_attribute_string(std::list<csf_string>{ "center" }
	, csf_attribute_exception_critical()));

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