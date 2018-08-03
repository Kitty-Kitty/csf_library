/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_times_task.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:52
*
*Description: Class(csf_times_task) ��ʾָ���������������ڼ�¼����
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_times_task.hpp"

using csf::core::utils::task::csf_times_task;


csf_times_task::csf_times_task()
	: m_sequence(0)
	, m_times(0) {

}



csf_times_task::~csf_times_task() {

}





/**
 * ��ʾ����ӿڣ���ֻ��is_process����true�����process��
 */
csf_int32 csf_times_task::process() {

	return 0;
}


/**
 * ��ʾ�Ƿ���д���,���is_process����true������ִ��process��
 */
csf_bool csf_times_task::is_process() {

	return csf_true;
}


/**
 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
 */
csf_bool csf_times_task::is_delete() {

	return csf_true;
}