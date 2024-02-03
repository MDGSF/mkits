#include "mckits/mstl/mckits_list.h"

#include <stdlib.h>
#include <string.h>

/*
@brief: Insert node after at, increment list->len, and returns node.
*/
static struct MckitsListNode* s_mckits_list_insert(struct MckitsList* list,
                                                   struct MckitsListNode* node,
                                                   struct MckitsListNode* at) {
  node->prev = at;
  node->next = at->next;
  node->prev->next = node;
  node->next->prev = node;
  node->list = list;
  list->len += 1;
  return node;
}

/*
@brief: Create new node with value. Insert new node after at,
  increment list->len, and returns new node.
*/
static struct MckitsListNode* s_mckits_list_insert_value(
    struct MckitsList* list, void* value, struct MckitsListNode* at) {
  struct MckitsListNode* node = mckits_list_node_new(value);
  return s_mckits_list_insert(list, node, at);
}

/*
@brief: Remove node from its list, decrements list->len.
*/
static void s_mckits_list_remove(struct MckitsList* list,
                                 struct MckitsListNode* node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->next = NULL;
  node->prev = NULL;
  node->list = NULL;
  list->len -= 1;
}

/*
@brief: Move node next to at.
*/
static void s_mckits_list_move(struct MckitsList* list,
                               struct MckitsListNode* node,
                               struct MckitsListNode* at) {
  if (node == at) {
    return;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;

  node->prev = at;
  node->next = at->next;
  node->prev->next = node;
  node->next->prev = node;
}

struct MckitsListNode* mckits_list_node_new(void* value) {
  struct MckitsListNode* node =
      (struct MckitsListNode*)malloc(sizeof(struct MckitsListNode));
  memset(node, 0, sizeof(struct MckitsListNode));
  node->value = value;
  return node;
}

void mckits_list_node_drop(struct MckitsListNode* node) {
  node->prev = NULL;
  node->next = NULL;
  node->list = NULL;
  node->value = NULL;
  free(node);
}

struct MckitsListNode* mckits_list_node_next(struct MckitsListNode* node) {
  struct MckitsListNode* next = node->next;
  if (node->list != NULL && next != &node->list->root) {
    return next;
  }
  return NULL;
}

struct MckitsListNode* mckits_list_node_prev(struct MckitsListNode* node) {
  struct MckitsListNode* prev = node->prev;
  if (node->list != NULL && prev != &node->list->root) {
    return prev;
  }
  return NULL;
}

struct MckitsList* mckits_list_new() {
  struct MckitsList* list =
      (struct MckitsList*)malloc(sizeof(struct MckitsList));
  list->root.next = &list->root;
  list->root.prev = &list->root;
  list->len = 0;
  return list;
}

void mckits_list_drop(struct MckitsList* list, void (*free_node_value)(void*)) {
  while (mckits_list_len(list) > 0) {
    struct MckitsListNode* node = mckits_list_front(list);
    void* value = mckits_list_remove(list, node);
    if (free_node_value != NULL) {
      free_node_value(value);
    }
    mckits_list_node_drop(node);
  }
  free(list);
}

int mckits_list_len(struct MckitsList* list) { return list->len; }

struct MckitsListNode* mckits_list_front(struct MckitsList* list) {
  if (list->len == 0) {
    return NULL;
  }
  return list->root.next;
}

struct MckitsListNode* mckits_list_back(struct MckitsList* list) {
  if (list->len == 0) {
    return NULL;
  }
  return list->root.prev;
}

void* mckits_list_remove(struct MckitsList* list, struct MckitsListNode* node) {
  if (list == node->list) {
    s_mckits_list_remove(list, node);
  }
  return node->value;
}

struct MckitsListNode* mckits_list_push_front(struct MckitsList* list,
                                              void* value) {
  return s_mckits_list_insert_value(list, value, &list->root);
}

struct MckitsListNode* mckits_list_push_back(struct MckitsList* list,
                                             void* value) {
  return s_mckits_list_insert_value(list, value, list->root.prev);
}

struct MckitsListNode* mckits_list_insert_before(struct MckitsList* list,
                                                 void* value,
                                                 struct MckitsListNode* mark) {
  if (mark->list != list) {
    return NULL;
  }
  return s_mckits_list_insert_value(list, value, mark->prev);
}

struct MckitsListNode* mckits_list_insert_after(struct MckitsList* list,
                                                void* value,
                                                struct MckitsListNode* mark) {
  if (mark->list != list) {
    return NULL;
  }
  return s_mckits_list_insert_value(list, value, mark);
}

void mckits_list_move_to_front(struct MckitsList* list,
                               struct MckitsListNode* node) {
  if (node->list != list || list->root.next == node) {
    return;
  }
  s_mckits_list_move(list, node, &list->root);
}

void mckits_list_move_to_back(struct MckitsList* list,
                              struct MckitsListNode* node) {
  if (node->list != list || list->root.prev == node) {
    return;
  }
  s_mckits_list_move(list, node, list->root.prev);
}

void mckits_list_move_before(struct MckitsList* list,
                             struct MckitsListNode* node,
                             struct MckitsListNode* mark) {
  if (node->list != list || node == mark || mark->list != list) {
    return;
  }
  s_mckits_list_move(list, node, mark->prev);
}

void mckits_list_move_after(struct MckitsList* list,
                            struct MckitsListNode* node,
                            struct MckitsListNode* mark) {
  if (node->list != list || node == mark || mark->list != list) {
    return;
  }
  s_mckits_list_move(list, node, mark);
}

void mckits_list_push_back_list(struct MckitsList* list,
                                struct MckitsList* other) {
  int other_len = mckits_list_len(other);
  struct MckitsListNode* node = mckits_list_front(other);
  while (other_len > 0) {
    s_mckits_list_insert_value(list, node->value, list->root.prev);
    other_len -= 1;
    node = mckits_list_node_next(node);
  }
}

void mckits_list_push_front_list(struct MckitsList* list,
                                 struct MckitsList* other) {
  int other_len = mckits_list_len(other);
  struct MckitsListNode* node = mckits_list_back(other);
  while (other_len > 0) {
    s_mckits_list_insert_value(list, node->value, &list->root);
    other_len -= 1;
    node = mckits_list_node_prev(node);
  }
}
