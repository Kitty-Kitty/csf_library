/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: vdu_panel_manager_interface.hpp
*
*Version: 1.0
*
*Date: 23-9��-2018 20:13:29
*
*Description: Interface(vdu_panel_manager_interface) ��ʾ�����������Ĳ����ӿ�
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(VDU_PANEL_MANAGER_INTERFACE_H_INCLUDED_)
#define VDU_PANEL_MANAGER_INTERFACE_H_INCLUDED_

#include "csf_base_include.h"
#include "vdu_box.hpp"

namespace vdu
{
	namespace core
	{
		/**
		 * ��ʾ�����������Ĳ����ӿ�
		 * @author f
		 * @version 1.0
		 * @created 23-9��-2018 20:13:29
		 */
		class vdu_panel_manager_interface
		{

		public:
			vdu_panel_manager_interface() {

			}

			virtual ~vdu_panel_manager_interface() {

			}

			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ��Ҫ�����Ļ���������
			 */
			virtual vdu_panel* create_panel(const csf_int32 index) =0;
			/**
			 * ��Ҫ�����ǣ�����һ�����㻭��
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 */
			inline virtual vdu_panel* create_top_panel() =0;
			/**
			 * ��Ҫ�����ǣ�����һ���ײ㻭��
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 */
			inline virtual vdu_panel* create_bottom_panel() =0;
			/**
			 * ��Ҫ�����ǣ����ݻ��������ţ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ��Ҫ���ٵĻ���������
			 */
			inline virtual csf_int32 destory_panel(const csf_int32 index) =0;
			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ��Ҫ���ٵĻ���ָ��
			 */
			virtual csf_int32 destory_panel(const vdu_panel* panel) =0;
			/**
			 * ��Ҫ�����ǣ����ݻ��������ţ����ָ���Ļ���
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 * @param panel    ��ʾ�������
			 */
			inline virtual csf_int32 add_panel(const csf_int32 index, const vdu_panel* panel) =0;
			/**
			 * ��Ҫ�����ǣ����ָ���Ļ���
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ�������
			 */
			virtual csf_int32 add_panel(const vdu_panel* panel) =0;
			/**
			 * ��Ҫ�����ǣ����ݻ��������ţ�ɾ��һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 */
			inline virtual csf_int32 remove_panel(const csf_int32 index) =0;
			/**
			 * ��Ҫ�����ǣ�����һ��ָ������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ����ָ��
			 */
			virtual csf_int32 remove_panel(const vdu_panel* panel) =0;
			/**
			 * ��Ҫ�����ǣ����»����������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param panel    ��ʾ��Ҫ�����µĻ������
			 * @param index    ��ʾ����������
			 */
			virtual csf_int32 update_panel(const vdu_panel* panel, const csf_int32 index) =0;
			/**
			 * ��Ҫ�����ǣ����ݻ�����󣬽��������������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param first    ��ʾ��Ҫ�����ĵ�һ���������
			 * @param second    ��ʾ��Ҫ�����ĵڶ����������
			 */
			virtual csf_int32 shift_panel(const vdu_panel* first, const vdu_panel* second) =0;
			/**
			 * ��Ҫ�����ǣ����ݻ��������ţ����������������
			 * ���أ�0��ʾ�ɹ���������ʾʧ�ܣ�
			 * 
			 * @param first    ��ʾ��Ҫ�����ĵ�һ����������
			 * @param second    ��ʾ��Ҫ�����ĵڶ�����������
			 */
			inline virtual csf_int32 shift_panel(const csf_int32 first, const csf_int32 second) =0;
			/**
			 * ��Ҫ�����ǣ����������Ų�ѯָ������
			 * ���أ��ǿձ�ʾ�ɹ���csf_nullptr��ʾʧ�ܣ�
			 * 
			 * @param index    ��ʾ����������
			 */
			virtual vdu_panel* find_panel(const csf_int32 index) =0;

		};

	}

}
#endif // !defined(VDU_PANEL_MANAGER_INTERFACE_H_INCLUDED_)
