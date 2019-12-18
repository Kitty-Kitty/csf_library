/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mdslot.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 16:44:05
*
*Description: Class(csf_mdslot)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_uuid.hpp"
#include "csf_mdslot.hpp"

using ec::core::csf_mdslot;


csf_mdslot::csf_mdslot()
	: m_guid{ 0, }
	, m_name{ 0, } {

	//每一个通道都有一个唯一的标识id
	set_guid();
}

csf_mdslot::~csf_mdslot() {

}

/**
* 表示通道的uuid，用于唯一标识一个通道
*/
void csf_mdslot::set_guid() {

	csf_memset(m_guid, 0, csf_sizeof(m_guid));
	csf::core::utils::csf_uuid::make32(m_guid, csf_sizeof(m_guid));
}
