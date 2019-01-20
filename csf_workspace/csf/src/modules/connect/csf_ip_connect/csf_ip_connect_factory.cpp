/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_ip_connect_factory.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:43
*
*Description: Class(csf_ip_connect_factory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_attribute_include.h"
#include "csf_ip_connect_factory.hpp"
#include "csf_tcp_connect.hpp"
#include "csf_udp_connect.hpp"


using csf::modules::connect::csf_ip_connect_factory;


csf_ip_connect_factory::csf_ip_connect_factory()
	: m_idle_interval(csf_ip_connect_factory_timer_interval_ms) {

 	set_version(
 		csf_connect_version
 		, CSF_CONNECT_VER
		, CSF_CONNECT_VAR
 		, "general ip connect"
 	);
}



csf_ip_connect_factory::~csf_ip_connect_factory() {

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
csf_int32 csf_ip_connect_factory::configure(const csf_element& element) {

	//��������Ϣ
	get_attribute_manager().set_root_element(&element);

	//��ʾ���ӹ�������Ҫ�������߳���������ֵĬ��Ϊ��2
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(thread_number)
		, csf_attribute_int(std::list<csf_string>{ "thread_number" }
		, csf_attribute_boundary("[2, n)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(csf_ip_connect_factory_thread_number)));
	//��ʾ���ӳ�ʱ��������Ҫ�������߳���������ֵĬ��Ϊ��2
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(timeout_manager_thread_number)
		, csf_attribute_int(std::list<csf_string>{ "timeout_manager_thread_number" }
		, csf_attribute_boundary("[1, n)")
		, csf_attribute_default_value<csf_attribute_int, csf_int32>(csf_ip_connect_factory_thread_number)));
	//��ʾ��ʱ��ʱ��������ֵĬ��Ϊ��500ms
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(idle_interval)
		, csf_attribute_time(std::list<csf_string>{ "idle_interval" }
		, csf_attribute_time::csf_time_unit_ms
		, csf_attribute_boundary("[10, n)")
		, csf_attribute_default_value<csf_attribute_time, csf_int64>(csf_ip_connect_factory_timer_interval_ms)));

	//����ϵͳ�Ŀ��м��ʱ�䣬��λ�����루ms��
	set_idle_interval(get_attribute_manager().get_value<csf_attribute_time>(CSF_ATTRIBUTE_NAME(idle_interval)));

	return 0;
}



/**
 * ��ʾ�����������ʹ���һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type) {

	csf_connect					*tmp_connect = csf_nullptr;

	if (type & csf_connect::csf_connect_type::csf_connect_type_tcp) {
		tmp_connect = new csf_tcp_connect(*this);
	}
	else if (type & csf_connect::csf_connect_type::csf_connect_type_udp) {
		tmp_connect = new csf_udp_connect(*this);
	}
	else {
		return m_null_connect_ptr;
	}

	csf_connect_ptr tmp_connect_ptr(tmp_connect);

	get_connect_collector().insert(tmp_connect, tmp_connect_ptr);

	return tmp_connect_ptr;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::del(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connect_factory::init(const csf_configure_manager * conf_mg) {

	csf_int32				tmp_int_ret = csf_failure;


	//��������������
	tmp_int_ret = csf_device_base::configure(conf_mg, std::list<csf_string>{ CSF_CONNECT_VAR });
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "configure failed!");
		return csf_failure;
	}

	return csf_connect_factory::init(conf_mg);
}


/**
 * ��ʾ�����������͡����ص�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url) {

	csf_connect_ptr					tmp_connect_ptr = create(type);

	if (tmp_connect_ptr == m_null_connect_ptr) {
		return m_null_connect_ptr;
	}
	else {
		if (tmp_connect_ptr->set_local_url(const_cast<csf_url&>(local_url))) {
			get_connect_collector().remove(tmp_connect_ptr.get());
			return m_null_connect_ptr;
		}
	}
	
	return  tmp_connect_ptr;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::ctrl(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connect_factory::start(const csf_configure_manager * conf_mg) {

	csf_int32				tmp_int_ret = csf_failure;


	//��������������
	tmp_int_ret = csf_device_base::configure(conf_mg, std::list<csf_string>{ CSF_CONNECT_VAR });
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "configure failed!");
		return csf_failure;
	}

	//������ʱ������
	tmp_int_ret = csf_connect_factory::get_timeout_manager().start(
		(csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(timeout_manager_thread_number)));
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "start timeout manager failed!");
		return csf_failure;
	}

	//���������̳߳�
	tmp_int_ret = start_thread_pool();
	if (csf_failure == tmp_int_ret) {
		csf_log_ex(error, csf_log_code_error
			, "start thread pool failed!");
		return csf_failure;
	}

	return csf_succeed;
}


/**
 * ��ʾ�����������͡����ص�ַ��Զ�̵�ַ����һ�����ӡ��ɹ����ط�0��ʧ�ܷ���0��
 * 
 * @param type    ��ʾ��������
 * @param local_url    ��ʾ���Ӵ򿪵ı��ص�ַ
 * @param remote_url    ��ʾ���Ӵ򿪵�Զ�̵�ַ
 */
csf_connect_ptr csf_ip_connect_factory::create(const csf_connect::csf_connect_type type, const csf_url& local_url, const csf_url& remote_url) {

	csf_connect_ptr					tmp_connect_ptr = create(type, local_url);

	if (tmp_connect_ptr == m_null_connect_ptr) {
		return m_null_connect_ptr;
	}
	else {
		if (tmp_connect_ptr->set_remote_url(const_cast<csf_url&>(remote_url))) {
			get_connect_collector().remove(tmp_connect_ptr.get());
			return m_null_connect_ptr;
		}
	}

	return  tmp_connect_ptr;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 csf_ip_connect_factory::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::update(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
 * ��ʾ�豸����Ӳ���
 * 
 * @param element    ��ʾ�豸��Ӳ���
 * @param callback    ��ʾ�豸�����Ļص�����
 */
csf_int32 csf_ip_connect_factory::add(csf_element& element, csf_device_operation_callback callback) {

	return 0;
}


/**
* ��Ҫ�����ǣ������̳߳�
* ���أ���
*/
csf_int32 csf_ip_connect_factory::start_thread_pool() {

	csf_int32				tmp_int_ret = csf_failure;

	
	//�����̳߳أ�׼�������������Ӵ���
	tmp_int_ret = get_thread_pool().start(
		(csf_int32)get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number))
		, csf_bind(&csf_ip_connect_factory::run_io_service, this));

	if (csf_failure == tmp_int_ret) {

		csf_log_ex(error, csf_log_code_error
			, "start thread pool failed! thread_number[%d], idle_interval[%d ms]."
			, get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number))
			, (csf_int32)get_idle_interval());

		return csf_failure;
	}
	else {
		csf_log_ex(notice, csf_log_code_notice
			, "start thread pool succeed! thread_number[%d], idle_interval[%d ms]."
			, get_attribute_manager().get_value<csf_attribute_int>(CSF_ATTRIBUTE_NAME(thread_number))
			, (csf_int32)get_idle_interval());
	}

	return csf_succeed;
}


/**
* ��Ҫ�����ǣ��̳߳�������io_service����
* ���أ���
*/
csf_void csf_ip_connect_factory::run_io_service() {

	try	{

		get_io_service().run();

		csf_msleep((csf_uint32)get_idle_interval());
	}
	catch (boost::exception& e)	{
		csf_log_ex(error, csf_log_code_error
			, "io_service run() failed! reason:[%s -- %s]."
			, boost::current_exception_diagnostic_information().c_str()
			, boost::diagnostic_information(e).c_str());

		//get_thread_pool().stop();
	}
}


/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* ��ʾģ���create �� destroy ������塣                                              */
/* ÿ����Ҫͨ��ģ�鹤��������ģ�鶼��Ҫ��Ӹú궨�塣                                    */
/* ����module_type��ʾ��ģ��������ƣ�����ʵ���˹��췽��Ϊ��                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(csf_ip_connect_factory)