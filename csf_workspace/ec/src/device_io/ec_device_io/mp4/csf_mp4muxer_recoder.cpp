/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_mp4muxer_recoder.hpp
*
*Version: 1.0
*
*Date: 07-12月-2019 13:15:01
*
*Description: Class(csf_mp4muxer_recoder)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hi_include.hpp"
#include "csf_mp4muxer_recoder.hpp"
#include "sleep_time.hpp"
#include "csf_uuid.hpp"
//#include "csf_minimp4_file.hpp"
#include "csf_mp4muxer_file.hpp"
#include "hivideo_channel_conf.hpp"

#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#define	BOOST_DATE_TIME_SOURCE

using ec::core::csf_mp4muxer_recoder;


csf_mp4muxer_recoder::csf_mp4muxer_recoder()
	: csf_mp4recoder(NULL)
	, m_video_channel(NULL)
	, m_audio_channel(NULL) {

	//set_mp4(new csf_minimp4_file());
	set_mp4(new csf_mp4muxer_file());
}
/**
* 功能：
*    根据processor、video、audio对象，创建recoder对象
*
* @param processor    表示当前媒体的processor对象
* @param video    表示视频通道
*
* @param audio    表示音频通道
*/
csf_mp4muxer_recoder::csf_mp4muxer_recoder(csf_hiprocessor* processor
	, csf_hichannel* video
	, csf_hichannel* audio)
	: csf_mp4recoder(processor)
	, m_video_channel(video)
	, m_audio_channel(audio) {

	//set_mp4(new csf_minimp4_file());
	set_mp4(new csf_mp4muxer_file());
}

csf_mp4muxer_recoder::~csf_mp4muxer_recoder() {

}


/**
 * 功能：
 *    模块初始化，进行模块启动前的准备工作。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_mp4muxer_recoder::init(const csf_configure_manager * conf_mg) {

	csf_bool		tmp_bool_ret = csf_false;


	//初始化存储目录
	tmp_bool_ret = make_directory();
	if (!tmp_bool_ret) {
		csf_log(error, "make directory failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "make directory succeed!");
	}

	return csf_succeed;
}


/**
 * 功能：
 *    模块启动，进行模块启动工作。表示模块已经正常运行。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_mp4muxer_recoder::start(const csf_configure_manager * conf_mg) {

	csf_bool		tmp_bool_ret = csf_false;


	//启动处理线程
	tmp_bool_ret = start_thread();
	if (!tmp_bool_ret) {
		csf_log(error, "start recoder failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start recoder succeed!");
	}

	return csf_succeed;
}


/**
 * 功能：
 *    模块停止，进行模块停止工作。释放模块初始化、运行时创建的资源。
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param conf_mg    表示配置文件信息
 */
csf::core::base::csf_int32 csf_mp4muxer_recoder::stop(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;


	//停止处理线程
	tmp_ret = stop_thread();
	if (tmp_ret) {
		csf_log(error, "stop recoder failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "stop recoder succeed!");
	}

	return csf_succeed;
}


/**
* 功能：
*    初始化mp4muxer处理相关内容
* 返回：
*    true ：表示成功
*    false：表示失败
*/
bool csf_mp4muxer_recoder::init_mp4muxer() {

	return false;
}


/**
* 功能：
*    启动mp4muxer处理相关内容
* 返回：
*    true ：表示成功
*    false：表示失败
*/
bool csf_mp4muxer_recoder::start_mp4muxer() {

	return false;
}


/**
* 功能：
*    停止mp4muxer处理相关内容
* 返回：
*    true ：表示成功
*    false：表示失败
*/
bool csf_mp4muxer_recoder::stop_mp4muxer() {

	return false;
}


/**
* 功能：
*    启动mp4处理线程
* 返回：
*    true：表示成功；
*    false：表示失败；
*
*/
bool csf_mp4muxer_recoder::start_thread() {

	//创建线程
	set_thread(new csf_thread(csf_bind(&csf_mp4muxer_recoder::thread_process, this, this)));

	csf_log(notice, "create thread[%p] succeed!", get_thread());

	return true;
}


/**
* 功能：
*    mp4线程处理函数
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param recoder    表示mp4记录对象指针
*/
bool csf_mp4muxer_recoder::thread_process(csf_mp4recoder* recoder) {

	csf_mdframe_ptr			tmp_video_mdframe_ptr;
	csf_mdframe_ptr			tmp_audio_mdframe_ptr;
	csf_mdslot				*tmp_video_mdslot = NULL;
	csf_mdslot				*tmp_audio_mdslot = NULL;


	tmp_video_mdslot = get_video_channel()->get_mdpipe().get_mdslot();
	tmp_audio_mdslot = get_audio_channel()->get_mdpipe().get_mdslot();

	while (get_thread()->is_start())
	{
		tmp_video_mdframe_ptr = tmp_video_mdslot->pop_frame();
		if (!tmp_video_mdframe_ptr) {
			//如果没有视频，则休眠等待
			//csf::core::utils::time::sleep_time::sleep_ms(10);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}
		else {
#ifdef HI_TEST_LOADER
			csf_log(notice
				, "recoder video hichannel[ %p ] mdslot size[ %d ]."
				, this
				, tmp_video_mdslot->size()
			);
#endif
		}

		//校验mp4文件情况
		if (!open_mp4()) {
			csf_log(error, "open mp4 file failed!");
			continue;
		}

		//写入mp4数据
		if (!get_mp4()->write_video(tmp_video_mdframe_ptr)) {

			if (!get_mp4()->isfinish()) {
				csf_log(error, "open mp4 video data failed!");
				continue;
			}

			//如果一个文件已经写满，则重新创建一个新文件
			close_mp4();

			//校验mp4文件情况
			if (!open_mp4()) {
				csf_log(error, "open mp4 file failed!");
				continue;
			}
		}

		//写入音频数据
		while (get_thread()->is_start())
		{
			tmp_audio_mdframe_ptr = tmp_audio_mdslot->pop_frame();
			if (!tmp_audio_mdframe_ptr) {
				//如果没有音频，则退出
				break;
			}
			//写入mp4数据
			//if (!get_mp4()->write_audio(tmp_audio_mdframe_ptr)) {
			//	csf_log(error, "open mp4 audio data failed!");
			//	continue;
			//}

			//判断时间戳是否已经超过视频时间戳，如果超过则停止写，等待下一个视频帧
			if (get_mp4()->compare_pts(tmp_video_mdframe_ptr
				, tmp_audio_mdframe_ptr) >= 0) {
				break;
			}
		}
	}

	return false;
}


/**
* 功能：
*    停止mp4处理线程
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param recoder    表示mp4记录对象指针
*/
bool csf_mp4muxer_recoder::stop_thread() {

	if (get_thread()) {
		get_thread()->stop();
	}

	return true;
}


/**
* 功能：
*    创建mp4文件
* 返回：
*    true ：表示成功
*    false：表示失败
*/
bool csf_mp4muxer_recoder::open_mp4() {

	if (get_mp4()->isopen()) {
		return true;
	}

	get_mp4()->set_video(300, 1920, 1080, 30, 60);
	get_mp4()->set_audio(1, 44100, 16, 1024);

	//校验mp4文件情况
// 	char	tmp_uuid[64] = { 0, };
// 	char	tmp_file_name[128] = { 0, };
// 
// 	csf::core::utils::csf_uuid::make32(tmp_uuid, sizeof(tmp_uuid));
//	csf_sprintf(tmp_file_name, "%s.mp4", tmp_uuid);

	std::string		tmp_file_name = make_file_name();
	if (!get_mp4()->open(tmp_file_name.c_str())) {
		csf_log(error
			, "create mp4 file[%s] failed!"
			, tmp_file_name.c_str());
		return false;
	}
	else {
		csf_log(notice
			, "create mp4 file[%s] succeed!"
			, tmp_file_name.c_str());
	}

	return true;
}


/**
* 功能：
*    关闭mp4文件
* 返回：
*    true ：表示成功
*    false：表示失败
*/
bool csf_mp4muxer_recoder::close_mp4() {

	return get_mp4()->close();
}


/**
* 功能：
*    生成一个格式化的文件名
* 返回：
*    一个文件名字符串
*/
std::string csf_mp4muxer_recoder::make_file_name() {
	char			tmp_file_name[1024] = { 0, };
	hivideo_channel_conf	*tmp_conf = dynamic_cast<hivideo_channel_conf*>(
		get_video_channel()->get_configure()
		);
	std::string		tmp_time = boost::posix_time::to_iso_string(
		boost::posix_time::microsec_clock::local_time());


	csf_snprintf(tmp_file_name
		, csf_sizeof(tmp_file_name)
		, "%s%c%s.mp4"
		, tmp_conf->get_disk_storage().get_path().c_str()
		, boost::filesystem::path::preferred_separator
		, tmp_time.c_str());

	return tmp_file_name;
}


/**
* 功能：
*    生成保存视频文件的目录
* 返回：
*    true  ：  表示创建成功
*    false ：  表示创建失败
*/
bool csf_mp4muxer_recoder::make_directory() {

	hivideo_channel_conf		*tmp_conf = dynamic_cast<hivideo_channel_conf*>(
		get_video_channel()->get_configure()
		);
	boost::filesystem::path		tmp_path(tmp_conf->get_disk_storage().get_path());


	//文件夹不存在，则创建
	if (boost::filesystem::exists(tmp_path)) {
		csf_log(notice
			, "disk storage directory[%s] exist!"
			, tmp_conf->get_disk_storage().get_path().c_str());
		return true;
	}

	try {
		if (!boost::filesystem::create_directory(tmp_path)) {
			csf_log(error
				, "create directory[%s] of disk storage failed!"
				, tmp_conf->get_disk_storage().get_path().c_str());
			return false;
		}
		else {
			csf_log(notice
				, "create directory[%s] of disk storage succeed!"
				, tmp_conf->get_disk_storage().get_path().c_str());
			return true;
		}
	}
	catch (boost::filesystem::filesystem_error e) {
		csf_log(error
			, "create directory[%s] of disk storage failed! exception: %s"
			, tmp_conf->get_disk_storage().get_path().c_str()
			, e.what());

		return false;
	}

	return true;
}