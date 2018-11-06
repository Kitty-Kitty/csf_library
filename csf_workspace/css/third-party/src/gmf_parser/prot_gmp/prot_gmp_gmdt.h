
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:gmdt defined

**************************************************************************/




#ifndef	_PROT_GMP_GMDT_H_
#define _PROT_GMP_GMDT_H_





#if defined(__cplusplus)


typedef	int				gmp_gmdt;

#define GMP_GMDT_B		0x00
#define GMP_GMDT_C		0x01
#define GMP_GMDT_UC 	0x02
#define GMP_GMDT_S		0x03
#define GMP_GMDT_US 	0x04
#define GMP_GMDT_IN 	0x05
#define GMP_GMDT_UIN 	0x06
#define GMP_GMDT_L		0x07
#define GMP_GMDT_UL 	0x08
#define GMP_GMDT_F		0x09
#define GMP_GMDT_UF		0x0A
#define GMP_GMDT_D		0x0B
#define GMP_GMDT_UD 	0x0C
#define GMP_GMDT_N		0x0D
#define GMP_GMDT_T		0x0E
#define GMP_GMDT_P		0x3F					//表示指针类型，不在基础数据类型
//容器类型(64--127)
#define GMP_GMDT_A		0x40
#define GMP_GMDT_O		0x41
#define GMP_GMDT_X		0x42
#define GMP_GMDT_JS 	0x43
#define GMP_GMDT_IOB 	0x44
//扩展类型(128--255)
#define GMP_GMDT_ST 	0x80
#define GMP_GMDT_R		0x81
#define GMP_GMDT_RP		0x82



typedef			int		gmp_gmdt_bool;
#define gmp_gmdt_false	0
#define gmp_gmdt_true	1


typedef			int		gmp_gmdu_segment;
#define gmp_gmdu_key	0
#define gmp_gmdu_value	1
#define gmp_gmdu_null	2



#else

typedef	enum gmp_gmdt_enum
{
	//常用基础数据类型(0--63)
	GMP_GMDT_B	=	0x00,
	GMP_GMDT_C	=	0x01,
	GMP_GMDT_UC =	0x02,
	GMP_GMDT_S	=	0x03,
	GMP_GMDT_US =	0x04,
	GMP_GMDT_IN =	0x05,
	GMP_GMDT_UIN =	0x06,
	GMP_GMDT_L	=	0x07,
	GMP_GMDT_UL =	0x08,
	GMP_GMDT_F	=	0x09,
	GMP_GMDT_UF	=	0x0A,
	GMP_GMDT_D	=	0x0B,
	GMP_GMDT_UD =	0x0C,
	GMP_GMDT_N	=	0x0D,
	GMP_GMDT_T	=	0x0E,
	GMP_GMDT_P	=	0x3F,					//表示指针类型，不在基础数据类型
	//容器类型(64--127)
	GMP_GMDT_A	=	0x40,
	GMP_GMDT_O	=	0x41,
	GMP_GMDT_X	=	0x42,
	GMP_GMDT_JS =	0x43,
	GMP_GMDT_IOB =	0x44,
	//扩展类型(128--255)
	GMP_GMDT_ST =	0x80,
	GMP_GMDT_R	=	0x81,
	GMP_GMDT_RP	=	0x82
}gmp_gmdt;





typedef	enum gmp_gmdt_bool_enum
{
	gmp_gmdt_false = 0,
	gmp_gmdt_true = 1
}gmp_gmdt_bool;



typedef	enum gmp_gmdu_segment_enum
{
	gmp_gmdu_key = 0,
	gmp_gmdu_value = 1,
	gmp_gmdu_null = 2
}gmp_gmdu_segment;

#endif




typedef		void						gm_std_void;
typedef		char						gm_std_char;
typedef		unsigned char				gm_std_uchar;
typedef		short						gm_std_short;
typedef		unsigned short				gm_std_ushort;
typedef		int							gm_std_int;
typedef		unsigned int				gm_std_uint;
typedef		int							gm_std_int64;
typedef		unsigned int				gm_std_uint64;
typedef		long long					gm_std_long;
typedef		unsigned long long			gm_std_ulong;
typedef		float						gm_std_float;
typedef		float						gm_std_ufloat;
typedef		double						gm_std_double;
typedef		double						gm_std_udouble;







#pragma pack(1)





typedef struct gmp_gmdu_s
{
	void				*key;					//保存key内容指针
	void				*val;					//保存value内容指针
	void				*parent;				//保存父节点指针
	void				*prev;					//上一个节点
	void				*next;					//下一个节点
	void				*gmf;					//保存gmf内容指针
}gmp_gmdu_t;




typedef void			gmp_gmdt_t;




/************************************************************************/
/* 常用基础数据类型                                                     */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
//bool
typedef struct gmdt_bool_s
{
	gm_std_uchar		gmdt;
	gm_std_uchar		data;
}gmdt_bool_t;


typedef struct gmdt_bool_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uchar		*data;
}gmdt_bool_p_t;
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//char
typedef struct gmdt_char_s
{
	gm_std_uchar		gmdt;
	gm_std_char			data;
}gmdt_char_t;


typedef struct gmdt_char_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_char			*data;
}gmdt_char_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//unsigned char
typedef struct gmdt_uchar_s
{
	gm_std_uchar		gmdt;
	gm_std_uchar		data;
}gmdt_uchar_t;


typedef struct gmdt_uchar_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uchar		*data;
}gmdt_uchar_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//short
typedef struct gmdt_short_s
{
	gm_std_uchar		gmdt;
	gm_std_short		data;
}gmdt_short_t;


typedef struct gmdt_short_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_short		*data;
}gmdt_short_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//unsigned short
typedef struct gmdt_ushort_s
{
	gm_std_uchar		gmdt;
	gm_std_ushort		data;
}gmdt_ushort_t;


typedef struct gmdt_ushort_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_ushort		*data;
}gmdt_ushort_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//int
typedef struct gmdt_int_s
{
	gm_std_uchar		gmdt;
	gm_std_int			data;
}gmdt_int_t;


typedef struct gmdt_int_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_int			*data;
}gmdt_int_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//unsigned int
typedef struct gmdt_uint_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			data;
}gmdt_uint_t;


typedef struct gmdt_uint_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*data;
}gmdt_uint_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//long
typedef struct gmdt_long_s
{
	gm_std_uchar		gmdt;
	gm_std_long			data;
}gmdt_long_t;


typedef struct gmdt_long_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_long			*data;
}gmdt_long_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//unsigned long
typedef struct gmdt_ulong_s
{
	gm_std_uchar		gmdt;
	gm_std_ulong		data;
}gmdt_ulong_t;


typedef struct gmdt_ulong_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_ulong		*data;
}gmdt_ulong_p_t;
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//float
typedef struct gmdt_float_s
{
	gm_std_uchar		gmdt;
	gm_std_float		data;
}gmdt_float_t;


typedef struct gmdt_float_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_float		*data;
}gmdt_float_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//unsigned float
typedef struct gmdt_ufloat_s
{
	gm_std_uchar		gmdt;
	gm_std_ufloat		data;
}gmdt_ufloat_t;


typedef struct gmdt_ufloat_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_ufloat		*data;
}gmdt_ufloat_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//double
typedef struct gmdt_double_s
{
	gm_std_uchar		gmdt;
	gm_std_double		data;
}gmdt_double_t;


typedef struct gmdt_double_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_double		*data;
}gmdt_double_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//unsigned double
typedef struct gmdt_udouble_s
{
	gm_std_uchar		gmdt;
	gm_std_udouble		data;
}gmdt_udouble_t;


typedef struct gmdt_udouble_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_udouble		*data;
}gmdt_udouble_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//null
typedef struct gmdt_null_s
{
	gm_std_uchar		gmdt;
	gm_std_uchar		data;
}gmdt_null_t;


typedef struct gmdt_null_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_void			*data;
}gmdt_null_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//type
typedef struct gmdt_type_s
{
	gm_std_uchar		gmdt;
	gm_std_uchar		data;
}gmdt_type_t;


typedef struct gmdt_type_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uchar		*data;
}gmdt_type_p_t;
//////////////////////////////////////////////////////////////////////////

/************************************************************************/















/************************************************************************/
/* 容器类型数据                                                     */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
//array
typedef struct gmdt_array_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			nelts;
	gmp_gmdu_t			*elts;
}gmdt_array_t;


typedef struct gmdt_array_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*nelts;
	gmp_gmdu_t			*elts;
}gmdt_array_p_t;
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//Object

typedef struct gmdt_object_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			nelts;
	gmp_gmdu_t			*elts;
}gmdt_object_t;


typedef struct gmdt_object_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*nelts;
	gmp_gmdu_t			*elts;
}gmdt_object_p_t;



//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//XML
typedef struct gmdt_xml_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			len;
	gm_std_char			*data;
}gmdt_xml_t;


typedef struct gmdt_xml_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*len;
	gm_std_char			*data;
}gmdt_xml_p_t;
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//JSON
typedef struct gmdt_json_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			len;
	gm_std_char			*data;
}gmdt_json_t;


typedef struct gmdt_json_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*len;
	gm_std_char			*data;
}gmdt_json_p_t;
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//IOBUFFER
typedef struct gmdt_iobuffer_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			len;
	gm_std_uchar		*data;
}gmdt_iobuffer_t;


typedef struct gmdt_iobuffer_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*len;
	gm_std_uchar		*data;
}gmdt_iobuffer_p_t;
//////////////////////////////////////////////////////////////////////////

/************************************************************************/















/************************************************************************/
/* 扩展类型数据                                                     */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
//string
typedef struct gmdt_string_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			len;
	gm_std_char			*data;
}gmdt_string_t;


typedef struct gmdt_string_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*len;
	gm_std_char			*data;
}gmdt_string_p_t;
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//rect
typedef struct gmdt_rect_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			x1;
	gm_std_uint			y1;
	gm_std_uint			x2;
	gm_std_uint			y2;
}gmdt_rect_t;


typedef struct gmdt_rect_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*x1;
	gm_std_uint			*y1;
	gm_std_uint			*x2;
	gm_std_uint			*y2;
}gmdt_rect_p_t;
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
//rectpair
typedef struct gmdt_rectpair_s
{
	gm_std_uchar		gmdt;
	gm_std_uint			x1;
	gm_std_uint			y1;
	gm_std_uint			x2;
	gm_std_uint			y2;
	gm_std_uint			x3;
	gm_std_uint			y3;
	gm_std_uint			x4;
	gm_std_uint			y4;
}gmdt_rectpair_t;


typedef struct gmdt_rectpair_p_s
{
	gm_std_uchar		*gmdt;
	gm_std_uint			*x1;
	gm_std_uint			*y1;
	gm_std_uint			*x2;
	gm_std_uint			*y2;
	gm_std_uint			*x3;
	gm_std_uint			*y3;
	gm_std_uint			*x4;
	gm_std_uint			*y4;
}gmdt_rectpair_p_t;
//////////////////////////////////////////////////////////////////////////

/************************************************************************/




#pragma pack()











#define		gmp_chk_gmdt(dt)			(((unsigned char)dt >= GMP_GMDT_B && (unsigned char)dt <= GMP_GMDT_T) ||										\
										((unsigned char)dt >= GMP_GMDT_A && (unsigned char)dt <= GMP_GMDT_IOB) ||										\
										((unsigned char)dt >= GMP_GMDT_ST && (unsigned char)dt <= GMP_GMDT_RP))



#define		gmp_is_array_object(dt)		((unsigned char)dt == GMP_GMDT_A || (unsigned char)dt == GMP_GMDT_O)
#define		gmp_is_p_array_object(dt)	(*(unsigned char*)dt == GMP_GMDT_A || *(unsigned char*)dt == GMP_GMDT_O)



#define		gmp_get_p_type(dt)			(((gmdt_uchar_p_t*)dt)->gmdt)



//判断一个gmdu是否拥有子节点
//判断依据为：1、key 和 val不能同时为array 或者 object;2、key 和 val中有一个为array 或者 object
#define		gmp_is_have_child(du)		(!(gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(du->key))) && gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(du->val))))	\
										&& (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(du->key))) || gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(du->val)))))


//gmdt 操作函数
#define		gmp_gmdt_type(dt)					(*((unsigned char*)dt))
#define		gmp_gmdt_type_compare(gmdt, ty)		(gmdt && *((unsigned char*)gmdt) == ty)


#endif








