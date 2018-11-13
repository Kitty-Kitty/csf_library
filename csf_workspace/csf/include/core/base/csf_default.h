/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_default.h
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_default.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CSF_DEFAULT_H_
#define _CSF_DEFAULT_H_


/************************************************************************/
/* 表示数据值最大最小值定义                                               */
/************************************************************************/
#define	csf_min_char					(-127 - 1)
#define	csf_min_short					(-32767 - 1)
#define	csf_min_int						(-2147483647 - 1)
#define	csf_min_long					(-9223372036854775807LL - 1)



#define	csf_min_uchar						0
#define	csf_min_ushort						0
#define	csf_min_uint						0
#define	csf_min_ulong						0



#define	csf_max_char						127i8
#define	csf_max_short						32767i16
#define	csf_max_int							2147483647i32
#define	csf_max_long						9223372036854775807LL


#define	csf_max_uchar						0xffu
#define	csf_max_ushort						0xffffu
#define	csf_max_uint						0xffffffffu
#define	csf_max_ulong						0xffffffffffffffffuLL



#define	csf_min_int8						csf_min_char
#define	csf_min_int16						csf_min_short	
#define	csf_min_int32						csf_min_int		
#define	csf_min_int64						csf_min_long	



#define	csf_min_uint8						csf_min_uchar	
#define	csf_min_uint16						csf_min_ushort	
#define	csf_min_uint32						csf_min_uint	
#define	csf_min_uint64						csf_min_ulong	



#define	csf_max_int8						csf_max_char
#define	csf_max_int16						csf_max_short	
#define	csf_max_int32						csf_max_int		
#define	csf_max_int64						csf_max_long	



#define	csf_max_uint8						csf_max_uchar	
#define	csf_max_uint16						csf_max_ushort	
#define	csf_max_uint32						csf_max_uint	
#define	csf_max_uint64						csf_max_ulong	



/************************************************************************/
/* 定义成功与失败默认值                                                   */
/************************************************************************/
#define csf_succeed							0					//表示正确的默认返回值，int返回函数默认0表示成功。
#define csf_failure							-1					//表示失败的默认返回值，int返回函数默认非0表示失败。



/************************************************************************/
/* 错误描述信息                                                          */
/************************************************************************/
#define csf_errno_max_length				512					//表示错误描述信息的最大长度



/************************************************************************/
/* 表示系统限制默认数值                                                   */
/************************************************************************/
#define csf_default_time_resolution			300					//表示系统默认的时间精度，单位：毫秒
#define csf_default_timer_resolution		500					//表示系统默认的定时器时间精度，单位：毫秒
#define csf_default_device_limit			128					//表示系统默认的最大设备数量
#define csf_default_device_io_limit			512					//表示系统默认的最大设备io数量
#define csf_default_connect_limit			1024				//表示系统默认的最大连接数量

#endif //_CSF_DEFAULT_H_


