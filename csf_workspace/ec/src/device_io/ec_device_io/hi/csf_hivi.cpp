/*******************************************************************************
*
*Copyright: f
*
*Author: f
*
*File name: csf_hivi.hpp
*
*Version: 1.0
*
*Date: 05-12月-2019 11:06:21
*
*Description: Class(csf_hivi)
*
*Others:
*
*History:
*
*******************************************************************************/

#include "hi_include.hpp"
#include "csf_hivi.hpp"
#include "csf_mdslot_cover.hpp"
#include "csf_h264_nalu.hpp"
#include "sleep_time.hpp"


using ec::core::csf_hivi;


csf_hivi::csf_hivi()
	: m_viconf(NULL)
	, m_attribute{ 0, } {

}

/**
* 功能：
*    使用参数创建对象
*
* @param hiproc    表示海思处理模块对象
* @param hiconf    表示海思通道配置信息
*/
csf_hivi::csf_hivi(csf_hiprocessor* hiproc, const hichannel_conf * hiconf)
	: csf_hivdev(hiproc, hiconf)
	, m_viconf(NULL)
	, m_attribute{ 0, } {

#ifdef WIN32
	get_mdpipe().set_mdslot(new csf_mdslot_cover(HIAI_CHANNEL_NAME, 32000));
#else
	get_mdpipe().set_mdslot(new csf_mdslot_cover(HIAI_CHANNEL_NAME, 32));
#endif
	
	get_mdpipe().set_mdpool(new csf_hipool_video(16, 128 * 1024));

}

csf_hivi::~csf_hivi() {
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
int csf_hivi::init(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	bool		tmp_bool_ret = false;


	tmp_bool_ret = init_dev();
	if (!tmp_bool_ret) {
		csf_log(error, "init_dev() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "init_dev() succeed!");
	}

	tmp_bool_ret = init_vpss();
	if (!tmp_bool_ret) {
		csf_log(error, "init_vpss() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "init_vpss() succeed!");
	}

	tmp_bool_ret = init_coder();
	if (!tmp_bool_ret) {
		csf_log(error, "init_coder() failed!");
		return csf_failure;
	}
	else {
		csf_log(notice, "init_coder() succeed!");
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
int csf_hivi::start(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	bool		tmp_bool_ret = false;


	tmp_bool_ret = start_dev();
	if (!tmp_bool_ret) {
		csf_log(error, "start_dev() failed!");
		return csf_failure;
	}

	tmp_bool_ret = start_vpss();
	if (!tmp_bool_ret) {
		csf_log(error, "start_vpss() failed!");
		return csf_failure;
	}

	tmp_bool_ret = start_coder();
	if (!tmp_bool_ret) {
		csf_log(error, "start_coder() failed!");
		return csf_failure;
	}

#if 0
	tmp_bool_ret = bind_dev_coder(get_attribute().dev_id
		, get_attribute().dev_channel
		, get_attribute().coder_channel);
	if (!tmp_bool_ret) {
		csf_log(error, "bind_dev_coder() failed!");
		return csf_failure;
	}
#endif

	tmp_bool_ret = start_coder_thread(this);
	if (!tmp_bool_ret) {
		csf_log(error, "start_coder_thread() failed!");
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
int csf_hivi::stop(csf_hiprocessor* hiproc, const hichannel_conf * hiconf) {

	bool		tmp_bool_ret = false;


	tmp_bool_ret = stop_coder_thread(this);
	if (!tmp_bool_ret) {
		csf_log(error, "stop_coder_thread() failed!");
		///return csf_failure;
	}

#if 0
	tmp_bool_ret = unbind_dev_coder(get_attribute().dev_id
		, get_attribute().dev_channel
		, get_attribute().coder_channel);
	if (!tmp_bool_ret) {
		csf_log(error, "unbind_dev_coder() failed!");
		//return csf_failure;
	}
#endif

	tmp_bool_ret = stop_coder();
	if (!tmp_bool_ret) {
		csf_log(error, "stop_coder() failed!");
		//return csf_failure;
	}

	tmp_bool_ret = stop_vpss();
	if (!tmp_bool_ret) {
		csf_log(error, "stop_vpss() failed!");
		//return csf_failure;
	}

	tmp_bool_ret = stop_dev();
	if (!tmp_bool_ret) {
		csf_log(error, "stop_dev() failed!");
		//return csf_failure;
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
bool csf_hivi::init_dev() {

#if defined(HI_BUILD_PLATFORM)

	get_attribute().dev_id = 0;
	get_attribute().dev_channel = 0;
	get_attribute().coder_channel = 0;

	//init vi first
	get_attribute().config.enViMode = SENSOR_TYPE;
	get_attribute().config.enRotate = ROTATE_NONE;
	get_attribute().config.enNorm = VIDEO_ENCODING_MODE_AUTO;
	get_attribute().config.enViChnSet = VI_CHN_SET_NORMAL;
	get_attribute().config.enWDRMode = WDR_MODE_NONE;
	get_attribute().config.enFrmRate = SAMPLE_FRAMERATE_DEFAULT;

	get_attribute().payload = PT_H264;
	get_attribute().gop_mode = VENC_GOPMODE_DUALP;
	get_attribute().profile = 0;
	get_attribute().rotate = ROTATE_NONE;
	//get_attribute().pic_size = PIC_HD1080;
	get_attribute().rc = SAMPLE_RC_CBR;
	get_attribute().video_norm = VIDEO_ENCODING_MODE_NTSC;

	SAMPLE_COMM_VI_GetSizeBySensor(&get_attribute().pic_size);

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
bool csf_hivi::start_dev() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32				tmp_int_ret = 0;


	tmp_int_ret = SAMPLE_COMM_VI_StartVi(&get_attribute().config);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VI_StartVi() failed! error_code[0x%x]!!!"
			, tmp_int_ret);
		return false;
	}
	else {
		csf_log(notice, "SAMPLE_COMM_VI_StartVi() succeed!");
	}

#if 0
	tmp_int_ret = HI_MPI_VI_EnableChn(get_attribute().dev_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VI_EnableChn() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, get_attribute().dev_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VI_EnableChn() attribute[dev:%d | channel:%d] succeed!"
			, get_attribute().dev_id
			, get_attribute().dev_channel);
	}
#endif

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
bool csf_hivi::stop_dev() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32				tmp_int_ret = 0;


#if 0
	tmp_int_ret = HI_MPI_VI_DisableChn(get_attribute().dev_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VI_DisableChn() attribute[dev:%d | channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().dev_id
			, get_attribute().dev_channel
			, tmp_int_ret);
	}
	else {
		csf_log(notice
			, "HI_MPI_VI_DisableChn() attribute[dev:%d | channel:%d] succeed!"
			, get_attribute().dev_id
			, get_attribute().dev_channel);
	}
#endif

	tmp_int_ret = SAMPLE_COMM_VI_StopVi(&get_attribute().config);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VI_StopVi() failed! error_code[0x%x]!!!"
			, tmp_int_ret);
		return false;
	}
	else {
		csf_log(notice, "SAMPLE_COMM_VI_StopVi() succeed!");
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
bool csf_hivi::init_coder() {
	return true;
}


/**
 * 功能：
 *    启动编解码器
 * 返回：
 *    true：表示成功；
 *    false：表示失败；
 */
bool csf_hivi::start_coder() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32				tmp_int_ret = 0;


	tmp_int_ret = SAMPLE_COMM_VENC_Start(get_attribute().coder_channel
		, get_attribute().payload
		, get_attribute().video_norm
		, get_attribute().pic_size
		, get_attribute().rc
		, get_attribute().profile
		, get_attribute().rotate);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VENC_Start() attribute[coder_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().coder_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VENC_Start() attribute[coder_channel:%d] succeed!"
			, get_attribute().coder_channel);
	}

	tmp_int_ret = SAMPLE_COMM_VENC_BindVpss(get_attribute().coder_channel
		, get_attribute().vpss_group
		, get_attribute().vpss_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VENC_BindVpss() attribute[coder_channel:%d | vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().coder_channel
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VENC_BindVpss() attribute[coder_channel:%d | vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().coder_channel
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
		);
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
 * @param hichannel    表示当前的csf_hivdev设备对象指针
 */
bool csf_hivi::start_coder_thread(csf_hivdev* hichannel) {

#if defined(HI_BUILD_PLATFORM)
	//创建线程
	set_thread(new csf_thread(csf_bind(&csf_hivi::coder_thread_process, this, this)));

	csf_log(notice, "create thread[%p] succeed!", get_thread());
#endif

#ifdef FILE_TEST
	//创建线程
	set_thread(new csf_thread(csf_bind(&csf_hivi::test_coder_thread_process, this, this)));

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
 * @param hichannel    表示当前的csf_hivdev设备对象指针
 */
bool csf_hivi::coder_thread_process(csf_hivdev* hichannel) {

#if defined(HI_BUILD_PLATFORM)

	bool					tmp_bool_ret = false;
	int						i = 0;
	HI_S32					tmp_int_ret = 0;
	fd_set					tmp_read_fds;
	HI_S32					tmp_fds = 0;
	struct timeval			tmp_timeout_val = { 0, };
	VENC_CHN_STAT_S			tmp_stat = { 0, };
	VENC_STREAM_S			tmp_stream = { 0, };
	VENC_STREAM_BUF_INFO_S	tmp_stream_buf_info = { 0, };
	const int				tmp_pack_buffer_number = 256;		//表示定义一个缓存VENC_PACK_S数量，减少处理过程中的内存分配
	VENC_PACK_S				tmp_pack[tmp_pack_buffer_number] = { 0, };
	csf_hiobject			*tmp_object = NULL;
	csf_mdslot				*tmp_mdslot = get_mdpipe().get_mdslot();
	csf_hipool				*tmp_hipool = dynamic_cast<csf_hipool*>(get_mdpipe().get_mdpool());


	tmp_int_ret = HI_MPI_VENC_GetStreamBufInfo(get_attribute().coder_channel
		, &tmp_stream_buf_info);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VENC_GetStreamBufInfo() attribute[coder_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().coder_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VENC_GetStreamBufInfo() attribute[coder_channel:%d] succeed!"
			, get_attribute().coder_channel);
	}

	tmp_fds = HI_MPI_VENC_GetFd(get_attribute().coder_channel);
	if (tmp_fds < 0) {
		csf_log(error
			, "HI_MPI_VENC_GetFd() attribute[coder_channel:%d] failed!"
			, get_attribute().coder_channel);
		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VENC_GetFd() attribute[coder_channel:%d | fd:%d] succeed!"
			, get_attribute().coder_channel
			, tmp_fds
		);
	}

	FD_ZERO(&tmp_read_fds);
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
				, "get venc stream time out [%d s]. select() attribute[channel:%d] warning!"
				, tmp_timeout_val.tv_sec
				, get_attribute().coder_channel);
			continue;
		}

		if (FD_ISSET(tmp_fds, &tmp_read_fds)) {

			/*******************************************************
			step 2.1 : query how many packs in one-frame stream.
			*******************************************************/
			memset(&tmp_stream, 0, sizeof(tmp_stream));

			tmp_int_ret = HI_MPI_VENC_Query(i, &tmp_stat);
			if (HI_SUCCESS != tmp_int_ret) {
				csf_log(error
					, "HI_MPI_VENC_Query() attribute[channel:%d] failed! error_code[0x%x]!!!"
					, get_attribute().coder_channel
					, tmp_int_ret);

				break;
			}
			/*******************************************************
			step 2.2 :suggest to check both u32CurPacks and u32LeftStreamFrames at the same time,for example:					 if(0 == stStat.u32CurPacks || 0 == stStat.u32LeftStreamFrames)
			{						SAMPLE_PRT("NOTE: Current  frame is NULL!\n");
			continue;
			}
			*******************************************************/
			if (0 == tmp_stat.u32CurPacks
				|| tmp_stat.u32CurPacks > tmp_pack_buffer_number)
			{
				//SAMPLE_PRT("NOTE: Current  frame is NULL!\n");
				csf_log(warning
					, "HI_MPI_VENC_Query() attribute[channel:%d | packs:%d] warning! NOTE: Current  frame is NULL! or more than %d"
					, get_attribute().coder_channel
					, tmp_stat.u32CurPacks
					, tmp_pack_buffer_number
				);
				continue;
			}
			/*******************************************************
			step 2.3 : malloc corresponding number of pack nodes.
			*******************************************************/
			tmp_stream.pstPack = tmp_pack;
			//stStream.pstPack = (VENC_PACK_S*)malloc(sizeof(VENC_PACK_S) * stStat.u32CurPacks);
			//if (NULL == stStream.pstPack)
			//{
			//	SAMPLE_PRT("malloc stream pack failed!\n");
			//	break;
			//}

			/*******************************************************
			step 2.4 : call mpi to get one-frame stream
			*******************************************************/
			tmp_stream.u32PackCount = tmp_stat.u32CurPacks;
			/* get frame from encoder */
			tmp_int_ret = HI_MPI_VENC_GetStream(get_attribute().coder_channel, &tmp_stream, HI_TRUE);
			if (HI_SUCCESS != tmp_int_ret) {

				csf_log(error
					, "HI_MPI_VENC_GetStream() attribute[channel:%d] failed! error_code[0x%x]!!!"
					, get_attribute().coder_channel
					, tmp_int_ret);
				break;
			}
			//else {
			//	csf_log(notice
			//		, "HI_MPI_VENC_GetStream() attribute[channel:%d] succeed!"
			//		, get_attribute().coder_channel);
			//}

			/************************************************************************/
			/* 将数据发送到媒体数据槽中，满足处理需求。                                 */
			/************************************************************************/
#ifdef HI_TEST_LOADER
			csf_log(notice
				, "sample video hichannel[ %p ] mdslot size[ %d ]."
				, this
				, tmp_mdslot->size()
			);
#endif
			
#ifndef __HuaweiLite__
			get_stream_by_memory_stream(tmp_hipool, tmp_mdslot, &tmp_stream);
#else
			get_stream_by_physical_stream(tmp_hipool, tmp_mdslot, &tmp_stream_buf_info, &tmp_stream);
#endif

			/* finally you must release the stream */
			tmp_int_ret = HI_MPI_VENC_ReleaseStream(get_attribute().coder_channel, &tmp_stream);
			if (HI_SUCCESS != tmp_int_ret) {
				csf_log(error
					, "HI_MPI_VENC_ReleaseStream() attribute[channel:%d] failed! error_code[0x%x]!!!"
					, get_attribute().coder_channel
					, tmp_int_ret);
				break;
			}
		}
	}

	//设置停止标记，停止线程
	get_thread()->stop();

	csf_log(warning, "stop thread[%p] succeed!", get_thread());

#endif

	return true;
}

#ifdef FILE_TEST
#ifdef _WIN32
#include <stddef.h>
typedef size_t ssize_t;
#else
#include <sys/time.h>
#endif
#include <stdio.h>
#include <sys/types.h>
unsigned char *csf_hivi::preload(const char *path, int *data_size)
{
	FILE *file = fopen(path, "rb");
	unsigned char *data;
	*data_size = 0;
	if (!file)
		return 0;
	if (fseek(file, 0, SEEK_END))
		exit(1);
	*data_size = (int)ftell(file);
	if (*data_size < 0)
		exit(1);
	if (fseek(file, 0, SEEK_SET))
		exit(1);
	data = (unsigned char*)malloc(*data_size);
	if (!data)
		exit(1);
	if ((int)fread(data, 1, *data_size, file) != *data_size)
		exit(1);
	fclose(file);
	return data;
}

int csf_hivi::get_nal_size(unsigned char *buf, int size)
{
	int pos = 3;
	while ((size - pos) > 3)
	{
		if (buf[pos] == 0 && buf[pos + 1] == 0 && buf[pos + 2] == 1)
			return pos;
		if (buf[pos] == 0 && buf[pos + 1] == 0 && buf[pos + 2] == 0 && buf[pos + 3] == 1)
			return pos;
		pos++;
	}
	return size;
}

/**
* 功能：
*    测试编解码线程处理函数
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param hichannel    表示当前的csf_hivdev设备对象指针
*/
bool csf_hivi::test_coder_thread_process(csf_hivdev* hichannel)
{
	csf_hiobject			*tmp_object = NULL;
	csf_mdslot				*tmp_mdslot = get_mdpipe().get_mdslot();
	csf_hipool				*tmp_hipool = dynamic_cast<csf_hipool*>(get_mdpipe().get_mdpool());
	
#if 0
	unsigned char			sps[] = { 0x00, 0x00, 0x00, 0x01, 0x67, 0x42, 0x00, 0x2a, 0x96, 0x35, 0xc0, 0xf0, 0x04, 0x4f, 0xcb, 0x37, 0x01, 0x01, 0x01, 0x02 };
	unsigned char			pps[] = { 0x00, 0x00, 0x00, 0x01, 0x68, 0xce, 0x3c, 0x80, 0x00, 0x00, 0x00, 0x01, 0x06, 0xe5, 0x01, 0xa1, 0x80 };


	tmp_object = static_cast<csf_hiobject_video*>(tmp_hipool->create(sizeof(sps)));
	if (tmp_object) {
		tmp_object->cat(sps
			, sizeof(sps)
			, 0
			, 0
		);
		tmp_mdslot->push_frame(tmp_object);
	}
	tmp_object = static_cast<csf_hiobject_video*>(tmp_hipool->create(sizeof(pps)));
	if (tmp_object) {
		tmp_object->cat(pps
			, sizeof(pps)
			, 0
			, 0
		);
		tmp_mdslot->push_frame(tmp_object);
	}
#endif

	//如果没有视频，则休眠等待
	csf::core::utils::time::sleep_time::sleep_ms(1000);
	csf_log(warning, "insert a test object");


	int h264_size;
	int frame_count = 0;
	int total_length = 0;
	unsigned char *alloc_buf;

	
	//unsigned char *buf_h264 = alloc_buf = preload("E:\\project_work\\arm_project\\kitty\\project\\trunk\\csf_library\\csf_workspace\\csf\\platform\\win32\\x64\\Debug\\stream_chn1.h264", &h264_size);
	unsigned char *buf_h264 = alloc_buf = preload("E:\\project_work\\arm_project\\kitty\\project\\trunk\\csf_library\\csf_workspace\\csf\\platform\\win32\\x64\\Debug\\123456-12345-19700101023221.mp4.h264", &h264_size);
	if (!buf_h264)
	{
		printf("error: can't open h264 file\n");
		return 0;
	}

	total_length = h264_size;
	while (h264_size > 0)
	{
		int nal_size = get_nal_size(buf_h264, h264_size);
		//printf("nal size=%ld, rest=%ld\n", nal_size, h264_size);
		if (!nal_size)
		{
			buf_h264 += 1;
			h264_size -= 1;
			continue;
		}

		tmp_object = static_cast<csf_hiobject_video*>(tmp_hipool->create(nal_size));
		if (tmp_object) {
			tmp_object->cat(buf_h264
				, nal_size
				, 90000 / 30
				, 0
			);
			tmp_mdslot->push_frame(tmp_object);
		}

		frame_count += 1;
		buf_h264 += nal_size;
		h264_size -= nal_size;

		printf("send length:%d   frames:%d\r\n"
			, total_length - h264_size
			, frame_count);
		
		csf::core::utils::time::sleep_time::sleep_ms(30);
	}

	//get_thread()->stop();
	return true;
}

#endif

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
bool csf_hivi::bind_dev_coder(int id, int channel, int coder_channel) {

	return bind_vi_vpss_venc();
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
bool csf_hivi::unbind_dev_coder(int id, int channel, int coder_channel) {

	return unbind_vi_vpss_venc();
}


/**
* 功能：
*    绑定vi、vpss、venc设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hivi::bind_vi_vpss_venc() {

#if defined(HI_BUILD_PLATFORM)

	MPP_CHN_S			tmp_src_chn;
	MPP_CHN_S			tmp_dest_chn;
	HI_S32				tmp_int_ret = 0;


	tmp_src_chn.enModId = HI_ID_VIU;
	tmp_src_chn.s32DevId = get_attribute().dev_id;
	tmp_src_chn.s32ChnId = get_attribute().dev_channel;
	tmp_dest_chn.enModId = HI_ID_VPSS;
	tmp_dest_chn.s32DevId = get_attribute().vpss_group;
	tmp_dest_chn.s32ChnId = get_attribute().vpss_channel;

	tmp_int_ret = HI_MPI_SYS_Bind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_Bind() bind[vi -- vpss] attribute[dev:%d | dev_channel:%d | vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_Bind() bind[vi -- vpss] attribute[dev:%d | dev_channel:%d | vpss_group:%d | vpss_channel:%d] succeed!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId);
	}

	tmp_src_chn.enModId = HI_ID_VPSS;
	tmp_src_chn.s32DevId = get_attribute().vpss_group;
	tmp_src_chn.s32ChnId = get_attribute().vpss_channel;
	tmp_dest_chn.enModId = HI_ID_VENC;
	tmp_dest_chn.s32DevId = 0;
	tmp_dest_chn.s32ChnId = get_attribute().coder_channel;

	tmp_int_ret = HI_MPI_SYS_Bind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_Bind() bind[vpss -- venc] attribute[vpss_group:%d | vpss_channel:%d | venc_dev:%d | venc_channel:%d] failed! error_code[0x%x]!!!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_Bind() bind[vi -- vpss] attribute[vpss_group:%d | vpss_channel:%d | venc_dev:%d | venc_channel:%d] succeed!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId);
	}

#endif
	return true;
}


/**
* 功能：
*    解除绑定vi、vpss、venc设备
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hivi::unbind_vi_vpss_venc() {

#if defined(HI_BUILD_PLATFORM)

	MPP_CHN_S			tmp_src_chn;
	MPP_CHN_S			tmp_dest_chn;
	HI_S32				tmp_int_ret = 0;


	tmp_src_chn.enModId = HI_ID_VIU;
	tmp_src_chn.s32DevId = get_attribute().dev_id;
	tmp_src_chn.s32ChnId = get_attribute().dev_channel;
	tmp_dest_chn.enModId = HI_ID_VPSS;
	tmp_dest_chn.s32DevId = get_attribute().vpss_group;
	tmp_dest_chn.s32ChnId = get_attribute().vpss_channel;

	tmp_int_ret = HI_MPI_SYS_UnBind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_UnBind() bind[vi -- vpss] attribute[dev:%d | dev_channel:%d | vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_UnBind() bind[vi -- vpss] attribute[dev:%d | dev_channel:%d | vpss_group:%d | vpss_channel:%d] succeed!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId);
	}

	tmp_src_chn.enModId = HI_ID_VPSS;
	tmp_src_chn.s32DevId = get_attribute().vpss_group;
	tmp_src_chn.s32ChnId = get_attribute().vpss_channel;
	tmp_dest_chn.enModId = HI_ID_VENC;
	tmp_dest_chn.s32DevId = 0;
	tmp_dest_chn.s32ChnId = get_attribute().coder_channel;

	tmp_int_ret = HI_MPI_SYS_UnBind(&tmp_src_chn, &tmp_dest_chn);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_SYS_UnBind() bind[vpss -- venc] attribute[vpss_group:%d | vpss_channel:%d | venc_dev:%d | venc_channel:%d] failed! error_code[0x%x]!!!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_SYS_UnBind() bind[vi -- vpss] attribute[vpss_group:%d | vpss_channel:%d | venc_dev:%d | venc_channel:%d] succeed!"
			, tmp_src_chn.s32DevId
			, tmp_src_chn.s32ChnId
			, tmp_dest_chn.s32DevId
			, tmp_dest_chn.s32ChnId);
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
bool csf_hivi::stop_coder() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32				tmp_int_ret = 0;


	tmp_int_ret = SAMPLE_COMM_VENC_UnBindVpss(get_attribute().coder_channel
		, get_attribute().vpss_group
		, get_attribute().vpss_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VENC_UnBindVpss() attribute[coder_channel:%d | vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().coder_channel
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VENC_UnBindVpss() attribute[coder_channel:%d | vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().coder_channel
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
		);
	}

	tmp_int_ret = SAMPLE_COMM_VENC_Stop(get_attribute().coder_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VENC_Stop() attribute[coder_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().coder_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VENC_Start() attribute[coder_channel:%d] succeed!"
			, get_attribute().coder_channel);
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
 * @param hichannel    表示当前的csf_hivdev设备对象指针
 */
bool csf_hivi::stop_coder_thread(csf_hivdev* hichannel) {

	if (get_thread()) {
		get_thread()->stop();
	}

	return true;
}


/**
* 功能：
*    初始化视频处理子系统
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hivi::init_vpss() {

#if defined(HI_BUILD_PLATFORM)
	SIZE_S				tmp_pic_size = { 0, };
	HI_S32				tmp_int_ret = 0;


	tmp_int_ret = SAMPLE_COMM_SYS_GetPicSize(get_attribute().video_norm
		, get_attribute().pic_size
		, &tmp_pic_size);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_SYS_GetPicSize() attribute[norm:%d | pic_size:%d] failed!"
			, get_attribute().video_norm
			, get_attribute().pic_size);
		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_SYS_GetPicSize() attribute[norm:%d | pic_size:%d | width:%d | height:%d] succeed!"
			, get_attribute().video_norm
			, get_attribute().pic_size
			, tmp_pic_size.u32Width
			, tmp_pic_size.u32Height
		);
	}

	get_attribute().vpss_group = 0;
	get_attribute().vpss_group_attr.u32MaxW = tmp_pic_size.u32Width;
	get_attribute().vpss_group_attr.u32MaxH = tmp_pic_size.u32Height;
	get_attribute().vpss_group_attr.bIeEn = HI_FALSE;
	get_attribute().vpss_group_attr.bNrEn = HI_TRUE;
	get_attribute().vpss_group_attr.bHistEn = HI_FALSE;
	get_attribute().vpss_group_attr.bDciEn = HI_FALSE;
	get_attribute().vpss_group_attr.enDieMode = VPSS_DIE_MODE_NODIE;
	get_attribute().vpss_group_attr.enPixFmt = SAMPLE_PIXEL_FORMAT;
	get_attribute().vpss_group_attr.bSharpenEn = HI_TRUE;

	get_attribute().vpss_channel = 0;

	get_attribute().vpss_channel_mode.enChnMode = VPSS_CHN_MODE_USER;
	get_attribute().vpss_channel_mode.bDouble = HI_FALSE;
	get_attribute().vpss_channel_mode.enPixelFormat = SAMPLE_PIXEL_FORMAT;
	get_attribute().vpss_channel_mode.u32Width = tmp_pic_size.u32Width;
	get_attribute().vpss_channel_mode.u32Height = tmp_pic_size.u32Height;
	get_attribute().vpss_channel_mode.enCompressMode = COMPRESS_MODE_NONE;

	memset(&get_attribute().vpss_channel_attr, 0, sizeof(get_attribute().vpss_channel_attr));
	get_attribute().vpss_channel_attr.s32SrcFrameRate = -1;
	get_attribute().vpss_channel_attr.s32DstFrameRate = -1;
#endif
	return true;
}


/**
* 功能：
*    启动视频处理子系统
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hivi::start_vpss() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32						tmp_int_ret = HI_FAILURE;


	tmp_int_ret = SAMPLE_COMM_VPSS_StartGroup(get_attribute().vpss_group
		, &get_attribute().vpss_group_attr);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_VPSS_StartGroup() attribute[vpss_group:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VPSS_StartGroup() attribute[vpss_group:%d] succeed!"
			, get_attribute().vpss_group);
	}

	tmp_int_ret = SAMPLE_COMM_VI_BindVpss(get_attribute().config.enViMode);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_VI_BindVpss() attribute[vpss_group:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VI_BindVpss() attribute[vpss_group:%d] succeed!"
			, get_attribute().vpss_group);
	}

	tmp_int_ret = SAMPLE_COMM_VPSS_EnableChn(get_attribute().vpss_group
		, get_attribute().vpss_channel
		, &get_attribute().vpss_channel_attr
		, &get_attribute().vpss_channel_mode
		, HI_NULL);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_VPSS_EnableChn() attribute[vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VPSS_EnableChn() attribute[vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
		);
	}

#if 0
	//表示创建一个VPSS
	tmp_int_ret = HI_MPI_VPSS_CreateGrp(get_attribute().vpss_group
		, &get_attribute().vpss_group_attr);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "HI_MPI_VPSS_CreateGrp() attribute[vpss_group:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VPSS_CreateGrp() attribute[vpss_group:%d] succeed!"
			, get_attribute().vpss_group);
	}

	//设置VPSS通道属性
	tmp_int_ret = HI_MPI_VPSS_SetChnAttr(get_attribute().vpss_group
		, get_attribute().vpss_channel
		, &get_attribute().vpss_channel_attr);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VPSS_SetChnAttr() attribute[vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VPSS_SetChnAttr() attribute[vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel);
	}

	//设置VPSS通道属性
	tmp_int_ret = HI_MPI_VPSS_SetChnMode(get_attribute().vpss_group
		, get_attribute().vpss_channel
		, &get_attribute().vpss_channel_mode);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VPSS_SetChnMode() attribute[vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VPSS_SetChnMode() attribute[vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel);
	}

	//启动VPSS通道
	tmp_int_ret = HI_MPI_VPSS_EnableChn(get_attribute().vpss_group
		, get_attribute().vpss_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "HI_MPI_VPSS_EnableChn() attribute[vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VPSS_EnableChn() attribute[vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel);
	}

	//启动VPSS组
	tmp_int_ret = HI_MPI_VPSS_StartGrp(get_attribute().vpss_group);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "HI_MPI_VPSS_StartGrp() attribute[vpss_group:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "HI_MPI_VPSS_StartGrp() attribute[vpss_group:%d] succeed!"
			, get_attribute().vpss_group);
	}

#endif

#endif

	return true;
}


/**
* 功能：
*    停止视频处理子系统
* 返回：
*    true：表示成功；
*    false：表示失败；
*/
bool csf_hivi::stop_vpss() {

#if defined(HI_BUILD_PLATFORM)
	HI_S32						tmp_int_ret = HI_FAILURE;


	tmp_int_ret = SAMPLE_COMM_VI_UnBindVpss(get_attribute().config.enViMode);
	if (tmp_int_ret != HI_SUCCESS) {
		csf_log(error
			, "SAMPLE_COMM_VI_UnBindVpss() attribute[vpss_group:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VI_UnBindVpss() attribute[vpss_group:%d] succeed!"
			, get_attribute().vpss_group);
	}

	//停止VPSS通道
	tmp_int_ret = SAMPLE_COMM_VPSS_DisableChn(get_attribute().vpss_group
		, get_attribute().vpss_channel);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VPSS_DisableChn() attribute[vpss_group:%d | vpss_channel:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VPSS_DisableChn() attribute[vpss_group:%d | vpss_channel:%d] succeed!"
			, get_attribute().vpss_group
			, get_attribute().vpss_channel);
	}

	//停止VPSS组
	tmp_int_ret = SAMPLE_COMM_VPSS_StopGroup(get_attribute().vpss_group);
	if (HI_SUCCESS != tmp_int_ret) {
		csf_log(error
			, "SAMPLE_COMM_VPSS_StopGroup() attribute[vpss_group:%d] failed! error_code[0x%x]!!!"
			, get_attribute().vpss_group
			, tmp_int_ret);

		return false;
	}
	else {
		csf_log(notice
			, "SAMPLE_COMM_VPSS_StopGroup() attribute[vpss_group:%d] succeed!"
			, get_attribute().vpss_group);
	}

#endif

	return true;
}


#if defined(HI_BUILD_PLATFORM)

/**
* 功能：
*    从逻辑内存中获取流数据
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param hipool    表示保存数据的内存池
* @param mdslot    表示获取后的数据存放入的数据槽
* @param stream    表示海思的流描述信息结构
*/
bool csf_hivi::get_stream_by_memory_stream(csf_hipool* hipool, csf_mdslot* mdslot, VENC_STREAM_S* stream) {

	int						i = 0;
	int						tmp_packe_length = 0;
	csf_hiobject_video		*tmp_object = NULL;
	csf_mdslot_cover		*tmp_mdslot = static_cast<csf_mdslot_cover*>(mdslot);


	for (i = 0; i < stream->u32PackCount; i++) {

		tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;

		tmp_object = static_cast<csf_hiobject_video*>(hipool->create(tmp_packe_length));
		if (tmp_object) {
			tmp_object->cat((unsigned char *)(stream->pstPack[i].pu8Addr + stream->pstPack[i].u32Offset)
				, tmp_packe_length
				, stream->pstPack[i].u64PTS
				, stream->u32Seq
			);
			set_nalu_type(tmp_object, stream->pstPack[i].DataType);
			if (tmp_mdslot->isfull()) {
				csf_log(error
					, "video hichannel[%p] mdslot[%d] is full!!!"
					, this
					, tmp_mdslot->size()
					);
			}
			mdslot->push_frame(tmp_object);
		}
	}

	return true;
}


/**
* 功能：
*    从物理内存中获取流数据
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param hipool    表示保存数据的内存池
* @param mdslot    表示获取后的数据存放入的数据槽
* @param stream_buf_info    定义码流 buffer信息的结构体
* @param stream    表示海思的流描述信息结构
*/
bool csf_hivi::get_stream_by_physical_stream(csf_hipool* hipool
	, csf_mdslot* mdslot
	, VENC_STREAM_BUF_INFO_S* stream_buf_info
	, VENC_STREAM_S* stream) {

	HI_U32					i = 0;
	HI_U32					tmp_phy_addr;
	HI_U32					tmp_left;
	HI_U32					tmp_packe_length = 0;
	HI_U32					tmp_sum_length = 0;
	csf_hiobject_video		*tmp_object = NULL;
	csf_mdslot_cover		*tmp_mdslot = static_cast<csf_mdslot_cover*>(mdslot);


	for (i = 0; i < stream->u32PackCount; i++) {

		if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Len >=
			stream_buf_info->u32PhyAddr + stream_buf_info->u32BufSize) {

			if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset >=
				stream_buf_info->u32PhyAddr + stream_buf_info->u32BufSize) {

				/* physical address retrace in offset segment */
				tmp_phy_addr = stream_buf_info->u32PhyAddr +
					((stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset) -
					(stream_buf_info->u32PhyAddr + stream_buf_info->u32BufSize));

				tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;

				tmp_object = static_cast<csf_hiobject_video*>(hipool->create(tmp_packe_length));
				if (tmp_object) {
					tmp_object->cat((unsigned char *)tmp_phy_addr
						, tmp_packe_length
						, stream->pstPack[i].u64PTS
						, stream->u32Seq
					);
					set_nalu_type(tmp_object, stream->pstPack[i].DataType);
					if (tmp_mdslot->isfull()) {
						csf_log(error
							, "video hichannel[%p] mdslot[%d] is full!!!"
							, this
							, tmp_mdslot->size()
						);
					}
					tmp_mdslot->push_frame(tmp_object);
				}
			}
			else {

				/* physical address retrace in data segment */
				tmp_left = (stream_buf_info->u32PhyAddr + stream_buf_info->u32BufSize) - stream->pstPack[i].u32PhyAddr;

				tmp_packe_length = (tmp_left - stream->pstPack[i].u32Offset) + (stream->pstPack[i].u32Len - tmp_left);

				tmp_object = static_cast<csf_hiobject_video*>(hipool->create(tmp_packe_length));
				if (tmp_object) {
					tmp_object->cat((unsigned char *)(stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset)
						, (tmp_left - stream->pstPack[i].u32Offset)
						, stream->pstPack[i].u64PTS
						, stream->u32Seq
					);
					tmp_object->cat((unsigned char *)(stream_buf_info->u32PhyAddr)
						, (stream->pstPack[i].u32Len - tmp_left)
						, stream->pstPack[i].u64PTS
						, stream->u32Seq
					);
					set_nalu_type(tmp_object, stream->pstPack[i].DataType);
					if (tmp_mdslot->isfull()) {
						csf_log(error
							, "video hichannel[%p] mdslot[%d] is full!!!"
							, this
							, tmp_mdslot->size()
						);
					}
					tmp_mdslot->push_frame(tmp_object);
				}
			}
		}
		else
		{
			/* physical address retrace does not happen */
			tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;

			tmp_object = static_cast<csf_hiobject_video*>(hipool->create(tmp_packe_length));
			if (tmp_object) {
				tmp_object->cat((unsigned char *)(stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset)
					, tmp_packe_length
					, stream->pstPack[i].u64PTS
					, stream->u32Seq
				);
				set_nalu_type(tmp_object, stream->pstPack[i].DataType);
				if (tmp_mdslot->isfull()) {
					csf_log(error
						, "video hichannel[%p] mdslot[%d] is full!!!"
						, this
						, tmp_mdslot->size()
					);
				}
				tmp_mdslot->push_frame(tmp_object);
			}
		}
	}

	return true;
}


/**
* 功能：
*    设置nalu帧数据的类型
* 返回：
*    true：表示成功；
*    false：表示失败；
*
* @param object    表示需要被设置的帧数据对象
* @param data_type    表示海思指定的帧类型
*/
void csf_hivi::set_nalu_type(csf_hiobject_video* object, VENC_DATA_TYPE_U &data_type) {

	/*
	typedef enum hiH264E_NALU_TYPE_E
	{
		H264E_NALU_PSLICE = 1,
		H264E_NALU_ISLICE = 5,
		H264E_NALU_SEI = 6,
		H264E_NALU_SPS = 7,
		H264E_NALU_PPS = 8,
		H264E_NALU_IPSLICE = 9,
		H264E_NALU_BUTT
	} H264E_NALU_TYPE_E;
	*/

	switch (data_type.enH264EType)
	{
	case H264E_NALU_BUTT:		//10
	{
		object->set_nalu_type(csf_h264_nalu::h264_nalu_nal);
	}
	break;
	default:
	{
		object->set_nalu_type((csf_h264_nalu::h264_nalu_type)(data_type.enH264EType));
	}
	break;
	}
}
#endif
