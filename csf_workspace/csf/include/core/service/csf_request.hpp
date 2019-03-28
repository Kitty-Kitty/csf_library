/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_request.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:57
*
*Description: Class(csf_request) 服务器的请求信息体，主要保存当前请求的连接信息，数据信息等等
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_REQUEST_H_INCLUDED_)
#define CSF_REQUEST_H_INCLUDED_

#include "csf_connect_callback.hpp"

using namespace csf::core::module::connect;

namespace csf
{
	namespace core
	{
		namespace service
		{
			/**
			 * 服务器的请求信息体，主要保存当前请求的连接信息，数据信息等等
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 28-3月-2019 14:56:57
			 */
			class csf_request
			{

			public:
				csf_request();
				virtual ~csf_request();

				/**
				 * 表示当前请求的连接信息
				 */
				inline csf_connect_ptr& get_connect() {

					return m_connect;
				}
				/**
				 * 表示当前请求的连接信息
				 * 
				 * @param newVal
				 */
				inline void set_connect(csf_connect_ptr& newVal) {

					m_connect = newVal;
				}

			private:
				/**
				 * 表示当前请求的连接信息
				 */
				csf_connect_ptr m_connect;

			};

		}

	}

}
#endif // !defined(CSF_REQUEST_H_INCLUDED_)
