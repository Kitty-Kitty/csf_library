/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_request_manager.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:30
*
*Description: Class(css_request_manager) ��ʾ�������������Ҫ���������������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_REQUEST_MANAGER_H_INCLUDED_)
#define CSS_REQUEST_MANAGER_H_INCLUDED_

#include "csf_manager.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾ�������������Ҫ���������������
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:30
		 */
		class css_request_manager : public csf::core::module::csf_manager
		{

		public:
			css_request_manager();
			virtual ~css_request_manager();

			/**
			 * ģ���ʼ��
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ģ������
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 start(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ģ��ֹͣ
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 stop(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ��ʾ�������
			 */
			inline csf_csfqueue<css_request> get_request_queue() {

				return m_request_queue;
			}
			/**
			 * ��ʾ�������
			 * 
			 * @param newVal
			 */
			inline csf_void set_request_queue(const csf_csfqueue<css_request>& newVal) {

				m_request_queue = newVal;
			}
			/**
			 * ��ʾ������function�б�
			 */
			inline csf_map<css_semh_command, css_semh_request_function> get_semh_request_function() {

				return m_semh_request_function;
			}
			/**
			 * ��ʾ�̴߳���������Ҫ�Ӷ����л�ȡ������д���
			 */
			csf_void process();
			/**
			 * ��ʾ������function�б�
			 * 
			 * @param newVal
			 */
			inline csf_void set_semh_request_function(const csf_map<css_semh_command, css_semh_request_function> newVal) {

				m_semh_request_function = newVal;
			}

		private:
			/**
			 * ��ʾ�������
			 */
			csf_csfqueue<css_request> m_request_queue;
			/**
			 * ��ʾ������function�б�
			 */
			csf_map<css_semh_command, css_semh_request_function> m_semh_request_function;

		};

	}

}
#endif // !defined(CSS_REQUEST_MANAGER_H_INCLUDED_)
