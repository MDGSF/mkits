/*
Murmur hash function. MurmurHash is a non-cryptographic hash function suitable
for general hash-based lookup.
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
@brief: Calculate hash code use murmur3 hash function.
@param data[in]: Input data.
@param len[in]: Input data size in bytes.
@param seed[in]: hash code initialize value.
@return hash code
*/
uint32_t mckits_murmur3_32(const uint8_t* data, size_t len, uint32_t seed);

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
