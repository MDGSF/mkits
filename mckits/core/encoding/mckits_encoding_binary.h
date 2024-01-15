#ifndef MKITS_MCKITS_CORE_MCKITS_ENCODING_BINARY_H_
#define MKITS_MCKITS_CORE_MCKITS_ENCODING_BINARY_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void mckits_little_endian_encode_u16(uint16_t v, uint8_t* b);
uint16_t mckits_little_endian_decode_u16(const uint8_t* b);
void mckits_little_endian_encode_u32(uint32_t v, uint8_t* b);
uint32_t mckits_little_endian_decode_u32(const uint8_t* b);
void mckits_little_endian_encode_u64(uint64_t v, uint8_t* b);
uint64_t mckits_little_endian_decode_u64(const uint8_t* b);

void mckits_big_endian_encode_u16(uint16_t v, uint8_t* b);
uint16_t mckits_big_endian_decode_u16(const uint8_t* b);
void mckits_big_endian_encode_u32(uint32_t v, uint8_t* b);
uint32_t mckits_big_endian_decode_u32(const uint8_t* b);
void mckits_big_endian_encode_u64(uint64_t v, uint8_t* b);
uint64_t mckits_big_endian_decode_u64(const uint8_t* b);

#ifdef __cplusplus
}
#endif

#endif
