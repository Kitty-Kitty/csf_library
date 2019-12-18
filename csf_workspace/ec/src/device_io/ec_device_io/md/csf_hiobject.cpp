/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hiobject.hpp
*
*Version: 1.0
*
*Date: 02-12月-2019 15:29:40
*
*Description: Class(csf_hiobject)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_hiobject.hpp"
#include "csf_mdpool.hpp"

using ec::core::csf_hiobject;


/**
 * 功能：表示媒体数据对象销毁接口
 */
void csf_hiobject::destroy() {
	if (get_mdpool()) {
		get_mdpool()->destroy(this);
	}
}


/**
 * 功能：重新初始化媒体数据对象
 * 返回：无
 */
void csf_hiobject::reset() {

}
