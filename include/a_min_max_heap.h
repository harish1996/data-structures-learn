#ifndef _A_MIN_MAX_HEAP_H
#define _A_MIN_MAX_HEAP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Min Max Heap
 *
 * @var array Array that stores the heap
 * @var size Size of the heap
 * @var capacity Capacity of the heap
 * @var element_size Size of each element 
 * @var comparator Comparator function of the heap
 */
typedef struct array_min_max_heap {
	void *array;
	size_t size;
	size_t capacity;
	size_t element_size;
	int (*comparator)( void*, void* );
}a_minmax_heap_t;

/**
 * @brief Initialises the min max heap
 * 
 * @param heap Heap instance
 * @param element_size Element size to be stored
 * @param compare Compare function of the heap
 * 
 * @return 0 on success, negative on failure
 */
int init_minmax_heap( a_minmax_heap_t *heap, size_t element_size, int (*compare)(void*,void*) );

/**
 * @brief Deletes the heap
 * 
 * @param heap Heap instance
 */
void delete_minmax_heap( a_minmax_heap_t *heap );

/**
 * @brief Extract Minimum element ( Root of the heap )
 * 
 * @param heap Heap instance
 * @param element Pointer to the location where the extracted data is to
 * 	be stored
 * 
 * @return 0 on success, negative on failure
 */
int ExtractMin_minmax( a_minmax_heap_t *heap, void *element );

/**
 * @brief Find Minimum element ( Root of the heap )
 * 
 * @param heap Heap instance
 * @param element Pointer to the location where the extracted data is to
 * 	be stored
 * 
 * @return 0 on success, negative on failure
 */
int FindMin_minmax( a_minmax_heap_t *heap, void *element );

/**
 * @brief Find Maximum element ( One of the children of the root of the heap )
 * 
 * @param heap Heap instance
 * @param element Pointer to the location where the extracted data is to
 * 	be stored
 * 
 * @return 0 on success, negative on failure
 */
int FindMax_minmax( a_minmax_heap_t *heap, void *element );

/**
 * @brief Extract Maximum element ( One of the children of the root of the heap )
 * 
 * @param heap Heap instance
 * @param element Pointer to the location where the extracted data is to
 * 	be stored
 * 
 * @return 0 on success, negative on failure
 */
int ExtractMax_minmax( a_minmax_heap_t *heap, void *element );

/**
 * @brief Inserts element into the heap
 * 
 * @param heap Heap instance
 * @param x Pointer to the location where the data is stored
 * 
 * @return 0 on success, negative on failure
 */
int insert_minmax_heap( a_minmax_heap_t *heap, void *x );

/**
 * @brief Prints the heap, given a print function
 * 
 * @param heap Heap instance
 * @param index Index to start the heap printing from
 * @param indent Starting indent
 * @param print Print routine for printing the heap
 * 
 */
void print_minmax_heap( a_minmax_heap_t *heap, int index, int indent, void (*print)(void*) );
#endif
