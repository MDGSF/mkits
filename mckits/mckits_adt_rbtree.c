#include "mckits_adt_rbtree.h"

static void mckits_rbtree_left_rotate(struct MckitsRbtreeNode** root,
                                      struct MckitsRbtreeNode* sentinel,
                                      struct MckitsRbtreeNode* node) {
  struct MckitsRbtreeNode* temp = node->right;
  node->right = temp->left;

  if (temp->left != sentinel) {
    temp->left->parent = node;
  }

  temp->parent = node->parent;

  if (node == *root) {
    *root = temp;
  } else if (node == node->parent->left) {
    node->parent->left = temp;
  } else {
    node->parent->right = temp;
  }

  temp->left = node;
  node->parent = temp;
}

static void mckits_rbtree_right_rotate(struct MckitsRbtreeNode** root,
                                       struct MckitsRbtreeNode* sentinel,
                                       struct MckitsRbtreeNode* node) {
  struct MckitsRbtreeNode* temp = node->left;
  node->left = temp->right;

  if (temp->right != sentinel) {
    temp->right->parent = node;
  }

  temp->parent = node->parent;

  if (node == *root) {
    *root = temp;
  } else if (node == node->parent->right) {
    node->parent->right = temp;
  } else {
    node->parent->left = temp;
  }

  temp->right = node;
  node->parent = temp;
}

void mckits_rbtree_insert(struct MckitsRbtree* tree,
                          struct MckitsRbtreeNode* node) {}

void mckits_rbtree_delete(struct MckitsRbtree* tree,
                          struct MckitsRbtreeNode* node) {}

void mckits_rbtree_insert_value(struct MckitsRbtreeNode* root,
                                struct MckitsRbtreeNode* node,
                                struct MckitsRbtreeNode* sentinel) {
  struct MckitsRbtreeNode** p = NULL;
  struct MckitsRbtreeNode* temp = root;
  for (;;) {
    p = (node->key < temp->key) ? &temp->left : &temp->right;
    if (*p == sentinel) {
      break;
    }
    temp = *p;
  }

  *p = node;
  node->parent = temp;
  node->left = sentinel;
  node->right = sentinel;
  mckits_rbtree_red(node);
}

void mckits_rbtree_insert_timer_value(struct MckitsRbtreeNode* root,
                                      struct MckitsRbtreeNode* node,
                                      struct MckitsRbtreeNode* sentinel) {
  struct MckitsRbtreeNode** p = NULL;
  struct MckitsRbtreeNode* temp = root;
  for (;;) {
    p = ((mckits_rbtree_key_int_t)(node->key - temp->key) < 0) ? &temp->left
                                                               : &temp->right;
    if (*p == sentinel) {
      break;
    }
    temp = *p;
  }

  *p = node;
  node->parent = temp;
  node->left = sentinel;
  node->right = sentinel;
  mckits_rbtree_red(node);
}

struct MckitsRbtreeNode* mckits_rbtree_next(struct MckitsRbtree* tree,
                                            struct MckitsRbtreeNode* node) {
  struct MckitsRbtreeNode* sentinel = tree->sentinel;
  if (node->right != sentinel) {
    return mckits_rbtree_min(node->right, sentinel);
  }

  struct MckitsRbtreeNode* root = tree->root;
  struct MckitsRbtreeNode* parent = NULL;
  for (;;) {
    parent = node->parent;

    if (node == root) {
      return NULL;
    }

    if (node == parent->left) {
      return parent;
    }

    node = parent;
  }
}

struct MckitsRbtreeNode* mckits_rbtree_min(struct MckitsRbtreeNode* node,
                                           struct MckitsRbtreeNode* sentinel) {
  while (node->left != sentinel) {
    node = node->left;
  }
  return node;
}
