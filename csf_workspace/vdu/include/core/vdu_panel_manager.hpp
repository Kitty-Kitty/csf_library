/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_panel_manager.hpp
*
*Version: 1.0
*
*Date: 23-9月-2018 20:13:29
*
*Description: Class(vdu_panel_manager) 表示矢量处理画布
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_PANEL_MANAGER_H_INCLUDED_)
#define VDU_PANEL_MANAGER_H_INCLUDED_

#include "csf_atomic.h"
#include "csf_mutex.hpp"

#include "vdu_panel_manager_interface.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * 表示矢量处理画布
		 * @author f
		 * @version 1.0
		 * @created 23-9月-2018 20:13:29
		 */
		class vdu_panel_manager : public vdu::core::vdu_panel_manager_interface
		{

		public:
			vdu_panel_manager();
			virtual ~vdu_panel_manager();

			/**
			 * 主要功能是：创建一个指定画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 * 
			 * @param index    表示需要创建的画层索引号
			 */
			virtual vdu_panel* create_panel(const csf_int32 index);
			/**
			 * 表示画布所包含的画层列表
			 */
			inline csf_map<csf_int32, vdu_panel*>& get_panels() {

				return m_panels;
			}
			/**
			 * 主要功能是：创建一个顶层画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 */
			inline virtual vdu_panel* create_top_panel() {

				return  create_panel((++m_top_index));
			}
			/**
			 * 表示最顶层的层编号，用正整数表示。
			 */
			inline csf_int32 get_top_index() {

				return m_top_index;
			}
			/**
			 * 主要功能是：创建一个底层画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 */
			inline virtual vdu_panel* create_bottom_panel() {

				return  create_panel((--m_bottom_index));
			}
			/**
			 * 表示最顶层的层编号，用正整数表示。
			 * 
			 * @param new_value
			 */
			inline void set_top_index(csf_int32 new_value) {

				m_top_index = new_value;
			}
			/**
			 * 主要功能是：根据画层索引号，销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param index    表示需要销毁的画层索引号
			 */
			inline virtual csf_int32 destory_panel(const csf_int32 index) {

				return 0;
			}
			/**
			 * 表示最底层的层编号，用负整数表示。
			 */
			inline csf_int32 get_bottom_index() {

				return m_bottom_index;
			}
			/**
			 * 主要功能是：销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示需要销毁的画层指针
			 */
			virtual csf_int32 destory_panel(const vdu_panel* panel);
			/**
			 * 表示最底层的层编号，用负整数表示。
			 * 
			 * @param new_value
			 */
			inline void set_bottom_index(csf_int32 new_value) {

				m_bottom_index = new_value;
			}
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
			 * 主要功能是：根据画层索引号，删除一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param index    表示画层索引号
			 */
			inline virtual csf_int32 remove_panel(const csf_int32 index) {

				return 0;
			}
			/**
			 * 主要功能是：销毁一个指定画层
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param panel    表示画层指针
			 */
			virtual csf_int32 remove_panel(const vdu_panel* panel);
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
			 * 主要功能是：根据画层索引号，交换两个画层次序
			 * 返回：0表示成功；其他表示失败；
			 * 
			 * @param first    表示需要交换的第一个画层索引
			 * @param second    表示需要交换的第二个画层索引
			 */
			inline virtual csf_int32 shift_panel(const csf_int32 first, const csf_int32 second) {

				return 0;
			}
			/**
			 * 主要功能是：根据索引号查询指定画层
			 * 返回：非空表示成功；csf_nullptr表示失败；
			 * 
			 * @param index    表示画层索引号
			 */
			virtual vdu_panel* find_panel(const csf_int32 index);

		private:
			/**
			 * 表示画布所包含的画层列表
			 */
			csf_map<csf_int32, vdu_panel*> m_panels;
			/**
			 * 表示最顶层的层编号，用正整数表示。
			 */
			csf_atomic_int m_top_index = 0;
			/**
			 * 表示最底层的层编号，用负整数表示。
			 */
			csf_atomic_int m_bottom_index = 0;
			/**
			 * 表示线程安全使用的互斥锁内容
			 */
			csf_shared_mutex m_mutex;

		};

	}

}
#endif // !defined(VDU_PANEL_MANAGER_H_INCLUDED_)
