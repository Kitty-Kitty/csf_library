/*******************************************************************************
*
*Copyright:compony
*
*File name: hi3531a_audio.h
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/08
*
*Description: create (hi3531a_audio.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _HI3531A_AUDIO_H_
#define _HI3531A_AUDIO_H_


// #ifdef WIN32
// #define	HI3531A_MODE
// #endif

#define HI3531A_HIFB	1

#if defined(HI3531A_MODE)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(__linux__)
#include <pthread.h>
#include <sys/ioctl.h>
#endif

#include "hi_common.h"
#include "hi_comm_sys.h"
#include "hi_comm_vb.h"
#include "hi_comm_adec.h"
#include "hi_comm_aenc.h"
#include "hi_comm_ai.h"
#include "hi_comm_ao.h"
#include "hi_comm_aio.h"
#include "hi_defines.h"

#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_adec.h"
#include "mpi_aenc.h"
#include "mpi_ai.h"
#include "mpi_ao.h"

#include "tlv320aic31.h"
#include "tp2823.h"


#define CSS_DEV_IO_AERO_ANALYZER_SYS_ALIGN_WIDTH						16

#endif



#include "hi_audio.h"
#include "hi3531a_audio_thread_info.h"

#ifdef HI3531A_HIFB
#include "hi3531a_hifb.h"
#endif




class hi3531a_audio_class;





typedef class hi3531a_audio_class						hi3531a_audio;




/************************************************************************/
/* 定义海狮音频信息                                                      */
/************************************************************************/
class hi3531a_audio_class : public virtual hi_audio
{
public:
	hi3531a_audio_class();
	~hi3531a_audio_class();

public:
	bool init();
	bool start();
	bool stop();

protected:
	bool sys_init();
	bool sys_exit();

#ifdef HI3531A_HIFB
	bool	start_hi3531a_hifb();
	bool	stop_hi3531a_hifb();
#endif
	bool init_ai();
#if defined(HI3531A_MODE)
	HI_S32	set_audio_acodec(AIO_ATTR_S *pstAioAttr);
	HI_S32	set_audio_tlv320_acodec(AIO_MODE_E work_mode, AUDIO_SAMPLE_RATE_E sample);
	HI_S32	set_audio_tw2865_acodec(AUDIO_SAMPLE_RATE_E sample);
	HI_S32	set_audio_tw2865_format(AIO_MODE_E work_mode);
	HI_S32	set_audio_tw2865_bit_width(AUDIO_BIT_WIDTH_E bit_width);
	HI_S32	set_audio_tp2823_format(const AIO_ATTR_S *aio_attr);
#endif
	bool start_ai();
	bool start_ai_resample(int ai_dev_id, int ai_channel);
	bool start_ai_vqe(int ai_dev_id, int ai_channel, int ao_dev_id, int ao_channel);
	bool set_ai_vqe_volume(int ai_dev_id, int ai_channel, int volume_db);
	bool stop_ai();
	bool stop_ai_resample(int ai_dev_id, int ai_channel);
	bool stop_ai_vqe(int ai_dev_id, int ai_channel);

	bool init_ao();
	bool start_ao();
	bool start_ao_resample(int ao_dev_id, int ao_channel);
	bool start_ao_vqe(int ao_dev_id, int ao_channel);
	bool set_ao_vqe_volume(int ao_dev_id, int ao_channel, int volume_db);
	bool stop_ao();
	bool stop_ao_resample(int ao_dev_id, int ao_channel);
	bool stop_ao_vqe(int ao_dev_id, int ao_channel);

	bool init_aenc();
	bool start_aenc();
	bool start_aenc_thread_proc(hi3531a_audio_thread_info &ati);
	bool aenc_thread_proc(hi3531a_audio_thread_info *ati);
	bool bind_ai_aenc(int ai_dev, int ai_channel, int aenc_channel);
	bool unbind_ai_aenc(int ai_dev, int ai_channel, int aenc_channel);
	bool stop_aenc();
	bool stop_aenc_channel();
	bool stop_aenc_thread_proc();

	bool init_adec();
	bool start_adec();
	bool start_adec_thread_proc(hi3531a_audio_thread_info &ati);
	bool adec_thread_proc(hi3531a_audio_thread_info *ati);
	bool delay_sleep_wait_ns(int s, int ns);
	bool bind_ao_adec(int ao_dev, int ao_channel, int adec_channel);
	bool unbind_ao_adec(int ao_dev, int ao_channel, int adec_channel);
	bool stop_adec();
	bool stop_adec_channel();
	bool stop_adec_thread_proc();

	//文件处理相关操作
	FILE* open_file(std::string name);
	int save_file_data(FILE* fb, char* data, int len);
	bool close_file(FILE* fb);

private:
#if defined(HI3531A_MODE)
	//表示系统配置
	MPP_SYS_CONF_S				m_sys_conf;
	VB_CONF_S					m_vb_conf;

	AUDIO_DEV					m_ai_dev;
	AI_CHN						m_ai_chn;
	AUDIO_DEV					m_ao_dev;
	AO_CHN						m_ao_chn;
	ADEC_CHN					m_adec_chn;
	AENC_CHN					m_aenc_chn;
	int							m_adec_channel_count;
	int							m_aenc_channel_count;

	int							m_ai_volume;
	int							m_ao_volume;

	AIO_ATTR_S					m_ai_attr;
	AIO_ATTR_S					m_ao_attr;

	//表示编码属性
	int							m_aenc_fd;
	AENC_CHN_ATTR_S				m_aenc_attr;
	AENC_ATTR_ADPCM_S			m_aenc_adpcm_attr;
	AENC_ATTR_G711_S			m_aenc_g711_attr;
	AENC_ATTR_G726_S			m_aenc_g726_attr;
	AENC_ATTR_LPCM_S			m_aenc_lpcm_attr;
	AUDIO_FRAME_S				m_aenc_frame;
	AI_CHN_PARAM_S				m_aenc_ai_chn_para;

	//表示解码属性
	int							m_adec_fd;
	ADEC_CHN_ATTR_S				m_adec_attr;
	ADEC_ATTR_ADPCM_S			m_adec_adpcm_attr;
	ADEC_ATTR_G711_S			m_adec_g711_attr;
	ADEC_ATTR_G726_S			m_adec_g726_attr;
	ADEC_ATTR_LPCM_S			m_adec_lpcm_attr;
	AUDIO_FRAME_S				m_adec_frame;


	AI_VQE_CONFIG_S				m_ai_vqe_conf;								//表示音频输入增强配置
	AO_VQE_CONFIG_S				m_ao_vqe_conf;								//表示音频输出增强配置

	AUDIO_SAMPLE_RATE_E			m_out_resample_rate;
#endif
	bool						m_is_init_system;							//表示是否初始化系统
	bool						m_is_ai_resample;							//表示是否音频增强
	bool						m_is_ao_resample;							//表示是否音频增强
	bool						m_is_ai_used_vqe;							//表示是否音频增强
	bool						m_is_ao_used_vqe;							//表示是否音频增强

	FILE						*m_aenc_file;								//表示保存编码数据到文件中
	FILE						*m_adec_file;								//表示保存解码数据到文件中
#ifdef HI3531A_HIFB
	hi3531a_hifb				m_hi3531a_hifb;									//表示hi3531a_hifb设备内容
#endif
};



#endif //_HI3531A_AUDIO_H_


