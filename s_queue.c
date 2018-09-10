#include "include/s_queue.h"

int s_queue_create_queue( s_queue_t *queue, size_t element_size )
{
	if( create_stack( &(queue->enqueue_stack) , element_size ) )
		return create_stack( &(queue->dequeue_stack) , element_size );
	else
		return 0;
}

int s_enqueue( s_queue_t *queue, void *object )
{
	if( push( &(queue->enqueue_stack) , object ) ){
		return 1;
	}
	else
		return 0;
}

int s_dequeue( s_queue_t *queue, void *object )
{
	int size;
	int poured_size;

	if( stack_size( &(queue->dequeue_stack) ) == 0 ){
		/* 
		 * BUG: if pour stack fails with lesser number of elements, 
		 * queue is corrupted. Failsafe API required in stack.
		 */
		size = stack_size( &(queue->enqueue_stack) );
		poured_size = pour_stack( &(queue->dequeue_stack) , &(queue->enqueue_stack) , size );
		if( poured_size != size ){
			pour_stack( &(queue->enqueue_stack) , &(queue->dequeue_stack) , poured_size );
			return -1;
		}
	}

	return pop( &(queue->dequeue_stack) , object );
}



