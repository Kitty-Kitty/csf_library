

/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:palloc defined

**************************************************************************/



#ifndef _PROT_GMP_PALLOC_H_
#define _PROT_GMP_PALLOC_H_




#include "prot_gmp_core.h"




#define GMP_POOL_ALIGNMENT				16
#define GMP_MAX_ALLOC_FROM_POOL			(16 * 1024)
#define GMP_DEFAULT_POOL_SIZE			(16 * 1024)




typedef	struct gmp_pool_data_s			gmp_pool_data_t;
typedef	struct gmp_pool_large_s			gmp_pool_large_t;




#pragma pack(1)

struct gmp_pool_data_s
{
	unsigned char			*last;
	unsigned char			*end;
	gmp_pool_t				*next;
	int						failed;
};




struct gmp_pool_large_s
{
	void					*alloc;
	gmp_pool_large_t		*next;
};




struct gmp_pool_s
{
	gmp_pool_data_t			d;
	size_t					max;
	gmp_pool_t				*current;
	gmp_chain_t				*chain;
	gmp_pool_large_t		*large;
};
#pragma pack()




#if defined(__cplusplus)
extern "C"{
#endif


gmp_pool_t *gmp_create_pool(size_t size);
void gmp_reset_pool(gmp_pool_t *pool);
void gmp_destroy_pool(gmp_pool_t *pool);



void *gmp_palloc_block(gmp_pool_t *pool, size_t size);
void *gmp_palloc_large(gmp_pool_t *pool, size_t size);
void *gmp_palloc(gmp_pool_t *pool, size_t size);

#if defined(__cplusplus)
};
#endif





#endif /* _PROT_GMP_PALLOC_H_ */










