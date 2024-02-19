#include <assert.h>
#include <stdio.h>

#include "mckits/core/mckits_mtime.h"
#include "mckits/mstl/encoding/mckits_encoding_binary.h"

void bench_little_endian_u16_01() {
  uint16_t v1 = 0x1234;
  uint8_t b[2] = {0};

  int64_t count = 100000000;
  int64_t start = mckits_current_clock_nanoseconds();
  for (int64_t i = 0; i < count; ++i) {
    mckits_little_endian_encode_u16(v1, b);
  }
  int64_t end = mckits_current_clock_nanoseconds();
  int64_t diff = end - start;
  printf(
      "[u16] encode diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf count/s\n",
      diff, count, (double)diff / (double)count,
      (double)count / ((double)diff / 1000000000));
}

void bench_little_endian_u32_01() {
  uint32_t v1 = 0x12345678;
  uint8_t b[4] = {0};

  int64_t count = 100000000;
  int64_t start = mckits_current_clock_nanoseconds();
  for (int64_t i = 0; i < count; ++i) {
    mckits_little_endian_encode_u32(v1, b);
  }
  int64_t end = mckits_current_clock_nanoseconds();
  int64_t diff = end - start;
  printf(
      "[u32] encode diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf count/s\n",
      diff, count, (double)diff / (double)count,
      (double)count / ((double)diff / 1000000000));
}

void bench_little_endian_u64_01() {
  uint64_t v1 = 0x1234567812345678;
  uint8_t b[8] = {0};

  int64_t count = 100000000;
  int64_t start = mckits_current_clock_nanoseconds();
  for (int64_t i = 0; i < count; ++i) {
    mckits_little_endian_encode_u64(v1, b);
  }
  int64_t end = mckits_current_clock_nanoseconds();
  int64_t diff = end - start;
  printf(
      "[u64] encode diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf count/s\n",
      diff, count, (double)diff / (double)count,
      (double)count / ((double)diff / 1000000000));
}

int main() {
  bench_little_endian_u16_01();
  bench_little_endian_u32_01();
  bench_little_endian_u64_01();
  return 0;
}
