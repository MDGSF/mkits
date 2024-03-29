#ifndef MKITS_INCLUDE_MCKITS_MSTL_MCKITS_HASHMAP_H_
#define MKITS_INCLUDE_MCKITS_MSTL_MCKITS_HASHMAP_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: hashmap
*/
struct MckitsHashMap;

/*
@brief: Create a new hashmap.
*/
struct MckitsHashMap* mckits_hashmap_new();

/*
@brief: Create a new hashmap with capacity.
*/
struct MckitsHashMap* mckits_hashmap_with_capacity(size_t capacity);

/*
@brief: Set hash function, it will be used to calculated key hash.
*/
void mckits_hashmap_set_hashfunc(struct MckitsHashMap* map,
                                 uint64_t (*hash_func)(void* key,
                                                       uint64_t seed0,
                                                       uint64_t seed1));

/*
@brief: Set seed0, used in hash function.
*/
void mckits_hashmap_set_seed0(struct MckitsHashMap* map, uint64_t seed0);

/*
@brief: Set seed1, used in hash function.
*/
void mckits_hashmap_set_seed1(struct MckitsHashMap* map, uint64_t seed1);

/*
@brief: Set compare function, it will be used to compare to two key.
*/
void mckits_hashmap_set_compare_func(struct MckitsHashMap* map,
                                     int (*compare_func)(void* keya,
                                                         void* keyb));

/*
@brief: Set free key function. If your key need to free, you need to set this
  function. If your key doesn't need to free, you can set it to NULL. Default
  is NULL.
*/
void mckits_hashmap_set_free_key(struct MckitsHashMap* map,
                                 void (*free_key)(void* key));

/*
@brief: Set free value function. If your value need to free, you need to set
  this function. If your value doesn't need to free, you can set it to NULL.
  Default is NULL.
*/
void mckits_hashmap_set_free_val(struct MckitsHashMap* map,
                                 void (*free_val)(void* val));

/*
@brief: Drop the hashmap. After call this function, hashmap object can't be
  used again.
*/
void mckits_hashmap_drop(struct MckitsHashMap* map);

/*
@brief: Clear the hashmap. Remove all entries. Your can insert after call this
  function.
*/
void mckits_hashmap_clear(struct MckitsHashMap* map);

/*
@brief: Return hashmap current entry number.
*/
size_t mckits_hashmap_len(struct MckitsHashMap* map);

/*
@brief: Check if hashmap is empty.
@return:
  1: means hashmap is empty.
  0: means hashmap is not empty.
*/
int mckits_hashmap_is_empty(struct MckitsHashMap* map);

/*
@brief: Insert new <key, val> into hashmap.
*/
void mckits_hashmap_insert(struct MckitsHashMap* map, void* key, void* val);

/*
@brief: Remove key from hashmap, return pointer to value.
@param val[out]: output value. If you don't want value, pass NULL.
@return:
  If key exists, return 1.
  If key not exists, return 0.
*/
int mckits_hashmap_remove(struct MckitsHashMap* map, void* key, void** value);

/*
@brief: Query key in hashmap.
@param map[in]: hashmap.
@param key[in]: key will be find in hashmap.
@param val[out]: output value.
@return:
  If found, return 1
  If not found, return 0.
*/
int mckits_hashmap_get(struct MckitsHashMap* map, void* key, void** value);

/*
@brief: Check if hashmap contains key.
@return:
  1: means hashmap contains key.
  0: means hashmap doesn't contains key.
*/
int mckits_hashmap_contains_key(struct MckitsHashMap* map, void* key);

/*
@brief: hash function fnv_1a_64.
  you can use it in `mckits_hashmap_set_hashfunc()`.
*/
uint64_t mckits_hashmap_hash_func_fnv_1a_64(const void* data, size_t len,
                                            uint64_t seed0, uint64_t seed1);

/*
@brief: hashmap iterator.
*/
struct MckitsHashMapIter;

/*
@brief: Create a new hashmap iterator. If hashmap insert or remove entry,
  iterator will invalid.
*/
struct MckitsHashMapIter* mckits_hashmap_iterator(struct MckitsHashMap* map);

/*
@brief: Get next value from iterator.
@param iterator[in]: iterator for hashmap.
@param value[out]: output value.
@return 1 means has next value, 0 means reached end of hashmap.
*/
int mckits_hashmap_iterator_next(struct MckitsHashMapIter* iterator,
                                 void** value);

/*
@brief: Drop hashmap iterator.
*/
void mckits_hashmap_iterator_drop(struct MckitsHashMapIter* iterator);

/*
@brief: Debug function, show some basic information.
*/
void mckits_hashmap_dbg(struct MckitsHashMap* map);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_MSTL_MCKITS_HASHMAP_H_
