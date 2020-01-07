/*******************************************************************************
*
*Copyright:compony
*
*File name: hi3531a_audio.cpp
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/08
*
*Description: create (hi3531a_audio.cpp)
*
*Others:
*
*History:
*******************************************************************************/

#include "hi3531a_audio.h"
#include "hi3531a_audio_thread_info.h"



#define		HI3531A_AUDIO_FRAME_SLEEP_INTERVAL_NS			5000000											//表示没有媒体流时，等待休眠的时间,单位为纳秒(ns)
#define		HI3531A_AUDIO_SEC_TO_NSEC						1000000000LL									//表示1秒所包含的纳秒
#define		HI3531A_AUDIO_SEC_TO_MSEC						1000LL											//表示1秒所包含的毫秒
#define		HI3531A_AUDIO_MSEC_TO_NSEC						1000000LL										//表示1毫秒所包含的纳秒
#define		HI3531A_AUDIO_THREAD_JOIN_TIME_MS				5000											//表示线程退出等待时间，单位秒

#define		HI3531A_AUDIO_SYS_ALIGN_WIDTH					16


//定义设备信息
#define		HI3531A_AUDIO_TW2865_FILE						"/dev/tw2865dev"
#define		HI3531A_AUDIO_TP2823_FILE						"/dev/tp2823dev"
#define		HI3531A_AUDIO_TLV320_FILE						"/dev/tlv320aic31"
#define		HI3531A_AUDIO_AENC_SAVE_FILE					"./aenc_file_data"
#define		HI3531A_AUDIO_ADEC_SAVE_FILE					"./adec_file_data"


hi3531a_audio_class::hi3531a_audio_class()
{
#if defined(HI3531A_MODE)

	//系统配置
	//////////////////////////////////////////////////////////////////////////
	memset(&m_sys_conf, 0, sizeof(m_sys_conf));
	memset(&m_vb_conf, 0, sizeof(m_vb_conf));



	m_sys_conf.u32AlignWidth = CSS_DEV_IO_AERO_ANALYZER_SYS_ALIGN_WIDTH;

	//音频配置
	//////////////////////////////////////////////////////////////////////////
	m_ai_dev = 2;
	m_ai_chn = 0;
	m_ao_dev = 0;
	m_ao_chn = 0;
	m_adec_chn = 0;
	m_aenc_chn = 0;

	m_adec_channel_count = 1;
	m_aenc_channel_count = 1;

	m_ai_volume = 0;
	m_ao_volume = 4;

	/************************************************************************/
	/* 音频采样率（从模式下，此参数不起作用）。
		静态属性。                                                           */
		/************************************************************************/
	m_ai_attr.enSamplerate = AUDIO_SAMPLE_RATE_8000;

	/************************************************************************/
	/* 音频采样精度（从模式下，此参数必须和音频AD/DA 的采样精
		度匹配）。
		静态属性。                                                           */
		/************************************************************************/
	m_ai_attr.enBitwidth = AUDIO_BIT_WIDTH_16;
	//m_ai_attr.enBitwidth = AUDIO_BIT_WIDTH_8;

	/************************************************************************/
	/* 音频输入输出工作模式。
		静态属性。                                                           */
		/************************************************************************/
	m_ai_attr.enWorkmode = AIO_MODE_I2S_SLAVE;
	//m_ai_attr.enWorkmode = AIO_MODE_PCM_MASTER_STD;

	/************************************************************************/
	/* 音频声道模式。
		静态属性。                                                           */
		/************************************************************************/
	m_ai_attr.enSoundmode = AUDIO_SOUND_MODE_MONO;

	/************************************************************************/
	/* 8bit 到16bit 扩展标志（只对AI采样精度为8bit 时有效）。
		取值范围：{0, 1}。
		 0：不扩展。
		 1：扩展。
		静态属性。                                                           */
		/************************************************************************/
	m_ai_attr.u32EXFlag = 1;

	/************************************************************************/
	/* 缓存帧数目。
		取值范围：[2, MAX_AUDIO_FRAME_NUM]。
		静态属性。                                                           */
		/************************************************************************/
	m_ai_attr.u32FrmNum = 30;

	/************************************************************************/
	/* 每帧的采样点个数。
		取值范围：G711、G726、ADPCM_DVI4编码时取值为80、
		160、240、320、480；ADPCM_IMA编码时取值为81、161、
		241、321、481。
		AI取值范围为：[80, 2048]，AO取值范围为：[80, 4096]。
		静态属性。                                                           */
		/************************************************************************/
	//m_ai_attr.u32PtNumPerFrm = 320;
	m_ai_attr.u32PtNumPerFrm = 160;

	/************************************************************************/
	/* 支持的时钟分频通道数目，即决定了codec 到AIO的I2S/PCM
		时序（时分复用关系），取值范围1、2、4、8、16、20（最大取
		值为AIO_MAX_CHN_NUM）。与对接的codec和u32ChnCnt 相
		关，要求u32ClkChnCnt大于等于u32ChnCnt。                               */
		/************************************************************************/
		//m_ai_attr.u32ClkChnCnt = AIO_MAX_CHN_NUM;
	m_ai_attr.u32ClkChnCnt = AIO_MAX_CHN_NUM;

	/************************************************************************/
	/* 支持的通道数目，实际可使能的最大通道数。
		取值：1、2、4、8、16、20。（输入最多支持
		AIO_MAX_CHN_NUM 个通道，输出最多支持2 个通道）                         */
		/************************************************************************/
		//m_ai_attr.u32ChnCnt = AIO_MAX_CHN_NUM;
	m_ai_attr.u32ChnCnt = 1;

	/************************************************************************/
	/* 配置AI设备是否复用AO设备的帧同步时钟及位流时钟。
		取值：0、1。
		0：不复用；
		1：复用。                                                            */
		/************************************************************************/
	m_ai_attr.u32ClkSel = 0;

	m_ao_attr = m_ai_attr;
	//m_ao_attr.u32ClkChnCnt = AIO_MAX_CHN_NUM;
	m_ao_attr.u32ClkChnCnt = 2;

	//编码属性
	memset(&m_aenc_attr, 0, sizeof(m_aenc_attr));
	memset(&m_aenc_adpcm_attr, 0, sizeof(m_aenc_adpcm_attr));
	memset(&m_aenc_g711_attr, 0, sizeof(m_aenc_g711_attr));
	memset(&m_aenc_g726_attr, 0, sizeof(m_aenc_g726_attr));
	memset(&m_aenc_lpcm_attr, 0, sizeof(m_aenc_lpcm_attr));
	//m_aenc_attr.enType = PT_G711A;
	//m_aenc_attr.enType = PT_ADPCMA;
	m_aenc_attr.enType = PT_G726;
	m_aenc_attr.u32PtNumPerFrm = m_ai_attr.u32PtNumPerFrm;
	m_aenc_attr.u32BufSize = m_ai_attr.u32FrmNum;

	//解码属性
	memset(&m_adec_attr, 0, sizeof(m_adec_attr));
	memset(&m_adec_adpcm_attr, 0, sizeof(m_adec_adpcm_attr));
	memset(&m_adec_g711_attr, 0, sizeof(m_adec_g711_attr));
	memset(&m_adec_g726_attr, 0, sizeof(m_adec_g726_attr));
	memset(&m_adec_lpcm_attr, 0, sizeof(m_adec_lpcm_attr));
	m_adec_attr.enType = m_aenc_attr.enType;
	m_adec_attr.u32BufSize = m_ai_attr.u32FrmNum;
	//m_adec_attr.enMode = ADEC_MODE_STREAM;
	m_adec_attr.enMode = ADEC_MODE_PACK;

	//音频增强的配置
	memset(&m_ai_vqe_conf, 0, sizeof(m_ai_vqe_conf));

	//重采样频率
	m_out_resample_rate = AUDIO_SAMPLE_RATE_16000;
#endif
	m_is_init_system = true;

	m_is_ai_resample = false;
	m_is_ao_resample = false;

	m_is_ai_used_vqe = false;
	m_is_ao_used_vqe = false;

	m_aenc_file = NULL;
	m_adec_file = NULL;
}

hi3531a_audio_class::~hi3531a_audio_class()
{

}

bool hi3531a_audio_class::init()
{
	bool						tmp_bool_ret = false;



	if (m_is_init_system)
	{
		/************************************************************************/
		/* 这里需要说明：
		之所以使用hi3531a_hifb的原因是音视部分都需要使用sys_init，通过测试发现sys_init部分内容不能分开初始化；
		该部分内容是需要继续优化的
		*/
		/************************************************************************/
#ifndef HI3531A_HIFB
		//初始化sys_init
		tmp_bool_ret = sys_init();
		if (!tmp_bool_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "sys_init() failed!");
			return tmp_bool_ret;
		}
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "sys_init() successed!");
#else
		//使用start_hi3531a_hifb初始化系统，同时启动hifb设备，满足画面显示需求
		tmp_bool_ret = start_hi3531a_hifb();
		if (!tmp_bool_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "start_hi3531a_hifb() failed!");
			return tmp_bool_ret;
		}
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "start_hi3531a_hifb() successed!");
#endif // !HI3531A_HIFB
	}

	//初始化ai
	tmp_bool_ret = init_ai();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "init_ai() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "init_ai() successed!");

	//初始化ao
	tmp_bool_ret = init_ao();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "init_ao() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "init_ao() successed!");

	//初始化init_aenc
	tmp_bool_ret = init_aenc();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "init_aenc() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "init_aenc() successed!");

	//初始化init_adec
	tmp_bool_ret = init_adec();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "init_adec() failed!");
		return tmp_bool_ret;
	}
	//write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "init_adec() successed!");

#ifdef AUDIO_SAVE_FILE
	//初始化编码init_file
	m_aenc_file = open_file(HI3531A_AUDIO_AENC_SAVE_FILE);
	if (!m_aenc_file) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open_file() [%s] failed!", HI3531A_AUDIO_AENC_SAVE_FILE);
		return false;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
		"open_file() [%s] successed!", HI3531A_AUDIO_AENC_SAVE_FILE);

	//初始化解码init_file
	m_adec_file = open_file(HI3531A_AUDIO_ADEC_SAVE_FILE);
	if (!m_adec_file) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open_file() [%s] failed!", HI3531A_AUDIO_ADEC_SAVE_FILE);
		return false;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
		"open_file() [%s] successed!", HI3531A_AUDIO_ADEC_SAVE_FILE);

#endif

	return true;
}

bool hi3531a_audio_class::start()
{
	bool						tmp_bool_ret = false;




	//初始化ai
	tmp_bool_ret = start_ai();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "start_ai() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "start_ai() successed!");

	//初始化ao
	tmp_bool_ret = start_ao();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "start_ao() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "start_ao() successed!");

	//初始化start_adec
	tmp_bool_ret = start_adec();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "start_adec() failed!");
		return tmp_bool_ret;
	}
	//write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "start_adec() successed!");

	//初始化start_aenc
	tmp_bool_ret = start_aenc();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "start_aenc() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "start_aenc() successed!");

	return true;
}

bool hi3531a_audio_class::stop()
{
	bool						tmp_bool_ret = false;



	//初始化ai
	tmp_bool_ret = stop_ai();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "stop_ai() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "stop_ai() successed!");

	//初始化ao
	tmp_bool_ret = stop_ao();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "stop_ao() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "stop_ao() successed!");

	//设置停止标志
	set_stop_thread_flag();

	//初始化stop_aenc
	tmp_bool_ret = stop_aenc();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "stop_aenc() failed!");
		return tmp_bool_ret;
	}
	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "stop_aenc() successed!");

	//初始化stop_adec
	tmp_bool_ret = stop_adec();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "stop_adec() failed!");
		return tmp_bool_ret;
	}
	//write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "stop_adec() successed!");

#ifdef AUDIO_SAVE_FILE
	//关闭文件
	close_file(m_aenc_file);
	close_file(m_adec_file);
#endif

	/************************************************************************/
	/* 这里需要说明：
		之所以使用hi3531a_hifb的原因是音视部分都需要使用sys_init，通过测试发现sys_init部分内容不能分开初始化；
		该部分内容是需要继续优化的
		*/
	/************************************************************************/
#ifndef HI3531A_HIFB
	if (m_is_init_system)
	{
		sys_exit();
	}
#else
	if (m_is_init_system)
	{
		stop_hi3531a_hifb();
	}
#endif
	return true;
}

bool hi3531a_audio_class::sys_init()
{
#if defined(HI3531A_MODE)
	HI_S32				tmp_int_ret = false;



	sys_exit();

	m_vb_conf.u32MaxPoolCnt = 128;
	m_vb_conf.astCommPool[1].u32BlkSize = 10240;
	m_vb_conf.astCommPool[1].u32BlkCnt = 64;
	m_vb_conf.astCommPool[2].u32BlkSize = 1024;
	m_vb_conf.astCommPool[3].u32BlkCnt = 64;

	tmp_int_ret = HI_MPI_VB_SetConf(&m_vb_conf);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VB_SetConf() failed! error_code[0x%x].", tmp_int_ret);

		return false;
	}

	tmp_int_ret = HI_MPI_VB_Init();
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VB_Init failed! error_code[0x%x].", tmp_int_ret);
		return false;
	}

	tmp_int_ret = HI_MPI_SYS_SetConf(&m_sys_conf);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_SYS_SetConf() failed! error_code[0x%x].", tmp_int_ret);
		return false;
	}

	tmp_int_ret = HI_MPI_SYS_Init();
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_SYS_Init() failed! error_code[0x%x].", tmp_int_ret);
		return false;
	}

#endif

	return true;
}

bool hi3531a_audio_class::sys_exit()
{
#if defined(HI3531A_MODE)
	HI_S32					i = 0;



	HI_MPI_SYS_Exit();

#if 0
	for (i = 0; i < VB_MAX_USER; i++) {
		HI_MPI_VB_ExitModCommPool((VB_UID_E)i);
	}

	for (i = 0; i < VB_MAX_POOLS; i++) {
		HI_MPI_VB_DestroyPool(i);
	}

	HI_MPI_VB_Exit();
#endif

#endif

	return true;
}

#ifdef HI3531A_HIFB
/*******************************************************************************
* 版权所有: fz & compony
*
* 函数名称: start_hi3531a_hifb
*
* 函数全名: dev_aero_bus_analyzer_class::start_hi3531a_hifb
*
* 函数访问: private
*
* 函数说明: 表示启动hi3531a_hifb设备
*
*
* 返 回 值: bool
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@compony.com.cn
* 创建日期：2018-5-28 17:12:37
********************************************************************************/
bool	hi3531a_audio_class::start_hi3531a_hifb()
{
	bool							tmp_bool_ret = false;



	tmp_bool_ret = m_hi3531a_hifb.init();
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"hi3531a_hifb() init() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"hi3531a_hifb() init() successed!");
	}

	tmp_bool_ret = m_hi3531a_hifb.start();
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"hi3531a_hifb() start() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"hi3531a_hifb() start() successed!");
	}

	return true;
}

/*******************************************************************************
* 版权所有: fz & compony
*
* 函数名称: stop_hi3531a_hifb
*
* 函数全名: dev_aero_bus_analyzer_class::stop_hi3531a_hifb
*
* 函数访问: private
*
* 函数说明: 表示停止hi3531a_hifb设备
*
*
* 返 回 值: bool
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@compony.com.cn
* 创建日期：2018-5-28 17:12:56
********************************************************************************/
bool	hi3531a_audio_class::stop_hi3531a_hifb()
{
	bool							tmp_bool_ret = false;



	tmp_bool_ret = m_hi3531a_hifb.stop();
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"hi3531a_hifb() stop() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"hi3531a_hifb() stop() successed!");
	}

	return true;
}
#endif

bool hi3531a_audio_class::init_ai()
{
#if defined(HI3531A_MODE)
	HI_S32								tmp_int_ret = 0;



	//获取aio属性，判断是否已经启动过了。如果返回成功表示已经启动。
	tmp_int_ret = set_audio_acodec(&m_ai_attr);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"set_audio_acodec() failed!");

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"set_audio_acodec() successed!");
	}

	//使用AI的声音质量增强功能
	m_is_ai_used_vqe = true;

	m_ai_vqe_conf.s32WorkSampleRate = m_ai_attr.enSamplerate;
	m_ai_vqe_conf.s32FrameSample = m_ai_attr.u32PtNumPerFrm;
	m_ai_vqe_conf.enWorkstate = VQE_WORKSTATE_NOISY;
	//m_ai_vqe_conf.enWorkstate = VQE_WORKSTATE_COMMON;

	//高通滤波
	m_ai_vqe_conf.bHpfOpen = HI_TRUE;
	m_ai_vqe_conf.stHpfCfg.bUsrMode = HI_FALSE;
	m_ai_vqe_conf.stHpfCfg.enHpfFreq = AUDIO_HPF_FREQ_150;

	//回声抵消
	m_ai_vqe_conf.bAecOpen = HI_TRUE;
	m_ai_vqe_conf.stAecCfg.bUsrMode = HI_FALSE;
	m_ai_vqe_conf.stAecCfg.s8CngMode = HI_TRUE;
	m_ai_vqe_conf.stAecCfg.s8NearAllPassEnergy = 1;
	m_ai_vqe_conf.stAecCfg.s8NearCleanSupEnergy = 2;
	m_ai_vqe_conf.stAecCfg.s16DTHnlSortQTh = 16384;
	m_ai_vqe_conf.stAecCfg.s16EchoBandLow = 10;
	m_ai_vqe_conf.stAecCfg.s16EchoBandHigh = 41;
	m_ai_vqe_conf.stAecCfg.s16EchoBandLow2 = 47;
	m_ai_vqe_conf.stAecCfg.s16EchoBandHigh2 = 63;
	//m_ai_vqe_conf.stAecCfg.s16ERLBand[6] = { 4, 6, 36, 49, 49, 49 };
	//m_ai_vqe_conf.stAecCfg.s16ERL[7] = { 7, 10, 16, 10, 18, 18, 18 };
	m_ai_vqe_conf.stAecCfg.s16VioceProtectFreqL = 3;
	m_ai_vqe_conf.stAecCfg.s16VioceProtectFreqL1 = 6;

	//语音降噪
	m_ai_vqe_conf.bAnrOpen = HI_TRUE;
	m_ai_vqe_conf.stAnrCfg.bUsrMode = HI_FALSE;

	//录音噪声消除
	//m_ai_vqe_conf.bRnrOpen = HI_TRUE;
	//m_ai_vqe_conf.stRnrCfg.bUsrMode = HI_FALSE;

#endif
	return true;
}

#if defined(HI3531A_MODE)
/* config codec  AcodecType: 0-inner 1-AIC31 2-HDMI 3-TW2865 */
HI_S32 hi3531a_audio_class::set_audio_acodec(AIO_ATTR_S *aio_attr)
{
	HI_S32						tmp_int_ret = HI_SUCCESS;
	HI_BOOL						tmp_bool_codec = HI_FALSE;

#ifdef HI_ACODEC_TYPE_TLV320AIC31 

	/*** ACODEC_TYPE_TLV320 ***/
	tmp_int_ret = set_audio_tlv320_acodec(aio_attr->enWorkmode, aio_attr->enSamplerate);
	if (HI_SUCCESS != tmp_int_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"set_audio_tlv320_acodec() failed!");
		return tmp_int_ret;
	}
	tmp_bool_codec = HI_TRUE;
#endif

#ifdef HI_ACODEC_TYPE_TW2865

	/*** ACODEC_TYPE_TW2865 ***/
	tmp_int_ret = set_audio_tw2865_acodec(aio_attr->enSamplerate);
	tmp_int_ret |= set_audio_tw2865_format(aio_attr->enWorkmode);
	tmp_int_ret |= set_audio_tw2865_bit_width(aio_attr->enBitwidth);
	tmp_bool_codec = HI_TRUE;
#endif

#ifdef HI_ACODEC_TYPE_TP2823

	/*** ACODEC_TYPE_TP2823 ***/
	tmp_int_ret = set_audio_tp2823_format(aio_attr);
	tmp_bool_codec = HI_TRUE;
#endif

	if (!tmp_bool_codec)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"input wrong codec type!");
		return HI_FALSE;
	}
	return tmp_int_ret;
}

HI_S32 hi3531a_audio_class::set_audio_tlv320_acodec(AIO_MODE_E work_mode, AUDIO_SAMPLE_RATE_E sample)
{
	HI_S32						tmp_sample_rate;
	HI_S32						tmp_vol = 0x100;
	Audio_Ctrl					tmp_audio_ctrl;
	int							tmp_fd_tlv = -1;
	HI_BOOL						tmp_pcm_mode = HI_FALSE;
	HI_BOOL						tmp_master = HI_TRUE;      /* master mode for Tlv320aic31 */
	HI_BOOL						tmp_pcm_std = HI_FALSE;
	HI_BOOL						tmp_44100hz_series = HI_FALSE;



	if (AUDIO_SAMPLE_RATE_8000 == sample)
	{
		tmp_sample_rate = AC31_SET_8K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_12000 == sample)
	{
		tmp_sample_rate = AC31_SET_12K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_11025 == sample)
	{
		tmp_44100hz_series = HI_TRUE;
		tmp_sample_rate = AC31_SET_11_025K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_16000 == sample)
	{
		tmp_sample_rate = AC31_SET_16K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_22050 == sample)
	{
		tmp_44100hz_series = HI_TRUE;
		tmp_sample_rate = AC31_SET_22_05K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_24000 == sample)
	{
		tmp_sample_rate = AC31_SET_24K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_32000 == sample)
	{
		tmp_sample_rate = AC31_SET_32K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_44100 == sample)
	{
		tmp_44100hz_series = HI_TRUE;
		tmp_sample_rate = AC31_SET_44_1K_SAMPLERATE;
	}
	else if (AUDIO_SAMPLE_RATE_48000 == sample)
	{
		tmp_sample_rate = AC31_SET_48K_SAMPLERATE;
	}
	else
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"not support sample[%d]", sample);
		return -1;
	}

	if (AIO_MODE_I2S_MASTER == work_mode)
	{
		tmp_pcm_mode = HI_FALSE;
		tmp_master = HI_FALSE;
	}
	else if (AIO_MODE_I2S_SLAVE == work_mode)
	{
		tmp_pcm_mode = HI_FALSE;
		tmp_master = HI_TRUE;
	}
	else if ((AIO_MODE_PCM_MASTER_NSTD == work_mode) || (AIO_MODE_PCM_MASTER_STD == work_mode))
	{
		tmp_pcm_mode = HI_TRUE;
		tmp_master = HI_FALSE;
	}
	else if ((AIO_MODE_PCM_SLAVE_NSTD == work_mode) || (AIO_MODE_PCM_SLAVE_STD == work_mode))
	{
		tmp_pcm_mode = HI_TRUE;
		tmp_master = HI_TRUE;
	}
	else
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"not support workmode[%d]", work_mode);
	}

	tmp_fd_tlv = open(HI3531A_AUDIO_TLV320_FILE, O_RDWR);
	if (tmp_fd_tlv < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open tlv320[%s] failed!", HI3531A_AUDIO_TLV320_FILE);
		return -1;
	}

	//add by andy
	//tmp_audio_ctrl.chip_num = 0;
	tmp_audio_ctrl.chip_num = 2;
	if (ioctl(tmp_fd_tlv, SOFT_RESET, &tmp_audio_ctrl))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tlv320aic31 reset failed!");
	}

	/* set master/slave mode, 1:master*/
	tmp_audio_ctrl.ctrl_mode = tmp_master;
	tmp_audio_ctrl.if_44100hz_series = tmp_44100hz_series;
	tmp_audio_ctrl.sample = tmp_sample_rate;
	tmp_audio_ctrl.sampleRate = sample;
	ioctl(tmp_fd_tlv, SET_CTRL_MODE, &tmp_audio_ctrl);

	/* set transfer mode 0:I2S 1:PCM */
	tmp_audio_ctrl.trans_mode = tmp_pcm_mode;
	if (ioctl(tmp_fd_tlv, SET_TRANSFER_MODE, &tmp_audio_ctrl))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"set tlv320aic31 trans_mode failed!");
		close(tmp_fd_tlv);
		return -1;
	}

	/*set sample of DAC and ADC */
	if (ioctl(tmp_fd_tlv, SET_DAC_SAMPLE, &tmp_audio_ctrl))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() set sample of ADC failed!");
		close(tmp_fd_tlv);
		return -1;
	}

	if (ioctl(tmp_fd_tlv, SET_ADC_SAMPLE, &tmp_audio_ctrl))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() set sample of ADC failed!");
		close(tmp_fd_tlv);
		return -1;
	}

	/*set volume control of left and right DAC */
	tmp_audio_ctrl.if_mute_route = 0;
	tmp_audio_ctrl.input_level = 0;
	ioctl(tmp_fd_tlv, LEFT_DAC_VOL_CTRL, &tmp_audio_ctrl);
	ioctl(tmp_fd_tlv, RIGHT_DAC_VOL_CTRL, &tmp_audio_ctrl);

	/*Right/Left DAC Datapath Control */
	tmp_audio_ctrl.if_powerup = 1;/*Left/Right DAC datapath plays left/right channel input data*/
	ioctl(tmp_fd_tlv, LEFT_DAC_POWER_SETUP, &tmp_audio_ctrl);
	if ((AIO_MODE_I2S_MASTER != work_mode) && (AIO_MODE_I2S_SLAVE != work_mode))
	{
		tmp_audio_ctrl.if_powerup = 0;
	}
	ioctl(tmp_fd_tlv, RIGHT_DAC_POWER_SETUP, &tmp_audio_ctrl);

	/* */
	if ((AIO_MODE_PCM_MASTER_STD == work_mode) || (AIO_MODE_PCM_SLAVE_STD == work_mode))
	{
		tmp_pcm_std = HI_TRUE;
		tmp_audio_ctrl.data_offset = tmp_pcm_std;
		ioctl(tmp_fd_tlv, SET_SERIAL_DATA_OFFSET, &tmp_audio_ctrl);
	}
	else if ((AIO_MODE_PCM_MASTER_NSTD == work_mode) || (AIO_MODE_PCM_SLAVE_NSTD == work_mode))
	{
		tmp_pcm_std = HI_FALSE;
		tmp_audio_ctrl.data_offset = tmp_pcm_std;
		ioctl(tmp_fd_tlv, SET_SERIAL_DATA_OFFSET, &tmp_audio_ctrl);
	}
	else
	{
		;
	}

	/* data bit width (0:16bit 1:20bit 2:24bit 3:32bit) */
	tmp_audio_ctrl.data_length = 0;
	ioctl(tmp_fd_tlv, SET_DATA_LENGTH, &tmp_audio_ctrl);

	/*DACL1 TO LEFT_LOP/RIGHT_LOP VOLUME CONTROL 82 92*/
	tmp_audio_ctrl.if_mute_route = 1;/* route*/
	tmp_audio_ctrl.input_level = tmp_vol; /*level control*/
	ioctl(tmp_fd_tlv, DACL1_2_LEFT_LOP_VOL_CTRL, &tmp_audio_ctrl);
	ioctl(tmp_fd_tlv, DACR1_2_RIGHT_LOP_VOL_CTRL, &tmp_audio_ctrl);

	/* LEFT_LOP/RIGHT_LOP OUTPUT LEVEL CONTROL 86 93*/
	tmp_audio_ctrl.if_mute_route = 1;
	tmp_audio_ctrl.if_powerup = 1;
	tmp_audio_ctrl.input_level = 0;
	ioctl(tmp_fd_tlv, LEFT_LOP_OUTPUT_LEVEL_CTRL, &tmp_audio_ctrl);
	ioctl(tmp_fd_tlv, RIGHT_LOP_OUTPUT_LEVEL_CTRL, &tmp_audio_ctrl);

	/*config AD*/
	/* LEFT/RIGHT ADC PGA GAIN CONTROL 15 16*/
	tmp_audio_ctrl.if_mute_route = 0;
	tmp_audio_ctrl.input_level = 0;
	ioctl(tmp_fd_tlv, LEFT_ADC_PGA_CTRL, &tmp_audio_ctrl);
	ioctl(tmp_fd_tlv, RIGHT_ADC_PGA_CTRL, &tmp_audio_ctrl);

	/*INT2L TO LEFT/RIGTH ADCCONTROL 17 18*/
	tmp_audio_ctrl.input_level = 0;
	ioctl(tmp_fd_tlv, IN2LR_2_LEFT_ADC_CTRL, &tmp_audio_ctrl);
	ioctl(tmp_fd_tlv, IN2LR_2_RIGTH_ADC_CTRL, &tmp_audio_ctrl);

	tmp_audio_ctrl.if_mute_route = 1;
	tmp_audio_ctrl.input_level = 9;
	tmp_audio_ctrl.if_powerup = 1;
	ioctl(tmp_fd_tlv, HPLOUT_OUTPUT_LEVEL_CTRL, &tmp_audio_ctrl);
	ioctl(tmp_fd_tlv, HPROUT_OUTPUT_LEVEL_CTRL, &tmp_audio_ctrl);

	close(tmp_fd_tlv);

	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
		"set aic31 master[%d] work_mode[%d] sample_rate[%d]",
		tmp_master, work_mode, sample);
	return 0;
}

HI_S32 hi3531a_audio_class::set_audio_tw2865_acodec(AUDIO_SAMPLE_RATE_E sample)
{
#if 0
	int									tmp_int_fb = 0;
	tw2865_audio_samplerate				tmp_samplerate;



	tmp_int_fb = open(HI3531A_AUDIO_TW2865_FILE, O_RDWR);
	if (tmp_int_fb < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open tw2865[%s] failed!", HI3531A_AUDIO_TW2865_FILE);
		return -1;
	}

	if (AUDIO_SAMPLE_RATE_8000 == sample)
	{
		tmp_samplerate = TW2865_SAMPLE_RATE_8000;
	}
	else if (AUDIO_SAMPLE_RATE_16000 == sample)
	{
		tmp_samplerate = TW2865_SAMPLE_RATE_16000;
	}
	else if (AUDIO_SAMPLE_RATE_32000 == sample)
	{
		tmp_samplerate = TW2865_SAMPLE_RATE_32000;
	}
	else if (AUDIO_SAMPLE_RATE_44100 == sample)
	{
		tmp_samplerate = TW2865_SAMPLE_RATE_44100;
	}
	else if (AUDIO_SAMPLE_RATE_48000 == sample)
	{
		tmp_samplerate = TW2865_SAMPLE_RATE_48000;
	}
	else
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tw2865 not support sample[%d]", sample);
		return -1;
	}

	if (ioctl(tmp_int_fb, TW2865_SET_SAMPLE_RATE, &tmp_samplerate))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() TW2865_SET_SAMPLE_RATE tmp_samplerate[%d] failed!", tmp_samplerate);
		close(tmp_int_fb);
		return -1;
	}

	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
		"tw2865 start sample[%d] successed", sample);

	close(tmp_int_fb);
#endif
	return 0;
}

HI_S32 hi3531a_audio_class::set_audio_tw2865_format(AIO_MODE_E work_mode)
{
#if 0
	int								tmp_int_fb = 0;
	tw2865_audio_format				audio_format;



	tmp_int_fb = open(HI3531A_AUDIO_TW2865_FILE, O_RDWR);
	if (tmp_int_fb < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open tw2865[%s] failed!", HI3531A_AUDIO_TW2865_FILE);
		return -1;
	}

	if (AIO_MODE_PCM_SLAVE_STD == work_mode
		|| AIO_MODE_PCM_SLAVE_NSTD == work_mode
		|| AIO_MODE_PCM_MASTER_STD == work_mode
		|| AIO_MODE_PCM_MASTER_NSTD == work_mode)
	{
		audio_format.format = 1;
		audio_format.clkdir = 1;
	}
	else
	{
		audio_format.format = 0;
		audio_format.clkdir = 0;
	}

	if (AIO_MODE_PCM_SLAVE_STD == work_mode
		|| AIO_MODE_PCM_SLAVE_NSTD == work_mode
		|| AIO_MODE_I2S_SLAVE == work_mode)
	{
		audio_format.mode = 1;
	}
	else
	{
		audio_format.mode = 0;
	}


	if (ioctl(tmp_int_fb, TW2865_SET_AUDIO_FORMAT, &audio_format))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() TW2865_SET_AUDIO_FORMAT format[%d] failed!", audio_format);
		close(tmp_int_fb);
		return -1;
	}

	close(tmp_int_fb);
#endif
	return 0;
}

HI_S32 hi3531a_audio_class::set_audio_tw2865_bit_width(AUDIO_BIT_WIDTH_E bit_width)
{
#if 0
	int							tmp_int_fb = 0;
	tw2865_audio_bitwidth		tmp_tw2865_bit_width;



	switch (bit_width)
	{
	case AUDIO_BIT_WIDTH_8:
	{
		tmp_tw2865_bit_width = TW2865_AUDIO_BITWIDTH_8;
	}
	break;
	case AUDIO_BIT_WIDTH_16:
	{
		tmp_tw2865_bit_width = TW2865_AUDIO_BITWIDTH_16;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tw2865 not support bit_width[%d]", bit_width);
	}
	return HI_FAILURE;
	}

	tmp_int_fb = open(HI3531A_AUDIO_TW2865_FILE, O_RDWR);
	if (tmp_int_fb < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open tw2865[%s] failed!", HI3531A_AUDIO_TW2865_FILE);
		return HI_FAILURE;
	}

	if (ioctl(tmp_int_fb, TW2865_SET_AUDIO_BITWIDTH, &tmp_tw2865_bit_width))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() TW2865_SET_AUDIO_BITWIDTH bit_width[%d] failed!",
			tmp_tw2865_bit_width);
		close(tmp_int_fb);
		return HI_FAILURE;
	}
	close(tmp_int_fb);
#endif
	return HI_SUCCESS;
}

HI_S32 hi3531a_audio_class::set_audio_tp2823_format(const AIO_ATTR_S *aio_attr)
{
	int							tmp_int_fb = 0;
	tp2823_audio_format			tmp_format;
	tp2802_audio_samplerate		tmp_samplerate;


	switch (aio_attr->enBitwidth)
	{
	case AUDIO_BIT_WIDTH_8:
	{
		tmp_format.precision = 1;
	}
	break;
	case AUDIO_BIT_WIDTH_16:
	{
		tmp_format.precision = 0;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tp2823 not support bit_width[%d]", aio_attr->enBitwidth);
	}
	return HI_FAILURE;
	}

	switch (aio_attr->enWorkmode)
	{
	case AIO_MODE_I2S_MASTER:
	case AIO_MODE_PCM_MASTER_NSTD:
	case AIO_MODE_PCM_MASTER_STD:
	{
		tmp_format.mode = 0;
		tmp_format.clkdir = 1;
	}
	break;
	case AIO_MODE_I2S_SLAVE:
	case AIO_MODE_PCM_SLAVE_NSTD:
	case AIO_MODE_PCM_SLAVE_STD:
	{
		tmp_format.mode = 1;
		tmp_format.clkdir = 0;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tp2823 not support mode[%d]", aio_attr->enWorkmode);
	}
	return HI_FAILURE;
	}

	switch (aio_attr->enWorkmode)
	{
	case AIO_MODE_I2S_MASTER:
	case AIO_MODE_I2S_SLAVE:
	{
		tmp_format.format = 0;
	}
	break;
	case AIO_MODE_PCM_MASTER_STD:
	case AIO_MODE_PCM_SLAVE_STD:
	{
		tmp_format.format = 1;
	}
	break;
	case AIO_MODE_PCM_MASTER_NSTD:
	case AIO_MODE_PCM_SLAVE_NSTD:
	{
		tmp_format.format = 1;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tp2823 not support mode[%d]", aio_attr->enWorkmode);
	}
	}

	switch (aio_attr->u32ChnCnt)
	{
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	{
		tmp_format.bitrate = 0;
		tmp_format.chn_num = aio_attr->u32ChnCnt;
	}
	break;
	case 20:
	{
		tmp_format.bitrate = 1;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tp2823 not support channel_number[%d]", aio_attr->u32ChnCnt);
	}
	return HI_FAILURE;
	}

	tmp_format.clkdir = 0;
	tmp_format.chip = 0;
	tmp_int_fb = open(HI3531A_AUDIO_TP2823_FILE, O_RDWR);
	if (tmp_int_fb < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open tp2823[%s] failed!", HI3531A_AUDIO_TP2823_FILE);
		return HI_FAILURE;
	}

	if (ioctl(tmp_int_fb, TP2802_SET_AUDIO_RM_FORMAT, &tmp_format))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() TP2802_SET_AUDIO_RM_FORMAT failed!");
		close(tmp_int_fb);
		return HI_FAILURE;
	}

	//tmp_format.mode = 0;
	if (ioctl(tmp_int_fb, TP2802_SET_AUDIO_PB_FORMAT, &tmp_format))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() TP2802_SET_AUDIO_PB_FORMAT failed!");
		close(tmp_int_fb);
		return HI_FAILURE;
	}

	switch (aio_attr->enSamplerate)
	{
	case AUDIO_SAMPLE_RATE_8000:
	{
		tmp_samplerate = SAMPLE_RATE_8000;
	}
	break;
	case AUDIO_SAMPLE_RATE_16000:
	{
		tmp_samplerate = SAMPLE_RATE_16000;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"tp2823 not support tmp_samplerate[%d] failed!", aio_attr->enSamplerate);
	}
	return HI_FAILURE;
	}

	if (ioctl(tmp_int_fb, TP2802_SET_SAMPLE_RATE, &tmp_samplerate))
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ioctl() TP2802_SET_AUDIO_PB_FORMAT tmp_samplerate[%d] failed!", tmp_samplerate);
		close(tmp_int_fb);
		return HI_FAILURE;
	}

	close(tmp_int_fb);
	return HI_SUCCESS;
}

#endif

bool hi3531a_audio_class::start_ai()
{
#if defined(HI3531A_MODE)

	HI_S32								i = 0;
	HI_S32								tmp_int_ret = 0;
	AIO_ATTR_S							tmp_aio_attr;




	//获取aio属性，判断是否已经启动过了。如果返回成功表示已经启动。
	tmp_int_ret = HI_MPI_AI_GetPubAttr(m_ai_dev, &tmp_aio_attr);
	if (HI_ERR_AI_NOT_CONFIG != tmp_int_ret) {
		write_log(LOG_WARNING, WARNING_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_GetPubAttr() success! start_ai() successed.",
			m_ai_dev);

		return true;
	}

	//配置aio属性
	tmp_int_ret = HI_MPI_AI_SetPubAttr(m_ai_dev, &m_ai_attr);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_SetPubAttr() ai[Bitwidth:%d PtNumPerFrm:%d] failed! error_code[0x%x].",
			m_ai_dev,
			m_ai_attr.enBitwidth,
			m_ai_attr.u32PtNumPerFrm,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_SetPubAttr() ai[Bitwidth:%d PtNumPerFrm:%d] successed!",
			m_ai_dev,
			m_ai_attr.enBitwidth,
			m_ai_attr.u32PtNumPerFrm);
	}

	//启动ai设备
	tmp_int_ret = HI_MPI_AI_Enable(m_ai_dev);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_Enable() failed! error_code[0x%x].",
			m_ai_dev,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_Enable() successed!",
			m_ai_dev);
	}

	//配置各个通道
	for (i = 0; i < m_ai_attr.u32ChnCnt; i++) {
		//启动通道
		tmp_int_ret = HI_MPI_AI_EnableChn(m_ai_dev, i);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ai_dev[%d] HI_MPI_AI_EnableChn() channel[%d] failed! error_code[0x%x].",
				m_ai_dev,
				i,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"ai_dev[%d] HI_MPI_AI_EnableChn() channel[%d] successed!",
				m_ai_dev,
				i);
		}

		//表示ai采样内容
		start_ai_resample(m_ai_dev, i);

		//配置是否音频增强
		start_ai_vqe(m_ai_dev, i, m_ao_dev, i);

		//设置音频音量信息
		set_ai_vqe_volume(m_ai_dev, i, m_ai_volume);
	}

#endif

	return true;
}

bool hi3531a_audio_class::start_ai_resample(int ai_dev_id, int ai_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	tmp_int_ret = HI_MPI_AI_DisableReSmp(ai_dev_id, ai_channel);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_AI_DisableReSmp() ai[dev:%d & channel:%d] failed! error_code[0x%x].",
			ai_dev_id,
			ai_channel,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_AI_DisableReSmp() ai[dev:%d & channel:%d] successed!",
			ai_dev_id,
			ai_channel);
	}

	//配置是否重采样
	if (!m_is_ai_resample) {
		return true;
	}

	tmp_int_ret |= HI_MPI_AI_EnableReSmp(ai_dev_id, ai_channel, m_out_resample_rate);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_EnableReSmp() channel[%d] failed! error_code[0x%x].",
			ai_dev_id,
			ai_channel,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_EnableReSmp() channel[%d] successed!",
			ai_dev_id,
			ai_channel);
	}

#endif

	return true;
}

bool hi3531a_audio_class::start_ai_vqe(
	int ai_dev_id, int ai_channel, int ao_dev_id, int ao_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	//配置是否音频增强
	if (!m_is_ai_used_vqe) {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_SetVqeAttr() channel[%d] disable!",
			m_ai_dev,
			ai_channel);

		return true;
	}
	else {
		//设置音频增强配置
		tmp_int_ret = HI_MPI_AI_SetVqeAttr(ai_dev_id, ai_channel, ao_dev_id, ao_channel, &m_ai_vqe_conf);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"HI_MPI_AI_SetVqeAttr() ai[dev:%d & channel:%d] -- ao[dev:%d & channel:%d] workstate[%d] failed! error_code[0x%x].",
				ai_dev_id,
				ai_channel,
				ao_dev_id,
				ao_channel,
				m_ai_vqe_conf.enWorkstate,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"HI_MPI_AI_SetVqeAttr() ai[dev:%d & channel:%d] -- ao[dev:%d & channel:%d] workstate[%d] successed!",
				ai_dev_id,
				ai_channel,
				ao_dev_id,
				ao_channel,
				m_ai_vqe_conf.enWorkstate);
		}

		//是否启动音频增强
		tmp_int_ret = HI_MPI_AI_EnableVqe(ai_dev_id, ai_channel);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"HI_MPI_AI_EnableVqe() ai[dev:%d & channel:%d] failed! error_code[0x%x].",
				ai_dev_id,
				ai_channel,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"HI_MPI_AI_EnableVqe() ai[dev:%d & channel:%d] successed!",
				ai_dev_id,
				ai_channel);
		}
	}

#endif

	return true;
}

/*******************************************************************************
* 版权所有: fz & compony
*
* 函数名称: set_ai_vqe_volume
*
* 函数全名: hi3531a_audio_class::set_ai_vqe_volume
*
* 函数访问: protected
*
* 函数说明: 设置音频采集增益，提高音量
*
* 参    数: int ai_dev_id						[in/out]参数说明
* 参    数: int ai_channel						[in/out]参数说明
* 参    数: int volume_db						[in/out]参数说明
*
* 返 回 值: bool
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@compony.com.cn
* 创建日期：2018-5-28 15:08:37
********************************************************************************/
bool hi3531a_audio_class::set_ai_vqe_volume(int ai_dev_id, int ai_channel, int volume_db)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	//设置音频增强配置
	tmp_int_ret = HI_MPI_AI_SetVqeVolume(ai_dev_id, ai_channel, volume_db);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_AI_SetVqeVolume() ai[dev:%d & channel:%d] volum[%d] failed! error_code[0x%x].",
			ai_dev_id,
			ai_channel,
			volume_db,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_AI_SetVqeVolume() ai[dev:%d & channel:%d] volum[%d] successed!",
			ai_dev_id,
			ai_channel,
			volume_db);
	}
#endif

	return true;
}

bool hi3531a_audio_class::stop_ai()
{
#if defined(HI3531A_MODE)

	HI_S32								i = 0;
	HI_S32								tmp_int_ret = 0;



	//配置各个通道
	for (i = 0; i < m_ai_attr.u32ChnCnt; i++) {
		//关闭音频增强
		stop_ai_vqe(m_ai_dev, i);

		//关闭重采样功能
		stop_ai_resample(m_ai_dev, i);

		//不使用通道
		tmp_int_ret = HI_MPI_AI_DisableChn(m_ai_dev, i);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ai_dev[%d] HI_MPI_AI_DisableChn() channel[%d] failed! error_code[0x%x].",
				m_ai_dev,
				i,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"ai_dev[%d] HI_MPI_AI_DisableChn() channel[%d] successed!",
				m_ai_dev,
				i);
		}
	}

	//停止ai设备
	tmp_int_ret = HI_MPI_AI_Disable(m_ai_dev);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_Disable() failed! error_code[0x%x].",
			m_ai_dev,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AI_Disable() successed!",
			m_ai_dev);
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_ai_resample(int ai_dev_id, int ai_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	if (m_is_ai_resample) {
		tmp_int_ret = HI_MPI_AI_DisableReSmp(ai_dev_id, ai_channel);
		if (HI_SUCCESS != tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ai_dev[%d] HI_MPI_AI_DisableReSmp() channel[%d] failed! error_code[0x%x].",
				m_ai_dev,
				ai_channel,
				tmp_int_ret);

			return false;
		}
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_ai_vqe(int ai_dev_id, int ai_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	if (m_is_ai_used_vqe) {
		tmp_int_ret = HI_MPI_AI_DisableVqe(ai_dev_id, ai_channel);
		if (HI_SUCCESS != tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ai_dev[%d] HI_MPI_AI_DisableVqe() channel[%d] failed! error_code[0x%x].",
				m_ai_dev,
				ai_channel,
				tmp_int_ret);

			return false;
		}
	}

#endif

	return true;
}



bool hi3531a_audio_class::init_ao()
{
#if defined(HI3531A_MODE)

	m_is_ao_used_vqe = true;

	//高通滤波
	m_ao_vqe_conf.bHpfOpen = HI_TRUE;
	m_ao_vqe_conf.s32WorkSampleRate = m_ao_attr.enSamplerate;
	m_ao_vqe_conf.s32FrameSample = m_ao_attr.u32PtNumPerFrm;
	m_ao_vqe_conf.enWorkstate = VQE_WORKSTATE_NOISY;
	//m_ao_vqe_conf.enWorkstate = VQE_WORKSTATE_COMMON;
	m_ao_vqe_conf.stHpfCfg.bUsrMode = HI_FALSE;
	//m_ao_vqe_conf.stHpfCfg.enHpfFreq = AUDIO_HPF_FREQ_150;

	//语音降噪功
	m_ao_vqe_conf.bAnrOpen = true;
	m_ao_vqe_conf.stAnrCfg.bUsrMode = HI_FALSE;

	//自动增益控制
	//m_ao_vqe_conf.bAgcOpen = true;
	//m_ao_vqe_conf.stAgcCfg.bUsrMode = HI_FALSE;

#endif

	return true;
}

bool hi3531a_audio_class::start_ao()
{
#if defined(HI3531A_MODE)

	HI_S32								i = 0;
	HI_S32								tmp_int_ret = 0;
	AIO_ATTR_S							tmp_aio_attr;




	//获取aio属性，判断是否已经启动过了。如果返回成功表示已经启动。
	tmp_int_ret = HI_MPI_AO_GetPubAttr(m_ai_dev, &tmp_aio_attr);
	if (HI_ERR_AO_NOT_CONFIG != tmp_int_ret) {
		write_log(LOG_WARNING, WARNING_MODULE_OPERATION,
			"ai_dev[%d] HI_MPI_AO_GetPubAttr() success! start_ao() successed.",
			m_ao_dev);

		return true;
	}

	//配置aio属性
	tmp_int_ret = HI_MPI_AO_SetPubAttr(m_ao_dev, &m_ao_attr);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ao_dev[%d] HI_MPI_AO_SetPubAttr() ao[Bitwidth:%d PtNumPerFrm:%d] failed! error_code[0x%x].",
			m_ao_dev,
			m_ao_attr.enBitwidth,
			m_ao_attr.u32PtNumPerFrm,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ao_dev[%d] HI_MPI_AO_SetPubAttr() ao[Bitwidth:%d PtNumPerFrm:%d] successed!",
			m_ao_dev,
			m_ao_attr.enBitwidth,
			m_ao_attr.u32PtNumPerFrm);
	}

	//启动ao设备
	tmp_int_ret = HI_MPI_AO_Enable(m_ao_dev);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"ao_dev[%d] HI_MPI_AO_Enable() faoled! error_code[0x%x].",
			m_ao_dev,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ao_dev[%d] HI_MPI_AO_Enable() successed!",
			m_ao_dev);
	}

	//配置各个通道
	for (i = 0; i < m_ai_attr.u32ChnCnt; i++) {

		//启动通道
		tmp_int_ret = HI_MPI_AO_EnableChn(m_ao_dev, i);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ao_dev[%d] HI_MPI_AO_EnableChn() channel[%d] faoled! error_code[0x%x].",
				m_ao_dev,
				i,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"ao_dev[%d] HI_MPI_AO_EnableChn() channel[%d] successed!",
				m_ao_dev,
				i);
		}

		//表示ao采样内容
		start_ao_resample(m_ao_dev, i);

		//配置是否音频增强
		start_ao_vqe(m_ao_dev, i);

		//设置音量信息
		set_ao_vqe_volume(m_ao_dev, i, m_ao_volume);
	}

#endif

	return true;
}

bool hi3531a_audio_class::start_ao_resample(int ao_dev_id, int ao_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	//配置是否重采样
	if (!m_is_ao_resample) {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ao_dev[%d] HI_MPI_AO_EnableReSmp() channel[%d] disable!",
			m_ao_dev,
			ao_channel);

		return true;
	}
	else {
		tmp_int_ret = HI_MPI_AO_DisableReSmp(m_ao_dev, ao_channel);
		tmp_int_ret |= HI_MPI_AO_EnableReSmp(m_ao_dev, ao_channel, m_out_resample_rate);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ao_dev[%d] HI_MPI_AO_EnableReSmp() channel[%d] failed! error_code[0x%x].",
				m_ao_dev,
				ao_channel,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"ao_dev[%d] HI_MPI_AO_EnableReSmp() channel[%d] successed!",
				m_ao_dev,
				ao_channel);
		}
	}

#endif

	return true;
}

bool hi3531a_audio_class::start_ao_vqe(int ao_dev_id, int ao_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	//配置是否音频增强
	if (!m_is_ao_used_vqe) {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"ao_dev[%d] HI_MPI_AO_SetVqeAttr() channel[%d] disable!",
			ao_dev_id,
			ao_channel);

		return true;
	}
	else {
		//设置音频增强配置
		tmp_int_ret = HI_MPI_AO_SetVqeAttr(ao_dev_id, ao_channel, &m_ao_vqe_conf);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"HI_MPI_AO_SetVqeAttr() ao[dev:%d & channel:%d] workstate[%d] failed! error_code[0x%x].",
				ao_dev_id,
				ao_channel,
				m_ao_vqe_conf.enWorkstate,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"HI_MPI_AO_SetVqeAttr() ao[dev:%d & channel:%d] workstate[%d] successed!",
				ao_dev_id,
				ao_channel,
				m_ao_vqe_conf.enWorkstate);
		}

		//是否启动音频增强
		tmp_int_ret = HI_MPI_AO_EnableVqe(ao_dev_id, ao_channel);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"HI_MPI_AO_EnableVqe() ao[dev:%d & channel:%d] failed! error_code[0x%x].",
				ao_dev_id,
				ao_channel,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"HI_MPI_AO_EnableVqe() ao[dev:%d & channel:%d] successed!",
				ao_dev_id,
				ao_channel);
		}
	}

#endif

	return true;
}

/*******************************************************************************
* 版权所有: fz & compony
*
* 函数名称: set_ao_vqe_volume
*
* 函数全名: hi3531a_audio_class::set_ao_vqe_volume
*
* 函数访问: protected
*
* 函数说明: 设置输出竟是
*
* 参    数: int ao_dev_id						[in/out]参数说明
* 参    数: int ao_channel						[in/out]参数说明
* 参    数: int volume_db						[in/out]参数说明
*
* 返 回 值: bool
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@compony.com.cn
* 创建日期：2018-5-28 15:09:49
********************************************************************************/
bool hi3531a_audio_class::set_ao_vqe_volume(int ao_dev_id, int ao_channel, int volume_db)
{
#if defined(HI3531A_MODE)
	HI_S32								tmp_int_ret;
	HI_S32								tmp_volume = 0;



	//设置音频增强配置
	tmp_int_ret = HI_MPI_AO_SetVolume(ao_dev_id, volume_db);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_AO_SetVqeAttr() ao[dev:%d & channel:%d] volume[%d] failed! error_code[0x%x].",
			ao_dev_id,
			ao_channel,
			volume_db,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_AO_SetVqeAttr() ao[dev:%d & channel:%d] volume[%d] successed!",
			ao_dev_id,
			ao_channel,
			volume_db);
	}
#endif
	return true;
}

bool hi3531a_audio_class::stop_ao()
{
	return true;
}

bool hi3531a_audio_class::stop_ao_resample(int ao_dev_id, int ao_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	if (m_is_ao_resample) {
		tmp_int_ret = HI_MPI_AO_DisableReSmp(ao_dev_id, ao_channel);
		if (HI_SUCCESS != tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ao_dev[%d] HI_MPI_AO_DisableReSmp() channel[%d] failed! error_code[0x%x].",
				m_ao_dev,
				ao_channel,
				tmp_int_ret);

			return false;
		}
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_ao_vqe(int ao_dev_id, int ao_channel)
{
#if defined(HI3531A_MODE)

	HI_S32								tmp_int_ret;



	if (m_is_ao_used_vqe) {
		tmp_int_ret = HI_MPI_AO_DisableVqe(ao_dev_id, ao_channel);
		if (HI_SUCCESS != tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"ao_dev[%d] HI_MPI_AO_DisableVqe() channel[%d] failed! error_code[0x%x].",
				m_ao_dev,
				ao_channel,
				tmp_int_ret);

			return false;
		}
	}

#endif

	return true;
}

bool hi3531a_audio_class::init_aenc()
{
#if defined(HI3531A_MODE)

	switch (m_aenc_attr.enType)
	{
	case PT_ADPCMA:
	{
		m_aenc_attr.pValue = &m_aenc_adpcm_attr;
		m_aenc_adpcm_attr.enADPCMType = ADPCM_TYPE_DVI4;
		m_ai_attr.enBitwidth = AUDIO_BIT_WIDTH_16;
		m_ai_attr.u32PtNumPerFrm = 320;
	}
	break;
	case PT_G711A:
	case PT_G711U:
	{
		m_aenc_attr.pValue = &m_aenc_g711_attr;
	}
	break;
	case PT_G726:
	{
		m_aenc_attr.pValue = &m_aenc_g726_attr;
		m_aenc_g726_attr.enG726bps = G726_16K;

		m_ai_attr.enBitwidth = AUDIO_BIT_WIDTH_16;
		m_ai_attr.u32PtNumPerFrm = 80;
	}
	break;
	case PT_LPCM:
	{
		m_aenc_attr.pValue = &m_aenc_lpcm_attr;
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"init_aenc() error! unknow aenc[Type:%d Bitwidth:%d PtNumPerFrm:%d].",
			m_aenc_attr.enType,
			m_ai_attr.enBitwidth,
			m_ai_attr.u32PtNumPerFrm);

		return false;
	}
	break;
	}

	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
		"init_aenc() successed! set aenc[Type:%d Bitwidth:%d PtNumPerFrm:%d].",
		m_aenc_attr.enType,
		m_ai_attr.enBitwidth,
		m_ai_attr.u32PtNumPerFrm);

#endif

	return true;
}

bool hi3531a_audio_class::start_aenc()
{
#if defined(HI3531A_MODE)
	AENC_CHN							tmp_aenc_chn = 0;
	HI_S32								i = 0;
	HI_S32								tmp_int_ret = 0;
	hi3531a_audio_thread_info		tmp_ati;



	//配置各个通道
	for (i = 0; i < m_aenc_channel_count; i++) {

		tmp_aenc_chn = i;

		//创建编码通道
		tmp_int_ret = HI_MPI_AENC_CreateChn(tmp_aenc_chn, &m_aenc_attr);
		if (HI_SUCCESS != tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"HI_MPI_AENC_CreateChn() channel[%d] failed! error_code[0x%x].",
				tmp_aenc_chn,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"HI_MPI_AENC_CreateChn() channel[%d] successed!",
				tmp_aenc_chn);
		}

		//启动处理线程
		tmp_ati.set_channel_info(m_ai_dev, m_ai_chn, tmp_aenc_chn);
		start_aenc_thread_proc(tmp_ati);
	}

#endif
	return true;
}

bool hi3531a_audio_class::start_aenc_thread_proc(hi3531a_audio_thread_info &ati)
{
#if defined(HI3531A_MODE)
	hi3531a_audio_thread_info		*tmp_ati = NULL;
	bool								tmp_bool_ret = false;



	tmp_ati = new hi3531a_audio_thread_info();
	if (!tmp_ati) {
		return false;
	}

	*tmp_ati = ati;

	//绑定ai和aenc内容
	tmp_bool_ret = bind_ai_aenc(ati.m_audio_dev, ati.m_audio_channel, ati.m_audio_process_channel);
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "bind_ai_aenc() failed!");
		return false;
	}

	//创建线程
	tmp_ati->m_thread_p = m_aenc_thread_group.create_thread(boost::bind(&hi3531a_audio_class::aenc_thread_proc, this, tmp_ati));
	if (!tmp_ati->m_thread_p) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"create aenc_thread_proc() error. make thread error.");
		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"aenc_thread_proc() thread_group[%d] thread[%p] successed.",
			m_aenc_thread_group.size(),
			tmp_ati->m_thread_p);
	}

#endif
	return true;
}

bool hi3531a_audio_class::aenc_thread_proc(hi3531a_audio_thread_info *ati)
{
#if defined(HI3531A_MODE)
	hi3531a_audio_thread_info		*tmp_ati = NULL;
	lock_free_pool_flag_buf_p		tmp_lf_buf_p = NULL;
	bool								tmp_bool_ret = false;
	HI_S32								tmp_int_ret = 0;
	fd_set								tmp_read_fds;
	HI_S32								tmp_ai_fds = 0;
	struct timeval						tmp_timeout_val = { 0, };
	AUDIO_STREAM_S						tmp_stream = { 0, };




	FD_ZERO(&tmp_read_fds);
	tmp_ai_fds = HI_MPI_AENC_GetFd(ati->m_audio_process_channel);
	FD_SET(tmp_ai_fds, &tmp_read_fds);
	m_aenc_is_start = true;

	while (m_aenc_is_start)
	{
		tmp_timeout_val.tv_sec = 1;
		tmp_timeout_val.tv_usec = 0;

		FD_ZERO(&tmp_read_fds);
		FD_SET(tmp_ai_fds, &tmp_read_fds);

		tmp_int_ret = select(tmp_ai_fds + 1, &tmp_read_fds, NULL, NULL, &tmp_timeout_val);
		if (tmp_int_ret < 0) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"select() aenc_channel[%d] error.", ati->m_audio_process_channel);
			break;
		}

#if 0
		if (0 == tmp_int_ret)
		{
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"select() aenc_channel[%d] time out warning.");
			break;
		}
#endif

		if (FD_ISSET(tmp_ai_fds, &tmp_read_fds)) {

			/* get frame from encoder */
			tmp_int_ret = HI_MPI_AENC_GetStream(ati->m_audio_process_channel, &tmp_stream, -1);
			if (HI_SUCCESS != tmp_int_ret) {
				write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
					"HI_MPI_AENC_GetStream() aenc_channel[%d] error. error_code[0x%x].",
					ati->m_audio_process_channel,
					tmp_int_ret);

				break;
			}

			/************************************************************************/
			/* 根据是否发送标志位，来发送数据。                                        */
			/************************************************************************/
			if (false == m_aenc_is_send || 
				m_audio_enc_ptr_queue.size() >= HI_AUDIO_DATA_QUEUE_MAX_SIZE)
			{
				//如果不发送，则清空缓存数据
				m_audio_enc_ptr_queue.clear();
			}
			else
			{
				/************************************************************************/
				/* 这里如果是测试模式，则直接将采集输出到解码器播放。所以使用的都是解码器的内存*/
				/************************************************************************/
#if !defined(AUDIO_DEBUG_MODE)
				//拷贝数据
				tmp_lf_buf_p = new lock_free_pool_flag_buffer_class(&m_audio_enc_lock_free_pool_manager, tmp_stream.u32Len);
#else
				//拷贝数据
				tmp_lf_buf_p = new lock_free_pool_flag_buffer_class(&m_audio_dec_lock_free_pool_manager, tmp_stream.u32Len);
#endif
				if (!tmp_lf_buf_p) {
					write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
						"aenc_thread_proc() aenc_channel[%d] error. alloc memory[%d] error.",
						ati->m_audio_process_channel,
						tmp_stream.u32Len);
					break;
				}
				tmp_lf_buf_p->copy(tmp_stream.pStream, tmp_stream.u32Len);

#ifdef AUDIO_SAVE_FILE
				//保存数据到文件中
				save_file_data(m_aenc_file, tmp_stream.pStream, tmp_stream.u32Len);
#endif

#if !defined(AUDIO_DEBUG_MODE)
				//插入到编码队列中
				m_audio_enc_ptr_queue.push_back(lock_free_pool_flag_buf_ptr(tmp_lf_buf_p));
#else
				//插入到编码队列中
				m_audio_dec_ptr_queue.push_back(lock_free_pool_flag_buf_ptr(tmp_lf_buf_p));
#endif
			}

			/* finally you must release the stream */
			tmp_int_ret = HI_MPI_AENC_ReleaseStream(ati->m_audio_process_channel, &tmp_stream);
			if (HI_SUCCESS != tmp_int_ret) {
				write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
					"HI_MPI_AENC_ReleaseStream() aenc_channel[%d] error. error_code[0x%x].",
					ati->m_audio_process_channel,
					tmp_int_ret);

				break;
			}
		}
	}

	if (ati) {
		//绑定ai和aenc内容
		tmp_bool_ret = unbind_ai_aenc(ati->m_audio_dev, ati->m_audio_channel, ati->m_audio_process_channel);
		if (!tmp_bool_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"unbind_ai_aenc() failed! error_code[0x%x].", tmp_int_ret);
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"unbind_ai_aenc() successed!");
		}

		delete ati;
	}

	write_log(LOG_WARNING, WARNING_MODULE_OPERATION,
		"thread[%p] aenc_thread_proc() stoped!", ati->m_thread_p);

#endif

	return true;
}

bool hi3531a_audio_class::bind_ai_aenc(int ai_dev, int ai_channel, int aenc_channel)
{
#if defined(HI3531A_MODE)

	MPP_CHN_S							tmp_src_chn;
	MPP_CHN_S							tmp_dest_chn;
	HI_S32								tmp_int_ret = 0;



	tmp_src_chn.enModId = HI_ID_AI;
	tmp_src_chn.s32DevId = ai_dev;
	tmp_src_chn.s32ChnId = ai_channel;
	tmp_dest_chn.enModId = HI_ID_AENC;
	tmp_dest_chn.s32DevId = 0;
	tmp_dest_chn.s32ChnId = aenc_channel;

	tmp_int_ret = HI_MPI_SYS_Bind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_SYS_Bind() ai_dev[%d] ai_channel[%d] aenc_channel[%d] failed! error_code[0x%x].",
			ai_dev,
			ai_channel,
			aenc_channel,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_SYS_Bind() ai_dev[%d] ai_channel[%d] aenc_channel[%d] successed!",
			ai_dev,
			ai_channel,
			aenc_channel);
	}

#endif

	return true;
}

bool hi3531a_audio_class::unbind_ai_aenc(int ai_dev, int ai_channel, int aenc_channel)
{
#if defined(HI3531A_MODE)

	MPP_CHN_S							tmp_src_chn;
	MPP_CHN_S							tmp_dest_chn;
	HI_S32								tmp_int_ret = 0;



	tmp_src_chn.enModId = HI_ID_AI;
	tmp_src_chn.s32DevId = ai_dev;
	tmp_src_chn.s32ChnId = ai_channel;
	tmp_dest_chn.enModId = HI_ID_AENC;
	tmp_dest_chn.s32DevId = 0;
	tmp_dest_chn.s32ChnId = aenc_channel;

	tmp_int_ret = HI_MPI_SYS_UnBind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_SYS_UnBind() ai_dev[%d] ai_channel[%d] aenc_channel[%d] failed! error_code[0x%x].",
			ai_dev,
			ai_channel,
			aenc_channel,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_SYS_UnBind() ai_dev[%d] ai_channel[%d] aenc_channel[%d] successed!",
			ai_dev,
			ai_channel,
			aenc_channel);
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_aenc()
{
	stop_aenc_thread_proc();
	stop_aenc_channel();

	return true;
}

bool hi3531a_audio_class::stop_aenc_channel()
{
#if defined(HI3531A_MODE)
	AENC_CHN							tmp_aenc_chn = 0;
	HI_S32								i = 0;
	HI_S32								tmp_int_ret = 0;



	//配置各个通道
	for (i = 0; i < m_aenc_channel_count; i++) {

		tmp_aenc_chn = i;

		//创建编码通道
		tmp_int_ret = HI_MPI_AENC_DestroyChn(tmp_aenc_chn);
		if (tmp_int_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"HI_MPI_AENC_DestroyChn() channel[%d] failed! error_code[0x%x].",
				tmp_aenc_chn,
				tmp_int_ret);

			return false;
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"HI_MPI_AENC_DestroyChn() channel[%d] successed!",
				tmp_aenc_chn);
		}
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_aenc_thread_proc()
{
	m_aenc_is_start = false;
	m_aenc_thread_group.timed_join_all(HI3531A_AUDIO_THREAD_JOIN_TIME_MS);

	return true;
}

bool hi3531a_audio_class::init_adec()
{
#if defined(HI3531A_MODE)

	m_ao_attr.enBitwidth = m_ai_attr.enBitwidth;
	m_ao_attr.u32PtNumPerFrm = m_ai_attr.u32PtNumPerFrm;

	switch (m_adec_attr.enType)
	{
	case PT_ADPCMA:
	{
		m_adec_attr.pValue = &m_adec_adpcm_attr;
		m_adec_adpcm_attr.enADPCMType = m_aenc_adpcm_attr.enADPCMType;
	}
	break;
	case PT_G711A:
	case PT_G711U:
	{
		m_adec_attr.pValue = &m_adec_g711_attr;
	}
	break;
	case PT_G726:
	{
		m_adec_attr.pValue = &m_adec_g726_attr;
		m_adec_g726_attr.enG726bps = m_aenc_g726_attr.enG726bps;
	}
	break;
	case PT_LPCM:
	{
		m_adec_attr.pValue = &m_adec_lpcm_attr;
		m_adec_attr.enMode = ADEC_MODE_PACK;/* lpcm must use pack mode */
	}
	break;
	default:
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"init_adec() error! unknow adec[Type:%d Bitwidth:%d PtNumPerFrm:%d].",
			m_adec_attr.enType,
			m_ao_attr.enBitwidth,
			m_ao_attr.u32PtNumPerFrm);

		return false;
	}
	break;
	}

	write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
		"init_adec() successed! set adec[Type:%d Bitwidth:%d PtNumPerFrm:%d].",
		m_adec_attr.enType,
		m_ao_attr.enBitwidth,
		m_ao_attr.u32PtNumPerFrm);

#endif

	return true;
}

bool hi3531a_audio_class::start_adec()
{
#if defined(HI3531A_MODE)
	HI_S32								tmp_int_ret = 0;
	hi3531a_audio_thread_info		tmp_ati;



	//创建编码通道
	tmp_int_ret = HI_MPI_ADEC_CreateChn(m_adec_chn, &m_adec_attr);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_ADEC_CreateChn() channel[%d] failed! error_code[0x%x].",
			m_adec_chn,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_ADEC_CreateChn() channel[%d] successed!",
			m_adec_chn);
	}

	//启动处理线程
	tmp_ati.set_channel_info(m_ao_dev, m_ao_chn, m_adec_chn);
	start_adec_thread_proc(tmp_ati);

#endif

	return true;
}

bool hi3531a_audio_class::start_adec_thread_proc(hi3531a_audio_thread_info &ati)
{
#if defined(HI3531A_MODE)
	hi3531a_audio_thread_info		*tmp_ati = NULL;
	bool								tmp_bool_ret = false;



	tmp_ati = new hi3531a_audio_thread_info();
	if (!tmp_ati) {
		return false;
	}

	*tmp_ati = ati;

	//绑定ao和adec内容
	tmp_bool_ret = bind_ao_adec(ati.m_audio_dev, ati.m_audio_channel, ati.m_audio_process_channel);
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "bind_ao_adec() failed!");
		return false;
	}

	//创建线程
	tmp_ati->m_thread_p = m_adec_thread_group.create_thread(boost::bind(&hi3531a_audio_class::adec_thread_proc, this, tmp_ati));
	if (!tmp_ati->m_thread_p) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"create adec_thread_proc() error. make thread error.");
		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"adec_thread_proc() thread_group[%d] thread[%p] successed.",
			m_adec_thread_group.size(),
			tmp_ati->m_thread_p);
	}

#endif
	return true;
}

bool hi3531a_audio_class::adec_thread_proc(hi3531a_audio_thread_info *ati)
{
#if defined(HI3531A_MODE)
	lock_free_pool_flag_buf_ptr		tmp_lf_buf_ptr = m_null_lock_free_pool_flag_buf_ptr;
	HI_S32								tmp_int_ret = 0;
	HI_S32								tmp_int_error = 0;
	bool								tmp_bool_ret = false;
	AUDIO_STREAM_S						tmp_stream = { 0, };



	m_adec_is_start = true;
	while (m_adec_is_start)
	{
		/************************************************************************/
		/* 根据解码是否发送标志位，来处理是否解码数据。                             */
		/************************************************************************/
		if (false == m_adec_is_send || 
			m_audio_dec_ptr_queue.size() >= HI_AUDIO_DATA_QUEUE_MAX_SIZE) {
			//如果不发送，则清空缓存数据
			m_audio_dec_ptr_queue.clear();
			delay_sleep_wait_ns(0, HI3531A_AUDIO_FRAME_SLEEP_INTERVAL_NS);
			continue;
		}

		tmp_lf_buf_ptr = m_audio_dec_ptr_queue.pop_front();
		if (tmp_lf_buf_ptr == m_null_lock_free_pool_flag_buf_ptr) {
			delay_sleep_wait_ns(0, HI3531A_AUDIO_FRAME_SLEEP_INTERVAL_NS);
			continue;
		}

		tmp_stream.pStream = tmp_lf_buf_ptr->get_buf();
		tmp_stream.u32Len = tmp_lf_buf_ptr->length();

		/* here only demo adec streaming sending mode, but pack sending mode is commended */
		tmp_int_ret = HI_MPI_ADEC_SendStream(ati->m_audio_process_channel, &tmp_stream, HI_TRUE);
		if (HI_SUCCESS != tmp_int_ret) {
			
			if (!(tmp_int_error % m_ao_attr.u32PtNumPerFrm)) {
				write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
					"HI_MPI_ADEC_SendStream() aenc_channel[%d] error. error_code[0x%x].",
					ati->m_audio_process_channel,
					tmp_int_ret);

				//防止数据太大，需要重置
				if (!tmp_int_error) {
					++tmp_int_error;
				}
				else {
					tmp_int_error = 0;
				}
			}
			
			//break;
		}

#ifdef AUDIO_SAVE_FILE
		//保存数据到文件中
		save_file_data(m_adec_file, tmp_stream.pStream, tmp_stream.u32Len);
#endif
	}

	if (ati) {
		//绑定ai和aenc内容
		tmp_bool_ret = unbind_ao_adec(ati->m_audio_dev, ati->m_audio_channel, ati->m_audio_process_channel);
		if (!tmp_bool_ret) {
			write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
				"unbind_ao_adec() failed!");
		}
		else {
			write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
				"unbind_ao_adec() successed!");
		}

		delete ati;
	}

	write_log(LOG_WARNING, WARNING_MODULE_OPERATION,
		"thread[%p] adec_thread_proc() stoped!", ati->m_thread_p);

#endif

	return true;
}

inline bool	hi3531a_audio_class::delay_sleep_wait_ns(int s, int ns)
{
#if defined(__linux__)

	//int						us_time = 0;

	struct timespec requested, remaining;

	requested.tv_sec = s;
	requested.tv_nsec = ns;

	while (nanosleep(&requested, &remaining) == -1)
		if (errno == EINTR)
			requested = remaining;
		else {
			break;
		}

		/*
		us_time = ns_time / 1000;
		if (us_time > 0)
		{
		struct timeval delay;
		delay.tv_sec = 0;
		delay.tv_usec = us_time;
		select(0, NULL, NULL, NULL, &delay);
		}
		*/

#else
	int				ms_time = 0;


	ms_time = (s * HI3531A_AUDIO_SEC_TO_MSEC) + (int)(ns / HI3531A_AUDIO_MSEC_TO_NSEC);
	if (ms_time < 1 || ms_time > 3600000) {
		sleep_millsecond(1);
	}
	else {
		sleep_millsecond(ms_time);
	}

#endif

	return true;
}

bool hi3531a_audio_class::bind_ao_adec(int ao_dev, int ao_channel, int adec_channel)
{
#if defined(HI3531A_MODE)

	MPP_CHN_S							tmp_src_chn;
	MPP_CHN_S							tmp_dest_chn;
	HI_S32								tmp_int_ret = 0;



	tmp_src_chn.enModId = HI_ID_ADEC;
	tmp_src_chn.s32DevId = 0;
	tmp_src_chn.s32ChnId = adec_channel;
	tmp_dest_chn.enModId = HI_ID_AO;
	tmp_dest_chn.s32DevId = ao_dev;
	tmp_dest_chn.s32ChnId = ao_channel;

	tmp_int_ret = HI_MPI_SYS_Bind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_SYS_Bind() ao_dev[%d] ao_channel[%d] adec_channel[%d] failed! error_code[0x%x].",
			ao_dev,
			ao_channel,
			adec_channel,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_SYS_Bind() ao_dev[%d] ao_channel[%d] adec_channel[%d] successed!",
			ao_dev,
			ao_channel,
			adec_channel);
	}

#endif

	return true;
}

bool hi3531a_audio_class::unbind_ao_adec(int ao_dev, int ao_channel, int adec_channel)
{
#if defined(HI3531A_MODE)

	MPP_CHN_S							tmp_src_chn;
	MPP_CHN_S							tmp_dest_chn;
	HI_S32								tmp_int_ret = 0;



	tmp_src_chn.enModId = HI_ID_ADEC;
	tmp_src_chn.s32ChnId = adec_channel;
	tmp_src_chn.s32DevId = 0;
	tmp_dest_chn.enModId = HI_ID_AO;
	tmp_dest_chn.s32DevId = ao_dev;
	tmp_dest_chn.s32ChnId = ao_channel;

	tmp_int_ret = HI_MPI_SYS_UnBind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_SYS_UnBind() ao_dev[%d] ao_channel[%d] adec_channel[%d] failed! error_code[0x%x].",
			ao_dev,
			ao_channel,
			adec_channel,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_SYS_UnBind() ao_dev[%d] ao_channel[%d] adec_channel[%d] successed!",
			ao_dev,
			ao_channel,
			adec_channel);
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_adec()
{
	stop_adec_thread_proc();
	stop_adec_channel();

	return true;
}

bool hi3531a_audio_class::stop_adec_channel()
{
#if defined(HI3531A_MODE)
	HI_S32								tmp_int_ret = 0;



	//创建编码通道
	tmp_int_ret = HI_MPI_ADEC_DestroyChn(m_adec_chn);
	if (tmp_int_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_ADEC_DestroyChn() channel[%d] failed! error_code[0x%x].",
			m_adec_chn,
			tmp_int_ret);

		return false;
	}
	else {
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_ADEC_DestroyChn() channel[%d] successed!",
			m_adec_chn);
	}

#endif

	return true;
}

bool hi3531a_audio_class::stop_adec_thread_proc()
{
	m_adec_is_start = false;
	m_adec_thread_group.timed_join_all(HI3531A_AUDIO_THREAD_JOIN_TIME_MS);
	return true;
}

//文件处理相关操作
FILE* hi3531a_audio_class::open_file(std::string name)
{
	FILE						*tmp_fd = 0;



	tmp_fd = fopen(cv_stoc(name), "wb");
	if (!tmp_fd)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open_file() [%s] failed! reason[%d:%s]",
			cv_stoc(name),
			errno,
			strerror(errno));
		return tmp_fd;
	}
	return tmp_fd;
}

int hi3531a_audio_class::save_file_data(FILE* fb, char* data, int len)
{
	int						tmp_int_return = 0;


	if (!fb || !data || !len)
	{
		return -1;
	}
	else
	{
		return fwrite(data, 1, len, fb);
	}

	return 0;
}

bool hi3531a_audio_class::close_file(FILE* fb)
{
	if (fb)
	{
		fclose(fb);
		fb = NULL;
	}
	return true;
}