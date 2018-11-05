/**
 * @file s_queue.h
 * @brief Stack Based Queue Data Structure. 
 *
 * As it is difficult to create an array based expanding queue directly.
 * This is based on two stacks, an enqueue stack and a dequeue stack, which
 * can be poured into each other. Average case cost = O(1)
 *
 * @author Harish
 * @bug Chance of queue corruption if `pour_stack` fails after pouring a non zero
 * but not entire stack.
 * @bug Both Stacks may seperately hit full size, which may cause it to return error.
 */
#ifndef _S_QUEUE_H
#define _S_QUEUE_H

#include "stack.h" /* For Stacks */

/**
 * @brief Stack based queue
 */
typedef struct s_queue{
	stack_t enqueue_stack;	
	stack_t dequeue_stack;
}s_queue_t;

/**
 * @brief Create Stack Based Queue
 *
 * Creates Queue with requested element size
 *
 * @param queue Queue structure to be initialised
 * @param element_size Size of each element
 *
 * @return 1 on success , 0 on failure
 */
int s_queue_create_queue( s_queue_t *queue, size_t element_size );

/**
 * @brief Enqueue
 *
 * Enqueue element
 *
 * @param queue Queue descriptor
 * @param object Object to be enqueued
 *
 * @return 1 on success , 0 on failure ( Stack push failure )
 */
int s_enqueue( s_queue_t *queue, void *object );

/**
 * @brief Add to front
 *
 * Adds an element in the front of the queue itself instead of at the back ( VIP pass )
 *
 * @param queue Queue Descriptor
 * @param object Object to be enqueued
 *
 * @return 1 on success , 0 on failure ( Stack push failure )
 */
int s_add_to_front( s_queue_t *queue, void *object );

/**
 * @brief Dequeue
 *
 * Dequeue element from the queue
 *
 * @param queue Queue descriptor
 * @param object Object where the dequeued element will be placed
 *
 * @bug Chance of queue corruption if `pour_stack` fails after pouring a non zero
 * but not entire stack.
 *
 * @return 1 on success , 0 on Stack pop failure , -1 on Stack pour failure
 */
int s_dequeue( s_queue_t *queue, void *object );

#endif
