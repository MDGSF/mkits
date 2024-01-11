#ifndef MKITS_MCKITS_MCKITS_ENCODING_HEX_H_
#define MKITS_MCKITS_MCKITS_ENCODING_HEX_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Hex encode src into dst. dst_size must be greater than src_size * 2.
@param dst[out]: Destination memory buffer used to store encoded hex binary.
@param dst_size[in]: Destination memory buffer size.
@param src[in]: Source memory buffer.
@param src_size[in]: Source memory buffer size.
*/
void mckits_hex_encode(uint8_t* dst, size_t dst_size, const uint8_t* src,
                       size_t src_size);

#ifdef __cplusplus
}
#endif

#endif
