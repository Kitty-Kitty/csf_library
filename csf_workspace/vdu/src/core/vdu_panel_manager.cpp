/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: vdu_panel_manager.hpp
*
*Version: 1.0
*
*Date: 23-9��-2018 20:13:29
*
*Description: Class(vdu_panel_manager)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "vdu_panel_manager.hpp"

using vdu::core::vdu_panel_manager;


vdu_panel_manager::vdu_panel_manager()
	: m_top_index(0)
	, m_bottom_index(0) {

}



vdu_panel_manager::~vdu_panel_manager() {

}





/**
 * ��Ҫ�����ǣ�����һ��ָ������
 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
 * 
 * @param index    ��ʾ��Ҫ�����Ļ���������
 */
vdu_panel* vdu_panel_manager::create_panel(const csf_int32 index) {

	return  csf_nullptr;
}


/**
 * ��Ҫ�����ǣ�����һ��ָ������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ��Ҫ���ٵĻ���ָ��
 */
csf_int32 vdu_panel_manager::destory_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����ָ���Ļ���
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ�������
 */
csf_int32 vdu_panel_manager::add_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * ��Ҫ�����ǣ�����һ��ָ������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ����ָ��
 */
csf_int32 vdu_panel_manager::remove_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����»����������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ��Ҫ�����µĻ������
 * @param index    ��ʾ����������
 */
csf_int32 vdu_panel_manager::update_panel(const vdu_panel* panel, const csf_int32 index) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����ݻ�����󣬽��������������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param first    ��ʾ��Ҫ�����ĵ�һ���������
 * @param second    ��ʾ��Ҫ�����ĵڶ����������
 */
csf_int32 vdu_panel_manager::shift_panel(const vdu_panel* first, const vdu_panel* second) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����������Ų�ѯָ������
 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
 * 
 * @param index    ��ʾ����������
 */
vdu_panel* vdu_panel_manager::find_panel(const csf_int32 index) {

	return  csf_nullptr;
}