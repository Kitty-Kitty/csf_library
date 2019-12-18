/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hichannel.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:14
*
*Description: Class(csf_hichannel)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_hichannel.hpp"

using ec::core::csf_hichannel;


csf_hichannel::csf_hichannel()
	: m_processor(NULL)
	, m_configure(NULL) {

}



csf_hichannel::~csf_hichannel() {

}





/**
 * 功能：
 *    初始化通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hichannel::init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	return 0;
}


/**
 * 功能：
 *    启动通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hichannel::start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	return 0;
}


/**
 * 功能：
 *    停止通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 * 
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hichannel::stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	return 0;
}