/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csfqueue.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Class(csf_csfqueue)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFQUEUE_INCLUDED_)
#define CSF_CSFQUEUE_INCLUDED_

#include "csf_collector.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf封装的队列
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:38
			 */
			class csf_csfqueue : public csf::core::base::csf_collector
			{

			public:
				csf_csfqueue();
				virtual ~csf_csfqueue();

			};

		}

	}

}
#endif // !defined(CSF_CSFQUEUE_INCLUDED_)
