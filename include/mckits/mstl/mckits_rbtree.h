// Inspired by nginx/ngx_rbtree
#ifndef MKITS_INCLUDE_MCKITS_MSTL_MCKITS_RBTREE_H_
#define MKITS_INCLUDE_MCKITS_MSTL_MCKITS_RBTREE_H_

#include <stddef.h>
#include <stdint.h>

#include "mckits/mstl/mckits_string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t mckits_rbtree_key_t;
typedef int64_t mckits_rbtree_key_int_t;

struct MckitsRbtreeNode {
  mckits_rbtree_key_t key;
  struct MckitsRbtreeNode* left;
  struct MckitsRbtreeNode* right;
  struct MckitsRbtreeNode* parent;
  uint8_t color;
};

typedef void (*mckits_rbtree_insert_callback)(
    struct MckitsRbtreeNode* root, struct MckitsRbtreeNode* node,
    struct MckitsRbtreeNode* sentinel);

struct MckitsRbtree {
  struct MckitsRbtreeNode* root;
  struct MckitsRbtreeNode* sentinel;
  mckits_rbtree_insert_callback insert;
};

/*
@brief: Initialize rbtree.
@param tree[in]: pointer to rbtree.
@param s[in]: pointer to sentinel tree node.
@param i[in}: insert callback function.
*/
#define mckits_rbtree_init(tree, s, i) \
  mckits_rbtree_sentinel_init(s);      \
  (tree)->root = s;                    \
  (tree)->sentinel = s;                \
  (tree)->insert = i

/*
@brief: Get user struct pointer.
@param node[in]: pointer to rbtree node.
@param type[in]: user struct type.
@param link[in]: rbtree node field name in user struct type.
@return pointer to user struct.
*/
#define mckits_rbtree_data(node, type, link) \
  (type*)((uint8_t*)(node)-offsetof(type, link))

#define mckits_rbtree_red(node) ((node)->color = 1)
#define mckits_rbtree_black(node) ((node)->color = 0)
#define mckits_rbtree_is_red(node) ((node)->color)
#define mckits_rbtree_is_black(node) (!mckits_rbtree_is_red(node))
#define mckits_rbtree_copy_color(n1, n2) (n1->color = n2->color)

// a sentinel must be black
#define mckits_rbtree_sentinel_init(node) mckits_rbtree_black(node)

/*
@brief: Insert node into rbtree.
@param tree[in]: rbtree.
@param node[in]: node will be insert into rbtree.
*/
void mckits_rbtree_insert(struct MckitsRbtree* tree,
                          struct MckitsRbtreeNode* node);

/*
@brief: Delete node from rbtree.
@param tree[in]: rbtree.
@param node[in]: node will be deleted from rbtree.
*/
void mckits_rbtree_delete(struct MckitsRbtree* tree,
                          struct MckitsRbtreeNode* node);

/*
@brief: Insert value into rbtree.
  Callback function used in `mckits_rbtree_init`.
*/
void mckits_rbtree_insert_value(struct MckitsRbtreeNode* root,
                                struct MckitsRbtreeNode* node,
                                struct MckitsRbtreeNode* sentinel);

/*
@brief: Insert timer value into rbtree.
  Callback function used in `mckits_rbtree_init`.
@notes:
  1) timer value are spread in small range, usually several minutes,
  2) timer value overflow each 49 days, if milliseconds are stored in 32 bits.
*/
void mckits_rbtree_insert_timer_value(struct MckitsRbtreeNode* root,
                                      struct MckitsRbtreeNode* node,
                                      struct MckitsRbtreeNode* sentinel);

/*
@brief: Search key in rbtree. Because rbtree can hold multiply same key, so
  this function just return the first finded node.
@param tree[in]: rbtree.
@param key[in]: key will be searched in rbtree.
@return: Returns pointer to tree node, or NULL if not found.
*/
struct MckitsRbtreeNode* mckits_rbtree_lookup(struct MckitsRbtree* tree,
                                              mckits_rbtree_key_t key);

/*
@brief: Get next node from rbtree.
@param tree[in]: rbtree.
@param node[in]: current node.
@return:
  On success, return the pointer to the next node.
  If not found, return NULL.
*/
struct MckitsRbtreeNode* mckits_rbtree_next(struct MckitsRbtree* tree,
                                            struct MckitsRbtreeNode* node);

/*
@brief: Recursion get left node until sentinel.
*/
struct MckitsRbtreeNode* mckits_rbtree_min(struct MckitsRbtreeNode* node,
                                           struct MckitsRbtreeNode* sentinel);

struct MckitsRbtreeStrNode {
  struct MckitsRbtreeNode node;
  struct MckitsString str;
};

/*
@brief: Insert string value into rbtree.
  Callback function used in `mckits_rbtree_init`.
@param root[in]: pointer to `struct MckitsRbtreeStrNode`
@param node[in]: pointer to `struct MckitsRbtreeStrNode`
*/
void mckits_rbtree_insert_str_value(struct MckitsRbtreeNode* root,
                                    struct MckitsRbtreeNode* node,
                                    struct MckitsRbtreeNode* sentinel);

/*
@brief: Search key in rbtree.
@param tree[in]: rbtree.
@param key[in]: string key will be searched in rbtree.
@param hash[in]: key string hash code.
@return: Returns pointer to string node, or NULL if not found.
*/
struct MckitsRbtreeStrNode* mckits_rbtree_str_lookup(struct MckitsRbtree* tree,
                                                     struct MckitsString* key,
                                                     uint64_t hash);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_MSTL_MCKITS_RBTREE_H_
