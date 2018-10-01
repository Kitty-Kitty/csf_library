/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_boundary.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 04-7��-2018 22:13:15
*
*Description: Class(csf_attribute_boundary)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_BOUNDARY_INCLUDED_)
#define CSF_ATTRIBUTE_BOUNDARY_INCLUDED_

#include <map>
#include <regex>
#include <functional>
#include <unordered_set>
#include "csf_typedef.h"
#include "csf_default.h"
#include "csf_stddef.h"
#include "csf_error.hpp"
#include "csf_csftype_template.hpp"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace attribute
			{
				/************************************************************************/
				/* �����ַ������Ĭ�ϳ���                                                 */
				/************************************************************************/
				#define csf_boundary_string_default_length				32				//�����ַ������Ĭ�ϳ���

				/************************************************************************/
				/* ��Ҫ��ȡ�Ĳ�������														*/
				/************************************************************************/
				#define csf_boundary_parametes_size						4				//��ʾ��Ҫ��ȡ�Ĳ�������

				/**
				* ��ʾ�������õ����ƣ����ֲ�ͬ�����������и��ԵĲ�ͬ��ʽ�����ơ�
				* @author fz
				* @version 1.0
				* @created 04-7��-2018 22:55:39
				*/
				class csf_attribute_boundary : public csf::core::module::csf_error, public csf::core::base::csf_csftype_template<csf_attribute_boundary>
				{

				public:
					inline explicit csf_attribute_boundary()
						: m_lower_bound(csf_min_long)
						, m_upper_bound(csf_max_long) {

					}
					virtual ~csf_attribute_boundary() {

					}

					/**
					* ��ʾ���������ַ�������У�����
					* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
					*
					* @param boundary    �����ַ������������Ʊ�ʾ��
					* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
					*/
					inline explicit csf_attribute_boundary(const csf_char* boundary)
						: m_lower_bound(csf_min_long)
						, m_upper_bound(csf_max_long) 
						, m_boundary(boundary) {

					}
					/**
					* ��ʾ���������ַ�������У�����
					* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
					*
					* @param boundary    �����ַ������������Ʊ�ʾ��
					* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
					*
					*/
					inline explicit csf_attribute_boundary(const csf_string& boundary) :
						csf_attribute_boundary(boundary.c_str()) {

					}
					/**
					* ��ʾ������麯����
					* ���أ�true��ʾ����ɹ���false��ʾ�������
					*
					* @param val    ��ʾ��ǰ�ĺ�����ֵ
					*/
					inline csf_bool process(const csf_int64 val) {

						if (csf_nullptr == get_function()) {
							return csf_false;
						}

						return process(val, get_lower_bound(), get_upper_bound(), get_function());
					}
					/**
					* ��ʾ��ֵ����Сֵ��
					*/
					inline csf_int64 get_lower_bound() {

						return m_lower_bound;
					}
					/**
					* ��ʾ��ֵ����Сֵ��
					*
					* @param new_value
					*/
					inline csf_void set_lower_bound(csf_int64 new_value) {

						m_lower_bound = new_value;
					}
					/**
					* ��ʾ��ֵ�����ֵ��
					*/
					inline csf_int64 get_upper_bound() {

						return m_upper_bound;
					}
					/**
					* ��ʾ��ֵ�����ֵ��
					*
					* @param new_value
					*/
					inline csf_void set_upper_bound(csf_int64 new_value) {

						m_upper_bound = new_value;
					}
					
					/**
					* ��ʾ��ֵ�����ַ�������
					*/
					inline csf_string& get_boundary() {

						return m_boundary;
					}
					/**
					* ��ʾ��ֵ�����ַ�������
					*
					* @param new_value
					*/
					inline void set_boundary(const csf_string& new_value) {

						m_boundary = new_value;
					}
					/**
					* ��ʾ��ֵ�����ַ�������
					*
					* @param new_value
					*/
					inline void set_boundary(const csf_char* new_value) {

						m_boundary = new_value;
					}
					/**
					* ��ʾboundaryʹ�÷�ʽ��������Ϣ��
					*/
					inline const csf_string& get_usage() {

						return m_usage;
					}
					/**
					* ��ʾ�ж��Ƿ�Ϊ�ա�
					* ���أ�true��ʾΪ�գ�false��ʾ��Ϊ�ա�
					*/
					inline virtual csf_bool is_null() {

						if (get_boundary().empty()) {
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
					/**
					* ��ʾ��ʼ���߽��������
					*/
					inline csf_bool init() {

						return parse(get_boundary());
					}
					protected:
						/**
						* ��ʾ���������ַ�������У�����
						* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
						*
						* @param boundary    �����ַ������������Ʊ�ʾ��
						* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
						*/
						csf_bool parse(const csf_char* boundary);
						/**
						* ��ʾ���������ַ�������У�����
						* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
						*
						* @param boundary    �����ַ������������Ʊ�ʾ��
						* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
						*
						*/
						inline csf_bool parse(const csf_string& boundary) {

							if (boundary.empty()) {
								return csf_false;
							}

							return parse(boundary.c_str());
						}
				private:
					/**
					* ��ʾ��ֵ����Сֵ��
					*/
					csf_int64 m_lower_bound = csf_min_long;
					/**
					* ��ʾ��ֵ�����ֵ��
					*/
					csf_int64 m_upper_bound = csf_max_long;
					/**
					* ��ʾ���鴦������Ӧ��
					*/
					static const std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>> m_functions;
					/**
					* ��ʾ��ֵ�����ַ�������,����:"(0, 100]"
					*/
					csf_string m_boundary = "";
					/**
					* ��ʾboundaryʹ�÷�ʽ��������Ϣ��
					*/
					static const csf_string m_usage;
					/**
					* ��ʾ��ǰ���鴦�������
					*/
					std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)> m_function = csf_nullptr;

					/**
					* ��ʾ������麯����
					* ���أ�true��ʾ����ɹ���false��ʾ�������
					*
					* @param val    ��ʾ��ǰ�ĺ�����ֵ
					* @param lower    ��ʾ��ֵ����Сֵ
					* @param upper    ��ʾ��ֵ�����ֵ
					* @param func    ��ʾ���鴦����
					*/
					inline csf_bool process(const csf_int64 val, const csf_int64 lower, const csf_int64 upper, 
						const std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)> func) {

						if (csf_nullptr == func) {
							return csf_false;
						}

						return func(val, lower, upper);
					}
					/**
					* ��ʾ���鴦������Ӧ��
					*/
					inline const std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>>& get_functions() {

						return m_functions;
					}
#if 0
					/**
					* ��ʾ���鴦������Ӧ��
					*
					* @param new_value
					*/
					inline csf_void set_functions(std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>>& new_value) {

						m_functions = new_value;
					}
#endif
					/**
					* ��ʾ��ǰ���鴦�������
					*/
					inline std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>& get_function() {

						return m_function;
					}
					/**
					* ��ʾ��ǰ���鴦�������
					*
					* @param new_value
					*/
					inline csf_void set_function(std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>& new_value) {

						m_function = new_value;
					}
					/**
					* ��ʾ���������ַ�������У�����
					* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param boundary    �����ַ������������Ʊ�ʾ��
					* ���и�ʽ�������������ʽ������:(-n, 100), [0, 100]�����С�(����ʾ�����ڱ߽磻��[����ʾ���ڱ߽������
					*
					*/
					csf_bool parse_parametes(const csf_string boundary);
					
					/**
					* ���ݴ������ֵ�߽������ַ�����ȡ���ݡ�����-nת��Ϊint64����Сֵ��+nת��Ϊint64�����ֵ��
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param lower	��ֵ����Сֵ
					* @param upper	��ֵ�����ֵ
					*/
					csf_bool get_parametes(const csf_string& lower, const csf_string& upper);
					/**
					* ���ݴ�����ַ���ƥ�����������
					* ���أ�true��ʾ�ɹ���false��ʾʧ�ܡ�
					*
					* @param boundary_flag
					*/
					inline csf_bool get_function(csf_string boundary_flag) {

						std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>>::iterator	tmp_iter;


						tmp_iter = const_cast<std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>>&>(get_functions()).find(boundary_flag);
						if (tmp_iter == get_functions().end()) {
							return csf_false;
						}
						else {
							set_function(tmp_iter->second);
						}
						return csf_true;
					}
#if 0
					/**
					* ��ʾboundaryʹ�÷�ʽ��������Ϣ��
					*
					* @param new_value
					*/
					inline void set_usage(csf_string& new_value) {

						m_usage = new_value;
					}
#endif
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_BOUNDARY_INCLUDED_)
