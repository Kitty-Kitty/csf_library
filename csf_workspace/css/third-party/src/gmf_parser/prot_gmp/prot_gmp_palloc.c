





#include "prot_gmp_palloc.h"







gmp_pool_t *gmp_create_pool(size_t size)
{
	gmp_pool_t			*p = NULL;





	p = (gmp_pool_t*)gmp_memalign(GMP_POOL_ALIGNMENT, size);
    if (p == NULL) {
        return NULL;
    }

    p->d.last = (unsigned char *) p + sizeof(gmp_pool_t);
    p->d.end = (unsigned char *) p + size;
    p->d.next = NULL;
    p->d.failed = 0;

    size = size - sizeof(gmp_pool_t);

    p->max = (size < GMP_MAX_ALLOC_FROM_POOL) ? size : GMP_MAX_ALLOC_FROM_POOL;

    p->current = p;
    p->chain = NULL;
    p->large = NULL;

    return p;
}


void gmp_reset_pool(gmp_pool_t *pool)
{
	gmp_pool_t				*p;
	gmp_pool_large_t		*l;




	// 释放所有大块内存
	for (l = pool->large; l; l = l->next) {
		if (l->alloc) {
			gmp_free(l->alloc);
		}
	}

	pool->large = NULL;

	// 初始化所有普通内存（所有内存池的last重新指向ngx_pool_t结构体后面 ）
	for (p = pool; p; p = p->d.next) {
		p->d.last = (unsigned char *) p + sizeof(gmp_pool_t);
	}
}


void gmp_destroy_pool(gmp_pool_t *pool)
{
	gmp_pool_t          *p, *n;
    gmp_pool_large_t    *l;




	// 释放所有的大块内存
    for (l = pool->large; l; l = l->next) {
        if (l->alloc) {
            gmp_free(l->alloc);
        }
    }

	// 释放所有普通内存
    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
         if (n == NULL) {
             break;
         }
    }

    for (p = pool, n = pool->d.next; /* void */; p = n, n = n->d.next) {
        gmp_free(p);

        if (n == NULL) {
            break;
        }
    }
}


void *gmp_palloc_block(gmp_pool_t *pool, size_t size)
{
	unsigned char		*m;
	size_t			psize;
	gmp_pool_t			*p, *new_p, *current;





	psize = (size_t) (pool->d.end - (unsigned char *) pool);

	m = (unsigned char*)gmp_memalign(GMP_POOL_ALIGNMENT, psize);
	if (m == NULL) {
		return NULL;
	}

	new_p = (gmp_pool_t *) m;

	new_p->d.end = m + psize;
	new_p->d.next = NULL;
	new_p->d.failed = 0;

	m += sizeof(gmp_pool_data_t);
	new_p->d.last = m + size;

	current = pool->current;

	for (p = current; p->d.next; p = p->d.next) {
		if (p->d.failed++ > 4) {
			current = p->d.next;
		}
	}

	p->d.next = new_p;

	pool->current = current ? current : new_p;

	return m;
}


void *gmp_palloc_large(gmp_pool_t *pool, size_t size)
{
	void				*p;
	size_t         n;
	gmp_pool_large_t	*large;




	p = gmp_alloc(size);
	if (p == NULL) {
		return NULL;
	}

	n = 0;

	for (large = pool->large; large; large = large->next) {
		if (large->alloc == NULL) {
			large->alloc = p;
			return p;
		}

		if (n++ > 3) {
			break;
		}
	}

	large = (gmp_pool_large_t*)gmp_palloc(pool, sizeof(gmp_pool_large_t));
	if (large == NULL) {
		gmp_free(p);
		return NULL;
	}

	large->alloc = p;
	large->next = pool->large;
	pool->large = large;

	return p;
}


/*
	从内存池分配内存，并对齐
*/
void *gmp_palloc(gmp_pool_t *pool, size_t size)
{
    unsigned char		*m;
    gmp_pool_t			*p;





    if (size <= pool->max) {

        p = pool->current;

        do {
			m = gmp_align_ptr(p->d.last, GMP_ALIGNMENT);

            if ((size_t) (p->d.end - m) >= size) {
                p->d.last = m + size;

                return m;
            }

            p = p->d.next;

        } while (p);

        return gmp_palloc_block(pool, size);
    }

	/*大内存尺寸则分配大块内存并添加到
	大块内存链表
	*/
    return gmp_palloc_large(pool, size);
}
























