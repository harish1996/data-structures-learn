#include "include/b_tree.h"

int init_btreenode( btree *node, int parent )
{
	if( !node )
		return -1;

	node->count = 0;
	for( int i=0; i<ORDER; i++ )
		node->link[i] = -1;
	node->parent = parent;
	return 0;
}

int init_btree( btree_t *tree, int (*comparator)( DATA, DATA ) )
{
	if( !tree )
		return -1;

	tree->tree = malloc( 10 * sizeof(btree) );
	if( !tree->tree )
		return -3;

	tree->size = 1;
	tree->capacity = 10;

	if( init_btreenode( tree->tree, -1 ) != 0 )
	       return -2;
		
	tree->comparator = comparator;

	return 0;
}

int insert_array( DATA *array, DATA b, int filled, int (*comparator)( DATA, DATA ) )
{
	int i=filled;
	char status = 0;

	if( !array )
		return -1;
	if( filled > ORDER )
		return -2;
	if( !comparator )
		return -3;


	while( 1 ){

		if( i == 0 ){
			array[0] = b;
			return 0;
		}

		status = comparator( array[i-1], b );
		if( status > 0 )
			array[i] = array[ i-1 ];
		else if( status == 0 )
			return 1;
		else{
			array[i] = b;
			break;
		}
		i--;
	}

	return 0;
}

int create_btree_node( btree_t *descr, int *link, int parent )
{
	if( !descr )
		return -1;
	if( !link )
		return -2;
	if( parent <= 0 )
		return -3;



int insert( btree_t *descr, btree *tree, DATA d )
{
	int ret;
	
	if( !descr )
		return -4;
	if( !tree )
		return -1;
	if( !d )
		return -2;

	if( tree.link[0] == -1 ){

		if( tree.count < ORDER ){
			ret = insert_array( tree.d, d, tree.count, descr->comparator );
			switch( ret ){
				case 1:
					return 1;
					break;
				case 0:
					tree.count += 1;
					return 0;
					break;
				default:
					return -3;
			}
		}

		if( tree.count == ORDER ){
			ret = create_btree_node( &tree.link[0], 









