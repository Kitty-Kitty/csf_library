/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*Author: f
*
*File name: csf_hichannel_manager.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:14
*
*Description: Class(csf_hichannel_manager) 表示海思媒体通道管理器
*
*Others:
*
*History:
*
*******************************************************************************/

#if !defined(CSF_HICHANNEL_MANAGER_H_INCLUDED_)
#define CSF_HICHANNEL_MANAGER_H_INCLUDED_

#include "csf_hichannel.hpp"
#include "csf_mdmanager_template.hpp"

namespace ec
{
	namespace core
	{
		/**
		 * 表示海思媒体通道管理器
		 * @author f
		 * @version 1.0
		 * @created 02-12月-2019 18:38:27
		 */
		typedef csf_mdmanager_template<csf_hichannel>  csf_hichannel_manager;

	}

}
#endif // !defined(CSF_HICHANNEL_MANAGER_H_INCLUDED_)
