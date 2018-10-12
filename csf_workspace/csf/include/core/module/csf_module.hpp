/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7��-2018 18:27:20
*
*Description: Class(csf_module)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_INCLUDED_)
#define CSF_MODULE_INCLUDED_

#include "csf_module_interface.hpp"
#include "csf_module_version.hpp"
#include "csf_error.hpp"
#include "csf_attribute_include.h"


using namespace csf::core::system::attribute;


namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾcfģ��Ļ�������Ϣ
			 * @author fz
			 * @version 1.0
			 * @created 01-7��-2018 18:27:20
			 */
			class csf_module : public csf::core::module::csf_module_interface
			{
			public:
				/**
				* ��ʾģ�������б���Ϣ
				* @author fz
				* @version 1.0
				* @updated 12-7��-2018 16:20:57
				*/
				enum csf_module_type
				{
					/**
					* ��ʾappģ��������ֵ
					*/
					csf_module_type_app = 0x01000000,
					/**
					* ��ʾdeviceģ��������ֵ
					*/
					csf_module_type_device = 0x02000000,
					/**
					* ��ʾdevice_ioģ��������ֵ
					*/
					csf_module_type_device_io = 0x04000000,
					/**
					* ��ʾδ֪��ģ������
					*/
					csf_module_type_none = 0x00000000
				};

				inline explicit csf_module()
					: m_type(csf_module_type_none)
					, m_guid("")
					, m_name("")
					, m_decorator(csf_nullptr)
					, m_configure_manager(csf_nullptr) {

				}
				/**
				 * ���������ļ������ʹ���һ��ģ�顣
				 *
				 * @param configure_manager    ��ʾģ��������ļ�
				 * @param type    ��ʾģ�������
				 */
				inline explicit csf_module(const csf_configure_manager* configure_manager
					, const csf_module_type type)

					: m_type(type)
					, m_guid("")
					, m_name("")
					, m_decorator(csf_nullptr)
					, m_configure_manager((csf_configure_manager*)configure_manager)
					, m_attribute_manager(configure_manager) {

				}
				inline virtual ~csf_module() {

				}
				/**
				 * ģ���ʼ��
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_success;
				}
				/**
				 * ģ������
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_success;
				}
				/**
				 * ģ��ֹͣ
				 *
				 * @param conf_mg    ��ʾ�����ļ���Ϣ
				 */
				inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_success;
				}
				/**
				 * ģ�������
				 */
				inline csf_module_type get_type() {

					return m_type;
				}
				/**
				 * ģ�������
				 *
				 * @param new_value    new_value
				 */
				inline csf::core::base::csf_void set_type(const csf_module_type new_value) {

				}
				/**
				 * ��ʾģ���uuid������Ψһ��ʶһ��ģ��
				 */
				inline csf_string& get_guid() {

					return m_guid;
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
				 * @param new_value    new_value
				 */
				inline csf_void set_name(const csf_string& new_value) {

					m_name = new_value;
				}
				/**
				 * ��ʾģ���������Ϣ������
				 */
				inline virtual csf::core::system::csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * ��ʾװ����ָ��
				 */
				inline csf_module* get_decorator() {

					return m_decorator;
				}
				/**
				 * ��ʾģ���������Ϣ������
				 *
				 * @param new_value    new_value
				 */
				inline virtual csf_void set_configure_manager(const csf::core::system::csf_configure_manager* new_value) {

					m_configure_manager = (csf::core::system::csf_configure_manager*)new_value;
				}
				/**
				 * ��ʾװ����ָ��
				 *
				 * @param new_value    new_value
				 */
				inline csf_void set_decorator(const csf_module* new_value) {

					m_decorator = (csf_module*)new_value;
				}
				/**
				 * ��ʾģ��İ汾��Ϣ
				 */
				inline csf::core::module::csf_module_version& get_version() {

					return m_version;
				}
				/**
				 * ��ʾģ��Ĵ�����Ϣ
				 */
				inline csf::core::module::csf_error& get_error() {

					return m_error;
				}
				/**
				 * ��ʾģ��Ĵ�����Ϣ
				 *
				 * @param new_value
				 */
				inline csf_void set_error(const csf::core::module::csf_error& new_value) {

					m_error = new_value;
				}
				/**
				 * ��ʾģ�������
				 *
				 * @param new_value    new_value
				 */
				inline csf_void set_name(const csf_char* new_value) {

					m_name = new_value;
				}
				/**
				* ģ�����һ�����Թ�������ͳһ����ģ������Ҫ��������������
				*/
				inline csf::core::system::attribute::csf_attribute_manager& get_attribute_manager() {

					return m_attribute_manager;
				}
			protected:
				/**
				* ��Ҫ�����ǣ�����ģ��İ汾��Ϣ
				* ���أ���
				*
				* @param version    ģ��İ汾��ֵ��Ϣ
				* @param strver    ģ��İ汾�ַ�����Ϣ
				* @param description    ģ�������������Ϣ
				*/
				inline csf_void set_version(const csf_uint32 version
					, const csf_string strver
					, const csf_string description) {
					
					get_version().set_version(version, strver, description);
				}
				/**
				* ��ʾģ��İ汾��Ϣ
				*
				* @param new_value
				*/
				inline csf_void set_version(const csf::core::module::csf_module_version& new_value) {

					m_version = new_value;
				}
			private:
				/**
				 * ģ�������
				 */
				csf_module_type m_type = csf_module_type_none;
				/**
				 * ��ʾģ���uuid������Ψһ��ʶһ��ģ��
				 */
				csf_string m_guid = "";
				/**
				 * ��ʾģ�������
				 */
				csf_string m_name = "";
				/**
				 * ��ʾװ����ָ��
				 */
				csf_module* m_decorator = csf_nullptr;
				/**
				 * ��ʾģ��İ汾��Ϣ
				 */
				csf::core::module::csf_module_version m_version;
				/**
				 * ��ʾģ��Ĵ�����Ϣ
				 */
				csf::core::module::csf_error m_error;
				/**
				 * ��ʾģ���������Ϣ������
				 */
				csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				* ģ�����һ�����Թ�������ͳһ����ģ������Ҫ��������������
				*/
				csf::core::system::attribute::csf_attribute_manager m_attribute_manager;

				/**
				* ģ�����һ�����Թ�������ͳһ����ģ������Ҫ��������������
				*
				* @param new_value
				*/
				inline void set_attribute_manager(csf::core::system::attribute::csf_attribute_manager& new_value) {

					m_attribute_manager = new_value;
				}
			};

		}

	}

}


/*************************************************************************************/
/* csf module symboy handle define                                                   */
/* ��ʾģ���create �� destroy ������塣                                              */
/* ÿ����Ҫͨ��ģ�鹤��������ģ�鶼��Ҫ��Ӹú궨�塣                                    */
/* ����module_type��ʾ��ģ��������ƣ�����ʵ���˹��췽��Ϊ��                             */
/* public:                                                                            */
/*     module_type(const csf::core::system::csf_configure_manager* configure_manager) */
/**************************************************************************************/
#define CSF_MODULE_SYMBOY_DEFINE(module_type)                                         \
extern "C" csf_symbol_export csf::core::module::csf_module* create(                   \
	const csf::core::system::csf_configure_manager* configure_manager) {              \
	return new module_type(configure_manager);                                        \
}                                                                                     \
extern "C" csf_symbol_export csf::core::base::csf_int32 destroy(                      \
	const csf::core::module::csf_module *module) {                                    \
	if (!module) {                                                                    \
		return csf_failure;                                                           \
	}                                                                                 \
	delete module;                                                                    \
	return csf_success;                                                               \
}


#endif // !defined(CSF_MODULE_INCLUDED_)
