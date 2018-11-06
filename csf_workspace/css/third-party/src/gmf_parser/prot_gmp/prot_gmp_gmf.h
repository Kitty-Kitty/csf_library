/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:gmf defined

**************************************************************************/




#ifndef	_PROT_GMP_GMF_H_
#define _PROT_GMP_GMF_H_





#include "prot_gmp_core.h"






#define		GMP_GMF_GMFF					"GMFT"
#define		GMP_GMF_GMFF_LENGTH				4
#define		GMP_USED_POOL					
#define		GMP_POOL_BUFFER_SIZE			128






typedef struct gmp_gmf_gmfh_s				gmp_gmf_gmfh_t;






#pragma pack(1)

/************************************************************************/
/* 通用信息交换格式，基础格式定义                                       */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
//gmfh
struct gmp_gmf_gmfh_s
{
	gm_std_char		gmff[GMP_GMF_GMFF_LENGTH];
	gm_std_uchar	version;
	gm_std_uchar	endian;
	gm_std_uchar	encode;
	gm_std_uint		size;
};



//////////////////////////////////////////////////////////////////////////
//gmf
struct gmp_gmf_s
{
	gmp_gmf_gmfh_t			gmfh;
	gmp_gmdu_t				*gmdu;

	gm_std_int				work_mode;
	gm_std_int				error_no;
	gm_std_char				*error_text;

	gmp_gmdu_t				*current_gmdu;							//表示当前所在的节点

#if defined(GMP_USED_POOL)
	gmp_pool_t				*pool;
#endif
};
/************************************************************************/

#pragma pack()




/************************************************************************/
/* 定义解析器错误码内容                                                  */
/************************************************************************/
enum	gmf_error_no_enum
{
	gmf_error_alloc_memory = 400,						//表示内存申请失败
	gmf_error_format = 401,								//表示内容格式错误
	gmf_error_unkown_type = 402,						//表示内容数据类型错误
	gmf_error_encode_parament = 403,					//表示解析参数
	gmf_error_destroyed,								//表示已经被释放
};



/************************************************************************/
/* 定义gmf字符的编码方式内容                                                  */
/************************************************************************/
enum gmf_encode_enum
{
	gmf_encode_ascii = 0x00,							//表示ascii编码方式
	gmf_encode_utf8 = 0x01,								//表示utf-8编码方式
	gmf_encode_gb2312 = 0x40,							//表示gb2312编码方式
	gmf_encode_gbk = 0x41,								//表示gbk编码方式
};


/************************************************************************/
/* 定义gmf工作模式，分为常规模式和共享内存方式                             */
/************************************************************************/
enum gmf_work_mode
{
	gmf_work_mode_general = 0x00,						//表示常规模式，不共享内容;该模式为默认模式
	gmf_work_mode_shared_memory = 0x01,					//表示共享内容方式，数据接收时不拷贝数据
};



/************************************************************************/
/* 定义解析器操作宏                                                     */
/************************************************************************/
#if defined(WIN32)
#define	gmp_sys_errno						0
#define gmp_sys_strerror(errno)				" "
#else
#include <errno.h>
#define	gmp_sys_errno						errno
#define gmp_sys_strerror(errno)				strerror(errno)
#endif

#define	gmp_get_error_text(gmf)				gmf->error_text
#define	gmp_get_error_no(gmf)				gmf->error_no






#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************/
/* 通用信息交换格式，解析器实现                                         */
/************************************************************************/

#if defined(GMP_USED_POOL)

	//////////////////////////////////////////////////////////////////////////
	//创建gmf
	gmp_gmf_t *gmp_create_gmf();
	//销毁gmf
	void gmp_destroy_gmf(gmp_gmf_t *gmf);



	//////////////////////////////////////////////////////////////////////////
	//创建一个gmdu
	gmp_gmdu_t *gmp_create_gmdu(gmp_gmf_t *gmf, const gm_std_char *fmt, ...);
	//创建一个gmdt
	gmp_gmdt_t *gmp_create_gmdt(gmp_gmf_t *gmf, const gm_std_char *fmt, ...);



	//////////////////////////////////////////////////////////////////////////
	//从gmf中查找一个兄弟gmdu
	gmp_gmdu_t *gmp_find_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);
	//从gmf中查找一个子节点gmdu
	gmp_gmdu_t *gmp_find_child_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);



	//////////////////////////////////////////////////////////////////////////
	//从gmf获取错误信息
	gm_std_int gmp_get_error(gmp_gmf_t *gmf, gm_std_int *error_no, gm_std_char *error_text, gm_std_int len);
	//获取版本信息
	gmp_gmdt_bool gmp_get_version(gmp_gmf_t *gmf, gm_std_int *version, gm_std_char *version_text, gm_std_int len);


	//////////////////////////////////////////////////////////////////////////
	//获取gmp_gmdu_t的内容
	gmp_gmdt_t *gmp_get_gmdt(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdu_segment seg);
	//判断gmp_gmdt_t的内容是否相同
	gmp_gmdt_bool gmp_gmdt_keycmp(gmp_gmdt_t *src_gmdt, gmp_gmdt_t *dest_gmdt);
	//修改gmdu的buffer类型的数据内容,该接口主要支持GMP_GMDT_ST/GMP_GMDT_X/GMP_GMDT_JS/GMP_GMDT_IOB四种类型的数据更新
	gmp_gmdt_bool gmp_gmdu_setbuffer(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdu_segment seg, const gm_std_char *buf, gm_std_int len, gm_std_int work_mode);
	//修改gmdt的buffer类型的数据内容,该接口主要支持GMP_GMDT_ST/GMP_GMDT_X/GMP_GMDT_JS/GMP_GMDT_IOB四种类型的数据更新
	gmp_gmdt_bool gmp_gmdt_setbuffer(gmp_gmf_t *gmf, gmp_gmdt_t *src_gmdt, const gm_std_char *buf, gm_std_int len, gm_std_int work_mode);
	



	//////////////////////////////////////////////////////////////////////////
	//设置当前节点位置
	gmp_gmdt_bool gmp_reset_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
	//进入当前节点gmdu
	gmp_gmdu_t *gmp_into_gmdu(gmp_gmf_t *gmf);
	//下一个兄弟节点gmdu
	gmp_gmdu_t *gmp_next_gmdu(gmp_gmf_t *gmf);
	//设置到当前节点的第一个子节点gmdu
	gmp_gmdu_t *gmp_first_gmdu(gmp_gmf_t *gmf);
	//设置到gmf的第一个gmdu
	gmp_gmdu_t *gmp_top_gmdu(gmp_gmf_t *gmf);
	//退出当前节点gmdu，进入上一层gmdu
	gmp_gmdu_t *gmp_outof_gmdu(gmp_gmf_t *gmf);



	//////////////////////////////////////////////////////////////////////////
	//往gmf中添加一个兄弟gmdu
	gmp_gmdt_bool gmp_add_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
	//往gmf中添加一个子节点gmdu
	gmp_gmdt_bool gmp_add_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
	//往一个容器gmdt中添加一个子节点gmdu
	gmp_gmdt_bool gmp_add_gmdu_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *dest_gmdu, gmp_gmdu_t *src_gmdu);
	//从gmf中删除当前gmdu
	gmp_gmdt_bool gmp_delete_current_gmdu(gmp_gmf_t *gmf);
	//从gmf中删除一个兄弟gmdu
	gmp_gmdt_bool gmp_delete_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);
	//从gmf中删除一个子节点gmdu
	gmp_gmdt_bool gmp_delete_child_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);



	//////////////////////////////////////////////////////////////////////////
	//gmf解析器
	gmp_gmdt_bool gmp_gmf_decode(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);
	//生成一个gmf格式数据流
	gm_std_uint gmp_gmf_encode(gmp_gmf_t *gmf, gmdt_iobuffer_p_t **iob, gm_std_uchar *dest, gm_std_uint len);
	//设置gmfh
	gmp_gmdt_bool gmp_set_gmfh(gmp_gmf_t *gmf, gm_std_uchar version, gm_std_uchar endian, gm_std_uchar encode);

	//设置工作模式
	gmp_gmdt_bool gmp_set_work_mode(gmp_gmf_t *gmf, gm_std_int work_mode);


#else
	//创建gmf
	gmp_gmf_t *gmp_create_gmf();
	//销毁gmf
	void gmp_destroy_gmf(gmp_gmf_t *gmf);
	//gmf解析器
	gmp_gmdt_bool gmp_gmf_decode(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);


#endif

/************************************************************************/

#ifdef __cplusplus
}
#endif









#endif











