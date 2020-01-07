/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mdpipe.hpp
*
*Version: 1.0
*
*Date: 30-11月-2019 16:44:05
*
*Description: Class(csf_mdpipe)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_uuid.hpp"
#include "csf_mdpipe.hpp"

using ec::core::csf_mdpipe;



/**
* 表示通道的uuid，用于唯一标识一个通道
*/
void csf_mdpipe::set_guid() {

	csf_memset(m_guid, 0, csf_sizeof(m_guid));
	csf::core::utils::csf_uuid::make32(m_guid, csf_sizeof(m_guid));
}


/**
 * 功能：向通道中发送媒体数据帧
 * 返回：true表示发送成功；false表示发送失败；
 *
 * @param data    表示需要发送的媒体数据帧数据
 * @param len    表示需要发送的数据长度
 */
bool csf_mdpipe::push_frame(unsigned char* data, unsigned int len) {

	csf_mdbuffer		tmp_mdbuffer;


	//验证参数的合法性
	if (!data || len <= 0) {
		return false;
	}

	//创建一个csf_mdbuffer用于保存数据
	tmp_mdbuffer = get_mdpool().mdalloc(len);
	if (!tmp_mdbuffer.is_null()) {
		return false;
	}

	//拷贝数据
	if (len != tmp_mdbuffer.cat(data, len)) {
		get_mdpool().mdfree(tmp_mdbuffer);
		return false;
	}

	//将数据帧插入到队列中保存
	csf_mdframe_ptr tmp_mdframe(new csf_mdframe(tmp_mdbuffer));
	get_queue().push_back(tmp_mdframe);

	return true;
}
