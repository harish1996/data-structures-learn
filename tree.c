#include "include/tree.h"

#define LEFT_CHILD(i) ( 2 * i) + 1
#define RIGHT_CHILD(i) ( 2 * i ) + 2

typedef struct tree{
	void *data;
	struct tree *right;
	struct tree *left;
} tree_t;

int init_tree(tree_t *root)
{
	root->data = NULL;
	root->right = NULL;
	root->left = NULL;
	return 1;
}

int construct_tree(tree_t *root,int *array,int indexStart,int arraySize)
{
	if( indexStart >= arraySize ){
		return -1;
	}
	root->data = array[indexStart];
