/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_ip_url.hpp
*
*Version: 1.0
*
*Date: 13-3月-2019 16:56:49
*
*Description: Class(csf_ip_url) 表示网络地址对象。地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_IP_URL_H_INCLUDED_)
#define CSF_IP_URL_H_INCLUDED_

#include "csf_url.hpp"

namespace csf
{
	namespace modules
	{
		namespace connect
		{
			/************************************************************************/
			/* 需要提取的参数个数														*/
			/************************************************************************/
			#define csf_ip_url_parametes_size						2		
			/************************************************************************/
			/* 表示ip url 数据默认的缓存大小											*/
			/************************************************************************/
			#define csf_ip_url_buffer_size							64		

			/**
			 * 表示网络地址对象。地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:
			 * 80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
			 * @author f
			 * @version 1.0
			 * @updated 13-3月-2019 17:33:46
			 */
			class csf_ip_url : public csf::core::module::connect::csf_url
			{

			public:
				/**
				 * 表示ip地址的类型，主要包括ipv4和ipv6两种格式
				 * @author fangzhenmu
				 * @version 1.0
				 * @updated 13-3月-2019 17:33:46
				 */
				typedef enum csf_ip_type_enum
				{
					/**
					 * 表示ipv4版本的地址格式
					 */
					csf_ip_type_v4 = 0x00000001,
					/**
					 * 表示ipv6版本的地址格式
					 */
					csf_ip_type_v6 = 0x00000002
				} csf_ip_type;

				/**
				* 表示ip字符串的格式。地址格式主要有 [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:80。
				* @author fangzhenmu
				* @version 1.0
				* @updated 16-3月-2019 16:57:24
				*/
				typedef enum csf_ip_string_format_enum
				{
					/**
					* 表示ip地址字符串格式错误
					*/
					csf_ip_string_format_error = 0x00,

					/**
					* 表示url地址字符串格式为单一简单格式（ip:port），例如：192.168.1.10:
					* 80。该种格式主要满足ipv4和端口使用，无法兼容ipv6和端口的描述。
					*/
					csf_ip_string_format_single = 0x01,

					/**
					* 表示url地址字符串格式为兼容格式（[ip]:port），例如：[192.168.1.10]:80。该种格式可以兼容ipv4和ipv6的表述
					*/
					csf_ip_string_format_compatible = 0x02
				} csf_ip_string_format;

				inline explicit csf_ip_url()
					: csf_url(csf_url::csf_url_type::csf_url_type_ip)
					, m_ip("")
					, m_port(0)
					, m_type(csf_ip_type::csf_ip_type_v4) {

				}
				/**
				*
				* @param type    表示ip地址的类型，主要分ipv4和ipv6两种
				*/
				/**
				*
				* @param type    表示ip地址的类型，主要分ipv4和ipv6两种
				*/
				inline explicit csf_ip_url(const csf_ip_type type)
					: csf_url(csf_url::csf_url_type::csf_url_type_ip)
					, m_ip("")
					, m_port(0)
					, m_type(type) {

				}
				virtual ~csf_ip_url() {

				}
				/**
				 * 表示IP地址字符串
				 */
				inline csf_string & get_ip() {

					return m_ip;
				}
				/**
				 * 获取端口数据
				 */
				inline csf::core::base::csf_ushort get_port() {

					return m_port;
				}
				/**
				 * 功能：
				 *    表示解析地址函数。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:
				 * 80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 *
				 * 返回：
				 *    0  ：表示成功
				 *    非0：表示错误
				 *
				 * @param url    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				virtual csf_int32 parse(const csf_string& url);
				/**
				 * 功能：
				 *    表示解析地址函数。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:
				 * 80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 *
				 * 返回：
				 *    0  ：表示成功
				 *    非0：表示错误
				 *
				 * @param url    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				inline virtual csf_int32 parse(const csf_char* url) {

					return parse(csf_string(url));
				}
				/**
				 * 主要功能是：表示url的完整字符串数据
				 * 返回：0表示成功；非0表示错误
				 *
				 * @param new_value    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				inline csf_int32 set_url(const csf_char* new_value) {

					if (csf_succeed == parse(new_value)) {

						csf_url::set_url(new_value);
						return csf_succeed;
					}

					return csf_failure;
				}
				/**
				 * 主要功能是：表示url的完整字符串数据
				 * 返回：0表示成功；非0表示错误
				 *
				 * @param new_value    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				inline csf_int32 set_url(const csf_string& new_value) {

					return set_url((csf_char*)(new_value.c_str()));
				}

				/**
				 * 主要功能：
				 *    判断url地址是否合法
				 * 返回：
				 *    true ：表示合法
				 *    false：表示不合法
				 */
				inline virtual csf_bool is_valid() {

					//判断是否合法，如果csf_url都非法则直接返回失败
					if (!csf_url::is_valid()) {
						return csf_false;
					}

					//判断ip url的类型合法性
					if (!is_valid_type(*this)) {
						return csf_false;
					}

					//判断数值和端口的合法性
					if (!check_ip(get_ip()) || !check_port(get_port())) {
						return csf_false;
					}

					return csf_true;
				}
				/**
				 * 主要功能是：
				 *    通过url字符串数据设置url对象。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.
				 * 1.10:80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 *
				 * 返回：
				 *    无异常表示成功；
				 *    抛出异常表示错误
				 *
				 * @param url    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				inline virtual csf_url& operator =(const csf_char* url) {

					set_url(url);

					return *this;
				}
				/**
				 * 主要功能是：
				 *    通过url字符串数据设置url对象。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.
				 * 1.10:80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 *
				 * 返回：
				 *    无异常表示成功；
				 *    抛出异常表示错误
				 *
				 * @param url    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				 * 80和192.168.1.10:80
				 */
				inline virtual csf_url& operator =(const csf_string& url) {

					set_url(url);

					return *this;
				}
				/**
				 * 功能：
				 *    校验url类型是否是合法。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.10:
				 * 80。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 *
				 * 返回：
				 *    true表示是合法；
				 *    false表示不合法
				 *
				 * @param url    表示需要校验的url对象
				 */
				inline static csf_bool is_valid_type(const csf_url& url) {

					if (csf_url::csf_url_type::csf_url_type_ip
						== ((csf_url&)url).csf_url::get_type()) {

						return csf_true;
					}
					return csf_false;
				}
				/**
				* 功能：
				*    表示是否为ipv4,如果是返回true，如果不是则返回false。
				* 返回：
				*    true：表示是；
				*    false：表示不是
				*/
				inline csf_bool is_ipv4() {
					if (csf_ip_type_v4 == csf_ip_url::get_type()) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				* 功能：
				*    表示是否为ipv6,如果是返回true，如果不是则返回false。
				* 返回：
				*    true：表示是；
				*    false：表示不是
				*/
				inline csf_bool is_ipv6() {
					if (csf_ip_type_v6 == csf_ip_url::get_type()) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				 * 主要功能是：根据ip和端口号设置url信息
				 * 返回：0表示成功；非0表示错误
				 *
				 * @param ip    表示ip字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.
				 * 168.1.10:80
				 * @param port    表示端口数据
				 */
				csf_int32 set_url(const csf_string& ip, const csf_ushort port);
			protected:
				/**
				* 表示IP地址字符串
				*
				* @param new_value    表示url字符串数据，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:
				* 80和192.168.1.10:80
				*/
				inline csf_void set_ip(const csf_string& new_value) {

					m_ip = new_value;
				}
				/**
				* 设置端口数据
				*
				* @param new_value
				*/
				inline void set_port(const csf::core::base::csf_ushort new_value) {

					m_port = new_value;
				}
				/**
				 * 功能：
				 *    对ip地址的格式合法性校验。地址格式为：1、[ip]:port；2、ip:port两种；例如:[192.168.1.10]:80和192.168.1.
				 * 10。推荐使用1格式，可以兼容ipv6格式的ip地址，更适合未来的url描述需求。
				 *
				 * 返回：
				 *    true表示成功；
				 *    false表示失败；
				 *
				 * @param ip    表示网络地址格式，地址格式为：1. [ip]:port; 2.ip:port两种；例如:[192.168.1.10]:80和192.
				 * 168.1.10:80
				 */
				virtual csf_bool check_ip(const csf_string& ip);
				/**
				 * 功能：
				 *    对port数值合法性校验
				 * 返回：
				 *    true表示成功；
				 *    false表示失败；
				 *
				 * @param port    表示需要被校验的数值
				 */
				csf_bool check_port(const csf_string& port);
				/**
				 * 主要功能是：对port数值合法性校验
				 * 返回：true表示成功；false表示失败；
				 *
				 * @param port    表示需要被校验的数值
				 */
				inline csf_bool check_port(const csf_ushort port) {

					if (port >= 0 && port <= csf_max_ushort) {
						return csf_true;
					}
					return csf_false;
				}
				/**
				 * 表示ip地址的类型描述信息，默认为：csf_ip_type_v4
				 */
				inline csf_ip_type get_type() {

					return m_type;
				}
				/**
				 * 表示ip地址的类型描述信息，默认为：csf_ip_type_v4
				 *
				 * @param new_value
				 */
				inline void set_type(csf_ip_type new_value) {

					m_type = new_value;
				}
				/**
				* 功能：
				*    清空url对象中的数据
				* 返回：
				*    无
				*/
				inline virtual void clear() {
					csf_url::clear();
					m_ip = "";
					m_port = 0;
					m_type = csf_ip_type_v4;
				}
			private:
				/**
				* 表示ip地址的格式化正则表达式
				*/
				inline const csf_map<csf_ip_string_format, csf_string>& get_format_regex() {

					return m_format_regex;
				}
				/**
				* 表示ip地址类型适配器列表，用于识别各种ip地址
				*/
				inline const csf_vector<csf_ip_url*>& get_adapter() {

					return m_adapter;
				}
			private:
				/**
				 * 表示IP地址字符串
				 */
				csf::core::base::csf_string m_ip = "";
				/**
				 * 表示网络地址的端口数据
				 */
				csf::core::base::csf_ushort m_port = 0;
				/**
				 * 表示ip地址的类型描述信息，默认为：csf_ip_type_v4
				 */
				csf_ip_type m_type = csf_ip_type_v4;
				/**
				* 表示ip地址的格式化正则表达式
				*/
				static const csf_map<csf_ip_string_format, csf_string> m_format_regex;
				/**
				* 表示ip地址类型适配器列表，用于识别各种ip地址
				*/
				static const csf_vector<csf_ip_url*> m_adapter;
			};

		}

	}

}
#endif // !defined(CSF_IP_URL_H_INCLUDED_)
