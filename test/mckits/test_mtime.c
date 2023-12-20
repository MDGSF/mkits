#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mckits_mtime.h"

void test01() {
  int64_t diff_sum = 0;
  int count = 1000;
  for (int i = 0; i < count; ++i) {
    int64_t start = mckits_current_clock_nanoseconds();
    mckits_sleep_nanoseconds(1);
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    diff_sum += diff;
  }
  int64_t diff_avg = diff_sum / count;
  printf("sleep 1 ns, diff = %ld ns\n", diff_avg);
}

void test02() {
  int result[1024] = {0};
  for (int i = 0; i < 1000; ++i) {
    int64_t start = mckits_current_clock_microseconds();
    int64_t expected_end = start + 10000;  // 10ms later
    mckits_sleep_to(expected_end);
    int64_t end = mckits_current_clock_microseconds();
    int64_t diff = end - expected_end;
    if (diff < 0 || diff > 1024) {
      printf("test02 start: %ld, end: %ld, expected_end: %ld, diff: %ld us\n",
             start, end, expected_end, diff);
      exit(0);
    }
    result[diff] += 1;
  }

  for (int i = 0; i < 1024; ++i) {
    if (result[i] > 0) {
      printf("[%d] = %d\n", i, result[i]);
    }
  }
}

int main() {
  test01();
  test02();
  return 0;
}

