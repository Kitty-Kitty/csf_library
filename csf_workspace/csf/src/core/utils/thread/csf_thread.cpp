/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_thread.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:51
*
*Description: Class(csf_thread) ��ʾ�߳���
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_thread.hpp"

using csf::core::utils::thread::csf_thread;


csf_thread::csf_thread()
	: m_status(csf_thread::csf_thread_status::csf_thread_status_none) {

}



csf_thread::~csf_thread() {

}
