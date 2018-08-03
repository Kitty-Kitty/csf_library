/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_task.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 19-7��-2018 20:11:50
*
*Description: Class(csf_task) ��ʾ��ʱ����
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_task.hpp"

using csf::core::utils::task::csf_task;


csf_task::csf_task()
	: m_type(csf_task_type_none)
	, m_status(csf_task_status_none)
	, m_callback(csf_null)
	, m_delete_callback(csf_null)
	, m_time(0)
	, m_offset(0)
	, m_decorator(csf_null)
	, m_interval(0)
	, m_task_manager(csf_null) {

}



csf_task::~csf_task() {

}





/**
 * ����task�����ͺ����ʹ���һ������
 * 
 * @param manager    ��ʾ����������ĵ�ַ
 * @param type    ��ʾ������ֵ
 * @param offset    ��ʾ������ʱ��
 * @param interval    ����ִ�еļ��ʱ��
 * @param callback    �����ִ�лص�����
 * @param delete_callback    ����ɾ����ִ�лص�����
 */
csf_task::csf_task(const csf_task_manager* manager, const csf_task_type type, const csf_time offset, const csf_time interval, const csf_task_callback callback, const csf_task_delete_callback delete_callback) {

}


/**
 * ��ʾ����ӿڣ���ֻ��is_process����true�����process��
 */
csf_int32 csf_task::process() {

	return 0;
}


/**
 * ��ʾ�Ƿ���д���,���is_process����true������ִ��process��
 */
csf_bool csf_task::is_process() {

	return csf_true;
}


/**
 * �ж��Ƿ���Ҫɾ�������is_delete����true��ɾ��task��
 */
csf_bool csf_task::is_delete() {

	return csf_true;
}


/**
 * ��ʾ�������������������
 */
csf_task_manager* csf_task::get_task_manager() {

	return m_task_manager;
}


/**
 * ��ʾ�������������������
 * 
 * @param newVal
 */
void csf_task::set_task_manager(const csf_task_manager* newVal) {

	m_task_manager = newVal;
}


/**
 * ��ʾ����ӿڣ���ֻ��is_delete����true�����process_delete��
 */
csf_int32 csf_task::process_delete() {

	return 0;
}