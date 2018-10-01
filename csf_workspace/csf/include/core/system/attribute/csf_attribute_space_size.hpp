/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_space_size.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7��-2018 10:47:28
*
*Description: Class(csf_attribute_space_size)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_SPACE_SIZE_INCLUDED_)
#define CSF_ATTRIBUTE_SPACE_SIZE_INCLUDED_

#include "csf_stdcollector.hpp"
#include "csf_attribute_int64.hpp"

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
				#define csf_attribute_space_size_parametes_size						2		//��ʾ��Ҫ��ȡ�Ĳ�������
				
				/**
				 * ��ʾ�ռ����͸�ʽΪ:��ֵ+��λ����λ������B/KB/MB/GB/TB/PB���ֱ��ʾ���ֽ�/ǧ�ֽ�/���ֽ�/���ֽ�/������λ�ϸ�Ҫ���ʽ������:100MB
				 * @author fz
				 * @version 1.0
				 * @created 11-7��-2018 10:47:28
				 */
				class csf_attribute_space_size : public csf::core::system::attribute::csf_attribute_int64
				{

				public:
					/**
					 * ��ʾ�ռ䵥λ
					 * @author f
					 * @version 1.0
					 * @created 11-7��-2018 10:47:28
					 */
					enum csf_space_size_unit
					{
						/**
						 * ��ʾδ֪�ռ䵥λ
						 */
						csf_space_size_unit_none = 0x00000000,
						/**
						 * ��ʾ�ֽڵ�λ
						 */
						csf_space_size_unit_b = 0x00000001,
						/**
						 * ��ʾ�ֽڵ�λ
						 */
						csf_space_size_unit_kb = 0x00000002,
						/**
						 * ��ʾ�ֽڵ�λ
						 */
						csf_space_size_unit_mb = 0x00000004,
						/**
						 * ��ʾ�ֽڵ�λ
						 */
						csf_space_size_unit_gb = 0x00000008,
						/**
						 * ��ʾ�ֽڵ�λ
						 */
						csf_space_size_unit_tb = 0x00000010,
						/**
						 * ��ʾ�ֽڵ�λ
						 */
						csf_space_size_unit_pb = 0x00000020
					};

					//������ִ�С��λ�̶ȵı���ֵ
#define				CSF_SPACE_SIZE_UNIT_SCALE(CSF_SPACE_SIZE_UNIT_SCALE_MAP)						\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(none, 1ll)										\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(b,	1ll)										\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(kb,   1024ll)										\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(mb,   1024 * 1024ll)								\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(gb,   1024 * 1024 * 1024ll)						\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(tb,   1024 * 1024 * 1024 * 1024ll)				\
					CSF_SPACE_SIZE_UNIT_SCALE_MAP(pb,   1024 * 1024 * 1024 * 1024 * 1024ll)			\

					inline explicit csf_attribute_space_size()
						: csf_attribute_int64(csf_attribute_type_space_size)
						, m_unit(csf_space_size_unit::csf_space_size_unit_b) {
					}

					virtual ~csf_attribute_space_size() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(csf_attribute_type_space_size, boundary, ex)
						, m_unit(csf_space_size_unit::csf_space_size_unit_b) {

					}

					/**
					* �������ʹ���һ������
					*
					* @param unit    ��ʾĬ�ϵĿռ䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf_space_size_unit unit = csf_space_size_unit_b
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(csf_attribute_type_space_size, boundary, ex)
						, m_unit(csf_space_size_unit::csf_space_size_unit_b) {

					}

					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param unit    ��ʾĬ�ϵĿռ䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf_string& name
						, const csf_space_size_unit unit = csf_space_size_unit_b
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_space_size(name.c_str(), unit, boundary, ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param unit    ��ʾĬ�ϵĿռ䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf_char* name
						, const csf_space_size_unit unit = csf_space_size_unit_b
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(name, csf_attribute_type_space_size, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					* @param unit    ��ʾĬ�ϵĿռ䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf_list<csf_string> items
						, const csf_space_size_unit unit = csf_space_size_unit_b
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(items, csf_attribute_type_space_size, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					* @param unit    ��ʾĬ�ϵĿռ䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf_string& name
						, const csf_list<csf_string> items
						, const csf_space_size_unit unit = csf_space_size_unit_b
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_space_size(name.c_str(), items, unit, boundary, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					* @param unit    ��ʾĬ�ϵĿռ䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_space_size(const csf_char* name
						, const csf_list<csf_string> items
						, const csf_space_size_unit unit = csf_space_size_unit_b
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(name, items, csf_attribute_type_space_size, boundary, ex)
						, m_unit(unit) {

					}
					/**
					 * ��ʾ�ռ�ĵ�λ
					 */
					inline csf_space_size_unit& get_unit() {

						return m_unit;
					}
					/**
					 * ��ʾ�ռ�ĵ�λ
					 * 
					 * @param new_value
					 */
					inline void set_unit(csf_space_size_unit& new_value) {

						m_unit = new_value;
					}
					/**
					 * �������н�����Ҫ�Ĳ�����
					 * ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
					 * 
					 * @param content    ��ʾ��Ҫ������������Ϣ
					 */
					csf_bool parse_parametes(const csf_string& content);
					/**
					 * �������н�����Ҫ�Ĳ�����
					 * ���أ�ture��ʾ�����ɹ���false��ʾ����ʧ�ܡ�
					 * 
					 * @param content    ��ʾ��Ҫ������������Ϣ
					 */
					inline csf_bool parse_parametes(const csf_char* content) {

						if (!content || csf_strlen(content) <= 0) {
							return csf_false;
						}

						return parse_parametes(csf_string(content));
					}
					/**
					 * ��ʾʱ�䵥λ���ƵĶ�Ӧ�б�
					 */
					inline const csf_unordered_map<csf_string, csf_space_size_unit>& get_unit_name() {

						return m_unit_name;
					}
					/**
					 * ��ʾ���ַ���ʱ�䵥λת��Ϊ������ֵ
					 * 
					 * @param unit    ��ʾ��Ҫ��ת���ĵ�λ�ַ���
					 */
					inline csf_space_size_unit convert(const csf_string& unit) {

						if (unit.empty()) {
							return csf_space_size_unit::csf_space_size_unit_none;
						}

						auto tmp_iter = get_unit_name().find(unit);
						if (tmp_iter != get_unit_name().end()) {
							return tmp_iter->second;
						}
						return csf_space_size_unit::csf_space_size_unit_none;
					}
					/**
					 * ��ʾ���ַ���ʱ�䵥λת��Ϊ������ֵ
					 * 
					 * @param unit    ��ʾ��Ҫ��ת���ĵ�λ�ַ���
					 */
					inline csf_space_size_unit convert(const csf_char* unit) {

						if (!unit || csf_strlen(unit)) {
							return csf_space_size_unit::csf_space_size_unit_none;
						}

						return  convert(csf_string(unit));
					}
					/**
					 * ��ʾ��ʱ����ֵת��Ϊָ����ʽ��ʱ����ֵ��
					 * ���أ�true��ʾת���ɹ���false��ʾת��ʧ�ܣ�
					 * 
					 * @param dest_value    ��ʾת�����Ŀ�굥λ��ֵ
					 * @param dest_unit    ��ʾת�����Ŀ����ֵ��λ
					 * @param src_value    ��ʾ��Ҫ��ת����Դ��λ��ֵ
					 * @param src_unit    ��ʾԴ��ֵ��λ
					 */
					inline csf_bool convert(csf_int64& dest_value, const csf_space_size_unit& dest_unit
						, const csf_int64& src_value, const csf_space_size_unit& src_unit) {

						csf_int64						tmp_value = 0;


						//Ϊʵ��ת�����Ƚ�Դ��ʽ�ռ䵥λת��Ϊ�ֽ�
						if (csf_false == convert_to_bytes(tmp_value, src_value, src_unit)) {
							return csf_false;
						}

						//Ϊʵ��ת�������Ž��ֽ�ת��Ϊָ���Ŀռ䵥λ
						if (csf_false == convert_from_bytes(tmp_value, dest_unit, tmp_value)) {
							return csf_false;
						}

						dest_value = tmp_value;

						return csf_true;
					}
					/**
					 * ��ʾ��������ֵת��Ϊ�ַ���ʱ�䵥λ
					 * 
					 * @param unit    ��ʾ��Ҫ��ת���ĵ�λ��ֵ
					 */
					inline const csf_string convert(const csf_space_size_unit unit) {

						for (auto &tmp_unit : get_unit_name()) {
							if (tmp_unit.second == unit) {
								return tmp_unit.first;
							}
						}
						return  csf_string_null;
					}
					/**
					* ���������ǽ�csf_attribute������Ϣ��ʽ��
					*/
					inline csf_string to_string() {
						csf_char				tmp_buf[csf_attribute_string_length] = { 0, };

						csf_snprintf(tmp_buf, csf_sizeof(tmp_buf)
							, "%s value[ %lld %s ]"
							, csf_attribute::to_string().c_str()
							, get_value()
							, convert(get_unit()).c_str()
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
					/**
					* ��ʾ���ָ�ʽ���ݵ�˵��
					*/
					inline const csf_string& get_usage() {

						return m_usage;
					}
				private:
					/**
					 * ��ʾ�ռ�ĵ�λ
					 */
					csf_space_size_unit m_unit = csf_space_size_unit_none;
					/**
					 * ��ʾʱ�䵥λ���ƵĶ�Ӧ�б�
					 */
					static const csf_unordered_map<csf_string, csf_space_size_unit> m_unit_name;
					/**
					* ��ʾ���ָ�ʽ���ݵ�˵��
					*/
					static const csf_string m_usage;
					/**
					 * ��ȡ��ֵ�͵�λ������ݡ�
					 * ���أ�true��ʾ����ɹ���false��ʾ����ʧ�ܡ�
					 * 
					 * @param val    ��ʾ��Ҫ�������ֵ����
					 * @param unit    ��ʾ����ֵ�ĵ�λ�ַ�
					 */
					csf_bool get_parametes(const csf_string& val, const csf_string& unit);
#if 0
					/**
					 * ��ʾʱ�䵥λ���ƵĶ�Ӧ�б�
					 * 
					 * @param new_value    ��ʾʱ�䵥λ���ƵĶ�Ӧ�б�
					 */
					inline csf_void set_unit_name(csf_unordered_map<csf_string, csf_space_size_unit>& new_value) {

						m_unit_name = new_value;
					}
#endif
					/**
					 * ��ʾ��ʱ����ֵת��Ϊ�����ʽ��ʱ����ֵ��
					 * ���أ�true��ʾת���ɹ���false��ʾת��ʧ�ܣ�
					 * 
					 * @param dest_value    ��ʾת�����Ŀ�굥λ��ֵ����λΪ����(ns)
					 * @param src_value    ��ʾ��Ҫ��ת����Դ��λ��ֵ
					 * @param src_unit    ��ʾԴ��ֵ��λ
					 */
					inline csf_bool convert_to_bytes(csf_int64& dest_value, const csf_int64& src_value, const csf_space_size_unit& src_unit) {

#ifndef CSF_SPACE_SIZE_UNIT_SCALE_GEN
#define CSF_SPACE_SIZE_UNIT_SCALE_GEN(type, scale)				case csf_space_size_unit_ ## type: {dest_value = src_value * scale;}break;

						switch (src_unit) {
							CSF_SPACE_SIZE_UNIT_SCALE(CSF_SPACE_SIZE_UNIT_SCALE_GEN)

						default:
							return csf_false;
							break;
						}

#undef  CSF_SPACE_SIZE_UNIT_SCALE_GEN
#endif // CSF_SPACE_SIZE_UNIT_SCALE_GEN
						return csf_true;
					}
					/**
					 * ��ʾ������ʱ����ֵת��Ϊָ����ʽ��ʱ����ֵ��
					 * ���أ�true��ʾת���ɹ���false��ʾת��ʧ�ܣ�
					 * 
					 * @param dest_value    ��ʾת�����Ŀ�굥λ��ֵ
					 * @param dest_unit    ��ʾת�����Ŀ����ֵ��λ
					 * @param src_value    ��ʾ��Ҫ��ת����Դ��λ��ֵ
					 */
					inline csf_bool convert_from_bytes(csf_int64& dest_value, const csf_space_size_unit& dest_unit, const csf_int64& src_value) {

#ifndef CSF_SPACE_SIZE_UNIT_SCALE_GEN
#define CSF_SPACE_SIZE_UNIT_SCALE_GEN(type, scale)				case csf_space_size_unit_ ## type: {dest_value = src_value / scale;}break;

						switch (dest_unit) {
							CSF_SPACE_SIZE_UNIT_SCALE(CSF_SPACE_SIZE_UNIT_SCALE_GEN)

						default:
							return csf_false;
							break;
						}

#undef  CSF_SPACE_SIZE_UNIT_SCALE_GEN
#endif // CSF_SPACE_SIZE_UNIT_SCALE_GEN

						return csf_true;
					}

				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_SPACE_SIZE_INCLUDED_)
