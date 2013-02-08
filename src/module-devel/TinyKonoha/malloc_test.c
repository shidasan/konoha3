#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char HEAP[1024];
#define HEAP_SIZE 1024

#include "allocate.h"

void test0()
{
	heap_init();
	void *ptr = tiny_malloc(12);
	tiny_free(ptr);
	void *_ptr = tiny_malloc(10);
	assert(ptr == _ptr);
}


void main(int argc, char **argv)
{
	test0();
}
