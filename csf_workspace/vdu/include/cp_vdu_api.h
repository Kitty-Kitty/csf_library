/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_api.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_api.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_API_H_
#define _CP_VDU_API_H_



#include "cp_vdu.h"
#include "cp_vdu_status.h"



#ifdef __cplusplus
extern "C" {
#endif


	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_create
	*
	* 函数全名: cp_vdu_create
	*
	* 函数访问: public
	*
	* 函数说明: 创建一个cp_vdu_t对象
	*
	*
	* 返 回 值: cp_vdu_t *
	*         非NULL: 成功
	*         NULL  : 失败
	*
	* 备    注:该
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-2 15:10:45
	********************************************************************************/
	cp_extern cp_vdu_t *cp_vdu_create();

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_destroy
	*
	* 函数全名: cp_vdu_destroy
	*
	* 函数访问: public
	*
	* 函数说明: 销毁cp_vdu对象
	*
	* 参    数: cp_vdu_t       *vdu    [in]需要处理的vdu信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:56:18
	********************************************************************************/
	cp_extern int cp_vdu_destroy(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_version
	*
	* 函数全名: cp_vdu_get_version
	*
	* 函数访问: public
	*
	* 函数说明: 获取版本信息
	*
	* 参    数: cp_vdu_t * vdu						[in/out]参数说明
	*
	* 返 回 值: cp_vdu_version_t
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 16:53:47
	********************************************************************************/
	cp_vdu_version_t cp_vdu_get_version(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_status
	*
	* 函数全名: cp_vdu_get_status
	*
	* 函数访问: public
	*
	* 函数说明: 表示获取当前的状态码
	*
	* 参    数: cp_vdu_t * vdu						[in/out]参数说明
	*
	* 返 回 值: cp_vdu_status_e
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 17:10:50
	********************************************************************************/
	cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_coordinate
	*
	* 函数全名: cp_vdu_set_coordinate
	*
	* 函数访问: public
	*
	* 函数说明: 设置坐标信息,该坐标为模块在坐标系中的原点坐标。
	*
	* 参    数: cp_vdu_t       *vdu    [in]需要处理的vdu信息
	* 参    数: cp_vdu_coordinate_t coordinate		[in]初始坐标信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:
	*			1、该接口可以不使用时，默认位置为(0, 0, 0)
	*			2、如果使用该接口，则所有的roi、rect都使用以此为原点的坐标描述
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:24
	********************************************************************************/
	cp_extern int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_coordinate
	*
	* 函数全名: cp_vdu_get_coordinate
	*
	* 函数访问: public
	*
	* 函数说明: 获取初始坐标信息
	*
	* 参    数: cp_vdu_t       *vdu    [in]需要处理的vdu信息
	* 参    数: cp_vdu_coordinate_t *coordinate    [in]需要处理的vdu信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:32
	********************************************************************************/
	cp_extern int cp_vdu_get_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t *coordinate);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_type
	*
	* 函数全名: cp_vdu_set_type
	*
	* 函数访问: public
	*
	* 函数说明: 设备vdu的类型
	*
	* 参    数: cp_vdu_t * vdu						[in/out]参数说明
	* 参    数: cp_vdu_type_e type						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:17:07
	********************************************************************************/
	cp_extern int cp_vdu_set_type(cp_vdu_t *vdu, cp_vdu_type_e type);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_type
	*
	* 函数全名: cp_vdu_get_type
	*
	* 函数访问: public
	*
	* 函数说明: 获取vdu的类型
	*
	* 参    数: cp_vdu_t * vdu						[in/out]参数说明
	*
	* 返 回 值: cp_vdu_type_e
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:17:28
	********************************************************************************/
	cp_vdu_type_e cp_vdu_get_type(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_roi
	*
	* 函数全名: cp_vdu_set_roi
	*
	* 函数访问: public
	*
	* 函数说明: 设置感兴趣区域
	*
	* 参    数: cp_vdu_t       *vdu				[in]需要处理的vdu信息
	* 参    数: cp_vdu_rect_t	rect			[in]设置感兴趣区域位置信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:35
	********************************************************************************/
	cp_extern int cp_vdu_set_roi(cp_vdu_t *vdu, cp_vdu_rect_t rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_roi
	*
	* 函数全名: cp_vdu_get_roi
	*
	* 函数访问: public
	*
	* 函数说明: 获取感兴趣区域
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	* 参    数: cp_vdu_rect_t *rect             [in]需要处理的vdu信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:40
	********************************************************************************/
	cp_extern int cp_vdu_get_roi(cp_vdu_t *vdu, cp_vdu_rect_t *rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_clear_roi
	*
	* 函数全名: cp_vdu_clear_roi
	*
	* 函数访问: public
	*
	* 函数说明: 清除感兴趣区域
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:00
	********************************************************************************/
	cp_extern int cp_vdu_clear_roi(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_roi_pixel
	*
	* 函数全名: cp_vdu_get_roi_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 获取感兴趣区域位图流
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	* 参    数: char * buf						[out]参数说明
	* 参    数: int len							[in]参数说明
	* 参    数: cp_vdu_pixel_format_e vpf		[in]参数说明
	* 参    数: cp_vdu_rect_t *scale_rect		[in]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:05
	********************************************************************************/
	cp_extern int cp_vdu_get_roi_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_rect_pixel
	*
	* 函数全名: cp_vdu_get_rect_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	* 参    数: char * buf						[out]参数说明
	* 参    数: int len							[in]参数说明
	* 参    数: cp_vdu_pixel_format_e vpf		[in]参数说明
	* 参    数: cp_vdu_rect_t rect				[in]参数说明
	* 参    数: cp_vdu_rect_t *scale_rect		[in]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:14
	********************************************************************************/
	cp_extern int cp_vdu_get_rect_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);






	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_create_channel
	*
	* 函数全名: cp_vdu_create_channel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	* 参    数: cp_vdu_channel_type_e channel_type             [in]创建的通道类型
	*
	* 返 回 值: cp_vdu_channel_t*
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:17
	********************************************************************************/
	cp_vdu_channel_t* cp_vdu_create_channel(cp_vdu_t *vdu, cp_vdu_channel_type_e channel_type);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_destroy_all_channels
	*
	* 函数全名: cp_vdu_destroy_all_channels
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:23
	********************************************************************************/
	cp_extern int cp_vdu_destroy_all_channels(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_destroy_channel
	*
	* 函数全名: cp_vdu_destroy_channel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel						[in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:28
	********************************************************************************/
	cp_extern int cp_vdu_destroy_channel(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_status
	*
	* 函数全名: cp_vdu_channel_get_status
	*
	* 函数访问: public
	*
	* 函数说明: 表示获取当前的状态码
	*
	* 参    数: cp_vdu_t * vdu						[in/out]参数说明
	*
	* 返 回 值: cp_vdu_status_e
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 17:13:32
	********************************************************************************/
	cp_extern cp_vdu_status_e cp_vdu_channel_get_status(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_insert_channel
	*
	* 函数全名: cp_vdu_insert_channel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:34
	********************************************************************************/
	cp_extern int cp_vdu_insert_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_remove_channel
	*
	* 函数全名: cp_vdu_remove_channel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_t       *vdu             [in]需要处理的vdu信息
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:39
	********************************************************************************/
	cp_extern int cp_vdu_remove_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_index
	*
	* 函数全名: cp_vdu_channel_set_index
	*
	* 函数访问: public
	*
	* 函数说明: 该函数主要用于设备通道索引号。
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: const int index						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:
	*			1、通道索引号：表示通道在cp_vdu中的层次关系，索引号越大越靠近上层。
	*			2、通道索引号取值：[0, 65535)
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:42
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_index(cp_vdu_channel_t *vdu_channel, const int index);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_index
	*
	* 函数全名: cp_vdu_channel_get_index
	*
	* 函数访问: public
	*
	* 函数说明: 获取通道的索引信息
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:07:16
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_index(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_vector_stream
	*
	* 函数全名: cp_vdu_channel_set_vector_stream
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_vector_stream_type_e vs_type						[in/out]参数说明
	* 参    数: const char * buf						[in/out]参数说明
	* 参    数: const int len						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:14:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_vector_stream(cp_vdu_channel_t *vdu_channel,
		cp_vdu_vector_stream_type_e vs_type, const char *buf, const int len);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_roi
	*
	* 函数全名: cp_vdu_channel_set_roi
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_rect_t rect						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_roi
	*
	* 函数全名: cp_vdu_channel_get_roi
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_rect_t *roi_rect      [in]表示需要处理的通道
	*
	* 返 回 值: cp_vdu_rect_t
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:56
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t *roi_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_clear_roi
	*
	* 函数全名: cp_vdu_channel_clear_roi
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:01
	********************************************************************************/
	cp_extern int cp_vdu_channel_clear_roi(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_roi_pixel
	*
	* 函数全名: cp_vdu_channel_get_roi_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: char * buf						[in/out]参数说明
	* 参    数: int len						[in/out]参数说明
	* 参    数: cp_vdu_pixel_format_e vpf						[in/out]参数说明
	* 参    数: cp_vdu_rect_t *scale_rect						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* 函数全名: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* 函数访问: public
	*
	* 函数说明: 根据image info将rect指定的区域图形生成image图片
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_image_info_t *image_info						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);


	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_rect_pixel
	*
	* 函数全名: cp_vdu_channel_get_rect_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: char * buf						[in/out]参数说明
	* 参    数: int len						[in/out]参数说明
	* 参    数: cp_vdu_rect_t rect						[in/out]参数说明
	* 参    数: cp_vdu_pixel_format_e vpf						[in/out]参数说明
	* 参    数: cp_vdu_rect_t *scale_rect						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:09
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* 函数全名: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* 函数访问: public
	*
	* 函数说明: 根据image info将rect指定的区域图形生成image图片
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_image_info_t *image_info						[in/out]参数说明
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);








#ifdef __cplusplus
}
#endif


#endif //_CP_VDU_API_H_


