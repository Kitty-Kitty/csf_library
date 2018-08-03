/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_csfmap.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 27-6月-2018 17:28:38
*
*Description: Class(csf_csfmap)
*
*Others:
*
*History:
*******************************************************************************/

#if !defined(CSF_CSFMAP_INCLUDED_)
#define CSF_CSFMAP_INCLUDED_

#include "csf_collector.hpp"

namespace csf
{
	namespace core
	{
		namespace base
		{
			/**
			 * 表示csf封装的map类型
			 * @author Administrator
			 * @version 1.0
			 * @created 27-6月-2018 17:28:38
			 */
			class csf_csfmap : public csf::core::base::csf_collector
			{

			public:
				csf_csfmap();
				virtual ~csf_csfmap();

			};

		}

	}

}
#endif // !defined(CSF_CSFMAP_INCLUDED_)
