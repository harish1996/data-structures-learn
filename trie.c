/******************************************
 * 
 *  HELPER FILE FOR CREATING AND USING A TRIE
 *  DATA STRUCTURE
 *
 ******************************************/
#include "include/trie.h"

int init_trie_rootlist( struct llist *list)
{
	return init_list( list );
}

int remove_element_trie(struct llist* trie_root, char *string, void **payload )
{
	struct linked_list *pointer=trie_root->head;
	struct trie *t_node;
	int position=1;
	int ret;

	if(string == NULL) return REM_TRIE_INVSTRING;
	if(*string == '\0') return REM_TRIE_EMPTYSTRING;
	if(trie_root == NULL) return REM_TRIE_INVROOT;
	if( !payload ) return REM_TRIE_INVPAYLOAD;

	while(pointer != NULL){
		t_node = (struct trie*) pointer->object;
		if ( t_node != NULL ){
			if( *string == t_node->value ){
				ret = remove_element_trie( &t_node->nodes_head, &string[1], payload);
				switch(ret){
					case REM_TRIE_SUCCESS:
						t_node->instances--;
						if(!t_node->instances){
							free(t_node);
						}
						ret = remove_link_between(trie_root,position);
						if(ret) return REM_TRIE_FAILURE;
						return REM_TRIE_SUCCESS;
						break;
					case REM_TRIE_FAILURE:
						return REM_TRIE_FAILURE;
						break;
					case REM_TRIE_INVROOT:
						return REM_TRIE_INVROOT;
						break;
					case REM_TRIE_NULLSTRING:
						return REM_TRIE_NULLSTRING;
						break;
					case REM_TRIE_EMPTYSTRING:
						if( t_node->is_end_available >= 1){
							t_node->is_end_available--;
							if(!t_node->is_end_available){
								t_node->instances--;
								*payload = t_node->payload;
								if(!t_node->instances){
									free(t_node);
								}
								ret = remove_link_between(trie_root,position);
								if(ret) return REM_TRIE_FAILURE;
								return REM_TRIE_SUCCESS;
								break;
							}
						}
						else
							return REM_TRIE_INVSTRING;
						break;
					case REM_TRIE_INVSTRING:
						return REM_TRIE_INVSTRING;
						break;
				}
			}
		}
		else{
			return REM_TRIE_FAILURE;
		}
		if( *string < t_node->value){
			return REM_TRIE_INVSTRING;
		}
		else{
			pointer = pointer->next;
			position++;
		}
	}
	return REM_TRIE_INVSTRING;
}


int add_element_trie(struct llist *trie_root, char* string, void *payload)
{
	struct linked_list *pointer= trie_root->head;
	uint8_t position=1;
	struct trie *node;
	int ret;

	if( trie_root == NULL )
		return -1;
	if( *string == '\0' )
		return -2;
	if( !payload )
		return -4;

	while( pointer != NULL && ((struct trie*)(pointer->object))->value < string[0] ){
		pointer = pointer->next;
		position++;
	}

	if( pointer == NULL ){
		
		node = (struct trie*)malloc(sizeof(struct trie));
		if(!node) return -3;
		node->value = string[0];
		init_list( &node->nodes_head );
		node->is_end_available = 0;
		node->instances=1;
		add_link( trie_root ,node);
		ret=add_element_trie( &node->nodes_head, &string[1], payload);
		if( ret == -2 ){
			node->is_end_available = 1;
			node->payload = payload;
			return 0;
		}
		else if( ret == -3 ){
			free(node);
			return -3;
		}
		else if( ret == 0 ){
			return 0;
		}

	}
	else if (((struct trie*)(pointer->object))->value == string[0]){
		node = (struct trie*) pointer->object;
		ret = add_element_trie( &node->nodes_head, &string[1], payload);
		node->instances++;
		if( ret == -2 ){
			node->is_end_available++;
			node->payload = payload;
			return 0;
		}
		else if( ret == -3){
			return -3;
		}
		else if( ret == 0) {
			return 0;
		}
	}
	else {
		node = (struct trie*)malloc(sizeof(struct trie));
		if( !node ) return -3;
		node->value = string[0];
		init_list( &node->nodes_head );
		node->is_end_available = 0;
		node->instances = 1;
		add_link_between( trie_root, node, position); 
		ret = add_element_trie( &node->nodes_head, &string[1], payload);
		if( ret == -2 ){
			node->is_end_available++;
			node->payload = payload;
			return 0;
		}
		else if( ret == -3 ){
			free(node);
			return -3;
		}
		else if( ret == 0 ){
			return 0;
		}
	}
}



int find_element_trie(struct llist *root, char *string, void **payload )
{
	struct trie* t_node;
	struct linked_list *pointer;
	int ret;
	
	if( string == NULL ) return FIND_TRIE_NULLSTRING;
	if( *string == '\0' ) return FIND_TRIE_ENDOFSTRING;
	if( root == NULL ) return FIND_TRIE_INVROOT;
	if( !payload ) return FIND_TRIE_INVPAYLOAD;
	
	pointer = root->head;

	while( pointer != NULL )
	{
		t_node = (struct trie *) pointer->object;
		if ( t_node != NULL )
		{
			if( *string == t_node->value ){
				
				ret = find_element_trie( &t_node->nodes_head, &string[1], payload);
				switch(ret){
					case FIND_TRIE_SUCCESS:
						return FIND_TRIE_SUCCESS;
						break;
					case FIND_TRIE_INVROOT:
						return FIND_TRIE_FAILURE;
						break;
					case FIND_TRIE_NULLSTRING:
						return FIND_TRIE_NULLSTRING;
						break;
					case FIND_TRIE_ENDOFSTRING:
						if( t_node->is_end_available >= 1 ){
							*payload = t_node->payload;
							return FIND_TRIE_SUCCESS;
						}
						else{
							return FIND_TRIE_FAILURE;
						}
						break;
					case FIND_TRIE_FAILURE:
						return FIND_TRIE_FAILURE;
						break;
				}
			}
		}
		else{
			return FIND_TRIE_FAILURE;
		}
		if( *string < t_node->value){
			return FIND_TRIE_FAILURE;
		}
		else{
			pointer = pointer->next;
		}
	}

	return FIND_TRIE_FAILURE;
}

void print_trie(struct linked_list *node)
{
	struct trie *trie_node = (struct trie*) node->object;
	printf(" \"%p\" -> \"%p\\n%c\" [color=\"red\"]\n",node,trie_node,trie_node->value);
	printf(" \"%p\\n%c\" -> \"%p\" [color=\"green\"]\n",trie_node,trie_node->value,trie_node->nodes_head.head);
	printf(" \"%p\" -> \"%p\" [color=\"blue\"]\n",trie_node->nodes_head.head,node->next);
	traverse_list( &trie_node->nodes_head, print_trie);
}

void print_trie_diff(struct trie *parent , char parent_value , struct llist *list)
{
	struct trie *t_node;
	struct linked_list* pointer=list->head;
	
	while( pointer != NULL )
	{
	        t_node = (struct trie*) pointer->object;
		printf(" \t\t %p\n",t_node);
		if( t_node != NULL ){
			printf(" \"%p\\n%c\" -> \"%p\\n%c\" [color=\"red\"]\n",parent,parent_value,t_node,t_node->value);
			print_trie_diff(t_node,t_node->value,&t_node->nodes_head);
		}
		pointer = pointer->next;
	}
}
