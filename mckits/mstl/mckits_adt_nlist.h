// Inspired by nginx/ngx_queue
#ifndef MKITS_MCKITS_MSTL_MCKITS_ADT_NLIST_H_
#define MKITS_MCKITS_MSTL_MCKITS_ADT_NLIST_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Double linked list. It has a dumb sentinel node, it's really like
  `mckits_adt_ring`. But this list should be put inside node data structure.
*/
struct MckitsNList {
  struct MckitsNList* prev;
  struct MckitsNList* next;
};

/*
@brief: Initialize a empty list. It has a sentinel head.
*/
#define mckits_nlist_init(q) \
  (q)->prev = q;             \
  (q)->next = q

/*
@brief: Check if the list is empty.
@param h: list sentinel pointer.
@return:
  1: means queue is empty.
  0: means queue is not empty.
*/
#define mckits_nlist_empty(h) (h == (h)->prev)

/*
@brief: Insert node `x` to list head.
@param h: list sentinel pointer.
@param x: new node pointer.
*/
#define mckits_nlist_insert_head(h, x) \
  (x)->next = (h)->next;               \
  (x)->next->prev = x;                 \
  (x)->prev = h;                       \
  (h)->next = x

#define mckits_nlist_insert_after mckits_nlist_insert_head

/*
@brief: Insert node `x` to list tail.
@param h: list sentinel pointer.
@param x: new node pointer.
*/
#define mckits_nlist_insert_tail(h, x) \
  (x)->prev = (h)->prev;               \
  (x)->prev->next = x;                 \
  (x)->next = h;                       \
  (h)->prev = x

#define mckits_nlist_insert_before mckits_nlist_insert_tail

/*
@brief: Get list first node pointer.
@param h: list sentinel pointer.
*/
#define mckits_nlist_head(h) (h)->next

/*
@brief: Get list last node pointer.
@param h: list sentinel pointer.
*/
#define mckits_nlist_last(h) (h)->prev

/*
@brief: Get list sentinel pointer.
@param h: list sentinel pointer.
*/
#define mckits_nlist_sentinel(h) (h)

/*
@brief: Get next list node pointer.
@param q: Pointer to list node.
*/
#define mckits_nlist_next(q) (q)->next

/*
@brief: Get prev list node pointer.
@param q: Pointer to list node.
*/
#define mckits_nlist_prev(q) (q)->prev

/*
@brief: Remove node `x` from list.
*/
#define mckits_nlist_remove(x) \
  (x)->next->prev = (x)->prev; \
  (x)->prev->next = (x)->next

/*
@brief: Split one list to two sublist.
  First sublist: from origin list head to q prev node.
  Second sublist: from q to origin list last node.
@param h: Origin list sentinel. After split, `h` is the first sublist sentinel.
@param q: Pointer to any node of origin list.
@param n: Second sublist sentinel.
*/
#define mckits_nlist_split(h, q, n) \
  (n)->prev = (h)->prev;            \
  (n)->prev->next = n;              \
  (n)->next = q;                    \
  (h)->prev = (q)->prev;            \
  (h)->prev->next = h;              \
  (q)->prev = n

/*
@brief: Connect two list. Append list `n` to list `h` tail.
@param h: one list sentinel.
@param n: one list sentinel.
*/
#define mckits_nlist_add(h, n) \
  (h)->prev->next = (n)->next; \
  (n)->next->prev = (h)->prev; \
  (h)->prev = (n)->prev;       \
  (h)->prev->next = h

/*
@brief: Get list node data pointer.
@param q: Pointer to list node.
@param type: List node data structure type.
@param link: The list name in data structure.
@return: Pointer to data structure.
*/
#define mckits_nlist_data(q, type, link) \
  (type*)((uint8_t*)q - offsetof(type, link))

/*
@brief: If the list has odd number of node, find the middle list node. If the
  list has even number of node, find the first node of the list's second part.
@param list[in]: list sentinel.
@return: Pointer to the middle node.
*/
struct MckitsNList* mckits_nlist_middle(struct MckitsNList* list);

/*
@brief: Sort list. The stable merge sort.
@param list[in]: list sentinel.
@param cmp[in]: compare callback function.
*/
void mckits_nlist_sort(struct MckitsNList* list,
                       int (*cmp)(struct MckitsNList*, struct MckitsNList*));

#ifdef __cplusplus
}
#endif

#endif
