#ifndef MKITS_INCLUDE_MCKITS_MSTL_HASH_MCKITS_HASH_XXHASH_H_
#define MKITS_INCLUDE_MCKITS_MSTL_HASH_MCKITS_HASH_XXHASH_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Calculate hash code.
@param data[in]: Input data.
@param len[in]: Input data size in bytes.
@param seed[in]: hash code initialize value.
@return hash code
*/
uint64_t mckits_hash_xxhash3(const uint8_t* data, size_t len, uint64_t seed);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_MSTL_HASH_MCKITS_HASH_XXHASH_H_
