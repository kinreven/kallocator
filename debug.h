/*
 * File:	debug.h
 * Author:	Kevin Ren <kinreven@gmail.com>
 * Brief:	This file is a common debug function definiton header file.
 *
 * $Date:: 2011-12-10 23:28:14 #$
 *
 */

#include <stdio.h>
#include <assert.h>

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __DEBUG
#define fix_puts()					printf("[%5d]@%s ", __LINE__, __func__);
#define dbg_printf(str, args...)	do {\
										fix_puts();\
										printf(str, ##args);\
									} while (0);

#define dbg_assert(x)				do {\
										if (!(x)) {\
											fix_puts();\
											puts("\""#x"\"\n");\
											assert(0);\
										}\
									} while (0);

extern inline void * __smalloc(size_t x);
extern inline void __sfree(void *p);

#define smalloc(x)					__smalloc(x);
#define sfree(p)					__sfree(p); p = NULL;

#else
#define dbg_printf(str, args...)			
#define dbg_assert(x)				

#define smalloc(x)					malloc(x);
#define sfree(p)					if (p != NULL) {free(p); p = NULL;}

#endif /*__DEBUG*/

#endif /*__DEBUG_H__*/
