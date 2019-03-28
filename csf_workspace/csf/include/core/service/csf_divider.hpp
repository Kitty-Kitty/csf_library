/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: fangzhenmu
*
*File name: csf_divider.hpp
*
*Version: 1.0
*
*Date: 28-3月-2019 14:56:48
*
*Description: Class(csf_divider) 服务请求分配器，用于各种请求的处理分配功能
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_DIVIDER_H_INCLUDED_)
#define CSF_DIVIDER_H_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace service
		{
			/**
			 * 服务请求分配器，用于各种请求的处理分配功能
			 * @author fangzhenmu
			 * @version 1.0
			 * @created 28-3月-2019 14:56:48
			 */
			class csf_divider
			{

			public:
				csf_divider();
				virtual ~csf_divider();

			};

		}

	}

}
#endif // !defined(CSF_DIVIDER_H_INCLUDED_)
