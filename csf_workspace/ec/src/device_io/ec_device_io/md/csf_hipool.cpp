/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hipool.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 14:31:29
*
*Description: Class(csf_hipool)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_hipool.hpp"
#include "csf_hiobject.hpp"

using ec::core::csf_hipool;
using ec::core::csf_mdobject;


/**
* 功能：创建一个资源对象
* 返回：成功则一个资源对象指针；失败则返回空
*
* @param size    表示当前帧数据长度
*/
csf_mdobject* csf_hipool::create_object(unsigned int size) {

	return new csf_hiobject(this, size);
}


/**
 * 功能：销毁一个资源对象
 * 返回：无
 *
 * @param mdobject
 */
void csf_hipool::destroy_object(csf_mdobject* mdobject) {
	delete mdobject;
}


/**
* 功能：创建一个资源对象
* 返回：一个资源对象
*
* @param buffer_size    表示需要创建内存空间大小
*/
csf_mdobject* csf_hipool::create(unsigned int size) {

	csf_hiobject		*tmp_object = NULL;


	if (size <= 0) {
		return NULL;
	}

	if (size > get_buffer_size()) {
		//创建一个内存对象
		tmp_object = static_cast<csf_hiobject*>(create_object(size));
		if (!tmp_object) {
			return NULL;
		}
		else {
			set_lager_count(get_lager_count() + 1);
			return tmp_object;
		}
	}
	else {
		//从队列中获取需要的对象，并判断是否满足需求
		if (get_queue().pop(tmp_object)) {
			if (check_valid(tmp_object, size)) {
				//如果满足需求，则直接返回使用
				return tmp_object;
			}
			else {
				get_queue().push(tmp_object);
			}
		}

		//创建一个内存对象
		tmp_object = static_cast<csf_hiobject*>(create_object(get_buffer_size()));
		if (!tmp_object) {
			return NULL;
		}
		else {
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
void csf_hipool::destroy(csf_mdobject* mdobject) {

	if (!mdobject) {
		return;
	}

	//如果不等于需要的内存，则直接释放
	if (!check_valid(mdobject, get_buffer_size())) {
		destroy_object(mdobject);
		set_lager_count(get_lager_count() - 1);
	}
	else {
		//如果内存块数量大于最大数量，则直接释放
		if (get_used_count() > (int)get_max_size()) {
			destroy_object(mdobject);
			set_used_count(get_used_count() - 1);
		}
		else {
			mdobject->reset();
			get_queue().push(mdobject);
		}
	}
}


/**
* 功能：
*    校验mdobject对象是否合法，满足需求。其中合法的标准为：内存大小是否大于需求大小。如果大于需求大小，则表示合法；其他为不合法；
* 返回：
*    true：表示满足需求，合法
*    false：表示不满足需求，不合法
*
* @param mdobject    表示需要被释放的MDObjectTyper对象
* @param size
*/
bool csf_hipool::check_valid(csf_mdobject* mdobject, unsigned int size) {

	if (!mdobject) {
		return false;
	}

	if (static_cast<csf_hiobject*>(mdobject)->size() <= size) {
		return true;
	}
	return false;
}