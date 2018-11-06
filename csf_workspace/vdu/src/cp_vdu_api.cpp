/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_api.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_api.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_vdu.h"
#include "vdu_core.h"


//创建一个cp_vdu_t对象
cp_vdu_t* cp_vdu_create() {
	cp_vdu_t					*tmp_vdu = NULL;
	

	return tmp_vdu;
}

//销毁cp_vdu对象
int cp_vdu_destroy(cp_vdu_t *vdu) {
	int							tmp_ret_int = 0;
	

	return cp_vdu_status_success;
}

//获取版本信息
cp_vdu_version_t cp_vdu_get_version(cp_vdu_t *vdu)
{
	cp_vdu_version_t						tmp_version = {
		CSF_VDU_VAR,
		csf_vdu_version,
		CSF_VDU_VERSION,
		CSF_VDU_VER
	};

	return tmp_version;
}

//获取vdu的状态码
cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu)
{
	int						tmp_ret_int = 0;


	return cp_vdu_status_null_pointer;
}

//设置坐标信息
int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate)
{
	int						tmp_ret_int = 0;

	return tmp_ret_int;
}

int cp_vdu_set_type(cp_vdu_t *vdu, cp_vdu_type_e type)
{
	int					tmp_ret_int = 0;
	

	return cp_vdu_status_success;
}

cp_vdu_type_e cp_vdu_get_type(cp_vdu_t *vdu)
{
	int					tmp_ret_int = 0;
	

	return vdu->type;
}

int cp_vdu_set_roi(cp_vdu_t *vdu, cp_vdu_rect_t rect)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_get_roi(cp_vdu_t *vdu, cp_vdu_rect_t *rect)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_clear_roi(cp_vdu_t *vdu)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_get_roi_pixel(cp_vdu_t *vdu,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t *scale_rect)
{
	int						tmp_ret_int = 0;
	
	return tmp_ret_int;
}

int cp_vdu_get_rect_pixel(cp_vdu_t *vdu,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t rect,
	cp_vdu_rect_t *scale_rect)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_init(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info)								/*模块创建接口，表示创建一个模块*/
{
	return cp_vdu_status_success;
}

int cp_vdu_open(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info)								/*模块打开运行接口，在模块init之后，会被调用*/
{
	return cp_vdu_status_success;
}

int cp_vdu_read(cp_vdu_t *vdu, char **buf, int len, int flag)								/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
{
	return cp_vdu_status_success;
}

int cp_vdu_write(cp_vdu_t *vdu, const char **buf, int len, int flag)						/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
{
	return cp_vdu_status_success;
}

int cp_vdu_close(cp_vdu_t *vdu)																/*关闭模块*/
{
	return cp_vdu_status_success;
}

int cp_vdu_exit(cp_vdu_t *vdu)																/*退出模块*/
{
	return cp_vdu_status_success;
}

int cp_vdu_set_option(cp_vdu_t *vdu, int optname, const void* optval)						/*设置模块参数*/
{
	return cp_vdu_status_success;
}

int cp_vdu_get_option(cp_vdu_t *vdu, int optname, void* optval)								/*获取模块参数*/
{
	return cp_vdu_status_success;
}


cp_vdu_channel_t* cp_vdu_create_channel(cp_vdu_t *vdu, cp_vdu_channel_type_e channel_type)
{
	int						tmp_ret_int = 0;
	

	return NULL;
}

int cp_vdu_destroy_all_channels(cp_vdu_t *vdu)
{
	int						tmp_ret_int = 0;
	
	
	return cp_vdu_status_success;
}

int cp_vdu_destroy_channel(cp_vdu_channel_t *vdu_channel)
{
	int						tmp_ret_int = 0;
	

	return cp_vdu_status_success;
}

cp_vdu_status_e cp_vdu_channel_get_status(cp_vdu_channel_t *vdu_channel)
{
	int						tmp_ret_int = 0;
	

	return cp_vdu_status_failed;
}

int cp_vdu_insert_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_remove_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_set_index(cp_vdu_channel_t *vdu_channel, const int index)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_get_index(cp_vdu_channel_t *vdu_channel)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_set_vector_stream(cp_vdu_channel_t *vdu_channel,
	cp_vdu_vector_stream_type_e vs_type, const char *buf, const int len)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_set_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t rect)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_get_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t *roi_rect)
{
	int								tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_clear_roi(cp_vdu_channel_t *vdu_channel)
{
	int								tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_get_roi_pixel(cp_vdu_channel_t *vdu_channel,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t *scale_rect)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_get_roi_pixel_by_image_info(
	cp_vdu_channel_t *vdu_channel,
	cp_vdu_image_info_t *image_info)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_get_rect_pixel(cp_vdu_channel_t *vdu_channel,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t rect,
	cp_vdu_rect_t *scale_rect)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}

int cp_vdu_channel_get_rect_pixel_by_image_info(
	cp_vdu_channel_t *vdu_channel,
	cp_vdu_image_info_t *image_info)
{
	int						tmp_ret_int = 0;
	

	return tmp_ret_int;
}
