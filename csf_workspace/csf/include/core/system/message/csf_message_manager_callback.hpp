/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_message_manager_callback.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:44
*
*Description: Class(csf_message_manager_callback)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_MESSAGE_MANAGER_CALLBACK_INCLUDED_)
#define CSF_MESSAGE_MANAGER_CALLBACK_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace system
		{
			namespace message
			{
				/**
				 * 表示message_manager的回调函数
				 * @author f
				 * @version 1.0
				 * @created 27-6月-2018 17:28:44
				 */
				class csf_message_manager_callback
				{

				public:
					csf_message_manager_callback();
					virtual ~csf_message_manager_callback();

				};

			}

		}

	}

}
#endif // !defined(CSF_MESSAGE_MANAGER_CALLBACK_INCLUDED_)
