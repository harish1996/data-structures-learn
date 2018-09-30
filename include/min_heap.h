#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct a_min_heap{
	void *array;
	size_t size;
	size_t capacity;
	size_t element_size;
	int (*comparator)(void *,int,int);
} a_heap_t;

int initHeap( a_heap_t *heap, size_t element_size, int (*comparator)(void*, int, int) );

int swap( a_heap_t *heap, int i, int j );

int swapUp( a_heap_t *heap, int k );

int swapDown( a_heap_t *heap, int k );

int ExtractMax( a_heap_t *heap, void *element );

int insert( a_heap_t *heap, void *x );

void printHeap( a_heap_t *heap );
#endif
