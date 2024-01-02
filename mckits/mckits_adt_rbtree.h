// Inspired by nginx/ngx_rbtree
#ifndef MKITS_MCKITS_MCKITS_ADT_RBTREE_H_
#define MKITS_MCKITS_MCKITS_ADT_RBTREE_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t mckits_rbtree_key_t;
typedef int32_t mckits_rbtree_key_int_t;

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

#define mckits_rbtree_init(tree, s, i)            \
  mckits_rbtree_sentinel_init(s)(tree)->root = s; \
  (tree)->sentinel = s;                           \
  (tree)->insert = i

#define mckits_rbtree_data(node, type, link) \
  (type*)((uint8_t*)(node)-offsetof(type, link))

#define mckits_rbtree_red(node) ((node)->color = 1)
#define mckits_rbtree_black(node) ((node)->color = 0)
#define mckits_rbtree_is_red(node) ((node)->color)
#define mckits_rbtree_is_black(node) (!mckits_rbtree_is_red(node))
#define mckits_rbtree_copy_color(n1, n2) (n1->color = n2->color)

// a sentinel must be black
#define mckits_rbtree_sentinel_init(node) mckits_rbtree_black(node)

struct MckitsRbtreeNode* mckits_rbtree_min(struct MckitsRbtreeNode* node,
                                           struct MckitsRbtreeNode* sentinel);

#ifdef __cplusplus
}
#endif

#endif
