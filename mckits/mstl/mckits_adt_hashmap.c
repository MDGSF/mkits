#include "mckits_adt_hashmap.h"

#include <string.h>

#include "mckits_adt_list.h"
#include "mckits_adt_rbtree.h"
#include "mckits_hash_fnv.h"
#include "mckits_malloc.h"

#define MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST 1
#define MCKITS_HASHMAP_BUCKET_STORE_TYPE_RBTREE 2

struct MckitsHashMapEntry {
  void* key;
  void* val;
  uint64_t key_hash;
};

struct MckitsHashMapRbEntry {
  struct MckitsRbtreeNode node;
  int (*compare_func)(void* keya, void* keyb);
  void* key;
  void* val;
};

struct MckitsHashMapBucket {
  void* store;       // list or rbtree
  int store_type;    // 1 means list, 2 means rbtree
  size_t entry_num;  // entry number in bucket
};

struct MckitsHashMap {
  struct MckitsHashMapBucket* buckets;
  size_t entry_num;   // entry number in hashmap
  size_t bucket_num;  // buckets number in hashmap

  // if buckets[i].store.length <= bucket_list_max_num, use list
  // if buckets[i].store.length >  bucket_list_max_num, use rbtree
  size_t bucket_list_max_num;

  // rbtree dumb sentinel node
  struct MckitsRbtreeNode sentinel;

  // seed used in hash_func
  uint64_t seed0;
  uint64_t seed1;
  uint64_t (*hash_func)(void* key, uint64_t seed0, uint64_t seed1);

  // compare function
  int (*compare_func)(void* keya, void* keyb);

  void (*free_key)(void* key);
  void (*free_val)(void* val);
};

/*
@brief: rbtree insert callback function.
*/
static void mckits_rbtree_insert_bucket_entry_value(
    struct MckitsRbtreeNode* root, struct MckitsRbtreeNode* node,
    struct MckitsRbtreeNode* sentinel) {
  struct MckitsRbtreeNode* temp = root;
  struct MckitsRbtreeNode** p = NULL;
  struct MckitsHashMapRbEntry* n = NULL;
  struct MckitsHashMapRbEntry* t = NULL;

  for (;;) {
    n = (struct MckitsHashMapRbEntry*)node;
    t = (struct MckitsHashMapRbEntry*)temp;

    if (node->key != temp->key) {
      p = (node->key < temp->key) ? &temp->left : &temp->right;
    } else {
      p = (n->compare_func(n->key, t->key) < 0) ? &temp->left : &temp->right;
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

/*
@brief: rbtree search function for entry.
*/
static struct MckitsHashMapRbEntry* mckits_rbtree_bucket_entry_lookup(
    struct MckitsRbtree* tree, void* key, uint64_t hash) {
  struct MckitsRbtreeNode* node = tree->root;
  struct MckitsRbtreeNode* sentinel = tree->sentinel;

  while (node != sentinel) {
    struct MckitsHashMapRbEntry* n = (struct MckitsHashMapRbEntry*)node;

    if (hash != node->key) {
      node = (hash < node->key) ? node->left : node->right;
      continue;
    }

    int ret = n->compare_func(key, n->key);

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

/*
@brief: Create a new list entry.
*/
static struct MckitsHashMapEntry* mckits_hashmap_list_entry_new(
    void* key, void* val, uint64_t key_hash) {
  struct MckitsHashMapEntry* entry = (struct MckitsHashMapEntry*)mckits_malloc(
      sizeof(struct MckitsHashMapEntry));
  entry->key = key;
  entry->val = val;
  entry->key_hash = key_hash;
  return entry;
}

/*
@brief: Drop list entry.
*/
static void mckits_hashmap_list_entry_drop(struct MckitsHashMapEntry* entry) {
  mckits_free(entry);
}

/*
@brief: Create a new rbtree entry.
*/
static struct MckitsHashMapRbEntry* mckits_hashmap_rbtree_entry_new(
    void* key, void* val, uint64_t key_hash,
    int (*compare_func)(void* keya, void* keyb)) {
  struct MckitsHashMapRbEntry* entry =
      (struct MckitsHashMapRbEntry*)mckits_malloc(
          sizeof(struct MckitsHashMapRbEntry));
  memset(entry, 0, sizeof(struct MckitsHashMapRbEntry));
  entry->node.key = key_hash;
  entry->compare_func = compare_func;
  entry->key = key;
  entry->val = val;
  return entry;
}

/*
@brief: Drop rbtree entry.
*/
static void mckits_hashmap_rbtree_entry_drop(
    struct MckitsHashMapRbEntry* entry) {
  mckits_free(entry);
}

/*
@brief: Check is bucket is empty.
*/
static int mckits_hashmap_bucket_is_empty(struct MckitsHashMapBucket* bucket) {
  return bucket->entry_num == 0 ? 1 : 0;
}

/*
@brief: Get one entry from bucket, and remove this entry from bucket.
  If store_type == list, remove from list front.
  If store_type == rbtree, remove from tree->root.
@return: pointer to MckitsHashMapEntry
*/
static struct MckitsHashMapEntry* mckits_hashmap_bucket_next_remove(
    struct MckitsHashMapBucket* bucket) {
  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    // remove list front node

    struct MckitsList* list = (struct MckitsList*)bucket->store;
    struct MckitsListNode* front = mckits_list_front(list);
    struct MckitsHashMapEntry* list_entry =
        (struct MckitsHashMapEntry*)mckits_list_remove(list, front);
    mckits_list_node_drop(front);

    bucket->entry_num -= 1;

    return list_entry;
  }

  // bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_RBTREE
  // remove tree root

  struct MckitsRbtree* tree = (struct MckitsRbtree*)bucket->store;
  struct MckitsHashMapRbEntry* rbtree_entry =
      mckits_rbtree_data(tree->root, struct MckitsHashMapRbEntry, node);
  mckits_rbtree_delete(tree, tree->root);

  struct MckitsHashMapEntry* list_entry = mckits_hashmap_list_entry_new(
      rbtree_entry->key, rbtree_entry->val, rbtree_entry->node.key);
  mckits_hashmap_rbtree_entry_drop(rbtree_entry);

  bucket->entry_num -= 1;

  return list_entry;
}

/*
@brief: Calculate bucket index with hash code and bucket_num.
*/
static size_t index_for(uint64_t hash, size_t bucket_num) {
  return hash % bucket_num;
}

/*
@brief: Check if hashmap need grow.
*/
static inline int mckits_hashmap_need_grow(struct MckitsHashMap* map) {
  if (map->entry_num > map->bucket_num * map->bucket_list_max_num) {
    return 1;
  }
  return 0;
}

/*
@brief: Insert new <key, val> into bucket, bucket->store is list.
*/
static void mckits_hashmap_bucket_push_back_list(
    struct MckitsHashMapBucket* bucket, void* key, void* val,
    uint64_t key_hash) {
  struct MckitsList* list = (struct MckitsList*)bucket->store;
  struct MckitsHashMapEntry* list_entry =
      mckits_hashmap_list_entry_new(key, val, key_hash);
  mckits_list_push_back(list, list_entry);
  bucket->entry_num += 1;
}

/*
@brief: Find specified key in bucket, bucket->store is list.
@return: pointer to entry, or NULL if not found.
*/
static struct MckitsHashMapEntry* mckits_hashmap_bucket_find_key_in_list(
    struct MckitsHashMapBucket* bucket, void* key,
    int (*compare_func)(void* keya, void* keyb)) {
  struct MckitsHashMapEntry* entry_founded = NULL;
  struct MckitsList* list = (struct MckitsList*)bucket->store;
  struct MckitsListNode* node = mckits_list_front(list);
  while (node != NULL) {
    struct MckitsHashMapEntry* entry = (struct MckitsHashMapEntry*)node->value;
    if (compare_func(key, entry->key) == 0) {
      entry_founded = entry;
      break;
    }
    node = mckits_list_node_next(node);
  }
  return entry_founded;
}

static struct MckitsHashMapRbEntry* mckits_hashmap_bucket_find_key_in_rbtree(
    struct MckitsHashMapBucket* bucket, void* key) {
  return NULL;
}

/*
@brief: Insert new <key, val> into bucket, bucket->store is rbtree.
*/
static void mckits_hashmap_bucket_insert_into_rbtree(
    struct MckitsHashMapBucket* bucket, void* key, void* val, uint64_t key_hash,
    int (*compare_func)(void* keya, void* keyb)) {
  struct MckitsRbtree* tree = (struct MckitsRbtree*)bucket->store;
  struct MckitsHashMapRbEntry* rbtree_entry =
      mckits_hashmap_rbtree_entry_new(key, val, key_hash, compare_func);
  mckits_rbtree_insert(tree, &rbtree_entry->node);
  bucket->entry_num += 1;
}

/*
@brief: Change bucket store from list to rbtree. It means bucket->entry_num
  reaches map->bucket_list_max_num. Default value is 8 number. It means when
  list->len > 8, it will be changed to red-black-tree.
*/
static void mckits_hashmap_bucket_list_to_rbtree(
    struct MckitsHashMap* map, struct MckitsHashMapBucket* bucket) {
  // new tree
  struct MckitsRbtree* tree =
      (struct MckitsRbtree*)mckits_malloc(sizeof(struct MckitsRbtree));
  mckits_rbtree_init(tree, &map->sentinel,
                     mckits_rbtree_insert_bucket_entry_value);

  // old list
  struct MckitsList* list = (struct MckitsList*)bucket->store;

  // move entry from old list to new tree
  while (mckits_list_len(list) > 0) {
    struct MckitsListNode* node = mckits_list_front(list);
    void* value = mckits_list_remove(list, node);
    mckits_list_node_drop(node);
    struct MckitsHashMapEntry* list_entry = (struct MckitsHashMapEntry*)value;

    struct MckitsHashMapRbEntry* rbtree_entry = mckits_hashmap_rbtree_entry_new(
        list_entry->key, list_entry->val, list_entry->key_hash,
        map->compare_func);
    mckits_rbtree_insert(tree, &rbtree_entry->node);

    mckits_hashmap_list_entry_drop(list_entry);
  }

  // drop old list
  mckits_list_drop(list, NULL);

  // set new tree
  bucket->store = tree;
  bucket->store_type = MCKITS_HASHMAP_BUCKET_STORE_TYPE_RBTREE;
}

/*
@brief: Insert new <key, val> into bucket.
@param map[in]: hashmap handler.
@param bucket[in]: new <key, val> will insert into this bucket.
*/
static void mckits_hashmap_bucket_insert(struct MckitsHashMap* map,
                                         struct MckitsHashMapBucket* bucket,
                                         void* key, void* val,
                                         uint64_t key_hash) {
  if (bucket->store == NULL) {
    // bucket has not been initialized

    struct MckitsList* list = mckits_list_new();
    bucket->store = list;
    bucket->store_type = MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST;
    bucket->entry_num = 0;

    mckits_hashmap_bucket_push_back_list(bucket, key, val, key_hash);

    return;
  }

  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    // try to find key in list
    struct MckitsHashMapEntry* entry_founded =
        mckits_hashmap_bucket_find_key_in_list(bucket, key, map->compare_func);

    // found key in list, just replace value
    if (entry_founded != NULL) {
      void* old_val = entry_founded->val;
      entry_founded->val = val;
      if (map->free_val != NULL) {
        map->free_val(old_val);
      }
      return;
    }

    // not found key, and list not reach max num.
    // just push new <key, value> into list.
    if (bucket->entry_num < map->bucket_list_max_num) {
      mckits_hashmap_bucket_push_back_list(bucket, key, val, key_hash);
      return;
    }

    // not found key, and list reach max num.
    // change bucket->store from list to rbtree
    mckits_hashmap_bucket_list_to_rbtree(map, bucket);

    // insert into rbtree
    mckits_hashmap_bucket_insert_into_rbtree(bucket, key, val, key_hash,
                                             map->compare_func);

    return;
  }

  // try to find key in rbtree
}

/*
@brief: Check if hashmap need grow size, if needed, malloc new memory, and move
  all <key, value> to new memory.
*/
static void mckits_hashmap_grow_size(struct MckitsHashMap* map) {
  if (!mckits_hashmap_need_grow(map)) {
    return;
  }

  // create new buckets
  size_t new_bucket_num = map->bucket_num * 2;
  struct MckitsHashMapBucket* new_buckets =
      (struct MckitsHashMapBucket*)mckits_calloc(
          new_bucket_num, sizeof(struct MckitsHashMapBucket));

  // move entries from old buckets to new buckets
  for (size_t i = 0; i < map->bucket_num; ++i) {
    struct MckitsHashMapBucket* bucket = &map->buckets[i];
    while (!mckits_hashmap_bucket_is_empty(bucket)) {
      struct MckitsHashMapEntry* entry =
          mckits_hashmap_bucket_next_remove(bucket);

      size_t new_bucket_index = index_for(entry->key_hash, new_bucket_num);
      struct MckitsHashMapBucket* new_bucket = &new_buckets[new_bucket_index];
      mckits_hashmap_bucket_insert(map, new_bucket, entry->key, entry->val,
                                   entry->key_hash);

      mckits_hashmap_list_entry_drop(entry);
    }
  }
}

struct MckitsHashMap* mckits_hashmap_new() {
  struct MckitsHashMap* map =
      (struct MckitsHashMap*)mckits_malloc(sizeof(struct MckitsHashMap));
  memset(map, 0, sizeof(struct MckitsHashMap));

  map->entry_num = 0;
  map->bucket_num = 16;
  map->buckets = (struct MckitsHashMapBucket*)mckits_calloc(
      map->bucket_num, sizeof(struct MckitsHashMapBucket));

  map->bucket_list_max_num = 8;

  mckits_rbtree_sentinel_init(&map->sentinel);

  return map;
}

void mckits_hashmap_drop(struct MckitsHashMap* map) {}

void mckits_hashmap_clear(struct MckitsHashMap* map) {}

size_t mckits_hashmap_len(struct MckitsHashMap* map) { return map->entry_num; }

int mckits_hashmap_is_empty(struct MckitsHashMap* map) {
  return map->entry_num == 0 ? 1 : 0;
}

void mckits_hashmap_insert(struct MckitsHashMap* map, void* key, void* val) {
  mckits_hashmap_grow_size(map);

  uint64_t hash = map->hash_func(key, map->seed0, map->seed1);
  size_t bucket_index = index_for(hash, map->bucket_num);
  struct MckitsHashMapBucket* bucket = &map->buckets[bucket_index];
  mckits_hashmap_bucket_insert(map, bucket, key, val, hash);
  map->entry_num += 1;
}

void mckits_hashmap_remove(struct MckitsHashMap* map, void* key) {}

void* mckits_hashmap_get(struct MckitsHashMap* map, void* key) { return NULL; }

int mckits_hashmap_contains_key(struct MckitsHashMap* map, void* key) {
  return 0;
}
