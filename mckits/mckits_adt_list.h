#ifndef MKITS_MCKITS_MCKITS_ADT_LIST_H_
#define MKITS_MCKITS_MCKITS_ADT_LIST_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: MckitsListNode is a node of MckitsList.
*/
struct MckitsListNode {
  struct MckitsListNode* prev;
  struct MckitsListNode* next;
  // The list to which this node belongs.
  struct MckitsList* list;
  // The value stored with this node.
  void* value;
};

/*
@brief: MckitsList represents a doubly linked list. A list l is implemented
  as a ring, such that &l.root is both the next node of the last list node
  and the previous node of the first list node.
*/
struct MckitsList {
  // sentinel list node, only root.prev and root.next are used.
  struct MckitsListNode root;
  // current this length excluding (this) sentinel node
  int len;
};

/*
@brief: Create an list node from value.
*/
struct MckitsListNode* mckits_list_node_new(void* value);

/*
@brief: Drop list node.
@notes: node must be remove from list firstly, and node->value must be free
  by user if needed.
*/
void mckits_list_node_drop(struct MckitsListNode* node);

/*
@brief: Returns the next list node or NULL.
*/
struct MckitsListNode* mckits_list_node_next(struct MckitsListNode* node);

/*
@brief: Returns the previous list node or NULL.
*/
struct MckitsListNode* mckits_list_node_prev(struct MckitsListNode* node);

/*
@brief: Create an initialized list.
*/
struct MckitsList* mckits_list_new();

/*
@brief: Drop list.
*/
void mckits_list_drop(struct MckitsList* list, void (*free_node_value)(void*));

/*
@brief: Returns the number of nodes of list.
*/
int mckits_list_len(struct MckitsList* list);

/*
@brief: Returns the first node of list or NULL if the list is empty.
*/
struct MckitsListNode* mckits_list_front(struct MckitsList* list);

/*
@brief: Returns the last node of list or NULL if the list is empty.
*/
struct MckitsListNode* mckits_list_back(struct MckitsList* list);

/*
@brief: Removes node from list if node is an element of list.
@return: value of node.
*/
void* mckits_list_remove(struct MckitsList* list, struct MckitsListNode* node);

/*
@brief: Inserts a new node with value at the front of list.
@return: new node pointer.
*/
struct MckitsListNode* mckits_list_push_front(struct MckitsList* list,
                                              void* value);

/*
@brief: Inserts a new node with value at the front of list.
@return: new node pointer.
*/
struct MckitsListNode* mckits_list_push_back(struct MckitsList* list,
                                             void* value);

/*
@brief: Inserts a new node with value before mark.
@return: new node pointer.
*/
struct MckitsListNode* mckits_list_insert_before(struct MckitsList* list,
                                                 void* value,
                                                 struct MckitsListNode* mark);

/*
@brief: Inserts a new node with value after mark.
@return: new node pointer.
*/
struct MckitsListNode* mckits_list_insert_after(struct MckitsList* list,
                                                void* value,
                                                struct MckitsListNode* mark);

/*
@brief: Move node to the front of list.
*/
void mckits_list_move_to_front(struct MckitsList* list,
                               struct MckitsListNode* node);

/*
@brief: Move node to the back of list.
*/
void mckits_list_move_to_back(struct MckitsList* list,
                              struct MckitsListNode* node);

/*
@brief: Move node before mark.
*/
void mckits_list_move_before(struct MckitsList* list,
                             struct MckitsListNode* node,
                             struct MckitsListNode* mark);

/*
@brief: Move node after mark.
*/
void mckits_list_move_after(struct MckitsList* list,
                            struct MckitsListNode* node,
                            struct MckitsListNode* mark);

/*
@brief: Inserts a copy of another list at the back of list.
*/
void mckits_list_push_back_list(struct MckitsList* list,
                                struct MckitsList* other);

/*
@brief: Inserts a copy of another list at the front of list.
*/
void mckits_list_push_front_list(struct MckitsList* list,
                                 struct MckitsList* other);

#ifdef __cplusplus
}
#endif

#endif
