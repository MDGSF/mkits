// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
#ifndef MKITS_MCKITS_MCKITS_HASH_FNV_H_
#define MKITS_MCKITS_MCKITS_HASH_FNV_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t fnv_1_32(const uint8_t* data, size_t size);
uint32_t fnv_1a_32(const uint8_t* data, size_t size);
uint64_t fnv_1_64(const uint8_t* data, size_t size);
uint64_t fnv_1a_64(const uint8_t* data, size_t size);

#ifdef __cplusplus
}
#endif

#endif
