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
*Date: 23-9��-2018 20:20:21
*
*Description: Class(vdu_panel) ��ʾʸ������ͼ��
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
		 * ��ʾʸ������ͼ��
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 23-9��-2018 20:20:21
		 */
		class vdu_panel : public vdu::core::vdu_box, public csf::core::module::csf_device, public vdu::core::vdu_panel_interface
		{

		public:
			/**
			 * ��ʾ���������
			 * @author f
			 * @version 1.0
			 * @created 23-9��-2018 20:20:21
			 */
			typedef enum vdu_panel_type_enum
			{
				/**
				 * ��ʾĬ�ϵ�δ֪��������
				 */
				vdu_panel_type_none = 0x00000000,
				/**
				 * ��ʾqt��������
				 */
				vdu_panel_type_qt = 0x00000001
			} vdu_panel_type;


			vdu_panel();
			virtual ~vdu_panel();

			/**
			 * 
			 * @param type    ��ʾ���������
			 */
			vdu_panel(const vdu_panel_type type);
			/**
			 * ģ���ʼ��
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

				return  0;
			}
			/**
			 * ��ʾpanel������canvas����
			 */
			inline vdu_canvas* get_canvas() {

				return m_canvas;
			}
			/**
			 * ģ������
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

				return  0;
			}
			/**
			 * ��ʾpanel������canvas����
			 * 
			 * @param newVal
			 */
			inline void set_canvas(vdu_canvas* newVal) {

				m_canvas = newVal;
			}
			/**
			 * ģ��ֹͣ
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

				return  0;
			}
			/**
			* ��ʾ���������
			*/
			inline vdu_panel_type get_type() {

				return m_type;
			}
			/**
			* ��ʾ���������
			*
			* @param newVal
			*/
			inline void set_type(vdu_panel_type newVal) {

				m_type = newVal;
			}
		private:
			/**
			 * ��ʾpanel������canvas����
			 */
			vdu::core::vdu_canvas *m_canvas;
			/**
			* ��ʾ���������
			*/
			vdu_panel_type m_type = vdu_panel_type_none;
		};

	}

}
#endif // !defined(VDU_PANEL_H_INCLUDED_)
