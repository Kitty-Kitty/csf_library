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
				 * ģ��汾���ֱ���
				 */
				inline csf_uint32 get_version() {

					return m_version;
				}
				/**
				 * ģ��汾���ֱ���
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_version(const csf_uint32 newVal) {

					m_version = newVal;
				}
				/**
				 * ģ�������������Ϣ
				 */
				inline csf_string & get_description() {

					return m_description;
				}
				inline csf::core::base::csf_string to_string() {

					return  "";
				}
				/**
				 * ģ��İ汾�ַ�����Ϣ
				 */
				inline csf_string& get_strver() {

					return m_strver;
				}
				/**
				 * ģ�������������Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_description(const csf_string& newVal) {

					m_description = newVal;
				}
				/**
				 * ģ��İ汾�ַ�����Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_strver(const csf_char* newVal) {

					m_strver = newVal;
				}
				/**
				 * ģ��İ汾�ַ�����Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_strver(const csf_string& newVal) {

					m_strver = newVal;
				}
				/**
				 * ģ�������������Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_description(const csf_char* newVal) {

					m_description = newVal;
				}

			protected:
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_build(const csf_string& newVal) {

					m_build = newVal;
				}
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_compile(const csf_string& newVal) {

					m_compile = newVal;
				}
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_build(const csf_char* newVal) {

					m_build = newVal;
				}
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_compile(const csf_char* newVal) {

					m_compile = newVal;
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

			};

		}

	}

}
#endif // !defined(CSF_MODULE_VERSION_INCLUDED_)
