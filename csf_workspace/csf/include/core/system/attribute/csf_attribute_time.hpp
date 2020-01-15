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
*Date: 05-7月-2018 20:55:12
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
				/* 需要提取的参数个数														*/
				/************************************************************************/
				#define csf_attribute_time_parametes_size						2		//表示需要提取的参数个数
				/**
				 * 表示时间格式属性类型。该类型格式为:
				 * 数值+单位。单位包括（ns/us/ms/s/m/h/d）分别表示（纳秒/微秒/毫秒/秒/分钟/小时/天）、单位严格要求小写形式。例如:100s为100秒
				 * @author fz
				 * @version 1.0
				 * @created 05-7月-2018 20:55:12
				 */
								class csf_attribute_time : public csf::core::system::attribute::csf_attribute_int64
				{

				public:
					/**
					* 表示时间格式的单位定义
					* @author Administrator
					* @version 1.0
					* @updated 08-7月-2018 15:17:20
					*/
					enum csf_time_unit
					{
						/**
						* 表示<font color="#008000">未定义的单位</font>
						*/
						csf_time_unit_none = 0x00000000,
						/**
						* 表示纳秒单位
						*/
						csf_time_unit_ns,
						/**
						* 表示<font color="#008000">微秒</font>单位
						*/
						csf_time_unit_us,
						/**
						* 表示<font color="#008000">毫秒</font>单位
						*/
						csf_time_unit_ms,
						/**
						* 表示<font color="#008000">秒</font>单位
						*/
						csf_time_unit_s,
						/**
						* 表示<font color="#008000">分钟</font>单位
						*/
						csf_time_unit_m,
						/**
						* 表示<font color="#008000">小时</font>单位
						*/
						csf_time_unit_h,
						/**
						* 表示<font color="#008000">天</font>单位
						*/
						csf_time_unit_d
					};

					//定义各种时间单位刻度的比例值
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
					* 根据类型创建一个对象
					*
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_time(const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(csf_attribute_type_time, boundary, ex)
						, m_unit(csf_time_unit::csf_time_unit_s) {

					}
					/**
					* 根据类型创建一个对象
					*
					* @param unit    表示默认的时间单位
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_time(const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param unit    表示默认的时间单位
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_time(const csf_string& name
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_time(name.c_str(), unit, boundary, ex) {

					}
					/**
					* 根据名称和类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param unit    表示默认的时间单位
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_time(const csf_char* name
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(name, csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* 根据属性路径、类型创建一个对象
					*
					* @param items    表示该属性所对应的配置文件节点位置
					* @param unit    表示默认的时间单位
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_time(const csf_list<csf_string> items
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_int64(items, csf_attribute_type_time, boundary, ex)
						, m_unit(unit) {

					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					* @param unit    表示默认的时间单位
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
					*/
					inline explicit csf_attribute_time(const csf_string& name
						, const csf_list<csf_string> items
						, const csf_time_unit unit = csf_time_unit_s
						, const csf::core::system::attribute::csf_attribute_boundary& boundary = csf_attribute_boundary::get_null()
						, const csf::core::system::attribute::csf_attribute_exception& ex = csf_attribute_exception::get_null())

						: csf_attribute_time(name.c_str(), items, unit, boundary, ex) {

					}
					/**
					* 根据名称、属性路径、类型创建一个对象
					*
					* @param name    表示属性的名称
					* @param items    表示该属性所对应的配置文件节点位置
					* @param unit    表示默认的时间单位
					* @param boundary    表示数字属性的范围边界核验信息
					* @param ex    表示属性异常处理对象
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
					 * 表示时间的单位
					 */
					inline csf_time_unit get_unit() {

						return m_unit;
					}
					/**
					 * 表示时间的单位
					 *
					 * @param new_value
					 */
					inline void set_unit(const csf_time_unit new_value) {

						m_unit = new_value;
					}
					/**
					* 表示时间单位名称的对应列表
					*/
					inline const csf_unordered_map<csf_string, csf_time_unit>& get_unit_name() {

						return m_unit_name;
					}
					/**
					* 从内容中解析需要的参数。
					* 返回：ture表示解析成功；false表示解析失败。
					*
					* @param content    表示需要解析的内容信息
					*/
					csf_bool parse_parametes(const csf_string& content);
					/**
					* 从内容中解析需要的参数。
					* 返回：ture表示解析成功；false表示解析失败。
					*
					* @param content    表示需要解析的内容信息
					*/
					inline csf_bool parse_parametes(const csf_char* content) {

						if (!content || csf_strlen(content) <= 0) {
							return csf_false;
						}

						return parse_parametes(csf_string(content));
					}

					/**
					* 表示将字符串时间单位转换为类型数值
					*
					* @param unit    表示需要被转换的单位字符串
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
					* 表示将字符串时间单位转换为类型数值
					*
					* @param unit    表示需要被转换的单位字符串
					*/
					inline csf_time_unit convert(const csf_char* unit) {

						if (!unit || csf_strlen(unit)) {
							return csf_time_unit::csf_time_unit_none;
						}

						return  convert(csf_string(unit));
					}
					/**
					* 表示将类型数值转换为字符串时间单位
					*
					* @param unit    表示需要被转换的单位数值
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
					* 表示将时间数值转换为指定格式的时间数值。
					* 返回：true表示转换成功；false表示转换失败；
					*
					* @param dest_value    表示转换后的目标单位数值
					* @param dest_unit    表示转换后的目标数值单位
					* @param src_value    表示需要被转换的源单位数值
					* @param src_unit    表示源数值单位
					*/
					inline csf_bool convert(csf_int64& dest_value, const csf_time_unit& dest_unit,
						const csf_int64& src_value, const csf_time_unit& src_unit) {

						csf_int64						tmp_value = 0;


						//为实现转换，先将源格式时间转换为纳秒格式
						if (csf_false == convert_to_ns(tmp_value, src_value, src_unit)) {
							return csf_false;
						}

						//为实现转换，接着将纳秒格式时间转换为指定的格式时间
						if (csf_false == convert_from_ns(tmp_value, dest_unit, tmp_value)) {
							return csf_false;
						}

						dest_value = tmp_value;

						return csf_true;
					}
					/**
					* 函数功能是将csf_attribute内容信息格式化
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
					* 表示处理csf_attribute属性操作。
					* 返回：true表示失败；false表示成功。
					*
					* @param configure_manager    表示保存配置管理器对象
					* @param alias    表示当前属性别名，如果属性名称为空则则使用该别名。
					*/
					virtual csf_bool process_number(const csf_configure_manager& configure_manager, const csf_string& alias);
					/**
					* 表示该种格式数据的说明
					*/
					inline const csf_string& get_usage() {

						return m_usage;
					}
				private:
					/**
					 * 表示时间的单位
					 */
					csf_time_unit m_unit = csf_time_unit::csf_time_unit_s;
					/**
					* 表示时间单位名称的对应列表
					*/
					static const csf_unordered_map<csf_string, csf_time_unit> m_unit_name;
					/**
					* 表示该种格式数据的说明
					*/
					static const csf_string m_usage;
					/**
					* 获取数值和单位相关内容。
					* 返回：true表示处理成功；false表示处理失败。
					*
					* @param val    表示需要处理的数值内容
					* @param unit    表示该数值的单位字符
					*/
					csf_bool get_parametes(const csf_string& val, const csf_string& unit);

#if 0
					/**
					* 表示时间单位名称的对应列表
					*
					* @param new_value    表示时间单位名称的对应列表
					*/
					inline void set_unit_name(const csf_unordered_map<csf_string, csf_time_unit>& new_value) {

						m_unit_name = new_value;
					}
#endif
					/**
					* 表示将时间数值转换为纳秒格式的时间数值。
					* 返回：true表示转换成功；false表示转换失败；
					*
					* @param dest_value    表示转换后的目标单位数值，单位为纳秒(ns)
					* @param src_value    表示需要被转换的源单位数值
					* @param src_unit    表示源数值单位
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
					* 表示将纳秒时间数值转换为指定格式的时间数值。
					* 返回：true表示转换成功；false表示转换失败；
					*
					* @param dest_value    表示转换后的目标单位数值
					* @param dest_unit    表示转换后的目标数值单位
					* @param src_value    表示需要被转换的源单位数值
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
