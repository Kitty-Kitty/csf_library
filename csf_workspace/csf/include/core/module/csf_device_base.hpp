/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_device_base.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6��-2018 17:28:39
*
*Description: Class(csf_device_base)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_DEVICE_BASE_INCLUDED_)
#define CSF_DEVICE_BASE_INCLUDED_

#include "csf_device_operation_interface.hpp"
#include "csf_module.hpp"
#include "csf_attribute_manager.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			//��ʾdevice id�ַ��������Ĭ�ϳ���
			#define csf_device_id_length							256

			//��ʾ�豸����ص�����
			typedef csf_function<csf_int32 (csf_element&)>			csf_device_operation_callback;

			//��ʾӦ�ó���ĵĳ���ģ��app����һ��app��ʾһ��Ӧ�ó���
			class csf_app;

			//��ʾ�豸����
			class csf_device;

			//��ʾ�豸io�ĳ���
			class csf_device_io;

			/**
			 * ��ʾ�����豸����
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6��-2018 17:28:39
			 */
			class csf_device_base : public csf::core::module::csf_module, public csf::core::module::csf_device_operation_interface
			{

			public:
				inline explicit csf_device_base()
					: m_mid{ 0, }
					, m_parent(csf_nullptr) {

				}

				inline virtual ~csf_device_base() {

				}
				/**
				* ��ʾ���������ļ������ʹ����豸ģ��
				*
				* @param configure_manager    ��ʾ�����ļ�����
				* @param type    ��ʾģ�������
				*/
				inline explicit csf_device_base(const csf_configure_manager * configure_manager
					, const csf_module::csf_module_type type) 
				
					: csf_module(configure_manager, type)
					, m_mid{ 0, }
					, m_parent(csf_nullptr) {

				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 del(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 ctrl(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 update(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* ��ʾ�豸����Ӳ���
				*
				* @param element    ��ʾ�豸��Ӳ���
				* @param callback    ��ʾ�豸�����Ļص�����
				*/
				inline virtual csf_int32 add(const csf_element& element, const csf_device_operation_callback callback) {

					return csf_success;
				}
				/**
				* ģ���ʼ��
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_success;
				}
				/**
				* ģ������
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_success;
				}
				/**
				* ��ʾ�豸��Ψһ����id
				*/
				inline csf_string get_mid() {

					return m_mid;
				}
				/**
				* ģ��ֹͣ
				*
				* @param conf_mg    ��ʾ�����ļ���Ϣ
				*/
				inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

					return csf_success;
				}
				/**
				* ��ʾ�豸��Ψһ����id������id��󳤶�256�ֽڡ�
				* ���أ�true��ʾ���óɹ���false��ʾ����ʧ�ܡ�
				*
				* @param new_value
				*/
				inline csf_bool set_mid(const csf_string& new_value) {

					if (new_value.empty() || new_value.length() >= csf_device_id_length) {
						return csf_false;
					}

					return set_mid(new_value.c_str());
				}
				/**
				* ��ʾ�豸��Ψһ����id������id��󳤶�256�ֽڡ�
				* ���أ�true��ʾ���óɹ���false��ʾ����ʧ�ܡ�
				*
				* @param new_value
				*/
				inline csf_bool set_mid(const csf_char* new_value) {

					if (!new_value || csf_strlen(new_value) >= csf_device_id_length) {
						return csf_false;
					}

					csf_memset(m_mid, 0, csf_sizeof(m_mid));
					csf_strcpy(m_mid, new_value);
					
					return csf_true;
				}
				/**
				* ���ܣ�����ģ����������ݣ��ж��Ƿ�Ϊcsf_device_base�豸��У��ķ������ж��Ƿ�Ϊapp��device��device_io���豸
				* ���أ�true��ʾ��device�豸��false��ʾ����device�豸��
				*
				* @param type    ��ʾģ���������ֵ
				*/
				inline static csf_bool is_device(const csf::core::module::csf_module::csf_module_type type) {

					if ((type && csf_module::csf_module_type::csf_module_type_app)
							|| (type && csf_module::csf_module_type::csf_module_type_device)
							|| (type && csf_module::csf_module_type::csf_module_type_device_io)) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				* ��ʾ�豸�����ĸ��豸�Ľڵ�����
				*
				* @param new_value    ��ʾ���豸�ڵ�
				*/
				inline virtual csf_void set_parent(const csf_device_base* new_value) {

					m_parent = (csf_device_base*)new_value;
				}
				/**
				* ��ʾ�豸�����ĸ��豸�Ľڵ�����
				*/
				inline virtual csf_device_base* get_parent() {

					return m_parent;
				}

			private:
				/**
				* ��ʾ�豸��Ψһ����id
				*/
				csf_char m_mid[csf_device_id_length] = { 0, };
				/**
				* ��ʾ�豸�����ĸ��豸�Ľڵ�����
				*/
				csf_device_base* m_parent = csf_nullptr;

			};

		}

	}

}
#endif // !defined(CSF_DEVICE_BASE_INCLUDED_)
