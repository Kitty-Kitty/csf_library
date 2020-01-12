/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_vm_option.hpp
*
*Version: 1.0
*
*Date: 12-1月-2020 11:18:35
*
*Description: Class(csf_vm_option)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_vm_option.hpp"

using csf::core::module::csf_vm_option;


/**
 *
 * @param vm    表示当前option对应的vm对象
 */
csf_vm_option::csf_vm_option(csf_vm& vm)
	: csf_app_option(vm)
	, m_vm(vm) {

}


csf_vm_option::~csf_vm_option() {

}


csf_vm& csf_vm_option::get_vm() {

	return m_vm;
}