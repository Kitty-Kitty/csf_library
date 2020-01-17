/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: csf_vm.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:43
*
*Description: Class(csf_vm)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_vm.hpp"
#include "csf_slave.hpp"

using csf::core::module::csf_vm;


csf_vm::csf_vm()
	: m_slaves{csf_nullptr, } {

	set_type(csf_module_type_vm);
}



csf_vm::~csf_vm() {

}





/**
 * 功能：
 *    模块初始化，进行模块启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_vm::init(const csf_configure_manager * conf_mg) {
	
	return csf_succeed;
}


/**
 * 功能：
 *    模块启动，进行模块启动工作。表示模块已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_vm::start(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 功能：
 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_vm::stop(const csf_configure_manager * conf_mg) {

	return 0;
}


/**
 * 功能：
 *    启动所有私服进程
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 */
csf_bool csf_vm::start_slaves() {

	return csf_true;
}


/**
 * 功能：
 *    停止所有私服进程
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 */
csf_bool csf_vm::stop_slaves() {

	for (int i = 0; i < csf_ary_size(m_slaves); i++) {
		stop_slave(m_slaves[0]);
	}
	return csf_true;
}


/**
 * 功能：
 *    启动指定的私服程序
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 *
 * @param element    表示当前需要启动的伺服信息
 */
csf_bool csf_vm::start_slave(csf_element& element) {

	return csf_true;
}


/**
 * 功能：
 *    根据名称停止指定的私服程序
 * 返回：
 *    true  ：  表示成功；
 *   false  ：  表示失败；
 *
 * @param name    表示当前需要停止的伺服名称
 */
csf_bool csf_vm::stop_slave(csf_string& name) {

	for (int i = 0; i < csf_ary_size(m_slaves); i++) {
		if (csf_nullptr == m_slaves[i]) {
			continue;
		}
		if (m_slaves[i]->get_name() == name) {
			return stop_slave(m_slaves[i]);
		}
	}

	return csf_true;
}


/**
 * 功能：
 *    根据名称查找指定的私服信息
 * 返回：
 *    非null  ：  表示查找到的伺服对象；
 *      null  ：  表示不存在指定的伺服对象；
 *
 * @param name    表示伺服名称
 */
csf_slave* csf_vm::find_slave(csf_string& name) {

	for (int i = 0; i < csf_ary_size(m_slaves); i++) {
		if (csf_nullptr == m_slaves[i]) {
			continue;
		}
		if (m_slaves[i]->get_name() == name) {
			return m_slaves[i];
		}
	}

	return  csf_nullptr;
}


/**
 * 功能：
 *    根据名称启动指定的私服程序
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param name    表示伺服名称
 */
csf_bool csf_vm::start_slave(csf_string& name) {

	for (int i = 0; i < csf_ary_size(m_slaves); i++) {
		if (csf_nullptr == m_slaves[i]) {
			continue;
		}
		if (m_slaves[i]->get_name() == name) {
			return start_slave(m_slaves[i]);
		}
	}

	return csf_true;
}


/**
 * 功能：
 *    启动指定的私服程序
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_vm::start_slave(csf_slave* slave) {

	return csf_true;
}


/**
 * 功能：
 *    停止指定的私服程序
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_vm::stop_slave(csf_slave* slave) {

	return csf_true;
}


/**
 * 功能：
 *    插入指定的私服信息
 * 返回：
 *   true  ：  表示成功；
 *   false ：  表示失败；
 *
 * @param slave    表示伺服信息对象
 */
csf_bool csf_vm::insert_slave(csf_slave* slave) {

	//遍历数组，播放到空位置
	for (int i = 0; i < csf_ary_size(m_slaves); i++) {
		if (csf_nullptr == m_slaves[i]) {
			m_slaves[i] = slave;
			return csf_true;
		}
	}
	return csf_false;
}

