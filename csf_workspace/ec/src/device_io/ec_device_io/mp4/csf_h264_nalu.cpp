/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_h264_nalu.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 16:30:52
*
*Description: Class(csf_h264_nalu)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_h264_nalu.hpp"

using ec::core::csf_h264_nalu;


csf_h264_nalu::csf_h264_nalu()
	: m_buffer(NULL)
	, m_length(0)
	, m_nalu_type(h264_nalu_nal)
	, m_flag_type(0)
	, m_head_length(0) {

}



csf_h264_nalu::~csf_h264_nalu() {

}



/**
 * 功能：
 *    解析传入的nalu数据内容
 * 返回：
 *    true ：表示解析成功；
 *    false：表示解析失败；
 * 
 * @param buf    表示数据内存起始地址
 * @param len    表示数据长度
 */
bool csf_h264_nalu::parse(unsigned char* buf, unsigned int len) {

	unsigned int			tmp_head_pos = 0;
	unsigned int			tmp_nalu_length = 0;


	//h264开始标识00 00 00 01
	tmp_head_pos = find_nalu_head(buf, len);
	if (tmp_head_pos >= len) {
		return false;
	}
	else {
		set_buffer(buf + tmp_head_pos);
	}
	//查找h264头的长度
	if (len - tmp_head_pos >= 3) {
		if (buf[tmp_head_pos] == 0 
			&& buf[tmp_head_pos + 1] == 0 
			&& buf[tmp_head_pos + 2] == 1) {
			set_head_length(3);
		}
	}
	if (len - tmp_head_pos >= 4) {
		if (buf[tmp_head_pos] == 0 
			&& buf[tmp_head_pos + 1] == 0 
			&& buf[tmp_head_pos + 2] == 0 
			&& buf[tmp_head_pos + 3] == 1) {
			set_head_length(4);
		}
	}

	//设置帧相关类型信息
	set_nalu_type((h264_nalu_type)(buf[get_head_length()] & 0x1f));
	set_flag_type(buf[get_head_length() + 1] & 0x80);

	tmp_nalu_length = find_nalu_head(buf + get_head_length(), len - get_head_length());
	set_length(tmp_nalu_length + get_head_length());

	return true;
}



/**
* 功能：
*    查找nalu head的起始位置
* 返回：
*    nalu head的起始位置
*
* @param buf    表示数据内存起始地址
* @param len    表示数据长度
*/
unsigned int csf_h264_nalu::find_nalu_head(unsigned char* buf, unsigned int len) {

	unsigned int		i = 0;
	unsigned int		tmp_head_size = 0;


	for (i = 0; i < len; i++) {

		tmp_head_size = nalu_head_size(buf + i, len - i);
		if (tmp_head_size > 0) {
			return tmp_head_size;
		}
	}
	return len;
}