/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_response.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:57
*
*Description: Class(csf_response) 表示请求的处理类型，包含应答的多种信息内容
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_RESPONSE_H_INCLUDED_)
#define CSF_RESPONSE_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace service
		{
			/**
			 * 表示请求的处理类型，包含应答的多种信息内容
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 28-3月-2019 14:56:57
			 */
			class csf_response
			{

			public:
				csf_response();
				virtual ~csf_response();

			};

		}

	}

}
#endif // !defined(CSF_RESPONSE_H_INCLUDED_)
