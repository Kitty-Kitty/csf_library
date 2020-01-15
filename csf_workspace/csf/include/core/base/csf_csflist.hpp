/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csflist.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Class(csf_csflist)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFLIST_INCLUDED_)
#define CSF_CSFLIST_INCLUDED_

#include "csf_collector.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf封闭的list类
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:38
			 */
			class csf_csflist : public csf::core::base::csf_collector
			{

			public:
				csf_csflist();
				virtual ~csf_csflist();

			};

		}

	}

}
#endif // !defined(CSF_CSFLIST_INCLUDED_)
