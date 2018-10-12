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
*Date: 30-6��-2018 17:49:52
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
#include "csf_stddef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ��ʾģ��汾��Ϣ
			 * @author fz
			 * @version 1.0
			 * @created 30-6��-2018 17:49:52
			 */
			class csf_module_version
			{

			public:
				inline csf_module_version()
					: m_version(0)
					, m_strver("")
#ifdef WIN32
#if _MSC_VER < 1200
					, m_compile( "vs lower")
#elif _MSC_VER == 1200
					, m_compile("vs98")
#elif _MSC_VER == 1300
					, m_compile("vs.net")
#elif _MSC_VER == 1310
					, m_compile("vs2003")
#elif _MSC_VER == 1400
					, m_compile("vs2005")
#elif _MSC_VER == 1500
					, m_compile("vs2008")
#elif _MSC_VER == 1600
					, m_compile("vs2010")
#elif _MSC_VER == 1700
					, m_compile("vs2012")
#elif _MSC_VER == 1800
					, m_compile("vs2013")
#elif _MSC_VER == 1900
					, m_compile("vs2015")
#else
					, m_compile("vs high")
#endif
#elif defined(__GNUC__)
					, m_compile("gcc " #__GNUC__ "." #__GNUC_MINOR__ "." #__GNUC_PATCHLEVEL__)
#else
					, m_compile("unknow compile")
#endif
					, m_build(__DATE__ "T" __TIME__)
					, m_description("") {

				}
				/**
				* @param version    ģ��İ汾��ֵ��Ϣ
				* @param strver    ģ��İ汾�ַ�����Ϣ
				* @param compile    ��ʾģ���������Ϣ
				* @param build    ģ����������Ϣ����Ҫ��ʱ����Ϣ
				* @param description    ģ�������������Ϣ
				*/
				inline csf_module_version(const csf_int32 version
					, const csf_string strver
					, const csf_string compile
					, const csf_string build
					, const csf_string description = "")
					
					: m_version(version)
					, m_strver(strver)
					, m_compile(compile)
					, m_build(build)
					, m_description(description) {

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
				 * ģ��汾���ֱ���
				 */
				inline csf_uint32 get_version() {

					return m_version;
				}
				/**
				 * ģ�������������Ϣ
				 */
				inline csf_string & get_description() {

					return m_description;
				}
				inline csf::core::base::csf_string to_string() {

					if (csf_strlen(m_format) <= 0) {

						//��ʽΪ��csf_lib/v1.0-1000-gcc 4.8.0-20180102-base library��
						csf_snprintf(m_format, csf_sizeof(m_format)
							, "%s-%d-%s-%s-%s"
							, get_strver().c_str()
							, get_version()
							, get_compile().c_str()
							, get_build().c_str()
							, get_description().c_str());
					}

					return csf_string(m_format);
				}
				/**
				 * ģ��İ汾�ַ�����Ϣ
				 */
				inline csf_string& get_strver() {

					return m_strver;
				}
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

					set_version(version);
					set_strver(strver);
					set_description(description);
				}
				/**
				* ��Ҫ�����ǣ�����ģ��İ汾��Ϣ
				* ���أ��޷���
				*
				* @param version    ģ��İ汾��ֵ��Ϣ
				* @param strver    ģ��İ汾�ַ�����Ϣ
				* @param compile    ��ʾģ���������Ϣ
				* @param build    ģ����������Ϣ����Ҫ��ʱ����Ϣ
				* @param description    ģ�������������Ϣ
				*/
				inline csf_void set_version(const csf_int32 version
					, const csf_string strver
					, const csf_string compile
					, const csf_string build
					, const csf_string description = "") {

					set_version(version);
					set_strver(strver);
					set_compile(compile);
					set_build(build);
					set_description(description);

				}
			protected:
				/**
				* ģ��汾���ֱ���
				*
				* @param new_value    new_value
				*/
				inline csf_void set_version(const csf_uint32 new_value) {

					m_version = new_value;
				}
				/**
				* ģ�������������Ϣ
				*
				* @param new_value    new_value
				*/
				inline csf_void set_description(const csf_string& new_value) {

					m_description = new_value;
				}
				/**
				* ģ��İ汾�ַ�����Ϣ
				*
				* @param new_value    new_value
				*/
				inline csf_void set_strver(const csf_char* new_value) {

					m_strver = new_value;
				}
				/**
				* ģ��İ汾�ַ�����Ϣ
				*
				* @param new_value    new_value
				*/
				inline csf_void set_strver(const csf_string& new_value) {

					m_strver = new_value;
				}
				/**
				* ģ�������������Ϣ
				*
				* @param new_value    new_value
				*/
				inline csf_void set_description(const csf_char* new_value) {

					m_description = new_value;
				}
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
				/**
				* ��ʾ�汾��Ϣ�ĸ�ʽ���ַ���
				*/
				inline csf_char* get_format() {

					return m_format;
				}
				/**
				* ��ʾ�汾��Ϣ�ĸ�ʽ���ַ���
				*
				* @param newVal
				*/
				inline csf_void set_format(csf_char* newVal) {
					
// 					csf_strncpy(m_format, newVal
// 						, csf_strlen(newVal) < csf_sizeof(m_format) ? csf_strlen(newVal) : csf_sizeof(m_format));
				}
			private:
				/**
				 * ģ��汾���ֱ���
				 */
				csf_uint32 m_version = 0;
				/**
				 * ģ��İ汾�ַ�����Ϣ
				 */
				csf::core::base::csf_string m_strver = "";
				/**
				 * ��ʾģ���������Ϣ
				 */
				csf::core::base::csf_string m_compile = "";
				/**
				 * ģ����������Ϣ����Ҫ��ʱ����Ϣ
				 */
				csf::core::base::csf_string m_build = "";
				/**
				 * ģ�������������Ϣ
				 */
				csf::core::base::csf_string m_description = "";
				/**
				* ��ʾ�汾��Ϣ�ĸ�ʽ���ַ���
				*/
				csf_char m_format[128] = { 0, };
			};

		}

	}

}
#endif // !defined(CSF_MODULE_VERSION_INCLUDED_)
