/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_stddef.h
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_stddef.h)表示对一些标准库的重定义
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CSF_STDDEF_H_
#define _CSF_STDDEF_H_


#include <stdlib.h>
#include <string.h>


#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


#ifdef __cplusplus
namespace csf
{
	namespace core
	{
		namespace base
		{
#endif

#define csf_memset							memset
#define csf_memcpy							memcpy
#define csf_memmove							memmove
#define csf_malloc							malloc
#define csf_free							free
#define csf_sizeof							sizeof
#define csf_strlen							strlen
#define csf_strcpy							strcpy
#define	csf_strncpy							strncpy
#define csf_strcmp							strcmp
#define	csf_strncmp							strncmp
#define	csf_printf							printf
#define	csf_scanf							scanf
#define	csf_htonl							htonl
#define	csf_ntohl							ntohl
#define	csf_htons							htons
#define	csf_ntohs							ntohs
#define	csf_rand							rand
#if defined(WIN32)
#define	csf_msleep(millsec)					Sleep(millsec)				//毫秒单位
#else
#define	csf_msleep(millsec)					usleep(millsec * 1000)		//毫秒单位
#endif
#define	csf_srand()							srand((uint32_t)time(NULL));
#define	csf_sprintf							sprintf
#define	csf_snprintf						snprintf
#if defined(WIN32)
#define	csf_vsnprintf						_vsnprintf
#else
#define	csf_vsnprintf						vsnprintf
#endif

#define	csf_vscprintf						_vscprintf


#define csf_atoi							atoi
#define csf_atoint32						atoi

#if defined(WIN32)
#define csf_atoint64						_atoi64
#else
#define csf_atoint64						atoll
#endif


//核验字符串非空白字符，ascii 数值范围[33, 126]，即[!, ~].非空为true，空为false
#define csf_char_no_space(ch)				((ch) >= 33 && (ch) <= 126)

#if defined(WIN32)
#define csf_symbol_export					_declspec(dllexport)
#else
#define csf_symbol_export					
#endif

#define csf_dec_abs(a, b)					((a) >= (b) ? ((a) - (b)) : ((b) - (a)))


#ifdef __cplusplus
		}
	}
}
#endif



#endif //_CSF_STDDEF_H_


