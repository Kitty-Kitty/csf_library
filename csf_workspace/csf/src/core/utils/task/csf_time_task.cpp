/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_time_task.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:52
*
*Description: Class(csf_time_task) ��ʾʱ������
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_time_task.hpp"

using csf::core::utils::task::csf_time_task;


csf_time_task::csf_time_task()
	: m_begin(0)
	, m_end(0) {

}



csf_time_task::~csf_time_task() {

}





/**
 * ��ʾ����ӿڣ���ֻ��is_process����true�����process��
 */
csf_int32 csf_time_task::process() {

	return 0;
}


/**
 * ��ʾ�Ƿ���д���,���is_process����true������ִ��process��
 */
csf_bool csf_time_task::is_process() {

	return csf_true;
}


/**
 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
 */
csf_bool csf_time_task::is_delete() {

	return csf_true;
}