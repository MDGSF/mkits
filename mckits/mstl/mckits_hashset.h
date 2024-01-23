#ifndef MKITS_MCKITS_MSTL_MCKITS_HASHSET_H_
#define MKITS_MCKITS_MSTL_MCKITS_HASHSET_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: hashset
*/
struct MckitsHashSet;

/*
@brief: Create a new hashset.
*/
struct MckitsHashSet* mckits_hashset_new();

/*
@brief: Create a new hashset with capacity.
*/
struct MckitsHashSet* mckits_hashset_with_capacity(size_t capacity);

/*
@brief: Set hash function, it will be used to calculated value hash.
*/
void mckits_hashset_set_hashfunc(struct MckitsHashSet* mset,
                                 uint64_t (*hash_func)(void* value,
                                                       uint64_t seed0,
                                                       uint64_t seed1));

/*
@brief: Set seed0, used in hash function.
*/
void mckits_hashset_set_seed0(struct MckitsHashSet* mset, uint64_t seed0);

/*
@brief: Set seed1, used in hash function.
*/
void mckits_hashset_set_seed1(struct MckitsHashSet* mset, uint64_t seed1);

/*
@brief: Set compare function, it will be used to compare to two value.
*/
void mckits_hashset_set_compare_func(struct MckitsHashSet* mset,
                                     int (*compare_func)(void* a, void* b));

/*
@brief: Set free value function. If your value need to free, you need to set
this function. If your value doesn't need to free, you can set it to NULL.
Default is NULL.
*/
void mckits_hashset_set_free_value(struct MckitsHashSet* mset,
                                   void (*free_value)(void* value));

/*
@brief: Drop the hashset. After call this function, hashset object can't be
  used again.
*/
void mckits_hashset_drop(struct MckitsHashSet* mset);

/*
@brief: Clear the hashset. Remove all values. Your can insert after call this
  function.
*/
void mckits_hashset_clear(struct MckitsHashSet* mset);

/*
@brief: Returns the number of elements in the set.
*/
size_t mckits_hashset_len(struct MckitsHashSet* mset);

/*
@brief: Returns true if the set contains no elements.
@return:
  1: means hashset is empty.
  0: means hashset is not empty.
*/
int mckits_hashset_is_empty(struct MckitsHashSet* mset);

/*
@brief: Insert new value into hashset.
*/
void mckits_hashset_insert(struct MckitsHashSet* mset, void* value);

/*
@brief: Removes a value from the set. Returns whether the value was present in
  the set.
@return:
  1: the value was present in the set.
  0: the value was not present int the set.
*/
int mckits_hashset_remove(struct MckitsHashSet* mset, void* value);

/*
@brief: Check if hashset contains value.
@return:
  1: means hashset contains value.
  0: means hashset doesn't contains value.
*/
int mckits_hashset_contains(struct MckitsHashSet* mset, void* value);

/*
@brief: hash function fnv_1a_64.
  you can use it in `mckits_hashset_set_hashfunc()`.
*/
uint64_t mckits_hashset_hash_func_fnv_1a_64(const void* data, size_t len,
                                            uint64_t seed0, uint64_t seed1);

#ifdef __cplusplus
}
#endif

#endif
