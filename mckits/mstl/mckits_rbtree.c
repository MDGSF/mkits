#include "mckits_rbtree.h"

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
                          struct MckitsRbtreeNode* node) {
  // a binary tree insert
  struct MckitsRbtreeNode** root = &tree->root;
  struct MckitsRbtreeNode* sentinel = tree->sentinel;

  if (*root == sentinel) {
    node->parent = NULL;
    node->left = sentinel;
    node->right = sentinel;
    mckits_rbtree_black(node);
    *root = node;
    return;
  }

  tree->insert(*root, node, sentinel);

  // re-balance tree

  struct MckitsRbtreeNode* temp = NULL;
  while (node != *root && mckits_rbtree_is_red(node->parent)) {
    if (node->parent == node->parent->parent->left) {
      temp = node->parent->parent->right;
      if (mckits_rbtree_is_red(temp)) {
        mckits_rbtree_black(node->parent);
        mckits_rbtree_black(temp);
        mckits_rbtree_red(node->parent->parent);
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          mckits_rbtree_left_rotate(root, sentinel, node);
        }
        mckits_rbtree_black(node->parent);
        mckits_rbtree_red(node->parent->parent);
        mckits_rbtree_right_rotate(root, sentinel, node->parent->parent);
      }
    } else {
      temp = node->parent->parent->left;
      if (mckits_rbtree_is_red(temp)) {
        mckits_rbtree_black(node->parent);
        mckits_rbtree_black(temp);
        mckits_rbtree_red(node->parent->parent);
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          mckits_rbtree_right_rotate(root, sentinel, node);
        }
        mckits_rbtree_black(node->parent);
        mckits_rbtree_red(node->parent->parent);
        mckits_rbtree_left_rotate(root, sentinel, node->parent->parent);
      }
    }
  }

  mckits_rbtree_black(*root);
}

void mckits_rbtree_delete(struct MckitsRbtree* tree,
                          struct MckitsRbtreeNode* node) {
  // a binary tree delete
  struct MckitsRbtreeNode* temp = NULL;
  struct MckitsRbtreeNode* subst = NULL;
  struct MckitsRbtreeNode** root = &tree->root;
  struct MckitsRbtreeNode* sentinel = tree->sentinel;

  if (node->left == sentinel) {
    temp = node->right;
    subst = node;
  } else if (node->right == sentinel) {
    temp = node->left;
    subst = node;
  } else {
    subst = mckits_rbtree_min(node->right, sentinel);
    temp = subst->right;
  }

  if (subst == *root) {
    *root = temp;
    mckits_rbtree_black(temp);

    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->key = 0;

    return;
  }

  uint8_t red = mckits_rbtree_is_red(subst);

  if (subst == subst->parent->left) {
    subst->parent->left = temp;
  } else {
    subst->parent->right = temp;
  }

  if (subst == node) {
    temp->parent = subst->parent;
  } else {
    if (subst->parent == node) {
      temp->parent = subst;
    } else {
      temp->parent = subst->parent;
    }

    subst->left = node->left;
    subst->right = node->right;
    subst->parent = node->parent;
    mckits_rbtree_copy_color(subst, node);

    if (node == *root) {
      *root = subst;
    } else {
      if (node == node->parent->left) {
        node->parent->left = subst;
      } else {
        node->parent->right = subst;
      }
    }

    if (subst->left != sentinel) {
      subst->left->parent = subst;
    }

    if (subst->right != sentinel) {
      subst->right->parent = subst;
    }
  }

  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->key = 0;

  if (red) {
    return;
  }

  // a delete fixup
  struct MckitsRbtreeNode* w = NULL;
  while (temp != *root && mckits_rbtree_is_black(temp)) {
    if (temp == temp->parent->left) {
      w = temp->parent->right;

      if (mckits_rbtree_is_red(w)) {
        mckits_rbtree_black(w);
        mckits_rbtree_red(temp->parent);
        mckits_rbtree_left_rotate(root, sentinel, temp->parent);
        w = temp->parent->right;
      }

      if (mckits_rbtree_is_black(w->left) && mckits_rbtree_is_black(w->right)) {
        mckits_rbtree_red(w);
        temp = temp->parent;
      } else {
        if (mckits_rbtree_is_black(w->right)) {
          mckits_rbtree_black(w->left);
          mckits_rbtree_red(w);
          mckits_rbtree_right_rotate(root, sentinel, w);
          w = temp->parent->right;
        }

        mckits_rbtree_copy_color(w, temp->parent);
        mckits_rbtree_black(temp->parent);
        mckits_rbtree_black(w->right);
        mckits_rbtree_left_rotate(root, sentinel, temp->parent);
        temp = *root;
      }
    } else {
      w = temp->parent->left;

      if (mckits_rbtree_is_red(w)) {
        mckits_rbtree_black(w);
        mckits_rbtree_red(temp->parent);
        mckits_rbtree_right_rotate(root, sentinel, temp->parent);
        w = temp->parent->left;
      }

      if (mckits_rbtree_is_black(w->left) && mckits_rbtree_is_black(w->right)) {
        mckits_rbtree_red(w);
        temp = temp->parent;
      } else {
        if (mckits_rbtree_is_black(w->left)) {
          mckits_rbtree_black(w->right);
          mckits_rbtree_red(w);
          mckits_rbtree_left_rotate(root, sentinel, w);
          w = temp->parent->left;
        }

        mckits_rbtree_copy_color(w, temp->parent);
        mckits_rbtree_black(temp->parent);
        mckits_rbtree_black(w->left);
        mckits_rbtree_right_rotate(root, sentinel, temp->parent);
        temp = *root;
      }
    }
  }

  mckits_rbtree_black(temp);
}

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

struct MckitsRbtreeNode* mckits_rbtree_lookup(struct MckitsRbtree* tree,
                                              mckits_rbtree_key_t key) {
  struct MckitsRbtreeNode* node = tree->root;
  struct MckitsRbtreeNode* sentinel = tree->sentinel;

  while (node != sentinel) {
    if (key != node->key) {
      node = (key < node->key) ? node->left : node->right;
      continue;
    }
    return node;
  }

  return NULL;
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

void mckits_rbtree_insert_str_value(struct MckitsRbtreeNode* root,
                                    struct MckitsRbtreeNode* node,
                                    struct MckitsRbtreeNode* sentinel) {
  struct MckitsRbtreeNode* temp = root;
  struct MckitsRbtreeNode** p = NULL;
  struct MckitsRbtreeStrNode* n = NULL;
  struct MckitsRbtreeStrNode* t = NULL;

  for (;;) {
    n = (struct MckitsRbtreeStrNode*)node;
    t = (struct MckitsRbtreeStrNode*)temp;

    if (node->key != temp->key) {
      p = (node->key < temp->key) ? &temp->left : &temp->right;
    } else if (n->str.len != t->str.len) {
      p = (n->str.len < t->str.len) ? &temp->left : &temp->right;
    } else {
      p = (mckits_memcmp(n->str.data, t->str.data, n->str.len) < 0)
              ? &temp->left
              : &temp->right;
    }

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

struct MckitsRbtreeStrNode* mckits_rbtree_str_lookup(struct MckitsRbtree* tree,
                                                     struct MckitsString* key,
                                                     uint64_t hash) {
  struct MckitsRbtreeNode* node = tree->root;
  struct MckitsRbtreeNode* sentinel = tree->sentinel;

  while (node != sentinel) {
    struct MckitsRbtreeStrNode* n = (struct MckitsRbtreeStrNode*)node;

    if (hash != node->key) {
      node = (hash < node->key) ? node->left : node->right;
      continue;
    }

    if (key->len != n->str.len) {
      node = (key->len < n->str.len) ? node->left : node->right;
      continue;
    }

    int ret = mckits_memcmp(key->data, n->str.data, key->len);

    if (ret < 0) {
      node = node->left;
      continue;
    }

    if (ret > 0) {
      node = node->right;
      continue;
    }

    return n;
  }

  return NULL;
}
