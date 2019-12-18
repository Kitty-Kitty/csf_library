/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_mdpipe_manager.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 18:01:01
*
*Description: Class(csf_mdpipe_manager) 表示媒体通道管理器，统一管理各种媒体通道，方便查找
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_MDPIPE_MANAGER_H_INCLUDED_)
#define CSF_MDPIPE_MANAGER_H_INCLUDED_

#include "csf_mdpipe.hpp"
#include "csf_mdmanager_template.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示媒体通道管理器，统一管理各种媒体通道，方便查找
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 18:01:01
		 */
		typedef csf_mdmanager_template<csf_mdpipe>  csf_mdpipe_manager;
	}

}
#endif // !defined(CSF_MDPIPE_MANAGER_H_INCLUDED_)
