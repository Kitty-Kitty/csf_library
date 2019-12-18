/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_connect_callback.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:37
*
*Description: Class(csf_connect_callback)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CONNECT_CALLBACK_INCLUDED_)
#define CSF_CONNECT_CALLBACK_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace module
		{
			namespace device
			{
				/**
				 * 表示连接的返回函数
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:37
				 */
				class csf_connect_callback
				{

				public:
					csf_connect_callback();
					virtual ~csf_connect_callback();

				};

			}

		}

	}

}
#endif // !defined(CSF_CONNECT_CALLBACK_INCLUDED_)
