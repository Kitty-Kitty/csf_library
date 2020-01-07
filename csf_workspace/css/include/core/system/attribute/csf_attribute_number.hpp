/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_number.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:09:28
*
*Description: Class(csf_attribute_number)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_NUMBER_INCLUDED_)
#define CSF_ATTRIBUTE_NUMBER_INCLUDED_

#include "csf_attribute_boundary.hpp"
#include "csf_attribute_template.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/**
				 * ��ʾ������������
				 * @author fz
				 * @version 1.0
				 * @created 05-7��-2018 20:09:28
				 */
				class csf_attribute_number : public csf::core::system::attribute::csf_attribute_template<csf_int64>
				{

				public:
					inline explicit csf_attribute_number() 
						: csf_attribute_template<csf_int64>(csf_attribute::csf_attribute_type_int64, 0){

					}
					virtual ~csf_attribute_number() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_number(const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(type, 0, ex)
						, m_boundary(boundary) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_number(const csf_string& name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, type, 0, ex)
						, m_boundary(boundary) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param type    ��ʾ���Ե�����
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_number(const csf_char* name
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, type, 0, ex)
						, m_boundary(boundary) {

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
					inline explicit csf_attribute_number(const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(items, type, 0, ex)
						, m_boundary(boundary) {

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
					inline explicit csf_attribute_number(const csf_string& name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, items, type, 0, ex)
						, m_boundary(boundary) {

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
					inline explicit csf_attribute_number(const csf_char* name
						, const csf_list<csf_string> items
						, const csf::core::system::attribute::csf_attribute::csf_attribute_type type
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_template<csf_int64>(name, items, type, 0, ex)
						, m_boundary(boundary) {

					}
					/**
					 * ��ʾģ��������ֵ�������
					 */
					inline csf::core::system::attribute::csf_attribute_boundary& get_boundary() {

						return m_boundary;
					}
					/**
					 * ��ʾģ��������ֵ�������
					 *
					 * @param newVal    ��ʾ��Ҫ���õ���ֵ����
					 */
					inline csf_void set_boundary(csf::core::system::attribute::csf_attribute_boundary& newVal) {

						m_boundary = newVal;
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
					virtual csf_bool process_number(const csf_configure_manager& configure_manager, const csf_string& alias) = 0;
					/**
					* ��ʾ����csf_attribute���Բ�����������csf_attribute�в�ͬ���ǣ��������һ��process_attribute������Ҫ��Ϊ��ʵ���쳣��e
					* xception����ͳһ�������쳣����ʱ��ֱ�Ӹ��ݷ��ش��󣬵����쳣��������
					* ���أ�true��ʾʧ�ܣ�false��ʾ�ɹ���
					*
					* @param configure_manager    ��ʾ�������ù���������
					* @param alias    ��ʾ��ǰ���Ա����������������Ϊ������ʹ�øñ�����
					*/
					virtual csf_bool process_attribute(const csf_configure_manager& configure_manager, const csf_string& alias) final;
				private:
					/**
					 * ��ʾģ��������ֵ�������
					 */
					csf::core::system::attribute::csf_attribute_boundary m_boundary;

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_NUMBER_INCLUDED_)
