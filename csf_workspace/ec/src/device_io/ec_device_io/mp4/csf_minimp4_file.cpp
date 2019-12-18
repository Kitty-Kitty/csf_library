/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_minimp4_file.hpp
*
*Version: 1.0
*
*Date: 11-12月-2019 18:37:30
*
*Description: Class(csf_minimp4_file)
*
*Others:
*
*History:
*
*******************************************************************************/
#define MINIMP4_IMPLEMENTATION
#ifdef WIN32
#include <sys/types.h>
#include <stddef.h>
#endif
#include "csf_minimp4_file.hpp"
#include "csf_hiobject_video.hpp"
#include "csf_logger.hpp"

using namespace ec::core;


csf_minimp4_file::csf_minimp4_file()
	: m_duration(300)
	, m_width(1920)
	, m_height(1080)
	, m_frame_rate(30)
	, m_gop(30)
	, m_channel_number(2)
	, m_sample_rate(44100)
	, m_sample_bits(16)
	, m_sample_number(1024)
	, m_mp4muxer(NULL)
	, m_frames(0)
	, m_size(0)
	, m_max_frames(9000)
	, m_max_size(209715200) {

}



csf_minimp4_file::~csf_minimp4_file() {

}


#ifdef __cplusplus
extern "C" {
#endif
	static void write_callback(int64_t offset, const void *buffer, size_t size, void *token)
	{
		FILE *f = (FILE*)token;
		fseek(f, offset, SEEK_SET);
		fwrite(buffer, size, 1, f);
	}
#ifdef __cplusplus
}
#endif

/**
 * 功能：
 *    创建一个新的mp4文件
 * 返回：
 *    true ： 表示成功
 *    false： 表示失败
 * 
 * @param name    表示需要创建的文件名称
 */
bool csf_minimp4_file::open(std::string name) {

	int sequential_mode = 0;


	m_fd = fopen(name.c_str(), "wb");
	if (!m_fd) {
		csf_log(error
			, "can't open output file[%s]"
			, name.c_str());
		return false;
	}
	else {
		csf_log(notice
			, "make mp4 file[%s]"
			, name.c_str());
	}

	m_mp4muxer = MP4E__open(sequential_mode, m_fd, write_callback);
	if (!m_mp4muxer) {
		csf_log(error, "MP4E__open() failed!");
		return false;
	}
	else {
		csf_log(notice, "MP4E__open() succeed!");
	}

	mp4_h26x_write_init(&get_mp4_write()
		, m_mp4muxer
		, get_width()
		, get_height()
		, 0);

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
bool csf_minimp4_file::write_video(csf_mdframe_ptr mdframe_ptr) {

	csf_hiobject_video	*tmp_hiobject = static_cast<csf_hiobject_video*>(mdframe_ptr->get_mdobject());
	unsigned char		*tmp_char = tmp_hiobject->get_buffer();
	unsigned int        tmp_lenght = tmp_hiobject->length();


	set_frames(get_frames() + 1);

	//表示已经满了，需要分文件
	if (isfinish()) {
		return false;
	}

	mp4_h26x_write_nal(&get_mp4_write()
		, tmp_char
		, tmp_lenght
		, 90000 / get_frame_rate()
	);

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
bool csf_minimp4_file::write_audio(csf_mdframe_ptr mdframe_ptr) {

	return false;
}


/**
* 功能：
*    关闭文件
* 返回：
*    true ： 表示成功
*    false： 表示失败
*/
bool csf_minimp4_file::close() {

	if (get_mp4muxer()) {
		mp4_h26x_write_free(&get_mp4_write());
		MP4E__close(get_mp4muxer());
		set_mp4muxer(NULL);
	}
	
	if (get_fd()) {
		fclose(get_fd());
		set_fd(NULL);
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
bool csf_minimp4_file::reset() {

	set_frames(0);
	set_size(0);

	return true;
}


/**
 * 功能：
 *    表示文件是否已经保存完成
 * 返回：
 *    true ： 表示成功
 *    false： 表示失败
 */
bool csf_minimp4_file::isfinish() {

	if (frame_finish() || size_finish()) {
		return true;
	}
	return false;
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
int csf_minimp4_file::compare_pts(csf_mdframe_ptr video_ptr, csf_mdframe_ptr audio_ptr) {

	csf_hiobject_video	*tmp_video_hiobject = static_cast<csf_hiobject_video*>(video_ptr->get_mdobject());
	csf_hiobject_video	*tmp_audio_hiobject = static_cast<csf_hiobject_video*>(video_ptr->get_mdobject());


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