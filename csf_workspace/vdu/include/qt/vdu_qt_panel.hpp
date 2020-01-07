/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_qt_panel.hpp
*
*Version: 1.0
*
*Date: 24-9��-2018 11:24:36
*
*Description: Class(vdu_qt_panel) ��ʾ����QTʵ�ֵ�ʸ������Ԫͼ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_QT_PANEL_H_INCLUDED_)
#define VDU_QT_PANEL_H_INCLUDED_

#include "vdu_qt_include.h"

#include "vdu_panel.hpp"

namespace vdu
{
	namespace qt
	{
		/**
		 * ��ʾ����QTʵ�ֵ�ʸ������Ԫͼ��
		 * @author f
		 * @version 1.0
		 * @created 24-9��-2018 11:24:36
		 */
		class vdu_qt_panel : public vdu::core::vdu_panel
		{

		public:
			vdu_qt_panel();
			virtual ~vdu_qt_panel();
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
			 * ��ʾһ��svg render����
			 */
			inline QSvgRenderer* get_render() {

				return m_render;
			}
			/**
			 * ��ʾһ��svgͼ�����
			 */
			inline QGraphicsSvgItem* get_item() {

				return m_item;
			}
		private:
			/**
			* ��ʾһ��svg render����
			*
			* @param newVal
			*/
			inline void set_render(QSvgRenderer* newVal) {

				m_render = newVal;
			}
			/**
			* ��ʾһ��svgͼ�����
			*
			* @param newVal
			*/
			inline void set_item(QGraphicsSvgItem* newVal) {

				m_item = newVal;
			}
		private:
			/**
			 * ��ʾһ��svgͼ�����
			 */
			QGraphicsSvgItem* m_item = csf_nullptr;
			/**
			 * ��ʾһ��svg render����
			 */
			QSvgRenderer* m_render = csf_nullptr;

		};

	}

}
#endif // !defined(VDU_QT_PANEL_H_INCLUDED_)
