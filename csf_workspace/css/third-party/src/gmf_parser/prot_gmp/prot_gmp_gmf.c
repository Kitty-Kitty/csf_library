



#include "prot_gmp_gmf.h"
#include "prot_gmp_std.h"
#include <stdarg.h>




//��ʾ����������Ϣ����󳤶�
#define		GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH					128
#define		GMP_GMF_DEFAULT_NULL_STRING							" "




#if defined(GMP_USED_POOL)

/////////////////////////////////////////////////////////////////////////////////////////
//��ȡgmfh
gmp_gmdt_bool gmp_gmf_get_gmfh(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);
//У��gmfh
gmp_gmdt_bool gmp_gmf_check_gmfh(gmp_gmf_t *gmf);
//����gmf�ַ�����
gmp_gmdt_bool gmp_gmf_parse(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);
//����Ԫ�ؼ�ֵ��
gm_std_uchar* gmp_gmf_get_gmdu(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//�����ӽڵ�Ԫ�ؼ�ֵ��
gm_std_uchar* gmp_gmf_get_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//��������Ԫ������
gm_std_uchar* gmp_gmf_get_gmdt(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//���û������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_bool(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_char(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_uchar(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_short(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_ushort(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_int(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_uint(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_long(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_ulong(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_float(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_ufloat(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_double(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_udouble(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_null(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_type(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);

//�����������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_array(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_object(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_xml(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_json(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_iobuffer(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);


//��չ�������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_string(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_rect(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_rectpair(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len);



//create gmdu
gmp_gmdu_t	*gmp_vcreate_gmdu(gmp_gmf_t *gmf, const gm_std_char *fmt, va_list *args);
gmp_gmdt_t	*gmp_vcreate_gmdt(gmp_gmf_t *gmf, const gm_std_char *fmt, va_list *args);
gmp_gmdt_bool gmp_vcreate_gmdt_value(gmp_gmf_t *gmf, const gm_std_char *fmt, va_list *args, gmp_gmdt_t **gmdt_p, gm_std_char **ret);
gmp_gmdt_bool gmp_set_gmdt_extend_segment(gmp_gmf_t *gmf, gm_std_void *val, const gm_std_char *fmt, va_list *args, gm_std_char **ret);
gmp_gmdt_bool gmp_set_gmdt_unsigned_integer(gmp_gmf_t *gmf, gm_std_char *fmt, va_list *args, gm_std_uint *data, gm_std_char **ret);
gmp_gmdt_bool gmp_get_gmdt_type(gmp_gmf_t *gmf, gm_std_char *fmt, gmp_gmdt *dt, gm_std_char **ret);
gmp_gmdt_bool gmp_get_gmdt_unsigned_type(gmp_gmf_t *gmf, gm_std_char *fmt, gmp_gmdt *dt, gm_std_char **ret);
gmp_gmdt_bool gmp_set_gmf_error(gmp_gmf_t *gmf, gm_std_int error_no, const gm_std_char *error_fmt, ...);



//gmf��������
gmp_gmdu_t *gmp_find_gmdt_by_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdt_t *gmdt);
gmp_gmdu_t *gmp_find_gmdu_object(gmp_gmf_t *gmf, gm_std_void *obj, gmp_gmdt_t *gmdt);
gmp_gmdu_t *gmp_into_object_gmdu(gmp_gmf_t *gmf, gm_std_void *obj);
gmp_gmdt_bool gmp_add_object_gmdu(gmp_gmdu_t *dest_gmdu, gmp_gmdu_t *src_gmdu);
gmp_gmdt_bool gmp_add_object_gmdt_gmdu(gm_std_void *obj, gmp_gmdu_t *src_gmdu);
gmp_gmdt_bool gmp_delete_object_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *dest_gmdu, gmp_gmdt_t *src_gmdt);
gmp_gmdt_bool gmp_delete_this_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);




gm_std_uint	gmp_gmf_count(gmp_gmf_t *gmf);
gm_std_uint gmp_gmf_count_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
gm_std_uint gmp_gmf_count_gmdt(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);



gm_std_uint gmp_gmf_encode_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gm_std_uchar *src, gm_std_int len);
gm_std_uint gmp_gmf_encode_gmdt(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt, gm_std_uchar *src, gm_std_int len);
gm_std_uint gmp_gmf_encode_array_object(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt, gm_std_uchar *src, gm_std_int len);



///////////////////////////////////////////////////////////////////////////////
//����gmf
gmp_gmf_t *gmp_create_gmf()
{
	gmp_gmf_t					*gmf_p;
	gmp_pool_t					*p;






	p = gmp_create_pool(GMP_POOL_BUFFER_SIZE);
	if (!p)
	{
		return NULL;
	}

	gmf_p = (gmp_gmf_t *)gmp_palloc(p, gmp_std_sizeof(gmp_gmf_t));
	if (!gmf_p)
	{
		return NULL;
	}

	gmp_std_memset(gmf_p, 0, gmp_std_sizeof(gmp_gmf_t));

	gmf_p->pool = p;
	gmf_p->work_mode = gmf_work_mode_general;

	return gmf_p;
}


//����gmf
void gmp_destroy_gmf(gmp_gmf_t *gmf)
{
	if (gmf)
	{
		if (gmf_error_destroyed == gmf->error_no) {
			return;
		}

		if (!gmp_std_strncmp(gmf->gmfh.gmff, GMP_GMF_GMFF, GMP_GMF_GMFF_LENGTH)) {
			gmf->error_no = gmf_error_destroyed;
			gmp_destroy_pool(gmf->pool);
		}
	}
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_create_gmdu
* ��    ��:
*			����һ��gmdu�ڵ�
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*fmt		��ʾ��֯��gmdu����
*			3���ɱ����							��ʾ��Ҫ���ݵĲ�����ֵ
* �� �� ֵ:
*			�������ɵ�gmp_gmdu_t ����ָ��
* ��    ע:
*			����һ��gmdu�ڵ�,�����������ͼ�ƣ�������Ҫ�Ľڵ�
* supported formats:
*	����	��������			����(HEX)	����(DEC)	ֵռ�ÿռ�		˵��
*=============================================================================================
*	%B		Boolen				0x00		0			1B				0x00��ʾfalse,0x01��ʾtrue
*	%C		Char				0x01		1			1B				-127~127
*	%UC		Unsigned Char		0x02		2			1B				0~255
*	%S		Short				0x03		3			2B		
*	%US		Unsigned Short		0x04		4			2B		
*	%IN		Int					0x05		5			4B		
*	%UIN	Unsigned Int		0x06		6			4B		
*	%L		Long				0x07		7			8B		
*	%UL		Unsigned Long		0x08		8			8B		
*	%F		Float				0x09		9			4B		
*	%UF		Unsigned float		0x0A		10			4B		
*	%D		Double				0x0B		11			8B		
*	%UD		Unsigned double		0x0C		12			8B		
*	%N		Null				0x0D		13			0B		
*	%T		Type				0x0E		14			1B		
*	%										
*	%A		Array				0x40		64			4B		
*	%O		Object				0x41		65			4B		
*	%X		XML					0x42		66			4B		
*	%JS		JSON				0x43		67			4B		
*	%IOB	IOBuffer			0x44		68			4B		
*	%										
*	%ST		String				0x80		128			4B		
*	%R		Rect				0x81		129			16B					[(x1,y1),(x2,y2)]
*	%RP		RectPair			0x82		130			32B					S[(x1,y1),(x2,y2)]D[(x1,y1),(x2,y2)]
*
*
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdu_t *gmp_create_gmdu(gmp_gmf_t *gmf, const gm_std_char *fmt, ...)
{
	gmp_gmdu_t						*gmdu;
	va_list							args;





	if (!gmf)
	{
		return NULL;
	}

	va_start(args, fmt);
	gmdu = gmp_vcreate_gmdu(gmf, fmt, &args);
	va_end(args);

	return gmdu;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_create_gmdt
* ��    ��:
*			����һ��gmdt����
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*fmt		��ʾ��֯��gmdu����
*			3���ɱ����							��ʾ��Ҫ���ݵĲ�����ֵ
* �� �� ֵ:
*			�������ɵ�gmp_gmdu_t ����ָ��
* ��    ע:
*			����һ��gmdu�ڵ�,�����������ͼ�ƣ�������Ҫ�Ľڵ�
* supported formats:
*	����	��������			����(HEX)	����(DEC)	ֵռ�ÿռ�		˵��
*=============================================================================================
*	%B		Boolen				0x00		0			1B				0x00��ʾfalse,0x01��ʾtrue
*	%C		Char				0x01		1			1B				-127~127
*	%UC		Unsigned Char		0x02		2			1B				0~255
*	%S		Short				0x03		3			2B		
*	%US		Unsigned Short		0x04		4			2B		
*	%IN		Int					0x05		5			4B		
*	%UIN	Unsigned Int		0x06		6			4B		
*	%L		Long				0x07		7			8B		
*	%UL		Unsigned Long		0x08		8			8B		
*	%F		Float				0x09		9			4B		
*	%UF		Unsigned float		0x0A		10			4B		
*	%D		Double				0x0B		11			8B		
*	%UD		Unsigned double		0x0C		12			8B		
*	%N		Null				0x0D		13			0B		
*	%T		Type				0x0E		14			1B		
*	%										
*	%A		Array				0x40		64			4B		
*	%O		Object				0x41		65			4B		
*	%X		XML					0x42		66			4B		
*	%JS		JSON				0x43		67			4B		
*	%IOB	IOBuffer			0x44		68			4B		
*	%										
*	%ST		String				0x80		128			4B		
*	%R		Rect				0x81		129			16B					[(x1,y1),(x2,y2)]
*	%RP		RectPair			0x82		130			32B					S[(x1,y1),(x2,y2)]D[(x1,y1),(x2,y2)]
*
*
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_t *gmp_create_gmdt(gmp_gmf_t *gmf, const gm_std_char *fmt, ...)
{
	gmp_gmdt_t						*gmdt_p;
	va_list							args;





	if (!gmf)
	{
		return NULL;
	}

	va_start(args, fmt);
	gmdt_p = gmp_vcreate_gmdt(gmf, fmt, &args);
	va_end(args);

	return gmdt_p;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_vcreate_gmdu
* ��    ��:
*			����һ��gmdu�ڵ�
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*fmt		��ʾ��֯��gmdu����
*			3��va_list				args		��ʾ�����б�
* �� �� ֵ:
*			�������ɵ�gmp_gmdu_t ����ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdu_t *gmp_vcreate_gmdu(gmp_gmf_t *gmf, const gm_std_char *fmt, va_list *args)
{
	gmp_gmdu_t						*gmdu;
	gm_std_char						*p = (gm_std_char*)fmt;
	gmp_gmdt						gmdt;
	gmp_gmdt_bool					ret_bool;
	gm_std_int						seg = gmp_gmdu_key;






	gmdu = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t));
	if (!gmdu)
	{
		return NULL;
	}

	gmp_std_memset(gmdu, 0, gmp_std_sizeof(gmp_gmdu_t));
	gmdu->gmf = gmf;

	for (;;)
	{
		ret_bool = gmp_get_gmdt_type(gmf, p, &gmdt, &p);
		if (ret_bool)
		{
			if (GMP_GMDT_T == gmdt)				//find Type
			{
				switch(seg)
				{
				case gmp_gmdu_key:
					{
						if (!gmp_vcreate_gmdt_value(gmf, p, args, (gmp_gmdt_t**)&(gmdu->key), &p))
						{
							return NULL;
						}

						++seg;
					}
					break;
				case gmp_gmdu_value:
					{
						if (!gmp_vcreate_gmdt_value(gmf, p, args, (gmp_gmdt_t**)&(gmdu->val), &p))
						{
							return NULL;
						}

						return gmdu;
					}
					break;
				default:
					{
						return NULL;
					}
					break;
				}
			}
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_vcreate_gmdt
* ��    ��:
*			����һ��gmdt���ݽڵ�
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*fmt		��ʾ��֯��gmdu����
*			3��va_list				args		��ʾ�����б�
* �� �� ֵ:
*			�������ɵ�gmp_gmdt_t ����ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_t *gmp_vcreate_gmdt(gmp_gmf_t *gmf, const gm_std_char *fmt, va_list *args)
{
	gmp_gmdt_t						*gmdt_p;
	gm_std_char						*p = (gm_std_char*)fmt;
	gmp_gmdt						gmdt;
	gmp_gmdt_bool					ret_bool;





	for (;;)
	{
		ret_bool = gmp_get_gmdt_type(gmf, p, &gmdt, &p);
		if (ret_bool)
		{
			if (GMP_GMDT_T == gmdt)				//find Type
			{
				if (!gmp_vcreate_gmdt_value(gmf, p, args, &gmdt_p, &p))
				{
					return NULL;
				}

				return gmdt_p;
			}
		}
		else
		{
			return NULL;
		}
	}

	return NULL;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_vcreate_gmdu_segment
* ��    ��:
*			����gmdu�ĸ��������ݣ���Ҫ��Ϊkey ��value
* ��    ��:
*			1��gmp_gmf_t				*gmf			��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��const gm_std_char		*fmt			��ʾ��ʽ���ַ���
*			3��va_list					args			��ʾ�����б�
*			4��gmp_gmdt_t				**gmdt_p		��ʾ���ɵ�gmdt����
5��gm_std_uchar				**ret_args		��ʾ���صı�����ַ
6��gm_std_char				**ret			��ʾ���ص���һ����ʽ��
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_vcreate_gmdt_value(gmp_gmf_t *gmf, const gm_std_char *fmt, va_list *args, gmp_gmdt_t **gmdt_p, gm_std_char **ret)
{
	gmp_gmdt_bool					ret_bool = gmp_gmdt_true;
	gmp_gmdt						gmdt;
	gmp_gmdt						fmt_gmdt;
	gm_std_void						*val;
	gm_std_void						*val_p;
	gm_std_uchar					*p;
	gm_std_char						*fmt_p = (gm_std_char*)fmt;
	gmp_gmdt_bool					is_base_type = gmp_gmdt_false;






	//��ȡ��������
	gmdt = va_arg(*args, gmp_gmdt);
	if (GMP_GMDT_B <= gmdt && gmdt <= GMP_GMDT_T)
	{
		is_base_type = gmp_gmdt_true;

		if (GMP_GMDT_N != gmdt)
		{
			//��ȡ������������ֵ�����͸�ʽ
			ret_bool = gmp_get_gmdt_type(gmf, fmt_p, &fmt_gmdt, &fmt_p);
			if (!ret_bool)
			{
				return gmp_gmdt_false;
			}
		}

		//ָ����һ�����͸�ʽ��
		*ret = fmt_p;
	}

	switch(gmdt)
	{
		//���û�����������(0--63)
	case GMP_GMDT_B:
		{
			int			b_val = 0;



			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_bool_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_bool_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

				return gmp_gmdt_false;
			}

			((gmdt_bool_p_t*)val_p)->gmdt = &(((gmdt_bool_t*)val)->gmdt);
			((gmdt_bool_p_t*)val_p)->data = &(((gmdt_bool_t*)val)->data);

			b_val = va_arg(*args, int);
			if (b_val > 0)
			{
				((gmdt_bool_t*)val)->data = gmp_gmdt_true;
			}
			else
			{
				((gmdt_bool_t*)val)->data = gmp_gmdt_false;
			}
		}
		break;
	case GMP_GMDT_C:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_char_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_char_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

				return gmp_gmdt_false;
			}

			((gmdt_char_p_t*)val_p)->gmdt = &(((gmdt_char_t*)val)->gmdt);
			((gmdt_char_p_t*)val_p)->data = &(((gmdt_char_t*)val)->data);

#if defined(WIN32)
			((gmdt_char_t*)val)->data = va_arg(*args, gm_std_char);
#else
			((gmdt_char_t*)val)->data = va_arg(*args, gm_std_int);
#endif
		}
		break;
	case GMP_GMDT_UC:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uchar_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uchar_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

				return gmp_gmdt_false;
			}

			((gmdt_uchar_p_t*)val_p)->gmdt = &(((gmdt_uchar_t*)val)->gmdt);
			((gmdt_uchar_p_t*)val_p)->data = &(((gmdt_uchar_t*)val)->data);

#if defined(WIN32)
			((gmdt_uchar_t*)val)->data = va_arg(*args, gm_std_uchar);
#else
			((gmdt_uchar_t*)val)->data = va_arg(*args, gm_std_int);
#endif
		}
		break;
	case GMP_GMDT_S:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_short_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_short_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]",
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

				return gmp_gmdt_false;
			}

			((gmdt_short_p_t*)val_p)->gmdt = &(((gmdt_short_t*)val)->gmdt);
			((gmdt_short_p_t*)val_p)->data = &(((gmdt_short_t*)val)->data);

#if defined(WIN32)
			((gmdt_short_t*)val)->data = va_arg(*args, gm_std_short);
#else
			((gmdt_short_t*)val)->data = va_arg(*args, gm_std_int);
#endif
		}
		break;
	case GMP_GMDT_US:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ushort_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ushort_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

				return gmp_gmdt_false;
			}

			((gmdt_ushort_p_t*)val_p)->gmdt = &(((gmdt_ushort_t*)val)->gmdt);
			((gmdt_ushort_p_t*)val_p)->data = &(((gmdt_ushort_t*)val)->data);

#if defined(WIN32)
			((gmdt_ushort_t*)val)->data = va_arg(*args, gm_std_ushort);
#else
			((gmdt_ushort_t*)val)->data = va_arg(*args, gm_std_int);
#endif
		}
		break;
	case GMP_GMDT_IN:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_int_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_int_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_int_p_t*)val_p)->gmdt = &(((gmdt_int_t*)val)->gmdt);
			((gmdt_int_p_t*)val_p)->data = &(((gmdt_int_t*)val)->data);

			((gmdt_int_t*)val)->data = va_arg(*args, gm_std_int);
		}
		break;
	case GMP_GMDT_UIN:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uint_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uint_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_uint_p_t*)val_p)->gmdt = &(((gmdt_uint_t*)val)->gmdt);
			((gmdt_uint_p_t*)val_p)->data = &(((gmdt_uint_t*)val)->data);

			((gmdt_uint_t*)val)->data = va_arg(*args, gm_std_uint);
		}
		break;
	case GMP_GMDT_L:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_long_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_long_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_long_p_t*)val_p)->gmdt = &(((gmdt_long_t*)val)->gmdt);
			((gmdt_long_p_t*)val_p)->data = &(((gmdt_long_t*)val)->data);

			((gmdt_long_t*)val)->data = va_arg(*args, gm_std_long);
		}
		break;
	case GMP_GMDT_UL:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ulong_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ulong_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_ulong_p_t*)val_p)->gmdt = &(((gmdt_ulong_t*)val)->gmdt);
			((gmdt_ulong_p_t*)val_p)->data = &(((gmdt_ulong_t*)val)->data);

			((gmdt_ulong_t*)val)->data = va_arg(*args, gm_std_ulong);
		}
		break;
	case GMP_GMDT_F:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_float_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_float_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_float_p_t*)val_p)->gmdt = &(((gmdt_float_t*)val)->gmdt);
			((gmdt_float_p_t*)val_p)->data = &(((gmdt_float_t*)val)->data);

#if defined(WIN32)
			((gmdt_float_t*)val)->data = va_arg(*args, gm_std_float);
#else
			((gmdt_float_t*)val)->data = va_arg(*args, gm_std_double);
#endif
		}
		break;
	case GMP_GMDT_UF:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ufloat_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ufloat_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_ufloat_p_t*)val_p)->gmdt = &(((gmdt_ufloat_t*)val)->gmdt);
			((gmdt_ufloat_p_t*)val_p)->data = &(((gmdt_ufloat_t*)val)->data);

#if defined(WIN32)
			((gmdt_ufloat_t*)val)->data = va_arg(*args, gm_std_ufloat);
#else
			((gmdt_ufloat_t*)val)->data = va_arg(*args, gm_std_double);
#endif
		}
		break;
	case GMP_GMDT_D:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_double_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_double_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_double_p_t*)val_p)->gmdt = &(((gmdt_double_t*)val)->gmdt);
			((gmdt_double_p_t*)val_p)->data = &(((gmdt_double_t*)val)->data);

			((gmdt_double_t*)val)->data = va_arg(*args, gm_std_double);
		}
		break;
	case GMP_GMDT_UD:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_udouble_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_udouble_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_udouble_p_t*)val_p)->gmdt = &(((gmdt_udouble_t*)val)->gmdt);
			((gmdt_udouble_p_t*)val_p)->data = &(((gmdt_udouble_t*)val)->data);

			((gmdt_udouble_t*)val)->data = va_arg(*args, gm_std_udouble);
		}
		break;
	case GMP_GMDT_N:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_null_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_null_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_null_p_t*)val_p)->gmdt = &(((gmdt_null_t*)val)->gmdt);
			((gmdt_null_p_t*)val_p)->data = &(((gmdt_null_t*)val)->data);

#if defined(WIN32)
			((gmdt_null_t*)val)->data = va_arg(*args, gm_std_uchar);
#else
			((gmdt_null_t*)val)->data = va_arg(*args, gm_std_int);
#endif
		}
		break;
	case GMP_GMDT_T:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_type_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_type_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_type_p_t*)val_p)->gmdt = &(((gmdt_type_t*)val)->gmdt);
			((gmdt_type_p_t*)val_p)->data = &(((gmdt_type_t*)val)->data);

#if defined(WIN32)
			((gmdt_type_t*)val)->data = va_arg(*args, gm_std_uchar);
#else
			((gmdt_type_t*)val)->data = va_arg(*args, gm_std_int);
#endif
		}
		break;
		//��������(64--127):
	case GMP_GMDT_A:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_array_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_array_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_array_t*)val)->elts = NULL;
			((gmdt_array_t*)val)->nelts = 0;

			((gmdt_array_p_t*)val_p)->gmdt = &(((gmdt_array_t*)val)->gmdt);
			((gmdt_array_p_t*)val_p)->nelts = &(((gmdt_array_t*)val)->nelts);
			((gmdt_array_p_t*)val_p)->elts = (((gmdt_array_t*)val)->elts);

		}
		break;
	case GMP_GMDT_O:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_object_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_object_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_object_t*)val)->elts = NULL;
			((gmdt_object_t*)val)->nelts = 0;

			((gmdt_object_p_t*)val_p)->gmdt = &(((gmdt_object_t*)val)->gmdt);
			((gmdt_object_p_t*)val_p)->nelts = &(((gmdt_object_t*)val)->nelts);
			((gmdt_object_p_t*)val_p)->elts = (((gmdt_object_t*)val)->elts);
		}
		break;
	case GMP_GMDT_X:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_xml_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_xml_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_xml_p_t*)val_p)->gmdt = &(((gmdt_xml_t*)val)->gmdt);
			((gmdt_xml_p_t*)val_p)->len = &(((gmdt_xml_t*)val)->len);
			((gmdt_xml_p_t*)val_p)->data = (((gmdt_xml_t*)val)->data);
		}
		break;
	case GMP_GMDT_JS:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_json_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_json_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_json_p_t*)val_p)->gmdt = &(((gmdt_json_t*)val)->gmdt);
			((gmdt_json_p_t*)val_p)->len = &(((gmdt_json_t*)val)->len);
			((gmdt_json_p_t*)val_p)->data = (((gmdt_json_t*)val)->data);
		}
		break;
	case GMP_GMDT_IOB:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_iobuffer_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_iobuffer_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_iobuffer_p_t*)val_p)->gmdt = &(((gmdt_iobuffer_t*)val)->gmdt);
			((gmdt_iobuffer_p_t*)val_p)->len = &(((gmdt_iobuffer_t*)val)->len);
			((gmdt_iobuffer_p_t*)val_p)->data = (((gmdt_iobuffer_t*)val)->data);
		}
		break;
		//��չ����(128--255):
	case GMP_GMDT_ST:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_string_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_string_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_string_p_t*)val_p)->gmdt = &(((gmdt_string_t*)val)->gmdt);
			((gmdt_string_p_t*)val_p)->len = &(((gmdt_string_t*)val)->len);
			((gmdt_string_p_t*)val_p)->data = (gm_std_char *)(((gmdt_string_t*)val)->data);
		}
		break;
	case GMP_GMDT_R:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_rect_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_rect_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_rect_p_t*)val_p)->gmdt = &(((gmdt_rect_t*)val)->gmdt);
			((gmdt_rect_p_t*)val_p)->x1 = &(((gmdt_rect_t*)val)->x1);
			((gmdt_rect_p_t*)val_p)->y1 = &(((gmdt_rect_t*)val)->y1);
			((gmdt_rect_p_t*)val_p)->x2 = &(((gmdt_rect_t*)val)->x2);
			((gmdt_rect_p_t*)val_p)->y2 = &(((gmdt_rect_t*)val)->y2);

		}
		break;
	case GMP_GMDT_RP:
		{
			val = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_rectpair_t));
			val_p = gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_rectpair_p_t));

			if (!val || !val_p)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
					gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
				return gmp_gmdt_false;
			}

			((gmdt_rectpair_p_t*)val_p)->gmdt = &(((gmdt_rectpair_t*)val)->gmdt);
			((gmdt_rectpair_p_t*)val_p)->x1 = &(((gmdt_rectpair_t*)val)->x1);
			((gmdt_rectpair_p_t*)val_p)->y1 = &(((gmdt_rectpair_t*)val)->y1);
			((gmdt_rectpair_p_t*)val_p)->x2 = &(((gmdt_rectpair_t*)val)->x2);
			((gmdt_rectpair_p_t*)val_p)->y2 = &(((gmdt_rectpair_t*)val)->y2);
			((gmdt_rectpair_p_t*)val_p)->x3 = &(((gmdt_rectpair_t*)val)->x3);
			((gmdt_rectpair_p_t*)val_p)->y3 = &(((gmdt_rectpair_t*)val)->y3);
			((gmdt_rectpair_p_t*)val_p)->x4 = &(((gmdt_rectpair_t*)val)->x4);
			((gmdt_rectpair_p_t*)val_p)->y4 = &(((gmdt_rectpair_t*)val)->y4);
		}
		break;
	default:
		{
			gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type[%d].", gmdt);
			return gmp_gmdt_false;
		}
	}

	if (!val)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s]", 
			gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_gmdt_false;
	}

	//����gmdt����������
	p = (gm_std_uchar*)val;
	*p = gmdt;

	//����Ϊ�˺ͽ��������ݣ�������Ҳͳһʹ��ָ��
	*gmdt_p = (gmp_gmdt_t*)val_p;

	if (is_base_type)
	{
		//�����������ͣ�������ɷ���

		return gmp_gmdt_true;
	}

	//������չ���ͺ������������ݵĴ���
	return gmp_set_gmdt_extend_segment(gmf, val_p, fmt_p, args, ret);
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_set_gmdt_extend_segment
* ��    ��:
*			����gmdu�ĸ��������ݣ���Ҫ��Ϊkey ��value
* ��    ��:
*			1��gm_std_void				*val		��ʾ��Ҫ���õ����ݵ�ַָ��
*			2��const gm_std_char		*fmt		��ʾ��ʽ���ַ���
*			3��va_list					args		��ʾ�����б�
*			4��gm_std_char				**ret		��ʾ���ص���һ����ʽ��
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_set_gmdt_extend_segment(gmp_gmf_t *gmf, gm_std_void *val, const gm_std_char *fmt, va_list *args, gm_std_char **ret)
{
	gmp_gmdt_bool					ret_bool = gmp_gmdt_true;
	gm_std_uchar					*p = ((gmdt_uchar_p_t*)val)->gmdt;
	gm_std_char						*fmt_p = (gm_std_char*)fmt;
	gm_std_void						*val_p;
	gm_std_int						i = 0;
	gmp_gmdt						fmt_gmdt;






	switch(*p)
	{
		//��������(64--127):
	case GMP_GMDT_A:
		{
			gmdt_array_p_t	*v = (gmdt_array_p_t*)val;



			*(v->nelts) = 0;
			v->elts = NULL;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t	*v = (gmdt_object_p_t*)val;



			*(v->nelts) = 0;
			v->elts = NULL;
		}
		break;
	case GMP_GMDT_X:							//%T%P%d / %T%p%IN / %T%P%IN / %T%p%d /%T%P%UIN
	case GMP_GMDT_JS:
	case GMP_GMDT_ST:
		{
			gmdt_xml_p_t	*v = (gmdt_xml_p_t*)val;


			//��һ������Ϊ�����ַ�����ָ��
			//��ȡ������������ֵ�����͸�ʽ--��Ҫ���� p/P
			ret_bool = gmp_get_gmdt_type(gmf, fmt_p, &fmt_gmdt, &fmt_p);
			if (!ret_bool)
			{
				*ret = fmt_p;
				return gmp_gmdt_false;
			}

			//xml����Ϊָ����������
			if (GMP_GMDT_P != fmt_gmdt)
			{
				return gmp_gmdt_false;
			}

			val_p = va_arg(*args, gm_std_void*);


			//�ڶ�������Ϊ�����ַ����ĳ���
			//��ȡ������������ֵ�����͸�ʽ--��Ҫ���� d/IN
			ret_bool = gmp_get_gmdt_type(gmf, fmt_p, &fmt_gmdt, &fmt_p);
			if (!ret_bool)
			{
				*ret = fmt_p;
				return gmp_gmdt_false;
			}

			//xml����Ϊָ����������
			if (GMP_GMDT_IN != fmt_gmdt && GMP_GMDT_UIN != fmt_gmdt)
			{
				gmp_set_gmf_error(gmf, gmf_error_format, "not length. not [IN] or [UIN]. type \"%d\"", fmt_gmdt);
				return gmp_gmdt_false;
			}

			*(v->len) = va_arg(*args, gm_std_uint);

			//�жϳ����Ƿ�׼ȷ���������0������Ҫ�����ڴ棬�洢�ַ�������
			if (*(v->len) <= 0)
			{
				return gmp_gmdt_true;
			}

			if (1 == *(v->len) && 0x20 == *((gm_std_char*)val_p))
			{
				//���ȴ���0�� ����Ҫ�����ڴ棬���xml�ַ�������
				*(v->len) = gmp_std_strlen(GMP_GMF_DEFAULT_NULL_STRING);

				if (!(*(v->len)))
				{
					v->data = NULL;
				}
				else
				{
					v->data = (gm_std_char *)gmp_palloc((gmf->pool), *(v->len));
					if (!v->data)
					{
						gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s] len[%d]", 
							gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno), *(v->len));

						return gmp_gmdt_false;
					}

					*ret = fmt_p;
					//�����ݿ������洢��
					gmp_std_strncpy((gm_std_char*)v->data, GMP_GMF_DEFAULT_NULL_STRING, *(v->len));
				}
			}
			else
			{
				//���ȴ���0�� ����Ҫ�����ڴ棬���xml�ַ�������
				v->data = (gm_std_char *)gmp_palloc((gmf->pool), *(v->len));
				if (!v->data)
				{
					gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. [%d:%s] len[%d]", 
						gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno), *(v->len));

					return gmp_gmdt_false;
				}

				*ret = fmt_p;
				//�����ݿ������洢��
				gmp_std_strncpy((gm_std_char*)v->data, (gm_std_char*)val_p, *(v->len));
			}
		}
		break;
	case GMP_GMDT_IOB:
		{
			gmdt_iobuffer_p_t	*v = (gmdt_iobuffer_p_t*)val;


			//��һ������Ϊ���ݵ�ָ��
			//��ȡ������������ֵ�����͸�ʽ--��Ҫ���� p/P
			ret_bool = gmp_get_gmdt_type(gmf, fmt_p, &fmt_gmdt, &fmt_p);
			if (!ret_bool)
			{
				*ret = fmt_p;
				return gmp_gmdt_false;
			}

			//xml����Ϊָ����������
			if (GMP_GMDT_P != fmt_gmdt)
			{
				gmp_set_gmf_error(gmf, gmf_error_format, "iobuffer format error. type[%d] not point", fmt_gmdt);
				return gmp_gmdt_false;
			}

			val_p = va_arg(*args, gm_std_void*);


			//�ڶ�������Ϊ���ݵĳ���
			//��ȡ������������ֵ�����͸�ʽ--��Ҫ���� d/IN
			ret_bool = gmp_get_gmdt_type(gmf, fmt_p, &fmt_gmdt, &fmt_p);
			if (!ret_bool)
			{
				*ret = fmt_p;
				return gmp_gmdt_false;
			}

			//xml����Ϊ�������ݣ���ʾ����
			if (GMP_GMDT_IN != fmt_gmdt && GMP_GMDT_UIN != fmt_gmdt)
			{
				gmp_set_gmf_error(gmf, gmf_error_format, "not length. not [IN] or [UIN]. type \"%d\"", fmt_gmdt);
				return gmp_gmdt_false;
			}

			*(v->len) = va_arg(*args, gm_std_uint);

			//�жϳ����Ƿ�׼ȷ���������0������Ҫ�����ڴ棬�洢�ַ�������
			if (*(v->len) <= 0)
			{
				return gmp_gmdt_true;
			}

			//���ȴ���0�� ����Ҫ�����ڴ棬���xml�ַ�������
			v->data = (gm_std_uchar*)gmp_palloc((gmf->pool), *(v->len));
			if (!v->data)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d]", *(v->len));
				return gmp_gmdt_false;
			}

			*ret = fmt_p;
			//�����ݿ������洢��
			gmp_std_memcpy((gm_std_uchar*)v->data, (gm_std_uchar*)val_p, *(v->len));
		}
		break;
	case GMP_GMDT_R:
		{
			gm_std_uint	*v = (gm_std_uint	*)++p;




			for (i = 0; i < 4; i++, v++)
			{
				if (!gmp_set_gmdt_unsigned_integer(gmf, fmt_p, args, v, &fmt_p))
				{
					*ret = fmt_p;

					return gmp_gmdt_false;
				}
			}

			*ret = fmt_p;
		}
		break;
	case GMP_GMDT_RP:
		{
			gm_std_uint	*v = (gm_std_uint	*)++p;




			for (i = 0; i < 8; i++, v++)
			{
				if (!gmp_set_gmdt_unsigned_integer(gmf, fmt_p, args, v, &fmt_p))
				{
					*ret = fmt_p;

					return gmp_gmdt_false;
				}
			}

			*ret = fmt_p;
		}
		break;
	default:
		{
			gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type[%d]", *p);
			return gmp_gmdt_false;
		}
	}

	*ret = fmt_p;
	return gmp_gmdt_true;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_set_gmdt_unsigned_integer
* ��    ��:
*			����У����������
* ��    ��:
*			1��const gm_std_char		*fmt		��ʾ��ʽ���ַ���
*			2��gm_std_uint				*data		��ʾ����������������
*			3��gm_std_char				**ret		��ʾ���ص���һ����ʽ��
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_set_gmdt_unsigned_integer(gmp_gmf_t *gmf, gm_std_char *fmt, va_list *args, gm_std_uint *data, gm_std_char **ret)
{
	gmp_gmdt_bool					ret_bool = gmp_gmdt_false;
	gm_std_char						*fmt_p = fmt;
	gmp_gmdt						fmt_gmdt;





	ret_bool = gmp_get_gmdt_type(gmf, fmt_p, &fmt_gmdt, &fmt_p);
	if (!ret_bool)
	{
		*ret = fmt_p;
		return gmp_gmdt_false;
	}

	//xml����Ϊָ����������
	if (GMP_GMDT_UIN != fmt_gmdt && GMP_GMDT_IN != fmt_gmdt)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "not length. not [IN] or [UIN]. type \"%d\"", fmt_gmdt);
		return gmp_gmdt_false;
	}

	*data = va_arg(*args, gm_std_uint);
	*ret = fmt_p;

	return ret_bool;
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_get_gmdt_type
* ��    ��:
*			��ȡ��һ��%ָ��������
* ��    ��:
*			1��const gm_std_char		*fmt		��ʾ��ʽ���ַ���
*			2��gmp_gmdt					*dt			��ʾת�����ʽ��ֵ�������ز�ѯ���
*			4��gm_std_char				**ret		��ʾ���ص���һ����ʽ��
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_get_gmdt_type(gmp_gmf_t *gmf, gm_std_char *fmt, gmp_gmdt *dt, gm_std_char **ret)
{
	gmp_gmdt_bool					ret_bool = gmp_gmdt_false;
	gm_std_char						*p;





	while(*fmt)
	{
		if (*fmt == '%')
		{
			for (;;)
			{
				switch(*++fmt)
				{
				case 'B':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_B;
						return gmp_gmdt_true;
					}
					break;
				case 'C':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_C;
						return gmp_gmdt_true;
					}
					break;
				case 'U':
					{
						return gmp_get_gmdt_unsigned_type(gmf, ++fmt, dt, ret);
					}
					break;
				case 'S':
					{
						p = fmt;
						if (*++p == 'T')			//ST
						{
							*ret = ++p;
							*dt = GMP_GMDT_ST;
						}
						else
						{
							*ret = ++fmt;
							*dt = GMP_GMDT_B;
						}
						return gmp_gmdt_true;
					}
					break;
				case 'd':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_IN;
						return gmp_gmdt_true;
					}
					break;
				case 'I':
					{
						p = fmt;
						if (*++p == 'N')			//IN
						{
							*ret = ++p;
							*dt = GMP_GMDT_IN;
							return gmp_gmdt_true;
						}
						else if (*++p == 'O')		//IOB
						{
							if (*++p == 'B')
							{
								*ret = ++p;
								*dt = GMP_GMDT_IOB;
								return gmp_gmdt_true;
							}
							else
							{
								gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"IO%c\"", *p);
								*ret = ++p;
								return gmp_gmdt_false;
							}
						}
						else						//not IN or IOB
						{
							gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"I%c\"", *fmt);
							*ret = ++fmt;
							return gmp_gmdt_false;
						}
					}
					break;
				case 'F':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_F;
						return gmp_gmdt_true;
					}
					break;
				case 'D':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_D;
						return gmp_gmdt_true;
					}
					break;
				case 'N':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_N;
						return gmp_gmdt_true;
					}
					break;
				case 'T':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_T;
						return gmp_gmdt_true;
					}
					break;
				case 'P':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_P;
						return gmp_gmdt_true;
					}
					break;
				case 'p':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_P;
						return gmp_gmdt_true;
					}
					break;
				case 'A':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_A;
						return gmp_gmdt_true;
					}
					break;
				case 'O':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_O;
						return gmp_gmdt_true;
					}
					break;
				case 'X':
					{
						*ret = ++fmt;
						*dt = GMP_GMDT_X;
						return gmp_gmdt_true;
					}
					break;
				case 'J':
					{
						p = fmt;
						if (*++p == 'S')				//JS
						{
							*ret = ++p;
							*dt = GMP_GMDT_JS;
							return gmp_gmdt_true;
						}
						else
						{
							gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"J%c\"", *fmt);
							*ret = ++fmt;
							return gmp_gmdt_false;
						}
					}
					break;
				case 'R':
					{
						p = fmt;
						if (*++p == 'P')				//RP
						{
							*ret = ++p;
							*dt = GMP_GMDT_RP;
							return gmp_gmdt_true;
						}
						else							//R
						{
							gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"R%c\"", *fmt);
							*ret = ++fmt;
							*dt = GMP_GMDT_R;
							return gmp_gmdt_true;
						}
					}
					break;
				default:
					{
						gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"%c\"", *fmt);
						*ret = ++fmt;
						return gmp_gmdt_false;
					}
					break;
				}
			}
		}

		++fmt;
	}

	return ret_bool;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_get_gmdt_unsigned_type
* ��    ��:
*			��ȡ��һ��%Uָ�����޷���������������
* ��    ��:
*			1��const gm_std_char		*fmt		��ʾ��ʽ���ַ���
*			2��gmp_gmdt					*dt			��ʾת�����ʽ��ֵ�������ز�ѯ���
*			4��gm_std_char				**ret		��ʾ���ص���һ����ʽ��
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_get_gmdt_unsigned_type(gmp_gmf_t *gmf, gm_std_char *fmt, gmp_gmdt *dt, gm_std_char **ret)
{
	gmp_gmdt_bool					ret_bool = gmp_gmdt_false;
	gm_std_char						*p;





	for(;;)
	{
		switch(*fmt)
		{
		case 'C':							//UC
			{
				*ret = ++fmt;
				*dt = GMP_GMDT_UC;
				return gmp_gmdt_true;
			}
			break;
		case 'S':							//US
			{
				*ret = ++fmt;
				*dt = GMP_GMDT_US;
				return gmp_gmdt_true;
			}
			break;
		case 'I':
			{
				p = ++fmt;
				if (*p == 'N')				//UIN
				{
					*ret = ++p;
					*dt = GMP_GMDT_UIN;
					return gmp_gmdt_true;
				}
				else
				{
					gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"I%c\"", *p);

					*ret = ++p;
					return gmp_gmdt_false;
				}
			}
			break;
		case 'L':							//UL
			{
				*ret = ++fmt;
				*dt = GMP_GMDT_UL;
				return gmp_gmdt_true;
			}
			break;
		case 'F':
			{
				*ret = ++fmt;
				*dt = GMP_GMDT_UF;
				return gmp_gmdt_true;
			}
			break;
		case 'D':
			{
				*ret = ++fmt;
				*dt = GMP_GMDT_UD;
				return gmp_gmdt_true;
			}
			break;
		default:
			{
				gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type \"I%c\"", *fmt);

				*ret = ++fmt;
				return gmp_gmdt_false;
			}
			break;
		}
	}

	return ret_bool;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_set_gmf_error
* ��    ��:
*			���ý�����������Ϣ
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾgmf�ṹ������ָ��
*			2��const gm_std_char		*error_text			��ʾ����������������
*			4��gm_std_int				error_no			��ʾ����������
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-18 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_set_gmf_error(gmp_gmf_t *gmf, gm_std_int error_no, const gm_std_char *error_fmt, ...)
{
	va_list			args;




	if (!gmf->error_text)
	{
		//���û�д������棬�򴴽�һ������
		gmf->error_text = (gm_std_char *)gmp_palloc((gmf->pool), GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH);
		if (!gmf->error_text)
		{
			gmf->error_no = gmf_error_alloc_memory;
			return gmp_gmdt_false;
		}
	}

	//��������գ��������ݸ�ʽ������
	gmp_std_memset(gmf->error_text, 0, GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH);

	gmf->error_no = error_no;

	va_start(args, error_fmt);
	gmp_vslprintf((gm_std_uchar*)(gmf->error_text), 
		(gm_std_uchar*)(gmf->error_text + GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH), error_fmt, args);
	va_end(args);

	return gmp_gmdt_true;
}

//��gmf�в���һ���ֵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_find_gmdu
* ��    ��:
*			�ӵ�ǰλ�ò���keyΪgmdt�Ľڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdt_t				*gmdt				��ʾ��Ϊ����key��gmdt
* �� �� ֵ:
*			���ر����ҵ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_find_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt)
{
	gmp_gmdu_t						*gmdu;





	if (!gmf || !gmdt)
	{
		return NULL;
	}

	if (!gmf->current_gmdu)
	{
		return NULL;
	}

	gmdu = (gmp_gmdu_t*)(((gmp_gmdu_t*)(gmf->current_gmdu))->parent);
	if (!gmdu)
	{
		return NULL;
	}

	return gmp_find_gmdt_by_gmdu(gmf, gmdu, gmdt);
}


//��gmf�в���һ���ֵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_find_gmdu
* ��    ��:
*			��gmdu�в���keyΪgmdt�Ľڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*gmdu				��ʾ��Ҫ���в��ҵ�gmdu
*			3��gmp_gmdt_t				*gmdt				��ʾ��Ϊ����key��gmdt
* �� �� ֵ:
*			���ر����ҵ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_find_gmdt_by_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdt_t *gmdt)
{
	if (!gmp_is_have_child(gmdu))
	{
		return NULL;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu->key))))
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_find_gmdu_object(gmf, gmdu->key, gmdt);
		}
		else
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_find_gmdu_object(gmf, gmdu->val, gmdt);
		}
	}

	return NULL;
}


//��gmf�в���һ���ֵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_find_gmdu_object
* ��    ��:
*			�ӵ�ǰgmdu�в���gmdt�ڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gm_std_void				*obj				��ʾ��Ҫ�����ҵĶ���ڵ�
*			3��gmp_gmdt_t				*gmdt				��ʾ��Ϊ����key��gmdt
* �� �� ֵ:
*			���ر����ҵ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_find_gmdu_object(gmp_gmf_t *gmf, gm_std_void *obj, gmp_gmdt_t *gmdt)
{
	gmp_gmdu_t						*gmdu;
	gm_std_uint						i = 0;
	gm_std_uint						num = 0;





	switch((unsigned char)(*(gmp_get_p_type(obj))))
	{
	case GMP_GMDT_A:
		{
			gmdt_array_p_t *ary = (gmdt_array_p_t *)(obj);
			gmdu = ary->elts;

			if (!gmdu)
			{
				return NULL;
			}

			for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			{
				if (gmp_gmdt_keycmp(gmdu->key, gmdt))
				{
					return gmdu;
				}
			}

			return NULL;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t *ob = (gmdt_object_p_t *)(obj);
			gmdu = ob->elts;

			if (!gmdu)
			{
				return NULL;
			}

			for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			{
				if (gmp_gmdt_keycmp(gmdu->key, gmdt))
				{
					return gmdu;
				}
			}

			return NULL;
		}
		break;
	default:
		break;
	}

	return NULL;
}




//��gmf�в���һ���ӽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_find_child_gmdu
* ��    ��:
*			�ڵ�ǰλ�õ��ӽڵ��в���keyΪgmdt�Ľڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdt_t				*gmdt				��ʾ��Ϊ����key��gmdt
* �� �� ֵ:
*			���ر����ҵ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_find_child_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt)
{
	if (!gmf || !gmdt)
	{
		return NULL;
	}

	if (!gmf->current_gmdu)
	{
		return NULL;
	}

	if (!gmp_is_have_child(gmf->current_gmdu))
	{
		return NULL;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmf->current_gmdu->key))))
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_find_gmdu_object(gmf, gmf->current_gmdu->key, gmdt);
		}
		else
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_find_gmdu_object(gmf, gmf->current_gmdu->val, gmdt);
		}
	}

	return NULL;
}


//��gmf��ȡ������Ϣ
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_get_error
* ��    ��:
*			��gmf��ȡ������Ϣ����ȡ֮�󣬴�����Ϣ�������
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gm_std_int				*error_no			��ʾ������
*			3��gm_std_char				*error_text			��ʾ����ԭ���Ż���
*			4��gm_std_int				len					��ʾ��Ŵ���ԭ�򻺴��С
* �� �� ֵ:
*			���ص�ǰ�����룬����޴����򷵻�0����Ϊ0�����Ǵ�����Ϣ
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gm_std_int gmp_get_error(gmp_gmf_t *gmf, gm_std_int *error_no, gm_std_char *error_text, gm_std_int len)
{
	if (!gmf || !error_no || !error_text)
	{
		return -1;
	}

	if (!gmf->error_no)
	{
		return 0;
	}

	*error_no = gmf->error_no;

	if (len >= GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH)
	{
		gmp_std_strncpy(error_text, gmf->error_text, GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH);
	}
	else
	{
		gmp_std_strncpy(error_text, gmf->error_text, len);
	}

	gmf->error_no = 0;
	gmp_std_memset(gmf->error_text, 0, GMP_GMF_DEFAULT_ERROR_TEXT_LENGTH);

	return *error_no;
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_get_version
* ��    ��:
*			��gmf�������İ汾��Ϣ
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gm_std_int				*version			��ʾ�汾����
*			3��gm_std_char				*version_text		��ʾ�汾�ַ�����Ϣ
*			4��gm_std_int				len					��ʾ��Ű汾�ַ����Ļ���
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ���false��ʾʧ�ܣ�
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_get_version(gmp_gmf_t *gmf, gm_std_int *version, gm_std_char *version_text, gm_std_int len)
{
	if (!gmf || !version || !version_text)
	{
		return gmp_gmdt_false;
	}

	*version = gmf_version;

	if (len < (gm_std_int)gmp_std_strlen(GMF_VER))
	{
		return gmp_gmdt_false;
	}

	gmp_std_strcpy(version_text, GMF_VER);

	return gmp_gmdt_true;
}

//////////////////////////////////////////////////////////////////////////
//��ȡgmp_gmdu_t������
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_get_gmdt
* ��    ��:
*			��ʾ�ӵ�ǰgmp_gmdu_t�У���ȡ��Ҫ��gmdt
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*gmdu				��ʾ��Ҫ����ȡ��gmdu����
*			3��gmp_gmdu_segment			seg					��ʾgmdu����ȡ�Ĳ��ֱ�ʶ
* �� �� ֵ:
*			���ر����ҵ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_t *gmp_get_gmdt(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdu_segment seg)
{
	if (!gmf || !gmdu)
	{
		return NULL;
	}

	switch(seg)
	{
	case gmp_gmdu_key:
		{
			return gmdu->key;
		}
		break;
	case gmp_gmdu_value:
		{
			return gmdu->val;
		}
		break;
	default:
		{
			return NULL;
		}
		break;
	}

	return NULL;
}


//�ж�gmp_gmdt_t�������Ƿ���ͬ
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmdt_cmp
* ��    ��:
*			�ж�gmdt�����Ƿ�һ��
* ��    ��:
*			1��gmp_gmdt_t				*src_gmdt			��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdt_t				*dest_gmdt			��ʾ��Ҫ����ȡ��gmdu����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmdt_keycmp(gmp_gmdt_t *src_gmdt, gmp_gmdt_t *dest_gmdt)
{
	if (!src_gmdt || !dest_gmdt)
	{
		return gmp_gmdt_false;
	}

	if (*(((gmdt_uchar_p_t*)src_gmdt)->gmdt) != *(((gmdt_uchar_p_t*)dest_gmdt)->gmdt))
	{
		return gmp_gmdt_false;
	}

	switch(*(((gmdt_uchar_p_t*)src_gmdt)->gmdt))
	{
	case GMP_GMDT_B:
	case GMP_GMDT_C:
	case GMP_GMDT_UC:
		{
			if (*(((gmdt_uchar_p_t*)src_gmdt)->data) != *(((gmdt_uchar_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_S:
		{
			if (*(((gmdt_short_p_t*)src_gmdt)->data) != *(((gmdt_short_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_US:
		{
			if (*(((gmdt_ushort_p_t*)src_gmdt)->data) != *(((gmdt_ushort_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_IN:
		{
			if (*(((gmdt_int_p_t*)src_gmdt)->data) != *(((gmdt_int_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_UIN:
		{
			if (*(((gmdt_uint_p_t*)src_gmdt)->data) != *(((gmdt_uint_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_L:
		{
			if (*(((gmdt_long_p_t*)src_gmdt)->data) != *(((gmdt_long_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_UL:
		{
			if (*(((gmdt_ulong_p_t*)src_gmdt)->data) != *(((gmdt_ulong_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_F:
		{
			if (*(((gmdt_float_p_t*)src_gmdt)->data) != *(((gmdt_float_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_UF:
		{
			if (*(((gmdt_ufloat_p_t*)src_gmdt)->data) != *(((gmdt_ufloat_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_D:
		{
			if (*(((gmdt_double_p_t*)src_gmdt)->data) != *(((gmdt_double_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_UD:
		{
			if (*(((gmdt_udouble_p_t*)src_gmdt)->data) != *(((gmdt_udouble_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	case GMP_GMDT_N:
		{
			return gmp_gmdt_true;
		}
		break;
	case GMP_GMDT_T:
		{
			if (*(((gmdt_type_p_t*)src_gmdt)->data) != *(((gmdt_type_p_t*)dest_gmdt)->data))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
		//	//��������(64--127):
		//case GMP_GMDT_A:
		//	{
		//		
		//	}
		//	break;
		//case GMP_GMDT_O:
		//	{
		//		
		//	}
		//	break;
		//case GMP_GMDT_X:
		//	{
		//		
		//	}
		//	break;
		//case GMP_GMDT_JS:
		//	{
		//		
		//	}
		//	break;
		//case GMP_GMDT_IOB:
		//	{
		//		
		//	}
		//	break;
		//��չ����(128--255):
	case GMP_GMDT_ST:
		{
			if (*(((gmdt_string_p_t*)src_gmdt)->len) != *(((gmdt_string_p_t*)dest_gmdt)->len))
			{
				return gmp_gmdt_false;
			}
			else
			{
				if (!gmp_std_strncmp(((gmdt_string_p_t*)src_gmdt)->data, ((gmdt_string_p_t*)dest_gmdt)->data, *(((gmdt_string_p_t*)src_gmdt)->len)))
				{
					return gmp_gmdt_true;
				}
				else
				{
					return gmp_gmdt_false;
				}
			}
		}
		break;
	case GMP_GMDT_R:
		{
			if(*(((gmdt_rect_p_t*)src_gmdt)->x1) != *(((gmdt_rect_p_t*)dest_gmdt)->x1) ||
				*(((gmdt_rect_p_t*)src_gmdt)->y1) != *(((gmdt_rect_p_t*)dest_gmdt)->y1) ||
				*(((gmdt_rect_p_t*)src_gmdt)->x2) != *(((gmdt_rect_p_t*)dest_gmdt)->x2) ||
				*(((gmdt_rect_p_t*)src_gmdt)->y2) != *(((gmdt_rect_p_t*)dest_gmdt)->y2))
			{
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmdt_true;
			}
		}
		break;
	default:
		{
			return gmp_gmdt_false;
		}
	}

	return gmp_gmdt_false;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmdu_setbuffer
* ��    ��:
*			��ʾ����buffer���������͵Ļ�����Ϣ
* ��    ��:
*			1��gmp_gmf_t							*gmf					[in]��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t						*gmdu					[out]��ʾ��Ҫ�������gmdt����
*			3��gmp_gmdu_segment					seg						[in]��ʾ��Ҫ���õ�key ���� value
*			4��const gm_std_char					*buf					[in]��ʾ����������ݵ�ַ
*			5��gm_std_int						len						[in]��ʾ����������ݳ���
*			6��gm_std_int						work_mode				[in]��ʾ����ģʽ
* �� �� ֵ:
*			pc_bool
*			ȡֵ˵��:
*					PC_TRUE : �ɹ� 
*					PC_FALSE: ʧ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2016-04-20 16:58:30
******************************************************************************************************/
gmp_gmdt_bool gmp_gmdu_setbuffer
(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdu_segment seg, const gm_std_char *buf, gm_std_int len, gm_std_int work_mode)
{
	if (!gmdu)
	{
		return gmp_gmdt_false;
	}

	return gmp_gmdt_setbuffer(gmf, gmp_get_gmdt(gmf, gmdu, seg), buf, len, work_mode);
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmdt_setbuffer
* ��    ��:
*			��ʾ����buffer���������͵Ļ�����Ϣ
* ��    ��:
*			1��gmp_gmf_t							*gmf					[in]��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdt_t						*dest_gmdt				[out]��ʾ��Ҫ�������gmdt����
*			3��const gm_std_char					*buf					[in]��ʾ����������ݵ�ַ
*			4��gm_std_int						len						[in]��ʾ����������ݳ���
*			5��gm_std_int						work_mode				[in]��ʾ����ģʽ
* �� �� ֵ:
*			pc_bool
*			ȡֵ˵��:
*					PC_TRUE : �ɹ� 
*					PC_FALSE: ʧ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2016-04-20 16:25:13
******************************************************************************************************/
gmp_gmdt_bool gmp_gmdt_setbuffer
(gmp_gmf_t *gmf, gmp_gmdt_t *dest_gmdt, const gm_std_char *buf, gm_std_int len, gm_std_int work_mode)
{
	if (!gmf || !dest_gmdt || !buf || !len)
	{
		return gmp_gmdt_false;
	}

	if (work_mode != gmf_work_mode_general &&
		work_mode != gmf_work_mode_shared_memory)
	{
		return gmp_gmdt_false;
	}

	if (!gmp_chk_gmdt(*gmp_get_p_type(dest_gmdt)))
	{
		return gmp_gmdt_false;
	}

	if (!gmp_gmdt_type_compare(gmp_get_p_type(dest_gmdt), GMP_GMDT_ST) &&
		!gmp_gmdt_type_compare(gmp_get_p_type(dest_gmdt), GMP_GMDT_IOB) &&
		!gmp_gmdt_type_compare(gmp_get_p_type(dest_gmdt), GMP_GMDT_X) &&
		!gmp_gmdt_type_compare(gmp_get_p_type(dest_gmdt), GMP_GMDT_JS))
	{
		return gmp_gmdt_false;
	}

	gmdt_string_p_t* tmp_gmdt = (gmdt_string_p_t*)dest_gmdt;
	if (work_mode == gmf_work_mode_shared_memory)
	{
		tmp_gmdt->data = (gm_std_char*)buf;
	}
	else
	{
		tmp_gmdt->data = (gm_std_char*)gmp_palloc(gmf->pool, len);
		if (!tmp_gmdt->data)
		{
			return gmp_gmdt_false;
		}
		gmp_std_memcpy(tmp_gmdt->data, buf, len);
	}

	*(tmp_gmdt->len) = len;

	return gmp_gmdt_true;
}


//////////////////////////////////////////////////////////////////////////
//���õ�ǰ�ڵ�λ��
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_reset_gmdu
* ��    ��:
*			��ʾ����ָ��gmduΪ��ǰgmdu
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*gmdu				��ʾ��Ҫ������Ϊ��ǰ�ڵ��gmdu
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_reset_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu)
{
	if (!gmf || !gmdu)
	{
		return gmp_gmdt_false;
	}

	gmf->current_gmdu = gmdu;

	return gmp_gmdt_true;
}



//���뵱ǰ�ڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_into_gmdu
* ��    ��:
*			��ʾ���뵱ǰgmdu�ڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
* �� �� ֵ:
*			���ص�ǰλ�õ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_into_gmdu(gmp_gmf_t *gmf)
{
	if (!gmf)
	{
		return NULL;
	}

	if (!gmf->current_gmdu)
	{
		return NULL;
	}

	if (!gmp_is_have_child(gmf->current_gmdu))
	{
		return NULL;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmf->current_gmdu->key))))
		{
			//�����ӽڵ�Ԫ��
			return gmp_into_object_gmdu(gmf, gmf->current_gmdu->key);
		}
		else
		{
			//�����ӽڵ�Ԫ��
			return gmp_into_object_gmdu(gmf, gmf->current_gmdu->val);
		}
	}

	return NULL;
}


//���������ڵ���
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_into_object_gmdu
* ��    ��:
*			��ʾ���뵱ǰ����������ӽڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gm_std_void				*obj				��ʾ�����ڵ�
* �� �� ֵ:
*			���ص�ǰλ�õ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_into_object_gmdu(gmp_gmf_t *gmf, gm_std_void *obj)
{
	gm_std_uint						i = 0;
	gm_std_uint						num = 0;




	if (!gmf || !obj)
	{
		return NULL;
	}

	switch((unsigned char)(*(gmp_get_p_type(obj))))
	{
	case GMP_GMDT_A:
		{
			gmdt_array_p_t *ary = (gmdt_array_p_t *)(obj);
			num = *(ary->nelts);

			if (num == 0 || !ary->elts)
			{
				return NULL;
			}

			gmf->current_gmdu = ary->elts;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t *ob = (gmdt_object_p_t *)(obj);
			num = *(ob->nelts);

			if (num == 0 || !ob->elts)
			{
				return NULL;
			}

			gmf->current_gmdu = ob->elts;
		}
		break;
	default:
		break;
	}

	return gmf->current_gmdu;
}


//��һ���ֵܽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_next_gmdu
* ��    ��:
*			��ʾ���뵱ǰgmdu�ڵ����һ���ڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
* �� �� ֵ:
*			���ص�ǰλ�õ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_next_gmdu(gmp_gmf_t *gmf)
{
	if (!gmf)
	{
		return NULL;
	}

	if (!gmf->current_gmdu)
	{
		return NULL;
	}

	if (!gmf->current_gmdu->next)
	{
		return NULL;
	}

	gmf->current_gmdu = (gmp_gmdu_t *)(gmf->current_gmdu->next);

	return gmf->current_gmdu;
}

//���õ���ǰ�ڵ�ĵ�һ���ӽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_first_gmdu
* ��    ��:
*			����ǰλ������Ϊ��һ���ӽڵ�λ��
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
* �� �� ֵ:
*			���ص�ǰλ�õ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_first_gmdu(gmp_gmf_t *gmf)
{
	gmp_gmdu_t				*gmdu;




	if (!gmf)
	{
		return NULL;
	}

	if (!gmf->current_gmdu)
	{
		return NULL;
	}

	if (!gmf->current_gmdu->parent)
	{
		return NULL;
	}

	gmdu = (gmp_gmdu_t*)(gmf->current_gmdu->parent);
	if (!gmp_is_have_child(gmdu))
	{
		return NULL;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu->key))))
		{
			//�����ӽڵ�Ԫ��
			return gmp_into_object_gmdu(gmf, gmdu->key);
		}
		else
		{
			//�����ӽڵ�Ԫ��
			return gmp_into_object_gmdu(gmf, gmdu->val);
		}
	}

	return NULL;
}

//���õ�gmf�ĵ�һ��gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_top_gmdu
* ��    ��:
*			����ǰλ������gmf�ĵ�һ��gmdu�ڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
* �� �� ֵ:
*			���ص�ǰλ�õ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_top_gmdu(gmp_gmf_t *gmf)
{
	if (!gmf)
	{
		return NULL;
	}

	if (!gmf->gmdu)
	{
		return NULL;
	}

	gmf->current_gmdu = gmf->gmdu;
	return gmf->current_gmdu;
}

//�˳���ǰ�ڵ�gmdu��������һ��gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_outof_gmdu
* ��    ��:
*			��������ǰ�ڵ㣬ָ���丸�ڵ�λ��
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
* �� �� ֵ:
*			���ص�ǰλ�õ�gmdu�ڵ�ָ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdu_t *gmp_outof_gmdu(gmp_gmf_t *gmf)
{
	if (!gmf)
	{
		return NULL;
	}

	if (!gmf->current_gmdu)
	{
		return NULL;
	}

	if (!gmf->current_gmdu->parent)
	{
		return NULL;
	}

	gmf->current_gmdu = (gmp_gmdu_t*)(gmf->current_gmdu->parent);
	return gmf->current_gmdu;
}



//////////////////////////////////////////////////////////////////////////
//��gmf�����һ���ֵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_add_gmdu
* ��    ��:
*			�ڵ�ǰλ�����һ���ֵܽڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в�����gmf�ṹ��
*			2��gmp_gmdu_t				*gmdu				��ʾ��Ҫ����ӵ�gmdu����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_add_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu)
{
	if (!gmf || !gmdu)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->gmdu)
	{
		gmf->gmdu = gmdu;
		gmf->current_gmdu = gmdu;

		return gmp_gmdt_true;
	}

	if (!gmf->current_gmdu)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->current_gmdu->parent)
	{
		return gmp_gmdt_false;
	}

	if(gmp_add_object_gmdu((gmp_gmdu_t *)(gmf->current_gmdu->parent), gmdu))
	{
		//����ɹ�����ָ��ָ���²���ڵ�
		gmf->current_gmdu = gmdu;
		return gmp_gmdt_true;
	}
	else
	{
		return gmp_gmdt_false;
	}
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_add_object_gmdu
* ��    ��:
*			��gmdu ��ӵ�ָ����gmdu��
* ��    ��:
*			1��gmp_gmdu_t				*dest_gmdu				��ʾ��Ҫ����ӵ�gmdu���ڵ�
*			2��gmp_gmdu_t				*src_gmdu				��ʾ��Ҫ����ӵ�gmdu����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_add_object_gmdu(gmp_gmdu_t *dest_gmdu, gmp_gmdu_t *src_gmdu)
{
	if (!dest_gmdu || !src_gmdu)
	{
		return gmp_gmdt_false;
	}

	if (!gmp_is_have_child(dest_gmdu))
	{
		return gmp_gmdt_false;
	}
	else
	{
		src_gmdu->parent = (gm_std_void*)dest_gmdu;

		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(dest_gmdu->key))))
		{
			//�����ӽڵ�Ԫ��
			return gmp_add_object_gmdt_gmdu(dest_gmdu->key, src_gmdu);
		}
		else
		{
			//�����ӽڵ�Ԫ��
			return gmp_add_object_gmdt_gmdu(dest_gmdu->val, src_gmdu);
		}
	}
	return gmp_gmdt_true;
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_add_object_gmdu
* ��    ��:
*			��gmdu ��ӵ�ָ����gmdu��
* ��    ��:
*			1��gm_std_void				*obj					��ʾ��Ҫ����ӵ�gmdt���ڵ�
*			2��gmp_gmdu_t				*src_gmdu				��ʾ��Ҫ����ӵ�gmdu����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_add_object_gmdt_gmdu(gm_std_void *obj, gmp_gmdu_t *src_gmdu)
{
	gm_std_uint						num = 0;






	if (!obj || !src_gmdu)
	{
		return gmp_gmdt_false;
	}

	src_gmdu->next = NULL;
	src_gmdu->prev = NULL;

	switch((unsigned char)(*(gmp_get_p_type(obj))))
	{
	case GMP_GMDT_A:
		{
			gmdt_array_p_t *ary = (gmdt_array_p_t *)(obj);
			num = *(ary->nelts);

			if(num)
			{
				src_gmdu->next = ary->elts;
				ary->elts->prev = src_gmdu;
			}

			ary->elts = src_gmdu;
			*(ary->nelts) = num + 1;
			return gmp_gmdt_true;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t *ob = (gmdt_object_p_t *)(obj);
			num = *(ob->nelts);

			if (num)
			{
				src_gmdu->next = ob->elts;
				ob->elts->prev = src_gmdu;
			}

			ob->elts = src_gmdu;
			*(ob->nelts) = num + 1;

			return gmp_gmdt_true;
		}
		break;
	default:
		break;
	}

	return gmp_gmdt_false;
}


//��gmf�����һ���ӽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_add_child_gmdu
* ��    ��:
*			�ڵ�ǰλ��gmdu�����һ���ӽڵ㣬��ӵ��ӽڵ㽫�Ǹ�gmdu�ĵ�һ���ӽڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*gmdu				��ʾ��Ҫ����ӵ�gmdu����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_add_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu)
{
	gmp_gmdu_t						*tmp_src_gmdu = NULL;




	if (!gmf || !gmdu)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->current_gmdu)
	{
		return gmp_gmdt_false;
	}

	tmp_src_gmdu = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t));
	if (!tmp_src_gmdu)
	{
		return gmp_gmdt_false;
	}
	else
	{
		*tmp_src_gmdu = *gmdu;
	}

	return gmp_add_object_gmdu(gmf->current_gmdu, tmp_src_gmdu);
}

//��һ������gmdt�����һ���ӽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_add_gmdu_child_gmdu
* ��    ��:
*			��ָ����gmdu�����һ����gmdu
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*dest_gmdu			��ʾ��Ҫ����ӽڵ��gmdu,Ŀ��gmdu
*			2��gmp_gmdu_t				*src_gmdu			��ʾ��Ҫ���������gmdu��Դgmdu
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_add_gmdu_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *dest_gmdu, gmp_gmdu_t *src_gmdu)
{
	gmp_gmdu_t						*tmp_src_gmdu = NULL;




	if (!gmf || !dest_gmdu || !src_gmdu)
	{
		return gmp_gmdt_false;
	}

	tmp_src_gmdu = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t));
	if (!tmp_src_gmdu)
	{
		return gmp_gmdt_false;
	}
	else
	{
		*tmp_src_gmdu = *src_gmdu;
	}

	return gmp_add_object_gmdu(dest_gmdu, tmp_src_gmdu);
}

//��gmf��ɾ����ǰgmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_delete_current_gmdu
* ��    ��:
*			��gmf��ɾ����ǰgmdu
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_delete_current_gmdu(gmp_gmf_t *gmf)
{
	if (!gmf)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->current_gmdu)
	{
		return gmp_gmdt_false;
	}

	return gmp_delete_this_gmdu(gmf, gmf->current_gmdu);
}

//��gmf��ɾ��һ���ֵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_delete_gmdu
* ��    ��:
*			�ӵ�ǰ�ڵ���ɾ��һ��gmdtָ�����ֵܽڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdt_t				*gmdt				��ʾ��Ҫ��ɾ��gmdt����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_delete_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt)
{
	if (!gmf || !gmdt)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->current_gmdu)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->current_gmdu->parent)
	{
		return gmp_gmdt_false;
	}

	return gmp_delete_object_gmdu(gmf, (gmp_gmdu_t *)(gmf->current_gmdu->parent), gmdt);
}


//��gmf��ɾ��һ���ӽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_delete_child_gmdu
* ��    ��:
*			�ӵ�ǰ�ڵ���ɾ��һ��gmdtָ�����ӽڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdt_t				*gmdt				��ʾ��Ҫ��ɾ��gmdt����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_delete_child_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt)
{

	if (!gmf || !gmdt)
	{
		return gmp_gmdt_false;
	}

	if (!gmf->current_gmdu)
	{
		return gmp_gmdt_false;
	}

	return gmp_delete_object_gmdu(gmf, gmf->current_gmdu, gmdt);
}


//��gmf��ɾ��һ���ӽڵ�gmdu
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_delete_object_gmdu
* ��    ��:
*			��ʾ��Ŀ��ڵ���ɾ��ָ��������Ϣ���ӽڵ�
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*dest_gmdu			��ʾ��Ҫ��ɾ��gmdu���ݵ�Ŀ��ڵ�
*			3��gmp_gmdt_t				*src_gmdt			��ʾ��Ҫ��ɾ���ڵ�����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_delete_object_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *dest_gmdu, gmp_gmdt_t *src_gmdt)
{
	gmp_gmdu_t						*gmdu;
	gm_std_void						*obj = NULL;
	gm_std_uint						num = 0;





	if (!dest_gmdu || !src_gmdt)
	{
		return gmp_gmdt_false;
	}

	if (!dest_gmdu->key || !dest_gmdu->val)
	{
		return gmp_gmdt_false;
	}

	if (!gmp_is_have_child(dest_gmdu))
	{
		return gmp_gmdt_false;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(dest_gmdu->key))))
		{
			//�����ӽڵ�Ԫ��
			obj = dest_gmdu->key;
		}
		else
		{
			//�����ӽڵ�Ԫ��
			obj = dest_gmdu->val;
		}

		if (!obj)
		{
			return gmp_gmdt_false;
		}
		else
		{
			switch((unsigned char)(*(gmp_get_p_type(obj))))
			{
			case GMP_GMDT_A:
				{
					gmdt_array_p_t *ary = (gmdt_array_p_t *)(obj);



					gmdu = ary->elts;
					for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next), ++num)
					{
						if (gmp_gmdt_keycmp(gmdu->key, src_gmdt))
						{
							*(ary->nelts) = *(ary->nelts) - 1;

							if (!num)
							{
								ary->elts = (gmp_gmdu_t*)gmdu->next;
							}
							else
							{
								((gmp_gmdu_t*)(gmdu->prev))->next = gmdu->next;
							}

							if (gmdu->next)
							{
								((gmp_gmdu_t*)(gmdu->next))->prev = gmdu->prev;
							}

							return gmp_gmdt_true;
						}
					}

					return gmp_gmdt_false;
				}
				break;
			case GMP_GMDT_O:
				{
					gmdt_object_p_t *ob = (gmdt_object_p_t *)(obj);



					gmdu = ob->elts;
					for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next), ++num)
					{
						if (gmp_gmdt_keycmp(gmdu->key, src_gmdt))
						{
							*(ob->nelts) = *(ob->nelts) - 1;

							if (!num)
							{
								ob->elts = (gmp_gmdu_t*)gmdu->next;
							}
							else
							{
								((gmp_gmdu_t*)(gmdu->prev))->next = gmdu->next;
							}

							if (gmdu->next)
							{
								((gmp_gmdu_t*)(gmdu->next))->prev = gmdu->prev;
							}

							return gmp_gmdt_true;
						}
					}

					return gmp_gmdt_false;
				}
				break;
			default:
				{
					return gmp_gmdt_false;
				}
				break;
			}
		}
	}

	return gmp_gmdt_false;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_delete_current_gmdu
* ��    ��:
*			��gmf��ɾ����ǰgmdu
* ��    ��:
*			1��gmp_gmf_t				*gmf				��ʾ��Ҫ���в��Ҳ�����gmf�ṹ��
*			2��gmp_gmdu_t				*gmdu				��ʾ��Ҫɾ���Ľڵ�����
* �� �� ֵ:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-2-22 16:23
******************************************************************************************************/
gmp_gmdt_bool gmp_delete_this_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu)
{
	gmp_gmdu_t						*gmdu_prev;
	gmp_gmdu_t						*gmdu_next;
	gmp_gmdu_t						*gmdu_parent;
	gm_std_void						*obj = NULL;






	if (!gmdu)
	{
		return gmp_gmdt_false;
	}

	gmdu_prev = (gmp_gmdu_t*)(gmdu->prev);
	if (!gmdu_prev)
	{
		gmdu_parent = (gmp_gmdu_t*)(gmdu->parent);
		if (!gmp_is_have_child(gmdu_parent))
		{
			return gmp_gmdt_false;
		}
		else
		{
			if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu_parent->key))))
			{
				//�����ӽڵ�Ԫ��
				obj = gmdu_parent->key;
			}
			else
			{
				//�����ӽڵ�Ԫ��
				obj = gmdu_parent->val;
			}

			if (!obj)
			{
				return gmp_gmdt_false;
			}
			else
			{
				switch((unsigned char)(*(gmp_get_p_type(obj))))
				{
				case GMP_GMDT_A:
					{
						gmdt_array_p_t *ary = (gmdt_array_p_t *)(obj);


						*(ary->nelts) = *(ary->nelts) - 1;
						ary->elts = (gmp_gmdu_t*)(gmdu->next);
						return gmp_gmdt_true;
					}
					break;
				case GMP_GMDT_O:
					{
						gmdt_object_p_t *ob = (gmdt_object_p_t *)(obj);


						*(ob->nelts) = *(ob->nelts) - 1;
						ob->elts = (gmp_gmdu_t*)(gmdu->next);
						return gmp_gmdt_true;
					}
					break;
				default:
					{
						return gmp_gmdt_false;
					}
					break;
				}
			}
		}
	}
	else
	{
		gmdu_next = (gmp_gmdu_t*)(gmdu->next);
		gmdu_prev->next = gmdu_next;

		if (gmdu_next)
		{
			gmdu_next->prev = gmdu_prev;
		}

		return gmp_gmdt_true;
	}


	return gmp_gmdt_false;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_decode
* ��    ��:
*			����gmf��ʽ������
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*src		��ʾ��Ҫ������gmf����
*			3��gm_std_uint			len			��ʾgmf���ݵĳ���
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			2��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			�ú�����gmf��������ں���
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_decode(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len)
{
	gmp_gmf_gmfh_t			*gmfh_p;
	gm_std_uchar			*p;
	gm_std_int				data_len = 0;






	//�������Ϊ0�����ش���
	if (!gmf || !src || len <= gmp_std_sizeof(gmp_gmf_gmfh_t))
	{
		return gmp_gmdt_false;
	}

	//�ж����ݳ��ȵĺϷ���,��ȡ��ȷ�ĳ�������
	gmfh_p = (gmp_gmf_gmfh_t*)src;
	if (len < (gm_std_int)(gmfh_p->size + gmp_std_sizeof(gmp_gmf_gmfh_t)))
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "data is lost error. len[%d] < size[%d]", 
			len, 
			(gmfh_p->size + gmp_std_sizeof(gmp_gmf_gmfh_t)));
		return gmp_gmdt_false;
	}
	else
	{
		data_len = gmfh_p->size + gmp_std_sizeof(gmp_gmf_gmfh_t);
	}

	if (gmf_work_mode_shared_memory == gmf->work_mode)
	{
		//����ǹ����ڴ淽ʽ���򲻿�������
		p = src;
	}
	else {
		//����һ���ڴ棬����������ݱ���һ�ݣ���Ϊ֮���ٸ������ݣ�ֱ��ʹ��ָ��
		p = (gm_std_uchar *)gmp_palloc(gmf->pool, data_len);
		if (!p)
		{
			gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
				data_len, gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

			return gmp_gmdt_false;
		}

		gmp_std_memcpy(p, src, data_len);
	}

	//���gmf�Ļ�����Ϣ���������pool����
	gmp_std_memset(gmf, 0, gmp_std_sizeof(gmp_gmf_t) - gmp_std_sizeof(gmp_pool_t*));

	//��ȡgmfhͷ��Ϣ
	if (!gmp_gmf_get_gmfh(gmf, p, data_len))
	{
		return gmp_gmdt_false;
	}

	//У��gmfh�Ƿ�׼ȷ
	if (!gmp_gmf_check_gmfh(gmf))
	{
		return gmp_gmdt_false;
	}

	gmfh_p = &(gmf->gmfh);

	switch (gmfh_p->size)
	{
	case 0:
		{
			gmf->gmdu = gmp_std_null;
		}
		break;
	case 1:
		{
			return gmp_gmf_parse(gmf, p + gmp_std_sizeof(gmp_gmf_gmfh_t), data_len - gmp_std_sizeof(gmp_gmf_gmfh_t));
		}
		break;
	default:
		{
			if (gmfh_p->size > data_len - gmp_std_sizeof(gmp_gmf_gmfh_t))
			{
				//������ݳ��Ȳ������򷵻ش���
				gmp_set_gmf_error(gmf, gmf_error_format, "data lenght error. gmfh_length[%d] != body_length[%d]." , 
					gmfh_p->size, (data_len - gmp_std_sizeof(gmp_gmf_gmfh_t)));
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmf_parse(gmf, p + gmp_std_sizeof(gmp_gmf_gmfh_t), data_len - gmp_std_sizeof(gmp_gmf_gmfh_t));
			}
		}
		break;
	}
	return gmp_gmdt_false;
}

//����һ��gmf��ʽ������
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_encode
* ��    ��:
*			��ȡgmf��ʽ�����ݣ���������gmdt_iobuffer_p_t ����destָ���Ļ�����
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gmdt_iobuffer_p_t		**iob		��ʾת������Ҫ�������ݵ�iobuffer�ṹ���У��������Ҫ���浽iobuffer�У���NULL
*			3��gm_std_uchar				*dest		��ʾת���󱣴����ݵĻ��棬��ֵֻ�е�iobΪNULLʱ��Ч
*			4��gm_std_uint				len			��ʾ�������ݵ�dest����ռ�Ĵ�С����ֵֻ�е�iobΪNULLʱ��Ч
* �� �� ֵ:
*			����ת�������ݵĳ��ȣ���Ϊ0��ʾ�����ݻ��ߴ��󣻵�����ʱ�����Բ�ѯgmf���ֲ�ѯ
*			��0��ʾ���ص�gmf���ݵĳ��ȣ���ע������ݲ�����gmf�����ͷ��Ϣ
* ��    ע:
*			�ú�����gmf��������ں���
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_encode(gmp_gmf_t *gmf, gmdt_iobuffer_p_t **iob, gm_std_uchar *dest, gm_std_uint len)
{
	gm_std_uint					count = 0;
	gm_std_uint					total = 0;
	gm_std_uint					buf_len = 0;
	gm_std_int					ret_len = 0;
	gm_std_uchar				*buf;
	gmdt_iobuffer_t				*i;





	if (!gmf || (!iob && !dest))
	{
		return 0;
	}

	if (!iob && (!dest || len < gmp_std_sizeof(gmp_gmf_gmfh_t)))
	{
		gmp_set_gmf_error(gmf, gmf_error_encode_parament, "gmf encode parament error. iob / dest is null.");
		return 0;
	}

	//����gmf�ĳ���
	count = gmp_gmf_count(gmf);
	if (!count)
	{
		return 0;
	}

	//�������gmfh����ܳ���
	total = count + gmp_std_sizeof(gmp_gmf_gmfh_t);

	if (iob)
	{
		*iob = (gmdt_iobuffer_p_t *)gmp_palloc(gmf->pool, gmp_std_sizeof(gmdt_iobuffer_p_t));
		i = (gmdt_iobuffer_t *)gmp_palloc(gmf->pool, gmp_std_sizeof(gmdt_iobuffer_t));
		if (!*iob || !i)
		{
			return 0;
		}

		buf = (gm_std_uchar *)gmp_palloc(gmf->pool, total);
		if (!buf)
		{
			return 0;
		}

		i->gmdt = GMP_GMDT_IOB;
		i->len = total;
		i->data = buf;

		(*iob)->gmdt = &(i->gmdt);
		(*iob)->len = &(i->len);
		(*iob)->data = i->data;

		buf_len = total;
	}
	else
	{
		if (!dest || len < total)
		{
			return 0;
		}

		buf = dest;
		buf_len = len;
	}

	//����gmfh��Ϣ
	gmp_set_gmfh(gmf, 1, 0, 1);
	gmf->gmfh.size = count;

	//����gmfhͷ��������
	gmp_std_cpymem(buf, gmf->gmfh.gmff, gmp_std_sizeof(gmp_gmf_gmfh_t));

	//���������ַ���
	ret_len = gmp_gmf_encode_gmdu(gmf, gmf->gmdu, (buf + gmp_std_sizeof(gmp_gmf_gmfh_t)), (buf_len - gmp_std_sizeof(gmp_gmf_gmfh_t)));
	if (ret_len <= 0)
	{
		return ret_len;
	}

	return total;
}

//����gmfh
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_set_gmfh
* ��    ��:
*			����gmfhͷ��Ϣ
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar				version		��ʾ���ð汾��Ϣ
*			3��gm_std_uchar				endian		��ʾ�����ֽ���
*			4��gm_std_uchar				encode		��ʾ���ñ��뷽ʽ
* �� �� ֵ:
*			�������óɹ����
* ��    ע:
*			���سɹ����,true��ʾ�ɹ�;false��ʾʧ��;
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_set_gmfh(gmp_gmf_t *gmf, gm_std_uchar version, gm_std_uchar endian, gm_std_uchar encode)
{
	if (!gmf)
	{
		return gmp_gmdt_false;
	}

	gmp_std_strcpy(gmf->gmfh.gmff, GMP_GMF_GMFF);

	gmf->gmfh.version = version;
	gmf->gmfh.endian = endian;
	gmf->gmfh.encode = encode;

	return gmp_gmdt_true;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_set_work_mode
* ��    ��:
*			���ù���ģʽ
* ��    ��:
*			1��gmp_gmf_t							*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_int						work_mode	��ʾ����ģʽ��ֵ

* �� �� ֵ:
*			pc_bool
*			ȡֵ˵��:
*					PC_TRUE : �ɹ� 
*					PC_FALSE: ʧ��
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2016-02-03 17:43:16
******************************************************************************************************/
gmp_gmdt_bool gmp_set_work_mode(gmp_gmf_t *gmf, gm_std_int work_mode)
{
	if (work_mode < 0)
	{
		return gmp_gmdt_false;
	}

	if (gmf_work_mode_general != work_mode &&
		gmf_work_mode_shared_memory != work_mode)
	{
		return gmp_gmdt_false;
	}

	gmf->work_mode = work_mode;
	return gmp_gmdt_true;
}


//����һ��gmf��ʽ������
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_count
* ��    ��:
*			ͳ��gmf��������
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
* �� �� ֵ:
*			����gmf��������
* ��    ע:
*			�ú�����gmf��������ں���
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-02-25 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_count(gmp_gmf_t *gmf)
{
	return gmp_gmf_count_gmdu(gmf, gmf->gmdu);
}


//ͳ��gmdu��������
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_count_gmdu
* ��    ��:
*			ͳ��gmdt��������
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gmp_gmdu_t				*gmdu		��ʾ��Ҫ����ͳ�Ƶ�gmdu
* �� �� ֵ:
*			����gmdu��������
* ��    ע:
*			�ú�����gmf��������ں���
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-02-25 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_count_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu)
{
	gm_std_uint					sum = 0;





	if (!gmdu)
	{
		return 0;
	}

	if (!gmdu->key || !gmdu->val)
	{
		return 0;
	}

	if (gmdu->key)
	{
		sum += gmp_gmf_count_gmdt(gmf, (gmp_gmdt_t*)(gmdu->key));
	}
	else
	{
		return 0;
	}

	if (gmdu->val)
	{
		sum += gmp_gmf_count_gmdt(gmf, (gmp_gmdt_t*)(gmdu->val));
	}
	else
	{
		return 0;
	}

	//if (gmp_is_have_child(gmdu))
	//{
	//	if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu->key))))
	//	{
	//		sum += gmp_gmf_count_gmdt(gmf, (gmp_gmdt_t*)(gmdu->key));
	//	}
	//	else
	//	{
	//		sum += gmp_gmf_count_gmdt(gmf, (gmp_gmdt_t*)(gmdu->val));
	//	}
	//}

	return sum;
}


//ͳ��gmdt��������
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_count_gmdt
* ��    ��:
*			ͳ��gmdt��������
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gmp_gmdt_t				*gmdt		��ʾ��Ҫ����ͳ�Ƶ�gmdt
* �� �� ֵ:
*			����gmdt��������
* ��    ע:
*			�ú�����gmf��������ں���
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-02-25 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_count_gmdt(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt)
{
	if (!gmf || !gmdt)
	{
		return 0;
	}

	switch(*gmp_get_p_type(gmdt))
	{
		//���û�����������(0--63)
	case GMP_GMDT_B:
	case GMP_GMDT_C:
	case GMP_GMDT_UC:
		{
			return gmp_std_sizeof(gmdt_uchar_t);
		}
		break;
	case GMP_GMDT_S:
	case GMP_GMDT_US:
		{
			return gmp_std_sizeof(gmdt_ushort_t);
		}
		break;
	case GMP_GMDT_IN:
	case GMP_GMDT_UIN:
		{
			return gmp_std_sizeof(gmdt_uint_t);
		}
		break;
	case GMP_GMDT_L:
	case GMP_GMDT_UL:
		{
			return gmp_std_sizeof(gmdt_ulong_t);
		}
		break;
	case GMP_GMDT_F:
	case GMP_GMDT_UF:
		{
			return gmp_std_sizeof(gmdt_ufloat_t);
		}
		break;
	case GMP_GMDT_D:
	case GMP_GMDT_UD:
		{
			return gmp_std_sizeof(gmdt_udouble_t);
		}
		break;
	case GMP_GMDT_N:
		{
			return 1;
		}
		break;
	case GMP_GMDT_T:
		{
			return gmp_std_sizeof(gmdt_type_t);
		}
		break;
		//��������(64--127):
	case GMP_GMDT_A:
		{
			gmdt_array_p_t		*ary = (gmdt_array_p_t *)(gmdt);
			gmp_gmdu_t			*gmdu = ary->elts;
			gm_std_uint			n = 5;



			for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			{
				n += gmp_gmf_count_gmdu(gmf, gmdu);
			}

			return n;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t		*obj = (gmdt_object_p_t *)(gmdt);
			gmp_gmdu_t			*gmdu = obj->elts;
			gm_std_uint			n = 5;



			for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			{
				n += gmp_gmf_count_gmdu(gmf, gmdu);
			}

			return n;
		}
		break;
	case GMP_GMDT_X:
		{
			return (5 + *(((gmdt_xml_p_t*)gmdt)->len));
		}
		break;
	case GMP_GMDT_JS:
		{
			return (5 + *(((gmdt_json_p_t*)gmdt)->len));
		}
		break;
	case GMP_GMDT_IOB:
		{
			return (5 + *(((gmdt_iobuffer_p_t*)gmdt)->len));
		}
		break;
		//��չ����(128--255):
	case GMP_GMDT_ST:
		{
			return (5 + *(((gmdt_string_p_t*)gmdt)->len));
		}
		break;
	case GMP_GMDT_R:
		{
			return gmp_std_sizeof(gmdt_rect_t);
		}
		break;
	case GMP_GMDT_RP:
		{
			return gmp_std_sizeof(gmdt_rectpair_t);
		}
		break;
	default:
		{
			return 0;
		}
	}

	return 0;
}


//����gmdu�ڵ�����
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_encode_gmdu
* ��    ��:
*			��ʾ����gmdu�ڵ�����
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬����Ҫ�����������
*			2��gmp_gmdu_t				*gmdu		��ʾ��Ҫ���б����gmdu
*			3��gm_std_uchar				*src		��ʾ��������ŵĻ���
*			4��gm_std_uint				len			��ʾ��ű���������ĳ���
* �� �� ֵ:
*			����gmdu��������
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-02-24 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_encode_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gm_std_uchar *src, gm_std_int len)
{
	gm_std_uint					n = len;
	gm_std_uint					ret = 0;
	gm_std_uchar				*p = src;





	//�ж�������Ч��
	if (!gmf || !gmdu)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "gmf format error. gmf / gmdu is null");
		return 0;
	}

	if (!src || len <= 0)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "memory error. src memory is null / len <= 0");
		return 0;
	}

	if (!gmdu->key || !gmdu->val)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "gmf format error. gmdu key / value is null");
		return 0;
	}

	//��ʼ����gmdu��key��������
	ret = gmp_gmf_encode_gmdt(gmf, (gmp_gmdt_t*)(gmdu->key), p, n);
	if (!ret)
	{
		return 0;
	}
	//���¼��㻺���ַ���ͻ��泤��
	p += ret;
	n -= ret;

	//��ʼ����gmdu��value��������
	ret = gmp_gmf_encode_gmdt(gmf, (gmp_gmdt_t*)(gmdu->val), p, n);
	if (!ret)
	{
		return 0;
	}
	p += ret;
	n -= ret;


	if (!gmp_is_have_child(gmdu))
	{
		//��������������ֱ�ӷ��ؽ��
		return (len - n);
	}
	else
	{
		//��ʼ����������������
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu->key))))
		{
			ret = gmp_gmf_encode_array_object(gmf, (gmp_gmdt_t*)(gmdu->key), p, n);
		}
		else
		{
			ret = gmp_gmf_encode_array_object(gmf, (gmp_gmdt_t*)(gmdu->val), p, n);
		}

		n-= ret;

		return (len - n);
	}

	return 0;
}


//����gmdt�ڵ�����
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_encode_gmdt
* ��    ��:
*			��ʾ����gmdu�ڵ�����
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬����Ҫ�����������
*			2��gmp_gmdt_t				*gmdt		��ʾ��Ҫ���б����gmdt
*			3��gm_std_uchar				*src		��ʾ��������ŵĻ���
*			4��gm_std_uint				len			��ʾ��ű���������ĳ���
* �� �� ֵ:
*			����gmdt��������
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-02-24 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_encode_gmdt(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt, gm_std_uchar *src, gm_std_int len)
{
	gm_std_uint					n = len;
	gm_std_uint					ret = 0;
	gm_std_uint					num = 0;
	gm_std_uchar				*p = src;






	if (!gmf || !gmdt)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "gmf format error. gmf / gmdu is null");
		return 0;
	}

	switch(*gmp_get_p_type(gmdt))
	{
		//���û�����������(0--63)
	case GMP_GMDT_B:
	case GMP_GMDT_C:
	case GMP_GMDT_UC:
		{
			if (gmp_std_sizeof(gmdt_uchar_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_uchar_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_uchar_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uchar_t));

			return gmp_std_sizeof(gmdt_uchar_t);
		}
		break;
	case GMP_GMDT_S:
	case GMP_GMDT_US:
		{
			if (gmp_std_sizeof(gmdt_ushort_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_ushort_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_uchar_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_ushort_t));

			return gmp_std_sizeof(gmdt_ushort_t);
		}
		break;
	case GMP_GMDT_IN:
	case GMP_GMDT_UIN:
		{
			if (gmp_std_sizeof(gmdt_uint_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_uint_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_uint_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			return gmp_std_sizeof(gmdt_uint_t);
		}
		break;
	case GMP_GMDT_L:
	case GMP_GMDT_UL:
		{
			if (gmp_std_sizeof(gmdt_ulong_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_ulong_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_ulong_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_ulong_t));

			return gmp_std_sizeof(gmdt_ulong_t);
		}
		break;
	case GMP_GMDT_F:
	case GMP_GMDT_UF:
		{
			if (gmp_std_sizeof(gmdt_ufloat_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_ufloat_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_ufloat_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_ufloat_t));

			return gmp_std_sizeof(gmdt_ufloat_t);
		}
		break;
	case GMP_GMDT_D:
	case GMP_GMDT_UD:
		{
			if (gmp_std_sizeof(gmdt_udouble_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_udouble_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_udouble_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_udouble_t));

			return gmp_std_sizeof(gmdt_udouble_t);
		}
		break;
	case GMP_GMDT_N:
		{
			if (1 > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, 1);
				return 0;
			}

			*p++ = *(((gmdt_uchar_p_t*)gmdt)->gmdt);

			return 1;
		}
		break;
	case GMP_GMDT_T:
		{
			if (gmp_std_sizeof(gmdt_type_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_type_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_type_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_type_t));

			return gmp_std_sizeof(gmdt_type_t);
		}
		break;
		//��������(64--127):
	case GMP_GMDT_A:
		{
			gmdt_array_p_t				*ary = (gmdt_array_p_t *)(gmdt);
			gmp_gmdu_t					*gmdu = ary->elts;





			if (gmp_std_sizeof(gmdt_uint_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_uint_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_uint_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			//���¼��㻺���ַ�ͻ����С
			//p += gmp_std_sizeof(gmdt_uint_t);
			n -= gmp_std_sizeof(gmdt_uint_t);

			//for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			//{
			//	ret = gmp_gmf_encode_gmdu(gmf, gmdu, p, n);

			//	if (!ret)
			//	{
			//		return 0;
			//	}

			//	p += ret;
			//	n -= ret;
			//}

			return (len - n);
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t				*obj = (gmdt_object_p_t *)(gmdt);
			gmp_gmdu_t					*gmdu = obj->elts;




			if (gmp_std_sizeof(gmdt_uint_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_uint_t));
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_uint_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			//���¼��㻺���ַ�ͻ����С
			//p += gmp_std_sizeof(gmdt_uint_t);
			n -= gmp_std_sizeof(gmdt_uint_t);

			//for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			//{
			//	ret = gmp_gmf_encode_gmdu(gmf, gmdu, p, n);

			//	if (!ret)
			//	{
			//		return 0;
			//	}

			//	p += ret;
			//	n -= ret;
			//}

			return (len - n);
		}
		break;
	case GMP_GMDT_X:
		{
			num = (5 + *(((gmdt_xml_p_t*)gmdt)->len));

			if (num > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, num);
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_xml_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			if (*(((gmdt_xml_p_t*)gmdt)->len) <= 0)
			{
				((gmdt_xml_p_t*)gmdt)->data = NULL;
				return num;
			}

			//���¼��㻺���ַ�ͻ����С
			p += gmp_std_sizeof(gmdt_uint_t);

			gmp_std_strncpy((gm_std_char*)p, (gm_std_char*)((gmdt_xml_p_t*)gmdt)->data, *(((gmdt_xml_p_t*)gmdt)->len));

			return num;
		}
		break;
	case GMP_GMDT_JS:
		{
			num = (5 + *(((gmdt_json_p_t*)gmdt)->len));

			if (num > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, num);
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_json_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			if (*(((gmdt_json_p_t*)gmdt)->len) <= 0)
			{
				((gmdt_json_p_t*)gmdt)->data = NULL;
				return num;
			}

			//���¼��㻺���ַ�ͻ����С
			p += gmp_std_sizeof(gmdt_uint_t);

			gmp_std_strncpy((gm_std_char*)p, (gm_std_char*)((gmdt_json_p_t*)gmdt)->data, *(((gmdt_json_p_t*)gmdt)->len));

			return num;
		}
		break;
	case GMP_GMDT_IOB:
		{
			num = (5 + *(((gmdt_iobuffer_p_t*)gmdt)->len));

			if (num > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, num);
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_iobuffer_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			if (*(((gmdt_iobuffer_p_t*)gmdt)->len) <= 0)
			{
				((gmdt_iobuffer_p_t*)gmdt)->data = NULL;
				return num;
			}

			//���¼��㻺���ַ�ͻ����С
			p += gmp_std_sizeof(gmdt_uint_t);

			gmp_std_cpymem(p, ((gmdt_iobuffer_p_t*)gmdt)->data, *(((gmdt_iobuffer_p_t*)gmdt)->len));

			return num;
		}
		break;
		//��չ����(128--255):
	case GMP_GMDT_ST:
		{
			num = (5 + *(((gmdt_string_p_t*)gmdt)->len));

			if (num > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, num);
				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_string_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_uint_t));

			if (*(((gmdt_string_p_t*)gmdt)->len) <= 0)
			{
				((gmdt_string_p_t*)gmdt)->data = NULL;
				return num;
			}

			//���¼��㻺���ַ�ͻ����С
			p += gmp_std_sizeof(gmdt_uint_t);

			gmp_std_strncpy((gm_std_char*)p, (gm_std_char*)((gmdt_string_p_t*)gmdt)->data, *(((gmdt_string_p_t*)gmdt)->len));

			return num;
		}
		break;
	case GMP_GMDT_R:
		{
			if (gmp_std_sizeof(gmdt_rect_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_rect_t));

				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_rect_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_rect_t));

			return gmp_std_sizeof(gmdt_rect_t);
		}
		break;
	case GMP_GMDT_RP:
		{
			if (gmp_std_sizeof(gmdt_rectpair_t) > n)
			{
				gmp_set_gmf_error(gmf, gmf_error_alloc_memory, 
					"memory error. src memory not enough.  len %d <= %d", n, gmp_std_sizeof(gmdt_rectpair_t));

				return 0;
			}

			gmp_std_cpymem(p, ((gmdt_rectpair_p_t*)gmdt)->gmdt, gmp_std_sizeof(gmdt_rectpair_t));

			return gmp_std_sizeof(gmdt_rectpair_t);
		}
		break;
	default:
		{
			return 0;
		}
	}

	return 0;
}


//����array / object�ڵ�����
/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_encode_array_object
* ��    ��:
*			��ʾ����array / object�ڵ�����
* ��    ��:
*			1��gmp_gmf_t				*gmf		��ʾgmf�ṹ������ָ�룬����Ҫ�����������
*			2��gmp_gmdt_t				*gmdt		��ʾ��Ҫ���б����gmdt
*			3��gm_std_uchar				*src		��ʾ��������ŵĻ���
*			4��gm_std_uint				len			��ʾ��ű���������ĳ���
* �� �� ֵ:
*			����array / object��������
* ��    ע:
*			
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2014-02-24 15:23
******************************************************************************************************/
gm_std_uint gmp_gmf_encode_array_object(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt, gm_std_uchar *src, gm_std_int len)
{
	gm_std_uint					n = len;
	gm_std_uint					ret = 0;
	gm_std_uint					num = 0;
	gm_std_uchar				*p = src;






	if (!gmf || !gmdt)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "gmf format error. gmf / gmdu is null");
		return 0;
	}

	switch(*gmp_get_p_type(gmdt))
	{
		//��������(64--127):
	case GMP_GMDT_A:
		{
			gmdt_array_p_t				*ary = (gmdt_array_p_t *)(gmdt);
			gmp_gmdu_t					*gmdu = ary->elts;




			for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			{
				ret = gmp_gmf_encode_gmdu(gmf, gmdu, p, n);

				if (!ret)
				{
					return 0;
				}

				p += ret;
				n -= ret;
			}

			return (len - n);
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t				*obj = (gmdt_object_p_t *)(gmdt);
			gmp_gmdu_t					*gmdu = obj->elts;




			for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
			{
				ret = gmp_gmf_encode_gmdu(gmf, gmdu, p, n);

				if (!ret)
				{
					return 0;
				}

				p += ret;
				n -= ret;
			}

			return (len - n);
		}
		break;
	default:
		{
			return 0;
		}
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_get_gmfh
* ��    ��:
*			��ȡgmfh��������
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*src		��ʾ��Ҫ������gmf����
*			3��gm_std_uint			len			��ʾgmf���ݵĳ���
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_get_gmfh(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len)
{
	if (len < gmp_std_sizeof(gmp_gmf_gmfh_t))
	{
		//src length error
		gmp_set_gmf_error(gmf, gmf_error_format, "gmfh length error. len[%d]", len);
		return gmp_gmdt_false;
	}

	gmp_std_memcpy(&(gmf->gmfh), src, gmp_std_sizeof(gmp_gmf_gmfh_t));

	return gmp_gmdt_true;
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_check_gmfh
* ��    ��:
*			У��gmfh�������ݣ���֤��Ϣ��׼ȷ��
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_check_gmfh(gmp_gmf_t *gmf)
{
	if (gmp_std_strncmp(gmf->gmfh.gmff, GMP_GMF_GMFF, 4))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "not \"GMFT\" flag error. ");
		return gmp_gmdt_false;
	}

	return gmp_gmdt_true;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_check_gmfh
* ��    ��:
*			����gmf��ʽ���ݵ�����
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*src		��ʾgmf���ݵ���ʼλ��
*			3��gm_std_uint			len			��ʾgmf���ݵĳ���
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_parse(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len)
{
	if (!src || len <= 0)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_gmdt_false;
	}

	if (!gmp_chk_gmdt(*src))
	{
		gmp_set_gmf_error(gmf, gmf_error_unkown_type, "body type error. unknow type[%d]", *src);
		return gmp_gmdt_false;
	}

	gmf->gmdu = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t));
	if (!gmf->gmdu)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmp_gmdu_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_gmdt_false;
	}

	gmp_std_memset(gmf->gmdu, 0, gmp_std_sizeof(gmp_gmdu_t));

	gmf->gmdu->parent = NULL;
	gmf->current_gmdu = gmf->gmdu;
	gmf->gmdu->gmf = gmf;

	if (!gmp_gmf_get_gmdu(gmf, (gm_std_void **)(&(gmf->gmdu)), src, len))
	{
		return gmp_gmdt_false;
	}

	return gmp_gmdt_true;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_get_gmdu
* ��    ��:
*			����������ֵ������
* ��    ��:
*			1��gmp_gmf_t			*gmf				��ʾ��Ҫ�����gmf
*			2��gm_std_void			**dest				��ʾ�����������λ��
*			3��gm_std_uchar			*src				��ʾԪ�����ݵ����λ��
*			4��gm_std_uint			len					��ʾԪ�����ݵĳ���
* �� �� ֵ:
*			������һ�����ݵ���ʼλ��
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gm_std_uchar* gmp_gmf_get_gmdu(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmp_gmdu_t						*gmdu_p = (gmp_gmdu_t*)*dest;
	gm_std_uint						last = 0;
	gm_std_uchar					*ret;





	if (!src || len <= 0)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	ret = gmp_gmf_get_gmdt(gmf, &(gmdu_p->key), src, len);
	if (!ret)
	{
		return gmp_std_null;
	}

	ret = gmp_gmf_get_gmdt(gmf, &(gmdu_p->val), ret, (len - (ret - src)));
	if (!ret)
	{
		return gmp_std_null;
	}

	if (!gmp_is_have_child(gmdu_p))
	{
		return ret;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu_p->key))))
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_gmf_get_child_gmdu(gmf, gmdu_p, &(gmdu_p->key), ret, (len - (ret - src)));
		}
		else
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_gmf_get_child_gmdu(gmf, gmdu_p, &(gmdu_p->val), ret, (len - (ret - src)));
		}
	}
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_get_child_gmdu
* ��    ��:
*			����������ֵ������
* ��    ��:
*			1��gmp_gmf_t			*gmf				��ʾ��Ҫ�����gmf
*			2��gmp_gmdu_t			*gmdu				��ʾ��Ҫ���õĽڵ�
*			3��gm_std_void			**dest				��ʾ�����������λ��
*			4��gm_std_uchar			*src				��ʾԪ�����ݵ����λ��
5��gm_std_uint			len					��ʾԪ�����ݵĳ���
* �� �� ֵ:
*			������һ�����ݵ���ʼλ��
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gm_std_uchar* gmp_gmf_get_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gm_std_int						i = 0;
	gm_std_int						num = 0;
	gm_std_uchar					*ret = src;
	gmp_gmdu_t						*p;
	gmp_gmdu_t						*gmdu_child_p;





	if (!src || len < 0)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	switch((unsigned char)(*(gmp_get_p_type((*dest)))))
	{
	case GMP_GMDT_A:
		{
			gmdt_array_p_t *ary = (gmdt_array_p_t *)(*dest);
			num = (gm_std_int)(*(ary->nelts));

			if (num <= 0)
			{
				p = NULL;
			}
			else
			{
				p = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t) * num);
				if (!p)
				{
					gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
						gmp_std_sizeof(gmp_gmdu_t) * num, gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

					return gmp_std_null;
				}

				gmp_std_memset(p, 0, gmp_std_sizeof(gmp_gmdu_t) * num);
			}

			ary->elts = p;
			gmdu_child_p = p;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t *obj = (gmdt_object_p_t *)(*dest);
			num = (gm_std_int)(*(obj->nelts));

			if (num <= 0)
			{
				p = NULL;
			}
			else
			{
				p = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t) * num);
				if (!p)
				{
					gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
						gmp_std_sizeof(gmp_gmdu_t) * num, gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

					return gmp_std_null;
				}

				gmp_std_memset(p, 0, gmp_std_sizeof(gmp_gmdu_t) * num);
			}

			obj->elts = p;
			gmdu_child_p = p;
		}
		break;
	default:
		{
			gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type[%d].", (unsigned char)(*(gmp_get_p_type((*dest)))));
			return gmp_std_null;
		}
		break;
	}

	for (i = 0; i < num; i++)
	{
		p = &gmdu_child_p[i];

		if (i)
		{
			gmdu_child_p[i - 1].next = p;
			p->prev = &gmdu_child_p[i - 1];
		}

		p->parent = gmdu;
		p->gmf = gmf;
		ret = gmp_gmf_get_gmdu(gmf, (gm_std_void**)(&p), ret, (len - (ret - src)));

		if (!ret)
		{
			return gmp_std_null;
		}
	}

	return ret;
}

gm_std_uchar* gmp_gmf_get_gmdt(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{

	if (!src || len <= 0)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	switch(*src)
	{
		//���û�����������(0--63)
	case GMP_GMDT_B:
		{
			return gmp_gmf_get_bool(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_C:
		{
			return gmp_gmf_get_char(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_UC:
		{
			return gmp_gmf_get_uchar(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_S:
		{
			return gmp_gmf_get_short(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_US:
		{
			return gmp_gmf_get_ushort(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_IN:
		{
			return gmp_gmf_get_int(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_UIN:
		{
			return gmp_gmf_get_uint(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_L:
		{
			return gmp_gmf_get_long(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_UL:
		{
			return gmp_gmf_get_ulong(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_F:
		{
			return gmp_gmf_get_float(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_UF:
		{
			return gmp_gmf_get_ufloat(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_D:
		{
			return gmp_gmf_get_double(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_UD:
		{
			return gmp_gmf_get_udouble(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_N:
		{
			return gmp_gmf_get_null(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_T:
		{
			return gmp_gmf_get_type(gmf, dest, src, len);
		}
		break;
		//��������(64--127):
	case GMP_GMDT_A:
		{
			return gmp_gmf_get_array(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_O:
		{
			return gmp_gmf_get_object(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_X:
		{
			return gmp_gmf_get_xml(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_JS:
		{
			return gmp_gmf_get_json(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_IOB:
		{
			return gmp_gmf_get_iobuffer(gmf, dest, src, len);
		}
		break;
		//��չ����(128--255):
	case GMP_GMDT_ST:
		{
			return gmp_gmf_get_string(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_R:
		{
			return gmp_gmf_get_rect(gmf, dest, src, len);
		}
		break;
	case GMP_GMDT_RP:
		{
			return gmp_gmf_get_rectpair(gmf, dest, src, len);
		}
		break;
	default:
		{
			gmp_set_gmf_error(gmf, gmf_error_unkown_type, "unknow type[%d].", *src);
			return gmp_std_null;
		}
	}

	return gmp_std_null;
}


//���û������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_bool(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_bool_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uchar))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_bool_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_bool_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_bool_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = src + 1;

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_bool_t);
}

gm_std_uchar* gmp_gmf_get_char(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_char_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_char))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_char_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_char_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_char_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_char *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_char_t);
}

gm_std_uchar* gmp_gmf_get_uchar(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_uchar_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uchar))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_uchar_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uchar_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_uchar_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_uchar *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_uchar_t);
}

gm_std_uchar* gmp_gmf_get_short(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_short_p_t						*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_short))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_short_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_short_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_short_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_short *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_short_t);
}

gm_std_uchar* gmp_gmf_get_ushort(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_ushort_p_t							*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_ushort))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_ushort_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ushort_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_ushort_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_ushort *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_ushort_t);
}

gm_std_uchar* gmp_gmf_get_int(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_int_p_t						*elts;





	if (!src || len - 1 < gmp_std_sizeof(gm_std_int))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_int_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_int_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_int_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_int *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_int_t);
}

gm_std_uchar* gmp_gmf_get_uint(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_uint_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_uint_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uint_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_uint_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_uint *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_uint_t);
}

gm_std_uchar* gmp_gmf_get_long(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_long_p_t					*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_long))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_long_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_long_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_long_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_long *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_long_t);
}

gm_std_uchar* gmp_gmf_get_ulong(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_ulong_p_t						*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_ulong))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_ulong_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ulong_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_ulong_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_ulong *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_ulong_t);
}

gm_std_uchar* gmp_gmf_get_float(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_float_p_t						*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_float))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_float_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_float_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_float_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_float *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_float_t);
}

gm_std_uchar* gmp_gmf_get_ufloat(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_ufloat_p_t							*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_ufloat))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_ufloat_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_ufloat_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_ufloat_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_ufloat *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_ufloat_t);
}

gm_std_uchar* gmp_gmf_get_double(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_double_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_double))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_double_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_double_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_double_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_double *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_double_t);
}

gm_std_uchar* gmp_gmf_get_udouble(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_udouble_p_t					*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_udouble))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_udouble_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_udouble_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_udouble_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_udouble *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_udouble_t);
}

gm_std_uchar* gmp_gmf_get_null(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_null_p_t *elts = (gmdt_null_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_null_p_t));






	if (!src || !elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = gmp_std_null;

	*dest = elts;

	return src + 1;
}

gm_std_uchar* gmp_gmf_get_type(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_uchar_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uchar))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_uchar_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_uchar_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_uchar_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_uchar *)(src + 1);

	if (!gmp_chk_gmdt(*(elts->data)))
	{
		return gmp_std_null;
	}

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_uchar_t);
}



//�����������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_array(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	//gm_std_uint					i = 0;
	//gm_std_uint					last = 0;
	gm_std_uchar				*begin;
	gm_std_uchar				*pos;
	gmdt_array_p_t				*elts;





	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_array_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_array_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_array_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->nelts = (gm_std_uint *)(src + 1);
	elts->elts = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t) * (*(elts->nelts)));
	if (!elts->elts)
	{
		return gmp_std_null;
	}

	gmp_std_memset(elts->elts, 0, gmp_std_sizeof(gmp_gmdu_t) * (*(elts->nelts)));

	begin = src + 5;
	//last = len - 5;
	pos = begin;
	*dest = elts;

	//for (i = 0; i < *(elts->nelts); i++)
	//{
	//	pos = gmp_gmf_get_gmdu(&(elts->elts[0].key), pos, (last - (pos - begin)));

	//	if (!pos)
	//	{
	//		return gmp_std_null;
	//	}
	//}

	return pos;
}

gm_std_uchar* gmp_gmf_get_object(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	//gm_std_uint					i = 0;
	//gm_std_uint					last = 0;
	gm_std_uchar				*begin;
	gm_std_uchar				*pos;
	gmdt_object_p_t				*elts;





	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_object_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_object_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_object_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->nelts = (gm_std_uint *)(src + 1);
	elts->elts = (gmp_gmdu_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmp_gmdu_t) * (*(elts->nelts)));
	if (!elts->elts)
	{
		return gmp_std_null;
	}

	gmp_std_memset(elts->elts, 0, gmp_std_sizeof(gmp_gmdu_t) * (*(elts->nelts)));

	begin = src + 5;
	//last = len - 5;
	pos = begin;
	*dest = elts;

	//for (i = 0; i < *(elts->nelts); i++)
	//{
	//	pos = gmp_gmf_get_gmdu(&(elts->elts[0].key), pos, (last - (pos - begin)));

	//	if (!pos)
	//	{
	//		return gmp_std_null;
	//	}
	//}

	return pos;
}

gm_std_uchar* gmp_gmf_get_xml(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_xml_p_t					*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_xml_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_xml_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_xml_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));

		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_char *)(src + 5);

	if (*(elts->len) > (len - gmp_std_sizeof(gm_std_uint) - 1))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d] len[%d] error.", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len), *(elts->len));
		return gmp_std_null;
	}

	*dest = elts;

	return (gm_std_uchar*)(elts->data + *(elts->len));
}

gm_std_uchar* gmp_gmf_get_json(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_json_p_t					*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_json_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_json_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_json_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_char *)(src + 5);

	if (*(elts->len) > (len - gmp_std_sizeof(gm_std_uint) - 1))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d] len[%d] error.", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len), *(elts->len));
		return gmp_std_null;
	}

	*dest = elts;

	return (gm_std_uchar*)(elts->data + *(elts->len));
}

gm_std_uchar* gmp_gmf_get_iobuffer(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_iobuffer_p_t				*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_iobuffer_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_iobuffer_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_iobuffer_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_uchar *)(src + 5);

	if (*(elts->len) > (len - gmp_std_sizeof(gm_std_uint) - 1))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d] len[%d] error.", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len), *(elts->len));
		return gmp_std_null;
	}

	*dest = elts;

	return (elts->data + *(elts->len));
}



//��չ�������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_string(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_string_p_t					*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_string_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_string_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_string_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_char *)(src + 5);

	if (*(elts->len) > (len - gmp_std_sizeof(gm_std_uint) - 1))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d] len[%d] error.", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len), *(elts->len));
		return gmp_std_null;
	}

	*dest = elts;

	return (gm_std_uchar*)(elts->data + *(elts->len));
}

gm_std_uchar* gmp_gmf_get_rect(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_rect_p_t					*elts;






	if (!src || len < gmp_std_sizeof(gmdt_rect_t))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_rect_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_rect_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]", 
			gmp_std_sizeof(gmdt_rect_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->x1 = (gm_std_uint *)(src + 1);
	elts->y1 = (gm_std_uint *)(src + 5);
	elts->x2 = (gm_std_uint *)(src + 9);
	elts->y2 = (gm_std_uint *)(src + 13);

	*dest = elts;

	return (src + gmp_std_sizeof(gmdt_rect_t));
}

gm_std_uchar* gmp_gmf_get_rectpair(gmp_gmf_t *gmf, gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_rectpair_p_t					*elts;






	if (!src || len < gmp_std_sizeof(gmdt_rectpair_t))
	{
		gmp_set_gmf_error(gmf, gmf_error_format, "body format error. pos[%d]", 
			(gmf->gmfh.size + gmp_std_sizeof(gmp_gmf_gmfh_t) - len));
		return gmp_std_null;
	}

	elts = (gmdt_rectpair_p_t *)gmp_palloc((gmf->pool), gmp_std_sizeof(gmdt_rectpair_p_t));
	if (!elts)
	{
		gmp_set_gmf_error(gmf, gmf_error_alloc_memory, "alloc memory error. len[%d] [%d:%s]",
			gmp_std_sizeof(gmdt_rectpair_p_t), gmp_sys_errno, gmp_sys_strerror(gmp_sys_errno));
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->x1 = (gm_std_uint *)(src + 1);
	elts->y1 = (gm_std_uint *)(src + 5);
	elts->x2 = (gm_std_uint *)(src + 9);
	elts->y2 = (gm_std_uint *)(src + 13);
	elts->x3 = (gm_std_uint *)(src + 17);
	elts->y3 = (gm_std_uint *)(src + 21);
	elts->x4 = (gm_std_uint *)(src + 25);
	elts->y4 = (gm_std_uint *)(src + 29);

	*dest = elts;

	return (src + gmp_std_sizeof(gmdt_rectpair_t));
}


#else  //defined(GMP_USED_POOL)
/////////////////////////////////////////////////////////////////////////////////////////
//��ȡgmfh
gmp_gmdt_bool gmp_gmf_get_gmfh(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);
//У��gmfh
gmp_gmdt_bool gmp_gmf_check_gmfh(gmp_gmf_t *gmf);
//����gmf�ַ�����
gmp_gmdt_bool gmp_gmf_parse(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);
//����Ԫ�ؼ�ֵ��
gm_std_uchar* gmp_gmf_get_gmdu(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//�����ӽڵ�Ԫ�ؼ�ֵ��
gm_std_uchar* gmp_gmf_get_child_gmdu(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//��������Ԫ������
gm_std_uchar* gmp_gmf_get_gmdt(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//���û������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_bool(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_char(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_uchar(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_short(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_ushort(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_int(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_uint(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_long(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_ulong(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_float(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_ufloat(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_double(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_udouble(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_null(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_type(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//�����������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_array(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_object(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_xml(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_json(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_iobuffer(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
//��չ�������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_string(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);
gm_std_uchar* gmp_gmf_get_rect(gm_std_void **dest, gm_std_uchar *src, gm_std_int len);




////////////////////////////////////////////////////////////////////////////////////////////
//����gmf
gmp_gmf_t *gmp_create_gmf()
{
	gmp_gmf_t					*gmf_p;




	gmf_p = (gmp_gmf_t *)gmp_std_malloc(gmp_std_sizeof(gmp_gmf_t));
	if (!gmf_p)
	{
		return NULL;
	}

	return gmf_p;
}

//����gmf
void gmp_destroy_gmf(gmp_gmf_t *gmf)
{

}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_decode
* ��    ��:
*			����gmf��ʽ������
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*src		��ʾ��Ҫ������gmf����
*			3��gm_std_uint			len			��ʾgmf���ݵĳ���
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			�ú�����gmf��������ں���
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_decode(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len)
{
	gmp_gmf_gmfh_t			*gmfh_p;





	gmp_std_memset(gmf, 0, gmp_std_sizeof(gmp_gmf_t));
	//��ȡgmfhͷ��Ϣ
	if (!gmp_gmf_get_gmfh(gmf, src, len))
	{
		return gmp_gmdt_false;
	}

	//У��gmfh�Ƿ�׼ȷ
	if (!gmp_gmf_check_gmfh(gmf))
	{
		return gmp_gmdt_false;
	}

	gmfh_p = &(gmf->gmfh);

	switch (gmfh_p->size)
	{
	case 0:
		{
			gmf->gmdu->key = gmp_std_null;
		}
		break;
	case 1:
		{
			return gmp_gmf_parse(gmf, src + gmp_std_sizeof(gmp_gmf_gmfh_t), len - gmp_std_sizeof(gmp_gmf_gmfh_t));
		}
		break;
	default:
		{
			if (gmfh_p->size > len - gmp_std_sizeof(gmp_gmf_gmfh_t))
			{
				//������ݳ��Ȳ������򷵻ش���
				return gmp_gmdt_false;
			}
			else
			{
				return gmp_gmf_parse(gmf, src + gmp_std_sizeof(gmp_gmf_gmfh_t), len - gmp_std_sizeof(gmp_gmf_gmfh_t));
			}
		}
		break;
	}
	return gmp_gmdt_false;
}



/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_get_gmfh
* ��    ��:
*			��ȡgmfh��������
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*src		��ʾ��Ҫ������gmf����
*			3��gm_std_uint			len			��ʾgmf���ݵĳ���
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_get_gmfh(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len)
{
	if (len < gmp_std_sizeof(gmp_gmf_gmfh_t))
	{
		//src length error
		return gmp_gmdt_false;
	}

	gmp_std_memcpy(&(gmf->gmfh), src, gmp_std_sizeof(gmp_gmf_gmfh_t));

	return gmp_gmdt_true;
}


/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_check_gmfh
* ��    ��:
*			У��gmfh�������ݣ���֤��Ϣ��׼ȷ��
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_check_gmfh(gmp_gmf_t *gmf)
{
	if (gmp_std_strncmp(gmf->gmfh.gmff, GMP_GMF_GMFF, 4))
	{
		return gmp_gmdt_false;
	}

	return gmp_gmdt_true;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_check_gmfh
* ��    ��:
*			����gmf��ʽ���ݵ�����
* ��    ��:
*			1��gmp_gmf_t			*gmf		��ʾgmf�ṹ������ָ�룬�ǽ�������ķ���ֵ
*			2��gm_std_uchar			*src		��ʾgmf���ݵ���ʼλ��
*			3��gm_std_uint			len			��ʾgmf���ݵĳ���
* �� �� ֵ:
*			���سɹ������Ϣ
*			1��gmp_gmdt_false					��ʾʧ��
*			1��gmp_gmdt_true					��ʾ�ɹ�
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gmp_gmdt_bool gmp_gmf_parse(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len)
{
	if (!src || len <= 0)
	{
		return gmp_gmdt_false;
	}

	if (!gmp_chk_gmdt(*src))
	{
		return gmp_gmdt_false;
	}

	gmf->gmdu = (gmp_gmdu_t *)gmp_std_malloc(gmp_std_sizeof(gmp_gmdu_t));
	if (!gmf->gmdu)
	{
		return gmp_gmdt_false;
	}

	gmf->gmdu->parent = NULL;
	if (!gmp_gmf_get_gmdu((gm_std_void **)(&(gmf->gmdu)), src, len))
	{
		return gmp_gmdt_false;
	}

	return gmp_gmdt_true;
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_get_gmdu
* ��    ��:
*			����������ֵ������
* ��    ��:
*			1��gm_std_void			**dest		��ʾ�����������λ��
*			2��gm_std_uchar			*src		��ʾԪ�����ݵ����λ��
*			3��gm_std_uint			len			��ʾԪ�����ݵĳ���
* �� �� ֵ:
*			������һ�����ݵ���ʼλ��
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gm_std_uchar* gmp_gmf_get_gmdu(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmp_gmdu_t						*gmdu_p = (gmp_gmdu_t*)*dest;
	gm_std_uint						last = 0;
	gm_std_uchar					*ret;





	if (!src || len <= 0)
	{
		return gmp_std_null;
	}

	ret = gmp_gmf_get_gmdt(&(gmdu_p->key), src, len);
	if (!ret)
	{
		return gmp_std_null;
	}

	ret = gmp_gmf_get_gmdt(&(gmdu_p->val), ret, (len - (ret - src)));
	if (!ret)
	{
		return gmp_std_null;
	}

	if (!gmp_is_have_child(gmdu_p))
	{
		return ret;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu_p->key))))
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_gmf_get_child_gmdu(&(gmdu_p->key), ret, (len - (ret - src)));
		}
		else
		{
			//��ȡ�ӽڵ�Ԫ��
			return gmp_gmf_get_child_gmdu(&(gmdu_p->val), ret, (len - (ret - src)));
		}
	}
}

/******************************************************************************************************
* ��Ȩ����:fz & novigo
* ��������:gmp_gmf_get_child_gmdu
* ��    ��:
*			����������ֵ������
* ��    ��:
*			1��gm_std_void			**dest		��ʾ�����������λ��
*			2��gm_std_uchar			*src		��ʾԪ�����ݵ����λ��
*			3��gm_std_uint			len			��ʾԪ�����ݵĳ���
* �� �� ֵ:
*			������һ�����ݵ���ʼλ��
* ��    ע:
*			��
* ��    ��:fz
* ��������:fangzhenmu@novigo.com.cn
* ��������:2013-12-25 15:23
******************************************************************************************************/
gm_std_uchar* gmp_gmf_get_child_gmdu(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gm_std_uint						i = 0;
	gm_std_uint						num = 0;
	gm_std_uchar					*ret = src;
	gmp_gmdu_t						*p;
	gmp_gmdu_t						*gmdu_child_p;





	if (!src || len <= 0)
	{
		return gmp_std_null;
	}

	switch((unsigned char)(*(gmp_get_p_type((*dest)))))
	{
	case GMP_GMDT_A:
		{
			gmdt_array_p_t *ary = (gmdt_array_p_t *)(*dest);
			num = *(ary->nelts);

			p = (gmp_gmdu_t *)gmp_std_malloc(gmp_std_sizeof(gmp_gmdu_t) * num);
			if (!p)
			{
				return gmp_std_null;
			}

			gmp_std_memset(p, 0, gmp_std_sizeof(gmp_gmdu_t) * num);
			ary->elts = p;
			gmdu_child_p = p;
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t *obj = (gmdt_object_p_t *)(*dest);
			num = *(obj->nelts);

			p = (gmp_gmdu_t *)gmp_std_malloc(gmp_std_sizeof(gmp_gmdu_t) * num);
			if (!p)
			{
				return gmp_std_null;
			}

			gmp_std_memset(p, 0, gmp_std_sizeof(gmp_gmdu_t) * num);
			obj->elts = p;
			gmdu_child_p = p;
		}
		break;
	default:
		{
			return gmp_std_null;
		}
		break;
	}

	for (i = 0; i < num; i++)
	{
		p = &gmdu_child_p[i];
		p->prev = (*dest);
		ret = gmp_gmf_get_gmdu((gm_std_void**)(&p), ret, (len - (ret - src)));

		if (!ret)
		{
			return gmp_std_null;
		}
	}

	return ret;
}

gm_std_uchar* gmp_gmf_get_gmdt(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{

	if (!src || len <= 0)
	{
		return gmp_std_null;
	}

	switch(*src)
	{
		//���û�����������(0--63)
	case GMP_GMDT_B:
		{
			return gmp_gmf_get_bool(dest, src, len);
		}
		break;
	case GMP_GMDT_C:
		{
			return gmp_gmf_get_char(dest, src, len);
		}
		break;
	case GMP_GMDT_UC:
		{
			return gmp_gmf_get_uchar(dest, src, len);
		}
		break;
	case GMP_GMDT_S:
		{
			return gmp_gmf_get_short(dest, src, len);
		}
		break;
	case GMP_GMDT_US:
		{
			return gmp_gmf_get_ushort(dest, src, len);
		}
		break;
	case GMP_GMDT_IN:
		{
			return gmp_gmf_get_int(dest, src, len);
		}
		break;
	case GMP_GMDT_UIN:
		{
			return gmp_gmf_get_uint(dest, src, len);
		}
		break;
	case GMP_GMDT_L:
		{
			return gmp_gmf_get_long(dest, src, len);
		}
		break;
	case GMP_GMDT_UL:
		{
			return gmp_gmf_get_ulong(dest, src, len);
		}
		break;
	case GMP_GMDT_F:
		{
			return gmp_gmf_get_float(dest, src, len);
		}
		break;
	case GMP_GMDT_UF:
		{
			return gmp_gmf_get_ufloat(dest, src, len);
		}
		break;
	case GMP_GMDT_D:
		{
			return gmp_gmf_get_double(dest, src, len);
		}
		break;
	case GMP_GMDT_UD:
		{
			return gmp_gmf_get_udouble(dest, src, len);
		}
		break;
	case GMP_GMDT_N:
		{
			return gmp_gmf_get_null(dest, src, len);
		}
		break;
	case GMP_GMDT_T:
		{
			return gmp_gmf_get_type(dest, src, len);
		}
		break;
		//��������(64--127):
	case GMP_GMDT_A:
		{
			return gmp_gmf_get_array(dest, src, len);
		}
		break;
	case GMP_GMDT_O:
		{
			return gmp_gmf_get_object(dest, src, len);
		}
		break;
	case GMP_GMDT_X:
		{
			return gmp_gmf_get_xml(dest, src, len);
		}
		break;
	case GMP_GMDT_JS:
		{
			return gmp_gmf_get_json(dest, src, len);
		}
		break;
	case GMP_GMDT_IOB:
		{
			return gmp_gmf_get_iobuffer(dest, src, len);
		}
		break;
		//��չ����(128--255):
	case GMP_GMDT_ST:
		{
			return gmp_gmf_get_string(dest, src, len);
		}
		break;
	case GMP_GMDT_R:
		{
			return gmp_gmf_get_rect(dest, src, len);
		}
		break;
	default:
		{
			return gmp_std_null;
		}
	}

	return gmp_std_null;
}


//���û������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_bool(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_bool_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uchar))
	{
		return gmp_std_null;
	}

	elts = (gmdt_bool_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_bool_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = src + 1;

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_bool_t);
}

gm_std_uchar* gmp_gmf_get_char(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_char_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_char))
	{
		return gmp_std_null;
	}

	elts = (gmdt_char_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_char_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_char *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_char_t);
}

gm_std_uchar* gmp_gmf_get_uchar(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_uchar_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uchar))
	{
		return gmp_std_null;
	}

	elts = (gmdt_uchar_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_uchar_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_uchar *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_uchar_t);
}

gm_std_uchar* gmp_gmf_get_short(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_short_p_t						*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_short))
	{
		return gmp_std_null;
	}

	elts = (gmdt_short_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_short_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_short *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_short_t);
}

gm_std_uchar* gmp_gmf_get_ushort(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_ushort_p_t							*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_ushort))
	{
		return gmp_std_null;
	}

	elts = (gmdt_ushort_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_ushort_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_ushort *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_ushort_t);
}

gm_std_uchar* gmp_gmf_get_int(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_int_p_t						*elts;





	if (!src || len - 1 < gmp_std_sizeof(gm_std_int))
	{
		return gmp_std_null;
	}

	elts = (gmdt_int_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_int_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_int *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_int_t);
}

gm_std_uchar* gmp_gmf_get_uint(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_uint_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_uint_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_uint_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_uint *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_uint_t);
}

gm_std_uchar* gmp_gmf_get_long(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_long_p_t					*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_long))
	{
		return gmp_std_null;
	}

	elts = (gmdt_long_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_long_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_long *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_long_t);
}

gm_std_uchar* gmp_gmf_get_ulong(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_ulong_p_t						*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_ulong))
	{
		return gmp_std_null;
	}

	elts = (gmdt_ulong_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_ulong_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_ulong *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_ulong_t);
}

gm_std_uchar* gmp_gmf_get_float(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_float_p_t						*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_float))
	{
		return gmp_std_null;
	}

	elts = (gmdt_float_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_float_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_float *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_float_t);
}

gm_std_uchar* gmp_gmf_get_ufloat(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_ufloat_p_t							*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_ufloat))
	{
		return gmp_std_null;
	}

	elts = (gmdt_ufloat_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_ufloat_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_ufloat *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_ufloat_t);
}

gm_std_uchar* gmp_gmf_get_double(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_double_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_double))
	{
		return gmp_std_null;
	}

	elts = (gmdt_double_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_double_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_double *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_double_t);
}

gm_std_uchar* gmp_gmf_get_udouble(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_udouble_p_t					*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_udouble))
	{
		return gmp_std_null;
	}

	elts = (gmdt_udouble_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_udouble_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_udouble *)(src + 1);

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_udouble_t);
}

gm_std_uchar* gmp_gmf_get_null(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_null_p_t *elts = (gmdt_null_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_null_p_t));







	if (!src || !elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = gmp_std_null;

	*dest = elts;

	return src + 1;
}

gm_std_uchar* gmp_gmf_get_type(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_uchar_p_t						*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uchar))
	{
		return gmp_std_null;
	}

	elts = (gmdt_uchar_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_uchar_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->data = (gm_std_uchar *)(src + 1);

	if (!gmp_chk_gmdt(*(elts->data)))
	{
		return gmp_std_null;
	}

	*dest = elts;

	return src + gmp_std_sizeof(gmdt_uchar_t);
}



//�����������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_array(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	//gm_std_uint					i = 0;
	//gm_std_uint					last = 0;
	gm_std_uchar				*begin;
	gm_std_uchar				*pos;
	gmdt_array_p_t				*elts;





	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_array_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_array_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->nelts = (gm_std_uint *)(src + 1);
	elts->elts = (gmp_gmdu_t *)gmp_std_malloc(gmp_std_sizeof(gmp_gmdu_t) * (*(elts->nelts)));
	if (!elts->elts)
	{
		return gmp_std_null;
	}

	begin = src + 5;
	//last = len - 5;
	pos = begin;
	*dest = elts;

	//for (i = 0; i < *(elts->nelts); i++)
	//{
	//	pos = gmp_gmf_get_gmdu(&(elts->elts[0].key), pos, (last - (pos - begin)));

	//	if (!pos)
	//	{
	//		return gmp_std_null;
	//	}
	//}

	return pos;
}

gm_std_uchar* gmp_gmf_get_object(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	//gm_std_uint					i = 0;
	//gm_std_uint					last = 0;
	gm_std_uchar				*begin;
	gm_std_uchar				*pos;
	gmdt_object_p_t				*elts;





	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_object_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_object_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->nelts = (gm_std_uint *)(src + 1);
	elts->elts = (gmp_gmdu_t *)gmp_std_malloc(gmp_std_sizeof(gmp_gmdu_t) * (*(elts->nelts)));
	if (!elts->elts)
	{
		return gmp_std_null;
	}

	begin = src + 5;
	//last = len - 5;
	pos = begin;
	*dest = elts;

	//for (i = 0; i < *(elts->nelts); i++)
	//{
	//	pos = gmp_gmf_get_gmdu(&(elts->elts[0].key), pos, (last - (pos - begin)));

	//	if (!pos)
	//	{
	//		return gmp_std_null;
	//	}
	//}

	return pos;
}

gm_std_uchar* gmp_gmf_get_xml(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_xml_p_t					*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_xml_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_xml_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_char *)(src + 5);

	*dest = elts;

	return (gm_std_uchar*)(elts->data + *(elts->len));
}

gm_std_uchar* gmp_gmf_get_json(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_json_p_t					*elts;






	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_json_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_json_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_char *)(src + 5);

	*dest = elts;

	return (gm_std_uchar*)(elts->data + *(elts->len));
}

gm_std_uchar* gmp_gmf_get_iobuffer(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_iobuffer_p_t				*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_iobuffer_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_iobuffer_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_uchar *)(src + 5);

	*dest = elts;

	return (elts->data + *(elts->len));
}



//��չ�������ݵĻ�ȡ
gm_std_uchar* gmp_gmf_get_string(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_string_p_t					*elts;







	if (!src || len - 1 < gmp_std_sizeof(gm_std_uint))
	{
		return gmp_std_null;
	}

	elts = (gmdt_string_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_string_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->len = (gm_std_uint *)(src + 1);
	elts->data = (gm_std_char *)(src + 5);

	*dest = elts;

	return (gm_std_uchar*)(elts->data + *(elts->len));
}

gm_std_uchar* gmp_gmf_get_rect(gm_std_void **dest, gm_std_uchar *src, gm_std_int len)
{
	gmdt_rect_p_t					*elts;






	if (!src || len < gmp_std_sizeof(gmdt_rect_t))
	{
		return gmp_std_null;
	}

	elts = (gmdt_rect_p_t *)gmp_std_malloc(gmp_std_sizeof(gmdt_rect_p_t));
	if (!elts)
	{
		return gmp_std_null;
	}

	elts->gmdt = src;
	elts->x1 = (gm_std_uint *)(src + 1);
	elts->y1 = (gm_std_uint *)(src + 5);
	elts->x2 = (gm_std_uint *)(src + 9);
	elts->y2 = (gm_std_uint *)(src + 13);

	*dest = elts;

	return (src + gmp_std_sizeof(gmdt_rect_t));
}


#endif	//defined(GMP_USED_POOL)















