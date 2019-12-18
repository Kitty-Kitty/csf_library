/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hiadev.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:13
*
*Description: Class(csf_hiadev)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_hiadev.hpp"

using ec::core::csf_hiadev;


csf_hiadev::csf_hiadev()
	: m_dev_id(0)
	, m_dev_channel(0)
	, m_coder_channel(0) {

}



csf_hiadev::~csf_hiadev() {

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
int csf_hiadev::init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

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
int csf_hiadev::start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

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
int csf_hiadev::stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	return 0;
}


/**
 * 功能：
 *    初始化设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiadev::init_dev() {

	return false;
}


/**
 * 功能：
 *    启动设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiadev::start_dev() {

	return false;
}


/**
 * 功能：
 *    启动设备重新采样处理
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiadev::start_dev_resample(int id, int channel) {

	return false;
}


/**
 * 功能：
 *    启动设备质量增强功能。
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiadev::start_dev_vqe(int id, int channel) {

	return false;
}


/**
 * 功能：
 *    停止设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiadev::stop_dev() {

	return false;
}


/**
 * 功能：
 *    停止设备重新采样处理
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiadev::stop_dev_resample(int id, int channel) {

	return false;
}


/**
* 功能：
*    停止设备质量增强功能。
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param id    表示设备id
* @param channel    表示设备通道
*/
bool csf_hiadev::stop_dev_vqe(int id, int channel) {

	return false;
}


/**
* 功能：
*    设置设备的音量大小。
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param id    表示设备id
* @param channel    表示设备通道
* @param volume    表示音频音量大小数值
*/
bool csf_hiadev::set_dev_vqe_volume(int id, int channel, int volume) {

	return false;
}


/**
 * 功能：
 *    初始化编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiadev::init_coder() {

	return false;
}


/**
 * 功能：
 *    启动编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiadev::start_coder() {

	return false;
}


/**
 * 功能：
 *    启动编解码处理线程
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param hichannel    表示当前的csf_hiadev设备对象指针
 */
bool csf_hiadev::start_coder_thread(csf_hiadev* hichannel) {

	return false;
}


/**
 * 功能：
 *    编解码线程处理函数
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param hichannel    表示当前的csf_hiadev设备对象指针
 */
bool csf_hiadev::coder_thread_process(csf_hiadev* hichannel) {

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
bool csf_hiadev::bind_dev_coder(int id, int channel, int coder_channel) {

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
bool csf_hiadev::unbind_dev_coder(int id, int channel, int coder_channel) {

	return false;
}


/**
 * 功能：
 *    停止编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiadev::stop_coder() {

	return false;
}


/**
 * 功能：
 *    停止编解码处理线程
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 * 
 * @param hichannel    表示当前的csf_hiadev设备对象指针
 */
bool csf_hiadev::stop_coder_thread(csf_hiadev* hichannel) {

	return false;
}