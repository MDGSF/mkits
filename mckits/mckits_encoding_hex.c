#include "mckits_encoding_hex.h"

static const char* hextable = "0123456789ABCDEF";

void mckits_hex_encode(uint8_t* dst, size_t dst_size, const uint8_t* src,
                       size_t src_size) {
  size_t j = 0;
  for (size_t i = 0; i < src_size; ++i) {
    uint8_t v = src[i];
    dst[j] = hextable[(v >> 4) & 0x0F];
    dst[j + 1] = hextable[v & 0x0F];
    j += 2;
  }
}
