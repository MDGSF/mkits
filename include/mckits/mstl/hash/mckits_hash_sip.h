#ifndef MKITS_INCLUDE_MCKITS_MSTL_HASH_MCKITS_HASH_SIP_H_
#define MKITS_INCLUDE_MCKITS_MSTL_HASH_MCKITS_HASH_SIP_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Calculate hash code.
@param data[in]: Input data.
@param len[in]: Input data size in bytes.
@param seed0[in]: hash code initialize value.
@param seed1[in]: hash code initialize value.
@return hash code
*/
uint64_t mckits_hash_sip(const uint8_t *data, size_t len, uint64_t seed0,
                         uint64_t seed1);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_MSTL_HASH_MCKITS_HASH_SIP_H_
