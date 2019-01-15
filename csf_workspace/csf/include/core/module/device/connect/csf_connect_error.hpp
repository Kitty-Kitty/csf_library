/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_connect_error.hpp
*
*Version: 1.0
*
*Date: 02-10月-2018 18:25:40
*
*Description: Class(csf_connect_error) 用于描述网络通信错误
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_CONNECT_ERROR_H_INCLUDED_)
#define CSF_CONNECT_ERROR_H_INCLUDED_

#include "csf_error.hpp"
#include "csf_logger.hpp"

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace connect
			{
				/**
				 * 用于描述网络通信错误
				 * @author f
				 * @version 1.0
				 * @created 02-10月-2018 18:25:40
				 */
				class csf_connect_error : public csf::core::module::csf_error
				{
				public:

					/**
					* 表示连接的错误编码
					* @author f
					* @version 1.0
					* @updated 04-11月-2018 20:11:47
					*/
					typedef enum csf_connect_code_enum
					{
						/**
						* 表示未知的错误编码
						*/
						csf_connect_code_none = 0x00000000,
						/**
						* 表示超时错误编码
						*/
						csf_connect_code_timeout = 0x00000010,
						/**
						* 表示打开监听地址错误编码
						*/
						csf_connect_code_listen = 0x00000020,
						/**
						* 表示传入非法参数，参数为空错误
						*/
						csf_connect_code_invalid_parametes = 0x00000040,
						/**
						* 表示存放数据的空间不足
						*/
						csf_connect_code_not_enough_space = 0x00000080,
						/**
						* 表示进行的处理错误
						*/
						csf_connect_code_operation_error = 0x00000100
					} csf_connect_code;

				public:
					inline explicit csf_connect_error() {

					}
					virtual ~csf_connect_error() {

					}
					/**
					* 表示根据错误码（code）和错误描述（description）创建一个csf_error。
					*
					* @param code    表示错误码编码
					* @param description    表示错误描述信息
					*/
					inline explicit csf_connect_error(const csf_int32 code, const csf_string& description)
						: csf_error(code, description) {

					}
					/**
					* 表示根据错误码（code）和错误描述（description）创建一个csf_error。
					*
					* @param code    表示错误码编码
					* @param description    表示错误描述信息
					*/
					inline explicit csf_connect_error(const csf_int32 code, const csf_char* description)
						: csf_error(code, description) {

					}
				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_ERROR_H_INCLUDED_)
