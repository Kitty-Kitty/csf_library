/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: vdu_qt_canvas.hpp
*
*Version: 1.0
*
*Date: 24-9��-2018 11:48:22
*
*Description: Class(vdu_qt_canvas)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "vdu_qt_canvas.hpp"

using vdu::qt::vdu_qt_canvas;


vdu_qt_canvas::vdu_qt_canvas()
	: vdu_canvas(vdu_canvas::vdu_canvas_type::vdu_canvas_type_qt)
	, m_app(csf_nullptr)
	, m_view(csf_nullptr)
	, m_scene(csf_nullptr) {

}



vdu_qt_canvas::~vdu_qt_canvas() {

}





/**
 * ��Ҫ�����ǣ�����һ��ָ������
 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
 * 
 * @param index    ��ʾ��Ҫ�����Ļ���������
 */
vdu_panel* vdu_qt_canvas::create_panel(const csf_int32 index) {

	return  csf_nullptr;
}


/**
 * ��Ҫ�����ǣ�����һ��ָ������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ��Ҫ���ٵĻ���ָ��
 */
csf_int32 vdu_qt_canvas::destory_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����ָ���Ļ���
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ�������
 */
csf_int32 vdu_qt_canvas::add_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * ��Ҫ�����ǣ�ɾ��һ��ָ������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ����ָ��
 */
csf_int32 vdu_qt_canvas::delete_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * ģ���ʼ��
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 vdu_qt_canvas::init(const csf_configure_manager* conf_mg) {
	int							tmp_argc = 0;
	char						*tmp_argv = csf_nullptr;


	//����application
	try
	{
		
		set_app(new QApplication(tmp_argc, csf_nullptr));
		if (!get_app()) {
			csf_log_ex(error, csf_log_code_error,
				"create QApplication[0x%x] failed.",
				get_app());

			return csf_failure;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"create QApplication[0x%x] success.", 
				get_app());
		}
	}
	catch (std::exception& e) {
		csf_log_ex(error, csf_log_code_error,
			"create QApplication() error. exception[%s]", e.what());
		
		return csf_failure;
	}

	//�����ͳ�ʼ��view��ͼ����
	try
	{
		set_view(new QGraphicsView());
		if (!get_view()) {
			csf_log_ex(error, csf_log_code_error,
				"create QGraphicsView[0x%x] failed.",
				get_view());

			return csf_failure;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"create QGraphicsView[0x%x] success.",
				get_view());
		}
	}
	catch (std::exception& e) {
		csf_log_ex(error, csf_log_code_error,
			"create QGraphicsView() error. exception[%s]", e.what());
		
		return csf_failure;
	}

	//�����ͳ�ʼ��scene��������
	try
	{
		if (get_rect().is_valid()) {
			set_scene(new QGraphicsScene(get_rect().get_top().get_x(), get_rect().get_top().get_y()
				, get_rect().get_width()
				, get_rect().get_height()
				, get_view()));
		}
		else {
			set_scene(new QGraphicsScene(get_view()));
		}

		if (!get_scene()) {
			csf_log_ex(error, csf_log_code_error,
				"create QGraphicsScene[0x%x] failed.",
				get_scene());

			return csf_failure;
		}
		else {
			csf_log_ex(notice, csf_log_code_notice,
				"create QGraphicsScene[0x%x] success.",
				get_scene());
		}
	}
	catch (std::exception& e) {
		csf_log_ex(error, csf_log_code_error,
			"create QGraphicsScene() error. exception[%s]", e.what());
		
		return csf_failure;
	}

	return 0;
}


/**
 * ��Ҫ�����ǣ����»����������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ��Ҫ�����µĻ������
 * @param index    ��ʾ����������
 */
csf_int32 vdu_qt_canvas::update_panel(const vdu_panel* panel, const csf_int32 index) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����ݻ�����󣬽��������������
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param first    ��ʾ��Ҫ�����ĵ�һ���������
 * @param second    ��ʾ��Ҫ�����ĵڶ����������
 */
csf_int32 vdu_qt_canvas::shift_panel(const vdu_panel* first, const vdu_panel* second) {

	return 0;
}


/**
 * ģ������
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 vdu_qt_canvas::start(const csf_configure_manager* conf_mg) {

	return 0;
}


/**
 * ģ��ֹͣ
 * 
 * @param conf_mg    ��ʾ�����ļ���Ϣ
 */
csf::core::base::csf_int32 vdu_qt_canvas::stop(const csf_configure_manager* conf_mg) {

	return 0;
}


/**
 * ��Ҫ�����ǣ����������Ų�ѯָ������
 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
 * 
 * @param index    ��ʾ����������
 */
vdu_panel* vdu_qt_canvas::find_panel(const csf_int32 index) {

	return  csf_nullptr;
}


/**
 * ��Ҫ�����ǣ���ָ�������豸Ϊ����
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ����ָ��
 */
csf_int32 vdu_qt_canvas::set_top(const vdu_panel* panel) {

	return 0;
}


/**
 * ��Ҫ�����ǣ���ָ�������豸Ϊ�ײ�
 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
 * 
 * @param panel    ��ʾ����ָ��
 */
csf_int32 vdu_qt_canvas::set_bottom(const vdu_panel* panel) {

	return 0;
}