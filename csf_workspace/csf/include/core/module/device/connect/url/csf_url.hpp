/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_url.hpp
*
*Version: 1.0
*
*Date: 01-10��-2018 12:54:56
*
*Description: Class(csf_url) url��ַ��Ϣ�Ļ�������Ϣ
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_URL_H_INCLUDED_)
#define CSF_URL_H_INCLUDED_

#include "csf_base_include.h"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * url��ַ��Ϣ�Ļ�������Ϣ
				 * @author f
				 * @version 1.0
				 * @created 01-10��-2018 12:54:56
				 */
				class csf_url
				{

				public:
					/**
					 * ��ʾurl����
					 * @author f
					 * @version 1.0
					 * @created 01-10��-2018 12:54:56
					 */
					typedef enum csf_url_type_enum
					{
						/**
						 * ��ʾ�յ�ַ
						 */
						csf_url_type_none = 0x00000000,
						/**
						 * ��ʾIP��ַ
						 */
						csf_url_type_ip = 0x00010000,
						/**
						 * ��ʾ���ڵ�ַ
						 */
						csf_url_type_serial = 0x00020000
					} csf_url_type;


					csf_url();
					virtual ~csf_url();

					/**
					 * 
					 * @param type    ��ʾ���ӵ�ַ����
					 */
					inline explicit csf_url(const csf::core::module::connect::csf_url::csf_url_type type)
						: m_type(type)
						, m_url("") {

					}
					/**
					* ��Ҫ�����ǣ�ͨ��url�ַ�����������url����
					* ���أ����쳣��ʾ�ɹ����׳��쳣��ʾ����
					*
					* @param url    ��ʾurl�ַ�������
					*/
					inline virtual csf_url& operator =(const csf_string& url) {

						return  *this;
					}
					/**
					* ��Ҫ�����ǣ�ͨ��url�ַ�����������url����
					* ���أ����쳣��ʾ�ɹ����׳��쳣��ʾ����
					*
					* @param url    ��ʾurl�ַ�������
					*/
					inline virtual csf_url& operator =(const csf_char* url) {

						set_url(url);

						return  *this;
					}
					/**
					 * ��ʾurl��ַ��������Ϣ
					 */
					inline const csf::core::module::connect::csf_url::csf_url_type get_type() const {

						return m_type;
					}
					
					/**
					 * ��ʾurl�������ַ�������
					 */
					inline const csf_string & get_url() const {

						return m_url;
					}
					/**
					 * ��ʾurl�������ַ�������
					 * 
					 * @param new_value
					 */
					inline csf_int32 set_url(const csf_string& new_value) {

						m_url = new_value;

						return csf_succeed;
					}
					/**
					 * ��ʾurl�������ַ�������
					 * 
					 * @param new_value
					 */
					inline csf_int32 set_url(const csf_char* new_value) {

						m_url = new_value;

						return csf_succeed;
					}
					/**
					* ��ʾ������ַ����
					*
					* @param url    ��ʾurl��ַ�ַ�������
					*/
					inline virtual csf_int32 parse(const csf_string& url) {

						set_url(url);

						return csf_succeed;
					}
					/**
					 * ��ʾ������ַ����
					 * 
					 * @param url    ��ʾurl��ַ�ַ�������
					 */
					inline virtual csf_int32 parse(const csf_char* url) {

						set_url(url);

						return csf_succeed;
					}
					/**
					* ��Ҫ���ܣ�
					*    �ж�url��ַ�Ƿ�Ϸ�
					* ���أ�
					*    true ����ʾ�Ϸ�
					*    false����ʾ���Ϸ�
					*/
					inline virtual csf_bool is_valid() {

						if (csf_url_type_none != get_type()
							&& !get_url().empty()) {
							return csf_true;
						}
						return csf_false;
					}
				protected:
					/**
					 * ��ʾurl��ַ��������Ϣ
					 * 
					 * @param new_value
					 */
					inline csf_void set_type(const csf::core::module::connect::csf_url::csf_url_type new_value) {

						m_type = new_value;
					}

				private:
					/**
					 * ��ʾurl�������ַ�������
					 */
					csf::core::base::csf_string m_url = "";
					/**
					 * ��ʾurl��ַ��������Ϣ
					 */
					csf::core::module::connect::csf_url::csf_url_type m_type = csf_url_type_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_URL_H_INCLUDED_)
