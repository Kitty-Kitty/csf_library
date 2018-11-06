/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: css_host.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:27
*
*Description: Class(css_host) ��ʾcss�豸������Ϣ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_HOST_H_INCLUDED_)
#define CSS_HOST_H_INCLUDED_

#include "css_id.hpp"
#include "css_information.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾcss�豸������Ϣ
		 * @author f
		 * @version 1.0
		 * @created 07-10��-2018 16:50:27
		 */
		class css_host
		{

		public:
			/**
			 * ��ʾ�豸������
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:27
			 */
			enum css_device_type
			{
				/**
				 * ��ʾδ֪���豸����
				 */
				m_css_device_type_none = 0x00000001
			};

			/**
			 * ��ʾ�豸�����豸����
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:27
			 */
			enum css_device_subtype
			{
				/**
				 * ��ʾδ֪���豸����
				 */
				m_css_device_subtype_none = 0x00000001
			};

			/**
			 * ��ʾ�豸��״̬��Ϣ
			 * @author f
			 * @version 1.0
			 * @created 07-10��-2018 16:50:27
			 */
			enum css_device_status
			{
				/**
				 * ��ʾδ֪���豸״̬
				 */
				m_css_device_status_none = 0x00000001
			};


			css_host();
			virtual ~css_host();

			/**
			 * ��ʾ�豸����
			 */
			inline css_device_type get_type() {

				return m_type;
			}
			/**
			 * ��ʾ�豸����
			 * 
			 * @param newVal
			 */
			inline void set_type(const css_device_type newVal) {

				m_type = newVal;
			}
			/**
			 * ��ʾ���豸����
			 */
			inline css_device_subtype get_subtype() {

				return m_subtype;
			}
			/**
			 * ��ʾ���豸����
			 * 
			 * @param newVal
			 */
			inline void set_subtype(const css_device_subtype newVal) {

				m_subtype = newVal;
			}
			/**
			 * ��ʾ�豸id��Ϣ
			 */
			inline csf_char* get_id() {

				return m_id[128];
			}
			/**
			 * ��ʾ�豸id��Ϣ
			 * 
			 * @param newVal
			 */
			inline void set_id(const csf_char* newVal) {

				m_id[128] = newVal;
			}
			/**
			 * ��ʾ�豸������
			 */
			inline csf_char* get_name() {

				return m_name[128];
			}
			/**
			 * ��ʾ�豸������
			 * 
			 * @param newVal
			 */
			inline void set_name(const csf_char* newVal) {

				m_name[128] = newVal;
			}
			/**
			 * ��ʾ�豸�İ汾��Ϣ
			 */
			inline csf_char* get_version() {

				return m_version[128];
			}
			/**
			 * ��ʾ�豸�İ汾��Ϣ
			 * 
			 * @param newVal
			 */
			inline void set_version(const csf_char* newVal) {

				m_version[128] = newVal;
			}
			/**
			 * ��ʾ�豸��״̬��
			 */
			inline css::core::css_device_status get_status() {

				return m_status;
			}
			/**
			 * ��ʾ�豸��״̬��
			 * 
			 * @param newVal
			 */
			inline void set_status(const css::core::css_device_status newVal) {

				m_status = newVal;
			}
			/**
			 * ��ʾ�豸��ʹ�õ������豸�б�
			 */
			inline csf_list<css_interface>& get_interfaces() {

				return m_interfaces;
			}
			/**
			 * ��ʾ�豸��ʹ�õ������豸�б�
			 * 
			 * @param newVal
			 */
			inline void set_interfaces(const csf_list<css_interface>& newVal) {

				m_interfaces = newVal;
			}
			/**
			 * ��ʾ�豸id��Ϣ
			 */
			css::core::css_id get_id();
			/**
			 * ��ʾ�豸id��Ϣ
			 * 
			 * @param newVal
			 */
			void set_id(css::core::css_id newVal);
			/**
			 * ��ʾ��������
			 */
			inline csf_int32 get_heartbeat_times() {

				return m_heartbeat_times;
			}
			/**
			 * ��ʾ��������
			 * 
			 * @param newVal
			 */
			inline void set_heartbeat_times(const csf_int32 newVal) {

				m_heartbeat_times = newVal;
			}
			/**
			 * ��ʾÿ�������ļ��ʱ��
			 */
			inline csf_int32 get_heartbeat_interval() {

				return m_heartbeat_interval;
			}
			/**
			 * ��ʾÿ�������ļ��ʱ��
			 * 
			 * @param newVal
			 */
			inline void set_heartbeat_interval(const csf_int32 newVal) {

				m_heartbeat_interval = newVal;
			}
			/**
			 * ��ʾ�豸��Ϣ�ṹ
			 */
			inline css_information& get_information() {

				return m_information;
			}
			/**
			 * ��ʾ�豸��Ϣ�ṹ
			 * 
			 * @param newVal
			 */
			inline void set_information(const css_information& newVal) {

				m_information = newVal;
			}

		private:
			/**
			 * ��ʾ�豸����
			 */
			css_device_type m_type = css_device_type_none;
			/**
			 * ��ʾ���豸����
			 */
			css_device_subtype m_subtype = css_device_subtype_none;
			/**
			 * ��ʾ�豸������
			 */
			csf_char m_name[128] = {0, };
			/**
			 * ��ʾ�豸�İ汾��Ϣ
			 */
			csf_char m_version[128] = {0, };
			/**
			 * ��ʾ�豸��״̬��
			 */
			css::core::css_device_status m_status = css_device_status_none;
			/**
			 * ��ʾ��������
			 */
			csf_int32 m_heartbeat_times = 0;
			/**
			 * ��ʾ�豸��ʹ�õ������豸�б�
			 */
			csf_list<css_interface> m_interfaces;
			/**
			 * ��ʾÿ�������ļ��ʱ��
			 */
			csf_int32 m_heartbeat_interval = 0;
			/**
			 * ��ʾ�豸��id��Ϣ
			 */
			css::core::css_id m_id;
			/**
			 * ��ʾ�豸��Ϣ�ṹ
			 * 
			 */
			css::core::css_information m_information;

		};

	}

}
#endif // !defined(CSS_HOST_H_INCLUDED_)
