/*******************************************************************************
*
*Copyright:compony
*
*File name: hi3531a_hifb.cpp
*
*Author:fangzhenmu@compony.com.cn
*
*Version: 1.0
*
*Date:2018/02/08
*
*Description: create (hi3531a_hifb.cpp)
*
*Others:
*
*History:
*******************************************************************************/

#include "hi3531a_hifb.h"


#define HI3531A_HIFB_WIDTH								800
#define HI3531A_HIFB_HEIGHT								600
#define HI3531A_HIFB_SYS_ALIGN_WIDTH						16
#define HI3531A_HIFB_GRAPHICS_LAYER_HC0					3
#define HI3531A_HIFB_GRAPHICS_LAYER_G0					0
#define HI3531A_HIFB_GRAPHICS_LAYER_G1					1
#define HI3531A_HIFB_VO_DEV_DHD0							0

#if defined(HI3531A_MODE)
static struct fb_bitfield s_r16 = { 10, 5, 0 };
static struct fb_bitfield s_g16 = { 5, 5, 0 };
static struct fb_bitfield s_b16 = { 0, 5, 0 };
static struct fb_bitfield s_a16 = { 15, 1, 0 };

static struct fb_bitfield s_a32 = { 24,8,0 };
static struct fb_bitfield s_r32 = { 16,8,0 };
static struct fb_bitfield s_g32 = { 8,8,0 };
static struct fb_bitfield s_b32 = { 0,8,0 };
#endif


hi3531a_hifb_class::hi3531a_hifb_class()
{
#if defined(HI3531A_MODE)

	//系统配置
	//////////////////////////////////////////////////////////////////////////
	memset(&m_sys_conf, 0, sizeof(m_sys_conf));
	memset(&m_vb_conf, 0, sizeof(m_vb_conf));
	memset(&m_vo_dev, 0, sizeof(m_vo_dev));
	memset(&m_vo_layer, 0, sizeof(m_vo_layer));
	memset(&m_public_attr, 0, sizeof(m_public_attr));
	memset(&m_layer_attr, 0, sizeof(m_layer_attr));

	m_vo_dev = HI3531A_HIFB_VO_DEV_DHD0;
	m_vo_layer = HI3531A_HIFB_GRAPHICS_LAYER_G0;
#endif

}

hi3531a_hifb_class::~hi3531a_hifb_class()
{

}

bool hi3531a_hifb_class::init()
{
	bool						tmp_bool_ret = false;



	//初始化sys_init
	tmp_bool_ret = sys_init();
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION, "sys_init() failed!");
		return tmp_bool_ret;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION, "sys_init() successed!");
	}

#if defined(HI3531A_MODE)
	tmp_bool_ret = init_vo();
	if (!tmp_bool_ret) {
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"init_vo() failed!");
		return tmp_bool_ret;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"init_vo() successed!");
	}

    tmp_bool_ret = init_layer();
    if (!tmp_bool_ret)
    {
        write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
            "init_layer() failed!");
        return tmp_bool_ret;
    }
    else
    {
        write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
            "init_layer() successed!");
    }

#endif

	return true;
}

bool hi3531a_hifb_class::start()
{
#if defined(HI3531A_MODE)
	bool						tmp_bool_ret = false;



	//启动hd 并绑定图形层
	tmp_bool_ret = start_hd();
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"start_hd() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"start_hd() successed.");
	}

	//启动vo
	tmp_bool_ret = start_vo(m_vo_dev, m_public_attr);
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"start_vo() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"start_vo() successed.");
	}

	//启动layer
	tmp_bool_ret = start_layer(m_vo_layer, m_layer_attr);
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"start_layer() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"start_layer() successed.");
	}

	//启动hifb
	tmp_bool_ret = start_hifb(m_vo_layer);
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"start_layer() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"start_layer() successed.");
	}

#endif

	return true;
}

bool hi3531a_hifb_class::stop()
{
#if defined(HI3531A_MODE)
	bool						tmp_bool_ret = false;



	//停止layer
	tmp_bool_ret = stop_layer(m_vo_layer);
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"stop_layer() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"stop_layer() successed.");
	}

	//停止vo
	tmp_bool_ret = stop_vo(m_vo_dev);
	if (!tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"stop_vo() failed!");
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"stop_vo() successed.");
	}

#endif

	sys_exit();
	return true;
}

bool hi3531a_hifb_class::sys_init()
{
#if defined(HI3531A_MODE)
	HI_S32				tmp_int_ret = false;
	HI_U32				tmp_block_size = 0;



	sys_exit();

	//配置block size数值
	tmp_block_size = CEILING_2_POWER(HI3531A_HIFB_WIDTH, HI3531A_HIFB_SYS_ALIGN_WIDTH)\
		* CEILING_2_POWER(HI3531A_HIFB_HEIGHT, HI3531A_HIFB_SYS_ALIGN_WIDTH) * 2;

 	m_vb_conf.u32MaxPoolCnt = 128;
 	m_vb_conf.astCommPool[0].u32BlkSize = tmp_block_size;
 	m_vb_conf.astCommPool[0].u32BlkCnt = 16;
	m_vb_conf.astCommPool[1].u32BlkSize = 1024;
	m_vb_conf.astCommPool[1].u32BlkCnt = 64;
// 	m_vb_conf.u32MaxPoolCnt = VB_MAX_POOLS;
// 	m_vb_conf.astCommPool[0].u32BlkSize = tmp_block_size;
// 	m_vb_conf.astCommPool[0].u32BlkCnt = VB_MAX_COMM_POOLS;

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

	m_sys_conf.u32AlignWidth = HI3531A_HIFB_SYS_ALIGN_WIDTH;
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

bool hi3531a_hifb_class::sys_exit()
{
#if defined(HI3531A_MODE)
	HI_S32					i = 0;



	HI_MPI_SYS_Exit();

	for (i = 0; i < VB_MAX_USER; i++) {
		HI_MPI_VB_ExitModCommPool((VB_UID_E)i);
	}

	for (i = 0; i < VB_MAX_POOLS; i++) {
		HI_MPI_VB_DestroyPool(i);
	}

	HI_MPI_VB_Exit();

#endif

	return true;
}

#if defined(HI3531A_MODE)

bool	hi3531a_hifb_class::init_vo()
{
#if defined(HI3531A_MODE)

	m_public_attr.enIntfSync = VO_OUTPUT_800x600_60;
	m_public_attr.enIntfType = VO_INTF_VGA;
	m_public_attr.u32BgColor = 0x00FF00;

#endif
	return true;
}

bool	hi3531a_hifb_class::init_layer()
{
#if defined(HI3531A_MODE)
	SIZE_S							tmp_size;
	HI_U32							tmp_vo_frame_rate;
	HI_S32							tmp_bool_ret = HI_FALSE;


	m_layer_attr.bClusterMode = HI_FALSE;
	m_layer_attr.bDoubleFrame = HI_FALSE;
	m_layer_attr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

	tmp_bool_ret = get_vo_info_by_sync(m_public_attr.enIntfSync, &tmp_size.u32Width,
		&tmp_size.u32Height, &tmp_vo_frame_rate);
	if (HI_SUCCESS != tmp_bool_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"get_vo_info_by_sync() failed!");
		return false;
	}
	memcpy(&m_layer_attr.stImageSize, &tmp_size, sizeof(tmp_size));

	m_layer_attr.u32DispFrmRt = 30;
	m_layer_attr.stDispRect.s32X = 0;
	m_layer_attr.stDispRect.s32Y = 0;
	m_layer_attr.stDispRect.u32Width = tmp_size.u32Width;
	m_layer_attr.stDispRect.u32Height = tmp_size.u32Height;

#endif
	return true;
}

bool	hi3531a_hifb_class::init_hifb()
{
	return true;
}

bool	hi3531a_hifb_class::start_hd()
{
#if defined(HI3531A_MODE)
	HI_S32				tmp_int_ret = false;

	/******************************************
	step 3:  start vo hd0.
	*****************************************/
	tmp_int_ret = HI_MPI_VO_UnBindGraphicLayer(HI3531A_HIFB_GRAPHICS_LAYER_HC0, m_vo_dev);
	if (HI_SUCCESS != tmp_int_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_UnBindGraphicLayer() vo[dev:%d] failed! error_code[0x%x].",
			m_vo_dev,
			tmp_int_ret);
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_VO_UnBindGraphicLayer() vo[dev:%d] successed.",
			m_vo_dev);
	}

	tmp_int_ret = HI_MPI_VO_BindGraphicLayer(HI3531A_HIFB_GRAPHICS_LAYER_HC0, m_vo_dev);
	if (HI_SUCCESS != tmp_int_ret)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_BindGraphicLayer() vo[dev:%d] failed! error_code[0x%x].",
			m_vo_dev,
			tmp_int_ret);
		return false;
	}
	else
	{
		write_log(LOG_NOTICE, NOTICE_MODULE_OPERATION,
			"HI_MPI_VO_BindGraphicLayer() vo[dev:%d] successed.",
			m_vo_dev);
	}

#endif

	return true;
}

bool	hi3531a_hifb_class::start_vo(VO_DEV vo_dev, VO_PUB_ATTR_S &pub_attr)
{
#if defined(HI3531A_MODE)
	HI_S32						tmp_int_ret = HI_SUCCESS;


	tmp_int_ret = HI_MPI_VO_SetPubAttr(vo_dev, &pub_attr);
	if (tmp_int_ret != HI_SUCCESS)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_SetPubAttr() vo[dev:%d] failed! error_code[0x%x].",
			vo_dev,
			tmp_int_ret);
		return false;
	}

	tmp_int_ret = HI_MPI_VO_Enable(vo_dev);
	if (tmp_int_ret != HI_SUCCESS)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_Enable() vo[dev:%d] failed! error_code[0x%x].",
			vo_dev,
			tmp_int_ret);
		return false;
	}

#endif
	return true;
}

bool	hi3531a_hifb_class::start_layer(VO_LAYER layer, VO_VIDEO_LAYER_ATTR_S &layer_attr)
{
#if defined(HI3531A_MODE)
	HI_S32						tmp_int_ret = HI_SUCCESS;


	tmp_int_ret = HI_MPI_VO_SetVideoLayerAttr(layer, &layer_attr);
	if (tmp_int_ret != HI_SUCCESS)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_SetVideoLayerAttr() vo[layer:%d] failed! error_code[0x%x].",
			layer,
			tmp_int_ret);

		return false;
	}

	tmp_int_ret = HI_MPI_VO_EnableVideoLayer(layer);
	if (tmp_int_ret != HI_SUCCESS)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_SetVideoLayerAttr() vo[layer:%d] failed! error_code[0x%x].",
			layer,
			tmp_int_ret);

		return false;
	}

#endif
	return true;
}

bool	hi3531a_hifb_class::start_hifb(VO_LAYER layer)
{
#if defined(HI3531A_MODE)
	struct fb_var_screeninfo		tmp_var_info = { 0, };
	HI_CHAR							tmp_file_path[12] = "/dev/fb0";
	HI_U32							tmp_fd = 0;
	HI_BOOL							tmp_enable = HI_FALSE;
	HIFB_BUFFER_S					tmp_canvas_buffer = { 0, };
	HI_S32							tmp_int_ret = 0;
	HI_S32							i = 0;



	switch (layer)
	{
	case HI3531A_HIFB_GRAPHICS_LAYER_G0:
		strcpy(tmp_file_path, "/dev/fb0");
		break;
	case HI3531A_HIFB_GRAPHICS_LAYER_G1:
		strcpy(tmp_file_path, "/dev/fb1");
		break;
	default:
		strcpy(tmp_file_path, "/dev/fb0");
		break;
	}

	/* 1. open framebuffer device overlay 0 */
	tmp_fd = open(tmp_file_path, O_RDWR, 0);
	if (tmp_fd < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"open() [%s] failed!",
			tmp_file_path);

		return false;
	}

	tmp_enable = HI_FALSE;
	ioctl(tmp_fd, FBIOPUT_SHOW_HIFB, &tmp_enable);
	tmp_int_ret = ioctl(tmp_fd, FBIOGET_VSCREENINFO, &tmp_var_info);
	if (tmp_int_ret < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"FBIOGET_VSCREENINFO failed!");
		close(tmp_fd);

		return false;
	}

	tmp_var_info.red = s_r32;
	tmp_var_info.green = s_g32;
	tmp_var_info.blue = s_b32;
	tmp_var_info.transp = s_a32;
	tmp_var_info.bits_per_pixel = 32;
	tmp_var_info.xres = HI3531A_HIFB_WIDTH;
	tmp_var_info.yres = HI3531A_HIFB_HEIGHT;
	tmp_var_info.activate = FB_ACTIVATE_NOW;
	tmp_var_info.xres_virtual = HI3531A_HIFB_WIDTH;
	tmp_var_info.yres_virtual = HI3531A_HIFB_HEIGHT;
	tmp_var_info.xoffset = 0;
	tmp_var_info.yoffset = 0;

	tmp_int_ret = ioctl(tmp_fd, FBIOPUT_VSCREENINFO, &tmp_var_info);
	if (tmp_int_ret < 0)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"FBIOPUT_VSCREENINFO failed!");
		close(tmp_fd);
		return HI_NULL;
	}

	tmp_enable = HI_TRUE;
	ioctl(tmp_fd, FBIOPUT_SHOW_HIFB, &tmp_enable);

#endif

	return true;
}

HI_S32 hi3531a_hifb_class::get_vo_info_by_sync(VO_INTF_SYNC_E sync, HI_U32 *width, HI_U32 *height, HI_U32 *frame_rate)
{
	switch (sync)
	{
	case VO_OUTPUT_PAL:  *width = 720;  *height = 576;  *frame_rate = 25; break;
	case VO_OUTPUT_NTSC:  *width = 720;  *height = 480;  *frame_rate = 30; break;
	case VO_OUTPUT_576P50:  *width = 720;  *height = 576;  *frame_rate = 50; break;
	case VO_OUTPUT_480P60:  *width = 720;  *height = 480;  *frame_rate = 60; break;
	case VO_OUTPUT_800x600_60:  *width = 800;  *height = 600;  *frame_rate = 60; break;
	case VO_OUTPUT_720P50:  *width = 1280; *height = 720;  *frame_rate = 50; break;
	case VO_OUTPUT_720P60:  *width = 1280; *height = 720;  *frame_rate = 60; break;
	case VO_OUTPUT_1080I50:  *width = 1920; *height = 1080; *frame_rate = 50; break;
	case VO_OUTPUT_1080I60:  *width = 1920; *height = 1080; *frame_rate = 60; break;
	case VO_OUTPUT_1080P24:  *width = 1920; *height = 1080; *frame_rate = 24; break;
	case VO_OUTPUT_1080P25:  *width = 1920; *height = 1080; *frame_rate = 25; break;
	case VO_OUTPUT_1080P30:  *width = 1920; *height = 1080; *frame_rate = 30; break;
	case VO_OUTPUT_1080P50:  *width = 1920; *height = 1080; *frame_rate = 50; break;
	case VO_OUTPUT_1080P60:  *width = 1920; *height = 1080; *frame_rate = 60; break;
	case VO_OUTPUT_1024x768_60:  *width = 1024; *height = 768;  *frame_rate = 60; break;
	case VO_OUTPUT_1280x1024_60: *width = 1280; *height = 1024; *frame_rate = 60; break;
	case VO_OUTPUT_1366x768_60:  *width = 1366; *height = 768;  *frame_rate = 60; break;
	case VO_OUTPUT_1440x900_60:  *width = 1440; *height = 900;  *frame_rate = 60; break;
	case VO_OUTPUT_1280x800_60:  *width = 1280; *height = 800;  *frame_rate = 60; break;
	case VO_OUTPUT_1600x1200_60: *width = 1600; *height = 1200; *frame_rate = 60; break;
	case VO_OUTPUT_1680x1050_60: *width = 1680; *height = 1050; *frame_rate = 60; break;
	case VO_OUTPUT_1920x1200_60: *width = 1920; *height = 1200; *frame_rate = 60; break;
	case VO_OUTPUT_3840x2160_30: *width = 3840; *height = 2160; *frame_rate = 30; break;
	case VO_OUTPUT_3840x2160_60: *width = 3840; *height = 2160; *frame_rate = 60; break;
	case VO_OUTPUT_USER:     *width = 720;  *height = 576;  *frame_rate = 25; break;
	default:
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"vo sync not support!.");
		return HI_FAILURE;
	}
	return HI_SUCCESS;
}

bool	hi3531a_hifb_class::stop_layer(VO_LAYER layer)
{

	HI_S32					tmp_bool_ret = HI_SUCCESS;


	tmp_bool_ret = HI_MPI_VO_DisableVideoLayer(layer);
	if (tmp_bool_ret != HI_SUCCESS)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_DisableVideoLayer() vo[layer:%d] failed!",
			layer);

		return false;
	}
	return true;
}

bool	hi3531a_hifb_class::stop_hifb()
{
	return true;
}

bool	hi3531a_hifb_class::stop_vo(VO_DEV vo_dev)
{
#if defined(HI3531A_MODE)

	HI_S32					tmp_bool_ret = HI_SUCCESS;


	tmp_bool_ret = HI_MPI_VO_Disable((VO_DEV)vo_dev);
	if (tmp_bool_ret != HI_SUCCESS)
	{
		write_log(LOG_ERROR, ERROR_MODULE_OPERATION,
			"HI_MPI_VO_DisableVideoLayer() vo[dev:%d] failed!",
			vo_dev);

		return false;
	}

#endif
	return true;
}
#endif