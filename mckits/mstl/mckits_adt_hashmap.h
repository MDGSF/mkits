#ifndef MKITS_MCKITS_MSTL_MCKITS_ADT_HASHMAP_H_
#define MKITS_MCKITS_MSTL_MCKITS_ADT_HASHMAP_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsHashMap;
struct MckitsHashMap* mckits_hashmap_new();
void mckits_hashmap_set_hashfunc(struct MckitsHashMap* map,
                                 uint64_t (*hash_func)(void* key,
                                                       uint64_t seed0,
                                                       uint64_t seed1));
void mckits_hashmap_set_seed0(struct MckitsHashMap* map, uint64_t seed0);
void mckits_hashmap_set_seed1(struct MckitsHashMap* map, uint64_t seed1);
void mckits_hashmap_set_compare_func(struct MckitsHashMap* map,
                                     int (*compare_func)(void* keya,
                                                         void* keyb));
void mckits_hashmap_set_free_key(struct MckitsHashMap* map,
                                 void (*free_key)(void* key));
void mckits_hashmap_set_free_val(struct MckitsHashMap* map,
                                 void (*free_val)(void* val));

void mckits_hashmap_drop(struct MckitsHashMap* map);
void mckits_hashmap_clear(struct MckitsHashMap* map);
size_t mckits_hashmap_len(struct MckitsHashMap* map);
int mckits_hashmap_is_empty(struct MckitsHashMap* map);
void mckits_hashmap_insert(struct MckitsHashMap* map, void* key, void* val);
void* mckits_hashmap_remove(struct MckitsHashMap* map, void* key);
void* mckits_hashmap_get(struct MckitsHashMap* map, void* key);
int mckits_hashmap_contains_key(struct MckitsHashMap* map, void* key);

uint64_t hash_func_fnv_1a_64(const void* data, size_t len, uint64_t seed0,
                             uint64_t seed1);

#ifdef __cplusplus
}
#endif

#endif
