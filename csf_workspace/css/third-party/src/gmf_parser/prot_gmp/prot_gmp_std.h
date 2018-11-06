/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:std defined

**************************************************************************/




#ifndef	_PROT_GMP_STD_H_
#define _PROT_GMP_STD_H_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if defined(WIN32)
#define	gmp_std_null								NULL
// Linux
#elif defined(__linux__)
#define	gmp_std_null								NULL

#endif




#define gmp_std_sizeof(s)							sizeof(s)
#define gmp_std_memcpy(dest, srcs, len)				memcpy(dest, srcs, len)
#define gmp_std_cpymem(dst, src, n)					(((unsigned char *) memcpy(dst, src, n)) + (n))
#define gmp_std_memset(s, ch, n)					memset(s, ch, n)
#define gmp_std_strcmp								strcmp
#define gmp_std_strncmp(s1, s2, n)					strncmp((const char *) s1, (const char *) s2, n)
#define	gmp_std_malloc(s)							malloc(s)
#define	gmp_std_strlen								strlen
#define	gmp_std_strcpy								strcpy
#define	gmp_std_strncpy								strncpy


#define	gmp_std_sprintf								sprintf












#endif




