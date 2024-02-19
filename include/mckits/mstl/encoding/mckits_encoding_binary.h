#ifndef MKITS_INCLUDE_MCKITS_MSTL_ENCODING_MCKITS_ENCODING_BINARY_H_
#define MKITS_INCLUDE_MCKITS_MSTL_ENCODING_MCKITS_ENCODING_BINARY_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: little endian encode u16.
@param v[in]: little endian byte order number
@param b[out]: buffer used to store number, at least 2 byte length.
*/
void mckits_little_endian_encode_u16(uint16_t v, uint8_t* b);

/*
@brief: little endian decode u16.
@param b[in]: buffer store number, at least 2 byte length.
@return: little endian byte order number
*/
uint16_t mckits_little_endian_decode_u16(const uint8_t* b);

/*
@brief: little endian encode u32.
@param v[in]: little endian byte order number
@param b[out]: buffer used to store number, at least 4 byte length.
*/
void mckits_little_endian_encode_u32(uint32_t v, uint8_t* b);

/*
@brief: little endian decode u32.
@param b[in]: buffer store number, at least 4 byte length.
@return: little endian byte order number
*/
uint32_t mckits_little_endian_decode_u32(const uint8_t* b);

/*
@brief: little endian encode u64.
@param v[in]: little endian byte order number
@param b[out]: buffer used to store number, at least 8 byte length.
*/
void mckits_little_endian_encode_u64(uint64_t v, uint8_t* b);

/*
@brief: little endian decode u64.
@param b[in]: buffer store number, at least 8 byte length.
@return: little endian byte order number
*/
uint64_t mckits_little_endian_decode_u64(const uint8_t* b);

/*
@brief: big endian encode u16.
@param v[in]: big endian byte order number
@param b[out]: buffer used to store number, at least 2 byte length.
*/
void mckits_big_endian_encode_u16(uint16_t v, uint8_t* b);

/*
@brief: big endian decode u16.
@param b[in]: buffer store number, at least 2 byte length.
@return: big endian byte order number
*/
uint16_t mckits_big_endian_decode_u16(const uint8_t* b);

/*
@brief: big endian encode u32.
@param v[in]: big endian byte order number
@param b[out]: buffer used to store number, at least 4 byte length.
*/
void mckits_big_endian_encode_u32(uint32_t v, uint8_t* b);

/*
@brief: big endian decode u32.
@param b[in]: buffer store number, at least 4 byte length.
@return: big endian byte order number
*/
uint32_t mckits_big_endian_decode_u32(const uint8_t* b);

/*
@brief: big endian encode u64.
@param v[in]: big endian byte order number
@param b[out]: buffer used to store number, at least 8 byte length.
*/
void mckits_big_endian_encode_u64(uint64_t v, uint8_t* b);

/*
@brief: big endian decode u64.
@param b[in]: buffer store number, at least 8 byte length.
@return: big endian byte order number
*/
uint64_t mckits_big_endian_decode_u64(const uint8_t* b);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_BINARY_H_
