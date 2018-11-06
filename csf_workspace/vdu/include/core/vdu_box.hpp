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
*Date: 24-9��-2018 14:09:56
*
*Description: Class(vdu_box) ����һ��������Ϣ����һ��������Ŀռ����
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
		* ���ﶨ�������࣬�����������
		* @author fangzhenmu
		* @version 1.0
		* @created 17-9��-2018 9:16:37
		*/
		class vdu_panel;
		class vdu_canvas;

		/**
		 * ����һ��������Ϣ����һ��������Ŀռ����
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 24-9��-2018 14:09:56
		 */
		class vdu_box
		{

		public:
			vdu_box();
			virtual ~vdu_box();

			/**
			 * ��ʾ�����Ĵ���ߴ��С
			 */
			inline vdu::core::base::vdu_rect& get_rect() {

				return m_rect;
			}
			/**
			 * ��ʾ�����Ĵ���ߴ��С
			 * 
			 * @param new_value
			 */
			inline void set_rect(vdu::core::base::vdu_rect& new_value) {

				m_rect = new_value;
			}

		private:
			/**
			 * ��ʾ�����Ĵ���ߴ��С
			 */
			vdu::core::base::vdu_rect m_rect;

		};

	}

}
#endif // !defined(VDU_BOX_H_INCLUDED_)
