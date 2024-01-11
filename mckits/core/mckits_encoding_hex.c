#include "mckits_encoding_hex.h"

static const char* hextable = "0123456789abcdef";

void mckits_hex_encode(uint8_t* dst, const uint8_t* src, size_t src_size) {
  size_t j = 0;
  for (size_t i = 0; i < src_size; ++i) {
    uint8_t v = src[i];
    dst[j] = hextable[(v >> 4) & 0x0F];
    dst[j + 1] = hextable[v & 0x0F];
    j += 2;
  }
}

static int mckits_hex_char_to_value(uint8_t b, uint8_t* v) {
  if (b >= '0' && b <= '9') {
    *v = b - '0';
    return 0;
  } else if (b >= 'a' && b <= 'f') {
    *v = b - 'a' + 10;
    return 0;
  } else if (b >= 'A' && b <= 'F') {
    *v = b - 'A' + 10;
    return 0;
  }
  return -1;
}

int mckits_hex_decode(uint8_t* dst, const uint8_t* src, size_t src_size) {
  if (src_size % 2 != 0) {
    return -1;
  }

  size_t j = 0;
  for (size_t i = 0; i < src_size; i += 2) {
    uint8_t high = 0;
    uint8_t low = 0;
    if (mckits_hex_char_to_value(src[i], &high) == -1) {
      return -2;
    }
    if (mckits_hex_char_to_value(src[i + 1], &low) == -1) {
      return -2;
    }
    dst[j++] = (high << 4) | low;
  }

  return 0;
}
