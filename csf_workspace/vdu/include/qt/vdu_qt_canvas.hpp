/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_qt_canvas.hpp
*
*Version: 1.0
*
*Date: 24-9��-2018 11:48:22
*
*Description: Class(vdu_qt_canvas) ��ʾ����QTʵ�ֵ�ʸ��������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_QT_CANVAS_H_INCLUDED_)
#define VDU_QT_CANVAS_H_INCLUDED_

#include "vdu_qt_include.h"

#include "vdu_canvas.hpp"

namespace vdu
{
	namespace qt
	{
		/**
		 * ��ʾ����QTʵ�ֵ�ʸ��������
		 * @author f
		 * @version 1.0
		 * @created 24-9��-2018 11:48:22
		 */
		class vdu_qt_canvas : public vdu::core::vdu_canvas
		{

		public:
			vdu_qt_canvas();
			virtual ~vdu_qt_canvas();

			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ��Ҫ�����Ļ���������
			 */
			virtual vdu_panel* create_panel(const csf_int32 index);
			/**
			 * ��Ҫ�����ǣ�����һ�����㻭��
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 */
			inline virtual vdu_panel* create_top_panel() {

				return  csf_nullptr;
			}
			/**
			 * ��Ҫ�����ǣ�����һ���ײ㻭��
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 */
			inline virtual vdu_panel* create_bottom_panel() {

				return  csf_nullptr;
			}
			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ��Ҫ���ٵĻ���ָ��
			 */
			virtual csf_int32 destory_panel(const vdu_panel* panel);
			/**
			 * ģ���ʼ��
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr);
			/**
			 * ��Ҫ�����ǣ����»����������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ��Ҫ�����µĻ������
			 * @param index    ��ʾ����������
			 */
			virtual csf_int32 update_panel(const vdu_panel* panel, const csf_int32 index);
			/**
			 * ��Ҫ�����ǣ����ݻ�����󣬽��������������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param first    ��ʾ��Ҫ�����ĵ�һ���������
			 * @param second    ��ʾ��Ҫ�����ĵڶ����������
			 */
			virtual csf_int32 shift_panel(const vdu_panel* first, const vdu_panel* second);
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
			 * ��Ҫ�����ǣ����������Ų�ѯָ������
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 */
			virtual vdu_panel* find_panel(const csf_int32 index);
			/**
			 * ��ʾQT��application����
			 */
			inline QApplication* get_app() {

				return m_app;
			}
			/**
			 * ��ʾͼ�ε���ͼ����
			 */
			inline QGraphicsView* get_view() {

				return m_view;
			}
			/**
			 * ��Ҫ�����ǣ���ָ�������豸Ϊ����
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ����ָ��
			 */
			virtual csf_int32 set_top(const vdu_panel* panel);
			/**
			 * ��ʾͼ�γ���
			 */
			inline QGraphicsScene* get_scene() {

				return m_scene;
			}
			/**
			 * ��Ҫ�����ǣ���ָ�������豸Ϊ�ײ�
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ����ָ��
			 */
			virtual csf_int32 set_bottom(const vdu_panel* panel);

		protected:
			/**
			 * ��Ҫ�����ǣ����ݻ��������ţ����ָ���Ļ���
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 * @param panel    ��ʾ�������
			 */
			inline virtual csf_int32 add_panel(const csf_int32 index, const vdu_panel* panel) {

				return 0;
			}
			/**
			 * ��Ҫ�����ǣ����ָ���Ļ���
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ�������
			 */
			virtual csf_int32 add_panel(const vdu_panel* panel);
			/**
			 * ��Ҫ�����ǣ�ɾ��һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ����ָ��
			 */
			virtual csf_int32 delete_panel(const vdu_panel* panel);
			/**
			* ��ʾQT��application����
			*
			* @param newVal
			*/
			inline void set_app(QApplication* newVal) {

				m_app = newVal;
			}
			/**
			* ��ʾͼ�ε���ͼ����
			*
			* @param newVal
			*/
			inline void set_view(QGraphicsView* newVal) {

				m_view = newVal;
			}
			/**
			* ��ʾͼ�γ���
			*
			* @param newVal
			*/
			inline void set_scene(QGraphicsScene* newVal) {

				m_scene = newVal;
			}
		private:
			/**
			 * ��ʾQT��application����
			 */
			QApplication* m_app = csf_nullptr;
			/**
			 * ��ʾͼ�ε���ͼ����
			 */
			QGraphicsView* m_view = csf_nullptr;
			/**
			 * ��ʾͼ�γ���
			 */
			QGraphicsScene* m_scene = csf_nullptr;

		};

	}

}
#endif // !defined(VDU_QT_CANVAS_H_INCLUDED_)
