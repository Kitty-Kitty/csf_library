/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mp4muxer_file.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 20:10:00
*
*Description: Class(csf_mp4muxer_file)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "csf_mp4muxer_file.hpp"
#include "mp4muxer.h"
#include "csf_hiobject_video.hpp"
#include "csf_h264_nalu.hpp"
#include "csf_logger.hpp"

using namespace ec::core;

csf_mp4muxer_file::csf_mp4muxer_file()
	: m_duration(300)
	, m_width(1920)
	, m_height(1080)
	, m_frame_rate(30)
	, m_gop(30)
	, m_channel_number(2)
	, m_sample_rate(44100)
	, m_sample_bits(16)
	, m_sample_number(1024)
	, m_sps(32)
	, m_pps(32)
	, m_mp4muxer(NULL)
	, m_frames(0)
	, m_size(0)
	, m_max_frames(9000)
	, m_max_size(200 * 1024 * 1024) {

}


csf_mp4muxer_file::~csf_mp4muxer_file() {

	close();
}


/**
* 功能：
*    创建一个新的mp4文件
* 返回：
*    true ： 表示成功
*    false： 表示失败
*
* @param name    表示需要创建的文件名称
*/
bool csf_mp4muxer_file::open(std::string name) {

	void *mp4 = mp4muxer_init((char*)name.c_str()
		, get_duration() * 1000
		, get_width()
		, get_height()
		, get_frame_rate()
		, get_gop()
		, get_channel_number()
		, get_sample_rate()
		, get_sample_bits()
		, get_sample_number()
		, NULL);

	if (!mp4) {
		return false;
	}
	else {
#ifdef FILE_TEST
		m_fd = fopen("test.h264", "wb");
#endif

		set_mp4muxer(mp4);

		set_aacdecspecinfo();
	}
	return true;
}


/**
* 功能：
*    写入视频帧数据
* 返回：
*    true ： 表示成功
*    false： 表示失败
*
* @param mdframe_ptr
*/
bool csf_mp4muxer_file::write_video(csf_mdframe_ptr mdframe_ptr) {

	csf_hiobject_video	*tmp_hiobject = static_cast<csf_hiobject_video*>(mdframe_ptr->get_mdobject());
	unsigned char		*tmp_char = tmp_hiobject->get_buffer();
	unsigned int        tmp_lenght = tmp_hiobject->length();


	//如果是sps或pps则获取更新
	if (csf_h264_nalu::isspspps(tmp_char, tmp_lenght)) {
		set_spspps(tmp_char, tmp_lenght);
		set_base_pts(tmp_hiobject->get_pts());
	}
	else {
		if (csf_h264_nalu::ispicture(tmp_char, tmp_lenght)) {
			set_frames(get_frames() + 1);
		}
	}

#ifdef FILE_TEST
	fwrite(tmp_char, tmp_lenght, 1, m_fd);
#endif

	//如果还没有设置sps 和 pps，则需要先设置一下
	if (isspspps()) {
		set_mp4muxer_spspps();
		return true;
	}

	//表示已经满了，需要分文件
	if (isfinish()) {
		return false;
	}

	if (csf_h264_nalu::ispps(tmp_char, tmp_lenght)) {
		set_mp4muxer_spspps();
	}
	else {
		//如果设置好了，则直接写文件
		mp4muxer_video(get_mp4muxer()
			, tmp_char
			, tmp_lenght
			, tmp_hiobject->get_pts()
			//, 90000 / get_frame_rate()
		);
	}

// 	csf_log(notice
// 		, "%d frame pts: %lld"
// 		, get_frames()
// 		, tmp_hiobject->get_pts());

	set_size(get_size() + tmp_lenght);

	return true;
}


/**
* 功能：
*    写入音频帧数据
* 返回：
*    true ： 表示成功
*    false： 表示失败
*
* @param mdframe_ptr
*/
bool csf_mp4muxer_file::write_audio(csf_mdframe_ptr mdframe_ptr) {

	csf_hiobject		*tmp_hiobject = static_cast<csf_hiobject*>(mdframe_ptr->get_mdobject());
	unsigned char		*tmp_char = tmp_hiobject->get_buffer();
	unsigned int        tmp_lenght = tmp_hiobject->length();


	//表示已经满了，需要分文件
	if (isfinish()) {
		return false;
	}

	//如果设置好了，则直接写文件
	mp4muxer_audio(get_mp4muxer()
		, tmp_char
		, tmp_lenght
		, tmp_hiobject->get_pts()
	);

	set_size(get_size() + tmp_lenght);

	return true;
}


/**
* 功能：
*    关闭文件
* 返回：
*    true ： 表示成功
*    false： 表示失败
*/
bool csf_mp4muxer_file::close() {

#ifdef FILE_TEST
	fclose(m_fd);
#endif

	if (get_mp4muxer()) {
		mp4muxer_exit(get_mp4muxer());
	}
	reset();

	return true;
}



/**
 * 功能：
 *    重置文件保存对象
 * 返回：
 *    true ： 表示成功
 *    false： 表示失败
 */
bool csf_mp4muxer_file::reset() {

	set_spspps(true);
	//get_sps().reset();
	//get_pps().reset();
	set_frames(0);
	set_size(0);
	set_mp4muxer(NULL);

	return true;
}


/**
* 功能：
*    表示文件是否已经保存完成
* 返回：
*    true ： 表示成功
*    false： 表示失败
*/
bool csf_mp4muxer_file::isfinish() {

	if (frame_finish() || size_finish()) {
		return true;
	}
	return false;
}


/**
* 功能：
*    设置sps和pps数据
* 返回：
*    true ： 表示成功
*    false： 表示失败
*/
bool csf_mp4muxer_file::set_mp4muxer_spspps() {

	if (get_sps().is_null() || get_pps().is_null()) {
		return false;
	}
	else {

		int  tmp_head_size = csf_h264_nalu::nalu_head_size(get_sps().get_buffer(), get_sps().length());
		
		mp4muxer_spspps(get_mp4muxer()
			, get_sps().get_buffer() + tmp_head_size
			, get_sps().length() - tmp_head_size
			, get_pps().get_buffer() + tmp_head_size
			, get_pps().length() - tmp_head_size
		);
		set_spspps(false);
	}

	return true;
}


/**
* 功能：
*    设置sps和pps缓存数据
* 返回：
*    true ： 表示成功
*    false： 表示失败
*
* @param buf    表示数据内存地址
* @param len    表示数据的长度
*/
bool csf_mp4muxer_file::set_spspps(unsigned char* buf, unsigned int len) {

	unsigned int			i = 0;
	unsigned int			j = 0;
	int						tmp_head_size = 0;
	unsigned char			*tmp_point[32] = { NULL, };


	//查找h264数据中的所有00 00 01或00 00 00 01标识
	for (i = 0; i < len; i++) {
		tmp_head_size = csf_h264_nalu::nalu_head_size(&buf[i], len - 1);
		if (!tmp_head_size) {
			continue;
		}
		else {
			tmp_point[j++] = &buf[i];
			i += tmp_head_size;
		}
	}

	if (j) {
		tmp_point[j] = buf + len;
	}
	
	for (i = 0; i < csf_ary_size(tmp_point); i++) {

		if (!tmp_point[i] || !tmp_point[i + 1]) {
			break;
		}

		tmp_head_size = csf_h264_nalu::nalu_head_size(tmp_point[i]
			, tmp_point[i + 1] - tmp_point[i]);
		if (!tmp_head_size) {
			continue;
		}
		else {
			if (csf_h264_nalu::issps(tmp_point[i], tmp_point[i + 1] - tmp_point[i])) {
				get_sps().reset();
				get_sps().cat(tmp_point[i], tmp_point[i + 1] - tmp_point[i]);
			}

			if (csf_h264_nalu::ispps(tmp_point[i], tmp_point[i + 1] - tmp_point[i])) {
				get_pps().reset();
				get_pps().cat(tmp_point[i], tmp_point[i + 1] - tmp_point[i]);
			}
		}
	}

	return true;
}


/**
* 功能：
*    设置aac的dsi数据
* 返回：
*    true ： 表示成功
*    false： 表示失败
*/
bool csf_mp4muxer_file::set_aacdecspecinfo() {

	unsigned char dsi[] = { 0x12, 0x34 };

	mp4muxer_aacdecspecinfo(get_mp4muxer(), dsi);

	return true;
}


/**
* 功能：
*    判断视频与音频时间戳的大小。根据时间戳大小返回不同的数值
* 返回：
*    1： 表示视频时间戳大于音频时间戳
*    0： 表示视频时间戳等于音频时间戳
*   -1： 表示视频时间戳小于音频时间戳
*
* @param video_ptr
* @param audio_ptr
*/
int csf_mp4muxer_file::compare_pts(csf_mdframe_ptr video_ptr, csf_mdframe_ptr audio_ptr) {

	csf_hiobject	*tmp_video_hiobject = static_cast<csf_hiobject*>(video_ptr->get_mdobject());
	csf_hiobject	*tmp_audio_hiobject = static_cast<csf_hiobject*>(video_ptr->get_mdobject());


	if (tmp_video_hiobject->get_pts() > tmp_audio_hiobject->get_pts()) {
		return 1;
	}
	else if (tmp_video_hiobject->get_pts() == tmp_audio_hiobject->get_pts()) {
		return 0;
	}
	else {
		return -1;
	}
	return 0;
}