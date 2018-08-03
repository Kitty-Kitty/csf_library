/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_int64.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:28
*
*Description: Class(csf_attribute_int64)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_INT64_INCLUDED_)
#define CSF_ATTRIBUTE_INT64_INCLUDED_

#include "csf_attribute_number.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * ��ʾ������������������
				 * @author fz
				 * @version 1.0
				 * @created 05-7��-2018 20:09:28
				 */
				class csf_attribute_int64 : public csf::core::system::attribute::csf_attribute_number
				{

				public:
					inline explicit csf_attribute_int64()
						: csf::core::system::attribute::csf_attribute_number(csf_attribute_type_int64) {

					}
					virtual ~csf_attribute_int64() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int64(const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(type, boundary, ex){

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int64(const csf_string& name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(name, type, boundary, ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int64(const csf_char* name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(name, type, boundary, ex) {

					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int64(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null()) 
					
						: csf_attribute_number(items, type, boundary, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int64(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())
					
						: csf_attribute_number(name, items, type, boundary, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					*
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_int64(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type = csf_attribute_type_int64
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null()) 
					
						: csf_attribute_number(name, items, type, boundary, ex) {

					}


				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_INT64_INCLUDED_)
