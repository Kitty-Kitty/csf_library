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
*Date: 24-9��-2018 14:09:58
*
*Description: Class(vdu_rect) ��ʾһ������������Ϣ��������ʼ����ͽ�������
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
			 * ��ʾһ������������Ϣ��������ʼ����ͽ�������
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9��-2018 14:09:58
			 */
			class vdu_rect
			{

			public:
				inline vdu_rect() {

				}
				inline virtual ~vdu_rect() {

				}
				/**
				 * ��Ҫ�����ǣ��жϾ��������Ƿ�Ϸ�����bottom��ֵȫ������top��ֵʱΪ�Ϸ�������Ϊ�Ƿ��� ���أ�true��ʾ�Ϸ���false��ʾ���Ϸ�
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
				 * ��ʾһ�����ε����½ǵ׵�����
				 */
				inline vdu::core::base::vdu_coordinate& get_top() {

					return m_top;
				}
				/**
				 * ��ʾһ�����ε����½ǵ׵�����
				 * 
				 * @param newVal    newVal
				 */
				inline void set_top(vdu::core::base::vdu_coordinate& newVal) {

					m_top = newVal;
				}
				/**
				 * ��ʾһ�����ε����ϽǶ�������
				 */
				inline vdu::core::base::vdu_coordinate& get_bottom() {

					return m_bottom;
				}
				/**
				 * ��ʾһ�����ε����ϽǶ�������
				 * 
				 * @param newVal    newVal
				 */
				inline void set_bottom(vdu::core::base::vdu_coordinate& newVal) {

					m_bottom = newVal;
				}
				/**
				* ��Ҫ�����ǣ�����ֱ��ʵĿ��
				* ���أ�����0��ʾ�ֱ��ʿ�ȣ�С�ڵ���0��ʾ����
				*/
				inline csf_double get_width() {

					return get_bottom().get_x() - get_top().get_x();
				}
				/**
				* ��Ҫ�����ǣ�����ֱ��ʵĸ߶�
				* ���أ�����0��ʾ�ֱ��ʸ߶ȣ�С�ڵ���0��ʾ����
				*/
				inline csf_double get_height() {

					return get_bottom().get_y() - get_top().get_y();
				}
				/**
				* ��Ҫ�����ǣ�����rect�Ķ�ά�ֱ�������
				* ���أ�0��ʾ�ɹ�����0��ʾ����
				*
				* @param left    ��ʾ��ʼ�����Ͻ�x����ֵ
				* @param top    ��ʾ��ʼ�����Ͻ�y����ֵ
				* @param right    ��ʾ��ʼ�����½�x����ֵ
				* @param bottom    ��ʾ��ʼ�����½�y����ֵ
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
				 * ��ʾһ�����ε����½ǵ׵�����
				 */
				vdu::core::base::vdu_coordinate m_top;
				/**
				 * ��ʾһ�����ε����ϽǶ�������
				 */
				vdu::core::base::vdu_coordinate m_bottom;

			};

		}

	}

}
#endif // !defined(VDU_RECT_H_INCLUDED_)
