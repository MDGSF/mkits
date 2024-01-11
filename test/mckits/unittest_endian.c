#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits_endian.h"

int is_little_endian() {
  int num = 1;
  char *ptr = (char *)&num;
  return (*ptr);
}

void test01() {
  assert(mckits_is_little_endian() == is_little_endian());
  assert(mckits_is_big_endian() != is_little_endian());
  assert(mckits_is_little_endian() != mckits_is_big_endian());
}

void test02() {
  uint16_t v = 0x1234;
  uint8_t b01[2] = {0};
  mckits_host_to_net_u16(v, b01);

  uint16_t net02_u16 = mckits_hton_u16(v);
  uint8_t b02[2] = {0};
  memcpy(b02, &net02_u16, 2);

  assert(b01[0] == 0x12);
  assert(b01[1] == 0x34);

  assert(b01[0] == b02[0]);
  assert(b01[1] == b02[1]);

  uint16_t *p_net01_u16 = (uint16_t *)b01;
  assert(*p_net01_u16 == net02_u16);
}

void test03() {
  uint32_t v = 0x12345678;
  uint8_t b01[4] = {0};
  mckits_host_to_net_u32(v, b01);

  uint32_t net02_u32 = mckits_hton_u32(v);
  uint8_t b02[4] = {0};
  memcpy(b02, &net02_u32, 4);

  assert(b01[0] == 0x12);
  assert(b01[1] == 0x34);
  assert(b01[2] == 0x56);
  assert(b01[3] == 0x78);

  assert(b01[0] == b02[0]);
  assert(b01[1] == b02[1]);
  assert(b01[2] == b02[2]);
  assert(b01[3] == b02[3]);

  uint32_t *p_net01_u32 = (uint32_t *)b01;
  assert(*p_net01_u32 == net02_u32);
}

void test04() {
  uint64_t v = 0x1234567812345678;
  uint8_t b01[8] = {0};
  mckits_host_to_net_u64(v, b01);

  assert(b01[0] == 0x12);
  assert(b01[1] == 0x34);
  assert(b01[2] == 0x56);
  assert(b01[3] == 0x78);
  assert(b01[4] == 0x12);
  assert(b01[5] == 0x34);
  assert(b01[6] == 0x56);
  assert(b01[7] == 0x78);
}

void test05() {
  uint16_t v = 0x1234;
  uint8_t b[2] = {0};
  mckits_host_to_net_u16(v, b);
  uint16_t v2 = mckits_net_to_host_u16(b);
  assert(v == v2);
}

void test06() {
  uint32_t v = 0x12345678;
  uint8_t b[4] = {0};
  mckits_host_to_net_u32(v, b);
  uint32_t v2 = mckits_net_to_host_u32(b);
  assert(v == v2);
}

void test07() {
  uint64_t v = 0x1234567812345678;
  uint8_t b[8] = {0};
  mckits_host_to_net_u64(v, b);
  uint64_t v2 = mckits_net_to_host_u64(b);
  assert(v == v2);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  return 0;
}
