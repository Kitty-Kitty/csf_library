/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_panel_manager_interface.hpp
*
*Version: 1.0
*
*Date: 23-9月-2018 20:13:29
*
*Description: Interface(vdu_panel_manager_interface) 表示画布管理器的操作接口
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_PANEL_MANAGER_INTERFACE_H_INCLUDED_)
#define VDU_PANEL_MANAGER_INTERFACE_H_INCLUDED_

#include "csf_base_include.h"
#include "vdu_box.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * 表示画布管理器的操作接口
		 * @author f
		 * @version 1.0
		 * @created 23-9月-2018 20:13:29
		 */
		class vdu_panel_manager_interface
		{

		public:
			vdu_panel_manager_interface() {

			}

			virtual ~vdu_panel_manager_interface() {

			}

			/**
			 * 主要功能是：创建一个指定画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 * 
			 * @param index    表示需要创建的画层索引号
			 */
			virtual vdu_panel* create_panel(const csf_int32 index) =0;
			/**
			 * 主要功能是：创建一个顶层画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 */
			inline virtual vdu_panel* create_top_panel() =0;
			/**
			 * 主要功能是：创建一个底层画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 */
			inline virtual vdu_panel* create_bottom_panel() =0;
			/**
			 * 主要功能是：根据画层索引号，销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param index    表示需要销毁的画层索引号
			 */
			inline virtual csf_int32 destory_panel(const csf_int32 index) =0;
			/**
			 * 主要功能是：销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示需要销毁的画层指针
			 */
			virtual csf_int32 destory_panel(const vdu_panel* panel) =0;
			/**
			 * 主要功能是：根据画层索引号，添加指定的画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param index    表示画层索引号
			 * @param panel    表示画层对象
			 */
			inline virtual csf_int32 add_panel(const csf_int32 index, const vdu_panel* panel) =0;
			/**
			 * 主要功能是：添加指定的画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层对象
			 */
			virtual csf_int32 add_panel(const vdu_panel* panel) =0;
			/**
			 * 主要功能是：根据画层索引号，删除一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param index    表示画层索引号
			 */
			inline virtual csf_int32 remove_panel(const csf_int32 index) =0;
			/**
			 * 主要功能是：销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层指针
			 */
			virtual csf_int32 remove_panel(const vdu_panel* panel) =0;
			/**
			 * 主要功能是：更新画层的索引号
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示需要被更新的画层对象
			 * @param index    表示画层索引号
			 */
			virtual csf_int32 update_panel(const vdu_panel* panel, const csf_int32 index) =0;
			/**
			 * 主要功能是：根据画层对象，交换两个画层次序
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param first    表示需要交换的第一个画层对象
			 * @param second    表示需要交换的第二个画层对象
			 */
			virtual csf_int32 shift_panel(const vdu_panel* first, const vdu_panel* second) =0;
			/**
			 * 主要功能是：根据画层索引号，交换两个画层次序
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param first    表示需要交换的第一个画层索引
			 * @param second    表示需要交换的第二个画层索引
			 */
			inline virtual csf_int32 shift_panel(const csf_int32 first, const csf_int32 second) =0;
			/**
			 * 主要功能是：根据索引号查询指定画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 * 
			 * @param index    表示画层索引号
			 */
			virtual vdu_panel* find_panel(const csf_int32 index) =0;

		};

	}

}
#endif // !defined(VDU_PANEL_MANAGER_INTERFACE_H_INCLUDED_)
