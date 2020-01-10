/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_shared_memory.hpp
*
*Version: 1.0
*
*Date: 10-1月-2020 14:50:42
*
*Description: Class(csf_shared_memory)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_shared_memory.hpp"

using csf::core::module::csf_shared_memory;


csf_shared_memory::csf_shared_memory()
	: m_smm(csf_nullptr) {

}



csf_shared_memory::~csf_shared_memory() {

}





/**
 * 功能：
 *    为对象创建一个指定名称和长度的共享内存
 * 返回：
 *    0  ：  表示成功；
 *   非0 ：  表示失败；
 * 
 * @param name    表示共享内存的名称
 * @param size    表示共享内存的空间大小
 */
csf_int32 csf_shared_memory::create(csf_string name, csf_uint32 size) {

	return 0;
}


/**
 * 功能：
 *    销毁共享对象中已经创建好的共享内存
 * 返回：
 *    无
 */
void csf_shared_memory::destroy() {

}