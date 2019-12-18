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
*Date: 08-10月-2018 20:52:07
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
 * 模块初始化
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 ec_device::init(
	const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 模块启动
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 ec_device::start(
	const csf_configure_manager * conf_mg) {

	init_device_ioes();
	start_device_ioes();
	return 0;
}


/**
 * 模块停止
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 ec_device::stop(
	const csf_configure_manager * conf_mg) {

	stop_device_ioes();
	return 0;
}

/**
* 主要功能是：主要实现模块的配置信息处理接口。
* 返回：0表示成功；非0表示失败；
*
* @param element    表示模块的配置信息
*
* 常用的配置信息保存结构为：
* <!--***该部分描述模块配置信息，是必须配置的数据内容***-->
* <module>
*        <!--***表示模块对应的模块名称信息***-->
*        <name>csf_connection</name>
*        <!--***表示该设备模块的唯一标识字符串，该字符串长度应小于等于64字节***-->
*        <mid>02000000-0000001</mid>
*        <!--表示该模块的配置信息，主要由模块的configure接口处理。该模块的配置项内容由模对应的模块确定-->
*        <configure>
*                <!--表示线程数量-->
*                <thread_number>4</thread_number>
*        </configure>
* </module>
*/
csf_int32 ec_device::configure(const csf_element& element) {

	//根配置信息
	get_attribute_manager().set_root_element(&element);

	//表示该模块使用的连接管理器配置
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(connect_factory)
		, csf_attribute_string(std::list<csf_string>{ "connect_factory", "mid" }
	, csf_attribute_exception_critical()));

	//表示连接中心的地址
	get_attribute_manager().add(CSF_ATTRIBUTE_NAME(center)
		, csf_attribute_string(std::list<csf_string>{ "center" }
	, csf_attribute_exception_critical()));

	return 0;
}



/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* 表示模块的create 和 destroy 句柄定义。                                              */
/* 每个需要通过模块工厂创建的模块都需要添加该宏定义。                                    */
/* 其中module_type表示该模块的类名称，该类实现了构造方法为：                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
CSF_MODULE_SYMBOY_DEFINE(ec_device)