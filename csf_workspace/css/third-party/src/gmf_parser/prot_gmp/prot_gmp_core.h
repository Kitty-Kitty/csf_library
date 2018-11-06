#ifndef	_PROT_GMP_CORE_H_
#define _PROT_GMP_CORE_H_




#define		gmf_version									4003
#define		GMF_VERSION									"V0.4.3"
#define		GMF_VER										"GMF/" GMF_VERSION
#define		GMF_VAR										"GMF"




#define	gmp_cdecl





#define gmp_abs(value)       (((value) >= 0) ? (value) : - (value))
#define gmp_max(val1, val2)  ((val1 < val2) ? (val2) : (val1))
#define gmp_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))





#define	CSS_GMP_BMH_LEN							5					//表示GMP协议基础信息头BMH长度
#define	CSS_GMP_EMH_SEMH_LEN					48					//表示GMP协议会话扩展头SEMH长度
#define	CSS_GMP_EMH_MEMH_LEN					22					//表示GMP协议媒体信息扩展头MEMH长度
#define	CSS_GMP_BMH_GMPV						0x00000001			//表示GMP协议基础信息头BMH中版本号
#define	CSS_GMP_BMH_SEMHT						0x01				//表示GMP协议基础信息头中扩展类型信息中，SEMH类型编码
#define	CSS_GMP_BMH_MEMHT						0x02				//表示GMP协议基础信息头中扩展类型信息中，MEMH类型编码




typedef	struct gmp_chain_s			gmp_chain_t;
typedef struct gmp_pool_s			gmp_pool_t;
typedef struct gmp_gmf_s			gmp_gmf_t;



#include "prot_gmp_std.h"
#include "prot_gmp_chain.h"
#include "prot_gmp_alloc.h"
#include "prot_gmp_palloc.h"
#include "prot_gmp_gmdt.h"
#include "prot_gmp_string.h"





#include "prot_gmp_gmph.h"
#include "prot_gmp_gmf.h"
#include "prot_gmp_print.h"












#endif
















