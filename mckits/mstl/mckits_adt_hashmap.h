#ifndef MKITS_MCKITS_MSTL_MCKITS_ADT_HASHMAP_H_
#define MKITS_MCKITS_MSTL_MCKITS_ADT_HASHMAP_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsHashMap;
struct MckitsHashMap* mckits_hashmap_new();
void mckits_hashmap_drop(struct MckitsHashMap* map);
void mckits_hashmap_clear(struct MckitsHashMap* map);
size_t mckits_hashmap_len(struct MckitsHashMap* map);
int mckits_hashmap_is_empty(struct MckitsHashMap* map);
void mckits_hashmap_insert(struct MckitsHashMap* map, void* key, void* val);
void mckits_hashmap_remove(struct MckitsHashMap* map, void* key);
void* mckits_hashmap_get(struct MckitsHashMap* map, void* key);
int mckits_hashmap_contains_key(struct MckitsHashMap* map, void* key);

#ifdef __cplusplus
}
#endif

#endif
