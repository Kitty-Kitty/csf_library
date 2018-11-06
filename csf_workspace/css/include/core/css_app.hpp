/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu@aliyun.com
*
*File name: css_app.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:25
*
*Description: Class(css_app) ��ƴ�ӷ�������ʵ��
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_APP_H_INCLUDED_)
#define CSS_APP_H_INCLUDED_

#include "csf_message_manager.hpp"
#include "csf_app.hpp"
#include "css_server_interface.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ƴ�ӷ�������ʵ��
		 * @author fangzhenmu@aliyun.com
		 * @version 1.0
		 * @created 07-10��-2018 16:50:25
		 */
		class css_app : public csf::core::module::csf_app, public css::core::css_server_interface
		{

		public:
			css_app();
			virtual ~css_app();

			/**
			 * ��ʾ���ù�����
			 */
			inline csf_configure_manager* get_configure_manager() {

				return m_configure_manager;
			}
			/**
			 * ģ���ʼ��
			 * 
			 * @param conf_mg    ��ʾ�����ļ���Ϣ
			 */
			virtual csf::core::base::csf_int32 init(const csf_configure_manager * conf_mg = csf_null);
			/**
			 * ��ʾ���ù�����
			 * 
			 * @param newVal
			 */
			inline csf::core::base::csf_void set_configure_manager(csf_configure_manager* newVal) {

				m_configure_manager = newVal;
			}
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
			csf_message_manager& get_message_manager();
			/**
			 * 
			 * @param newVal
			 */
			void set_message_manager(csf::core::system::message::csf_message_manager newVal);
			/**
			 * ��ʾ����һ��message����
			 * 
			 * @param message    ��ʾ��ӵ���Ϣ����
			 */
			virtual csf_int32 post(csf_message& message);
			/**
			 * �������͡��ص���������Ϣ���ݴ�����Ϣ
			 * 
			 * @param type    ��ʾ��Ϣ����
			 * @param callback    ��ʾ�ص�����
			 * @param element    ��ʾ��Ϣ����
			 */
			virtual csf_int32 post(csf::core::system::message::csf_message_type type, csf::core::system::message::csf_message_callback callback, csf_element& element);
			/**
			 * ��ʾ������Ϣ����
			 */
			virtual csf::core::system::message::csf_message pop();
			/**
			 * ��ʾ����һ��message����
			 * 
			 * @param message    ��ʾ��ӵ���Ϣ����
			 */
			virtual csf_int32 post(const csf_message& message);
			/**
			 * �������͡��ص���������Ϣ���ݴ�����Ϣ
			 * 
			 * @param type    ��ʾ��Ϣ����
			 * @param callback    ��ʾ�ص�����
			 * @param element    ��ʾ��Ϣ����
			 */
			virtual csf_int32 post(const csf::core::system::message::csf_message_type type, const csf::core::system::message::csf_message_callback callback, const csf_element& element);
			/**
			 * ��ʾ������Ϣ����
			 */
			virtual csf::core::system::message::csf_message pop();

		private:
			/**
			 * ��ʾ��Ϣ������
			 */
			csf::core::system::message::csf_message_manager m_message_manager;

		};

	}

}
#endif // !defined(CSS_APP_H_INCLUDED_)
