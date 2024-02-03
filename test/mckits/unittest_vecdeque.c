#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/mckits_vecdeque.h"

void test01() {
  struct MckitsVecDeque* vecdeque = mckits_vecdeque_new(sizeof(int));

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  mckits_vecdeque_clear(vecdeque);
  mckits_vecdeque_drop(vecdeque);
}

void test02() {
  size_t capacity = 8;
  struct MckitsVecDeque* vecdeque =
      mckits_vecdeque_with_capacity(sizeof(int), capacity);

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(capacity == mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  mckits_vecdeque_clear(vecdeque);
  mckits_vecdeque_drop(vecdeque);
}

void test03() {
  // push back, pop front
  struct MckitsVecDeque vecdeque;
  mckits_vecdeque_init(&vecdeque, sizeof(int64_t));

  assert(0 == mckits_vecdeque_len(&vecdeque));
  assert(0 <= mckits_vecdeque_capacity(&vecdeque));
  assert(1 == mckits_vecdeque_is_empty(&vecdeque));

  for (int64_t i = 0; i < 100; ++i) {
    mckits_vecdeque_push_back(&vecdeque, &i);
    assert(i + 1 == mckits_vecdeque_len(&vecdeque));
    assert(0 == mckits_vecdeque_is_empty(&vecdeque));

    void* output_value = NULL;
    assert(1 == mckits_vecdeque_back(&vecdeque, &output_value));
    int64_t* output_int64_value = (int64_t*)output_value;
    assert(*output_int64_value == i);
  }

  for (int64_t i = 0; i < 100; ++i) {
    int64_t* value = NULL;
    assert(1 == mckits_vecdeque_front(&vecdeque, (void**)&value));
    assert(*value == i);
    mckits_vecdeque_pop_front(&vecdeque);
  }

  assert(0 == mckits_vecdeque_len(&vecdeque));
  assert(0 <= mckits_vecdeque_capacity(&vecdeque));
  assert(1 == mckits_vecdeque_is_empty(&vecdeque));

  mckits_vecdeque_clear(&vecdeque);
}

void test04() {
  // push front, pop back
  size_t capacity = 8;
  struct MckitsVecDeque vecdeque;
  mckits_vecdeque_init_with_capacity(&vecdeque, sizeof(int64_t), capacity);

  assert(0 == mckits_vecdeque_len(&vecdeque));
  assert(capacity == mckits_vecdeque_capacity(&vecdeque));
  assert(1 == mckits_vecdeque_is_empty(&vecdeque));

  for (int64_t i = 0; i < 100; ++i) {
    mckits_vecdeque_push_front(&vecdeque, &i);
    assert(i + 1 == mckits_vecdeque_len(&vecdeque));
    assert(0 == mckits_vecdeque_is_empty(&vecdeque));

    int64_t* output_value = NULL;
    assert(1 == mckits_vecdeque_front(&vecdeque, (void**)&output_value));
    assert(*output_value == i);
  }

  for (int64_t i = 0; i < 100; ++i) {
    int64_t* value = NULL;
    assert(1 == mckits_vecdeque_back(&vecdeque, (void**)&value));
    assert(*value == i);
    mckits_vecdeque_pop_back(&vecdeque);
  }

  mckits_vecdeque_clear(&vecdeque);
}

void test05() {
  struct MckitsVecDeque* vecdeque = mckits_vecdeque_new(sizeof(int));

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  assert(0 == mckits_vecdeque_back(vecdeque, NULL));
  assert(0 == mckits_vecdeque_front(vecdeque, NULL));

  mckits_vecdeque_pop_back(vecdeque);
  mckits_vecdeque_pop_front(vecdeque);

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  assert(0 == mckits_vecdeque_get(vecdeque, 0, NULL));
  assert(0 == mckits_vecdeque_get(vecdeque, 1, NULL));
  assert(0 == mckits_vecdeque_get(vecdeque, 2, NULL));

  mckits_vecdeque_clear(vecdeque);
  mckits_vecdeque_drop(vecdeque);
}

void test06() {
  // push front, pop front
  struct MckitsVecDeque* vecdeque = mckits_vecdeque_new(sizeof(int64_t));

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  for (int64_t i = 0; i < 100; ++i) {
    mckits_vecdeque_push_front(vecdeque, &i);
    assert(i + 1 == mckits_vecdeque_len(vecdeque));
    assert(0 == mckits_vecdeque_is_empty(vecdeque));

    int64_t* output_value = NULL;
    assert(1 == mckits_vecdeque_front(vecdeque, (void**)&output_value));
    assert(*output_value == i);
  }

  while (!mckits_vecdeque_is_empty(vecdeque)) {
    mckits_vecdeque_pop_front(vecdeque);
  }

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  mckits_vecdeque_drop(vecdeque);
}

void test07() {
  // push back, pop back
  struct MckitsVecDeque* vecdeque =
      mckits_vecdeque_with_capacity(sizeof(int64_t), 100);

  for (int64_t i = 0; i < 100; ++i) {
    mckits_vecdeque_push_back(vecdeque, &i);
    assert(i + 1 == mckits_vecdeque_len(vecdeque));
    assert(0 == mckits_vecdeque_is_empty(vecdeque));

    void* output_value = NULL;
    assert(1 == mckits_vecdeque_back(vecdeque, &output_value));
    int64_t* output_int64_value = (int64_t*)output_value;
    assert(*output_int64_value == i);
  }

  for (int64_t i = 0; i < 100; ++i) {
    int64_t* value = NULL;
    assert(1 == mckits_vecdeque_get(vecdeque, i, (void**)&value));
    assert(*value == i);
  }

  while (!mckits_vecdeque_is_empty(vecdeque)) {
    mckits_vecdeque_pop_back(vecdeque);
  }

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  mckits_vecdeque_drop(vecdeque);
}

// insert after clear
void test08() {
  struct MckitsVecDeque* vecdeque =
      mckits_vecdeque_with_capacity(sizeof(int64_t), 100);

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(100 == mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  for (int64_t i = 0; i < 100; ++i) {
    mckits_vecdeque_push_back(vecdeque, &i);
  }

  assert(100 == mckits_vecdeque_len(vecdeque));
  assert(100 == mckits_vecdeque_capacity(vecdeque));
  assert(0 == mckits_vecdeque_is_empty(vecdeque));

  mckits_vecdeque_clear(vecdeque);

  assert(0 == mckits_vecdeque_len(vecdeque));
  assert(0 == mckits_vecdeque_capacity(vecdeque));
  assert(1 == mckits_vecdeque_is_empty(vecdeque));

  for (int64_t i = 0; i < 100; ++i) {
    mckits_vecdeque_push_back(vecdeque, &i);
  }

  assert(100 == mckits_vecdeque_len(vecdeque));
  assert(0 <= mckits_vecdeque_capacity(vecdeque));
  assert(0 == mckits_vecdeque_is_empty(vecdeque));

  mckits_vecdeque_drop(vecdeque);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
  return 0;
}
