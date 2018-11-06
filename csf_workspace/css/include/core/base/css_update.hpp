/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: Administrator
*
*File name: css_update.hpp
*
*Version: 1.0
*
*Date: 07-10��-2018 16:50:32
*
*Description: Class(css_update) ��ʾcssϵͳ�ĸ�����Ϣ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSS_UPDATE_H_INCLUDED_)
#define CSS_UPDATE_H_INCLUDED_

#include "csf_pfstring.hpp"

namespace css
{
	namespace core
	{
		/**
		 * ��ʾcssϵͳ�ĸ�����Ϣ
		 * @author Administrator
		 * @version 1.0
		 * @created 07-10��-2018 16:50:32
		 */
		class css_update
		{

		public:
			css_update();
			virtual ~css_update();

			/**
			 * ��ʾ�������õ��豸����
			 */
			inline css::core::css_device_type get_type() {

				return m_type;
			}
			/**
			 * ��ʾ�������õ��豸����
			 * 
			 * @param newVal
			 */
			inline csf_void set_type(const css::core::css_device_type newVal) {

				m_type = newVal;
			}
			/**
			 * ��ʾ�������Ĵ����ʽ
			 */
			inline css_packet_type get_packet_type() {

				return m_packet_type;
			}
			/**
			 * ��ʾ�������Ĵ����ʽ
			 * 
			 * @param newVal
			 */
			inline csf_void set_packet_type(const css_packet_type newVal) {

				m_packet_type = newVal;
			}
			/**
			 * ��ʾ�������õ��豸����
			 */
			inline css::core::css_device_type get_device_type() {

				return m_device_type;
			}
			/**
			 * ��ʾ�������õ��豸����
			 * 
			 * @param newVal
			 */
			inline csf_void set_device_type(const css::core::css_device_type newVal) {

				m_device_type = newVal;
			}
			/**
			 * <font color="#008000">���°���������</font>
			 */
			inline csf::core::base::csf_pfstring& get_program_file() {

				return m_program_file;
			}
			/**
			 * <font color="#008000">���°���������</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_program_file(const csf::core::base::csf_pfstring& newVal) {

				m_program_file = newVal;
			}
			/**
			 * <font color="#008000">���°��г�����������</font>
			 */
			inline csf::core::base::csf_pfstring& get_file_data() {

				return m_file_data;
			}
			/**
			 * <font color="#008000">���°��г�����������</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_file_data(const csf::core::base::csf_pfstring& newVal) {

				m_file_data = newVal;
			}
			/**
			 * <font color="#008000">��ʾʹ�ñ�ʶ</font>
			 */
			inline css_update_operation get_operation_flag() {

				return m_operation_flag;
			}
			/**
			 * <font color="#008000">��ʾʹ�ñ�ʶ</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_operation_flag(const css_update_operation newVal) {

				m_operation_flag = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�汾������Ϣ</font>
			 */
			inline csf_uint32 get_version() {

				return m_version_addtion;
			}
			/**
			 * <font color="#008000">��ʾ�汾������Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_version(const csf_uint32 newVal) {

				m_version_addtion = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�Ƿ����conf/conf.
			 * xml�ļ���TRUE��ʾ��Ҫ���£����ʱ��IP���ܻᱻ�޸ģ���FLASE��ʾ����Ҫ����</font>
			 */
			inline csf_bool get_is_update_conf_file() {

				return m_is_update_conf_file;
			}
			/**
			 * <font color="#008000">��ʾ�Ƿ����conf/conf.
			 * xml�ļ���TRUE��ʾ��Ҫ���£����ʱ��IP���ܻᱻ�޸ģ���FLASE��ʾ����Ҫ����</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_is_update_conf_file(const csf_bool newVal) {

				m_is_update_conf_file = newVal;
			}
			/**
			 * <font
			 * color="#008000">��ʾ�Ƿ����data�е������ļ���TRUE��ʾ��Ҫ���£����ʱ�����ݿ��ܱ�ɾ������FLASE��ʾ����Ҫ����</font>
			 */
			inline csf_bool get_is_update_data_file() {

				return m_is_update_data_file;
			}
			/**
			 * <font
			 * color="#008000">��ʾ�Ƿ����data�е������ļ���TRUE��ʾ��Ҫ���£����ʱ�����ݿ��ܱ�ɾ������FLASE��ʾ����Ҫ����</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_is_update_data_file(const csf_bool newVal) {

				m_is_update_data_file = newVal;
			}
			/**
			 * <font color="#008000">��ʾ����ķ���ʱ����Ϣ</font>
			 */
			inline csf_uint64 get_time() {

				return m_time;
			}
			/**
			 * <font color="#008000">��ʾ����ķ���ʱ����Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_time(const csf_uint64 newVal) {

				m_time = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�豸�ı���ID</font>
			 */
			inline csf_string& get_device_id() {

				return m_device_id;
			}
			/**
			 * <font color="#008000">��ʾ�豸�ı���ID</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_device_id(const csf_string& newVal) {

				m_device_id = newVal;
			}
			/**
			 * <font color="#008000">��ʾ���������</font>
			 */
			inline csf_string& get_packet_name() {

				return m_packet_name;
			}
			/**
			 * <font color="#008000">��ʾ���������</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_packet_name(const csf_string& newVal) {

				m_packet_name = newVal;
			}
			/**
			 * <font color="#008000">��ʾ����ĸ�����Ϣ</font>
			 */
			inline csf_string& get_change_log() {

				return m_change_log;
			}
			/**
			 * <font color="#008000">��ʾ����ĸ�����Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_change_log(const csf_string& newVal) {

				m_change_log = newVal;
			}
			/**
			 * <font color="#008000">��ʾƽ̨Ӳ����Ϣ</font>
			 */
			inline csf_string& get_platform_hardware() {

				return m_platform_hardware;
			}
			/**
			 * <font color="#008000">��ʾƽ̨Ӳ����Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_platform_hardware(const csf_string& newVal) {

				m_platform_hardware = newVal;
			}
			/**
			 * <font color="#008000">��ʾƽ̨�����Ϣ</font>
			 */
			inline csf_string& get_platform_software() {

				return m_platform_software;
			}
			/**
			 * <font color="#008000">��ʾƽ̨�����Ϣ</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_platform_software(const csf_string& newVal) {

				m_platform_software = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�豸���ͺ�</font>
			 */
			inline csf_string& get_serial_master() {

				return m_serial_master;
			}
			/**
			 * <font color="#008000">��ʾ�豸���ͺ�</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_serial_master(const csf_string& newVal) {

				m_serial_master = newVal;
			}
			/**
			 * <font color="#008000">��ʾ�豸���ͺ�</font>
			 */
			inline csf_string& get_serial_slave() {

				return m_serial_slave;
			}
			/**
			 * <font color="#008000">��ʾ�豸���ͺ�</font>
			 * 
			 * @param newVal
			 */
			inline csf_void set_serial_slave(const csf_string& newVal) {

				m_serial_slave = newVal;
			}

		private:
			/**
			 * ��ʾ�������õ��豸����
			 */
			css::core::css_device_type m_device_type = css_device_type_none;
			/**
			 * ��ʾ�������Ĵ����ʽ
			 */
			css_packet_type m_packet_type = css_packet_type_none;
			/**
			 * <font color="#008000">���°���������</font>
			 */
			csf::core::base::csf_pfstring m_program_file;
			/**
			 * <font color="#008000">���°��г�����������</font>
			 */
			csf::core::base::csf_pfstring m_file_data = csf_null;
			/**
			 * <font color="#008000">��ʾʹ�ñ�ʶ</font>
			 */
			css_update_operation m_operation_flag;
			/**
			 * <font color="#008000">��ʾ�Ƿ����conf/conf.
			 * xml�ļ���TRUE��ʾ��Ҫ���£����ʱ��IP���ܻᱻ�޸ģ���FLASE��ʾ����Ҫ����</font>
			 */
			csf_bool m_is_update_conf_file = csf_false;
			/**
			 * <font
			 * color="#008000">��ʾ�Ƿ����data�е������ļ���TRUE��ʾ��Ҫ���£����ʱ�����ݿ��ܱ�ɾ������FLASE��ʾ����Ҫ����</font>
			 */
			csf_bool m_is_update_data_file = csf_false;
			/**
			 * <font color="#008000">��ʾ�汾����Ϣ</font>
			 */
			csf_uint32 m_version = 0;
			/**
			 * <font color="#008000">��ʾ�汾������Ϣ</font>
			 */
			csf_uint32 m_version_addtion = 0;
			/**
			 * <font color="#008000">��ʾ����ķ���ʱ����Ϣ</font>
			 */
			csf_uint64 m_time = 0;
			/**
			 * <font color="#008000">��ʾ�豸�ı���ID</font>
			 */
			csf_string m_device_id = "";
			/**
			 * <font color="#008000">��ʾ���������</font>
			 */
			csf_string m_packet_name = "";
			/**
			 * <font color="#008000">��ʾ�豸���ͺ�</font>
			 */
			csf_string m_serial_master = "";
			/**
			 * <font color="#008000">��ʾ�豸���ͺ�</font>
			 */
			csf_string m_serial_slave = "";
			/**
			 * <font color="#008000">��ʾƽ̨Ӳ����Ϣ</font>
			 */
			csf_string m_platform_hardware = "";
			/**
			 * <font color="#008000">��ʾƽ̨�����Ϣ</font>
			 */
			csf_string m_platform_software = "";
			/**
			 * <font color="#008000">��ʾ����ĸ�����Ϣ</font>
			 */
			csf_string m_change_log = "";

		};

	}

}
#endif // !defined(CSS_UPDATE_H_INCLUDED_)
