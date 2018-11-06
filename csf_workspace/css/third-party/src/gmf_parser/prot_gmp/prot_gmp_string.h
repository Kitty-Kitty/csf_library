/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:string defined

**************************************************************************/



#ifndef	_PROT_GMP_STRING_H_
#define _PROT_GMP_STRING_H_




#include <stdio.h>
#include <stdarg.h>
#include "prot_gmp_core.h"






#define		gmp_cdecl
#define		GM_SDT_INT32_LEN   sizeof("-2147483648") - 1
#define		GM_SDT_INT64_LEN   sizeof("-9223372036854775808") - 1

#if (NGX_PTR_SIZE == 4)
#define		GM_SDT_INT_T_LEN   GM_SDT_INT32_LEN
#else
#define		GM_SDT_INT_T_LEN   GM_SDT_INT64_LEN
#endif


#if ((__GNU__ == 2) && (__GNUC_MINOR__ < 8))
#define GM_SDT_MAX_UINT32_VALUE  (unsigned int) 0xffffffffLL
#else
#define GM_SDT_MAX_UINT32_VALUE  (unsigned int) 0xffffffff
#endif


#define GM_SDT_LF						(unsigned char) 10
#define GM_SDT_CR						(unsigned char) 13
#define GM_SDT_CRLF						"\x0d\x0a"




#ifdef __cplusplus
extern "C"{;
#endif

gm_std_uchar * gmp_cdecl
	gmp_sprintf(gm_std_uchar *buf, const gm_std_char *fmt, ...);

gm_std_uchar * gmp_cdecl
	gm_gmp_sprintf(gm_std_uchar *buf, const gm_std_char *fmt, ...);

gm_std_uchar *
	gmp_vslprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, va_list args);

gm_std_uchar *
	gm_gmp_vslprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, va_list args);

#if defined(hi3531)
gm_std_uchar *
	gmp_sprintf_num(gm_std_uchar *buf, gm_std_uchar *last, gm_std_uint64 ui64, gm_std_uchar zero,
	gm_std_uint hexadecimal, gm_std_uint width);
#else
static gm_std_uchar *
	gmp_sprintf_num(gm_std_uchar *buf, gm_std_uchar *last, gm_std_uint64 ui64, gm_std_uchar zero,
	gm_std_uint hexadecimal, gm_std_uint width);
#endif

gm_std_int gm_gmp_gmdt_vslprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, gm_std_uchar *dt);


#ifdef __cplusplus
};
#endif



#endif













