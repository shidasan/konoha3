#include <stdio.h>
#include "allocate.h"
int main(int argc, char *args[])
{
	void *ptr0 = NULL;
	void *ptr1 = NULL;
	heap_init();
	size_t i = 0;
	ptr1 = malloc(10);
	void *ptr2 = malloc(100);
	free(ptr1);
	for (; i < 100000; i++) {
		free(ptr2);
		ptr2 = malloc(100);
		ptr0 = malloc(10);
		ptr1 = malloc(10);
		free(ptr0);
		free(ptr1);
	}
	free(ptr2);
	fprintf(stderr, "%zd\n", header_global->size);
}
