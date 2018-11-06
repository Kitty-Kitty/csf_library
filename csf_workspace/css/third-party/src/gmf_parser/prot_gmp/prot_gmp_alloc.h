/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:alloc defined

**************************************************************************/

#ifndef _PROT_GMP_ALLOC_H_
#define _PROT_GMP_ALLOC_H_




#include "prot_gmp_core.h"






#define		gmp_free		free

#if defined(WIN32)

#define		gmp_align_ptr(p, a)                                                   \
	(unsigned char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#else


//������Ҫע��32λ��64λ���������32λ��int �� long����32Ϊ���ȣ������64λ��long��64λ������ת��Ϊ���ֽ��м���ʱҲҪע��������
#define		gmp_align_ptr(p, a)                                                   \
	(unsigned char *) (((unsigned long) (p) + ((unsigned long) a - 1)) & ~((unsigned long) a - 1))

#endif
#define		GMP_ALIGNMENT   sizeof(unsigned long)






#if defined(__cplusplus)
extern "C"{
#endif


void *gmp_memalign(size_t alignment, size_t size);
void *gmp_alloc(size_t size);


#if defined(__cplusplus)
};
#endif





#endif /* _PROT_GMP_PALLOC_H_ */










