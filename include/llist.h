#ifndef _LLIST_H
#define _LLIST_H

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Linked list structure
 *
 * @var head Head pointer
 * @var tail Tail pointer
 */
struct llist{
	struct linked_list *head;
	struct linked_list *tail;
};

/**
 * @brief Linked list node
 *
 * @var object Pointer the value stored
 * @var next Pointer to the next node
 */
struct linked_list {
	void *object;
	struct linked_list *next;
};

/**
 * @brief Initialises the linked list
 *
 * @param list Linked list instance
 *
 * @return 0 on success, -1 on failure
 */
int init_list( struct llist *list );

/**
 * @brief Gets the node mentioned by `pos`
 *
 * @param list Linked list instance
 * @param pos Position query
 *
 * @return node in the particular position, NULL on error
 */
struct linked_list* get_pos(struct llist *list,uint32_t pos);

/**
 * @brief Adds a link at the tail
 *
 * @param list Linked list instance
 * @param object Data to be inserted
 *
 * @return 0 on success, negative on failure
 */
int add_link(struct llist *list,void* object);

/**
 * @brief Removes a link at the tail
 *
 * @param list Linked list instance
 *
 * @return 0 on success, negative on failure
 */
int remove_last_link( struct llist *list );
/**
 * @brief Adds a link at the tail
 *
 * @param list Linked list instance
 * @param object Data to be inserted
 *
 * @return 0 on success, negative on failure
 */

int add_link_between( struct llist *list, void *object, uint32_t pos );

/**
 * @brief Removes a link at the middle
 *
 * @param list Linked list instance
 * @param pos Position to be removed
 *
 * @return 0 on success, negative on failure
 */
int remove_link_between( struct llist *list, uint32_t pos );

/**
 * @brief Traverses and prints the list
 *
 * @param list Linked list instance
 * @param print Print function
 *
 */
void traverse_list( struct llist* list, void (*print)(struct linked_list*) );

/**
 * @brief Finds the link length
 *
 * @param list Linked list instance
 *
 * @return link length on success, negative on failure
 */
int link_length(struct llist *list);

/**
 * @brief Swaps 2 links
 *
 * @param list Linked list instance
 * @param fp First link position
 * @param sp Second link position
 *
 * @return 0 on success, negative on failure
 */
int link_swap( struct llist *list , int fp , int sp );

#endif
