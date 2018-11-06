/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: vdu_qt_panel.hpp
*
*Version: 1.0
*
*Date: 24-9��-2018 11:24:36
*
*Description: Class(vdu_qt_panel)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "vdu_qt_panel.hpp"

using vdu::qt::vdu_qt_panel;


vdu_qt_panel::vdu_qt_panel()
	: vdu_panel(vdu_panel::vdu_panel_type::vdu_panel_type_qt)
	, m_item(csf_nullptr)
	, m_render(csf_nullptr) {

}



vdu_qt_panel::~vdu_qt_panel() {

}



/**
* ģ���ʼ��
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 vdu_qt_panel::init(const csf_configure_manager* conf_mg) {

	//�����ͳ�ʼ��svg item
	try
	{
		set_item(new QGraphicsSvgItem());
		if (!get_item()) {
			csf_log_ex(error, csf_log_code_error,
				"create QGraphicsSvgItem[0x%x] failed.",
				get_item());

			return csf_failure;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"create QGraphicsSvgItem[0x%x] success.",
				get_item());
		}
	}
	catch (std::exception& e) {
		csf_log_ex(error, csf_log_code_error,
			"create QGraphicsSvgItem() error. exception[%s]",
			e.what());
		
		return csf_failure;
	}

	//�����ͳ�ʼ��render
	try
	{
		set_render(new QSvgRenderer());
		if (!get_render()) {
			csf_log_ex(error, csf_log_code_error,
				"create QSvgRenderer[0x%x] failed.",
				get_render());

			return csf_failure;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"create QSvgRenderer[0x%x] success.",
				get_render());
		}
	}
	catch (std::exception& e) {
		csf_log_ex(error, csf_log_code_error,
			"create QSvgRenderer() error. exception[%s]",
			e.what());
		
		return csf_failure;
	}

	return 0;
}



/**
* ģ������
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 vdu_qt_panel::start(const csf_configure_manager* conf_mg) {

	return 0;
}



/**
* ģ��ֹͣ
*
* @param conf_mg    ��ʾ�����ļ���Ϣ
*/
csf::core::base::csf_int32 vdu_qt_panel::stop(const csf_configure_manager* conf_mg) {

	return 0;
}