/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hiai.hpp
*
*Version: 1.0
*
*Date: 03-12月-2019 13:50:13
*
*Description: Class(csf_hiai)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hi_include.hpp"
#include "csf_hiai.hpp"
#include "csf_mdslot_cover.hpp"
#include "csf_hipool.hpp"
#include "csf_hiobject.hpp"
#include "sleep_time.hpp"

using ec::core::csf_hiai;


/**
* 功能：
*    使用参数创建对象
*
* @param hiproc    表示海思处理模块对象
* @param hiconf    表示海思通道配置信息
*/
csf_hiai::csf_hiai(csf_hiprocessor* hiproc, const hichannel_conf * hiconf)
	: m_aiconf(dynamic_cast<hiaudio_aiconf*>(const_cast<hichannel_conf *>(hiconf)))
	, m_processor(hiproc)
	, m_dev_channel_count(1)
	, m_coder_channel_count(1)
	, m_attribute{0, } {

	get_mdpipe().set_mdslot(new csf_mdslot_cover(HIAI_CHANNEL_NAME, 32));
	get_mdpipe().set_mdpool(new csf_hipool(128, 1 * 512));
}


csf_hiai::~csf_hiai() {
	delete get_mdpipe().get_mdslot();
	delete get_mdpipe().get_mdpool();

	get_mdpipe().set_mdslot(NULL);
	get_mdpipe().set_mdpool(NULL);
}


/**
 * 功能：
 *    初始化通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hiai::init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	bool		tmp_bool_ret = false;


	tmp_bool_ret = init_dev();
	if (!tmp_bool_ret) {
		csf_log(error, "init_dev() failed!");
		return csf_failure;
	}

	tmp_bool_ret = init_coder();
	if (!tmp_bool_ret) {
		csf_log(error, "init_coder() failed!");
		return csf_failure;
	}

	return csf_succeed;
}


/**
 * 功能：
 *    启动通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hiai::start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	bool		tmp_bool_ret = false;


	tmp_bool_ret = start_dev();
	if (!tmp_bool_ret) {
		csf_log(error, "start_dev() failed!");
		return csf_failure;
	}

	tmp_bool_ret = start_coder();
	if (!tmp_bool_ret) {
		csf_log(error, "start_coder() failed!");
		return csf_failure;
	}

	return csf_succeed;
}


/**
 * 功能：
 *    停止通道
 * 返回：
 *    0   ：表示成功
 *    非0 ：表示失败
 *
 * @param hiproc    表示海思处理模块对象
 * @param hiconf    表示海思通道配置信息
 */
int csf_hiai::stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	bool		tmp_bool_ret = false;


	tmp_bool_ret = stop_coder();
	if (!tmp_bool_ret) {
		csf_log(error, "stop_coder() failed!");
		return csf_failure;
	}

	tmp_bool_ret = stop_dev();
	if (!tmp_bool_ret) {
		csf_log(error, "stop_dev() failed!");
		return csf_failure;
	}

	return csf_succeed;
}


/**
* 功能：
*    初始化设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hiai::init_dev() {

#if defined(HI_BUILD_PLATFORM)

	get_attribute().dev_id = get_aiconf()->get_dev_id();
	get_attribute().dev_channel = get_aiconf()->get_dev_channel();
	get_attribute().coder_channel = get_aiconf()->get_coder_channel();

#ifdef HISIV_AAC
	get_attribute().payload_type = PT_AAC;
#else
	get_attribute().payload_type = PT_ADPCMA;
#endif
	get_attribute().aio_attr.enSamplerate = AUDIO_SAMPLE_RATE_8000;
	get_attribute().aio_attr.enBitwidth = AUDIO_BIT_WIDTH_16;
	get_attribute().aio_attr.enWorkmode = AIO_MODE_I2S_MASTER;
	get_attribute().aio_attr.enSoundmode = AUDIO_SOUND_MODE_MONO;
	get_attribute().aio_attr.u32EXFlag = 0;
	get_attribute().aio_attr.u32FrmNum = 30;
	get_attribute().aio_attr.u32PtNumPerFrm = SAMPLE_AUDIO_PTNUMPERFRM;
	get_attribute().aio_attr.u32ChnCnt = get_dev_channel_count();
	get_attribute().aio_attr.u32ClkSel = 0;

#endif

	return true;
}


/**
 * 功能：
 *    启动设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiai::start_dev() {

#if defined(HI_BUILD_PLATFORM)

	HI_S32				i = 0;
	HI_S32				tmp_int_ret = 0;
	AIO_ATTR_S			tmp_aio_attr;


	/********************************************
	step 1: config audio codec
	********************************************/
	tmp_int_ret = SAMPLE_COMM_AUDIO_CfgAcodec(&get_attribute().aio_attr);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_AUDIO_CfgAcodec() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_AUDIO_CfgAcodec() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}

	/********************************************
	step 2: start Ai
	********************************************/
	tmp_int_ret = SAMPLE_COMM_AUDIO_StartAi(get_attribute().dev_id
		, get_attribute().aio_attr.u32ChnCnt
		, &get_attribute().aio_attr
		, AUDIO_SAMPLE_RATE_BUTT
		, HI_FALSE
		, NULL
		, 0);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_AUDIO_StartAi() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_AUDIO_StartAi() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}

#endif

	return true;
}


/**
* 功能：
*    启动设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hiai::start_dev_large() {

#if defined(HI_BUILD_PLATFORM)

	HI_S32				i = 0;
	HI_S32				tmp_int_ret = 0;
	AIO_ATTR_S			tmp_aio_attr;


	memset(&tmp_aio_attr, 0, sizeof(tmp_aio_attr));
	//获取aio属性，判断是否已经启动过了。如果返回成功表示已经启动。
	tmp_int_ret = HI_MPI_AI_GetPubAttr(get_attribute().dev_id, &tmp_aio_attr);
	if (HI_ERR_AI_NOT_CONFIG != tmp_int_ret) {
		csf_log(warning
			, "HI_MPI_AI_GetPubAttr() attribute[dev:%d] succeed! hisystem ready start!"
			, get_attribute().dev_id);

		return true;
	}
	else {
		csf_log(notice, "HI_MPI_AI_GetPubAttr() succeed!");
	}

	//配置aio属性
	tmp_int_ret = HI_MPI_AI_SetPubAttr(get_attribute().dev_id, &tmp_aio_attr);
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_SetPubAttr() attribute[dev:%d | Bitwidth:%d | PtNumPerFrm:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_aio_attr.enBitwidth
			, tmp_aio_attr.u32PtNumPerFrm
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_SetPubAttr() attribute[dev:%d | Bitwidth:%d | PtNumPerFrm:%d] succeed!"
			, get_attribute().dev_id
			, tmp_aio_attr.enBitwidth
			, tmp_aio_attr.u32PtNumPerFrm);
	}

	//启动ai设备
	tmp_int_ret = HI_MPI_AI_Enable(get_attribute().dev_id);
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_Enable() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_Enable() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}

	//配置各个通道
	//for (i = 0; i < m_ai_attr.u32ChnCnt; i++) {
	for (i = 0; i < get_dev_channel_count(); i++) {
		//启动通道
		tmp_int_ret = HI_MPI_AI_EnableChn(get_attribute().dev_id, i);
		if (tmp_int_ret) {
			csf_log(error
				, "HI_MPI_AI_EnableChn() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
				, get_attribute().dev_id
				, i
				, tmp_int_ret);

			return false;
		}
		else {
			csf_log(notice
				, "HI_MPI_AI_EnableChn() attribute[dev:%d | channel:%d] succeed!"
				, get_attribute().dev_id
				, i);
		}

		//表示ai采样内容
		start_dev_resample(get_attribute().dev_id, i);

		//配置是否音频增强
		start_dev_vqe(get_attribute().dev_id, i);

		//设置音频音量信息
		set_dev_vqe_volume(get_attribute().dev_id, i, get_aiconf()->get_volume());
	}

#endif

	return true;
}


/**
 * 功能：
 *    启动设备重新采样处理
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiai::start_dev_resample(int id, int channel) {

#if defined(HI_BUILD_PLATFORM)

	HI_S32				tmp_int_ret;


	tmp_int_ret = HI_MPI_AI_DisableReSmp(id, channel);
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_DisableReSmp() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
			, id
			, channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_DisableReSmp() attribute[dev:%d | channel:%d] succeed!"
			, id
			, channel);
	}

	//配置是否重采样
	if (!get_aiconf()->isresample()) {
		return true;
	}

	tmp_int_ret |= HI_MPI_AI_EnableReSmp(id, channel, (AUDIO_SAMPLE_RATE_E)get_aiconf()->get_sample_rate());
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_EnableReSmp() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
			, id
			, channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_EnableReSmp() attribute[dev:%d | channel:%d] succeed!"
			, id
			, channel);
	}

#endif

	return true;
}


/**
 * 功能：
 *    启动设备质量增强功能。
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiai::start_dev_vqe(int id, int channel) {

#if defined(HI_BUILD_PLATFORM)

	HI_S32			tmp_int_ret;


	//配置是否音频增强
	if (!get_aiconf()->isuse_vqe()) {
		csf_log(notice
			, "HI_MPI_AI_SetVqeAttr() attribute[dev:%d | channel:%d] disable!"
			, id
			, channel);

		return true;
	}

#if 0
	//设置音频增强配置
	tmp_int_ret = HI_MPI_AI_SetVqeAttr(ai_dev_id, ai_channel, ao_dev_id, ao_channel, &m_ai_vqe_conf);
	if (tmp_int_ret) {
		write_log(PC_LOG_ERROR, PC_ERROR_MODULE_OPERATION,
			"HI_MPI_AI_SetVqeAttr() attribute[dev:%d | channel:%d] -- ao[dev:%d | channel:%d] workstate[%d] failed! error_code[0x%x]!!!",
			ai_dev_id,
			ai_channel,
			ao_dev_id,
			ao_channel,
			m_ai_vqe_conf.enWorkstate,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(PC_LOG_NOTICE, PC_NOTICE_MODULE_OPERATION,
			"HI_MPI_AI_SetVqeAttr() attribute[dev:%d | channel:%d] -- ao[dev:%d | channel:%d] workstate[%d] succeed!",
			ai_dev_id,
			ai_channel,
			ao_dev_id,
			ao_channel,
			m_ai_vqe_conf.enWorkstate);
	}
#endif

	//是否启动音频增强
	tmp_int_ret = HI_MPI_AI_EnableVqe(id, channel);
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_EnableVqe() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
			, id
			, channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_EnableVqe() attribute[dev:%d | channel:%d] disable!"
			, id
			, channel);
	}

#endif

	return true;
}


/**
* 功能：
*    设置设备的音量大小。
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param id    表示设备id
* @param channel    表示设备通道
* @param volume    表示音频音量大小数值
*/
bool csf_hiai::set_dev_vqe_volume(int id, int channel, int volume) {

#if defined(HI_BUILD_PLATFORM)

	HI_S32			tmp_int_ret;


	//设置音频增强配置
	tmp_int_ret = HI_MPI_AI_SetVqeVolume(id, channel, volume);
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_SetVqeVolume() attribute[dev:%d | channel:%d | volum:%d] failed! error_code[0x%x]!!!"
			, id
			, channel
			, volume
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_SetVqeVolume() attribute[dev:%d | channel:%d | volum:%d] succeed!"
			, id
			, channel
			, volume);
	}
#endif

	return true;
}


/**
 * 功能：
 *    停止设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiai::stop_dev() {

#if defined(HI_BUILD_PLATFORM)

	HI_S32				tmp_int_ret = 0;


	tmp_int_ret = SAMPLE_COMM_AUDIO_StopAi(get_attribute().dev_id
		, get_attribute().aio_attr.u32ChnCnt
		, HI_FALSE
		, HI_FALSE);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_AUDIO_StopAi() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_AUDIO_StopAi() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}

#endif

	return true;
}


/**
* 功能：
*    停止设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hiai::stop_dev_large() {

#if defined(HI_BUILD_PLATFORM)

	HI_S32				i = 0;
	HI_S32				tmp_int_ret = 0;


	//配置各个通道
	for (i = 0; i < get_dev_channel_count(); i++) {
		//关闭音频增强
		stop_dev_vqe(get_attribute().dev_id, i);

		//关闭重采样功能
		stop_dev_resample(get_attribute().dev_id, i);

		//不使用通道
		tmp_int_ret = HI_MPI_AI_DisableChn(get_attribute().dev_id, i);
		if (tmp_int_ret) {
			csf_log(error
				, "HI_MPI_AI_DisableChn() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
				, get_attribute().dev_id
				, i
				, tmp_int_ret);

			return false;
		}
		else {
			csf_log(notice
				, "HI_MPI_AI_DisableChn() attribute[dev:%d | channel:%d] succeed!"
				, get_attribute().dev_id
				, i);
		}
	}

	//停止ai设备
	tmp_int_ret = HI_MPI_AI_Disable(get_attribute().dev_id);
	if (tmp_int_ret) {
		csf_log(error
			, "HI_MPI_AI_Disable() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_AI_Disable() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}

#endif

	return true;
}


/**
 * 功能：
 *    停止设备重新采样处理
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiai::stop_dev_resample(int id, int channel) {

#if defined(HI_BUILD_PLATFORM)

	HI_S32			tmp_int_ret = 0;


	if (get_aiconf()->isresample()) {

		tmp_int_ret = HI_MPI_AI_DisableReSmp(id, channel);
		if (HI_SUCCESS != tmp_int_ret) {
			csf_log(error
				, "HI_MPI_AI_DisableReSmp() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
				, id
				, channel
				, tmp_int_ret);

			return false;
		}
	}

#endif

	return true;
}


/**
 * 功能：
 *    停止设备质量增强功能。
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param id    表示设备id
 * @param channel    表示设备通道
 */
bool csf_hiai::stop_dev_vqe(int id, int channel) {

#if defined(HI_BUILD_PLATFORM)

	HI_S32			tmp_int_ret = 0;


	if (get_aiconf()->isuse_vqe()) {

		tmp_int_ret = HI_MPI_AI_DisableVqe(id, channel);
		if (HI_SUCCESS != tmp_int_ret) {

			csf_log(error
				, "HI_MPI_AI_DisableVqe() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
				, id
				, channel
				, tmp_int_ret);

			return false;
		}
	}

#endif

	return true;
}


/**
 * 功能：
 *    初始化编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiai::init_coder() {

	return init_coder(get_attribute());
}


/**
* 功能：
*    初始化编码器参数
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param adev_attr    表示需要被初始化参数
*/
bool csf_hiai::init_coder(hi_adev_attribute& adev_attr) {

#if defined(HI_BUILD_PLATFORM)

	switch (adev_attr.payload_type) {
	case PT_ADPCMA:
	{
		adev_attr.aenc_attr.pValue = &adev_attr.aenc_adpcm;
		adev_attr.aenc_adpcm.enADPCMType = ADPCM_TYPE_DVI4;
		adev_attr.aio_attr.enBitwidth = AUDIO_BIT_WIDTH_16;
		adev_attr.aio_attr.u32PtNumPerFrm = 320;
	}
	break;
	case PT_G711A:
	case PT_G711U:
	{
		adev_attr.aenc_attr.pValue = &adev_attr.aenc_g711;
	}
	break;
	case PT_G726:
	{
		adev_attr.aenc_attr.pValue = &adev_attr.aenc_g726;
		adev_attr.aenc_g726.enG726bps = G726_16K;

		adev_attr.aio_attr.enBitwidth = AUDIO_BIT_WIDTH_16;
		adev_attr.aio_attr.u32PtNumPerFrm = 80;
	}
	break;
	case PT_LPCM:
	{
		adev_attr.aenc_attr.pValue = &adev_attr.aenc_lpcm;
	}
	break;
#ifdef HISIV_AAC
	case PT_AAC:
	{
		adev_attr.aenc_attr.u32BufSize = 30;
		adev_attr.aenc_attr.pValue = &adev_attr.aenc_aac;
		adev_attr.aenc_attr.u32PtNumPerFrm = 1024;

		adev_attr.aenc_aac.enAACType = AAC_TYPE_AACLC;
		adev_attr.aenc_aac.enBitRate = AAC_BPS_64K;
		adev_attr.aenc_aac.enBitWidth = AUDIO_BIT_WIDTH_16;
		adev_attr.aenc_aac.enSmpRate = AUDIO_SAMPLE_RATE_44100;
		adev_attr.aenc_aac.enSoundMode = AUDIO_SOUND_MODE_MONO;
		adev_attr.aenc_aac.enTransType = AAC_TRANS_TYPE_ADTS;
		adev_attr.aenc_aac.s16BandWidth = 0;
	}
	break;
#endif
	default:
	{
		csf_log(error
			, "unknow aenc[Type:%d Bitwidth:%d PtNumPerFrm:%d]"
			, adev_attr.aenc_attr.enType
			, adev_attr.aio_attr.enBitwidth
			, adev_attr.aio_attr.u32PtNumPerFrm);

		return false;
	}
	break;
	}

	csf_log(notice
		, "set aenc[Type:%d Bitwidth:%d PtNumPerFrm:%d] succeed!"
		, adev_attr.aenc_attr.enType
		, adev_attr.aio_attr.enBitwidth
		, adev_attr.aio_attr.u32PtNumPerFrm);

#endif

	return true;
}


/**
 * 功能：
 *    启动编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiai::start_coder() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32				tmp_int_ret = 0;


	/********************************************
	step 3: start Aenc
	********************************************/
	tmp_int_ret = SAMPLE_COMM_AUDIO_StartAenc(get_coder_channel_count()
		, get_attribute().aio_attr.u32PtNumPerFrm
		, get_attribute().payload_type);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_AUDIO_StartAenc() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_AUDIO_StartAenc() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}

	//启动处理线程
	return start_coder_thread(this);

#endif

	return true;
}


/**
* 功能：
*    启动编解码器
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hiai::start_coder_large() {

#if defined(HI_BUILD_PLATFORM)
	AENC_CHN			tmp_aenc_chn = get_attribute().coder_channel;
	HI_S32				i = 0;
	HI_S32				tmp_int_ret = 0;


	//配置各个通道
	for (i = 0; i < get_coder_channel(); i++) {

		tmp_aenc_chn = i;

		//创建编码通道
		tmp_int_ret = HI_MPI_AENC_CreateChn(tmp_aenc_chn, &get_attribute().aenc_attr);
		if (HI_SUCCESS != tmp_int_ret) {
			csf_log(error
				, "HI_MPI_AENC_CreateChn() attribute[channel:%d] failed! error_code[0x%x]!!!"
				, get_attribute().coder_channel
				, tmp_int_ret);

			return false;
		}
		else {
			csf_log(notice
				, "HI_MPI_AENC_CreateChn() attribute[channel:%d] succeed!"
				, get_attribute().coder_channel);
		}

		//启动处理线程
		return start_coder_thread(this);
	}
#endif

	return true;
}


/**
 * 功能：
 *    启动编解码处理线程
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param hichannel    表示当前的csf_hiadev设备对象指针
 */
bool csf_hiai::start_coder_thread(csf_hiadev* hichannel) {

#if defined(HI_BUILD_PLATFORM)
	bool				tmp_bool_ret = false;


	//绑定ai和aenc内容
	tmp_bool_ret = bind_dev_coder(get_attribute().dev_id
		, get_attribute().dev_channel
		, get_attribute().coder_channel);
	if (!tmp_bool_ret) {
		csf_log(error, "bind_dev_coder() failed!");
		return false;
	}

	//创建线程
	set_thread(new csf_thread(csf_bind(&csf_hiai::coder_thread_process, this, this)));

	csf_log(notice, "create thread[%p] succeed!", get_thread());
#endif

#if WIN32
	//创建线程
	set_thread(new csf_thread(csf_bind(&csf_hiai::test_coder_thread_process, this, this)));

	csf_log(notice, "create thread[%p] succeed!", get_thread());

#endif

	return true;
}


/**
 * 功能：
 *    编解码线程处理函数
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param hichannel    表示当前的csf_hiadev设备对象指针
 */
bool csf_hiai::coder_thread_process(csf_hiadev* hichannel) {

#if defined(HI_BUILD_PLATFORM)
	bool				tmp_bool_ret = false;
	HI_S32				tmp_int_ret = 0;
	fd_set				tmp_read_fds;
	HI_S32				tmp_fds = 0;
	struct timeval		tmp_timeout_val = { 0, };
	AUDIO_STREAM_S		tmp_stream = { 0, };
	csf_hiobject		*tmp_object = NULL;
	csf_mdslot_cover	*tmp_mdslot = dynamic_cast<csf_mdslot_cover*>(get_mdpipe().get_mdslot());
	csf_hipool			*tmp_hipool = dynamic_cast<csf_hipool*>(get_mdpipe().get_mdpool());


	FD_ZERO(&tmp_read_fds);
	tmp_fds = HI_MPI_AENC_GetFd(get_attribute().coder_channel);
	FD_SET(tmp_fds, &tmp_read_fds);

	while (get_thread()->is_start())
	{
		tmp_timeout_val.tv_sec = 2;
		tmp_timeout_val.tv_usec = 0;

		FD_ZERO(&tmp_read_fds);
		FD_SET(tmp_fds, &tmp_read_fds);

		tmp_int_ret = select(tmp_fds + 1, &tmp_read_fds, NULL, NULL, &tmp_timeout_val);
		if (tmp_int_ret < 0) {
			csf_log(error
				, "select() attribute[channel:%d] failed! return[%d]!!!"
				, get_attribute().coder_channel
				, tmp_int_ret);
			break;
		}
		else if (0 == tmp_int_ret) {
			csf_log(warning
				, "get aenc stream time out [%d s]. select() attribute[channel:%d] warning!"
				, tmp_timeout_val.tv_sec
				, get_attribute().coder_channel);
			continue;
		}

		if (FD_ISSET(tmp_fds, &tmp_read_fds)) {

			/* get frame from encoder */
			tmp_int_ret = HI_MPI_AENC_GetStream(get_attribute().coder_channel, &tmp_stream, -1);
			if (HI_SUCCESS != tmp_int_ret) {

				csf_log(error
					, "HI_MPI_AENC_GetStream() attribute[channel:%d] failed! error_code[0x%x]!!!"
					, get_attribute().coder_channel
					, tmp_int_ret);
				break;
			}

			/************************************************************************/
			/* 将数据发送到媒体数据槽中，满足处理需求。                                 */
			/************************************************************************/
			tmp_object = static_cast<csf_hiobject*>(tmp_hipool->create(tmp_stream.u32Len));
			if (tmp_object) {
				tmp_object->cat(tmp_stream.pStream
					, tmp_stream.u32Len
					, tmp_stream.u64TimeStamp
					, tmp_stream.u32Seq
				);
				if (tmp_mdslot->isfull()) {
					csf_log(error
						, "audio hichannel[%p] mdslot is full!!!"
						, this);
				}
				tmp_mdslot->push_frame(tmp_object);
			}

			/* finally you must release the stream */
			tmp_int_ret = HI_MPI_AENC_ReleaseStream(get_attribute().coder_channel, &tmp_stream);
			if (HI_SUCCESS != tmp_int_ret) {
				csf_log(error
					, "HI_MPI_AENC_ReleaseStream() attribute[channel:%d] failed! error_code[0x%x]!!!"
					, get_attribute().coder_channel
					, tmp_int_ret);
				break;
			}
		}
	}

	//设置停止标记，停止线程
	get_thread()->stop();

	//绑定ai和aenc内容
	tmp_bool_ret = unbind_dev_coder(get_attribute().dev_id
		, get_attribute().dev_channel
		, get_attribute().coder_channel);
	if (!tmp_bool_ret) {
		csf_log(error
			, "unbind_dev_coder() attribute[channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().coder_channel
			, tmp_int_ret);
		return false;
	}
	else {
		csf_log(notice
			, "unbind_dev_coder() attribute[channel:%d] succeed!"
			, get_attribute().coder_channel);
	}

	csf_log(warning, "stop thread[%p] succeed!", get_thread());

#endif

	return true;
}


/**
* 功能：
*    测试编解码线程处理函数
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param hichannel    表示当前的csf_hiadev设备对象指针
*/
bool csf_hiai::test_coder_thread_process(csf_hiadev* hichannel) {

	csf_hiobject			*tmp_object = NULL;
	csf_mdslot				*tmp_mdslot = get_mdpipe().get_mdslot();
	csf_hipool				*tmp_hipool = dynamic_cast<csf_hipool*>(get_mdpipe().get_mdpool());
	unsigned char			sps[] = { 0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x2a, 0x96, 0x35, 0xc0, 0xf0, 0x04, 0x4f, 0xcb, 0x37, 0x01, 0x01, 0x01, 0x02 };
	unsigned char			pps[] = { 0x00, 0x00, 0x00, 0x01, 0x68, 0xce, 0x3c, 0x80, 0x00, 0x00, 0x00, 0x01, 0x06, 0xe5, 0x01, 0xa1, 0x80 };


	tmp_object = static_cast<csf_hiobject*>(tmp_hipool->create(sizeof(sps)));
	if (tmp_object) {
		tmp_object->cat(sps
			, sizeof(sps)
			, 0
			, 0
		);
		tmp_mdslot->push_frame(tmp_object);
	}
	tmp_object = static_cast<csf_hiobject*>(tmp_hipool->create(sizeof(pps)));
	if (tmp_object) {
		tmp_object->cat(pps
			, sizeof(pps)
			, 0
			, 0
		);
		tmp_mdslot->push_frame(tmp_object);
	}

	//如果没有视频，则休眠等待
	csf::core::utils::time::sleep_time::sleep_ms(1000);
	csf_log(warning, "insert a test object");

	return true;
}

/**
 * 功能：
 *    绑定设备和编码器设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param id    表示设备id
 * @param channel    表示设备通道
 * @param coder_channel    表示编码器设备通道
 */
bool csf_hiai::bind_dev_coder(int id, int channel, int coder_channel) {

#if defined(HI_BUILD_PLATFORM)

	MPP_CHN_S			tmp_src_chn;
	MPP_CHN_S			tmp_dest_chn;
	HI_S32				tmp_int_ret = 0;


	tmp_src_chn.enModId = HI_ID_AI;
	tmp_src_chn.s32DevId = id;
	tmp_src_chn.s32ChnId = channel;
	tmp_dest_chn.enModId = HI_ID_AENC;
	tmp_dest_chn.s32DevId = 0;
	tmp_dest_chn.s32ChnId = coder_channel;

	tmp_int_ret = HI_MPI_SYS_Bind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_Bind() attribute[dev:%d | dev_channel:%d | coder_channel:%d] failed! error_code[0x%x]!!!"
			, id
			, channel
			, coder_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_Bind() attribute[dev:%d | dev_channel:%d | coder_channel:%d] succeed!"
			, id
			, channel
			, coder_channel);
	}

#endif

	return true;
}


/**
 * 功能：
 *    解除绑定设备和编码器设备
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param id    表示设备id
 * @param channel    表示设备通道
 * @param coder_channel    表示编码器设备通道
 */
bool csf_hiai::unbind_dev_coder(int id, int channel, int coder_channel) {

#if defined(HI_BUILD_PLATFORM)

	MPP_CHN_S			tmp_src_chn;
	MPP_CHN_S			tmp_dest_chn;
	HI_S32				tmp_int_ret = 0;



	tmp_src_chn.enModId = HI_ID_AI;
	tmp_src_chn.s32DevId = id;
	tmp_src_chn.s32ChnId = channel;
	tmp_dest_chn.enModId = HI_ID_AENC;
	tmp_dest_chn.s32DevId = 0;
	tmp_dest_chn.s32ChnId = coder_channel;

	tmp_int_ret = HI_MPI_SYS_UnBind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_UnBind() attribute[dev:%d | dev_channel:%d | coder_channel:%d] failed! error_code[0x%x]!!!"
			, id
			, channel
			, coder_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_UnBind() attribute[dev:%d | dev_channel:%d | coder_channel:%d] succeed!"
			, id
			, channel
			, coder_channel);
	}
#endif

	return true;
}


/**
 * 功能：
 *    停止编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hiai::stop_coder() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32				tmp_int_ret = 0;


	tmp_int_ret = SAMPLE_COMM_AUDIO_StopAenc(get_coder_channel_count());
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_AUDIO_StopAenc() attribute[dev:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_AUDIO_StopAenc() attribute[dev:%d] succeed!"
			, get_attribute().dev_id);
	}
#endif

	return true;
}


/**
* 功能：
*    停止编解码器
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hiai::stop_coder_large() {

	//stop_coder_thread(this);
#if defined(HI_BUILD_PLATFORM)
	AENC_CHN			tmp_aenc_chn = get_attribute().coder_channel;
	HI_S32				i = 0;
	HI_S32				tmp_int_ret = 0;


	stop_coder_thread(this);

	//配置各个通道
	for (i = 0; i < get_coder_channel(); i++) {

		tmp_aenc_chn = i;

		//创建编码通道
		tmp_int_ret = HI_MPI_VENC_DestroyChn(tmp_aenc_chn);
		if (HI_SUCCESS != tmp_int_ret) {
			csf_log(error
				, "HI_MPI_VENC_DestroyChn() attribute[channel:%d] failed! error_code[0x%x]!!!"
				, get_attribute().coder_channel
				, tmp_int_ret);

			//return false;
		}
		else {
			csf_log(notice
				, "HI_MPI_VENC_DestroyChn() attribute[channel:%d] succeed!"
				, get_attribute().coder_channel);
		}
	}
#endif

	return true;
}



/**
 * 功能：
 *    停止编解码处理线程
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 *
 * @param hichannel    表示当前的csf_hiadev设备对象指针
 */
bool csf_hiai::stop_coder_thread(csf_hiadev* hichannel) {

	if (get_thread()) {
		get_thread()->stop();
	}

	return true;
}