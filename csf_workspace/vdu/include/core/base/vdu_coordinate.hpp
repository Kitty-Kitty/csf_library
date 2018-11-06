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
*Date: 24-9��-2018 14:09:56
*
*Description: Class(vdu_coordinate) ��ʾ������Ϣ
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
			 * ��ʾ������Ϣ
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 24-9��-2018 14:09:56
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
				 * ��ʾ����x������
				 */
				inline csf_double& get_x() {

					return m_x;
				}
				/**
				 * ��ʾ����x������
				 * 
				 * @param new_value    new_value
				 */
				inline void set_x(const csf_double& new_value) {

					m_x = new_value;
				}
				/**
				 * ��ʾ����y������
				 */
				inline csf_double& get_y() {

					return m_y;
				}
				/**
				 * ��ʾ����y������
				 * 
				 * @param new_value    new_value
				 */
				inline void set_y(const csf_double& new_value) {

					m_y = new_value;
				}
				/**
				 * ��ʾ����z������
				 */
				inline csf_double& get_z() {

					return m_z;
				}
				/**
				 * ��ʾ����z������
				 * 
				 * @param new_value    new_value
				 */
				inline void set_z(const csf_double& new_value) {

					m_z = new_value;
				}
				/**
				* ��Ҫ�����ǣ������������ֵ
				* ���أ�0��ʾ�ɹ����Ǳ�ʾ����
				*
				* @param x    ��ʾ����x������
				*
				* @param y    ��ʾ����y������
				*
				* @param z    ��ʾ����z������
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
				 * ��ʾ����x������
				 */
				csf_double m_x = 0.0;
				/**
				 * ��ʾ����y������
				 */
				csf_double m_y = 0.0;
				/**
				 * ��ʾ����z������
				 */
				csf_double m_z = 0.0;

			};

		}

	}

}
#endif // !defined(VDU_COORDINATE_H_INCLUDED_)
