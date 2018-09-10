#include "include/stack.h"

int create_stack(stack_t * stack, size_t element_size)
{
	stack->arr = malloc(element_size * 10);
	if (!stack->arr)
		return 0;
	stack->size = 0;
	stack->capacity = 10;
	stack->element_size = element_size;
	return 1;
}

int push(stack_t * stack, void *object)
{
	if (stack->size >= stack->capacity) {
		stack->arr =
		    realloc(stack->arr,
			    stack->element_size * 2 * stack->capacity);
		if (!stack->arr)
			return 0;
		stack->capacity = 2 * stack->capacity;
	}

	memcpy((((__uint8_t *) stack->arr) +
		(stack->size * stack->element_size)), object,
	       stack->element_size);

	stack->size += 1;
	return 1;
}

int pop(stack_t * stack, void *object)
{
	if (stack->size == 0)
		return 0;
	if (!object)
		return -1;

	stack->size -= 1;

	memcpy(object,
	       (((__uint8_t *) stack->arr) +
		(stack->size * stack->element_size)), stack->element_size);

	return 1;
}

int delete_stack(stack_t * stack)
{
	if (!stack)
		return 0;
	if (!stack->arr)
		return 0;

	free(stack->arr);

	stack->size = 0;
	stack->capacity = 0;
	stack->element_size = 0;


	return 1;
}

int pour_stack(stack_t * dest_stack, stack_t * src_stack, size_t elements)
{
	void *temp = malloc(src_stack->element_size);

	for(int i=0; i < elements; i++){
		if( pop(src_stack, temp) == 1 ){
			push(dest_stack, temp);
		}
		else
			return i;
	}

	return elements;
}

size_t stack_size(stack_t * stack)
{
	return stack->size;
}
