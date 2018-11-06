
#include "prot_gmp_print.h"






#define				GMP_PRINT_MAX_LAYER								64





#if defined(CSS_GMP_PRINT_TO_LOG)

gmp_print_string	*gmp_gmf_print_gmfh(gmp_gmf_t *gmf, gmp_pool_t *pool, gmp_print_string *prev, gmp_print_style sty);
gmp_print_string	*gmp_gmf_print_gmdu(gmp_gmdu_t *gmdu, gmp_pool_t *pool, gmp_print_string *prev, gmp_print_style sty, gm_std_int layer);
gmp_print_string	*gmp_gmf_print_child_gmdu(gmp_pool_t *pool, gm_std_void *dest, gmp_print_string *prev, gmp_print_style sty, gm_std_int layer);
gmp_print_string	*gmp_gmf_print_gmdt(gmp_pool_t *pool, gm_std_void *dest, gmp_print_string *prev, gmp_print_style sty, gm_std_int layer);

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
gmp_gmdt_bool gmp_gmf_print_rectpair(gm_std_void *dest, gm_std_int layer);



gmp_print_string* gmp_gmf_print_tab(gmp_pool_t *pool, gmp_print_string *prev, gm_std_int layer);
gmp_print_string* gmp_gmf_print_stirng_copy(gmp_pool_t *pool, gmp_print_string *prev, char* src, int len);
gmp_print_string* gmp_gmf_create_print_stirng(gmp_pool_t *pool, gm_std_int len);

#endif









#if defined(CSS_GMP_PRINT_TO_LOG)
gmp_gmdt_bool gmp_gmf_printf(gmp_gmf_t *gmf, gmdt_string_p_t **gmdt_str, gm_std_char *dest, gm_std_uint len, gmp_print_style sty)
{
	gmp_print_string					*dest_gmp_str;
	gmp_print_string					*tmp_gmp_str;
	gmdt_string_t						*str;
	gm_std_char							*buf;
	gmp_pool_t							*pool;
	gm_std_uint							total_len = 0;
	gm_std_uint							buf_len = 0;





	pool = gmp_create_pool(GMP_POOL_BUFFER_SIZE);
	if (!pool)
	{
		return gmp_gmdt_false;
	}

	dest_gmp_str = gmp_gmf_create_print_stirng(pool, 1);
	if (!dest_gmp_str)
	{
		gmp_destroy_pool(pool);
		return gmp_gmdt_false;
	}

	tmp_gmp_str = dest_gmp_str;
	tmp_gmp_str = gmp_gmf_print_gmfh(gmf, pool, tmp_gmp_str, sty);
	if (!tmp_gmp_str)
	{
		gmp_destroy_pool(pool);
		return gmp_gmdt_false;
	}

	tmp_gmp_str = gmp_gmf_print_stirng_copy(pool, tmp_gmp_str, "gmfb|", gmp_std_strlen("gmfb|"));

	tmp_gmp_str = gmp_gmf_print_gmdu(gmf->gmdu, pool, tmp_gmp_str, sty, 0);

	tmp_gmp_str = gmp_gmf_print_stirng_copy(pool, tmp_gmp_str, " |", gmp_std_strlen(" |"));

	//计算总长度
	for (tmp_gmp_str = dest_gmp_str, total_len = 0; tmp_gmp_str; tmp_gmp_str = tmp_gmp_str->next)
	{
		total_len += (tmp_gmp_str->last - tmp_gmp_str->pos);
	}

	if (gmdt_str)
	{
		*gmdt_str = (gmdt_string_p_t *)gmp_palloc(gmf->pool, gmp_std_sizeof(gmdt_string_p_t));
		str = (gmdt_string_t *)gmp_palloc(gmf->pool, gmp_std_sizeof(gmdt_string_t));
		if (!*gmdt_str || !str)
		{
			gmp_destroy_pool(pool);
			return gmp_gmdt_false;
		}

		buf = (gm_std_char *)gmp_palloc(gmf->pool, total_len + 1);
		if (!buf)
		{
			gmp_destroy_pool(pool);
			return gmp_gmdt_false;
		}

		str->gmdt = GMP_GMDT_ST;
		str->len = total_len;
		str->data = buf;

		(*gmdt_str)->gmdt = &(str->gmdt);
		(*gmdt_str)->len = &(str->len);
		(*gmdt_str)->data = str->data;

		buf_len = total_len;
	}
	else
	{
		if (!dest || len < total_len)
		{
			gmp_destroy_pool(pool);
			return gmp_gmdt_false;
		}

		buf = dest;
		buf_len = len;
	}

	//把数据拷贝到缓存中
	for (tmp_gmp_str = dest_gmp_str; tmp_gmp_str; tmp_gmp_str = tmp_gmp_str->next)
	{
		gmp_std_strncpy(buf, tmp_gmp_str->pos, (tmp_gmp_str->last - tmp_gmp_str->pos));
		buf += (tmp_gmp_str->last - tmp_gmp_str->pos);
	}

	*buf = 0;
	gmp_destroy_pool(pool);

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_current_gmdu(gmp_gmf_t *gmf, gmdt_string_p_t **gmdt_str, gm_std_char *dest, gm_std_uint len, gmp_print_style sty)
{
	return gmp_gmf_print_this_gmdu(gmf, gmf->current_gmdu, gmdt_str, dest, len, sty);
}

gmp_gmdt_bool gmp_gmf_print_this_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmdt_string_p_t **gmdt_str, gm_std_char *dest, gm_std_uint len, gmp_print_style sty)
{
	gmp_print_string					*dest_gmp_str;
	gmp_print_string					*tmp_gmp_str;
	gmdt_string_t						*str;
	gm_std_char							*buf;
	gmp_pool_t							*pool;
	gm_std_uint							total_len = 0;
	gm_std_uint							buf_len = 0;





	pool = gmp_create_pool(GMP_POOL_BUFFER_SIZE);
	if (!pool)
	{
		return gmp_gmdt_false;
	}

	if (!gmf || !gmdu || !gmdt_str)
	{
		gmp_destroy_pool(pool);
		return gmp_gmdt_false;
	}

	dest_gmp_str = gmp_gmf_create_print_stirng(pool, 1);
	if (!dest_gmp_str)
	{
		gmp_destroy_pool(pool);
		return gmp_gmdt_false;
	}

	tmp_gmp_str = dest_gmp_str;

	tmp_gmp_str = gmp_gmf_print_stirng_copy(pool, tmp_gmp_str, "gmfb|", gmp_std_strlen("gmfb|"));

	tmp_gmp_str = gmp_gmf_print_gmdu(gmdu, pool, tmp_gmp_str, sty, 2);

	tmp_gmp_str = gmp_gmf_print_stirng_copy(pool, tmp_gmp_str, " |", gmp_std_strlen(" |"));

	//计算总长度
	for (tmp_gmp_str = dest_gmp_str, total_len = 0; tmp_gmp_str; tmp_gmp_str = tmp_gmp_str->next)
	{
		total_len += (tmp_gmp_str->last - tmp_gmp_str->pos);
	}

	if (gmdt_str)
	{
		*gmdt_str = (gmdt_string_p_t *)gmp_palloc(gmf->pool, gmp_std_sizeof(gmdt_string_p_t));
		str = (gmdt_string_t *)gmp_palloc(gmf->pool, gmp_std_sizeof(gmdt_string_t));
		if (!*gmdt_str || !str)
		{
			gmp_destroy_pool(pool);
			return gmp_gmdt_false;
		}

		buf = (gm_std_char *)gmp_palloc(gmf->pool, total_len + 1);
		if (!buf)
		{
			gmp_destroy_pool(pool);
			return gmp_gmdt_false;
		}

		str->gmdt = GMP_GMDT_ST;
		str->len = total_len;
		str->data = buf;

		(*gmdt_str)->gmdt = &(str->gmdt);
		(*gmdt_str)->len = &(str->len);
		(*gmdt_str)->data = str->data;

		buf_len = total_len;
	}
	else
	{
		if (!dest || len < total_len)
		{
			gmp_destroy_pool(pool);
			return gmp_gmdt_false;
		}

		buf = dest;
		buf_len = len;
	}

	//把数据拷贝到缓存中
	for (tmp_gmp_str = dest_gmp_str; tmp_gmp_str; tmp_gmp_str = tmp_gmp_str->next)
	{
		gmp_std_strncpy(buf, tmp_gmp_str->pos, (tmp_gmp_str->last - tmp_gmp_str->pos));
		buf += (tmp_gmp_str->last - tmp_gmp_str->pos);
	}
	*buf = 0;

	gmp_destroy_pool(pool);
	return gmp_gmdt_true;
}

gmp_print_string *gmp_gmf_print_gmfh(gmp_gmf_t *gmf, gmp_pool_t *pool, gmp_print_string *prev, gmp_print_style sty)
{
	gm_std_char						buf[CSS_PRINT_STRING_MAX_LEN] = {0,};
	gm_std_char						tmp_buf[CSS_PRINT_STRING_MAX_LEN] = {0,};




	switch(sty)
	{
	case gmp_print_style_null:
		{
			gmp_std_memcpy(buf, gmf->gmfh.gmff, gmp_std_sizeof(gmf->gmfh.gmff));
			gmp_std_sprintf(tmp_buf, "gmfh|%s 0x%02X 0x%02X 0x%02X %d| ", buf, gmf->gmfh.version, gmf->gmfh.endian, gmf->gmfh.encode, gmf->gmfh.size);
		}
		break;
	case gmp_print_style_pretty:
		{
			gmp_std_memcpy(buf, gmf->gmfh.gmff, gmp_std_sizeof(gmf->gmfh.gmff));
			gmp_std_sprintf(tmp_buf, "gmfh|%s 0x%02X 0x%02X 0x%02X %d|\r\n", buf, gmf->gmfh.version, gmf->gmfh.endian, gmf->gmfh.encode, gmf->gmfh.size);
		}
		break;
	}

	return gmp_gmf_print_stirng_copy(pool, prev, tmp_buf, gmp_std_strlen(tmp_buf));
}

gmp_print_string *gmp_gmf_print_gmdu(gmp_gmdu_t *gmdu, gmp_pool_t *pool, gmp_print_string *prev, gmp_print_style sty, gm_std_int layer)
{
	gm_std_char							buf[CSS_PRINT_STRING_MAX_LEN] = {0,};
	gmp_print_string					*gmp_str = prev;







	if (layer > GMP_PRINT_MAX_LAYER)
	{
		//这里定义了一个最大层限制，避免递归错误
		return gmp_str;
	}

	if (gmp_print_style_pretty == sty)
	{
		gmp_str = gmp_gmf_print_tab(pool, gmp_str, layer);
	}

	if (!gmdu)
	{
		return gmp_gmf_print_stirng_copy(pool, gmp_str, "<gmdu null error>", gmp_std_strlen("<gmdu null error>"));
	}

	if (gmdu->key)
	{
		gmp_str = gmp_gmf_print_gmdt(pool, gmdu->key, gmp_str, sty, layer);
	}
	else
	{
		return gmp_gmf_print_stirng_copy(pool, gmp_str, "<key null error>", gmp_std_strlen("<key null error>"));
	}

	gmp_str = gmp_gmf_print_stirng_copy(pool, gmp_str, " : ", gmp_std_strlen(" : "));

	if (gmdu->val)
	{
		gmp_str = gmp_gmf_print_gmdt(pool, gmdu->val, gmp_str, sty, layer);
	}
	else
	{
		return gmp_gmf_print_stirng_copy(pool, gmp_str, "<value null error>", gmp_std_strlen("<value null error>"));
	}

	if (gmp_print_style_pretty == sty)
	{
#if defined(WIN32)
		gmp_str = gmp_gmf_print_stirng_copy(pool, gmp_str, "\r\n", gmp_std_strlen("\r\n"));
#else
		gmp_str = gmp_gmf_print_stirng_copy(pool, gmp_str, "\n", gmp_std_strlen("\n"));
#endif
	}

	if (!gmdu->key || !gmdu->val)
	{
		return gmp_str;
	}

	if (!gmp_is_have_child(gmdu))
	{
		return gmp_str;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu->key))))
		{
			//获取子节点元素
			return gmp_gmf_print_child_gmdu(pool, gmdu->key, gmp_str, sty, layer);
		}
		else
		{
			//获取子节点元素
			return gmp_gmf_print_child_gmdu(pool, gmdu->val, gmp_str, sty, layer);
		}
	}
	return gmp_str;
}

gmp_print_string *gmp_gmf_print_child_gmdu(gmp_pool_t *pool, gm_std_void *dest, gmp_print_string *prev, gmp_print_style sty, gm_std_int layer)
{
	gmdt_array_p_t						*p;
	gmp_gmdu_t							*gmdu;
	gmp_print_string					*gmp_str = prev;




	if (!dest)
	{
		return gmp_str;
	}

	p = (gmdt_array_p_t*)dest;

	if (*(p->nelts) <= 0)
	{
		return gmp_str;
	}

	gmdu = p->elts;

	for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
	{
		gmp_str = gmp_gmf_print_gmdu(gmdu, pool, gmp_str, sty, layer + 1);
	}

	return gmp_str;
}

gmp_print_string *gmp_gmf_print_gmdt(gmp_pool_t *pool, gm_std_void *dest, gmp_print_string *prev, gmp_print_style sty, gm_std_int layer)
{
	gm_std_char						buf[CSS_PRINT_STRING_MAX_LEN] = {0,};





	if (!dest)
	{
		return NULL;
	}

	switch(*gmp_get_p_type(dest))
	{
		//常用基础数据类型(0--63)
	case GMP_GMDT_B:
		{
			gmdt_bool_p_t			*p;

			p = (gmdt_bool_p_t*)dest;

			//gmp_std_sprintf(buf, "(bool 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(B 0x%02X) [0x%02X]%s", *(p->gmdt), *(p->data), *(p->data) > 0 ? "true" : "false");
			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_C:
		{
			gmdt_char_p_t			*p;


			p = (gmdt_char_p_t*)dest;
			//gmp_std_sprintf(buf, "(char 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(C 0x%02X) 0x%02X", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_UC:
		{
			gmdt_uchar_p_t			*p;


			p = (gmdt_uchar_p_t*)dest;
			//gmp_std_sprintf(buf, "(uchar 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(UC 0x%02X) 0x%02X", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_S:
		{
			gmdt_short_p_t			*p;


			p = (gmdt_short_p_t*)dest;
			//gmp_std_sprintf(buf, "(short 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(S 0x%02X) %d", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_US:
		{
			gmdt_ushort_p_t			*p;


			p = (gmdt_ushort_p_t*)dest;
			//gmp_std_sprintf(buf, "(ushort 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(US 0x%02X) %d", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_IN:
		{
			gmdt_int_p_t			*p;


			p = (gmdt_int_p_t*)dest;
			//gmp_std_sprintf(buf, "(int 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(IN 0x%02X) %d", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_UIN:
		{
			gmdt_uint_p_t			*p;


			p = (gmdt_uint_p_t*)dest;
			//gmp_std_sprintf(buf, "(uint 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(UIN 0x%02X) %d", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_L:
		{
			gmdt_long_p_t			*p;




			p = (gmdt_long_p_t*)dest;
			//gmp_std_sprintf(buf, "(long 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(L 0x%02X) %lld", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_UL:
		{
			gmdt_ulong_p_t			*p;




			p = (gmdt_ulong_p_t*)dest;
			//gmp_std_sprintf(buf, "(ulong 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(UL 0x%02X) %lld", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_F:
		{
			gmdt_float_p_t			*p;




			p = (gmdt_float_p_t*)dest;
			//gmp_std_sprintf(buf, "(float 0x%02X) %f", *(p->gmdt), *(p->data));
			//gmp_std_sprintf(buf, "(F 0x%02X) %f", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(F 0x%02X) ...", *(p->gmdt));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_UF:
		{
			gmdt_ufloat_p_t			*p;


			p = (gmdt_ufloat_p_t*)dest;
			//gmp_std_sprintf(buf, "(ufloat 0x%02X) %f", *(p->gmdt), *(p->data));
			//gmp_std_sprintf(buf, "(UF 0x%02X) %f", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(UF 0x%02X) ...", *(p->gmdt));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_D:
		{
			gmdt_double_p_t			*p;


			p = (gmdt_double_p_t*)dest;
			//gmp_std_sprintf(buf, "(double 0x%02X) %lf", *(p->gmdt), *(p->data));
			//gmp_std_sprintf(buf, "(D 0x%02X) %lf", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(D 0x%02X) ...", *(p->gmdt));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_UD:
		{
			gmdt_udouble_p_t			*p;




			p = (gmdt_udouble_p_t*)dest;
			//gmp_std_sprintf(buf, "(udouble 0x%02X) %lf", *(p->gmdt), *(p->data));
			//gmp_std_sprintf(buf, "(UD 0x%02X) %lf", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(UD 0x%02X) ...", *(p->gmdt));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_N:
		{
			gmdt_null_p_t			*p;




			p = (gmdt_null_p_t*)dest;
			//gmp_std_sprintf(buf, "(null 0x%02X)", *(p->gmdt));
			gmp_std_sprintf(buf, "(N 0x%02X)", *(p->gmdt));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_T:
		{
			gmdt_type_p_t			*p;




			p = (gmdt_type_p_t*)dest;
			//gmp_std_sprintf(buf, "(type 0x%02X) %d", *(p->gmdt), *(p->data));
			gmp_std_sprintf(buf, "(T 0x%02X) %d", *(p->gmdt), *(p->data));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
		//容器类型(64--127):
	case GMP_GMDT_A:
		{
			gmdt_array_p_t			*p;
			

			p = (gmdt_array_p_t*)dest;
			//gmp_std_sprintf(buf, "(array 0x%02X) %d", *(p->gmdt), *(p->nelts));
			gmp_std_sprintf(buf, "(A 0x%02X) %d", *(p->gmdt), *(p->nelts));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_O:
		{
			gmdt_object_p_t			*p;



			p = (gmdt_object_p_t*)dest;
			//gmp_std_sprintf(buf, "(object 0x%02X) %d", *(p->gmdt), *(p->nelts));
			gmp_std_sprintf(buf, "(O 0x%02X) %d", *(p->gmdt), *(p->nelts));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_X:
		{
			gmdt_xml_p_t			*p;
			gmp_print_string		*gmp_str;



			p = (gmdt_xml_p_t*)dest;
			//gmp_std_sprintf(buf, "(xml 0x%02X)[%d] ", *(p->gmdt), *(p->len));
			gmp_std_sprintf(buf, "(X 0x%02X)[%d] ", *(p->gmdt), *(p->len));

			gmp_str = gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));

			return gmp_gmf_print_stirng_copy(pool, gmp_str, p->data, *(p->len));
		}
		break;
	case GMP_GMDT_JS:
		{
			gmdt_json_p_t			*p;
			gmp_print_string		*gmp_str;



			p = (gmdt_json_p_t*)dest;
			//gmp_std_sprintf(buf, "(json 0x%02X)[%d] ", *(p->gmdt), *(p->len));
			gmp_std_sprintf(buf, "(JS 0x%02X)[%d] ", *(p->gmdt), *(p->len));

			gmp_str = gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));

			return gmp_gmf_print_stirng_copy(pool, gmp_str, p->data, *(p->len));
		}
		break;
	case GMP_GMDT_IOB:
		{
			gmdt_iobuffer_p_t			*p;


			p = (gmdt_iobuffer_p_t*)dest;
			//gmp_std_sprintf(buf, "(iobuffer 0x%02X)[%d] ...", *(p->gmdt), *(p->len));
			gmp_std_sprintf(buf, "(IOB 0x%02X)[%d] ...", *(p->gmdt), *(p->len));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
		//扩展类型(CSS_PRINT_STRING_MAX_LEN--255):
	case GMP_GMDT_ST:
		{
			gmdt_string_p_t			*p;
			gmp_print_string		*gmp_str;



			p = (gmdt_string_p_t*)dest;
			//gmp_std_sprintf(buf, "(string 0x%02X)[%d] ", *(p->gmdt), *(p->len));
			gmp_std_sprintf(buf, "(ST 0x%02X)[%d] ", *(p->gmdt), *(p->len));

			gmp_str = gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));

			return gmp_gmf_print_stirng_copy(pool, gmp_str, p->data, *(p->len));
		}
		break;
	case GMP_GMDT_R:
		{
			gmdt_rect_p_t			*p;


			p = (gmdt_rect_p_t*)dest;
			//gmp_std_sprintf(buf, "(rect 0x%02X) (%d, %d) (%d, %d)", 
			//	*(p->gmdt), *(p->x1), *(p->y1), *(p->x2), *(p->y2));

			gmp_std_sprintf(buf, "(R 0x%02X) (%d, %d) (%d, %d)", 
				*(p->gmdt), *(p->x1), *(p->y1), *(p->x2), *(p->y2));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	case GMP_GMDT_RP:
		{
			gmdt_rectpair_p_t			*p;


			p = (gmdt_rectpair_p_t*)dest;
			gmp_std_sprintf(buf, "(RP 0x%02X) S(%d, %d) (%d, %d) D(%d, %d) (%d, %d)", 
				*(p->gmdt), *(p->x1), *(p->y1), *(p->x2), *(p->y2), *(p->x3), *(p->y3), *(p->x4), *(p->y4));

			return gmp_gmf_print_stirng_copy(pool, prev, buf, gmp_std_strlen(buf));
		}
		break;
	default:
		{
			return prev;
		}
	}

	return prev;
}

gmp_gmdt_bool gmp_gmf_print_bool(gm_std_void *dest, gm_std_int layer)
{
	gmdt_bool_p_t			*p;




	p = (gmdt_bool_p_t*)dest;
	printf("(bool 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_char(gm_std_void *dest, gm_std_int layer)
{
	gmdt_char_p_t			*p;




	p = (gmdt_char_p_t*)dest;
	printf("(char 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_uchar(gm_std_void *dest, gm_std_int layer)
{
	gmdt_uchar_p_t			*p;




	p = (gmdt_uchar_p_t*)dest;
	printf("(uchar 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_short(gm_std_void *dest, gm_std_int layer)
{
	gmdt_short_p_t			*p;




	p = (gmdt_short_p_t*)dest;
	printf("(short 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_ushort(gm_std_void *dest, gm_std_int layer)
{
	gmdt_ushort_p_t			*p;




	p = (gmdt_ushort_p_t*)dest;
	printf("(ushort 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_int(gm_std_void *dest, gm_std_int layer)
{
	gmdt_int_p_t			*p;




	p = (gmdt_int_p_t*)dest;
	printf("(int 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_uint(gm_std_void *dest, gm_std_int layer)
{
	gmdt_uint_p_t			*p;




	p = (gmdt_uint_p_t*)dest;
	printf("(uint 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_long(gm_std_void *dest, gm_std_int layer)
{
	gmdt_long_p_t			*p;




	p = (gmdt_long_p_t*)dest;
#if defined(WIN32)
	printf("(long 0x%02X) %lld", *(p->gmdt), *(p->data));
#else
	printf("(long 0x%02X) %l64d", *(p->gmdt), *(p->data));
#endif
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_ulong(gm_std_void *dest, gm_std_int layer)
{
	gmdt_ulong_p_t			*p;




	p = (gmdt_ulong_p_t*)dest;
#if defined(WIN32)
	printf("(ulong 0x%02X) %lld", *(p->gmdt), *(p->data));
#else
	printf("(ulong 0x%02X) %l64d", *(p->gmdt), *(p->data));
#endif
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_float(gm_std_void *dest, gm_std_int layer)
{
	gmdt_float_p_t			*p;




	p = (gmdt_float_p_t*)dest;
//#if defined(hi3531)
	printf("(float 0x%02X) ...", *(p->gmdt));
// #else
// 	printf("(float 0x%02X) %f", *(p->gmdt), *(p->data));
// #endif

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_ufloat(gm_std_void *dest, gm_std_int layer)
{
	gmdt_ufloat_p_t			*p;




	p = (gmdt_ufloat_p_t*)dest;
//#if defined(hi3531)
	printf("(ufloat 0x%02X) ...", *(p->gmdt));
// #else
// 	printf("(ufloat 0x%02X) %f", *(p->gmdt), *(p->data));
// #endif

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_double(gm_std_void *dest, gm_std_int layer)
{
	gmdt_double_p_t			*p;




	p = (gmdt_double_p_t*)dest;
//#if defined(hi3531)
	printf("(double 0x%02X) ...", *(p->gmdt));
// #else
// 	printf("(double 0x%02X) %lf", *(p->gmdt), *(p->data));
// #endif

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_udouble(gm_std_void *dest, gm_std_int layer)
{
	gmdt_udouble_p_t			*p;




	p = (gmdt_udouble_p_t*)dest;
//#if defined(hi3531)
	printf("(udouble 0x%02X) ...", *(p->gmdt));
// #else
// 	printf("(udouble 0x%02X) %lf", *(p->gmdt), *(p->data));
// #endif

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_null(gm_std_void *dest, gm_std_int layer)
{
	gmdt_null_p_t			*p;




	p = (gmdt_null_p_t*)dest;
	printf("(null 0x%02X)", *(p->gmdt));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_type(gm_std_void *dest, gm_std_int layer)
{
	gmdt_type_p_t			*p;




	p = (gmdt_type_p_t*)dest;
	printf("(type 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}


//容器类型数据的获取
gmp_gmdt_bool gmp_gmf_print_array(gm_std_void *dest, gm_std_int layer)
{
	gmdt_array_p_t			*p;
	gmp_gmdu_t				*gmdu;
	//gm_std_uint				i;





	p = (gmdt_array_p_t*)dest;
	gmdu = p->elts;


	//for (i = 0; i < *(p->nelts); i++)
	//{
	//	gmp_gmf_print_gmdu(&gmdu[i], layer + 1);
	//}
	printf("(array 0x%02X) %d", *(p->gmdt), *(p->nelts));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_object(gm_std_void *dest, gm_std_int layer)
{
	gmdt_array_p_t			*p;
	gmp_gmdu_t				*gmdu;
	//gm_std_uint				i;





	p = (gmdt_array_p_t*)dest;
	gmdu = p->elts;


	//for (i = 0; i < *(p->nelts); i++)
	//{
	//	gmp_gmf_print_gmdu(&gmdu[i], layer + 1);
	//}
	printf("(object 0x%02X) %d", *(p->gmdt), *(p->nelts));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_xml(gm_std_void *dest, gm_std_int layer)
{
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_json(gm_std_void *dest, gm_std_int layer)
{
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_iobuffer(gm_std_void *dest, gm_std_int layer)
{
	return gmp_gmdt_true;
}



//扩展类型数据的获取
gmp_gmdt_bool gmp_gmf_print_string(gm_std_void *dest, gm_std_int layer)
{
	gmdt_string_p_t			*p;
	gm_std_char				buf[256] = {0,};




	gmp_std_memset(buf, 0, 256);
	p = (gmdt_string_p_t*)dest;
	gmp_std_memcpy(buf, p->data, *(p->len));
	printf("(string 0x%02X) %s [%d]", *(p->gmdt), buf, *(p->len));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_rect(gm_std_void *dest, gm_std_int layer)
{
	gmdt_rect_p_t			*p;




	p = (gmdt_rect_p_t*)dest;
	printf("(rect 0x%02X) (%d, %d)(%d, %d)", *(p->gmdt), *(p->x1), *(p->y1), *(p->x2), *(p->y2));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_rectpair(gm_std_void *dest, gm_std_int layer)
{
	gmdt_rectpair_p_t			*p;




	p = (gmdt_rectpair_p_t*)dest;
	printf("(rectpair 0x%02X) S[(%d, %d)(%d, %d)] D[(%d, %d)(%d, %d)]", *(p->gmdt), *(p->x1), *(p->y1), *(p->x2), *(p->y2), *(p->x3), *(p->y3), *(p->x4), *(p->y4));

	return gmp_gmdt_true;
}

gmp_print_string* gmp_gmf_print_tab(gmp_pool_t *pool, gmp_print_string *prev, gm_std_int layer)
{
	gm_std_int				i;
	gm_std_char				layer_buf[128] = {0,};




	if (!layer)
	{
		return prev;
	}

	for (i = 0; i < layer; i++)
	{
		layer_buf[i] = '\t';
	}

	return gmp_gmf_print_stirng_copy(pool, prev, layer_buf, gmp_std_strlen(layer_buf));
}

gmp_print_string* gmp_gmf_print_stirng_copy(gmp_pool_t *pool, gmp_print_string *prev, char* src, int len)
{
	gmp_print_string				*gmp_str;




	if (!prev)
	{
		return NULL;
	}

	gmp_str = gmp_gmf_create_print_stirng(pool, len + 1);
	if (!gmp_str)
	{
		return NULL;
	}

	gmp_std_strncpy(gmp_str->last, src, len);

	gmp_str->last = gmp_str->last + len;
	prev->next = gmp_str;

	return gmp_str;
}

gmp_print_string* gmp_gmf_create_print_stirng(gmp_pool_t *pool, gm_std_int len)
{
	gmp_print_string				*gmp_str;




	if (!len)
	{
		return NULL;
	}

	gmp_str = (gmp_print_string*)gmp_palloc(pool, gmp_std_sizeof(gmp_print_string));
	if (!gmp_str)
	{
		return NULL;
	}

	gmp_str->start = (char*)gmp_palloc(pool, len);
	if (!gmp_str->start)
	{
		return NULL;
	}

	gmp_std_memset(gmp_str->start, 0, len);
	gmp_str->pos = gmp_str->start;
	gmp_str->last = gmp_str->pos;
	gmp_str->end = gmp_str->last;
	gmp_str->next = NULL;


	return gmp_str;
}

#endif










#if defined(CSS_GMP_PRINT_TO_STDOUT)
gmp_gmdt_bool gmp_gmf_printf(gmp_gmf_t *gmf)
{
	gmp_gmf_print_gmfh(gmf);

	gmp_gmf_print_gmdu(gmf->gmdu, 2);
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_gmfh(gmp_gmf_t *gmf)
{
	gm_std_char				buf[8] = {0,};





	gmp_std_memcpy(buf, gmf->gmfh.gmff, 4);
	printf("\r\n\tprint gmf:\r\n");
	printf("\tgmfh-->\r\n\t\t[%s | 0x%02X | 0x%02X | 0x%02X | %d]\r\n", buf, gmf->gmfh.version, gmf->gmfh.endian, gmf->gmfh.encode, gmf->gmfh.size);
	printf("\r\n\r\n\tgmfb-->\r\n");
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_current_gmdu(gmp_gmf_t *gmf)
{
	return gmp_gmf_print_gmdu(gmf->current_gmdu, 0);
}

gmp_gmdt_bool gmp_gmf_print_gmdu(gmp_gmdu_t *gmdu, gm_std_int layer)
{
	gmp_gmf_print_tab(layer);

	if (!gmdu)
	{
		printf("<gmdu null error>");
		return gmp_gmdt_false;
	}

	if (gmdu->key)
	{
		gmp_gmf_print_gmdt(gmdu->key, layer);
	}
	else
	{
		printf("<key null error>");
	}

	printf(" : ");

	if (gmdu->val)
	{
		gmp_gmf_print_gmdt(gmdu->val, layer);
	}
	else
	{
		printf("<value null error>");
	}

	printf("\r\n");


	if (!gmdu->key || !gmdu->val)
	{
		return gmp_gmdt_false;
	}

	if (!gmp_is_have_child(gmdu))
	{
		return gmp_gmdt_true;
	}
	else
	{
		if (gmp_is_p_array_object(gmp_get_p_type((unsigned char*)(gmdu->key))))
		{
			//获取子节点元素
			return gmp_gmf_print_child_gmdu(gmdu->key, layer);
		}
		else
		{
			//获取子节点元素
			return gmp_gmf_print_child_gmdu(gmdu->val, layer);
		}
	}
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_child_gmdu(gm_std_void *dest, gm_std_int layer)
{
	gmdt_array_p_t			*p;
	gmp_gmdu_t				*gmdu;





	if (!dest)
	{
		return gmp_gmdt_false;
	}

	p = (gmdt_array_p_t*)dest;
	gmdu = p->elts;

	for (; gmdu; gmdu = (gmp_gmdu_t*)(gmdu->next))
	{
		gmp_gmf_print_gmdu(gmdu, layer + 1);
	}

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_gmdt(gm_std_void *dest, gm_std_int layer)
{

	if (!dest)
	{
		return gmp_gmdt_false;
	}

	switch(*gmp_get_p_type(dest))
	{
		//常用基础数据类型(0--63)
	case GMP_GMDT_B:
		{
			return gmp_gmf_print_bool(dest, layer);
		}
		break;
	case GMP_GMDT_C:
		{
			return gmp_gmf_print_char(dest, layer);
		}
		break;
	case GMP_GMDT_UC:
		{
			return gmp_gmf_print_uchar(dest, layer);
		}
		break;
	case GMP_GMDT_S:
		{
			return gmp_gmf_print_short(dest, layer);
		}
		break;
	case GMP_GMDT_US:
		{
			return gmp_gmf_print_ushort(dest, layer);
		}
		break;
	case GMP_GMDT_IN:
		{
			return gmp_gmf_print_int(dest, layer);
		}
		break;
	case GMP_GMDT_UIN:
		{
			return gmp_gmf_print_uint(dest, layer);
		}
		break;
	case GMP_GMDT_L:
		{
			return gmp_gmf_print_long(dest, layer);
		}
		break;
	case GMP_GMDT_UL:
		{
			return gmp_gmf_print_ulong(dest, layer);
		}
		break;
	case GMP_GMDT_F:
		{
			return gmp_gmf_print_float(dest, layer);
		}
		break;
	case GMP_GMDT_UF:
		{
			return gmp_gmf_print_ufloat(dest, layer);
		}
		break;
	case GMP_GMDT_D:
		{
			return gmp_gmf_print_double(dest, layer);
		}
		break;
	case GMP_GMDT_UD:
		{
			return gmp_gmf_print_udouble(dest, layer);
		}
		break;
	case GMP_GMDT_N:
		{
			return gmp_gmf_print_null(dest, layer);
		}
		break;
	case GMP_GMDT_T:
		{
			return gmp_gmf_print_type(dest, layer);
		}
		break;
		//容器类型(64--127):
	case GMP_GMDT_A:
		{
			return gmp_gmf_print_array(dest, layer);
		}
		break;
	case GMP_GMDT_O:
		{
			return gmp_gmf_print_object(dest, layer);
		}
		break;
	case GMP_GMDT_X:
		{
			return gmp_gmf_print_xml(dest, layer);
		}
		break;
	case GMP_GMDT_JS:
		{
			return gmp_gmf_print_json(dest, layer);
		}
		break;
	case GMP_GMDT_IOB:
		{
			return gmp_gmf_print_iobuffer(dest, layer);
		}
		break;
		//扩展类型(CSS_PRINT_STRING_MAX_LEN--255):
	case GMP_GMDT_ST:
		{
			return gmp_gmf_print_string(dest, layer);
		}
		break;
	case GMP_GMDT_R:
		{
			return gmp_gmf_print_rect(dest, layer);
		}
		break;
	default:
		{
			return gmp_gmdt_true;
		}
	}

	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_bool(gm_std_void *dest, gm_std_int layer)
{
	gmdt_bool_p_t			*p;




	p = (gmdt_bool_p_t*)dest;
	printf("(bool 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_char(gm_std_void *dest, gm_std_int layer)
{
	gmdt_char_p_t			*p;




	p = (gmdt_char_p_t*)dest;
	printf("(char 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_uchar(gm_std_void *dest, gm_std_int layer)
{
	gmdt_uchar_p_t			*p;




	p = (gmdt_uchar_p_t*)dest;
	printf("(uchar 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_short(gm_std_void *dest, gm_std_int layer)
{
	gmdt_short_p_t			*p;




	p = (gmdt_short_p_t*)dest;
	printf("(short 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_ushort(gm_std_void *dest, gm_std_int layer)
{
	gmdt_ushort_p_t			*p;




	p = (gmdt_ushort_p_t*)dest;
	printf("(ushort 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_int(gm_std_void *dest, gm_std_int layer)
{
	gmdt_int_p_t			*p;




	p = (gmdt_int_p_t*)dest;
	printf("(int 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_uint(gm_std_void *dest, gm_std_int layer)
{
	gmdt_uint_p_t			*p;




	p = (gmdt_uint_p_t*)dest;
	printf("(uint 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_long(gm_std_void *dest, gm_std_int layer)
{
	gmdt_long_p_t			*p;




	p = (gmdt_long_p_t*)dest;
	printf("(long 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_ulong(gm_std_void *dest, gm_std_int layer)
{
	gmdt_ulong_p_t			*p;




	p = (gmdt_ulong_p_t*)dest;
	printf("(ulong 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_float(gm_std_void *dest, gm_std_int layer)
{
	gmdt_float_p_t			*p;




	p = (gmdt_float_p_t*)dest;
	//printf("(float 0x%02X) %f", *(p->gmdt), *(p->data));
	printf("(float 0x%02X) ...", *(p->gmdt));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_ufloat(gm_std_void *dest, gm_std_int layer)
{
	gmdt_ufloat_p_t			*p;




	p = (gmdt_ufloat_p_t*)dest;
	/*printf("(ufloat 0x%02X) %f", *(p->gmdt), *(p->data));*/
	printf("(ufloat 0x%02X) ...", *(p->gmdt));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_double(gm_std_void *dest, gm_std_int layer)
{
	gmdt_double_p_t			*p;




	p = (gmdt_double_p_t*)dest;
	//printf("(double 0x%02X) %lf", *(p->gmdt), *(p->data));
	printf("(double 0x%02X) ...", *(p->gmdt));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_udouble(gm_std_void *dest, gm_std_int layer)
{
	gmdt_udouble_p_t			*p;




	p = (gmdt_udouble_p_t*)dest;
	//printf("(udouble 0x%02X) %lf", *(p->gmdt), *(p->data));
	printf("(udouble 0x%02X) ...", *(p->gmdt));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_null(gm_std_void *dest, gm_std_int layer)
{
	gmdt_null_p_t			*p;




	p = (gmdt_null_p_t*)dest;
	printf("(null 0x%02X)", *(p->gmdt));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_type(gm_std_void *dest, gm_std_int layer)
{
	gmdt_type_p_t			*p;




	p = (gmdt_type_p_t*)dest;
	printf("(type 0x%02X) %d", *(p->gmdt), *(p->data));
	return gmp_gmdt_true;
}


//容器类型数据的获取
gmp_gmdt_bool gmp_gmf_print_array(gm_std_void *dest, gm_std_int layer)
{
	gmdt_array_p_t			*p;
	gmp_gmdu_t				*gmdu;
	//gm_std_uint				i;





	p = (gmdt_array_p_t*)dest;
	gmdu = p->elts;


	//for (i = 0; i < *(p->nelts); i++)
	//{
	//	gmp_gmf_print_gmdu(&gmdu[i], layer + 1);
	//}
	printf("(array 0x%02X) %d", *(p->gmdt), *(p->nelts));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_object(gm_std_void *dest, gm_std_int layer)
{
	gmdt_array_p_t			*p;
	gmp_gmdu_t				*gmdu;
	//gm_std_uint				i;





	p = (gmdt_array_p_t*)dest;
	gmdu = p->elts;


	//for (i = 0; i < *(p->nelts); i++)
	//{
	//	gmp_gmf_print_gmdu(&gmdu[i], layer + 1);
	//}
	printf("(object 0x%02X) %d", *(p->gmdt), *(p->nelts));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_xml(gm_std_void *dest, gm_std_int layer)
{
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_json(gm_std_void *dest, gm_std_int layer)
{
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_iobuffer(gm_std_void *dest, gm_std_int layer)
{
	return gmp_gmdt_true;
}



//扩展类型数据的获取
gmp_gmdt_bool gmp_gmf_print_string(gm_std_void *dest, gm_std_int layer)
{
	gmdt_string_p_t			*p;
	gm_std_char				buf[256] = {0,};




	gmp_std_memset(buf, 0, 256);
	p = (gmdt_string_p_t*)dest;
	gmp_std_memcpy(buf, p->data, *(p->len));
	printf("(string 0x%02X) %s [%d]", *(p->gmdt), buf, *(p->len));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_rect(gm_std_void *dest, gm_std_int layer)
{
	gmdt_rect_p_t			*p;




	p = (gmdt_rect_p_t*)dest;
	printf("(rect 0x%02X) (%d, %d)(%d, %d)", *(p->gmdt), *(p->x1), *(p->x1), *(p->x1), *(p->x1));
	return gmp_gmdt_true;
}

gmp_gmdt_bool gmp_gmf_print_tab(gm_std_int layer)
{
	gm_std_int				i;





	for (i = 0; i < layer; i++)
	{
		printf("\t");
	}

	return gmp_gmdt_true;
}

#endif


