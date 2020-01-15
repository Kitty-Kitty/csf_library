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
*Date: 04-7月-2018 22:13:15
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
				/* 限制字符缓存的默认长度                                                 */
				/************************************************************************/
				#define csf_boundary_string_default_length				32				//限制字符缓存的默认长度

				/************************************************************************/
				/* 需要提取的参数个数														*/
				/************************************************************************/
				#define csf_boundary_parametes_size						4				//表示需要提取的参数个数

				/**
				* 表示属性配置的限制，各种不同的属性配置有各自的不同格式的限制。
				* @author fz
				* @version 1.0
				* @created 04-7月-2018 22:55:39
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
					* 表示根据限制字符串创建校验对象。
					* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
					*
					* @param boundary    其中字符串描述的限制表示。
					* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
					*/
					inline explicit csf_attribute_boundary(const csf_char* boundary)
						: m_lower_bound(csf_min_long)
						, m_upper_bound(csf_max_long) 
						, m_boundary(boundary) {

					}
					/**
					* 表示根据限制字符串创建校验对象。
					* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
					*
					* @param boundary    其中字符串描述的限制表示。
					* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
					*
					*/
					inline explicit csf_attribute_boundary(const csf_string& boundary) :
						csf_attribute_boundary(boundary.c_str()) {

					}
					/**
					* 表示处理核验函数。
					* 返回：true表示核验成功；false表示核验错误。
					*
					* @param val    表示当前的核验数值
					*/
					inline csf_bool process(const csf_int64 val) {

						if (csf_nullptr == get_function()) {
							return csf_false;
						}

						return process(val, get_lower_bound(), get_upper_bound(), get_function());
					}
					/**
					* 表示阈值的最小值。
					*/
					inline csf_int64 get_lower_bound() {

						return m_lower_bound;
					}
					/**
					* 表示阈值的最小值。
					*
					* @param newVal
					*/
					inline csf_void set_lower_bound(csf_int64 newVal) {

						m_lower_bound = newVal;
					}
					/**
					* 表示阈值的最大值。
					*/
					inline csf_int64 get_upper_bound() {

						return m_upper_bound;
					}
					/**
					* 表示阈值的最大值。
					*
					* @param newVal
					*/
					inline csf_void set_upper_bound(csf_int64 newVal) {

						m_upper_bound = newVal;
					}
					
					/**
					* 表示阈值描述字符串内容
					*/
					inline csf_string& get_boundary() {

						return m_boundary;
					}
					/**
					* 表示阈值描述字符串内容
					*
					* @param newVal
					*/
					inline void set_boundary(const csf_string& newVal) {

						m_boundary = newVal;
					}
					/**
					* 表示阈值描述字符串内容
					*
					* @param newVal
					*/
					inline void set_boundary(const csf_char* newVal) {

						m_boundary = newVal;
					}
					/**
					* 表示boundary使用方式的描述信息。
					*/
					inline const csf_string& get_usage() {

						return m_usage;
					}
					/**
					* 表示判断是否为空。
					* 返回：true表示为空；false表示不为空。
					*/
					inline virtual csf_bool is_null() {

						if (get_boundary().empty()) {
							return csf_true;
						}
						return csf_false;
					}
					/**
					* 表示判断是否不为空。
					* 返回：true表示不为空；false表示为空。
					*/
					inline virtual csf_bool not_null() {

						return !is_null();
					}
					/**
					* 表示初始化边界核验内容
					*/
					inline csf_bool init() {

						return parse(get_boundary());
					}
					protected:
						/**
						* 表示根据限制字符串创建校验对象。
						* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
						*
						* @param boundary    其中字符串描述的限制表示。
						* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
						*/
						csf_bool parse(const csf_char* boundary);
						/**
						* 表示根据限制字符串创建校验对象。
						* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
						*
						* @param boundary    其中字符串描述的限制表示。
						* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
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
					* 表示阈值的最小值。
					*/
					csf_int64 m_lower_bound = csf_min_long;
					/**
					* 表示阈值的最大值。
					*/
					csf_int64 m_upper_bound = csf_max_long;
					/**
					* 表示核验处理函数对应表
					*/
					static const std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>> m_functions;
					/**
					* 表示阈值描述字符串内容,例如:"(0, 100]"
					*/
					csf_string m_boundary = "";
					/**
					* 表示boundary使用方式的描述信息。
					*/
					static const csf_string m_usage;
					/**
					* 表示当前核验处理函数句柄
					*/
					std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)> m_function = csf_nullptr;

					/**
					* 表示处理核验函数。
					* 返回：true表示核验成功；false表示核验错误。
					*
					* @param val    表示当前的核验数值
					* @param lower    表示阈值的最小值
					* @param upper    表示阈值的最大值
					* @param func    表示核验处理函数
					*/
					inline csf_bool process(const csf_int64 val, const csf_int64 lower, const csf_int64 upper, 
						const std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)> func) {

						if (csf_nullptr == func) {
							return csf_false;
						}

						return func(val, lower, upper);
					}
					/**
					* 表示核验处理函数对应表
					*/
					inline const std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>>& get_functions() {

						return m_functions;
					}
#if 0
					/**
					* 表示核验处理函数对应表
					*
					* @param newVal
					*/
					inline csf_void set_functions(std::map<std::string, std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>>& newVal) {

						m_functions = newVal;
					}
#endif
					/**
					* 表示当前核验处理函数句柄
					*/
					inline std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>& get_function() {

						return m_function;
					}
					/**
					* 表示当前核验处理函数句柄
					*
					* @param newVal
					*/
					inline csf_void set_function(std::function<csf_bool(const csf_int64, const csf_int64, const csf_int64)>& newVal) {

						m_function = newVal;
					}
					/**
					* 表示根据限制字符串创建校验对象。
					* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
					* 返回：true表示成功；false表示失败。
					*
					* @param boundary    其中字符串描述的限制表示。
					* 其中格式采用数字区间格式，例如:(-n, 100), [0, 100]。其中“(”表示不等于边界；“[”表示等于边界操作。
					*
					*/
					csf_bool parse_parametes(const csf_string boundary);
					
					/**
					* 根据传入的阈值边界数据字符串提取数据。其中-n转化为int64的最小值；+n转化为int64的最大值。
					* 返回：true表示成功；false表示失败。
					*
					* @param lower	阈值的最小值
					* @param upper	阈值的最大值
					*/
					csf_bool get_parametes(const csf_string& lower, const csf_string& upper);
					/**
					* 根据传入的字符串匹配操作函数。
					* 返回：true表示成功；false表示失败。
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
					* 表示boundary使用方式的描述信息。
					*
					* @param newVal
					*/
					inline void set_usage(csf_string& newVal) {

						m_usage = newVal;
					}
#endif
				};

			}

		}

	}

}
#endif // !defined(CSF_ATTRIBUTE_BOUNDARY_INCLUDED_)
