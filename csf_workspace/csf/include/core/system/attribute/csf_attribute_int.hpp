/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_int.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7��-2018 11:09:59
*
*Description: Class(csf_attribute_int)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INT_INCLUDED_)
#define CSF_ATTRIBUTE_INT_INCLUDED_

#include "csf_attribute_exception.hpp"
#include "csf_attribute_number.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/************************************************************************/
				/* ��Ҫ��ȡ�Ĳ�������														*/
				/************************************************************************/
				#define csf_attribute_int_parametes_size						1		//��ʾ��Ҫ��ȡ�Ĳ�������
				/**
				 * ��ʾ�����������͡�
				 * @author fz
				 * @version 1.0
				 * @created 11-7��-2018 11:09:59
				 */
				class csf_attribute_int : public csf::core::system::attribute::csf_attribute_number
				{

				public:
					inline explicit csf_attribute_int()
						: csf_attribute_number(csf_attribute_type_int) {
					}

					virtual ~csf_attribute_int() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int(const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(csf_attribute_type_int, boundary, ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int(const csf_string& name
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int(name.c_str(), boundary, ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int(const csf_char* name
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(name, csf_attribute_type_int, boundary, ex) {

					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(items, csf_attribute_type_int, boundary, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int(name.c_str(), items, boundary, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_number(name, items, csf_attribute_type_int, boundary, ex) {

					}
					/**
					 * �������н�����Ҫ�Ĳ�����
					 * ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
					 * 
					 * @param content    ��ʾ��Ҫ������������Ϣ
					 */
					inline csf_bool parse_parametes(const csf_char* content) {

						return csf_true;
					}
					/**
					 * �������н�����Ҫ�Ĳ�����
					 * ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
					 * 
					 * @param content    ��ʾ��Ҫ������������Ϣ
					 */
					csf_bool parse_parametes(const csf_string& content);
					/**
					 * ���������ǽ�csf_attribute������Ϣ��ʽ��
					 */
					inline csf_string to_string() {

						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
							, "%s value[ %lld ]"
							, csf_attribute::to_string().c_str()
							, get_value()
						);

						return tmp_buf;
					}

				protected:
					/**
					 * ��ʾ����csf_attribute���Բ�����������csf_attribute_template�в�ͬ���ǣ��������һ��process_number������Ҫ��Ϊ��
					 * ʵ�����ݱ߽��ͳһ����
					 * ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					 * 
					 * @param configure_manager    ��ʾ�������ù���������
					 * @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					 */
					virtual csf_bool process_number(const csf_configure_manager& configure_manager, const csf_string& alias);

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_INT_INCLUDED_)
