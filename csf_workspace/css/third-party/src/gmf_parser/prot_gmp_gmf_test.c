







#if /*_PC_TEST_SWITCH_*/  1


#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#include "prot_gmp/prot_gmp_core.h"


gmp_gmdt_bool get_gmf_value(gmp_gmf_t *gmf, gmp_gmdt_t* dest, gmp_gmdt gmdt_type, char *name)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;


	if (!gmf)
	{
		printf("null gmf error.\r\n");

		return gmp_gmdt_false;
	}

	if (!gmp_chk_gmdt(gmdt_type))
	{
		printf("gmf gmdt[0x%02X] error.\r\n", gmdt_type);

		return gmp_gmdt_false;
	}

	//查找指定节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, name, strlen(name));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu)
	{
		printf("not %s element error.\r\n", name);

		return gmp_gmdt_false;
	}
	else
	{
		//获取gmdt的数值
		gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
		if (!gmdt)
		{
			printf("element %s not value error.\r\n", name);

			return gmp_gmdt_false;
		}
		else
		{
			if (gmdt_type != GMP_GMDT_UC)
			{
				//判断gmdt的类型是否相同
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) != gmdt_type)
				{
					printf("element %s type[0x%02X] error.\r\n", name, *(((gmdt_type_p_t*)gmdt)->gmdt));

					return gmp_gmdt_false;
				}
			}
			else
			{
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) > GMP_GMDT_T || *(((gmdt_type_p_t*)gmdt)->gmdt) < GMP_GMDT_B)
				{
					printf("element %s type[0x%02X] error.\r\n", name, *(((gmdt_type_p_t*)gmdt)->gmdt));

					return gmp_gmdt_false;
				}
			}

			switch (gmdt_type)
			{
				//常用基础数据类型(0--63)
			case GMP_GMDT_B:
			{
				((gmdt_bool_t *)dest)->gmdt = *(((gmdt_bool_p_t*)gmdt)->gmdt);
				((gmdt_bool_t *)dest)->data = *(((gmdt_bool_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_C:
			{
				((gmdt_char_t *)dest)->gmdt = *(((gmdt_char_p_t*)gmdt)->gmdt);
				((gmdt_char_t *)dest)->data = *(((gmdt_char_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UC:
			{
				((gmdt_uchar_t *)dest)->gmdt = *(((gmdt_uchar_p_t*)gmdt)->gmdt);
				((gmdt_uchar_t *)dest)->data = *(((gmdt_uchar_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_S:
			{
				((gmdt_short_t *)dest)->gmdt = *(((gmdt_short_p_t*)gmdt)->gmdt);
				((gmdt_short_t *)dest)->data = *(((gmdt_short_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_US:
			{
				((gmdt_ushort_t *)dest)->gmdt = *(((gmdt_ushort_p_t*)gmdt)->gmdt);
				((gmdt_ushort_t *)dest)->data = *(((gmdt_ushort_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_IN:
			{
				((gmdt_int_t *)dest)->gmdt = *(((gmdt_int_p_t*)gmdt)->gmdt);
				((gmdt_int_t *)dest)->data = *(((gmdt_int_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UIN:
			{
				((gmdt_uint_t *)dest)->gmdt = *(((gmdt_uint_p_t*)gmdt)->gmdt);
				((gmdt_uint_t *)dest)->data = *(((gmdt_uint_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_L:
			{
				((gmdt_long_t *)dest)->gmdt = *(((gmdt_long_p_t*)gmdt)->gmdt);
				((gmdt_long_t *)dest)->data = *(((gmdt_long_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UL:
			{
				((gmdt_ulong_t *)dest)->gmdt = *(((gmdt_ulong_p_t*)gmdt)->gmdt);
				((gmdt_ulong_t *)dest)->data = *(((gmdt_ulong_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_F:
			{
				((gmdt_float_t *)dest)->gmdt = *(((gmdt_float_p_t*)gmdt)->gmdt);
				((gmdt_float_t *)dest)->data = *(((gmdt_float_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UF:
			{
				((gmdt_ufloat_t *)dest)->gmdt = *(((gmdt_ufloat_p_t*)gmdt)->gmdt);
				((gmdt_ufloat_t *)dest)->data = *(((gmdt_ufloat_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_D:
			{
				((gmdt_double_t *)dest)->gmdt = *(((gmdt_double_p_t*)gmdt)->gmdt);
				((gmdt_double_t *)dest)->data = *(((gmdt_double_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UD:
			{
				((gmdt_udouble_t *)dest)->gmdt = *(((gmdt_udouble_p_t*)gmdt)->gmdt);
				((gmdt_udouble_t *)dest)->data = *(((gmdt_udouble_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_T:
			{
				((gmdt_uchar_t *)dest)->gmdt = *(((gmdt_uchar_p_t*)gmdt)->gmdt);
				((gmdt_uchar_t *)dest)->data = *(((gmdt_uchar_p_t*)gmdt)->data);
			}
			break;
			//容器类型(64--127):
			case GMP_GMDT_A:
			{
				((gmdt_array_t *)dest)->gmdt = *(((gmdt_array_p_t*)gmdt)->gmdt);
				((gmdt_array_t *)dest)->nelts = *(((gmdt_array_p_t*)gmdt)->nelts);
				((gmdt_array_t *)dest)->elts = ((gmdt_array_p_t*)gmdt)->elts;
			}
			break;
			case GMP_GMDT_O:
			{
				((gmdt_object_t *)dest)->gmdt = *(((gmdt_object_p_t*)gmdt)->gmdt);
				((gmdt_object_t *)dest)->nelts = *(((gmdt_object_p_t*)gmdt)->nelts);
				((gmdt_object_t *)dest)->elts = ((gmdt_object_p_t*)gmdt)->elts;
			}
			break;
			case GMP_GMDT_X:
			{
				((gmdt_xml_t *)dest)->gmdt = *(((gmdt_xml_p_t*)gmdt)->gmdt);
				((gmdt_xml_t *)dest)->len = *(((gmdt_xml_p_t*)gmdt)->len);
				((gmdt_xml_t *)dest)->data = ((gmdt_xml_p_t*)gmdt)->data;
			}
			break;
			case GMP_GMDT_JS:
			{
				((gmdt_json_t *)dest)->gmdt = *(((gmdt_json_p_t*)gmdt)->gmdt);
				((gmdt_json_t *)dest)->len = *(((gmdt_json_p_t*)gmdt)->len);
				((gmdt_json_t *)dest)->data = ((gmdt_json_p_t*)gmdt)->data;
			}
			break;
			case GMP_GMDT_ST:
			{
				((gmdt_string_t *)dest)->gmdt = *(((gmdt_string_p_t*)gmdt)->gmdt);
				((gmdt_string_t *)dest)->len = *(((gmdt_string_p_t*)gmdt)->len);
				((gmdt_string_t *)dest)->data = ((gmdt_string_p_t*)gmdt)->data;
			}
			break;
			case GMP_GMDT_IOB:
			{
				((gmdt_iobuffer_t *)dest)->gmdt = *(((gmdt_iobuffer_p_t*)gmdt)->gmdt);
				((gmdt_iobuffer_t *)dest)->len = *(((gmdt_iobuffer_p_t*)gmdt)->len);
				((gmdt_iobuffer_t *)dest)->data = ((gmdt_iobuffer_p_t*)gmdt)->data;
			}
			break;
			//扩展类型(128--255):
			case GMP_GMDT_R:
			{
				((gmdt_rect_t *)dest)->gmdt = *(((gmdt_rect_p_t*)gmdt)->gmdt);
				((gmdt_rect_t *)dest)->x1 = *(((gmdt_rect_p_t*)gmdt)->x1);
				((gmdt_rect_t *)dest)->y1 = *(((gmdt_rect_p_t*)gmdt)->y1);
				((gmdt_rect_t *)dest)->x2 = *(((gmdt_rect_p_t*)gmdt)->x2);
				((gmdt_rect_t *)dest)->y2 = *(((gmdt_rect_p_t*)gmdt)->y2);
			}
			break;
			case GMP_GMDT_RP:
			{
				((gmdt_rectpair_t *)dest)->gmdt = *(((gmdt_rectpair_p_t*)gmdt)->gmdt);
				((gmdt_rectpair_t *)dest)->x1 = *(((gmdt_rectpair_p_t*)gmdt)->x1);
				((gmdt_rectpair_t *)dest)->y1 = *(((gmdt_rectpair_p_t*)gmdt)->y1);
				((gmdt_rectpair_t *)dest)->x2 = *(((gmdt_rectpair_p_t*)gmdt)->x2);
				((gmdt_rectpair_t *)dest)->y2 = *(((gmdt_rectpair_p_t*)gmdt)->y2);
				((gmdt_rectpair_t *)dest)->x3 = *(((gmdt_rectpair_p_t*)gmdt)->x3);
				((gmdt_rectpair_t *)dest)->y3 = *(((gmdt_rectpair_p_t*)gmdt)->y3);
				((gmdt_rectpair_t *)dest)->x4 = *(((gmdt_rectpair_p_t*)gmdt)->x4);
				((gmdt_rectpair_t *)dest)->y4 = *(((gmdt_rectpair_p_t*)gmdt)->y4);
			}
			break;
			default:
			{
				printf("element %s unknow type[%d] error.\r\n", name, gmdt_type);

				return gmp_gmdt_false;
			}
			}
		}
	}
	return gmp_gmdt_true;
}

gmp_gmdt_bool get_gmf_value_demo()
{
	gmp_gmf_t				*gmf;
	gmp_gmdu_t				*gmdu;
	gmp_gmdt_bool			ret_bool = gmp_gmdt_true;
	gm_std_char				ver_buf[512] = { 0, };
	gmdt_int_t				number;
	gmdt_string_t			str;





	//创建一个gmf
	//////////////////////////////////////////////////////////////////////////
	gmf = gmp_create_gmf();
	
	gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	gmp_add_gmdu(gmf, gmdu);

	//添加一个Int类型节点
	gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T%d", GMP_GMDT_ST, "number", strlen("number"), GMP_GMDT_IN, 200);
	gmp_add_child_gmdu(gmf, gmdu);

	gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T%p%d", GMP_GMDT_ST, "string", strlen("string"), GMP_GMDT_ST, "hello world!", strlen("hello world!"));
	gmp_add_child_gmdu(gmf, gmdu);

	//跳到根节点
	gmp_top_gmdu(gmf);
	//进入根节点，即number和string节点层
	gmp_into_gmdu(gmf);
	
	//查询数值
	ret_bool = get_gmf_value(gmf, &number, GMP_GMDT_IN, "number");
	if (ret_bool)
	{
		printf("get \"number\" value [%d]\r\n", number.data);
	}

	ret_bool = get_gmf_value(gmf, &str, GMP_GMDT_ST, "string");
	if (ret_bool)
	{
		memset(ver_buf, 0, 512);
		memcpy(ver_buf, str.data, str.len);
		printf("get \"string\" value [%s]\r\n", ver_buf);
	}

	gmp_destroy_gmf(gmf);

	return gmp_gmdt_true;
}

int main(int argc, char** argv)
{

	gmp_gmf_t				*gmf;
	gmp_gmf_t				*new_gmf;
	gmp_gmdu_t				*new_gmdu;
	gmp_gmdt_t				*new_gmdt;
	gmdt_iobuffer_p_t		*iob;

#if defined(CSS_GMP_PRINT_TO_LOG)
	gmdt_string_p_t			*gmp_str;
#endif

	gm_std_int				ver;
	gm_std_int				len = 0;
	gmp_gmdt_bool			ret_bool = gmp_gmdt_true;
	gm_std_char				ver_buf[512] = { 0, };





	//创建一个gmf
	//////////////////////////////////////////////////////////////////////////
	gmf = gmp_create_gmf();
	if (!gmf)
	{
		printf("gmp_create_gmf error!\r\n");
		return -1;
	}

	gmp_get_version(gmf, &ver, ver_buf, 100);
	printf("version:%d\ttext:%s\r\n", ver, ver_buf);


	printf("add gmdu\r\n");
	//创建一个gmdu节点
	new_gmdu = gmp_create_gmdu(gmf, "%T,%T%d", GMP_GMDT_O, GMP_GMDT_IN, 200);
	if (!new_gmdu)
	{
		printf("gmp_create_gmdu error!\r\n");
	}
	else
	{
		printf("gmp_create_gmdu successed!\r\n");
	}

	//添加一个节点，将新节点作为当前节点
	if (!gmp_add_gmdu(gmf, new_gmdu))
	{
		printf("gmp_add_gmdu failed!\r\n");
	}
	else
	{
		printf("gmp_add_gmdu successed!\r\n");
	}

#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_printf(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_printf(gmf);
#endif


	printf("print currnet gmdu\r\n");
#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_print_current_gmdu(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_print_current_gmdu(gmf);
#endif


	//添加gmdu子节点，只有当前节点为容器节点，才能添加子节点。 添加子节点，当前位置不变
	new_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T%d", GMP_GMDT_ST, "abcded", 5, GMP_GMDT_IN, 200);
	if (!gmp_add_child_gmdu(gmf, new_gmdu))
	{
		printf("gmp_add_gmdu failed!\r\n");
	}
	else
	{
		printf("gmp_add_gmdu successed!\r\n");
	}

#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_printf(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_printf(gmf);
#endif


	//进入子节点,只有容器节点才能被进入
	gmp_into_gmdu(gmf);

	printf("print currnet gmdu\r\n");
#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_print_current_gmdu(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_print_current_gmdu(gmf);
#endif

	//添加gmdu节点
	new_gmdu = gmp_create_gmdu(gmf, "%T,%T%d", GMP_GMDT_A, GMP_GMDT_IN, 10);
	gmp_add_gmdu(gmf, new_gmdu);


	//添加gmdu节点
	new_gmdu = gmp_create_gmdu(gmf, "%T%p%d, %T", GMP_GMDT_ST, "object", gmp_std_strlen("object"), GMP_GMDT_O);
	gmp_add_gmdu(gmf, new_gmdu);


#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_printf(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_printf(gmf);
#endif


	printf("print currnet gmdu\r\n");
#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_print_current_gmdu(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_print_current_gmdu(gmf);
#endif


	//只有容器节点才能进入
	gmp_into_gmdu(gmf);

	//添加gmdu节点
	new_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T%p%d", GMP_GMDT_ST, "string", gmp_std_strlen("string"), GMP_GMDT_ST, "12345", gmp_std_strlen("12345"));
	if (!gmp_add_child_gmdu(gmf, new_gmdu))
	{
		printf("gmp_add_gmdu failed!\r\n");
	}
	else
	{
		printf("gmp_add_gmdu successed!\r\n");
	}

	//共享的方式更新一个字符串内容
	char*			update_buffer = "new data";
	gmp_gmdu_setbuffer(gmf, new_gmdu, gmp_gmdu_value, update_buffer, strlen(update_buffer), gmf_work_mode_shared_memory);


	gmp_add_child_gmdu(gmf, new_gmdu);


#if defined(CSS_GMP_PRINT_TO_LOG)
	gmp_gmf_printf(gmf, &gmp_str, NULL, 0, gmp_print_style_null);
	if (gmp_str)
	{
		printf("%s\r\n", gmp_str->data);
	}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
	gmp_gmf_printf(gmf);
#endif



	//生成一个gmf
	//////////////////////////////////////////////////////////////////////////
	//采用iobuffer方式获取gmf字节流
	len = gmp_gmf_encode(gmf, &iob, NULL, 0);
	if (!len)
	{
		printf("gmp_gmf_encode iobuffer error!\r\n");
	}
	else
	{
		printf("gmp_gmf_encode iobuffer successed! len = %d\r\n", len);
	}


	//采用buffer方式获取gmf字节流
	gmp_std_memset(ver_buf, 0, 512);
	len = gmp_gmf_encode(gmf, NULL, (gm_std_uchar*)ver_buf, 512);
	if (!len)
	{
		printf("gmp_gmf_encode buffer error!\r\n");
	}
	else
	{
		printf("gmp_gmf_encode buffer successed! len = %d\r\n", len);
	}


	new_gmf = gmp_create_gmf();
	if (!new_gmf)
	{
		printf("gmp_create_gmf error!\r\n");
		return -1;
	}


	//解析一个gmf
	//////////////////////////////////////////////////////////////////////////
	if (!gmp_gmf_decode(new_gmf, iob->data, *(iob->len)))
	{
		printf("gmp_gmf_decode error!\r\n");
	}
	else
	{
		printf("gmp_gmf_decode successed!\r\n");


#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_printf(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_printf(new_gmf);
#endif

		//下一层节点
		printf("into gmdu\r\n\r\n");
		gmp_into_gmdu(new_gmf);

#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif



		//下一个节点
		printf("next gmdu\r\n\r\n");
		gmp_next_gmdu(new_gmf);


#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif


		//跳到本层的第一个节点
		printf("first gmdu\r\n\r\n");
		gmp_first_gmdu(new_gmf);

#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif


		//回到上一层节点
		printf("outof gmdu\r\n\r\n");
		gmp_outof_gmdu(new_gmf);

#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif



		//下一层节点
		printf("into gmdu\r\n\r\n");
		gmp_into_gmdu(new_gmf);


#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif


		//回到主节点
		printf("top gmdu\r\n\r\n");
		gmp_top_gmdu(new_gmf);

#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif


		//查找子节点
		new_gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, "object", gmp_std_strlen("object"));
		if (!new_gmdt)
		{
			printf("create gmdt failed!\r\n");
		}
		else
		{
			printf("create gmdt successed!\r\n");
		}

		new_gmdu = gmp_find_child_gmdu(new_gmf, new_gmdt);
		if (!new_gmdu)
		{
			printf("find gmdu failed!\r\n");
		}
		else
		{
			printf("find gmdu successed!\r\n");
		}

#if defined(CSS_GMP_PRINT_TO_LOG)
#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_gmdu(new_gmdu, 0);
#endif


		//将查找到的节点设置为当前节点
		printf("pint current gmdu\r\n\r\n");
		gmp_reset_gmdu(new_gmf, new_gmdu);


#if defined(CSS_GMP_PRINT_TO_LOG)
		gmp_gmf_print_current_gmdu(new_gmf, &gmp_str, NULL, 0, gmp_print_style_null);
		if (gmp_str)
		{
			printf("%s\r\n", gmp_str->data);
		}

#elif defined(CSS_GMP_PRINT_TO_STDOUT)
		gmp_gmf_print_current_gmdu(new_gmf);
#endif


	}

	gmp_destroy_gmf(new_gmf);

	gmp_destroy_gmf(gmf);

	get_gmf_value_demo();

	return 0;
}



#endif





