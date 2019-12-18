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
*Date: 28-6��-2018 22:10:59
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
			 * ��ʾcsfϵͳ��汾��Ϣ
			 * @author fz
			 * @version 1.0
			 * @created 28-6��-2018 22:10:59
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


				#if 0
					switch (_MSC_VER)
					{
					case 1800:
						m_compile = "Visual Studio 2013";
						break;
					case 1700:
						m_compile = "Visual Studio 2012";
						break;
					case 1600:
						m_compile = "Visual Studio 2010";
						break;
					case 1500:
						m_compile = "Visual Studio 2008";
						break;
					case 1400:
						m_compile = "Visual Studio 2005";
						break;
					case 1310:
						m_compile = "Visual Studio 2003";
						break;
					default:
						m_compile = "unknow compiler[MSC_VER=]";
						break;
					}
				#endif


#else	//__linux__
					m_compile = __VERSION__;
#endif	//WIN32

				}
				/**
				*
				* @param version    ��ʾ�汾����Ϣ
				*/
				csf_version_(const csf_version_& version) {

				}
				virtual ~csf_version_() {

				}
				/**
				*
				* @param version    ��ʾ�汾����Ϣ
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
				 * �汾���ֱ���
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

					return  NULL;
				}
				/**
				 * �汾�ַ�����Ϣ
				 */
				inline csf::core::base::csf_string& get_strver() {

					return m_strver;
				}

			protected:
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_build(csf::core::base::csf_string newVal) {

				}
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_compile(csf_string newVal) {

					m_compile = newVal;
				}
				/**
				 * �汾���ֱ���
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_version(csf_uint32 newVal) {

					m_version = newVal;
				}
				/**
				 * ģ�������������Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_description(csf_string newVal) {

					m_description = newVal;
				}
				/**
				 * ģ��İ汾�ַ�����Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_strver(csf_char* newVal) {

					m_strver = newVal;
				}
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_build(csf_char* newVal) {

					m_build = newVal;
				}
				/**
				 * �汾�ַ�����Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_strver(csf::core::base::csf_string& newVal) {

				}
				/**
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_compile(csf_char* newVal) {

					m_compile = newVal;
				}
				/**
				 * ģ�������������Ϣ
				 * 
				 * @param newVal    newVal
				 */
				inline csf_void set_description(csf_char* newVal) {

					m_description = newVal;
				}

			private:
				/**
				 * �汾���ֱ���
				 */
				csf_uint32 m_version = 0;
				/**
				 * �汾�ַ�����Ϣ
				 */
				csf::core::base::csf_string m_strver = "";
				/**
				 * ��ʾ��������Ϣ
				 */
				csf::core::base::csf_string m_compile = "";
				/**
				 * ���������Ϣ����Ҫ��ʱ����Ϣ
				 */
				csf::core::base::csf_string m_build = "";
				/**
				 * ����������Ϣ
				 */
				csf::core::base::csf_string m_description = "";

			};

		}

	}

}

static csf::core::base::csf_version_					csf_version;

#endif // !defined(CSF_VERSION_INCLUDED_)