#ifndef MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_HEX_H_
#define MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_HEX_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Hex encoded length.
@return src_size * 2
*/
size_t mckits_hex_encode_len(size_t src_size);

/*
@brief: Hex decoded length, src_size must be even number
@return src_size / 2
*/
size_t mckits_hex_decode_len(size_t src_size);

/*
@brief: Hex encode src into dst. dst memory buffer size must be greater or equal
  than src_size * 2.
@param dst[out]: Destination memory buffer used to store encoded hex binary.
@param src[in]: Source memory buffer.
@param src_size[in]: Source memory buffer size.
*/
void mckits_hex_encode(uint8_t* dst, const uint8_t* src, size_t src_size);

/*
@brief: Hex decode src into dst.
@param dst[out]: Destination memory buffer used to decoded data.
@param src[in]: Source data encoded in hex format.
@param src_size[in]: Source memory buffer size.
@return
  On success, 0 is returned.
  -1: means invalid src_size, src_size must be even number.
  -2: src contains invalid byte.
*/
int mckits_hex_decode(uint8_t* dst, const uint8_t* src, size_t src_size);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_ENCODING_MCKITS_ENCODING_HEX_H_
