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
*Date: 01-7月-2018 18:27:20
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
			 * 表示cf模块的基础类信息
			 * @author fz
			 * @version 1.0
			 * @created 01-7月-2018 18:27:20
			 */
			class csf_module : public csf::core::module::csf_module_interface
			{
			public:
				/**
				* 表示模块类型列表信息
				* @author fz
				* @version 1.0
				* @updated 12-7月-2018 16:20:57
				*/
				enum csf_module_type
				{
					/**
					* 表示app模块类型数值
					*/
					csf_module_type_app = 0x01000000,
					/**
					* 表示device模块类型数值
					*/
					csf_module_type_device = 0x02000000,
					/**
					* 表示device_io模块类型数值
					*/
					csf_module_type_device_io = 0x04000000,
					/**
					* 表示未知的模块类型
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
				 * 根据配置文件和类型创建一个模块。
				 * 
				 * @param configure_manager    表示模块的配置文件
				 * @param type    表示模块的类型
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
				 * 模块初始化
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_success;
				}
				/**
				 * 模块启动
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_success;
				}
				/**
				 * 模块停止
				 * 
				 * @param conf_mg    表示配置文件信息
				 */
				inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_success;
				}
				/**
				 * 模块的类型
				 */
				inline csf_module_type get_type() {

					return m_type;
				}
				/**
				 * 模块的类型
				 * 
				 * @param new_value    new_value
				 */
				inline csf::core::base::csf_void set_type(const csf_module_type new_value) {

				}
				/**
				 * 表示模块的uuid，用于唯一标识一个模块
				 */
				inline csf_string& get_guid() {

					return m_guid;
				}
				/**
				 * 表示模块的名称
				 */
				inline csf_string& get_name() {

					return m_name;
				}
				/**
				 * 表示模块的名称
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_name(const csf_string& newVal) {

					m_name = newVal;
				}
				/**
				 * 表示模块的配置信息管理器
				 */
				inline virtual csf::core::system::csf_configure_manager* get_configure_manager() {

					return m_configure_manager;
				}
				/**
				 * 表示装饰者指针
				 */
				inline csf_module* get_decorator() {

					return m_decorator;
				}
				/**
				 * 表示模块的配置信息管理器
				 * 
				 * @param newVal    newVal
				 */
				inline virtual csf_void set_configure_manager(const csf::core::system::csf_configure_manager* newVal) {

					m_configure_manager = (csf::core::system::csf_configure_manager*)newVal;
				}
				/**
				 * 表示装饰者指针
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_decorator(const csf_module* newVal) {

					m_decorator = (csf_module*)newVal;
				}
				/**
				 * 表示模块的版本信息
				 */
				inline csf::core::module::csf_module_version& get_version() {

					return m_version;
				}
				/**
				 * 表示模块的版本信息
				 * 
				 * @param newVal
				 */
				inline csf_void set_version(const csf::core::module::csf_module_version& newVal) {

					m_version = newVal;
				}
				/**
				 * 表示模块的错误信息
				 */
				inline csf::core::module::csf_error& get_error() {

					return m_error;
				}
				/**
				 * 表示模块的错误信息
				 * 
				 * @param newVal
				 */
				inline csf_void set_error(const csf::core::module::csf_error& newVal) {

					m_error = newVal;
				}
				/**
				 * 表示模块的名称
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_name(const csf_char* newVal) {

					m_name = newVal;
				}
				/**
				* 模块包含一个属性管理器，统一保存模块所需要的配置属性内容
				*/
				inline csf::core::system::attribute::csf_attribute_manager& get_attribute_manager() {

					return m_attribute_manager;
				}

			private:
				/**
				 * 模块的类型
				 */
				csf_module_type m_type = csf_module_type_none;
				/**
				 * 表示模块的uuid，用于唯一标识一个模块
				 */
				csf_string m_guid = "";
				/**
				 * 表示模块的名称
				 */
				csf_string m_name = "";
				/**
				 * 表示装饰者指针
				 */
				csf_module* m_decorator = csf_nullptr;
				/**
				 * 表示模块的版本信息
				 */
				csf::core::module::csf_module_version m_version;
				/**
				 * 表示模块的错误信息
				 */
				csf::core::module::csf_error m_error;
				/**
				 * 表示模块的配置信息管理器
				 */
				csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				* 模块包含一个属性管理器，统一保存模块所需要的配置属性内容
				*/
				csf::core::system::attribute::csf_attribute_manager m_attribute_manager;

				/**
				* 模块包含一个属性管理器，统一保存模块所需要的配置属性内容
				*
				* @param newVal
				*/
				inline void set_attribute_manager(csf::core::system::attribute::csf_attribute_manager& newVal) {

					m_attribute_manager = newVal;
				}
			};

		}

	}

}
#endif // !defined(CSF_MODULE_INCLUDED_)
