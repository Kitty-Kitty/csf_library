/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_version_.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 28-6月-2018 22:10:59
*
*Description: Class(csf_version_)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_VERSION_INCLUDED_)
#define CSF_VERSION_INCLUDED_

#include "csf_typedef.h"

#define CSF_VERSION										100
#define	CSF_STRVER										"V0.1.0"
#define	CSF_VAR											"libcsf"
#define	CSF_VER											"libcsf/" CSF_STRVER


namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf系统库版本信息
			 * @author fz
			 * @version 1.0
			 * @created 28-6月-2018 22:10:59
			 */
			class csf_version_
			{

			public:
				csf_version_()
					: m_version(CSF_VERSION)
					, m_strver(CSF_STRVER)
					, m_compile("")
					, m_build("")
					, m_description(CSF_VER) {

					m_build = __DATE__ "T" __TIME__;

#ifdef WIN32

				#if _MSC_VER == 1900
					m_compile = "Visual Studio 2015";
				#elif _MSC_VER == 1800
					m_compile = "Visual Studio 2013";
				#elif _MSC_VER == 1700
					m_compile = "Visual Studio 2012";
				#elif _MSC_VER == 1600
					m_compile = "Visual Studio 2010";
				#elif _MSC_VER == 1500
					m_compile = "Visual Studio 2008";
				#elif _MSC_VER == 1400
					m_compile = "Visual Studio 2005";
				#elif _MSC_VER == 1310
					m_compile = "Visual Studio 2003";
				#else
					m_compile = "unknow compiler[MSC_VER=]";
				#endif	//_MSC_VER == 1900

#else	//__linux__
					m_compile = __VERSION__;
#endif	//WIN32

				}
				virtual ~csf_version_() {

				}
				/**
				*
				* @param version    表示版本号信息
				*/
				csf_version_& operator =(const csf_version_& version) {

				}

				inline csf_string & get_build() {

					return m_build;
				}
				inline csf_string & get_compile() {

					return m_compile;
				}
				/**
				 * 版本数字编码
				 */
				inline csf_uint32 get_version() {

					return m_version;
				}
				/**
				 * 模块的其他描述信息
				 */
				inline csf_string & get_description() {

					return m_description;
				}
				inline csf::core::base::csf_string to_string() {

					return  NULL;
				}
				/**
				 * 版本字符串信息
				 */
				inline csf::core::base::csf_string& get_strver() {

					return m_strver;
				}

			protected:
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_build(csf::core::base::csf_string new_value) {

				}
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_compile(csf_string new_value) {

					m_compile = new_value;
				}
				/**
				 * 版本数字编码
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_version(csf_uint32 new_value) {

					m_version = new_value;
				}
				/**
				 * 模块的其他描述信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_description(csf_string new_value) {

					m_description = new_value;
				}
				/**
				 * 模块的版本字符串信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_strver(csf_char* new_value) {

					m_strver = new_value;
				}
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_build(csf_char* new_value) {

					m_build = new_value;
				}
				/**
				 * 版本字符串信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_strver(csf::core::base::csf_string& new_value) {

				}
				/**
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_compile(csf_char* new_value) {

					m_compile = new_value;
				}
				/**
				 * 模块的其他描述信息
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_description(csf_char* new_value) {

					m_description = new_value;
				}

			private:
				/**
				 * 版本数字编码
				 */
				csf_uint32 m_version = 0;
				/**
				 * 版本字符串信息
				 */
				csf::core::base::csf_string m_strver = "";
				/**
				 * 表示编译器信息
				 */
				csf::core::base::csf_string m_compile = "";
				/**
				 * 编译相关信息，主要是时间信息
				 */
				csf::core::base::csf_string m_build = "";
				/**
				 * 其他描述信息
				 */
				csf::core::base::csf_string m_description = "";

			};

		}

	}

}

static csf::core::base::csf_version_					csf_version;

#endif // !defined(CSF_VERSION_INCLUDED_)
