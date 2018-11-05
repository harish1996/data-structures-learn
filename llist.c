/********************************************
 *
 *	HELPER FILE FOR IMPLEMENTING GENERIC
 *	LINKED LISTS
 *
 ********************************************/
#include "include/llist.h"

int init_list( struct llist *list)
{
	if( !list )
		return -1;

	list->head = NULL;
	list->tail = NULL;
	return 0;
}

struct linked_list* get_pos(struct llist *list,uint32_t pos)
{
	struct linked_list *pointer = list->head;
	uint32_t position=0;
	while( pointer != NULL ){
		if(pos==position)
			return pointer;
		else{
			pointer = pointer->next;
			position++;
		}
	}
	return NULL;
}

int add_link(struct llist *list,void* object)
{
	if( !list ) 
		return -1;
	if( !object )
		return -2;

	struct linked_list *pointer = list->tail;
	
	if( pointer != NULL){	
		pointer->next = malloc( sizeof(struct linked_list) );
		if( pointer->next == NULL ){
			return -1;
		}
		pointer = pointer->next;
	}
	else{
		pointer = malloc( sizeof( struct linked_list) );
		if( !pointer )
			return -1;
		list->head = pointer;
	}
	      
	pointer->next = NULL;
	pointer->object = object;
	list->tail = pointer;
	return 0;
}

int remove_last_link(struct llist *list)
{
	struct linked_list *pointer;
	
	if( !list )
		return -1;

	pointer = list->head;
	while(pointer->next != NULL && pointer->next->next !=NULL) pointer= pointer->next;
	free(pointer->next);
	pointer->next = NULL;
	return 0;
}

int add_link_between(struct llist *list,void* object,uint32_t pos)
{
	if( !list )
		return -1;
	if( !object )
		return -2;

	struct linked_list *pointer= list->head;
	struct linked_list *temp;
	uint32_t position=1;
	if(pos < 1)
		return -1;

	if( pos == 1 ){
		list->head = malloc( sizeof(struct linked_list ) );
		if( !list->head )
			return -1;
		list->head->next = pointer;
		pointer = list->head;
		if( !pointer->next )
			list->tail = list->head;
		pointer->object = object;
		return 0;
	}
	while( pointer != NULL ){
		if(pos-1==position){
			temp = pointer->next;
			pointer->next = (struct linked_list*)malloc(sizeof(struct linked_list));
			if(pointer->next == NULL){
				return -1;
			}
			pointer = pointer->next;
			pointer->next = temp;
			if( !pointer->next )
				list->tail = pointer;
			pointer->object = object;
			return 0;
		}
		else{
			pointer = pointer->next;
			position++;
		}
	}
	return -1;
}

int remove_link_between(struct llist *list,uint32_t pos)
{
	if( !list )
		return -1;
	struct linked_list *pointer = list->head;
	struct linked_list *temp;
	uint32_t position=0;
	if(pos<1)
		return -2;
	while(pointer != NULL){
		if(pos-1==position){
			temp=pointer->next;
			if(temp){
				pointer->next=pointer->next->next;
				if( !pointer->next )
					list->tail = pointer->next;
				free(temp);
			}
			return 0;
		}
		else{
			pointer=pointer->next;
			position++;
		}
	}
	return -3;
}

void traverse_list( struct llist *list, void (*print)(struct linked_list*) )
{
	struct linked_list *pointer = list->head;
	pointer = pointer->next;
	while( pointer != NULL ){
		if( print != NULL ) print(pointer);
		pointer= pointer->next;
	}
}

int link_length(struct llist *list)
{
	struct linked_list *pointer = list->head;
	uint8_t link_len = 0;
	pointer = pointer->next;
	while( pointer != NULL ) {
		link_len++;
		pointer = pointer->next;
	}
	return link_len;
}


int link_swap( struct llist *list , int fp , int sp )
{
	struct linked_list *fsb = get_pos(list,fp-1);
	if(!fsb) return -1;
	struct linked_list *ssb = get_pos(list,sp-1);
	if(!ssb) return -1;
	struct linked_list *fs = fsb->next;
	if(!fsb) return -1;
	struct linked_list *ss = ssb->next;
	if(!ssb) return -1;
	struct linked_list *temp;

	fsb->next = ss;
	ssb->next = fs;
	temp = ss->next;
	ss->next = fs->next;
	fs->next = temp;

	return 0;
}
