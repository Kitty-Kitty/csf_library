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
					 * 表示虚拟机vm模块类型数值
					 */
					csf_module_type_vm = 0x01000000,
					/**
					* 表示app模块类型数值
					*/
					csf_module_type_app = 0x02000000,
					/**
					* 表示device模块类型数值
					*/
					csf_module_type_device = 0x04000000,
					/**
					* 表示device_io模块类型数值
					*/
					csf_module_type_device_io = 0x08000000,
					/**
					* 表示未知的模块类型
					*/
					csf_module_type_none = 0x00000000
				};

				inline explicit csf_module()
					: m_decorator(csf_nullptr)
					, m_configure_manager(csf_nullptr)
					, m_type(csf_module_type_none)
					, m_guid{ 0, }
					, m_name{ 0, }
					, m_format{ 0, } {

					set_guid();
				}
				/**
				 * 根据配置文件和类型创建一个模块。
				 *
				 * @param configure_manager    表示模块的配置文件
				 * @param type    表示模块的类型
				 */
				inline explicit csf_module(const csf_configure_manager* configure_manager
					, const csf_module_type type)

					: m_decorator(csf_nullptr)
					, m_configure_manager((csf_configure_manager*)configure_manager)
					, m_type(type)
					, m_guid{ 0, }
					, m_name{ 0, }
					, m_format{ 0, }
					, m_attribute_manager(configure_manager) {

					set_guid();
				}
				inline virtual ~csf_module() {

				}
				/**
				 * 模块初始化
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				inline virtual csf::core::base::csf_int32 init(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_succeed;
				}
				/**
				 * 模块启动
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				inline virtual csf::core::base::csf_int32 start(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_succeed;
				}
				/**
				 * 模块停止
				 *
				 * @param conf_mg    表示配置文件信息
				 */
				inline virtual csf::core::base::csf_int32 stop(const csf_configure_manager* conf_mg = csf_nullptr) {

					return  csf_succeed;
				}
				/**
				 * 模块的类型
				 */
				inline csf_module_type get_type() const {

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
				inline csf_string get_guid() const {

					return csf_string(m_guid);
				}
				/**
				 * 表示模块的名称
				 */
				inline csf_string get_name() const {

					return csf_string(m_name);
				}
				/**
				 * 表示模块的名称
				 *
				 * @param new_value    new_value
				 */
				inline csf_void set_name(const csf_string& new_value) {

					set_name(new_value.c_str());
				}
				/**
				 * 表示模块的配置信息管理器
				 */
				inline virtual csf::core::system::csf_configure_manager* get_configure_manager() const {

					return m_configure_manager;
				}
				/**
				 * 表示装饰者指针
				 */
				inline csf_module* get_decorator() const {

					return m_decorator;
				}
				/**
				 * 表示模块的配置信息管理器
				 *
				 * @param new_value    new_value
				 */
				inline virtual csf_void set_configure_manager(const csf::core::system::csf_configure_manager* new_value) {

					m_configure_manager = (csf::core::system::csf_configure_manager*)new_value;
				}
				/**
				 * 表示装饰者指针
				 *
				 * @param new_value    new_value
				 */
				inline csf_void set_decorator(const csf_module* new_value) {

					m_decorator = (csf_module*)new_value;
				}
				/**
				 * 表示模块的版本信息
				 */
				inline csf::core::module::csf_module_version& get_version() {

					return m_version;
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
				 * @param new_value
				 */
				inline csf_void set_error(const csf::core::module::csf_error& new_value) {

					m_error = new_value;
				}
				/**
				 * 表示模块的名称
				 *
				 * @param new_value    new_value
				 */
				inline csf_void set_name(const csf_char* new_value) {

					csf_strncpy(m_name, new_value, csf_sizeof(m_name) - 1);
				}
				/**
				* 模块包含一个属性管理器，统一保存模块所需要的配置属性内容
				*/
				inline csf::core::system::attribute::csf_attribute_manager& get_attribute_manager() {

					return m_attribute_manager;
				}
				/**
				* 主要功能是：将模块信息格式化成字符串输出
				* 返回：模块信息字符串
				*/
				inline virtual csf_string to_string() {

					//if (csf_strlen(m_format) <= 0) {
					if ('\0' == m_format[0]) {

						csf_snprintf(m_format
							, csf_sizeof(m_format)
							, "module[%p name:%s guid:%s type:%d] version[%s]"
							, this
							, m_name
							, m_guid
							, get_type()
							, get_version().to_string().c_str());
					}

					return csf_string(m_format);
				}
				/**
				* 主要功能是：刷新格式化字符串缓存空间
				* 返回：无
				*/
				inline virtual void flush_string() {

					csf_memset(m_format, 0, csf_sizeof(m_format));
				}
			protected:
				/**
				* 主要功能是：设置模块的版本信息
				* 返回：无
				*
				* @param version    模块的版本数值信息
				* @param strver    模块的版本字符串信息
				* @param name    表示模块的名称
				* @param description    模块的其他描述信息
				*/
				inline csf_void set_version(const csf_uint32 version
					, const csf_string strver
					, const csf_string name
					, const csf_string description) {

					get_version().set_version(version, strver, name, description);
				}
				/**
				* 表示模块的版本信息
				*
				* @param new_value
				*/
				inline csf_void set_version(const csf::core::module::csf_module_version& new_value) {

					m_version = new_value;
				}
				/**
				* 表示模块信息的格式化字符串
				*/
				inline csf_char* get_format() {

					return m_format;
				}
				/**
				* 表示模块信息的格式化字符串
				*
				* @param new_value
				*/
				inline void set_format(csf_char* new_value) {

					csf_strcpy(m_format, new_value);
				}
			private:
				/**
				* 表示模块的uuid，用于唯一标识一个模块
				*/
				void set_guid();
			private:
				/**
				* 表示装饰者指针
				*/
				csf_module* m_decorator = csf_nullptr;
				/**
				* 表示模块的配置信息管理器
				*/
				csf::core::system::csf_configure_manager* m_configure_manager = csf_nullptr;
				/**
				 * 模块的类型
				 */
				csf_module_type m_type = csf_module_type_none;
				/**
				* 表示模块的uuid，用于唯一标识一个模块
				*/
				csf_char m_guid[128] = { 0, };
				/**
				* 表示模块的名称
				*/
				csf_char m_name[128] = { 0, };
				/**
				* 表示模块信息的格式化字符串
				*/
				csf_char m_format[256] = { 0, };
				/**
				 * 表示模块的版本信息
				 */
				csf::core::module::csf_module_version m_version;
				/**
				 * 表示模块的错误信息
				 */
				csf::core::module::csf_error m_error;
				/**
				* 模块包含一个属性管理器，统一保存模块所需要的配置属性内容
				*/
				csf::core::system::attribute::csf_attribute_manager m_attribute_manager;

				/**
				* 模块包含一个属性管理器，统一保存模块所需要的配置属性内容
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
/* 表示模块的create 和 destroy 句柄定义。                                              */
/* 每个需要通过模块工厂创建的模块都需要添加该宏定义。                                    */
/* 其中module_type表示该模块的类名称，该类实现了构造方法为：                             */
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
	return csf_succeed;                                                               \
}


#endif // !defined(CSF_MODULE_INCLUDED_)
