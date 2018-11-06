/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_box.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 14:09:56
*
*Description: Class(vdu_box) 描述一个区域信息，是一个最基础的空间对象
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_BOX_H_INCLUDED_)
#define VDU_BOX_H_INCLUDED_

#include "csf_base_include.h"
#include "vdu_rect.hpp"

using namespace vdu::core;

namespace vdu
{
	namespace core
	{
		/**
		* 这里定义两个类，解决引用问题
		* @author fangzhenmu
		* @version 1.0
		* @created 17-9月-2018 9:16:37
		*/
		class vdu_panel;
		class vdu_canvas;

		/**
		 * 描述一个区域信息，是一个最基础的空间对象
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 24-9月-2018 14:09:56
		 */
		class vdu_box
		{

		public:
			vdu_box();
			virtual ~vdu_box();

			/**
			 * 表示画布的处理尺寸大小
			 */
			inline vdu::core::base::vdu_rect& get_rect() {

				return m_rect;
			}
			/**
			 * 表示画布的处理尺寸大小
			 * 
			 * @param new_value
			 */
			inline void set_rect(vdu::core::base::vdu_rect& new_value) {

				m_rect = new_value;
			}

		private:
			/**
			 * 表示画布的处理尺寸大小
			 */
			vdu::core::base::vdu_rect m_rect;

		};

	}

}
#endif // !defined(VDU_BOX_H_INCLUDED_)
