#include "mckits_hashmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_hash_fnv.h"
#include "mckits_list.h"
#include "mckits_malloc.h"
#include "mckits_rbtree.h"

#define MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST 0
#define MCKITS_HASHMAP_BUCKET_STORE_TYPE_RBTREE 1

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
  uint64_t key_hash;
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
@brief: Calculate bucket index with hash code and bucket_num.
*/
static inline size_t index_for(uint64_t hash, size_t bucket_num) {
  return hash % bucket_num;
}

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
  entry->key_hash = key_hash;
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
      rbtree_entry->key, rbtree_entry->val, rbtree_entry->key_hash);
  mckits_hashmap_rbtree_entry_drop(rbtree_entry);

  bucket->entry_num -= 1;

  return list_entry;
}

static struct MckitsListNode* mckits_hashmap_bucket_find_node_int_list(
    struct MckitsList* list, void* key,
    int (*compare_func)(void* keya, void* keyb)) {
  struct MckitsListNode* node = mckits_list_front(list);
  while (node != NULL) {
    struct MckitsHashMapEntry* entry = (struct MckitsHashMapEntry*)node->value;
    if (compare_func(key, entry->key) == 0) {
      return node;
    }
    node = mckits_list_node_next(node);
  }
  return NULL;
}

/*
@brief: Remove key in bucket, return pointer to value.
*/
static void* mckits_hashmap_bucket_remove_key(
    struct MckitsHashMap* map, struct MckitsHashMapBucket* bucket, void* key,
    uint64_t key_hash) {
  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    // remove key from list

    struct MckitsList* list = (struct MckitsList*)bucket->store;

    struct MckitsListNode* node =
        mckits_hashmap_bucket_find_node_int_list(list, key, map->compare_func);
    if (node == NULL) {
      return NULL;
    }

    struct MckitsHashMapEntry* entry = mckits_list_remove(list, node);
    mckits_list_node_drop(node);

    if (map->free_key != NULL) {
      map->free_key(entry->key);
    }
    void* val = entry->val;
    mckits_hashmap_list_entry_drop(entry);

    bucket->entry_num -= 1;

    return val;
  }

  // remove key from rbtree

  struct MckitsRbtree* tree = (struct MckitsRbtree*)bucket->store;

  struct MckitsHashMapRbEntry* entry =
      mckits_rbtree_bucket_entry_lookup(tree, key, key_hash);
  if (entry == NULL) {
    return NULL;
  }

  mckits_rbtree_delete(tree, &entry->node);

  if (map->free_key != NULL) {
    map->free_key(entry->key);
  }
  void* val = entry->val;
  mckits_hashmap_rbtree_entry_drop(entry);

  bucket->entry_num -= 1;

  return val;
}

struct MckitsHashMapBucket* mckits_hashmap_buckets_new(size_t bucket_num) {
  return mckits_calloc(bucket_num, sizeof(struct MckitsHashMapBucket));
}

void mckits_hashmap_buckets_free(struct MckitsHashMapBucket* buckets) {
  mckits_free(buckets);
}

/*
@brief: Drop bucket store. Must sure bucket is empty.
*/
static void mckits_hashmap_bucket_drop_store(
    struct MckitsHashMapBucket* bucket) {
  if (bucket->store == NULL) {
    return;
  }

  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    // drop list
    struct MckitsList* list = (struct MckitsList*)bucket->store;
    mckits_list_drop(list, NULL);
    bucket->store = NULL;
    return;
  }

  // drop rbtree
  struct MckitsRbtree* tree = (struct MckitsRbtree*)bucket->store;
  mckits_free(tree);
  bucket->store = NULL;
  bucket->store_type = MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST;
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
@brief: Find specified key in bucket, bucket->store is list.
@return: pointer to entry, or NULL if not found.
*/
static struct MckitsHashMapEntry* mckits_hashmap_bucket_find_entry_in_list(
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

/*
@brief: Find specified key in bucket, bucket->store is rbtree.
@return: pointer to entry, or NULL if not found.
*/
static struct MckitsHashMapRbEntry* mckits_hashmap_bucket_find_entry_in_rbtree(
    struct MckitsHashMapBucket* bucket, void* key, uint64_t key_hash) {
  struct MckitsRbtree* tree = (struct MckitsRbtree*)bucket->store;
  struct MckitsHashMapRbEntry* entry =
      mckits_rbtree_bucket_entry_lookup(tree, key, key_hash);
  return entry;
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
@return
  1: key not found in hashmap
  0: key founded in hashamp
*/
static int mckits_hashmap_bucket_insert(struct MckitsHashMap* map,
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

    return 1;
  }

  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    // try to find key in list
    struct MckitsHashMapEntry* entry_founded =
        mckits_hashmap_bucket_find_entry_in_list(bucket, key,
                                                 map->compare_func);

    // found key in list, just replace value
    if (entry_founded != NULL) {
      void* old_key = entry_founded->key;
      void* old_val = entry_founded->val;
      entry_founded->key = key;
      entry_founded->val = val;
      if (map->free_key != NULL) {
        map->free_key(old_key);
      }
      if (map->free_val != NULL) {
        map->free_val(old_val);
      }
      return 0;
    }

    // not found key, and list not reach max num.
    // just push new <key, value> into list.
    if (bucket->entry_num < map->bucket_list_max_num) {
      mckits_hashmap_bucket_push_back_list(bucket, key, val, key_hash);
      return 1;
    }

    // not found key, and list reach max num.
    // change bucket->store from list to rbtree
    mckits_hashmap_bucket_list_to_rbtree(map, bucket);

    // insert into rbtree
    mckits_hashmap_bucket_insert_into_rbtree(bucket, key, val, key_hash,
                                             map->compare_func);

    return 1;
  }

  // try to find key in rbtree
  struct MckitsHashMapRbEntry* entry =
      mckits_hashmap_bucket_find_entry_in_rbtree(bucket, key, key_hash);

  // found key in rbtree, just replace value
  if (entry != NULL) {
    void* old_key = entry->key;
    void* old_val = entry->val;
    entry->key = key;
    entry->val = val;
    if (map->free_key != NULL) {
      map->free_key(old_key);
    }
    if (map->free_val != NULL) {
      map->free_val(old_val);
    }
    return 0;
  }

  // not found key, insert into rbtree
  mckits_hashmap_bucket_insert_into_rbtree(bucket, key, val, key_hash,
                                           map->compare_func);
  return 1;
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
      mckits_hashmap_buckets_new(new_bucket_num);

  // move entries from old buckets to new buckets
  for (size_t i = 0; i < map->bucket_num; ++i) {
    struct MckitsHashMapBucket* bucket = &map->buckets[i];

    // move current bucket's entries to new buckets
    while (!mckits_hashmap_bucket_is_empty(bucket)) {
      struct MckitsHashMapEntry* entry =
          mckits_hashmap_bucket_next_remove(bucket);

      size_t new_bucket_index = index_for(entry->key_hash, new_bucket_num);
      struct MckitsHashMapBucket* new_bucket = &new_buckets[new_bucket_index];
      (void)mckits_hashmap_bucket_insert(map, new_bucket, entry->key,
                                         entry->val, entry->key_hash);

      mckits_hashmap_list_entry_drop(entry);
    }

    // drop current bucket store
    mckits_hashmap_bucket_drop_store(bucket);
  }

  // drop old buckets
  mckits_hashmap_buckets_free(map->buckets);

  // set new buckets to hashmap
  map->buckets = new_buckets;
  map->bucket_num = new_bucket_num;
}

struct MckitsHashMap* mckits_hashmap_new() {
  return mckits_hashmap_with_capacity(16);
}

struct MckitsHashMap* mckits_hashmap_with_capacity(size_t capacity) {
  struct MckitsHashMap* map =
      (struct MckitsHashMap*)mckits_malloc(sizeof(struct MckitsHashMap));
  memset(map, 0, sizeof(struct MckitsHashMap));

  map->entry_num = 0;
  map->bucket_num = capacity;
  map->buckets = mckits_hashmap_buckets_new(map->bucket_num);

  map->bucket_list_max_num = 8;

  mckits_rbtree_sentinel_init(&map->sentinel);

  return map;
}

void mckits_hashmap_set_hashfunc(struct MckitsHashMap* map,
                                 uint64_t (*hash_func)(void* key,
                                                       uint64_t seed0,
                                                       uint64_t seed1)) {
  map->hash_func = hash_func;
}

void mckits_hashmap_set_seed0(struct MckitsHashMap* map, uint64_t seed0) {
  map->seed0 = seed0;
}

void mckits_hashmap_set_seed1(struct MckitsHashMap* map, uint64_t seed1) {
  map->seed1 = seed1;
}

void mckits_hashmap_set_compare_func(struct MckitsHashMap* map,
                                     int (*compare_func)(void* keya,
                                                         void* keyb)) {
  map->compare_func = compare_func;
}

void mckits_hashmap_set_free_key(struct MckitsHashMap* map,
                                 void (*free_key)(void* key)) {
  map->free_key = free_key;
}

void mckits_hashmap_set_free_val(struct MckitsHashMap* map,
                                 void (*free_val)(void* val)) {
  map->free_val = free_val;
}

void mckits_hashmap_drop(struct MckitsHashMap* map) {
  mckits_hashmap_clear(map);
  mckits_hashmap_buckets_free(map->buckets);
  mckits_free(map);
}

void mckits_hashmap_bucket_list_clear(struct MckitsHashMap* map,
                                      struct MckitsHashMapBucket* bucket) {
  struct MckitsList* list = (struct MckitsList*)bucket->store;
  while (mckits_list_len(list) > 0) {
    struct MckitsListNode* front = mckits_list_front(list);
    struct MckitsHashMapEntry* entry =
        (struct MckitsHashMapEntry*)mckits_list_remove(list, front);
    mckits_list_node_drop(front);

    if (map->free_key != NULL) {
      map->free_key(entry->key);
    }
    if (map->free_val != NULL) {
      map->free_val(entry->val);
    }

    mckits_hashmap_list_entry_drop(entry);

    bucket->entry_num -= 1;
    map->entry_num -= 1;
  }
  mckits_list_drop(list, NULL);
  bucket->store = NULL;
}

void mckits_hashmap_bucket_rbtree_clear(struct MckitsHashMap* map,
                                        struct MckitsHashMapBucket* bucket) {
  struct MckitsRbtree* tree = (struct MckitsRbtree*)bucket->store;
  while (tree->root != tree->sentinel) {
    struct MckitsHashMapRbEntry* entry =
        mckits_rbtree_data(tree->root, struct MckitsHashMapRbEntry, node);
    mckits_rbtree_delete(tree, tree->root);

    if (map->free_key != NULL) {
      map->free_key(entry->key);
    }
    if (map->free_val != NULL) {
      map->free_val(entry->val);
    }

    mckits_hashmap_rbtree_entry_drop(entry);

    bucket->entry_num -= 1;
    map->entry_num -= 1;
  }

  mckits_free(tree);
  bucket->store = NULL;
  bucket->store_type = MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST;
}

void mckits_hashmap_bucket_clear(struct MckitsHashMap* map,
                                 struct MckitsHashMapBucket* bucket) {
  if (bucket->store == NULL) {
    return;
  }

  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    mckits_hashmap_bucket_list_clear(map, bucket);
  } else {
    mckits_hashmap_bucket_rbtree_clear(map, bucket);
  }
}

void mckits_hashmap_clear(struct MckitsHashMap* map) {
  for (size_t i = 0; i < map->bucket_num; ++i) {
    struct MckitsHashMapBucket* bucket = &map->buckets[i];
    mckits_hashmap_bucket_clear(map, bucket);
  }
}

size_t mckits_hashmap_len(struct MckitsHashMap* map) { return map->entry_num; }

int mckits_hashmap_is_empty(struct MckitsHashMap* map) {
  return map->entry_num == 0 ? 1 : 0;
}

void mckits_hashmap_insert(struct MckitsHashMap* map, void* key, void* val) {
  mckits_hashmap_grow_size(map);

  uint64_t key_hash = map->hash_func(key, map->seed0, map->seed1);
  size_t bucket_index = index_for(key_hash, map->bucket_num);
  struct MckitsHashMapBucket* bucket = &map->buckets[bucket_index];
  int added_num = mckits_hashmap_bucket_insert(map, bucket, key, val, key_hash);
  map->entry_num += added_num;
}

void* mckits_hashmap_remove(struct MckitsHashMap* map, void* key) {
  uint64_t key_hash = map->hash_func(key, map->seed0, map->seed1);
  size_t bucket_index = index_for(key_hash, map->bucket_num);
  struct MckitsHashMapBucket* bucket = &map->buckets[bucket_index];

  if (mckits_hashmap_bucket_is_empty(bucket)) {
    return NULL;
  }

  void* value = mckits_hashmap_bucket_remove_key(map, bucket, key, key_hash);
  map->entry_num -= 1;
  return value;
}

void* mckits_hashmap_get(struct MckitsHashMap* map, void* key) {
  uint64_t key_hash = map->hash_func(key, map->seed0, map->seed1);
  size_t bucket_index = index_for(key_hash, map->bucket_num);
  struct MckitsHashMapBucket* bucket = &map->buckets[bucket_index];

  if (mckits_hashmap_bucket_is_empty(bucket)) {
    return NULL;
  }

  void* value = NULL;
  if (bucket->store_type == MCKITS_HASHMAP_BUCKET_STORE_TYPE_LIST) {
    struct MckitsHashMapEntry* entry = mckits_hashmap_bucket_find_entry_in_list(
        bucket, key, map->compare_func);
    if (entry != NULL) {
      value = entry->val;
    }
  } else {
    struct MckitsHashMapRbEntry* entry =
        mckits_hashmap_bucket_find_entry_in_rbtree(bucket, key, key_hash);
    if (entry != NULL) {
      value = entry->val;
    }
  }

  return value;
}

int mckits_hashmap_contains_key(struct MckitsHashMap* map, void* key) {
  void* value = mckits_hashmap_get(map, key);
  return value != NULL ? 1 : 0;
}

uint64_t hash_func_fnv_1a_64(const void* data, size_t len, uint64_t seed0,
                             uint64_t seed1) {
  (void)seed0;
  (void)seed1;
  return mckits_fnv_1a_64(data, len);
}

void mckits_hashmap_dbg(struct MckitsHashMap* map) {
  printf("-----------------------------------\n");
  printf("hashmap->entry_num = %zu\n", map->entry_num);
  printf("hashmap->bucket_num = %zu\n", map->bucket_num);
  printf("hashmap->buckets = %p\n", map->buckets);
  for (size_t i = 0; i < map->bucket_num; ++i) {
    struct MckitsHashMapBucket* bucket = &map->buckets[i];
    printf("[%02zu]<%p> [%s] entry_num:%zu\n", i, bucket,
           bucket->store_type == 0 ? "list" : "rbtree", bucket->entry_num);
  }
  printf("-----------------------------------\n");
}
