/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:gmph defined

**************************************************************************/


#ifndef	_PROT_GMP_GMPH_H_
#define _PROT_GMP_GMPH_H_




#include	<stdio.h>




#define			GMP_GMPV_LITTLE_ENDIAN									0x00000001
#define			GMP_GMPV_BIG_ENDIAN										0x01000000
#define			GMP_GMPH_SEMH_SESSION_ID_LEN							32
#define			GMP_GMPH_CPQMH_DEVICE_ID_LEN							64




enum gmp_gmph_emh_type_enum
{
	gmp_gmph_emh_type_null = 0x00,
	gmp_gmph_emh_type_semh = 0x01,
	gmp_gmph_emh_type_ptpemh = 0x02,
	gmp_gmph_emh_type_sdsemh = 0x03,
	gmp_gmph_emh_type_daemh = 0x04,
	gmp_gmph_emh_type_memh = 0x40,
	gmp_gmph_emh_type_cpqemh = 0x41
};


#pragma pack(1)


/************************************************************************/
/* 通用信息协议头GMPH中，BMH部分内容                                    */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
//bmh
typedef struct gmp_gmph_bmh_s
{
	unsigned int			gmpv;
	unsigned char			emht;
}gmp_gmph_bmh_t;




//////////////////////////////////////////////////////////////////////////
//semh

typedef struct gmp_gmph_semh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned int					command;
	unsigned int					length;
	unsigned int					packet_no;
	unsigned int					status;
	char							session_id[GMP_GMPH_SEMH_SESSION_ID_LEN];
}gmp_gmph_semh_t;







//////////////////////////////////////////////////////////////////////////
//ptpemh
typedef struct gmp_gmph_ptpemh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned int					command;
	unsigned int					status;
	unsigned char					device_type;
	unsigned char					heartbeat_interval;
	unsigned int					effective_precision_s;
	unsigned int					effective_precision_ns;
	unsigned int					current_precision_s;
	unsigned int					current_precision_ns;
	unsigned int					time_stamp_s;
	unsigned int					time_stamp_ns;
}gmp_gmph_ptpemh_t;






//////////////////////////////////////////////////////////////////////////
//memh
typedef struct gmp_gmph_memh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned char					media_type;
	unsigned char					packet_type;
	unsigned int					field_id;
	unsigned int					packet_no;
	unsigned int					body_size;
	unsigned int					time_stamp_s;									//表示格林尼治时间1970-1-1 0:0:0开始到当前经过的秒s
	unsigned int					time_stamp_ns;									//表示当前秒内经过的纳秒ns
}gmp_gmph_memh_t;




//////////////////////////////////////////////////////////////////////////
//cpqemh
typedef struct gmp_gmph_cpqemh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned int					command;
	unsigned int					length;
	unsigned int					packet_no;
	unsigned int					status;
	char							session_id[GMP_GMPH_SEMH_SESSION_ID_LEN];
	unsigned char					media_type;
	unsigned char					frame_rate;
	unsigned int					width;
	unsigned int					height;
	unsigned char					group_id;
	unsigned char					rows;
	unsigned char					columns;
	char							device_id[GMP_GMPH_CPQMH_DEVICE_ID_LEN];			//表示设备的编号id
}gmp_gmph_cpqemh_t;




//////////////////////////////////////////////////////////////////////////
//sdsemh
typedef struct gmp_gmph_sdsemh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned char					start_flags;
	unsigned char					header_length;
	unsigned short					domain_flags;
	unsigned short					function_code;
	unsigned short					data_length;
}gmp_gmph_sdsemh_t;


typedef struct gmp_gmph_daemh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned char					start_flags;
	unsigned char					header_length;
	unsigned short					domain_flags;
	unsigned short					function_code;
	unsigned short					data_length;
	unsigned short					dev_type;
	unsigned short					desp;
}gmp_gmph_daemh_t;



//////////////////////////////////////////////////////////////////////////
//uemh
typedef struct gmp_gmph_uemh_s
{
	gmp_gmph_bmh_t					bmh;
	unsigned char					start_flags;
	unsigned char					update_type;
	unsigned char					content_type;
	unsigned int					content_length;
}gmp_gmph_uemh_t;

//定义uemh中的content type的类型数据
typedef enum gmp_gmph_uemh_content_type_enum
{
	gmp_gmph_uemh_content_type_none = 0,					//表示预留类型
	gmp_gmph_uemh_content_type_normal = 0x01,				//表示固定长度
	gmp_gmph_uemh_content_type_gmf = 0x02,					//表示gmf格式
}gmp_gmph_uemh_content_type;



/************************************************************************/



#pragma pack()



#define	CSS_GMP_GMPH_BMH_LEN				sizeof(gmp_gmph_bmh_t)
#define	CSS_GMP_GMPH_SEMH_LEN				sizeof(gmp_gmph_semh_t)
#define	CSS_GMP_GMPH_PTPEMH_LEN				sizeof(gmp_gmph_ptpemh_t)
#define	CSS_GMP_GMPH_MEMH_LEN				sizeof(gmp_gmph_memh_t)
#define	CSS_GMP_GMPH_CPQEMH_LEN				sizeof(gmp_gmph_cpqemh_t)
#define CSS_GMP_GMPH_SDSEMH_LEN				sizeof(gmp_gmph_sdsemh_t)
#define CSS_GMP_GMPH_DAEMH_LEN				sizeof(gmp_gmph_daemh_t)





#endif






