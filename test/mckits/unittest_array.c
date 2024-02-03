#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/mckits_array.h"

void test01() {
  struct MckitsArray array;
  assert(0 == mckits_array_init(&array, 10, 4));
  assert(array.size == 0);
  assert(array.capacity == 10);
  assert(array.element_bytes == 4);

  for (int i = 1; i <= 10; ++i) {
    int32_t* p = (int32_t*)mckits_array_push(&array);
    *p = i;
    assert(array.size == i);
  }

  int32_t* start = (int32_t*)array.buffer;
  for (int i = 0; i < 10; ++i) {
    int32_t v = start[i];
    assert(v == i + 1);
  }

  mckits_array_destroy(&array);
}

void test02() {
  struct MckitsArray array;
  assert(0 == mckits_array_init(&array, 10, 4));

  for (int i = 1; i <= 10; ++i) {
    int32_t* p = (int32_t*)mckits_array_push(&array);
    *p = i;
    assert(array.size == i);
  }
  assert(array.size == 10);
  assert(array.capacity == 10);
  assert(array.element_bytes == 4);

  mckits_array_push(&array);
  assert(array.size == 11);
  assert(array.capacity == 20);
  assert(array.element_bytes == 4);

  mckits_array_destroy(&array);
}

void test03() {
  struct MckitsArray array;
  assert(0 == mckits_array_init(&array, 1, 1));
  assert(array.size == 0);
  assert(array.capacity == 1);
  assert(array.element_bytes == 1);

  mckits_array_push(&array);
  assert(array.size == 1);
  assert(array.capacity == 1);
  assert(array.element_bytes == 1);

  mckits_array_push(&array);
  assert(array.size == 2);
  assert(array.capacity == 2);
  assert(array.element_bytes == 1);

  mckits_array_push(&array);
  assert(array.size == 3);
  assert(array.capacity == 4);
  assert(array.element_bytes == 1);

  mckits_array_push(&array);
  assert(array.size == 4);
  assert(array.capacity == 4);
  assert(array.element_bytes == 1);

  mckits_array_push(&array);
  assert(array.size == 5);
  assert(array.capacity == 8);
  assert(array.element_bytes == 1);

  mckits_array_destroy(&array);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
