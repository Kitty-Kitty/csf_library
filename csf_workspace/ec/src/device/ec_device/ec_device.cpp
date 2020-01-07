/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: ec_device.hpp
*
*Version: 1.0
*
*Date: 08-10��-2018 20:52:07
*
*Description: Class(ec_device)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "ec_device.hpp"

using csf::device::ec_device;



ec_device::~ec_device() {

}





/**
 * ģ���ʼ��
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 ec_device::init(
	const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * ģ������
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 ec_device::start(
	const csf_configure_manager * conf_mg) {

	init_device_ioes();
	start_device_ioes();
	return 0;
}


/**
 * ģ��ֹͣ
 *
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 ec_device::stop(
	const csf_configure_manager * conf_mg) {

	stop_device_ioes();
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
csf_int32 ec_device::configure(const csf_element& element) {

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
CSF_MODULE_SYMBOY_DEFINE(ec_device)