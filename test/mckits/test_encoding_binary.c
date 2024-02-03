#include <assert.h>
#include <stdio.h>

#include "mckits/core/encoding/mckits_encoding_binary.h"

void test_little_endian_u16_01() {
  uint16_t v1 = 0x1234;
  uint8_t b[2] = {0};
  mckits_little_endian_encode_u16(v1, b);
  uint16_t v2 = mckits_little_endian_decode_u16(b);
  assert(v1 == v2);
}

void test_little_endian_u32_01() {
  uint32_t v1 = 0x12345678;
  uint8_t b[4] = {0};
  mckits_little_endian_encode_u32(v1, b);
  uint32_t v2 = mckits_little_endian_decode_u32(b);
  assert(v1 == v2);
}

void test_little_endian_u64_01() {
  uint64_t v1 = 0x1234567812345678;
  uint8_t b[8] = {0};
  mckits_little_endian_encode_u64(v1, b);
  uint64_t v2 = mckits_little_endian_decode_u64(b);
  assert(v1 == v2);
}

void test_big_endian_u16_01() {
  uint16_t v1 = 0x1234;
  uint8_t b[2] = {0};
  mckits_big_endian_encode_u16(v1, b);
  uint16_t v2 = mckits_big_endian_decode_u16(b);
  assert(v1 == v2);
}

void test_big_endian_u32_01() {
  uint32_t v1 = 0x12345678;
  uint8_t b[4] = {0};
  mckits_big_endian_encode_u32(v1, b);
  uint32_t v2 = mckits_big_endian_decode_u32(b);
  assert(v1 == v2);
}

void test_big_endian_u64_01() {
  uint64_t v1 = 0x1234567812345678;
  uint8_t b[8] = {0};
  mckits_big_endian_encode_u64(v1, b);
  uint64_t v2 = mckits_big_endian_decode_u64(b);
  assert(v1 == v2);
}

int main() {
  test_little_endian_u16_01();
  test_little_endian_u32_01();
  test_little_endian_u64_01();
  test_big_endian_u16_01();
  test_big_endian_u32_01();
  test_big_endian_u64_01();
  return 0;
}
