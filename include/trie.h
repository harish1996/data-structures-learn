#ifndef _TRIE_H

#define _TRIE_H

#include "llist.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Trie data structure
 *
 * @var value Character stored in the node
 * @var is_end_available Indicates termination of string
 * @var instances Number of times node used
 * @var payload Payload carried by node
 * @var nodes_head List for the children trie node
 */
struct trie {
	char value;
	int is_end_available;
	int instances;
	void *payload;
	struct llist nodes_head;
};

/**
 * @brief Inits the Trie linked list
 *
 * @param list list which carries the trie structure
 *
 * @return 0 on success, negative on success
 */
int init_trie_rootlist( struct llist *list );

/**
 * @brief Return status for remove_element_trie
 */
enum rem_cases {
	REM_TRIE_INVPAYLOAD=-5,
	REM_TRIE_INVSTRING,
	REM_TRIE_INVROOT,
	REM_TRIE_NULLSTRING,
	REM_TRIE_EMPTYSTRING,
	REM_TRIE_SUCCESS,
	REM_TRIE_FAILURE
};

/**
 * @brief Removes a string from the trie
 *
 * @param trie_root List which carries trie structure
 * @param string String to be removed
 * @param payload pointer to a pointer which will be assigned to the payload
 *
 * @return Refer rem_cases
 */
int remove_element_trie(struct llist *trie_root, char *string, void **payload);

/**
 * @brief Adds a string to the trie
 *
 * @param trie_root List which carries trie structure
 * @param string String to be removed
 * @param payload pointer which will be assigned to the payload
 *
 * @return 0 on success, negative on failure
 */
int add_element_trie(struct llist *trie_root, char* string, void *payload);

/**
 * @brief Return statuses for find_element_trie
 */
enum find_cases {
	FIND_TRIE_INVPAYLOAD=-4,
	FIND_TRIE_ENDOFSTRING,
	FIND_TRIE_NULLSTRING,
	FIND_TRIE_INVROOT,
	FIND_TRIE_SUCCESS,
	FIND_TRIE_FAILURE
};

/**
 * @brief Removes a string from the trie
 *
 * @param root List which carries trie structure
 * @param string String to be removed
 * @param payload pointer to a pointer which will be assigned to the payload
 *
 * @return Refer find_cases
 */
int find_element_trie(struct llist *root, char *string, void **payload);

/**
 * 	TO BE IMPLEMENTED
 *
typedef struct {
	int ret;
	struct trie* t_node;
} found_element;

found_element find_return_element_trie(struct linked_list *root,char *string);

 *
 */

/**
 * @brief Prints trie to be drawn using graphviz
 *
 * @param root Linked list which carries trie structure
 */
void print_trie(struct linked_list *node);

/**
 * @brief Prints entire trie recursively for graphviz visualization
 *
 * @param parent Parent trie node. NULL when no parent
 * @param parent_vale Parent string value, ' ' when no parent value
 * @param node Linked list which carries trie data structure
 */
void print_trie_diff(struct trie *parent , char parent_value , struct llist *node);

/**
 * 	TO BE IMPLEMENTED
 *

int traverse_recursive(struct linked_list *root,char *string,void (*apply)(char *string,int count));

int traverse_alphabetically(struct linked_list *root,void (*apply)(char *string,int count));

enum traverse_returns {
	TRAV_NO_ROOT=-5,
	TRAV_NO_STRING,
	TRAV_MEM_ALLOC_FAIL,
	TRAV_NO_APPLY,
	TRAV_FAIL,
	TRAV_SUCCESS
};

struct packet {
	char *string;
	int size;
};
*
*/
#endif
