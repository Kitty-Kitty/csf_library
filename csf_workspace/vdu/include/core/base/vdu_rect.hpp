/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_rect.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 14:09:58
*
*Description: Class(vdu_rect) 表示一个矩形描述信息，包括起始坐标和结束坐标
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_RECT_H_INCLUDED_)
#define VDU_RECT_H_INCLUDED_

#include "csf_base_include.h"

#include "vdu_coordinate.hpp"

namespace vdu
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示一个矩形描述信息，包括起始坐标和结束坐标
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9月-2018 14:09:58
			 */
			class vdu_rect
			{

			public:
				inline vdu_rect() {

				}
				inline virtual ~vdu_rect() {

				}
				/**
				 * 主要功能是：判断矩形数据是否合法；当bottom数值全部大于top数值时为合法；否则为非法； 返回：true表示合法；false表示不合法
				 */
				inline csf_bool is_valid() {

					if (get_top().get_x() >= get_bottom().get_x()
						&& get_top().get_y() >= get_bottom().get_y()
						&& get_top().get_z() >= get_bottom().get_z()) {

						return csf_true;
					}

					return csf_false;
				}
				/**
				 * 表示一个矩形的右下角底点坐标
				 */
				inline vdu::core::base::vdu_coordinate& get_top() {

					return m_top;
				}
				/**
				 * 表示一个矩形的右下角底点坐标
				 * 
				 * @param newVal    newVal
				 */
				inline void set_top(vdu::core::base::vdu_coordinate& newVal) {

					m_top = newVal;
				}
				/**
				 * 表示一个矩形的左上角顶点坐标
				 */
				inline vdu::core::base::vdu_coordinate& get_bottom() {

					return m_bottom;
				}
				/**
				 * 表示一个矩形的左上角顶点坐标
				 * 
				 * @param newVal    newVal
				 */
				inline void set_bottom(vdu::core::base::vdu_coordinate& newVal) {

					m_bottom = newVal;
				}
				/**
				* 主要功能是：计算分辨率的宽度
				* 返回：大于0表示分辨率宽度；小于等于0表示错误
				*/
				inline csf_double get_width() {

					return get_bottom().get_x() - get_top().get_x();
				}
				/**
				* 主要功能是：计算分辨率的高度
				* 返回：大于0表示分辨率高度；小于等于0表示错误
				*/
				inline csf_double get_height() {

					return get_bottom().get_y() - get_top().get_y();
				}
				/**
				* 主要功能是：设置rect的二维分辨率数据
				* 返回：0表示成功；非0表示错误
				*
				* @param left    表示起始的左上角x轴数值
				* @param top    表示起始的左上角y轴数值
				* @param right    表示起始的右下角x轴数值
				* @param bottom    表示起始的右下角y轴数值
				*/
				inline csf_int32 set_rect(const csf_double left
					, const csf_double top
					, const csf_double right
					, const csf_double bottom) {

					get_top().set_coordinate(left, top, 0.0);
					get_bottom().set_coordinate(right, bottom, 0.0);

					return 0;
				}
			private:
				/**
				 * 表示一个矩形的右下角底点坐标
				 */
				vdu::core::base::vdu_coordinate m_top;
				/**
				 * 表示一个矩形的左上角顶点坐标
				 */
				vdu::core::base::vdu_coordinate m_bottom;

			};

		}

	}

}
#endif // !defined(VDU_RECT_H_INCLUDED_)
