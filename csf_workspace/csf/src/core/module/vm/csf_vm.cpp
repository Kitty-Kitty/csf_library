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

using csf::core::module::csf_vm;


csf_vm::csf_vm()
	: m_slaves{csf_nullptr, } {

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

	return 0;
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