#include "mckits_adt_rbtree.h"

struct MckitsRbtreeNode* mckits_rbtree_min(struct MckitsRbtreeNode* node,
                                           struct MckitsRbtreeNode* sentinel) {
  while (node->left != sentinel) {
    node = node->left;
  }
  return node;
}
