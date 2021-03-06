﻿/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hivdev.hpp
*
*Version: 1.0
*
*Date: 05-12月-2019 11:06:20
*
*Description: Class(csf_hivdev)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_hivdev.hpp"

using ec::core::csf_hivdev;


csf_hivdev::csf_hivdev()
	: m_thread(NULL) {

}



csf_hivdev::~csf_hivdev() {

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
int csf_hivdev::init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

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
int csf_hivdev::start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

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
int csf_hivdev::stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	return 0;
}


/**
 * 功能：
 *    初始化设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivdev::init_dev() {

	return false;
}


/**
 * 功能：
 *    启动设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivdev::start_dev() {

	return false;
}


/**
 * 功能：
 *    停止设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivdev::stop_dev() {

	return false;
}


/**
 * 功能：
 *    初始化编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivdev::init_coder() {

	return false;
}


/**
 * 功能：
 *    启动编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivdev::start_coder() {

	return false;
}


/**
 * 功能：
 *    启动编解码处理线程
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param hichannel    表示当前的csf_hivdev设备对象指针
 */
bool csf_hivdev::start_coder_thread(csf_hivdev* hichannel) {

	return false;
}


/**
 * 功能：
 *    编解码线程处理函数
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param hichannel    表示当前的csf_hivdev设备对象指针
 */
bool csf_hivdev::coder_thread_process(csf_hivdev* hichannel) {

	return false;
}


/**
 * 功能：
 *    绑定设备和编码器设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param id    表示设备id
 * @param channel    表示设备通道
 * @param coder_channel    表示编码器设备通道
 */
bool csf_hivdev::bind_dev_coder(int id, int channel, int coder_channel) {

	return false;
}


/**
 * 功能：
 *    解除绑定设备和编码器设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param id    表示设备id
 * @param channel    表示设备通道
 * @param coder_channel    表示编码器设备通道
 */
bool csf_hivdev::unbind_dev_coder(int id, int channel, int coder_channel) {

	return false;
}


/**
 * 功能：
 *    停止编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivdev::stop_coder() {

	return false;
}


/**
 * 功能：
 *    停止编解码处理线程
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param hichannel    表示当前的csf_hivdev设备对象指针
 */
bool csf_hivdev::stop_coder_thread(csf_hivdev* hichannel) {

	return false;
}