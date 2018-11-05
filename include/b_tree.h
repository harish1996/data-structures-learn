#define ORDER 7
typedef int DATA;
#include <stdlib.h>

typedef struct treenode{
	int count;
	DATA d[ORDER];
	int link[ORDER];
	int parent;
} btree;

typedef struct b_tree_info{
	btree *tree;
	int size;
	int capacity;
	int (*comparator)( DATA, DATA );
} btree_t;

int init_btree( btree_t *tree, int (*comparator)( DATA, DATA ) );

int insert_array( DATA *array, DATA b, int filled, int (*comparator)( DATA, DATA ) );

