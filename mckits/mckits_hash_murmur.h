/*
murmur hash function.
wiki: https://en.wikipedia.org/wiki/MurmurHash
*/
#ifndef MKITS_MCKITS_MCKITS_HASH_MURMUR_H_
#define MKITS_MCKITS_MCKITS_HASH_MURMUR_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Calculate hash code use murmur2 hash function.
@param data[in]: Input data.
@param len[in]: Input data size in bytes.
@return hash code
*/
uint32_t mckits_murmur2_32(const uint8_t* data, size_t len);

#ifdef __cplusplus
}
#endif

#endif
