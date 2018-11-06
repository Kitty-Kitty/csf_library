/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: time_maker.hpp
*
*Version: 1.0
*
*Date: 04-11��-2018 10:45:10
*
*Description: Class(time_maker)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "time_maker.hpp"

using csf::core::utils::time::time_maker;


/**
* ��ʼ��time_maker���ڲ��ͷŶ���ָ��Ϊ��
*/
time_maker* time_maker::m_instance = csf_nullptr;
csf::core::utils::thread::csf_shared_mutex time_maker::m_mutex;


/**
* ��Ҫ�����ǣ�ʱ�������̴߳�������
* ��Ҫ�������Ϊ��1����ȡ����ʱ�䣬���±���ʱ�䣻2������ǰʱ������һ��ʱ��̶ȣ�
* ���أ���
*/
csf_void time_maker::time_cycle() {

	set_native_time(gettimeofday_millsecond());
	csf_msleep((csf_uint32)m_time_resolution);
	set_time(get_time() + m_time_resolution);
}