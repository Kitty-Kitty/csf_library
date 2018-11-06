/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_server.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:32
*
*Description: Class(css_server) ��ʾʹ�õ�css������
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_SERVER_H_INCLUDED_)
#define CSS_SERVER_H_INCLUDED_

#include "csf_message_manager.hpp"
#include "css_app.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾʹ�õ�css������
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:32
		 */
		class css_server : public css::core::css_app
		{

		public:
			css_server();
			virtual ~css_server();

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

		};

	}

}
#endif // !defined(CSS_SERVER_H_INCLUDED_)
