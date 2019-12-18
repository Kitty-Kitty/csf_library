/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hiprocessor.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 8:46:36
*
*Description: Class(csf_hiprocessor)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hi_include.hpp"
#include "csf_hiprocessor.hpp"
#include "csf_hiai.hpp"
#include "csf_hivi.hpp"
#include "csf_mp4muxer_recoder.hpp"

using ec::core::csf_hiprocessor;


csf_hiprocessor::csf_hiprocessor() {

}



csf_hiprocessor::~csf_hiprocessor() {

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
csf::core::base::csf_int32 csf_hiprocessor::init(const csf_configure_manager * conf_mg) {

	return 0;
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
csf::core::base::csf_int32 csf_hiprocessor::start(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;


	//启动hisystem,
	tmp_ret = start_hisystem();
	if (csf_failure == tmp_ret) {
		stop_hisystem();
		csf_log(error, "start hisystem failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start hisystem succeed!");
	}

	//启动hivi,
	tmp_ret = start_hivi(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error, "start hivi failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start hivi succeed!");
	}

	//启动hiai,
	tmp_ret = start_hiai(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error, "start hiai failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "start hiai succeed!");
	}

	//启动recoder,
	tmp_ret = start_recoder(conf_mg);
	if (csf_failure == tmp_ret) {
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
csf::core::base::csf_int32 csf_hiprocessor::stop(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;


	//停止hisystem,
	tmp_ret = stop_hisystem();
	if (csf_failure == tmp_ret) {
		csf_log(error, "stop hisystem failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "stop hisystem succeed!");
	}

	//停止hivi,
	tmp_ret = stop_hivi(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error, "stop hivi failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "stop hivi succeed!");
	}

	//停止hiai,
	tmp_ret = stop_hiai(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error, "stop hiai failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "stop hiai succeed!");
	}

	//停止recoder,
	tmp_ret = stop_recoder(conf_mg);
	if (csf_failure == tmp_ret) {
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
*    启动海思通道对象。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param hichannel    表示需要被启动的hichannel对象
* @param hiconfigure    表示hichannel对象对应的配置信息对象
*/
csf::core::base::csf_int32 csf_hiprocessor::start_hichannel(csf_hichannel * hichannel, hichannel_conf* hiconfigure) {

	csf_int32		tmp_ret = 0;


	//初始化hiai音频采集通道
	tmp_ret = hichannel->init(this, hiconfigure);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "init hichannel[%p] failed!"
			, hichannel);
		return csf_failure;
	}
	else {
		csf_log(notice
			, "init hichannel[%p] succeed!"
			, hichannel);
	}

	//启动hiai音频采集通道
	tmp_ret = hichannel->start(this, hiconfigure);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "start hichannel[%p] failed!"
			, hichannel);
		hichannel->stop(this, hiconfigure);
		return csf_failure;
	}
	else {
		csf_log(notice, "start hichannel[%p] succeed!"
			, hichannel);
	}

	return csf_succeed;
}


/**
* 功能：
*    停止指定名称的通道对象。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param name    表示需要停止的通道对象名称
*/
csf::core::base::csf_int32 csf_hiprocessor::stop_hichannel(const std::string name) {

	csf_int32		tmp_ret = 0;
	csf_hichannel	*tmp_hichannel = NULL;


	//查找需要的通道对象
	tmp_hichannel = get_hichannel_manager().find(name);
	if (!tmp_hichannel) {
		csf_log(error
			, "not found hichannel[%s]. stop hichannel failed!"
			, name.c_str());
		return csf_failure;
	}
	//停止通道对象,即使是停止失败，也需要释放资源
	tmp_ret = stop_hichannel(tmp_hichannel);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "stop hichannel[%s(%p)] failed!"
			, name.c_str()
			, tmp_hichannel);
		//即使是停止失败，也需要释放资源...
	}
	else {
		csf_log(notice
			, "stop hichannel[%s(%p)] succeed!"
			, name.c_str()
			, tmp_hichannel);
	}
	//从队列中删除通道
	get_hichannel_manager().del(name);
	delete tmp_hichannel;

	csf_log(notice
		, "remove hichannel[%s(%p)] succeed!"
		, name.c_str()
		, tmp_hichannel);

	return csf_succeed;
}


/**
* 功能：
*    停止海思通道对象。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param hichannel    表示需要被启动的hichannel对象
*/
csf::core::base::csf_int32 csf_hiprocessor::stop_hichannel(csf_hichannel * hichannel) {

	csf_int32		tmp_ret = 0;


	//停止通道对象,即使是停止失败，也需要释放资源
	tmp_ret = hichannel->stop(NULL, NULL);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "stop hichannel[%p] failed!"
			, hichannel);
		//即使是停止失败，也需要释放资源...
		return csf_failure;
	}
	else {
		csf_log(notice
			, "stop hichannel[%p] succeed!"
			, hichannel);
	}

	return csf_succeed;
}


/**
* 功能：
*    启动音频采集编码通道。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_hiprocessor::start_hiai(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;
	csf_hichannel	*tmp_hichannel = NULL;


	//创建一个hiai音频采集通道，用于音频的编码保存
	tmp_hichannel = new csf_hiai(this, &get_hiconf().get_audio_conf().get_ai_conf());
	if (!tmp_hichannel) {
		csf_log(error
			, "create csf_hiai[%s] failed!"
			, HIAI_CHANNEL_NAME);
		return csf_failure;
	}

	tmp_ret = start_hichannel(tmp_hichannel, &get_hiconf().get_audio_conf().get_ai_conf());
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "start csf_hiai[%s(%p)] failed!"
			, HIAI_CHANNEL_NAME
			, tmp_hichannel);
		stop_hichannel(tmp_hichannel);
		delete tmp_hichannel;
		return csf_failure;
	}
	else {
		csf_log(notice
			, "start csf_hiai[%s(%p)] succeed!"
			, HIAI_CHANNEL_NAME
			, tmp_hichannel);
	}
	
	//将通道添加到列表中
	//tmp_hichannel->get_mdpipe().get_mdslot()->set_name(HIAI_CHANNEL_NAME);
	get_hichannel_manager().add(HIAI_CHANNEL_NAME, tmp_hichannel);

	return csf_succeed;
}


/**
* 功能：
*    停止音频采集编码通道。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_hiprocessor::stop_hiai(const csf_configure_manager * conf_mg) {

	return stop_hichannel(HIAI_CHANNEL_NAME);
}


/**
* 功能：
*    启动视频采集编码通道。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_hiprocessor::start_hivi(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;
	csf_hichannel	*tmp_hichannel = NULL;
	hivideo_channel_conf	*tmp_hivideo_channel_conf = NULL;


	tmp_hivideo_channel_conf = get_hiconf().get_video_conf().find("video_configure");
	if (!tmp_hivideo_channel_conf) {
		csf_log(error
			, "get video configure by name[video_configure] failed!");
		return csf_failure;
	}

	//创建一个hiai音频采集通道，用于音频的编码保存
	tmp_hichannel = new csf_hivi(this, tmp_hivideo_channel_conf);
	if (!tmp_hichannel) {
		csf_log(error
			, "create csf_hivi[%s] failed!"
			, HIVI_CHANNEL_NAME);
		return csf_failure;
	}

	tmp_ret = start_hichannel(tmp_hichannel, tmp_hivideo_channel_conf);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "start csf_hiai[%s(%p)] failed!"
			, HIVI_CHANNEL_NAME
			, tmp_hichannel);
		stop_hichannel(tmp_hichannel);
		delete tmp_hichannel;
		return csf_failure;
	}
	else {
		csf_log(notice
			, "start csf_hiai[%s(%p)] succeed!"
			, HIVI_CHANNEL_NAME
			, tmp_hichannel);
	}

	//将通道添加到列表中
	//tmp_hichannel->get_mdpipe().get_mdslot()->set_name(HIAI_CHANNEL_NAME);
	get_hichannel_manager().add(HIVI_CHANNEL_NAME, tmp_hichannel);

	return csf_succeed;
}


/**
* 功能：
*    停止视频采集编码通道。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_hiprocessor::stop_hivi(const csf_configure_manager * conf_mg) {

	return stop_hichannel(HIVI_CHANNEL_NAME);
}


/**
* 功能：
*    启动海思系统
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*/
csf::core::base::csf_int32 csf_hiprocessor::start_hisystem() {

	csf_int32		tmp_ret = 0;
	

	tmp_ret = get_hisystem().init(this, &get_hiconf().get_sys_conf());
	if (csf_failure == tmp_ret) {
		csf_log(error, "init hisystem failed!");
		return csf_failure;
	}
	else {
		csf_log(notice
			, "init hisystem succeed!");
	}

	tmp_ret = get_hisystem().start(this, &get_hiconf().get_sys_conf());
	if (csf_failure == tmp_ret) {
		get_hisystem().stop(this, &get_hiconf().get_sys_conf());
		csf_log(error, "start hisystem failed!");
		return csf_failure;
	}
	else {
		csf_log(notice
			, "start hisystem succeed!");
	}

	return csf_succeed;
}


/**
* 功能：
*    停止海思系统
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*/
csf::core::base::csf_int32 csf_hiprocessor::stop_hisystem() {

	csf_int32		tmp_ret = 0;


	tmp_ret = get_hisystem().stop(this, &get_hiconf().get_sys_conf());
	if (csf_failure == tmp_ret) {
		csf_log(error, "stop hisystem failed!");
		return csf_failure;
	}
	else {
		csf_log(notice
			, "stop hisystem succeed!");
	}	

	return csf_succeed;
}


/**
* 功能：
*    启动数据记录保存对象。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_hiprocessor::start_recoder(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;
	csf_mp4recoder	*tmp_recoder = NULL;
	csf_hichannel	*tmp_audio_hichannel = NULL;
	csf_hichannel	*tmp_video_hichannel = NULL;


	tmp_audio_hichannel = get_hichannel_manager().find(HIAI_CHANNEL_NAME);
	tmp_video_hichannel = get_hichannel_manager().find(HIVI_CHANNEL_NAME);
	if (!tmp_audio_hichannel || !tmp_video_hichannel) {
		csf_log(error
			, "video channel[%p] or audio channel[%p] is null failed!"
			, tmp_video_hichannel
			, tmp_audio_hichannel);
		return csf_failure;
	}

	//创建一个mp4记录对象
	tmp_recoder = new csf_mp4muxer_recoder(this, tmp_video_hichannel, tmp_audio_hichannel);
	if (!tmp_recoder) {
		csf_log(error
			, "create mp4 recoder failed!");
		return csf_failure;
	}
	set_mp4recoder(tmp_recoder);

	//初始化hiai音频采集通道
	tmp_ret = tmp_recoder->init(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "init recoder[%p] failed!"
			, tmp_recoder);
		return csf_failure;
	}
	else {
		csf_log(notice
			, "init recoder[%p] succeed!"
			, tmp_recoder);
	}

	//启动hiai音频采集通道
	tmp_ret = tmp_recoder->start(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "start recoder[%p] failed!"
			, tmp_recoder);
		tmp_recoder->stop(conf_mg);
		return csf_failure;
	}
	else {
		csf_log(notice, "start recoder[%p] succeed!"
			, tmp_recoder);
	}

	return csf_succeed;
}


/**
* 功能：
*    停止数据记录保存对象。
* 返回：
*    0   ：表示成功
*    非0 ：表示失败
*
* @param conf_mg    表示配置文件信息
*/
csf::core::base::csf_int32 csf_hiprocessor::stop_recoder(const csf_configure_manager * conf_mg) {

	csf_int32		tmp_ret = 0;
	csf_mp4recoder	*tmp_recoder = NULL;


	tmp_recoder = get_mp4recoder();

	//停止recoder对象
	tmp_ret = tmp_recoder->stop(conf_mg);
	if (csf_failure == tmp_ret) {
		csf_log(error
			, "stop recoder[%p] failed!"
			, tmp_recoder);
		return csf_failure;
	}
	else {
		csf_log(notice
			, "stop recoder[%p] succeed!"
			, tmp_recoder);
	}
	delete tmp_recoder;
	set_mp4recoder(NULL);

	return csf_succeed;
}