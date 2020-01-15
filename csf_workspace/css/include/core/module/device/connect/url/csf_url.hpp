/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: f
*
*Author: fz
*
*Version: 1.0
*
*Date: 11-7月-2018 22:10:25
*
*Description: Class(csf_url) url地址信息的基础类信息
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_URL_INCLUDED_)
#define CSF_URL_INCLUDED_

#include "csf_typedef.h"

using namespace csf::core::base;

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * url地址信息的基础类信息
				 * @author f
				 * @version 1.0
				 * @created 11-7月-2018 22:10:25
				 */
				class csf_url
				{

				public:
					/**
					 * 表示url类型
					 * @author f
					 * @version 1.0
					 * @created 11-7月-2018 22:10:25
					 */
					enum csf_url_type
					{
						/**
						 * 表示空地址
						 */
						csf_url_type_none = 0,
						/**
						 * 表示IP地址
						 */
						csf_url_type_ip,
						/**
						 * 表示串口地址
						 */
						csf_url_type_serial
					};

					inline explicit csf_url()
						: m_url("")
						, m_type(csf_url_type_none) {

					}

					virtual ~csf_url() {

					}

					/**
					 * 
					 * @param type    表示连接地址类型
					 */
					inline explicit csf_url(csf_url_type type)
						: m_url("")
						, m_type(type) {

					}
					/**
					 * 表示url地址的类型信息
					 */
					inline csf_url_type get_type() {

						return m_type;
					}
					/**
					 * 表示解析地址函数
					 * 
					 * @param url    表示url地址字符串数据
					 */
					inline virtual csf_int32 parse(csf_string& url) {

						return 0;
					}
					/**
					 * 表示url的完整字符串数据
					 */
					inline csf_string & get_url() {

						return m_url;
					}
					/**
					 * 表示url的完整字符串数据
					 * 
					 * @param newVal
					 */
					inline csf_void set_url(csf_string& newVal) {

						m_url = newVal;
					}
					/**
					 * 表示url的完整字符串数据
					 * 
					 * @param newVal
					 */
					inline csf_void set_url(csf_char* newVal) {

						m_url = newVal;
					}
					/**
					 * 表示解析地址函数
					 * 
					 * @param url    表示url地址字符串数据
					 */
					inline virtual csf_int32 parse(csf_char* url) {

						return 0;
					}

				protected:
					/**
					 * 表示url地址的类型信息
					 * 
					 * @param newVal
					 */
					inline csf_void set_type(csf_url_type newVal) {

						m_type = newVal;
					}

				private:
					/**
					 * 表示url的完整字符串数据
					 */
					csf::core::base::csf_string m_url = "";
					/**
					 * 表示url地址的类型信息
					 */
					csf_url_type m_type = csf_url_type_none;

				};

			}

		}

	}

}
#endif // !defined(CSF_URL_INCLUDED_)
