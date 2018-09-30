#include <stdlib.h>
#include <stdint.h>

struct linked_list {
	void *object;
	struct linked_list *next;
};

struct linked_list* init_list();

struct linked_list* get_pos(struct linked_list *head,uint32_t pos);

int8_t add_link(struct linked_list *head,void* object);

int8_t remove_last_link(struct linked_list *head);

void traverse_list( struct linked_list* head, void (*print)(struct linked_list*) );

uint8_t link_length(struct linked_list *head);

int8_t link_swap( struct linked_list *head , int fp , int sp );

int8_t add_link_between(struct linked_list *head,void* object,uint32_t pos);

int8_t remove_link_between(struct linked_list *head,uint32_t pos);
