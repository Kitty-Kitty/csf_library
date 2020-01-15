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

using csf::modules::vm::csf_shared_memory;


csf_shared_memory::csf_shared_memory()
	: m_smm(csf_nullptr)
	, m_name("") {
	destroy();
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

	if (name.empty()) {
		return csf_failure;
	}

	//先释放原来的共享内存资源
	//destroy();
	shared_memory_object::remove(name.c_str());

	//创建一个共享内存对象
	set_smm(new managed_shared_memory(create_only, name.c_str(), size));
	//set_smm(new managed_shared_memory(create_only, name.c_str(), 1024 * 1024));
	if (csf_nullptr == get_smm()) {
		return csf_failure;
	}
	else {
		set_name(name);
	}

	return 0;
}


/**
 * 功能：
 *    销毁共享对象中已经创建好的共享内存
 * 返回：
 *    无
 */
void csf_shared_memory::destroy() {
	if (get_smm()) {
		shared_memory_object::remove(get_name().c_str());
		set_smm(csf_nullptr);
	}
}