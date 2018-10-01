/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_attribute_time.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 05-7��-2018 20:55:12
*
*Description: Class(csf_attribute_time)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_ATTRIBUTE_TIME_INCLUDED_)
#define CSF_ATTRIBUTE_TIME_INCLUDED_

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
				#define csf_attribute_time_parametes_size						2		//��ʾ��Ҫ��ȡ�Ĳ�������
				/**
				 * ��ʾʱ���ʽ�������͡������͸�ʽΪ:
				 * ��ֵ+��λ����λ������ns/us/ms/s/m/h/d���ֱ��ʾ������/΢��/����/��/����/Сʱ/�죩����λ�ϸ�Ҫ��Сд��ʽ������:100sΪ100��
				 * @author fz
				 * @version 1.0
				 * @created 05-7��-2018 20:55:12
				 */
								class csf_attribute_time : public csf::core::system::attribute::csf_attribute_int64
				{

				public:
					/**
					* ��ʾʱ���ʽ�ĵ�λ����
					* @author Administrator
					* @version 1.0
					* @updated 08-7��-2018 15:17:20
					*/
					enum csf_time_unit
					{
						/**
						* ��ʾ<font color="#008000">δ����ĵ�λ</font>
						*/
						csf_time_unit_none = 0x00000000,
						/**
						* ��ʾ���뵥λ
						*/
						csf_time_unit_ns,
						/**
						* ��ʾ<font color="#008000">΢��</font>��λ
						*/
						csf_time_unit_us,
						/**
						* ��ʾ<font color="#008000">����</font>��λ
						*/
						csf_time_unit_ms,
						/**
						* ��ʾ<font color="#008000">��</font>��λ
						*/
						csf_time_unit_s,
						/**
						* ��ʾ<font color="#008000">����</font>��λ
						*/
						csf_time_unit_m,
						/**
						* ��ʾ<font color="#008000">Сʱ</font>��λ
						*/
						csf_time_unit_h,
						/**
						* ��ʾ<font color="#008000">��</font>��λ
						*/
						csf_time_unit_d
					};

					//�������ʱ�䵥λ�̶ȵı���ֵ
#define				CSF_TIME_UNIT_SCALE(CSF_TIME_UNIT_SCALE_MAP)							\
					CSF_TIME_UNIT_SCALE_MAP(none, 1ll)										\
					CSF_TIME_UNIT_SCALE_MAP(ns,	  1ll)										\
					CSF_TIME_UNIT_SCALE_MAP(us,   1000ll)									\
					CSF_TIME_UNIT_SCALE_MAP(ms,   1000000ll)								\
					CSF_TIME_UNIT_SCALE_MAP(s,    1000000000ll)								\
					CSF_TIME_UNIT_SCALE_MAP(m,    (60 * 1000000000ll))						\
					CSF_TIME_UNIT_SCALE_MAP(h,    (60 * 60 * 1000000000ll))					\
					CSF_TIME_UNIT_SCALE_MAP(d,    (24 * 60 * 60 * 1000000000ll))			\


					inline explicit csf_attribute_time()
						: csf_attribute_int64(csf_attribute_type_time)
						, m_unit(csf_time_unit::csf_time_unit_s) {
					}

					virtual ~csf_attribute_time() {

					}

					/**
					* �������ʹ���һ������
					*
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(csf_attribute_type_time, boundary, ex)
						, m_unit(csf_time_unit::csf_time_unit_s) {

					}
					/**
					* �������ʹ���һ������
					*
					* @param unit    ��ʾĬ�ϵ�ʱ�䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param unit    ��ʾĬ�ϵ�ʱ�䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf_string& name
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_time(name.c_str(), unit, boundary, ex) {

					}
					/**
					* �������ƺ����ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param unit    ��ʾĬ�ϵ�ʱ�䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf_char* name
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(name, csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* ��������·�������ʹ���һ������
					*
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					* @param unit    ��ʾĬ�ϵ�ʱ�䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf_list<csf_string> items
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(items, csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					* @param unit    ��ʾĬ�ϵ�ʱ�䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf_string& name
						, const csf_list<csf_string> items
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_time(name.c_str(), items, unit, boundary, ex) {

					}
					/**
					* �������ơ�����·�������ʹ���һ������
					*
					* @param name    ��ʾ���Ե�����
					* @param items    ��ʾ����������Ӧ�������ļ��ڵ�λ��
					* @param unit    ��ʾĬ�ϵ�ʱ�䵥λ
					* @param boundary    ��ʾ�������Եķ�Χ�߽������Ϣ
					* @param ex    ��ʾ�����쳣�������
					*/
					inline explicit csf_attribute_time(const csf_char* name
						, const csf_list<csf_string> items
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(name, items, csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					 * ��ʾʱ��ĵ�λ
					 */
					inline csf_time_unit get_unit() {

						return m_unit;
					}
					/**
					 * ��ʾʱ��ĵ�λ
					 *
					 * @param new_value
					 */
					inline void set_unit(const csf_time_unit new_value) {

						m_unit = new_value;
					}
					/**
					* ��ʾʱ�䵥λ���ƵĶ�Ӧ�б�
					*/
					inline const csf_unordered_map<csf_string, csf_time_unit>& get_unit_name() {

						return m_unit_name;
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
					* ��ʾ���ַ���ʱ�䵥λת��Ϊ������ֵ
					*
					* @param unit    ��ʾ��Ҫ��ת���ĵ�λ�ַ���
					*/
					inline csf_time_unit convert(const csf_string& unit) {

						if (unit.empty()) {
							return csf_time_unit::csf_time_unit_none;
						}

						auto tmp_iter = get_unit_name().find(unit);
						if (tmp_iter != get_unit_name().end()) {
							return tmp_iter->second;
						}
						return csf_time_unit::csf_time_unit_none;
					}
					/**
					* ��ʾ���ַ���ʱ�䵥λת��Ϊ������ֵ
					*
					* @param unit    ��ʾ��Ҫ��ת���ĵ�λ�ַ���
					*/
					inline csf_time_unit convert(const csf_char* unit) {

						if (!unit || csf_strlen(unit)) {
							return csf_time_unit::csf_time_unit_none;
						}

						return  convert(csf_string(unit));
					}
					/**
					* ��ʾ��������ֵת��Ϊ�ַ���ʱ�䵥λ
					*
					* @param unit    ��ʾ��Ҫ��ת���ĵ�λ��ֵ
					*/
					inline const csf_string convert(const csf_time_unit unit) {

						for (auto &tmp_unit : get_unit_name()) {
							if (tmp_unit.second == unit) {
								return tmp_unit.first;
							}
						}
						return  csf_string_null;
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
					inline csf_bool convert(csf_int64& dest_value, const csf_time_unit& dest_unit,
						const csf_int64& src_value, const csf_time_unit& src_unit) {

						csf_int64						tmp_value = 0;


						//Ϊʵ��ת�����Ƚ�Դ��ʽʱ��ת��Ϊ�����ʽ
						if (csf_false == convert_to_ns(tmp_value, src_value, src_unit)) {
							return csf_false;
						}

						//Ϊʵ��ת�������Ž������ʽʱ��ת��Ϊָ���ĸ�ʽʱ��
						if (csf_false == convert_from_ns(tmp_value, dest_unit, tmp_value)) {
							return csf_false;
						}

						dest_value = tmp_value;

						return csf_true;
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
					* ��ʾ����csf_attribute���Բ�����
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
					 * ��ʾʱ��ĵ�λ
					 */
					csf_time_unit m_unit = csf_time_unit::csf_time_unit_s;
					/**
					* ��ʾʱ�䵥λ���ƵĶ�Ӧ�б�
					*/
					static const csf_unordered_map<csf_string, csf_time_unit> m_unit_name;
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
					inline void set_unit_name(const csf_unordered_map<csf_string, csf_time_unit>& new_value) {

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
					inline csf_bool convert_to_ns(csf_int64& dest_value, const csf_int64& src_value, const csf_time_unit& src_unit) {

#ifndef CSF_TIME_UNIT_SCALE_GEN
#define CSF_TIME_UNIT_SCALE_GEN(type, scale)				case csf_time_unit_ ## type: {dest_value = src_value * scale;}break;

						switch (src_unit) {
							CSF_TIME_UNIT_SCALE(CSF_TIME_UNIT_SCALE_GEN)

						default:
							return csf_false;
							break;
						}

#undef  CSF_TIME_UNIT_SCALE_GEN
#endif // CSF_TIME_UNIT_SCALE_GEN

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
					inline csf_bool convert_from_ns(csf_int64& dest_value, const csf_time_unit& dest_unit, const csf_int64& src_value) {

#ifndef CSF_TIME_UNIT_SCALE_GEN
#define CSF_TIME_UNIT_SCALE_GEN(type, scale)				case csf_time_unit_ ## type: {dest_value = src_value / scale;}break;

						switch (dest_unit) {
							CSF_TIME_UNIT_SCALE(CSF_TIME_UNIT_SCALE_GEN)

						default:
							return csf_false;
							break;
						}

#undef  CSF_TIME_UNIT_SCALE_GEN
#endif // CSF_TIME_UNIT_SCALE_GEN

						return csf_true;
					}
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_TIME_INCLUDED_)
