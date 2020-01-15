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
*Date: 23-9月-2018 20:13:29
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
 * 主要功能是：创建一个指定画层
 * 返回：非空表示成功；csf_nullptr表示失败；
 * 
 * @param index    表示需要创建的画层索引号
 */
vdu_panel* vdu_panel_manager::create_panel(const csf_int32 index) {

	return  csf_nullptr;
}


/**
 * 主要功能是：销毁一个指定画层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示需要销毁的画层指针
 */
csf_int32 vdu_panel_manager::destory_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * 主要功能是：添加指定的画层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示画层对象
 */
csf_int32 vdu_panel_manager::add_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * 主要功能是：销毁一个指定画层
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示画层指针
 */
csf_int32 vdu_panel_manager::remove_panel(const vdu_panel* panel) {

	return 0;
}


/**
 * 主要功能是：更新画层的索引号
 * 返回：0表示成功；其他表示失败；
 * 
 * @param panel    表示需要被更新的画层对象
 * @param index    表示画层索引号
 */
csf_int32 vdu_panel_manager::update_panel(const vdu_panel* panel, const csf_int32 index) {

	return 0;
}


/**
 * 主要功能是：根据画层对象，交换两个画层次序
 * 返回：0表示成功；其他表示失败；
 * 
 * @param first    表示需要交换的第一个画层对象
 * @param second    表示需要交换的第二个画层对象
 */
csf_int32 vdu_panel_manager::shift_panel(const vdu_panel* first, const vdu_panel* second) {

	return 0;
}


/**
 * 主要功能是：根据索引号查询指定画层
 * 返回：非空表示成功；csf_nullptr表示失败；
 * 
 * @param index    表示画层索引号
 */
vdu_panel* vdu_panel_manager::find_panel(const csf_int32 index) {

	return  csf_nullptr;
}