/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_queue.hpp
*
*Author: f
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:47
*
*Description: Class(csf_queue)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_QUEUE_INCLUDED_)
#define CSF_QUEUE_INCLUDED_

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf使用的队列
			 * @author f
			 * @version 1.0
			 * @created 27-6月-2018 17:28:47
			 */
			class csf_queue
			{

			public:
				csf_queue();
				virtual ~csf_queue();

			};

		}

	}

}
#endif // !defined(CSF_QUEUE_INCLUDED_)
