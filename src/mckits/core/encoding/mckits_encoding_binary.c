#include "mckits/core/encoding/mckits_encoding_binary.h"

void mckits_little_endian_encode_u16(uint16_t v, uint8_t* b) {
  b[0] = (uint8_t)(v);
  b[1] = (uint8_t)(v >> 8);
}

uint16_t mckits_little_endian_decode_u16(const uint8_t* b) {
  return (uint16_t)(b[0]) | ((uint16_t)(b[1]) << 8);
}

void mckits_little_endian_encode_u32(uint32_t v, uint8_t* b) {
  b[0] = (uint8_t)(v);
  b[1] = (uint8_t)(v >> 8);
  b[2] = (uint8_t)(v >> 16);
  b[3] = (uint8_t)(v >> 24);
}

uint32_t mckits_little_endian_decode_u32(const uint8_t* b) {
  return (uint32_t)(b[0]) | ((uint32_t)(b[1]) << 8) | ((uint32_t)(b[2]) << 16) |
         ((uint32_t)(b[3]) << 24);
}

void mckits_little_endian_encode_u64(uint64_t v, uint8_t* b) {
  b[0] = (uint8_t)(v);
  b[1] = (uint8_t)(v >> 8);
  b[2] = (uint8_t)(v >> 16);
  b[3] = (uint8_t)(v >> 24);
  b[4] = (uint8_t)(v >> 32);
  b[5] = (uint8_t)(v >> 40);
  b[6] = (uint8_t)(v >> 48);
  b[7] = (uint8_t)(v >> 56);
}

uint64_t mckits_little_endian_decode_u64(const uint8_t* b) {
  return (uint64_t)(b[0]) | ((uint64_t)(b[1]) << 8) | ((uint64_t)(b[2]) << 16) |
         ((uint64_t)(b[3]) << 24) | ((uint64_t)(b[4]) << 32) |
         ((uint64_t)(b[5]) << 40) | ((uint64_t)(b[6]) << 48) |
         ((uint64_t)(b[7]) << 56);
}

void mckits_big_endian_encode_u16(uint16_t v, uint8_t* b) {
  b[0] = (uint8_t)(v >> 8);
  b[1] = (uint8_t)(v);
}

uint16_t mckits_big_endian_decode_u16(const uint8_t* b) {
  return (uint16_t)(b[1]) | ((uint16_t)(b[0]) << 8);
}

void mckits_big_endian_encode_u32(uint32_t v, uint8_t* b) {
  b[0] = (uint8_t)(v >> 24);
  b[1] = (uint8_t)(v >> 16);
  b[2] = (uint8_t)(v >> 8);
  b[3] = (uint8_t)(v);
}

uint32_t mckits_big_endian_decode_u32(const uint8_t* b) {
  return (uint32_t)(b[3]) | ((uint32_t)(b[2]) << 8) | ((uint32_t)(b[1]) << 16) |
         ((uint32_t)(b[0]) << 24);
}

void mckits_big_endian_encode_u64(uint64_t v, uint8_t* b) {
  b[0] = (uint8_t)(v >> 56);
  b[1] = (uint8_t)(v >> 48);
  b[2] = (uint8_t)(v >> 40);
  b[3] = (uint8_t)(v >> 32);
  b[4] = (uint8_t)(v >> 24);
  b[5] = (uint8_t)(v >> 16);
  b[6] = (uint8_t)(v >> 8);
  b[7] = (uint8_t)(v);
}

uint64_t mckits_big_endian_decode_u64(const uint8_t* b) {
  return (uint64_t)(b[7]) | ((uint64_t)(b[6]) << 8) | ((uint64_t)(b[5]) << 16) |
         ((uint64_t)(b[4]) << 24) | ((uint64_t)(b[3]) << 32) |
         ((uint64_t)(b[2]) << 40) | ((uint64_t)(b[1]) << 48) |
         ((uint64_t)(b[0]) << 56);
}
