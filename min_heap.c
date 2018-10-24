#include "include/min_heap.h"

int initHeap( a_heap_t *heap, size_t element_size, int (*comparator)(void*, int, int) )
{
	if( !heap )
		return -1;
	if( element_size == 0 )
		return -2;
	if( !comparator )
		return -3;

	heap->array = malloc( 10 * element_size );
	if( !heap->array )
		return -4;

	heap->capacity = 10;
	heap->size = 1;
	heap->element_size = element_size;
	heap->comparator = comparator;
	return 1;
}


int swap( a_heap_t *heap, int i, int j )
{
	void *ith = ((char*)heap->array + i * heap->element_size );
	void *jth = ((char*)heap->array + j * heap->element_size );

	memcpy( heap->array , ith , heap->element_size );
	memcpy( ith , jth , heap->element_size );
	memcpy( jth , heap->array , heap->element_size );

	return 1;
}

int swapUp( a_heap_t *heap, int k )
{
	if( !heap )
		return -1;
	if( k > heap->size )
		return -2;
	if( k < 1 )
		return -3;

	while( k>1 && heap->comparator( heap->array , k , k/2 ) ){
		swap( heap , k , k/2 );
		k = k/2;
	}

	return 1;
}

int swapDown( a_heap_t *heap, int k )
{
	int min;

	if( !heap )
		return -1;
	if( k > heap->size )
		return -2;
	if( k < 1 )
		return -3;

	if( 2*k >= heap->size )
		return 1;

	if( heap->comparator( heap->array , k , 2*k ) )
		min = k;
	else
		min = 2*k;

	if( 2*k + 1 < heap->size && !heap->comparator( heap->array , min , 2*k + 1 ) )
		min = 2*k + 1;
	
	if( min != k ){
		swap( heap , k , min );
		return swapDown( heap , min );
	}
	else
		return 1;
}

int ExtractMin( a_heap_t *heap, void *element )
{
	if( !heap )
		return -1;
	if( !element )
		return -2;

	if( heap->size > 1 ){
		memcpy( element , (char*)heap->array + heap->element_size , heap->element_size );
		swap( heap , 1 , heap->size - 1 );
		heap->size -= 1;
		return swapDown( heap , 1 );	
	}
	else
		return -3;
}


int insert( a_heap_t *heap, void *x )
{
	if( !heap )
		return -1;
	if( !x )
		return -2;

	if( heap->size == heap->capacity ){
		heap->array = realloc( heap->array , heap->element_size * heap->capacity * 2 );
		if( !heap->array )
			return -3;
		heap->capacity = 2 * heap->capacity;
	}

	heap->size += 1;
	memcpy( (char*)heap->array + ( ( heap->size - 1 ) * heap->element_size ) , x , heap->element_size );
	swapUp( heap , heap->size - 1 );
}
/*
int compareInt( void *array , int firstIndex , int SecondIndex )
{
	int *arr = (int*) array;

	if( !array )
		return -1;

	if( arr[firstIndex] > arr[SecondIndex] )
		return 1;
	else
		return 0;
}

int main()
{
	int a[]={1,6,4,5,7,4,5,9,6,7,23,56,43,76,45,33,2,7,54,91,23,54,65,3,2,8,-5,-10,-50};

	a_heap_t heap;
	initHeap( &heap , sizeof(int) , compareInt );
	int temp;

	for(int i=0; i< sizeof(a)/sizeof(a[0]); i++ ){
		insert( &heap , &a[i] );
	}

	//printHeap( &heap );
	//printf("\n\n");
	while( ExtractMax( &heap , &temp ) >= 0 ){
		//printHeap( &heap );
		//printf("\n\n");
		printf(" %d\n",temp );
	}
}
*/
