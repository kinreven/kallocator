/*
 * File:	safemem.c
 * Author:	Kevin Ren <kinreven@gmail.com>
 * Brief:	This file is a simlply implement of memory safely alloc and free.
 *
 * $Date:: 2011-12-10 23:28:14 #$
 *
 */

#include <assert.h>
#include "typedef.h"

#define __MAGIC_NUM		0x55aa55aaUL
	
inline void * __smalloc(size_t x)
{
	void *p = NULL;

	p = malloc(x + 8);
	if (p != NULL) {
		*(uint32_t *)p = x;
		*(uint32_t *)(p + 4 + x) = __MAGIC_NUM;
	}

	return (p + 4);
}

inline void __sfree(void *p)
{
	if (p != NULL) {
		assert(*(uint32_t *)(p + *(uint32_t *)(p - 4)) == __MAGIC_NUM);
		free(p - 4);
	}
}
