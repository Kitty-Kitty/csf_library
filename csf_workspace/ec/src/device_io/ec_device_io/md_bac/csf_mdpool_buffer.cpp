/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mdpool_buffer.hpp
*
*Version: 1.0
*
*Date: 28-11月-2019 21:21:53
*
*Description: Class(csf_mdpool_buffer)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_mdpool_buffer.hpp"
#include <boost/optional.hpp>

using namespace ec::core;
using ec::core::csf_mdpool_buffer;



/**
 * 功能：分配指定大小的内存块
 * 返回：csf_mdbuffer 对象，描述该内存信息
 * 
 * @param size    表示需要用于分配的内存大小
 */
csf_mdbuffer* csf_mdpool_buffer::mdalloc(unsigned int size) {

	unsigned char*	 tmp_buf = NULL;
	csf_mdbuffer*	 tmp_mdbuf = NULL;


	if (size <= 0) {
		return NULL;
	}

	if (size > get_buffer_size()) {
		//分配一个大内存块
		tmp_buf = (unsigned char*)malloc(size);
		if (!tmp_buf) {
			return NULL;
		}
		else {
			set_lager_count(get_lager_count() + 1);
			return new csf_mdbuffer(tmp_buf, size);
		}
	}
	else {
		//如果小于默认的大小,则尽量从缓存中获取
		if (m_queue.pop(tmp_mdbuf)) {
			return tmp_mdbuf;
		}
		else {
			//如果空闲列表没有，则重新分配一个内存块
			tmp_buf = (unsigned char*)malloc(get_buffer_size());
			if (!tmp_buf) {
				return NULL;
			}
			else {
				set_used_count(get_used_count() + 1);
				return new csf_mdbuffer(tmp_buf, get_buffer_size());
			}
		}
	}
	return NULL;
}


/**
* 功能：释放之前分配的资源
* 返回：无
*
* @param mdbuffer    表示需要被释放的mdbuffer对象
*/
void csf_mdpool_buffer::mdfree(csf_mdbuffer* mdbuffer) {

	if (!mdbuffer ||!mdbuffer->get_mdpool() || !mdbuffer->get_buffer()) {
		return;
	}

	//如果不等于需要的内存，则直接释放
	if (mdbuffer->get_size() != get_buffer_size()) {
		destroy(mdbuffer);
		set_lager_count(get_lager_count() - 1);
	}
	else {
		//如果内存块数量大于最大数量，则直接释放
		if (get_used_count() > (int)get_max_size()) {
			destroy(mdbuffer);
			set_used_count(get_used_count() - 1);
		}
		else {
			mdbuffer->reset();
			m_queue.push(mdbuffer);
		}
	}
}


/**
 * 功能：清除内存管理器中的所有内存对象，释放内存管理器中保存的所有内存
 * 返回：无
 */
void csf_mdpool_buffer::clear() {
	csf_mdbuffer*	tmp_mdbuf = NULL;
	int				i = 0;


	while (m_queue.pop(tmp_mdbuf)) {
		destroy(tmp_mdbuf);
		tmp_mdbuf = NULL;
	}

	for (i = get_lager_count(); i > 0; i--) {
		tmp_mdbuf = NULL;
		m_queue.pop(tmp_mdbuf);
		destroy(tmp_mdbuf);
	}
}