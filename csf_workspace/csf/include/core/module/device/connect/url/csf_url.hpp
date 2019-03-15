/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_url.hpp
*
*Version: 1.0
*
*Date: 01-10月-2018 12:54:56
*
*Description: Class(csf_url) url地址信息的基础类信息
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_URL_H_INCLUDED_)
#define CSF_URL_H_INCLUDED_

#include "csf_base_include.h"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * url地址信息的基础类信息
				 * @author f
				 * @version 1.0
				 * @created 01-10月-2018 12:54:56
				 */
				class csf_url
				{

				public:
					/**
					 * 表示url类型
					 * @author f
					 * @version 1.0
					 * @created 01-10月-2018 12:54:56
					 */
					typedef enum csf_url_type_enum
					{
						/**
						 * 表示空地址
						 */
						csf_url_type_none = 0x00000000,
						/**
						 * 表示IP地址
						 */
						csf_url_type_ip = 0x00010000,
						/**
						 * 表示串口地址
						 */
						csf_url_type_serial = 0x00020000
					} csf_url_type;


					csf_url();
					virtual ~csf_url();

					/**
					 * 
					 * @param type    表示连接地址类型
					 */
					inline explicit csf_url(const csf::core::module::connect::csf_url::csf_url_type type)
						: m_type(type)
						, m_url("") {

					}
					/**
					* 主要功能是：通过url字符串数据设置url对象
					* 返回：无异常表示成功；抛出异常表示错误
					*
					* @param url    表示url字符串数据
					*/
					inline virtual csf_url& operator =(const csf_string& url) {

						return  *this;
					}
					/**
					* 主要功能是：通过url字符串数据设置url对象
					* 返回：无异常表示成功；抛出异常表示错误
					*
					* @param url    表示url字符串数据
					*/
					inline virtual csf_url& operator =(const csf_char* url) {

						set_url(url);

						return  *this;
					}
					/**
					 * 表示url地址的类型信息
					 */
					inline const csf::core::module::connect::csf_url::csf_url_type get_type() const {

						return m_type;
					}
					
					/**
					 * 表示url的完整字符串数据
					 */
					inline const csf_string & get_url() const {

						return m_url;
					}
					/**
					 * 表示url的完整字符串数据
					 * 
					 * @param new_value
					 */
					inline csf_int32 set_url(const csf_string& new_value) {

						m_url = new_value;

						return csf_succeed;
					}
					/**
					 * 表示url的完整字符串数据
					 * 
					 * @param new_value
					 */
					inline csf_int32 set_url(const csf_char* new_value) {

						m_url = new_value;

						return csf_succeed;
					}
					/**
					* 表示解析地址函数
					*
					* @param url    表示url地址字符串数据
					*/
					inline virtual csf_int32 parse(const csf_string& url) {

						set_url(url);

						return csf_succeed;
					}
					/**
					 * 表示解析地址函数
					 * 
					 * @param url    表示url地址字符串数据
					 */
					inline virtual csf_int32 parse(const csf_char* url) {

						set_url(url);

						return csf_succeed;
					}
					/**
					* 主要功能：
					*    判断url地址是否合法
					* 返回：
					*    true ：表示合法
					*    false：表示不合法
					*/
					inline virtual csf_bool is_valid() {

						if (csf_url_type_none != get_type()
							&& !get_url().empty()) {
							return csf_true;
						}
						return csf_false;
					}
				protected:
					/**
					 * 表示url地址的类型信息
					 * 
					 * @param new_value
					 */
					inline csf_void set_type(const csf::core::module::connect::csf_url::csf_url_type new_value) {

						m_type = new_value;
					}

				private:
					/**
					 * 表示url的完整字符串数据
					 */
					csf::core::base::csf_string m_url = "";
					/**
					 * 表示url地址的类型信息
					 */
					csf::core::module::connect::csf_url::csf_url_type m_type = csf_url_type_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_URL_H_INCLUDED_)
