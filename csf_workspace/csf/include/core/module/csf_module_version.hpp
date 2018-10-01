/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module_version.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6月-2018 17:49:52
*
*Description: Class(csf_module_version)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MODULE_VERSION_INCLUDED_)
#define CSF_MODULE_VERSION_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * 表示模块版本信息
			 * @author fz
			 * @version 1.0
			 * @created 30-6月-2018 17:49:52
			 */
			class csf_module_version
			{

			public:
				inline csf_module_version()
				    : m_version(0),m_strver(""),m_compile(""),m_build(""),m_description("")
				 {

				}
				inline virtual ~csf_module_version() {

				}
				inline csf_string & get_build() {

					return m_build;
				}
				inline csf_string & get_compile() {

					return m_compile;
				}
				/**
				 * 模块版本数字编码
				 */
				inline csf_uint32 get_version() {

					return m_version;
				}
				/**
				 * 模块版本数字编码
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_version(const csf_uint32 new_value) {

					m_version = new_value;
				}
				/**
				 * 模块的其他描述信息
				 */
				inline csf_string & get_description() {

					return m_description;
				}
				inline csf::core::base::csf_string to_string() {

					return  "";
				}
				/**
				 * 模块的版本字符串信息
				 */
				inline csf_string& get_strver() {

					return m_strver;
				}
				/**
				 * 模块的其他描述信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_description(const csf_string& new_value) {

					m_description = new_value;
				}
				/**
				 * 模块的版本字符串信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_strver(const csf_char* new_value) {

					m_strver = new_value;
				}
				/**
				 * 模块的版本字符串信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_strver(const csf_string& new_value) {

					m_strver = new_value;
				}
				/**
				 * 模块的其他描述信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_description(const csf_char* new_value) {

					m_description = new_value;
				}

			protected:
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_build(const csf_string& new_value) {

					m_build = new_value;
				}
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_compile(const csf_string& new_value) {

					m_compile = new_value;
				}
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_build(const csf_char* new_value) {

					m_build = new_value;
				}
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_compile(const csf_char* new_value) {

					m_compile = new_value;
				}

			private:
				/**
				 * 模块版本数字编码
				 */
				csf_uint32 m_version = 0;
				/**
				 * 模块的版本字符串信息
				 */
				csf::core::base::csf_string m_strver = "";
				/**
				 * 表示模块编译器信息
				 */
				csf::core::base::csf_string m_compile = "";
				/**
				 * 模块编译相关信息，主要是时间信息
				 */
				csf::core::base::csf_string m_build = "";
				/**
				 * 模块的其他描述信息
				 */
				csf::core::base::csf_string m_description = "";

			};

		}

	}

}
#endif // !defined(CSF_MODULE_VERSION_INCLUDED_)
