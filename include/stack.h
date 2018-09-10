/**
 * @file stack.h
 * @brief Provides declarations for array based stacks
 *
 * @author Harish
 * @bug None until now
 */

#ifndef _STACK_H
#define _STACK_H

#include <string.h>	/* for memcpy() */
#include <stdlib.h>	/* for malloc() */

/**
 * @brief Array based Stack Data Structure
 */
typedef struct _stack_ {
	void *arr;
	size_t size;
	size_t capacity;
	size_t element_size;
} stack_t;

/**
 * @brief Initialise a stack variable
 *
 * @param stack		The address to the uninitialised stack
 * @param element_size 	The size of each element
 *
 * @returns 1 on success , 0 on failure
 *
 */ 
int create_stack(stack_t * stack, size_t element_size);

/**
 * @brief Push an object pointed by 'object' in the stack referred by
 * 		'stack'
 *
 * Note that the values are copied into the stack structure. For large
 * data types, this is probably not the one you are looking for. Note that
 * changing the source variable does not modify the value in the stack
 *
 * @param stack		Address of the stack object
 * @param object 	Reference to the object to be pushed in the stack
 *
 * @returns 1 on success , 0 on failure ( Unavailable memory )
 */
int push(stack_t * stack, void *object);

/**
 * @brief Pop the last pushed object from the stack and copy to address
 * 	pointed by 'object'.
 *
 * Note that address pointed should be allocated for the size of the variable
 * length. I am not responsible for Segmentation faults due to that.
 *
 * @param stack 	Address of the stack object
 * @param object 	Reference to the address where popped object is stored
 *
 * @returns 1 on success , 0 on failure ( Empty Stack )
 */
int pop(stack_t * stack, void *object);

/**
 * @brief Deletes the stack and frees all memory
 *
 * Deletes the stack without any warning.
 *
 * @param stack 	Address of the stack object
 *
 * @returns 1 on success , 0 on failure ( Uninitialised Stack )
 */
int delete_stack(stack_t * stack);

/**
 * @brief Pours one stack into another stack
 *
 * Pours the stacks contents, like a glass of water into another glass. Top of the
 * first stack goes to the bottom of the destination stack.
 *
 * @param dest_stack 	Address of the destination stack object
 * @param src_stack 	Address of the source stack object
 * @param elements	Number of stack elements to pour.
 *
 * @returns number of elements poured.
 */
int pour_stack(stack_t * dest_stack, stack_t * src_stack, size_t elements);

/**
 * @brief Returns current stack size
 *
 * @param stack 	Address of the stack object
 *
 * @returns Current stack size.
 */
size_t stack_size(stack_t * stack);

#endif
