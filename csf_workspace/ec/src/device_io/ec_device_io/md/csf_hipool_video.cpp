/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hipool_video.hpp
*
*Version: 1.0
*
*Date: 08-12月-2019 20:54:21
*
*Description: Class(csf_hipool_video)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_hipool_video.hpp"
#include "csf_hiobject_video.hpp"

using ec::core::csf_hipool_video;
using ec::core::csf_mdobject;


/**
 * 功能：创建一个资源对象
 * 返回：成功则一个资源对象指针；失败则返回空
 * 
 * @param size    表示当前帧数据长度
 */
csf_mdobject* csf_hipool_video::create_object(unsigned int size) {

	return new csf_hiobject_video(this, size);
}