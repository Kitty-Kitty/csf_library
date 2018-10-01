/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_error.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 30-6��-2018 17:22:42
*
*Description: Class(csf_error) ����������Ϣ
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ERROR_INCLUDED_)
#define CSF_ERROR_INCLUDED_

#include <stdarg.h>
#include "csf_typedef.h"
#include "csf_stddef.h"
#include "csf_default.h"
#include "csf_errno.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			/**
			 * ����������Ϣ
			 * @author fz
			 * @version 1.0
			 * @created 30-6��-2018 17:22:42
			 */
			class csf_error
			{

			public:
				inline explicit csf_error()
				    : m_code(0) {

				}
				/**
				 * ��ʾ���ݴ����루code���ʹ���������description������һ��csf_error��
				 * 
				 * @param code    ��ʾ���������
				 * @param description    ��ʾ����������Ϣ
				 */
				inline explicit csf_error(const csf_int32 code, const csf_string& description)
					: m_code(code) {

					csf_error(code, description.c_str());
				}
				/**
				 * ��ʾ���ݴ����루code���ʹ���������description������һ��csf_error��
				 * 
				 * @param code    ��ʾ���������
				 * @param description    ��ʾ����������Ϣ
				 */
				inline explicit csf_error(const csf_int32 code, const csf_char* description) 
					: m_code(code) {

					if (csf_failure == set_descripion(description)) {
						throw csf_nullptr;
					}
				}
				inline virtual ~csf_error() {

				}
				inline csf_string to_string() {

					return "";
				}
				/**
				 * ��ʾ������
				 */
				inline csf_int32 get_code() {

					return m_code;
				}
				/**
				 * ��ʾ������
				 * 
				 * @param new_value    new_value
				 */
				inline csf_void set_code(const csf_int32 new_value) {

					m_code = new_value;
				}
				/**
				 * ��ʾ����ԭ��������Ϣ
				 */
				inline csf_char* get_description() {

					return m_descripion;
				}
				/**
				 * ��ʾ����ԭ��������Ϣ
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 * 
				 * @param new_value    new_value
				 */
				inline csf_int32 set_description(const csf_char* new_value) {

					if (!new_value || csf_strlen(new_value) > csf_errno_max_length) {
						return csf_failure;
					}

					csf_strcpy(m_descripion, new_value);
					return csf_success;
				}
				/**
				 * ��ʾ����ԭ��������Ϣ
				 */
				inline csf_string get_descripion() {

					return m_descripion;
				}
				/**
				 * ��ʾ����ԭ��������Ϣ
				 * ���أ�0��ʾ�ɹ�����0��ʾʧ�ܡ�
				 * 
				 * @param new_value
				 */
				inline csf_int32 set_descripion(const csf_string& new_value) {

					return set_description(new_value.c_str());
				}
				/**
				* ��ʾ���ݴ����루code���ʹ���������description������һ��csf_error��
				*
				* @param code    ��ʾ���������
				* @param fmt    ��ʾ����������Ϣ��ʽ���ַ���
				* @param ...    ��ʾ��ʽ����������
				*/
				inline csf_bool set_error(const csf_int32 code, const csf_char* fmt, ...) {

					va_list					tmp_marker;
					csf_char				tmp_buf[csf_errno_max_length] = { 0, };


					if (!fmt || csf_strlen(fmt) <= 0) {
						return csf_false;
					}

					va_start(tmp_marker, fmt);					
					if (csf_vsnprintf(tmp_buf, csf_sizeof(tmp_buf), fmt, tmp_marker) < 0) {
						//������󳤶Ⱥ�ֻ��ӡ��������
						tmp_buf[csf_sizeof(tmp_buf) - 2] = '.';
						tmp_buf[csf_sizeof(tmp_buf) - 3] = '.';
						tmp_buf[csf_sizeof(tmp_buf) - 4] = '.';
					}
					va_end(tmp_marker);

					set_code(code);
					set_descripion(tmp_buf);

					return csf_true;
				}
				/**
				* ��ʾ���ݴ����루code���ʹ���������description������һ��csf_error��
				*
				* @param code    ��ʾ���������
				* @param description    ��ʾ����������Ϣ
				*/
				inline csf_bool set_error(const csf_int32 code, const csf_string& description) {

					if (description.empty()) {
						return csf_false;
					}
					return set_error(code, description.c_str());
				}
			private:
				/**
				 * ��ʾ������
				 */
				csf_int32 m_code = 0;
				/**
				 * ��ʾ����ԭ��������Ϣ
				 */
				csf_char m_descripion[csf_errno_max_length] = {0};

			};

		}

	}

}
#endif // !defined(CSF_ERROR_INCLUDED_)
