/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_qt_panel.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 11:24:36
*
*Description: Class(vdu_qt_panel) 表示基于QT实现的矢量处理单元图层
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_QT_PANEL_H_INCLUDED_)
#define VDU_QT_PANEL_H_INCLUDED_

#include "vdu_qt_include.h"

#include "vdu_panel.hpp"

namespace vdu
{
	namespace qt
	{
		/**
		 * 表示基于QT实现的矢量处理单元图层
		 * @author f
		 * @version 1.0
		 * @created 24-9月-2018 11:24:36
		 */
		class vdu_qt_panel : public vdu::core::vdu_panel
		{

		public:
			vdu_qt_panel();
			virtual ~vdu_qt_panel();
			/**
			* 模块初始化
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			* 模块启动
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			* 模块停止
			*
			* @param conf_mg    表示配置文件信息
			*/
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * 表示一个svg render内容
			 */
			inline QSvgRenderer* get_render() {

				return m_render;
			}
			/**
			 * 表示一个svg图层对象
			 */
			inline QGraphicsSvgItem* get_item() {

				return m_item;
			}
		private:
			/**
			* 表示一个svg render内容
			*
			* @param newVal
			*/
			inline void set_render(QSvgRenderer* newVal) {

				m_render = newVal;
			}
			/**
			* 表示一个svg图层对象
			*
			* @param newVal
			*/
			inline void set_item(QGraphicsSvgItem* newVal) {

				m_item = newVal;
			}
		private:
			/**
			 * 表示一个svg图层对象
			 */
			QGraphicsSvgItem* m_item = csf_nullptr;
			/**
			 * 表示一个svg render内容
			 */
			QSvgRenderer* m_render = csf_nullptr;

		};

	}

}
#endif // !defined(VDU_QT_PANEL_H_INCLUDED_)
