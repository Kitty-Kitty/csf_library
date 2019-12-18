/*******************************************************************************
*
*Copyright:fz
*
*File name: csf_typedef.hpp
*
*Author:armuxinxian@aliyun.com
*
*Version: 1.0
*
*Date:2018/06/27
*
*Description: create (csf_typedef.hpp),重新定义各种数据类型成为csf自已的数据类型
*
*Others:
*
*History:
*******************************************************************************/


#if !defined(_CSF_TYPEDEF_H_)
#define _CSF_TYPEDEF_H_


#include <stdint.h>
#ifdef __cplusplus
#include <iostream>
#endif


#ifdef __cplusplus
namespace csf
{
	namespace core
	{
		namespace base
		{
#endif
			typedef	void							csf_void;
			#define csf_null						NULL
#ifdef __cplusplus
			#define csf_nullptr						nullptr
			typedef bool							csf_bool;
			#define csf_false						false
			#define csf_true						true
#else
			#define csf_nullptr						NULL
			typedef enum
			{
				/**
				* 表示假
				*/
				csf_false = 0x00,
				/**
				* 表示真
				*/
				csf_true = 0x01
			} csf_bool;

#endif // __cplusplus
			typedef	char							csf_char;
			typedef signed short int				csf_short;
			typedef int								csf_int;
#ifdef WIN32
			typedef	__int64							csf_long;
#else
			typedef	long long						csf_long;
#endif
			typedef	time_t							csf_millsec;
			typedef	float							csf_float;
			typedef	double							csf_double;


			typedef unsigned char					csf_uchar;
			typedef unsigned short int				csf_ushort;
			typedef unsigned int					csf_uint;
#ifdef WIN32
			typedef	unsigned __int64				csf_ulong;
#else
			typedef	unsigned long long				csf_ulong;
#endif


			typedef signed char						csf_int8;
			typedef signed short int				csf_int16;
			typedef signed int						csf_int32;
#ifdef WIN32
			typedef	__int64							csf_int64;
#else
			typedef	long long						csf_int64;
#endif


			typedef unsigned char					csf_uint8;
			typedef unsigned short int				csf_uint16;
			typedef unsigned int					csf_uint32;
#ifdef WIN32
			typedef	unsigned __int64				csf_uint64;
#else
			typedef	unsigned long long				csf_uint64;
#endif

#ifdef __cplusplus
			typedef std::string						csf_string;
#endif

#ifdef __cplusplus
		}
	}
}
#endif

#include "csf_stdcollector.hpp"

#endif // !defined(_CSF_TYPEDEF_H_)


