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
/* ��ʾ����ֵ�����Сֵ����                                               */
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
/* ����ɹ���ʧ��Ĭ��ֵ                                                   */
/************************************************************************/
#define csf_succeed							0					//��ʾ��ȷ��Ĭ�Ϸ���ֵ��int���غ���Ĭ��0��ʾ�ɹ���
#define csf_failure							-1					//��ʾʧ�ܵ�Ĭ�Ϸ���ֵ��int���غ���Ĭ�Ϸ�0��ʾʧ�ܡ�



/************************************************************************/
/* ����������Ϣ                                                          */
/************************************************************************/
#define csf_errno_max_length				512					//��ʾ����������Ϣ����󳤶�



/************************************************************************/
/* ��ʾϵͳ����Ĭ����ֵ                                                   */
/************************************************************************/
#define csf_default_time_resolution			300					//��ʾϵͳĬ�ϵ�ʱ�侫�ȣ���λ������
#define csf_default_timer_resolution		500					//��ʾϵͳĬ�ϵĶ�ʱ��ʱ�侫�ȣ���λ������
#define csf_default_device_limit			128					//��ʾϵͳĬ�ϵ�����豸����
#define csf_default_device_io_limit			512					//��ʾϵͳĬ�ϵ�����豸io����
#define csf_default_connect_limit			1024				//��ʾϵͳĬ�ϵ������������

#endif //_CSF_DEFAULT_H_


