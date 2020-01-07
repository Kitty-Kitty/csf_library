/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: vdu_canvas.hpp
*
*Version: 1.0
*
*Date: 23-9��-2018 20:13:28
*
*Description: Class(vdu_canvas) ��ʾʸ��������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_CANVAS_H_INCLUDED_)
#define VDU_CANVAS_H_INCLUDED_

#include "vdu_panel.hpp"
#include "csf_app.hpp"
#include "vdu_panel_manager.hpp"
#include "vdu_canvas_interface.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * ��ʾʸ��������
		 * @author fangzhenmu
		 * @version 1.0
		 * @created 23-9��-2018 20:13:28
		 */
		class vdu_canvas : public vdu::core::vdu_panel, public csf::core::module::csf_app, public vdu::core::vdu_panel_manager, public vdu::core::vdu_canvas_interface
		{

		public:
			/**
			 * ��ʾ������������
			 * @author f
			 * @version 1.0
			 * @created 23-9��-2018 20:13:28
			 */
			typedef enum vdu_canvas_type_enum
			{
				/**
				 * ��ʾĬ�ϵ�δ֪��������
				 */
				vdu_canvas_type_none = 0x00000000,
				/**
				 * ��ʾqt��������
				 */
				vdu_canvas_type_qt = 0x00000001
			} vdu_canvas_type;


			vdu_canvas();
			virtual ~vdu_canvas();

			/**
			 * 
			 * @param type    ��ʾ����������
			 */
			vdu_canvas(const vdu_canvas_type type);
			/**
			 * ģ���ʼ��
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * ģ������
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * ģ��ֹͣ
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr);

			/**
			* ��ʾ����������
			*/
			inline vdu_canvas_type get_type() {

				return m_type;
			}
			/**
			* ��ʾ����������
			*
			* @param newVal
			*/
			inline void set_type(vdu_canvas_type newVal) {

				m_type = newVal;
			}

		private:
			/**
			* ��ʾ����������
			*/
			vdu_canvas_type m_type = vdu_canvas_type_none;
		};

	}

}
#endif // !defined(VDU_CANVAS_H_INCLUDED_)
