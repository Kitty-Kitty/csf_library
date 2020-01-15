/*******************************************************************************
*
*Copyright: armuxinxian@aliyun.com
*
*File name: csf_module.hpp
*
*Author: fz
*
*Version: 1.0
*
*Date: 01-7月-2018 18:27:20
*
*Description: Class(csf_module)
*
*Others:
*
*History:
*******************************************************************************/

#include "csf_module.hpp"
#include "csf_uuid.hpp"

using csf::core::module::csf_module;

/**
* 表示模块的uuid，用于唯一标识一个模块
*
*/
void csf_module::set_guid() {

	csf_memset(m_guid, 0, csf_sizeof(m_guid));
	csf::core::utils::csf_uuid::make32(m_guid, csf_sizeof(m_guid));
}