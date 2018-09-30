#include "include/llist.h"

struct linked_list* init_list()
{
	struct linked_list* head = (struct linked_list*)malloc(sizeof(struct linked_list));
	return head;
}

struct linked_list* get_pos(struct linked_list *head,uint32_t pos)
{
	struct linked_list *pointer = head;
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

int8_t add_link(struct linked_list *head,void* object)
{
	struct linked_list *pointer = head;
	while( pointer->next != NULL ) pointer=pointer->next;
	pointer->next = (struct linked_list*)malloc(sizeof(struct linked_list));
	if( pointer->next == NULL ){
		return -1;
	}
	pointer = pointer->next;
	pointer->object = object;
	pointer->next = NULL;
}

int8_t remove_last_link(struct linked_list *head)
{
	struct linked_list *pointer=head;
	while(pointer->next != NULL && pointer->next->next !=NULL) pointer= pointer->next;
	free(pointer->next);
	pointer->next = NULL;
}

int8_t add_link_between(struct linked_list *head,void* object,uint32_t pos)
{
	struct linked_list *pointer= head;
	struct linked_list *temp;
	uint32_t position=0;
	if(pos < 1)
		return -1;
	while( pointer != NULL ){
		if(pos-1==position){
			temp=pointer->next;
			pointer->next = (struct linked_list*)malloc(sizeof(struct linked_list));
			if(pointer->next == NULL){
				return -1;
			}
			pointer = pointer->next;
			pointer->next = temp;
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

int8_t remove_link_between(struct linked_list *head,uint32_t pos)
{
	struct linked_list *pointer = head;
	struct linked_list *temp;
	uint32_t position=0;
	if(pos<1)
		return -1;
	while(pointer != NULL){
		if(pos-1==position){
			temp=pointer->next;
			if(temp){
				pointer->next=pointer->next->next;
				free(temp);
			}
			return 0;
		}
		else{
			pointer=pointer->next;
			position++;
		}
	}
	return -1;
}

void traverse_list( struct linked_list* head, void (*print)(struct linked_list*) )
{
	struct linked_list *pointer = head;
	pointer = pointer->next;
	while( pointer != NULL ){
		if( print != NULL ) print(pointer);
		pointer= pointer->next;
	}
}

uint8_t link_length(struct linked_list *head)
{
	struct linked_list *pointer = head;
	uint8_t link_len = 0;
	pointer = pointer->next;
	while( pointer != NULL ) {
		link_len++;
		pointer = pointer->next;
	}
	return link_len;
}


int8_t link_swap( struct linked_list *head , int fp , int sp )
{
	struct linked_list *fsb = get_pos(head,fp-1);
	if(!fsb) return -1;
	struct linked_list *ssb = get_pos(head,sp-1);
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
