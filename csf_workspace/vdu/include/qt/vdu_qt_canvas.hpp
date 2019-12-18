/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_qt_canvas.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 11:48:22
*
*Description: Class(vdu_qt_canvas) 表示基于QT实现的矢量处理画布
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_QT_CANVAS_H_INCLUDED_)
#define VDU_QT_CANVAS_H_INCLUDED_

#include "vdu_qt_include.h"

#include "vdu_canvas.hpp"

namespace vdu
{
	namespace qt
	{
		/**
		 * 表示基于QT实现的矢量处理画布
		 * @author f
		 * @version 1.0
		 * @created 24-9月-2018 11:48:22
		 */
		class vdu_qt_canvas : public vdu::core::vdu_canvas
		{

		public:
			vdu_qt_canvas();
			virtual ~vdu_qt_canvas();

			/**
			 * 主要功能是：创建一个指定画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 * 
			 * @param index    表示需要创建的画层索引号
			 */
			virtual vdu_panel* create_panel(const csf_int32 index);
			/**
			 * 主要功能是：创建一个顶层画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 */
			inline virtual vdu_panel* create_top_panel() {

				return  csf_nullptr;
			}
			/**
			 * 主要功能是：创建一个底层画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 */
			inline virtual vdu_panel* create_bottom_panel() {

				return  csf_nullptr;
			}
			/**
			 * 主要功能是：销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示需要销毁的画层指针
			 */
			virtual csf_int32 destory_panel(const vdu_panel* panel);
			/**
			 * 模块初始化
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * 主要功能是：更新画层的索引号
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示需要被更新的画层对象
			 * @param index    表示画层索引号
			 */
			virtual csf_int32 update_panel(const vdu_panel* panel, const csf_int32 index);
			/**
			 * 主要功能是：根据画层对象，交换两个画层次序
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param first    表示需要交换的第一个画层对象
			 * @param second    表示需要交换的第二个画层对象
			 */
			virtual csf_int32 shift_panel(const vdu_panel* first, const vdu_panel* second);
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
			 * 主要功能是：根据索引号查询指定画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 * 
			 * @param index    表示画层索引号
			 */
			virtual vdu_panel* find_panel(const csf_int32 index);
			/**
			 * 表示QT的application对象
			 */
			inline QApplication* get_app() {

				return m_app;
			}
			/**
			 * 表示图形的视图对象
			 */
			inline QGraphicsView* get_view() {

				return m_view;
			}
			/**
			 * 主要功能是：将指定画层设备为顶层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层指针
			 */
			virtual csf_int32 set_top(const vdu_panel* panel);
			/**
			 * 表示图形场景
			 */
			inline QGraphicsScene* get_scene() {

				return m_scene;
			}
			/**
			 * 主要功能是：将指定画层设备为底层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层指针
			 */
			virtual csf_int32 set_bottom(const vdu_panel* panel);

		protected:
			/**
			 * 主要功能是：根据画层索引号，添加指定的画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param index    表示画层索引号
			 * @param panel    表示画层对象
			 */
			inline virtual csf_int32 add_panel(const csf_int32 index, const vdu_panel* panel) {

				return 0;
			}
			/**
			 * 主要功能是：添加指定的画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层对象
			 */
			virtual csf_int32 add_panel(const vdu_panel* panel);
			/**
			 * 主要功能是：删除一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层指针
			 */
			virtual csf_int32 delete_panel(const vdu_panel* panel);
			/**
			* 表示QT的application对象
			*
			* @param newVal
			*/
			inline void set_app(QApplication* newVal) {

				m_app = newVal;
			}
			/**
			* 表示图形的视图对象
			*
			* @param newVal
			*/
			inline void set_view(QGraphicsView* newVal) {

				m_view = newVal;
			}
			/**
			* 表示图形场景
			*
			* @param newVal
			*/
			inline void set_scene(QGraphicsScene* newVal) {

				m_scene = newVal;
			}
		private:
			/**
			 * 表示QT的application对象
			 */
			QApplication* m_app = csf_nullptr;
			/**
			 * 表示图形的视图对象
			 */
			QGraphicsView* m_view = csf_nullptr;
			/**
			 * 表示图形场景
			 */
			QGraphicsScene* m_scene = csf_nullptr;

		};

	}

}
#endif // !defined(VDU_QT_CANVAS_H_INCLUDED_)
