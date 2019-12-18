/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_panel.hpp
*
*Version: 1.0
*
*Date: 23-9月-2018 20:20:21
*
*Description: Class(vdu_panel) 表示矢量处理图层
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_PANEL_H_INCLUDED_)
#define VDU_PANEL_H_INCLUDED_

#include "vdu_panel_interface.hpp"
#include "vdu_box.hpp"
#include "csf_device.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * 表示矢量处理图层
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 23-9月-2018 20:20:21
		 */
		class vdu_panel : public vdu::core::vdu_box, public csf::core::module::csf_device, public vdu::core::vdu_panel_interface
		{

		public:
			/**
			 * 表示画层的类型
			 * @author f
			 * @version 1.0
			 * @created 23-9月-2018 20:20:21
			 */
			typedef enum vdu_panel_type_enum
			{
				/**
				 * 表示默认的未知画层类型
				 */
				vdu_panel_type_none = 0x00000000,
				/**
				 * 表示qt画层类型
				 */
				vdu_panel_type_qt = 0x00000001
			} vdu_panel_type;


			vdu_panel();
			virtual ~vdu_panel();

			/**
			 * 
			 * @param type    表示画层的类型
			 */
			vdu_panel(const vdu_panel_type type);
			/**
			 * 模块初始化
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

				return  0;
			}
			/**
			 * 表示panel所属的canvas对象
			 */
			inline vdu_canvas* get_canvas() {

				return m_canvas;
			}
			/**
			 * 模块启动
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

				return  0;
			}
			/**
			 * 表示panel所属的canvas对象
			 * 
			 * @param newVal
			 */
			inline void set_canvas(vdu_canvas* newVal) {

				m_canvas = newVal;
			}
			/**
			 * 模块停止
			 * 
			 * @param conf_mg    表示配置文件信息
			 */
			inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

				return  0;
			}
			/**
			* 表示画层的类型
			*/
			inline vdu_panel_type get_type() {

				return m_type;
			}
			/**
			* 表示画层的类型
			*
			* @param newVal
			*/
			inline void set_type(vdu_panel_type newVal) {

				m_type = newVal;
			}
		private:
			/**
			 * 表示panel所属的canvas对象
			 */
			vdu::core::vdu_canvas *m_canvas;
			/**
			* 表示画层的类型
			*/
			vdu_panel_type m_type = vdu_panel_type_none;
		};

	}

}
#endif // !defined(VDU_PANEL_H_INCLUDED_)
