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
	gmp_print_style_null = 0x00,						//��ʾû�и�ʽ�����е����ݶ���һ�����
	gmp_print_style_pretty = 0x01,						//��ʾʹ�û��У�������ʽ
	gmp_print_style_null_flag = 0x02,					//��ʾû�и�ʽ�����е����ݶ���һ�����,��������˸�����ʶͷ��Ϣ
	gmp_print_style_pretty_flag = 0x03,					//��ʾʹ�û��У�������ʽ,��������˸�����ʶͷ��Ϣ
	gmp_print_style_pretty_sdt = 0x04					//��ʾʹ�û��У�������ʽ,��������˸�����ʶͷ��Ϣ,��������Ϊ�����ʶ��
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
//��ӡgmf����������
gmp_gmdt_bool gmp_gmf_printf(gmp_gmf_t *gmf);
gmp_gmdt_bool gmp_gmf_print_gmfh(gmp_gmf_t *gmf);
gmp_gmdt_bool gmp_gmf_print_current_gmdu(gmp_gmf_t *gmf);
gmp_gmdt_bool gmp_gmf_print_gmdu(gmp_gmdu_t *gmdu, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_child_gmdu(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_gmdt(gm_std_void *dest, gm_std_int layer);

//�����������ݵĻ�ȡ
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

//�����������ݵĻ�ȡ
gmp_gmdt_bool gmp_gmf_print_array(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_object(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_xml(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_json(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_iobuffer(gm_std_void *dest, gm_std_int layer);


//��չ�������ݵĻ�ȡ
gmp_gmdt_bool gmp_gmf_print_string(gm_std_void *dest, gm_std_int layer);
gmp_gmdt_bool gmp_gmf_print_rect(gm_std_void *dest, gm_std_int layer);



gmp_gmdt_bool gmp_gmf_print_tab(gm_std_int layer);

#endif


#ifdef __cplusplus
};
#endif





#endif




