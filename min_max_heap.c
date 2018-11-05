#include "include/a_min_max_heap.h"

static unsigned int odd_interleave,even_interleave;

static void gen_interleaves()
{
	char *word;
	int size = sizeof(unsigned int);
	
	word = (char *)&odd_interleave;
	for(int i = 0; i < size; i++ )
		*(word+i)=0xAA;
	word = (char *)&even_interleave;
	for( int i = 0; i < size; i++ )
		*(word+i)=0x55;
}

int init_minmax_heap( a_minmax_heap_t *heap, size_t element_size, int (*compare)(void*,void*) )
{
	if( !heap )
		return -1;
	if( !element_size )
		return -2;
	if( !compare )
		return -3;

	gen_interleaves();
	heap->array = malloc( element_size * 10 );
	if( !heap->array )
		return -4;
	heap->size = 1;
	heap->capacity = 10;
	heap->element_size = element_size;
	heap->comparator = compare;
	return 0;
}

void delete_minmax_heap( a_minmax_heap_t *heap )
{
	if( heap ){
		if( heap->array ){
			free(heap->array);
		}
		heap->size = 0;
		heap->capacity = 0;
	}
}

static int swap( a_minmax_heap_t *heap, int i, int j )
{
	void *ith = ((char*)heap->array + i * heap->element_size );
	void *jth = ((char*)heap->array + j * heap->element_size );

	memcpy( heap->array , ith , heap->element_size );
	memcpy( ith , jth , heap->element_size );
	memcpy( jth , heap->array , heap->element_size );

	return 1;
}

#define ODD_LEVEL  1
#define EVEN_LEVEL 2
static int find_level( unsigned int k )
{
	if( ( k & odd_interleave ) > ( k & even_interleave ) )
		return ODD_LEVEL;
	else
		return EVEN_LEVEL;
}


#define _arr(k) ( arr + ( (k) * heap->element_size ) )
enum positions{
	SELF=0,
	CHILD,
	GRANDCHILD
};

enum max_min{
	MAX=0,
	MIN
};

static int find_extremum_2_levels( a_minmax_heap_t *heap, int k, int *index, int *pos, int max_min )
{
	char *arr = heap->array;
	int indices[6]={ 2*k, 2*k + 1, 4*k, 4*k + 1, 4*k + 2, 4*k + 3 };
	int position[6]={ CHILD,CHILD,GRANDCHILD,GRANDCHILD,GRANDCHILD,GRANDCHILD };
	int first_index,second_index;
	
	if( !heap )
		return -1;
	if( !heap->array )
		return -2;
	if( k<=0 || k >= heap->size )
		return -3;
	if( !index )
		return -4;
	if( !pos )
		return -5;
	if( max_min != MAX && max_min != MIN )
		return -6;
	
	memcpy( _arr(0), _arr(k), heap->element_size );
	*index = k;
	*pos = 0;

	for( int i=0; i<6; i++ ){
		if( indices[i] < heap->size ){
			first_index = max_min == MAX ? indices[i]: *index;
			second_index = max_min == MAX ? *index : indices[i];
			
			if( !heap->comparator( _arr(first_index), _arr(second_index) ) ){
				*index = indices[i];
				*pos = position[i];
			}
		}
		else
			break;
	}

	return 0;
}

static int trickle_down_min( a_minmax_heap_t *heap, int k )
{
	int min_index,min_pos;
	char *arr= heap->array;
	
	if ( find_extremum_2_levels( heap, k, &min_index, &min_pos, MIN ) == 0 ){
		if( min_pos == GRANDCHILD ){
			swap( heap, k, min_index );
			if( !heap->comparator( _arr(min_index), _arr(min_index/2) ) )
				swap( heap, min_index, min_index/2 );
			trickle_down_min(heap, min_index );
		}
		else if( min_pos == CHILD ){
			swap( heap, k, min_index );
		}
	}

	return 0;
}

static int trickle_down_max( a_minmax_heap_t *heap, int k )
{
	int max_index,max_pos;
	char *arr= heap->array;

	if( find_extremum_2_levels( heap, k, &max_index, &max_pos, MAX ) == 0 ){
		if( max_pos == GRANDCHILD ){
			swap( heap, k, max_index );
			if( heap->comparator( _arr(max_index), _arr(max_index/2) ) )
				swap( heap, max_index, max_index/2 );
			trickle_down_max(heap, max_index );
		}
		else if( max_pos == CHILD ){
			swap( heap, k, max_index );
		}
	}
	return 0;
}

static int trickle_down( a_minmax_heap_t *heap, int k )
{
	if( !heap )
		return -1;
	if( k <= 0 || k >= heap->size )
		return -2;
	
	if( find_level( k ) == ODD_LEVEL )
		return trickle_down_min( heap, k );
	else
		return trickle_down_max( heap, k );
}

static int bubble_up_max( a_minmax_heap_t *heap, int k )
{
	char *arr = heap->array;
	
	if( !heap )
		return -1;
	if( k <= 0 || k >= heap->size )
		return -2;
	if( !arr )
		return -3;
	
	if( k/4 >= 0 && !heap->comparator( _arr(k/4), _arr(k) ) ){
		swap( heap, k, k/4 );
		return bubble_up_max( heap, k/4 );
	}

	return 0;
}
	
static int bubble_up_min( a_minmax_heap_t *heap, int k )
{
	char *arr = heap->array;
	
	if( !heap )
		return -1;
	if( k <= 0 || k >= heap->size )
		return -2;
	if( !arr )
		return -3;
	
	if( k/4 >= 0 && heap->comparator( _arr(k/4), _arr(k) ) ){
		swap( heap, k, k/4 );
		return bubble_up_min( heap, k/4 );
	}

	return 0;
}				

static int bubble_up( a_minmax_heap_t *heap, int k )
{
	char *arr = heap->array;
	
	if( !heap )
		return -1;
	if( k<=0 || k >= heap->size )
		return -2;

	if( find_level( k ) == ODD_LEVEL ){
		if( k/2 >= 0 && heap->comparator( _arr(k/2), _arr(k) ) ){
			swap( heap, k, k/2 );
			return bubble_up_min( heap, k/2 );
		}
		else
			return bubble_up_max( heap, k );
	}
	else{
		if( k/2 >= 0 && !heap->comparator( _arr(k/2), _arr(k) ) ){
			swap( heap, k, k/2 );
			return bubble_up_max( heap, k/2 );
		}
		else
			return bubble_up_min( heap, k );
	}
}

int ExtractMin_minmax( a_minmax_heap_t *heap, void *element )
{
	char *arr = heap->array;
	
	if( !heap )
		return -1;
	if( !element )
		return -2;

	if( heap->size > 1 ){
		memcpy( element, _arr(1), heap->element_size );
		swap( heap, 1, heap->size - 1 );
		heap->size -= 1;
		return trickle_down( heap, 1);
	}
	else
		return -3;
}

int FindMin_minmax( a_minmax_heap_t *heap, void *element )
{
	char *arr = heap->array;
	
	if( !heap )
		return -1;
	if( !element )
		return -2;

	if( heap->size > 1 ){
		memcpy( element, _arr(1), heap->element_size );
		return 1;
	}
	else
		return -3;
}

int ExtractMax_minmax( a_minmax_heap_t *heap, void *element )
{
	char *arr = heap->array;
	int max_index;
	
	if( !heap )
		return -1;
	if( !element )
		return -2;

	if( heap->size >= 2 ){
		if( heap->size > 3 ){
			if( heap->comparator( _arr(3), _arr(2) ) )
				max_index = 3;
			else
				max_index = 2;
		}
		else if( heap->size == 3 )
			max_index = 2;
		else if( heap->size == 2 )
			max_index = 1;
			
		memcpy( element, _arr(max_index), heap->element_size );
		swap( heap, max_index, heap->size - 1 );
		heap->size -= 1;
		if( heap->size > 3 )
			return trickle_down( heap, max_index );
		else
			return 1;
	}
	else
		return -3;
}

int FindMax_minmax( a_minmax_heap_t *heap, void *element )
{
	char *arr = heap->array;
	int max_index;
	
	if( !heap )
		return -1;
	if( !element )
		return -2;

	if( heap->size >= 2 ){
		if( heap->size > 3 ){
			if( heap->comparator( _arr(3), _arr(2) ) )
				max_index = 3;
			else
				max_index = 2;
		}
		else if( heap->size == 3 )
			max_index = 2;
		else
			max_index = 1;
		memcpy( element, _arr(max_index), heap->element_size );
		return 1;
	}
	else
		return -3;
}

int insert_minmax_heap( a_minmax_heap_t *heap, void *x )
{
	char *arr= heap->array;
	
	if( !heap )
		return -1;
	if( !x )
		return -2;

	if( heap->size == heap->capacity ){
		heap->array = realloc( heap->array , heap->element_size * heap->capacity * 2 );
		if( !heap->array )
			return -3;
		arr = heap->array;
		heap->capacity = 2 * heap->capacity;
	}
	
	heap->size += 1;
	memcpy( _arr(heap->size-1) , x , heap->element_size );
	return bubble_up( heap , heap->size - 1 );
}

void print_minmax_heap( a_minmax_heap_t *heap, int index, int indent, void (*print)(void*) )
{
	char *arr = heap->array;
	
	for(int i=0;i<indent;i++)
		printf("\t");
	print( _arr(index) );
	if( 2*index < heap->size ){
		print_minmax_heap( heap, 2*index, indent+1, print );
		if( 2*index + 1 < heap->size ){
			print_minmax_heap( heap, 2*index + 1, indent+1, print );
		}
	}
}
