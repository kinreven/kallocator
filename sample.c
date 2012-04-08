#include "kallocator.h"

void test(heap_t heap, size_t size)
{
	char *p;
	size_t l = rand() % size + 1;

	p = kallocator_alloc(heap, l);
	if (p) {
		test(heap, size);
	}
	else {
		return ;
	}
	kallocator_free(heap, p, l);
	test(heap, size);
}

int main(int argc, char **argv)
{
	heap_t heap;
	char *p1;
	char *p2;
	char *p3;
	size_t l1 = 128;
	size_t l2 = 256;
	size_t l3 = 512;

	heap = kallocator_heap_new(4096);

	p1 = kallocator_alloc(heap, l1);
	p2 = kallocator_alloc(heap, l2);
	p3 = kallocator_alloc(heap, l3);

	kallocator_free(heap, p1, l1);
	kallocator_free(heap, p2, l2);
	kallocator_free(heap, p3, l3);

	p1 = kallocator_alloc(heap, 0);
	p2 = kallocator_alloc(heap, 1024);
	p3 = kallocator_alloc(heap, 128);

	kallocator_free(heap, p1, 0);
	kallocator_free(heap, p2, 1024);
	kallocator_free(heap, p3, 128);

	srand((int)time(0));
	test(heap, 4096);

	kallocator_heap_del(heap);

	return 0;
}
