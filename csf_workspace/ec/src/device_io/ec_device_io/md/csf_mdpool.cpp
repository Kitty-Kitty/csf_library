/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mdpool.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 12:20:35
*
*Description: Class(csf_mdpool)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_mdpool.hpp"

using ec::core::csf_mdpool;
using ec::core::csf_mdobject;


/**
 * 功能：创建一个资源对象
 * 返回：一个资源对象
 */
csf_mdobject* csf_mdpool::create() {

	csf_mdobject*	 tmp_object = NULL;


	//查找队列中是否存在现有对象
	if (m_queue.pop(tmp_object)) {
		return tmp_object;
	}
	else {
		//如果空闲列表没有，则重新一个对象
		tmp_object = create_object();
		if (tmp_object) {
			set_used_count(get_used_count() + 1);
			return tmp_object;
		}
	}
	return NULL;
}


/**
 * 功能：释放资源对象
 * 返回：无
 *
 * @param mdobject    表示需要被释放的MDObjectTyper对象
 */
void csf_mdpool::destroy(csf_mdobject* mdobject) {

	if (!mdobject) {
		return;
	}

	//如果内存块数量大于最大数量，则直接释放
	if (get_used_count() > (int)get_max_size()) {
		destroy_object(mdobject);
		set_used_count(get_used_count() - 1);
	}
	else {
		mdobject->reset();
		m_queue.push(mdobject);
	}
}


/**
 * 功能：清除内存管理器中的所有内存对象，释放内存管理器中保存的所有内存
 * 返回：无
 */
void csf_mdpool::clear() {
	csf_mdobject*	tmp_mdobject = NULL;
	int				i = 0;


	//设置最大内存数量
	set_max_size(0);

	/*
	* 释放所有已经分配资源
	*/
	while (m_queue.pop(tmp_mdobject)) {
		if (tmp_mdobject) {
			destroy_object(tmp_mdobject);
		}
		tmp_mdobject = NULL;
	}

	for (i = get_lager_count(); i > 0; i--) {

		tmp_mdobject = NULL;
		m_queue.pop(tmp_mdobject);
		if (tmp_mdobject) {
			destroy_object(tmp_mdobject);
		}
	}
}

