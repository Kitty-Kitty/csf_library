/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_message_error.hpp
*
*Version: 1.0
*
*Date: 22-3月-2019 22:38:33
*
*Description: Class(csf_message_error) 用于描述模块通信的错误
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MESSAGE_ERROR_H_INCLUDED_)
#define CSF_MESSAGE_ERROR_H_INCLUDED_

#include "csf_error.hpp"

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * 用于描述模块通信的错误
				 * @author fangzhenmu
				 * @version 1.0
				 * @created 22-3月-2019 22:38:33
				 */
				class csf_message_error : public csf::core::module::csf_error
				{

				public:
					inline explicit csf_message_error() {

					}
					/**
					 * 表示根据错误码（code）和错误描述（description）创建一个csf_message_error。
					 * 
					 * @param code    表示错误码编码
					 * @param description    表示错误描述信息
					 */
					inline explicit csf_message_error(const csf_int32 code, const csf_string& description) {

					}
					/**
					 * 表示根据错误码（code）和错误描述（description）创建一个csf_message_error。
					 * 
					 * @param code    表示错误码编码
					 * @param description    表示错误描述信息
					 */
					inline explicit csf_message_error(const csf_int32 code, const csf_char* description) {

					}
					virtual ~csf_message_error() {

					}
				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_ERROR_H_INCLUDED_)
