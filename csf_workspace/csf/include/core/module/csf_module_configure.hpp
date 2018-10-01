/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_configure.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 01-7��-2018 16:21:03
*
*Description: Class(csf_module_configure)��ʾģ��������Ϣ
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_CONFIGURE_INCLUDED_)
#define CSF_MODULE_CONFIGURE_INCLUDED_

#include "csf_typedef.h"
#include "csf_csftype_template.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾģ��������Ϣ
			 * @author f
			 * @version 1.0
			 * @created 01-7��-2018 16:21:03
			 */
			class csf_module_configure : public csf::core::base::csf_csftype_template<csf_module_configure>
			{

			public:
				csf_module_configure()
					: m_name("")
					, m_child("")
					, m_device("")
					, m_file("") {

				}
				virtual ~csf_module_configure() {

				}

				/**
				 * ���ݸ������Դ���ģ�����ö���
				 * 
				 * @param name    ��ʾģ�������
				 * @param file    ��ʾģ���ļ�·��
				 * @param child    ��ʾģ�����ģ��
				 * @param device    ��ʾ�豸
				 */
				inline csf_module_configure(const csf_string& name, const csf_string& file, const csf_string child = "", const csf_string device = "")
					: m_name(name)
					, m_child(child)
					, m_device(device)
					, m_file(file) {

				}
				/**
				 * ���ݸ������Դ���ģ�����ö���
				 * 
				 * @param name    ��ʾģ�������
				 * @param file    ��ʾģ���ļ�·��
				 * @param child    ��ʾģ�����ģ��
				 * @param device    ��ʾ�豸
				 */
				inline csf_module_configure(const csf_char* name, const csf_char* file, const csf_char* child = csf_null, const csf_char* device = csf_null)
					: m_name(name)
					, m_child(child)
					, m_device(device)
					, m_file(file) {

				}
				/**
				 * ��ʾģ�������
				 */
				inline csf_string& get_name() {

					return m_name;
				}
				/**
				 * ��ʾģ�������
				 * 
				 * @param new_value
				 */
				inline csf_void set_name(const csf_string& new_value) {

					m_name = new_value;
				}
				/**
				 * ��ʾ��ģ����Ϣ
				 */
				inline csf_string& get_child() {

					return m_child;
				}
				/**
				 * ��ʾ��ģ����Ϣ
				 * 
				 * @param new_value
				 */
				inline csf_void set_child(const csf_char* new_value) {

					m_child = new_value;
				}
				/**
				 * ��ʾ�豸��Ϣ
				 */
				inline csf_string& get_device() {

					return m_device;
				}
				/**
				 * ��ʾ�豸��Ϣ
				 * 
				 * @param new_value
				 */
				inline csf_void set_device(const csf_char* new_value) {

					m_device = new_value;
				}
				/**
				 * ��ʾģ����ļ���ַ
				 */
				inline csf_string& get_file() {

					return m_file;
				}
				/**
				 * ��ʾģ����ļ���ַ
				 * 
				 * @param new_value
				 */
				inline csf_void set_file(const csf_char* new_value) {

					m_file = new_value;
				}
				/**
				 * ��ʾģ�������
				 * 
				 * @param new_value
				 */
				inline csf_void set_name(const csf_char* new_value) {

					m_name = new_value;
				}
				/**
				 * ��ʾģ����ļ���ַ
				 * 
				 * @param new_value
				 */
				inline csf_void set_file(const csf_string& new_value) {

					m_file = new_value;
				}
				/**
				 * ��ʾ�豸��Ϣ
				 * 
				 * @param new_value
				 */
				inline csf_void set_device(const csf_string& new_value) {

					m_device = new_value;
				}
				/**
				 * ��ʾ��ģ����Ϣ
				 * 
				 * @param new_value
				 */
				inline csf_void set_child(const csf_string& new_value) {

					m_child = new_value;
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline virtual csf_bool is_null() {

					if (get_name().empty() 
						&& get_child().empty()
						&& get_device().empty()
						&& get_file().empty()) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾ��Ϊ�գ�false��ʾΪ�ա�
				*/
				inline virtual csf_bool not_null() {

					return !is_null();
				}
			private:
				/**
				 * ��ʾģ�������
				 */
				csf_string m_name = "";
				/**
				 * ��ʾ��ģ����Ϣ
				 */
				csf_string m_child = "";
				/**
				 * ��ʾ�豸��Ϣ
				 */
				csf_string m_device = "";
				/**
				 * ��ʾģ����ļ���ַ
				 */
				csf_string m_file = "";

			};

		}

	}

}
#endif // !defined(CSF_MODULE_CONFIGURE_INCLUDED_)
