#include "mckits/core/encoding/mckits_endian.h"

#include <endian.h>

#include "mckits/mstl/encoding/mckits_encoding_binary.h"

int mckits_is_little_endian() {
#if BYTE_ORDER == LITTLE_ENDIAN
  return 1;
#else
  return 0;
#endif
}

int mckits_is_big_endian() {
#if BYTE_ORDER == BIG_ENDIAN
  return 1;
#else
  return 0;
#endif
}

void mckits_host_to_net_u16(uint16_t v, uint8_t* b) {
#if BYTE_ORDER == LITTLE_ENDIAN
  mckits_big_endian_encode_u16(v, b);
#else
  mckits_little_endian_encode_u16(v, b);
#endif
}

uint16_t mckits_net_to_host_u16(const uint8_t* b) {
#if BYTE_ORDER == LITTLE_ENDIAN
  return mckits_big_endian_decode_u16(b);
#else
  return mckits_little_endian_decode_u16(b);
#endif
}

void mckits_host_to_net_u32(uint32_t v, uint8_t* b) {
#if BYTE_ORDER == LITTLE_ENDIAN
  mckits_big_endian_encode_u32(v, b);
#else
  mckits_little_endian_encode_u32(v, b);
#endif
}

uint32_t mckits_net_to_host_u32(const uint8_t* b) {
#if BYTE_ORDER == LITTLE_ENDIAN
  return mckits_big_endian_decode_u32(b);
#else
  return mckits_little_endian_decode_u32(b);
#endif
}

void mckits_host_to_net_u64(uint64_t v, uint8_t* b) {
#if BYTE_ORDER == LITTLE_ENDIAN
  mckits_big_endian_encode_u64(v, b);
#else
  mckits_little_endian_encode_u64(v, b);
#endif
}

uint64_t mckits_net_to_host_u64(const uint8_t* b) {
#if BYTE_ORDER == LITTLE_ENDIAN
  return mckits_big_endian_decode_u64(b);
#else
  return mckits_little_endian_decode_u64(b);
#endif
}
