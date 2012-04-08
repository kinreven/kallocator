/*
 * File:	kallocator.h
 * Author:	Kevin Ren <kinreven@gmail.com>
 * Brief:	This file is a API list of Simple memory allocator based on bitmap.
 *
 * $Date:: 2011-12-10 23:26:55 #$
 *
 */

#include "typedef.h"

#ifndef __KALLOCATOR_H__
#define __KALLOCATOR_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void * heap_t;

heap_t kallocator_heap_new(size_t size);
void * kallocator_alloc(heap_t *heap, size_t size);
void   kallocator_free(heap_t *heap, void *p, size_t size);
void   kallocator_heap_del(heap_t *heap);

#ifdef __cplusplus
}
#endif

#endif /*__KALLOCATOR_H__*/ 
