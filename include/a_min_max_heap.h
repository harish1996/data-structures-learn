#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct array_min_max_heap {
	void *array;
	size_t size;
	size_t capacity;
	size_t element_size;
	int (*comparator)( void*, void* );
}a_minmax_heap_t;

int init_minmax_heap( a_minmax_heap_t *heap, size_t element_size, int (*compare)(void*,void*) );

int ExtractMin_minmax( a_minmax_heap_t *heap, void *element );

int FindMin_minmax( a_minmax_heap_t *heap, void *element );

int FindMax_minmax( a_minmax_heap_t *heap, void *element );

int ExtractMax_minmax( a_minmax_heap_t *heap, void *element );

int insert_minmax_heap( a_minmax_heap_t *heap, void *x );

void print_minmax_heap( a_minmax_heap_t *heap, int index, int indent, void (*print)(void*) );
