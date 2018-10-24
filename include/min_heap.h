#ifndef _MIN_HEAP_H
#define _MIN_HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Array based min heap
 */
typedef struct a_min_heap{
	void *array;
	size_t size;
	size_t capacity;
	size_t element_size;
	int (*comparator)(void *,int,int);
} a_heap_t;

/**
 * @brief Initialises the heap data structure 
 *
 * @param heap Heap instance
 * @param element_size Element size of the elements in the heap
 * @param comparator Function which does the comparisons
 * @return 1 in success , negative on failure
 */
int initHeap( a_heap_t *heap, size_t element_size, int (*comparator)(void*, int, int) );

/**
 * @brief Swaps two indices in the heap array
 *
 * @param heap Heap instance
 * @param i Index of the first element
 * @param j Index of the second element
 * @return 1 on success
 */
int swap( a_heap_t *heap, int i, int j );

/**
 * @brief Swaps the particular element up to the actual position
 *
 * @param heap Heap instance
 * @param k index of the value
 *
 * @return 1 on success
 */
int swapUp( a_heap_t *heap, int k );

/**
 * @brief Swaps the particular element down to the actual position
 *
 * @param heap Heap instance
 * @param k index of the value
 *
 * @return 1 on success
 */
int swapDown( a_heap_t *heap, int k );

/**
 * @brief Extracts the minimum element ( i.e. top most element ) from the heap
 *
 * The mistake in naming is regretted
 *
 * @param heap Heap instance
 * @param element Address to the variable where the extracted value is to be stored
 * @return 1 on success
 */
int ExtractMin( a_heap_t *heap, void *element );

/**
 * @brief Inserts an element into  the heap
 *
 * @param heap Heap instance
 * @param x Reference to the element to be inserted
 * @return 1 on success
 */
int insert( a_heap_t *heap, void *x );

/**
 * @brief Helper function to visualise contents of the heap
 *
 * @param heap Heap instance
 */
void printHeap( a_heap_t *heap );
#endif
