/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_panel_manager.hpp
*
*Version: 1.0
*
*Date: 23-9��-2018 20:13:29
*
*Description: Class(vdu_panel_manager) ��ʾʸ��������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_PANEL_MANAGER_H_INCLUDED_)
#define VDU_PANEL_MANAGER_H_INCLUDED_

#include "csf_atomic.h"
#include "csf_mutex.hpp"

#include "vdu_panel_manager_interface.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * ��ʾʸ��������
		 * @author f
		 * @version 1.0
		 * @created 23-9��-2018 20:13:29
		 */
		class vdu_panel_manager : public vdu::core::vdu_panel_manager_interface
		{

		public:
			vdu_panel_manager();
			virtual ~vdu_panel_manager();

			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ��Ҫ�����Ļ���������
			 */
			virtual vdu_panel* create_panel(const csf_int32 index);
			/**
			 * ��ʾ�����������Ļ����б�
			 */
			inline csf_map<csf_int32, vdu_panel*>& get_panels() {

				return m_panels;
			}
			/**
			 * ��Ҫ�����ǣ�����һ�����㻭��
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 */
			inline virtual vdu_panel* create_top_panel() {

				return  create_panel((++m_top_index));
			}
			/**
			 * ��ʾ���Ĳ��ţ�����������ʾ��
			 */
			inline csf_int32 get_top_index() {

				return m_top_index;
			}
			/**
			 * ��Ҫ�����ǣ�����һ���ײ㻭��
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 */
			inline virtual vdu_panel* create_bottom_panel() {

				return  create_panel((--m_bottom_index));
			}
			/**
			 * ��ʾ���Ĳ��ţ�����������ʾ��
			 * 
			 * @param new_value
			 */
			inline void set_top_index(csf_int32 new_value) {

				m_top_index = new_value;
			}
			/**
			 * ��Ҫ�����ǣ����ݻ��������ţ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ��Ҫ���ٵĻ���������
			 */
			inline virtual csf_int32 destory_panel(const csf_int32 index) {

				return 0;
			}
			/**
			 * ��ʾ��ײ�Ĳ��ţ��ø�������ʾ��
			 */
			inline csf_int32 get_bottom_index() {

				return m_bottom_index;
			}
			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ��Ҫ���ٵĻ���ָ��
			 */
			virtual csf_int32 destory_panel(const vdu_panel* panel);
			/**
			 * ��ʾ��ײ�Ĳ��ţ��ø�������ʾ��
			 * 
			 * @param new_value
			 */
			inline void set_bottom_index(csf_int32 new_value) {

				m_bottom_index = new_value;
			}
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
			 * ��Ҫ�����ǣ����ݻ��������ţ�ɾ��һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 */
			inline virtual csf_int32 remove_panel(const csf_int32 index) {

				return 0;
			}
			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ����ָ��
			 */
			virtual csf_int32 remove_panel(const vdu_panel* panel);
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
			 * ��Ҫ�����ǣ����ݻ��������ţ����������������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param first    ��ʾ��Ҫ�����ĵ�һ����������
			 * @param second    ��ʾ��Ҫ�����ĵڶ�����������
			 */
			inline virtual csf_int32 shift_panel(const csf_int32 first, const csf_int32 second) {

				return 0;
			}
			/**
			 * ��Ҫ�����ǣ����������Ų�ѯָ������
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 */
			virtual vdu_panel* find_panel(const csf_int32 index);

		private:
			/**
			 * ��ʾ�����������Ļ����б�
			 */
			csf_map<csf_int32, vdu_panel*> m_panels;
			/**
			 * ��ʾ���Ĳ��ţ�����������ʾ��
			 */
			csf_atomic_int m_top_index = 0;
			/**
			 * ��ʾ��ײ�Ĳ��ţ��ø�������ʾ��
			 */
			csf_atomic_int m_bottom_index = 0;
			/**
			 * ��ʾ�̰߳�ȫʹ�õĻ���������
			 */
			csf_shared_mutex m_mutex;

		};

	}

}
#endif // !defined(VDU_PANEL_MANAGER_H_INCLUDED_)
