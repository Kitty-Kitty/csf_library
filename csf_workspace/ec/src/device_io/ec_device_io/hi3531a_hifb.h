/*******************************************************************************
*
*Copyright:compony
*
*File name: hi3531a_hifb.h
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/08
*
*Description: create (hi3531a_hifb.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _HI3531A_HIFB_H_
#define _HI3531A_HIFB_H_


// #ifdef WIN32
// #define	HI3531A_MODE
// #endif


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
#include <linux/fb.h>
#endif


#include <sys/sem.h>
#include "hi_common.h"
#include "hi_comm_sys.h"
#include "hi_comm_vb.h"
#include "hi_comm_vi.h"
#include "hi_comm_vo.h"
#include "hi_comm_venc.h"
#include "hi_comm_vpss.h"
#include "hi_comm_vdec.h"
#include "hi_comm_vda.h"
#include "hi_comm_region.h"
#include "hi_comm_adec.h"
#include "hi_comm_aenc.h"
#include "hi_comm_ai.h"
#include "hi_comm_ao.h"
#include "hi_comm_aio.h"
#include "hi_comm_hdmi.h"
#include "hi_defines.h"

#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_vi.h"
#include "mpi_vo.h"
#include "mpi_venc.h"
#include "mpi_vpss.h"
#include "mpi_vdec.h"
#include "mpi_vda.h"
#include "mpi_region.h"
#include "mpi_adec.h"
#include "mpi_aenc.h"
#include "mpi_ai.h"
#include "mpi_ao.h"
#include "mpi_hdmi.h"

#include "hifb.h"
#include "hi_tde_api.h"
#include "hi_tde_type.h"
#include "hi_tde_errcode.h"

#endif

#include "hi_include.h"




class hi3531a_hifb_class;





typedef class hi3531a_hifb_class						hi3531a_hifb;




/************************************************************************/
/* 定义海狮音频信息                                                      */
/************************************************************************/
class hi3531a_hifb_class 
{
public:
	hi3531a_hifb_class();
	~hi3531a_hifb_class();

public:
	bool init();
	bool start();
	bool stop();

protected:
	bool sys_init();
	bool sys_exit();

	bool	init_vo();
	bool	init_layer();
	bool	init_hifb();

#if defined(HI3531A_MODE)
	bool	start_hd();
	bool	start_vo(VO_DEV vo_dev, VO_PUB_ATTR_S &pub_attr);
	bool	start_layer(VO_LAYER layer, VO_VIDEO_LAYER_ATTR_S &layer_attr);
	bool	start_hifb(VO_LAYER layer);

	HI_S32 get_vo_info_by_sync(VO_INTF_SYNC_E sync, HI_U32 *width, HI_U32 *height, HI_U32 *frame_rate);
	bool	stop_layer(VO_LAYER layer);
	bool	stop_hifb();
	bool	stop_vo(VO_DEV vo_dev);
#endif

private:
#if defined(HI3531A_MODE)
	//表示系统配置
	MPP_SYS_CONF_S				m_sys_conf;
	VB_CONF_S					m_vb_conf;

	VO_DEV						m_vo_dev;
	VO_LAYER					m_vo_layer;
	VO_PUB_ATTR_S				m_public_attr;
	VO_VIDEO_LAYER_ATTR_S		m_layer_attr;
#endif
};



#endif //_HI3531A_AUDIO_H_


