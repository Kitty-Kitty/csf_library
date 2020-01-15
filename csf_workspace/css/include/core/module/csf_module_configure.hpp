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
*Date: 01-7月-2018 16:21:03
*
*Description: Class(csf_module_configure)表示模块配置信息
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
			 * 表示模块配置信息
			 * @author f
			 * @version 1.0
			 * @created 01-7月-2018 16:21:03
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
				 * 根据各种属性创建模块配置对象
				 * 
				 * @param name    表示模块的名称
				 * @param file    表示模块文件路径
				 * @param child    表示模块的子模块
				 * @param device    表示设备
				 */
				inline csf_module_configure(const csf_string& name, const csf_string& file, const csf_string child = "", const csf_string device = "")
					: m_name(name)
					, m_child(child)
					, m_device(device)
					, m_file(file) {

				}
				/**
				 * 根据各种属性创建模块配置对象
				 * 
				 * @param name    表示模块的名称
				 * @param file    表示模块文件路径
				 * @param child    表示模块的子模块
				 * @param device    表示设备
				 */
				inline csf_module_configure(const csf_char* name, const csf_char* file, const csf_char* child = csf_null, const csf_char* device = csf_null)
					: m_name(name)
					, m_child(child)
					, m_device(device)
					, m_file(file) {

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
				 * @param newVal
				 */
				inline csf_void set_name(const csf_string& newVal) {

					m_name = newVal;
				}
				/**
				 * 表示子模块信息
				 */
				inline csf_string& get_child() {

					return m_child;
				}
				/**
				 * 表示子模块信息
				 * 
				 * @param newVal
				 */
				inline csf_void set_child(const csf_char* newVal) {

					m_child = newVal;
				}
				/**
				 * 表示设备信息
				 */
				inline csf_string& get_device() {

					return m_device;
				}
				/**
				 * 表示设备信息
				 * 
				 * @param newVal
				 */
				inline csf_void set_device(const csf_char* newVal) {

					m_device = newVal;
				}
				/**
				 * 表示模块的文件地址
				 */
				inline csf_string& get_file() {

					return m_file;
				}
				/**
				 * 表示模块的文件地址
				 * 
				 * @param newVal
				 */
				inline csf_void set_file(const csf_char* newVal) {

					m_file = newVal;
				}
				/**
				 * 表示模块的名称
				 * 
				 * @param newVal
				 */
				inline csf_void set_name(const csf_char* newVal) {

					m_name = newVal;
				}
				/**
				 * 表示模块的文件地址
				 * 
				 * @param newVal
				 */
				inline csf_void set_file(const csf_string& newVal) {

					m_file = newVal;
				}
				/**
				 * 表示设备信息
				 * 
				 * @param newVal
				 */
				inline csf_void set_device(const csf_string& newVal) {

					m_device = newVal;
				}
				/**
				 * 表示子模块信息
				 * 
				 * @param newVal
				 */
				inline csf_void set_child(const csf_string& newVal) {

					m_child = newVal;
				}
				/**
				* 表示判断是否为空。
				* 返回：true表示为空；false表示不为空。
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
				* 表示判断是否不为空。
				* 返回：true表示不为空；false表示为空。
				*/
				inline virtual csf_bool not_null() {

					return !is_null();
				}
			private:
				/**
				 * 表示模块的名称
				 */
				csf_string m_name = "";
				/**
				 * 表示子模块信息
				 */
				csf_string m_child = "";
				/**
				 * 表示设备信息
				 */
				csf_string m_device = "";
				/**
				 * 表示模块的文件地址
				 */
				csf_string m_file = "";

			};

		}

	}

}
#endif // !defined(CSF_MODULE_CONFIGURE_INCLUDED_)
