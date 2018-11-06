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
/* ͨ����Ϣ������ʽ��������ʽ����                                       */
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

	gmp_gmdu_t				*current_gmdu;							//��ʾ��ǰ���ڵĽڵ�

#if defined(GMP_USED_POOL)
	gmp_pool_t				*pool;
#endif
};
/************************************************************************/

#pragma pack()




/************************************************************************/
/* �������������������                                                  */
/************************************************************************/
enum	gmf_error_no_enum
{
	gmf_error_alloc_memory = 400,						//��ʾ�ڴ�����ʧ��
	gmf_error_format = 401,								//��ʾ���ݸ�ʽ����
	gmf_error_unkown_type = 402,						//��ʾ�����������ʹ���
	gmf_error_encode_parament = 403,					//��ʾ��������
	gmf_error_destroyed,								//��ʾ�Ѿ����ͷ�
};



/************************************************************************/
/* ����gmf�ַ��ı��뷽ʽ����                                                  */
/************************************************************************/
enum gmf_encode_enum
{
	gmf_encode_ascii = 0x00,							//��ʾascii���뷽ʽ
	gmf_encode_utf8 = 0x01,								//��ʾutf-8���뷽ʽ
	gmf_encode_gb2312 = 0x40,							//��ʾgb2312���뷽ʽ
	gmf_encode_gbk = 0x41,								//��ʾgbk���뷽ʽ
};


/************************************************************************/
/* ����gmf����ģʽ����Ϊ����ģʽ�͹����ڴ淽ʽ                             */
/************************************************************************/
enum gmf_work_mode
{
	gmf_work_mode_general = 0x00,						//��ʾ����ģʽ������������;��ģʽΪĬ��ģʽ
	gmf_work_mode_shared_memory = 0x01,					//��ʾ�������ݷ�ʽ�����ݽ���ʱ����������
};



/************************************************************************/
/* ���������������                                                     */
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
/* ͨ����Ϣ������ʽ��������ʵ��                                         */
/************************************************************************/

#if defined(GMP_USED_POOL)

	//////////////////////////////////////////////////////////////////////////
	//����gmf
	gmp_gmf_t *gmp_create_gmf();
	//����gmf
	void gmp_destroy_gmf(gmp_gmf_t *gmf);



	//////////////////////////////////////////////////////////////////////////
	//����һ��gmdu
	gmp_gmdu_t *gmp_create_gmdu(gmp_gmf_t *gmf, const gm_std_char *fmt, ...);
	//����һ��gmdt
	gmp_gmdt_t *gmp_create_gmdt(gmp_gmf_t *gmf, const gm_std_char *fmt, ...);



	//////////////////////////////////////////////////////////////////////////
	//��gmf�в���һ���ֵ�gmdu
	gmp_gmdu_t *gmp_find_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);
	//��gmf�в���һ���ӽڵ�gmdu
	gmp_gmdu_t *gmp_find_child_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);



	//////////////////////////////////////////////////////////////////////////
	//��gmf��ȡ������Ϣ
	gm_std_int gmp_get_error(gmp_gmf_t *gmf, gm_std_int *error_no, gm_std_char *error_text, gm_std_int len);
	//��ȡ�汾��Ϣ
	gmp_gmdt_bool gmp_get_version(gmp_gmf_t *gmf, gm_std_int *version, gm_std_char *version_text, gm_std_int len);


	//////////////////////////////////////////////////////////////////////////
	//��ȡgmp_gmdu_t������
	gmp_gmdt_t *gmp_get_gmdt(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdu_segment seg);
	//�ж�gmp_gmdt_t�������Ƿ���ͬ
	gmp_gmdt_bool gmp_gmdt_keycmp(gmp_gmdt_t *src_gmdt, gmp_gmdt_t *dest_gmdt);
	//�޸�gmdu��buffer���͵���������,�ýӿ���Ҫ֧��GMP_GMDT_ST/GMP_GMDT_X/GMP_GMDT_JS/GMP_GMDT_IOB�������͵����ݸ���
	gmp_gmdt_bool gmp_gmdu_setbuffer(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, gmp_gmdu_segment seg, const gm_std_char *buf, gm_std_int len, gm_std_int work_mode);
	//�޸�gmdt��buffer���͵���������,�ýӿ���Ҫ֧��GMP_GMDT_ST/GMP_GMDT_X/GMP_GMDT_JS/GMP_GMDT_IOB�������͵����ݸ���
	gmp_gmdt_bool gmp_gmdt_setbuffer(gmp_gmf_t *gmf, gmp_gmdt_t *src_gmdt, const gm_std_char *buf, gm_std_int len, gm_std_int work_mode);
	



	//////////////////////////////////////////////////////////////////////////
	//���õ�ǰ�ڵ�λ��
	gmp_gmdt_bool gmp_reset_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
	//���뵱ǰ�ڵ�gmdu
	gmp_gmdu_t *gmp_into_gmdu(gmp_gmf_t *gmf);
	//��һ���ֵܽڵ�gmdu
	gmp_gmdu_t *gmp_next_gmdu(gmp_gmf_t *gmf);
	//���õ���ǰ�ڵ�ĵ�һ���ӽڵ�gmdu
	gmp_gmdu_t *gmp_first_gmdu(gmp_gmf_t *gmf);
	//���õ�gmf�ĵ�һ��gmdu
	gmp_gmdu_t *gmp_top_gmdu(gmp_gmf_t *gmf);
	//�˳���ǰ�ڵ�gmdu��������һ��gmdu
	gmp_gmdu_t *gmp_outof_gmdu(gmp_gmf_t *gmf);



	//////////////////////////////////////////////////////////////////////////
	//��gmf�����һ���ֵ�gmdu
	gmp_gmdt_bool gmp_add_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
	//��gmf�����һ���ӽڵ�gmdu
	gmp_gmdt_bool gmp_add_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu);
	//��һ������gmdt�����һ���ӽڵ�gmdu
	gmp_gmdt_bool gmp_add_gmdu_child_gmdu(gmp_gmf_t *gmf, gmp_gmdu_t *dest_gmdu, gmp_gmdu_t *src_gmdu);
	//��gmf��ɾ����ǰgmdu
	gmp_gmdt_bool gmp_delete_current_gmdu(gmp_gmf_t *gmf);
	//��gmf��ɾ��һ���ֵ�gmdu
	gmp_gmdt_bool gmp_delete_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);
	//��gmf��ɾ��һ���ӽڵ�gmdu
	gmp_gmdt_bool gmp_delete_child_gmdu(gmp_gmf_t *gmf, gmp_gmdt_t *gmdt);



	//////////////////////////////////////////////////////////////////////////
	//gmf������
	gmp_gmdt_bool gmp_gmf_decode(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);
	//����һ��gmf��ʽ������
	gm_std_uint gmp_gmf_encode(gmp_gmf_t *gmf, gmdt_iobuffer_p_t **iob, gm_std_uchar *dest, gm_std_uint len);
	//����gmfh
	gmp_gmdt_bool gmp_set_gmfh(gmp_gmf_t *gmf, gm_std_uchar version, gm_std_uchar endian, gm_std_uchar encode);

	//���ù���ģʽ
	gmp_gmdt_bool gmp_set_work_mode(gmp_gmf_t *gmf, gm_std_int work_mode);


#else
	//����gmf
	gmp_gmf_t *gmp_create_gmf();
	//����gmf
	void gmp_destroy_gmf(gmp_gmf_t *gmf);
	//gmf������
	gmp_gmdt_bool gmp_gmf_decode(gmp_gmf_t *gmf, gm_std_uchar *src, gm_std_int len);


#endif

/************************************************************************/

#ifdef __cplusplus
}
#endif









#endif











