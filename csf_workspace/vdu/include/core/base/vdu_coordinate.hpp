/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_coordinate.hpp
*
*Version: 1.0
*
*Date: 24-9月-2018 14:09:56
*
*Description: Class(vdu_coordinate) 表示坐标信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_COORDINATE_H_INCLUDED_)
#define VDU_COORDINATE_H_INCLUDED_

#include "csf_base_include.h"

namespace vdu
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示坐标信息
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9月-2018 14:09:56
			 */
			class vdu_coordinate
			{

			public:
				inline vdu_coordinate()
					: m_x(0.0)
					, m_y(0.0)
					, m_z(0.0) {

				}

				inline ~vdu_coordinate() {

				}

				/**
				 * 表示坐标x轴数据
				 */
				inline csf_double& get_x() {

					return m_x;
				}
				/**
				 * 表示坐标x轴数据
				 * 
				 * @param new_value    new_value
				 */
				inline void set_x(const csf_double& new_value) {

					m_x = new_value;
				}
				/**
				 * 表示坐标y轴数据
				 */
				inline csf_double& get_y() {

					return m_y;
				}
				/**
				 * 表示坐标y轴数据
				 * 
				 * @param new_value    new_value
				 */
				inline void set_y(const csf_double& new_value) {

					m_y = new_value;
				}
				/**
				 * 表示坐标z轴数据
				 */
				inline csf_double& get_z() {

					return m_z;
				}
				/**
				 * 表示坐标z轴数据
				 * 
				 * @param new_value    new_value
				 */
				inline void set_z(const csf_double& new_value) {

					m_z = new_value;
				}
				/**
				* 主要功能是：设置坐标的数值
				* 返回：0表示成功；非表示错误；
				*
				* @param x    表示坐标x轴数据
				*
				* @param y    表示坐标y轴数据
				*
				* @param z    表示坐标z轴数据
				*
				*/
				inline csf_int32 set_coordinate(const csf_double& x, const csf_double& y, const csf_double& z = 0.0) {

					set_x(x);
					set_y(y);
					set_z(z);

					return 0;
				}
			private:
				/**
				 * 表示坐标x轴数据
				 */
				csf_double m_x = 0.0;
				/**
				 * 表示坐标y轴数据
				 */
				csf_double m_y = 0.0;
				/**
				 * 表示坐标z轴数据
				 */
				csf_double m_z = 0.0;

			};

		}

	}

}
#endif // !defined(VDU_COORDINATE_H_INCLUDED_)
