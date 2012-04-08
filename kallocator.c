/*
 * File:	kallocator.c
 * Author:	Kevin Ren <kinreven@gmail.com>
 * Brief:	This file is a implemention of Simple memory allocator based on bitmap.
 *
 * $Date:: 2011-12-10 23:26:55 #$
 *
 */

#include <string.h>
#include "debug.h"
#include "kallocator.h"


#define MEM_BLOCK_BIT_SIZE	4
#define MEM_BLOCK_SIZE	(1 << MEM_BLOCK_BIT_SIZE)
#define ROUND_UP_BIT(x, y)	((((x) + (y) - 1) >> (y)) << (y))

#define MEM_UNUSE	0
#define MEM_USED	1

typedef struct mem_heap_s {
	size_t bitmap_size;
	uint8_t *bitmap_area;
	size_t heap_size;
	uint8_t (*heap_area)[MEM_BLOCK_SIZE];
} mem_heap_t;

static char set_bit_mask[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
static char cls_bit_mask[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

static void __bitmap_set(char *pb, unsigned int off, unsigned int num)
{
	unsigned int bit = off % 8;
	pb += off / 8;

	while (num--) {
		(*pb) |= set_bit_mask[bit];
		if (bit++ == 7) {
			bit = 0;
			pb++;
		}
	}
}

static void __bitmap_cls(char *pb, unsigned int off, unsigned int num)
{
	unsigned int bit = off % 8;
	pb += off / 8;

	while (num--) {
		(*pb) &= cls_bit_mask[bit];
		if (bit++ == 7) {
			bit = 0;
			pb++;
		}
	}
}

#if __DEBUG
static void __heap_dump(mem_heap_t *pheap)
{
	char *p = pheap->bitmap_area;
	unsigned int size = pheap->bitmap_size;
	unsigned int i;

	while (size--) {
		for (i = 0; i < 8; i++) {
			printf("%c", ((*p) & set_bit_mask[i]) ? '1' : '0');
		}
		if (size % 8 == 0) {
			printf("\n");
		}
		else {
			printf(" ");
		}
		p++;
	}
	printf("\n");
}
#endif

heap_t kallocator_heap_new(size_t size)
{
	mem_heap_t *pheap = NULL;
	size_t bitmap_size;
	size_t heap_size;

	if (size) {
		heap_size = ROUND_UP_BIT(size, MEM_BLOCK_BIT_SIZE);
		bitmap_size = ROUND_UP_BIT(heap_size >> MEM_BLOCK_BIT_SIZE, 3) >> 3;
		dbg_printf("heap_size[%u], bitmap_size[%u]\n", heap_size, bitmap_size);
		pheap = (mem_heap_t *)malloc(sizeof(mem_heap_t) + bitmap_size + heap_size);
		if (pheap != NULL) {
			pheap->bitmap_size = bitmap_size;
			pheap->bitmap_area = (uint8_t *)((void *)pheap + sizeof(mem_heap_t));
			memset(pheap->bitmap_area, MEM_UNUSE, pheap->bitmap_size);
			pheap->heap_size = heap_size;
			pheap->heap_area = (uint8_t (*)[MEM_BLOCK_SIZE])(pheap->bitmap_area + pheap->bitmap_size);
		}
	}

	return (heap_t)pheap;
}

void * kallocator_alloc(heap_t *heap, size_t size)
{
	mem_heap_t *pheap;
	uint8_t (*p)[MEM_BLOCK_SIZE] = NULL;
	uint8_t *pbitmap;
	uint32_t cnt_bit;
	uint32_t bit;
	uint32_t num_block;
	uint32_t off_block;

	dbg_assert(heap);

	pheap = (mem_heap_t *)heap;
	if (size && (size <= pheap->heap_size)) {
		num_block = ROUND_UP_BIT(size, MEM_BLOCK_BIT_SIZE) >> MEM_BLOCK_BIT_SIZE;
		pbitmap = pheap->bitmap_area;
		cnt_bit = bit = 0;
		off_block = 0;

		while (pbitmap != (uint8_t *)pheap->heap_area) {
			if ((*pbitmap & set_bit_mask[bit]) == MEM_UNUSE) {
				cnt_bit++;
			}
			else {
				cnt_bit = 0;
			}

			if (cnt_bit == num_block) {
				off_block = ((pbitmap - pheap->bitmap_area) << 3) + bit + 1 - num_block;
				__bitmap_set(pheap->bitmap_area, off_block, num_block);
				p = pheap->heap_area + off_block;

				break;
			}

			if (bit++ == 7) {
				bit = 0;
				pbitmap++;
			}
		}
	}
#if __DEBUG
	__heap_dump(pheap);
#endif

	return (void *)p;
}

void   kallocator_free(heap_t *heap, void *p, size_t size)
{
	mem_heap_t *pheap;
	uint32_t num_block;
	uint32_t off_block;

	dbg_assert(heap);

	pheap = (mem_heap_t *)heap;
	if ((p != NULL) && size) {
		num_block = ROUND_UP_BIT(size, MEM_BLOCK_BIT_SIZE) >> MEM_BLOCK_BIT_SIZE;
		off_block = ((uint8_t (*)[MEM_BLOCK_SIZE])p - pheap->heap_area);

		__bitmap_cls(pheap->bitmap_area, off_block, num_block);
	}
#if __DEBUG
	__heap_dump(pheap);
#endif
}

void   kallocator_heap_del(heap_t *heap)
{
	dbg_assert(heap != NULL);

	free(heap);
	dbg_printf("%x", heap);
}
