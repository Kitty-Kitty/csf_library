/*******************************************************************************
*
*Copyright: fangzhenmu
*
*Author: fangzhenmu
*
*File name: vdu_canvas.hpp
*
*Version: 1.0
*
*Date: 23-9月-2018 20:13:29
*
*Description: Class(vdu_canvas)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "vdu_canvas.hpp"

using vdu::core::vdu_canvas;


vdu_canvas::vdu_canvas() {

}



vdu_canvas::~vdu_canvas() {

}





/**
 * 
 * @param type    表示画布的类型
 */
vdu_canvas::vdu_canvas(const vdu_canvas_type type) {

}


/**
 * 模块初始化
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 vdu_canvas::init(const csf_configure_manager* conf_mg) {

	return  0;
}


/**
 * 模块启动
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 vdu_canvas::start(const csf_configure_manager* conf_mg) {

	return  0;
}


/**
 * 模块停止
 * 
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 vdu_canvas::stop(const csf_configure_manager* conf_mg) {

	return  0;
}