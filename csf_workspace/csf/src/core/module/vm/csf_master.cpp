/*******************************************************************************
*
*Copyright: Administrator
*
*Author: Administrator
*
*File name: csf_master.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_master)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_master.hpp"

using csf::core::module::csf_master;


csf_master::csf_master() {

}



csf_master::~csf_master() {

}





/**
 * 功能：
 *    模块初始化，进行模块启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 */
csf::core::base::csf_int32 csf_master::init() {

	return 0;
}


/**
 * 功能：
 *    模块启动，进行模块启动工作。表示模块已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 */
csf::core::base::csf_int32 csf_master::start() {

	return 0;
}


/**
 * 功能：
 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 */
csf::core::base::csf_int32 csf_master::stop() {

	return 0;
}