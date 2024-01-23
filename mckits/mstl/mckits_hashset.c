#include "mckits_hashset.h"

#include "mckits_hashmap.h"
#include "mckits_malloc.h"

struct MckitsHashSet {
  struct MckitsHashMap* map;
};

struct MckitsHashSet* mckits_hashset_new() {
  struct MckitsHashSet* mset =
      (struct MckitsHashSet*)mckits_malloc(sizeof(struct MckitsHashSet));
  mset->map = mckits_hashmap_new();
  return mset;
}

struct MckitsHashSet* mckits_hashset_with_capacity(size_t capacity) {
  struct MckitsHashSet* mset =
      (struct MckitsHashSet*)mckits_malloc(sizeof(struct MckitsHashSet));
  mset->map = mckits_hashmap_with_capacity(capacity);
  return mset;
}

void mckits_hashset_set_hashfunc(struct MckitsHashSet* mset,
                                 uint64_t (*hash_func)(void* value,
                                                       uint64_t seed0,
                                                       uint64_t seed1)) {
  mckits_hashmap_set_hashfunc(mset->map, hash_func);
}

void mckits_hashset_set_seed0(struct MckitsHashSet* mset, uint64_t seed0) {
  mckits_hashmap_set_seed0(mset->map, seed0);
}

void mckits_hashset_set_seed1(struct MckitsHashSet* mset, uint64_t seed1) {
  mckits_hashmap_set_seed1(mset->map, seed1);
}

void mckits_hashset_set_compare_func(struct MckitsHashSet* mset,
                                     int (*compare_func)(void* a, void* b)) {
  mckits_hashmap_set_compare_func(mset->map, compare_func);
}

void mckits_hashset_set_free_value(struct MckitsHashSet* mset,
                                   void (*free_value)(void* value)) {
  mckits_hashmap_set_free_key(mset->map, free_value);
}

void mckits_hashset_drop(struct MckitsHashSet* mset) {
  mckits_hashmap_drop(mset->map);
}

void mckits_hashset_clear(struct MckitsHashSet* mset) {
  mckits_hashmap_clear(mset->map);
}

size_t mckits_hashset_len(struct MckitsHashSet* mset) {
  return mckits_hashmap_len(mset->map);
}

int mckits_hashset_is_empty(struct MckitsHashSet* mset) {
  return mckits_hashmap_is_empty(mset->map);
}

void mckits_hashset_insert(struct MckitsHashSet* mset, void* value) {
  mckits_hashmap_insert(mset->map, value, value);
}

int mckits_hashset_remove(struct MckitsHashSet* mset, void* value) {
  void* ptr = mckits_hashmap_remove(mset->map, value);
  return ptr != NULL ? 1 : 0;
}

int mckits_hashset_contains(struct MckitsHashSet* mset, void* value) {
  return mckits_hashmap_contains_key(mset->map, value);
}

uint64_t mckits_hashset_hash_func_fnv_1a_64(const void* data, size_t len,
                                            uint64_t seed0, uint64_t seed1) {
  return mckits_hashmap_hash_func_fnv_1a_64(data, len, seed0, seed1);
}
