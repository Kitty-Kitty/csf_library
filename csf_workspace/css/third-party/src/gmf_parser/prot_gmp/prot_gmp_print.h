/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:printf defined

**************************************************************************/



#ifndef	_PROT_GMP_PRINT_H_
#define _PROT_GMP_PRINT_H_






#include <stdio.h>
#include <stdlib.h>
#include <string.h>






#include "prot_gmp_core.h"
#include "prot_gmp_gmf.h"




#define CSS_PRINT_STRING_MAX_LEN					128
#define CSS_GMP_PRINT_TO_LOG
//#define CSS_GMP_PRINT_TO_STDOUT




typedef enum gmp_print_style_enum
{
	gmp_print_style_null = 0x00,						//表示没有格式，所有的内容都是一行输出
	gmp_print_style_pretty = 0x01,						//表示使用换行，缩进格式
	gmp_print_style_null_flag = 0x02,					//表示没有格式，所有的内容都是一行输出,但是添加了各个标识头信息
	gmp_print_style_pretty_flag = 0x03,					//表示使用换行，缩进格式,并且添加了各个标识头信息
	gmp_print_style_pretty_sdt = 0x04					//表示使用换行，缩进格式,并且添加了各个标识头信息,数据类型为精简标识符
}gmp_print_style;



typedef struct gmp_print_string_struct	gmp_print_string;

struct gmp_print_string_struct
{
	char					*start;
	char					*pos;
	char					*last;
	char					*end;
	gmp_print_string		*next;
	int						layer;
};



#ifdef __cplusplus
extern "C"{
#endif


#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmdt_bool		gmp_gmf_printf(gmp_gmf_t *gmf, gmdt_string_p_t **gmdt_str, gm_std_char *dest, gm_std_uint len, gmp_print_style sty);
	gmp_gmdt_bool		gmp_gmf_print_current_gmdu(gmp_gmf_t *gmf, gmdt_string_p_t **gmdt_str, gm_std_char *dest, gm_std_uint len, gmp_print_style sty);
	gmp_gmdt_bool		gmp_gmf_print_this_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmdt_string_p_t **gmdt_str, gm_std_char *dest, gm_std_uint len, gmp_print_style sty);

#endif


#if defined(CSS_GMP_PRINT_TO_STDOUT)
//打印gmf的所有内容
gmp_gmdt_bool gmp_gmf_printf(gmp_gmf_t *gmf);
gmp_gmdt_bool gmp_gmf_print_gmfh(gmp_gmf_t *gmf);
gmp_gmdt_bool gmp_gmf_print_current_gmdu(gmp_gmf_t *gmf);
gmp_gmdt_bool gmp_gmf_print_gmdu(gmp_gmdu_t *gmdu, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_child_gmdu(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_gmdt(gm_std_void *dest, gm_std_int layer);

//基础类型数据的获取
gmp_gmdt_bool gmp_gmf_print_bool(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_char(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_uchar(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_short(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_ushort(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_int(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_uint(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_long(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_ulong(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_float(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_ufloat(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_double(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_udouble(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_null(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_type(gm_std_void *dest, gm_std_int layer);

//容器类型数据的获取
gmp_gmdt_bool gmp_gmf_print_array(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_object(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_xml(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_json(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_iobuffer(gm_std_void *dest, gm_std_int layer);


//扩展类型数据的获取
gmp_gmdt_bool gmp_gmf_print_string(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_rect(gm_std_void *dest, gm_std_int layer);



gmp_gmdt_bool gmp_gmf_print_tab(gm_std_int layer);

#endif


#ifdef __cplusplus
};
#endif





#endif




