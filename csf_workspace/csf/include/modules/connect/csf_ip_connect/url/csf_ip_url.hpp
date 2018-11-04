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
*Date: 01-10月-2018 12:54:43
*
*Description: Class(csf_ip_url) 表示网络地址对象。地址格式为：ip:port；例如:192.168.1.10:80
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
			#define csf_ip_url_parametes_size						2		//表示需要提取的参数个数
			/************************************************************************/
			/* 表示ip url 数据默认的缓存大小											*/
			/************************************************************************/
			#define csf_ip_url_buffer_size							32		//表示ip url 数据默认的缓存大小
			/**
			 * @author f
			 * @version 1.0
			 * @created 01-10月-2018 12:54:43
			 */
			class csf_ip_url : public csf::core::module::connect::csf_url
			{

			public:
				csf_ip_url();
				virtual ~csf_ip_url();
				/**
				* 主要功能是：通过url字符串数据设置url对象
				* 返回：无异常表示成功；抛出异常表示错误
				*
				* @param url    表示url字符串数据，地址格式为：xxx.xxx.xxx.xxx；例如:192.168.1.10
				*/
				inline csf_url& operator =(const csf_char* url) {

// 					if (set_url(url)) {
// 						throw url;
// 					}
					set_url(url);

					return *this;
				}
				/**
				* 主要功能是：通过url字符串数据设置url对象
				* 返回：无异常表示成功；抛出异常表示错误
				*
				* @param url    表示url字符串数据，地址格式为：xxx.xxx.xxx.xxx；例如:192.168.1.10
				*/
				inline csf_url& operator =(const csf_string& url) {

// 					if (set_url(url)) {
// 						throw url;
// 					}
					set_url(url);

					return *this;
				}
				/**
				 * 表示IP地址字符串
				 */
				inline const csf_string & get_ip() {

					return m_ip;
				}
				/**
				 * 表示IP地址字符串
				 * 
				 * @param new_value
				 */
				inline csf_bool set_ip(const csf_string& new_value) {

					if (check_ip(new_value)) {
						m_ip = new_value;
						return csf_true;
					}
					return csf_false;
				}
				/**
				 * 获取端口数据
				 */
				inline csf::core::base::csf_ushort get_port() {

					return m_port;
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
				 * 表示解析地址函数
				 * 
				 * @param url    表示url地址字符串数据
				 */
				virtual csf_int32 parse(const csf_string& url);
				/**
				 * 表示IP地址字符串
				 * 
				 * @param new_value
				 */
				inline csf_bool set_ip(const csf_char* new_value) {

					return set_ip(csf_string(new_value));
				}
				/**
				* 主要功能是：表示url的完整字符串数据
				* 返回：0表示成功；非0表示错误
				*
				* @param newVal    表示url字符串数据，地址格式为：xxx.xxx.xxx.xxx；例如:192.168.1.10
				*/
				inline csf_int32 set_url(const csf_char* newVal) {

					if (csf_succeed == parse(newVal)) {
						csf_url::set_url(newVal);
						return csf_succeed;
					}
					
					return csf_failure;
				}
				/**
				* 主要功能是：表示url的完整字符串数据
				* 返回：0表示成功；非0表示错误
				*
				* @param newVal    表示url字符串数据，地址格式为：xxx.xxx.xxx.xxx；例如:192.168.1.10
				*/
				inline csf_int32 set_url(const csf_string& newVal) {

					return set_url((csf_char*)(newVal.c_str()));
				}
				/**
				* 主要功能是：根据ip和端口号设置url信息
				* 返回：0表示成功；非0表示错误
				*
				* @param ip    表示ip字符串数据，地址格式为：xxx.xxx.xxx.xxxxt；例如:192.168.1.10
				* @param port    表示端口数据
				*/
				csf_int32 set_url(const csf_string& ip, const csf_ushort port);
				/**
				* 表示解析地址函数
				*
				* @param url    表示url字符串数据，地址格式为：xxx.xxx.xxx.xxx；例如:192.168.1.10，地址格式为：ip:port；例如:192.168.1.10:80
				*/
				inline virtual csf_int32 csf_ip_url::parse(const csf_char* url) {

					return parse(csf_string(url));
				}
				/**
				* 主要功能是：校验url类型是否是合法
				* 返回：true表示是合法；false表示不合法
				*
				* @param url    表示需要校验的url对象
				*/
				inline static csf_bool is_valid_type(const csf_url& url) {

					if (csf_url::csf_url_type::csf_url_type_ip == ((csf_url&)url).get_type()) {
						return csf_true;
					}
					return csf_false;
				}
			protected:
				/**
				* 主要功能是：对ip地址的格式合法性校验
				* 返回：true表示成功；false表示失败；
				*
				* @param ip    表示网络地址格式
				*/
				csf_bool check_ip(const csf_string& ip);
				/**
				* 主要功能是：对port数值合法性校验
				* 返回：true表示成功；false表示失败；
				*
				* @param port    表示网络端口
				*/
				csf_bool check_port(const csf_string& port);
				/**
				* 主要功能是：对port数值合法性校验
				* 返回：true表示成功；false表示失败；
				*
				* @param port    表示需要被校验的数值
				*/
				inline csf_bool check_port(const csf_ushort port) {
					if (port >= 0 && port <= csf_max_ushort ) {
						return csf_true;
					}
					return csf_false;
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

			};

		}

	}

}
#endif // !defined(CSF_IP_URL_H_INCLUDED_)
