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
*Date: 24-9月-2018 11:48:22
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
 * 主要功能是：创建一个指定画层
 * 返回：非空表示成功；csf_nullptr表示失败；
 * 
 * @param index    表示需要创建的画层索引号
 */
vdu_panel* vdu_qt_canvas::create_panel(const csf_int32 index) {

	return  csf_nullptr;
}


/**
 * 主要功能是：销毁一个指定画层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示需要销毁的画层指针
 */
csf_int32 vdu_qt_canvas::destory_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * 主要功能是：添加指定的画层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示画层对象
 */
csf_int32 vdu_qt_canvas::add_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * 主要功能是：删除一个指定画层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示画层指针
 */
csf_int32 vdu_qt_canvas::delete_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 vdu_qt_canvas::init(const csf_configure_manager* conf_mg) {
	int							tmp_argc = 0;
	char						*tmp_argv = csf_nullptr;


	//创建application
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

	//创建和初始化view视图对象
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

	//创建和初始化scene场景对象
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
 * 主要功能是：更新画层的索引号
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示需要被更新的画层对象
 * @param index    表示画层索引号
 */
csf_int32 vdu_qt_canvas::update_panel(const vdu_panel* panel, const csf_int32 index) {

	return 0;
}


/**
 * 主要功能是：根据画层对象，交换两个画层次序
 * 返回：0表示成功；其他表示失败；
 * 
 * @param first    表示需要交换的第一个画层对象
 * @param second    表示需要交换的第二个画层对象
 */
csf_int32 vdu_qt_canvas::shift_panel(const vdu_panel* first, const vdu_panel* second) {

	return 0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 vdu_qt_canvas::start(const csf_configure_manager* conf_mg) {

	return 0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 vdu_qt_canvas::stop(const csf_configure_manager* conf_mg) {

	return 0;
}


/**
 * 主要功能是：根据索引号查询指定画层
 * 返回：非空表示成功；csf_nullptr表示失败；
 * 
 * @param index    表示画层索引号
 */
vdu_panel* vdu_qt_canvas::find_panel(const csf_int32 index) {

	return  csf_nullptr;
}


/**
 * 主要功能是：将指定画层设备为顶层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示画层指针
 */
csf_int32 vdu_qt_canvas::set_top(const vdu_panel* panel) {

	return 0;
}


/**
 * 主要功能是：将指定画层设备为底层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示画层指针
 */
csf_int32 vdu_qt_canvas::set_bottom(const vdu_panel* panel) {

	return 0;
}