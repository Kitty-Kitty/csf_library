/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_configure_file.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6��-2018 11:58:29
*
*Description: Class(csf_configure_file) ��ʾ�����ļ���һ���ļ�һ��configure_file����
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONFIGURE_FILE_INCLUDED_)
#define CSF_CONFIGURE_FILE_INCLUDED_

#include "csf_typedef.h"
#include "csf_csftype_template.hpp"
#include "csf_configure_interface.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace system
		{
			/**
			 * ��ʾ�����ļ���һ���ļ�һ��configure_file����
			 * @author fz
			 * @version 1.0
			 * @created 30-6��-2018 11:58:29
			 */
			class csf_configure_file : public csf::core::system::csf_configure_interface, public csf::core::base::csf_csftype_template<csf_configure_file>
			{

			public:
				inline explicit csf_configure_file()
					: m_file_path("")
					, m_format("")
					, m_name("") {

				}
				virtual ~csf_configure_file() {

				}

				/**
				 * �����������ԵĹ��캯��
				 * 
				 * @param name    ��ʾ�������������
				 * @param file_path    ��ʾ�����ļ����ļ�·��
				 * @param format    ��ʾ�����ļ����ļ���ʽ������ָ���ļ��Ľ���
				 */
				inline explicit csf_configure_file(const csf_char* name, const csf_char* file_path, const csf_char* format)
					: m_name(name)
					, m_file_path(file_path)
					, m_format(format) {

				}
				/**
				 * �����������ԵĹ��캯��
				 * 
				 * @param name    ��ʾ�������������
				 * @param file_path    ��ʾ�����ļ����ļ�·��
				 * @param format    ��ʾ�����ļ����ļ���ʽ������ָ���ļ��Ľ���
				 */
				inline explicit csf_configure_file(const csf_string& name, const csf_string& file_path, const csf_string& format)
					: csf_configure_file(name.c_str(), file_path.c_str(), format.c_str()){

				}
				/**
				 * ��ʾ�����ļ���Ŀ¼��ַ
				 */
				inline csf_string& get_file_path() {

					return m_file_path;
				}
				/**
				 * ��ʾ�����ļ���Ŀ¼��ַ
				 * 
				 * @param newVal
				 */
				inline csf_void set_file_path(csf_string& newVal) {

					m_file_path = newVal;
				}
				/**
				 * ��ʾ�����ļ��ĸ�ʽ
				 */
				inline csf_string& get_format() {

					return m_format;
				}
				/**
				 * ��ʾ�����ļ��ĸ�ʽ
				 * 
				 * @param newVal
				 */
				inline csf_void set_format(csf_string& newVal) {

					m_format = newVal;
				}
				/**
				 * ��ʾ�����ļ������������ڷḻ�����ļ��Ĵ���
				 */
				inline csf_string& get_name() {

					return m_name;
				}
				/**
				 * ��ʾ�����ļ������������ڷḻ�����ļ��Ĵ���
				 * 
				 * @param newVal
				 */
				inline csf_void set_name(csf_string& newVal) {

					m_name = newVal;
				}
				/**
				 * ��ʾ�����ļ������������ڷḻ�����ļ��Ĵ���
				 * 
				 * @param newVal
				 */
				inline csf_void set_name(csf_char* newVal) {

					m_name = newVal;
				}
				/**
				 * ��ʾ�����ļ��ĸ�ʽ
				 * 
				 * @param newVal
				 */
				inline csf_void set_format(csf_char* newVal) {

					m_format = newVal;
				}
				/**
				 * ��ʾ�����ļ���Ŀ¼��ַ
				 * 
				 * @param newVal
				 */
				inline csf_void set_file_path(csf_char* newVal) {

					m_file_path = newVal;
				}
				/**
				* ��ʾ�ж��Ƿ�Ϊ�ա�
				* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
				*/
				inline virtual csf_bool is_null() {

					if (get_name().empty() 
						&& get_file_path().empty()
						&& get_format().empty()) {
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
				 * ��ʾ�����ļ���Ŀ¼��ַ
				 */
				csf_string m_file_path = "";
				/**
				 * ��ʾ�����ļ��ĸ�ʽ
				 */
				csf_string m_format = "";
				/**
				 * ��ʾ�����ļ������������ڷḻ�����ļ��Ĵ���
				 */
				csf_string m_name = "";

			};

		}

	}

}
#endif // !defined(CSF_CONFIGURE_FILE_INCLUDED_)
