#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/mstl/mckits_vector.h"

static void test_int_mvec(struct MckitsVector* mvec, int* expected_nums,
                          size_t expected_len) {
  assert(mckits_vec_len(mvec) == expected_len);
  assert(mckits_vec_capacity(mvec) >= expected_len);
  for (size_t i = 0; i < expected_len; ++i) {
    int value = *(int*)mckits_vec_get(mvec, i);
    assert(value == expected_nums[i]);
  }
}

static void test_str_mvec(struct MckitsVector* mvec, const char* expected_vec[],
                          size_t expected_len) {
  assert(mckits_vec_len(mvec) == expected_len);
  assert(mckits_vec_capacity(mvec) >= expected_len);
  for (size_t i = 0; i < expected_len; ++i) {
    const char* s = (const char*)mckits_vec_get(mvec, i);
    assert(strcmp(s, expected_vec[i]) == 0);
  }
}

void test01() {
  struct MckitsVector* mvec = mckits_vec_new(4);
  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);
  mckits_vec_drop(mvec);
}

void test02() {
  struct MckitsVector* mvec = mckits_vec_with_capacity(4, 10);
  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 10);
  assert(mckits_vec_is_empty(mvec) == 1);
  mckits_vec_drop(mvec);
}

void test03() {
  struct MckitsVector mvec;
  mckits_vec_init(&mvec, 4);
  assert(mckits_vec_len(&mvec) == 0);
  assert(mckits_vec_capacity(&mvec) == 0);
  assert(mckits_vec_is_empty(&mvec) == 1);
  mckits_vec_drop_data(&mvec);
}

void test04() {
  struct MckitsVector mvec;
  mckits_vec_init_with_capacity(&mvec, 4, 20);
  assert(mckits_vec_len(&mvec) == 0);
  assert(mckits_vec_capacity(&mvec) == 20);
  assert(mckits_vec_is_empty(&mvec) == 1);
  mckits_vec_drop_data(&mvec);
}

void test05() {
  struct MckitsVector mvec;
  mckits_vec_init_with_capacity(&mvec, 4, 20);
  assert(mckits_vec_len(&mvec) == 0);
  assert(mckits_vec_capacity(&mvec) == 20);
  assert(mckits_vec_is_empty(&mvec) == 1);

  for (int i = 1; i <= 10; ++i) {
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == i);
    assert(mckits_vec_is_empty(&mvec) == 0);
  }

  for (size_t i = 0; i < 10; ++i) {
    void* element = mckits_vec_get(&mvec, i);
    assert((int)(i + 1) == *(int*)element);
  }

  void* first_element = mckits_vec_first(&mvec);
  assert(1 == *(int*)first_element);

  void* last_element = mckits_vec_last(&mvec);
  assert(10 == *(int*)last_element);

  for (int i = 1; i <= 10; ++i) {
    mckits_vec_pop(&mvec);
    assert(mckits_vec_len(&mvec) == 10 - i);
  }
  assert(mckits_vec_is_empty(&mvec) == 1);

  mckits_vec_drop_data(&mvec);
}

void test06() {
  struct MckitsVector mvec;
  mckits_vec_init(&mvec, sizeof(int));
  assert(mckits_vec_len(&mvec) == 0);
  assert(mckits_vec_capacity(&mvec) == 0);
  assert(mckits_vec_is_empty(&mvec) == 1);

  {
    int i = 1;
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == 1);
    assert(mckits_vec_capacity(&mvec) == 4);
  }

  {
    int i = 2;
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == 2);
    assert(mckits_vec_capacity(&mvec) == 4);
  }

  {
    int i = 3;
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == 3);
    assert(mckits_vec_capacity(&mvec) == 4);
  }

  {
    int i = 4;
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == 4);
    assert(mckits_vec_capacity(&mvec) == 4);
  }

  {
    int i = 5;
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == 5);
    assert(mckits_vec_capacity(&mvec) == 8);
  }

  for (int i = 0; i < 3; ++i) {
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_capacity(&mvec) == 8);
  }
  {
    int i = 123;
    mckits_vec_push(&mvec, &i);
    assert(mckits_vec_len(&mvec) == 9);
    assert(mckits_vec_capacity(&mvec) == 16);
  }

  mckits_vec_drop_data(&mvec);
}

void test07() {
  // mvec and other all is empty

  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));
  struct MckitsVector* other = mckits_vec_new(sizeof(int));

  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  mckits_vec_append(mvec, other);

  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  mckits_vec_drop(mvec);
  mckits_vec_drop(other);
}

void test08() {
  // mvec has data, but other is empty

  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));
  struct MckitsVector* other = mckits_vec_new(sizeof(int));

  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  for (int i = 1; i <= 10; ++i) {
    mckits_vec_push(mvec, &i);
  }

  mckits_vec_append(mvec, other);

  assert(mckits_vec_len(mvec) == 10);
  assert(mckits_vec_capacity(mvec) == 16);
  assert(mckits_vec_is_empty(mvec) == 0);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  mckits_vec_drop(mvec);
  mckits_vec_drop(other);
}

void test09() {
  // mvec is empty, but other has data.

  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));
  struct MckitsVector* other = mckits_vec_new(sizeof(int));

  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  for (int i = 1; i <= 10; ++i) {
    mckits_vec_push(other, &i);
  }

  assert(mckits_vec_len(other) == 10);
  assert(mckits_vec_capacity(other) == 16);
  assert(mckits_vec_is_empty(other) == 0);

  mckits_vec_append(mvec, other);

  assert(mckits_vec_len(mvec) == 10);
  assert(mckits_vec_capacity(mvec) == 16);
  assert(mckits_vec_is_empty(mvec) == 0);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  mckits_vec_drop(mvec);
  mckits_vec_drop(other);
}

void test10() {
  // mvec has data, and other has data.

  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));
  struct MckitsVector* other = mckits_vec_new(sizeof(int));

  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  for (int i = 1; i <= 5; ++i) {
    mckits_vec_push(mvec, &i);
  }

  assert(mckits_vec_len(mvec) == 5);
  assert(mckits_vec_capacity(mvec) == 8);
  assert(mckits_vec_is_empty(mvec) == 0);

  for (int i = 6; i <= 10; ++i) {
    mckits_vec_push(other, &i);
  }

  assert(mckits_vec_len(other) == 5);
  assert(mckits_vec_capacity(other) == 8);
  assert(mckits_vec_is_empty(other) == 0);

  mckits_vec_append(mvec, other);

  assert(mckits_vec_len(mvec) == 10);
  assert(mckits_vec_capacity(mvec) == 16);
  assert(mckits_vec_is_empty(mvec) == 0);

  assert(mckits_vec_len(other) == 0);
  assert(mckits_vec_capacity(other) == 0);
  assert(mckits_vec_is_empty(other) == 1);

  for (size_t i = 0; i < 10; ++i) {
    void* element = mckits_vec_get(mvec, i);
    assert((int)(i + 1) == *(int*)element);
  }

  mckits_vec_drop(mvec);
  mckits_vec_drop(other);
}

void test11() {
  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));
  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  for (int i = 1; i <= 10; ++i) {
    mckits_vec_push(mvec, &i);
  }

  assert(mckits_vec_len(mvec) == 10);
  assert(mckits_vec_capacity(mvec) >= 10);
  assert(mckits_vec_is_empty(mvec) == 0);

  size_t capacity_before_clear = mckits_vec_capacity(mvec);

  mckits_vec_clear(mvec);

  size_t capacity_after_clear = mckits_vec_capacity(mvec);

  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) >= 10);
  assert(mckits_vec_is_empty(mvec) == 1);
  assert(capacity_before_clear == capacity_after_clear);

  mckits_vec_drop(mvec);
}

void test12() {
  struct MckitsVector* mvec = mckits_vec_with_capacity(sizeof(int), 10);
  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 10);
  assert(mckits_vec_is_empty(mvec) == 1);

  void* mvec_buffer = mckits_vec_as_ptr(mvec);
  assert(mvec_buffer == mvec->buffer);

  mckits_vec_drop(mvec);
}

void test13() {
  struct MckitsVector* mvec = mckits_vec_with_capacity(sizeof(int), 10);

  for (int i = 1; i <= 10; ++i) {
    mckits_vec_push(mvec, &i);
  }
  assert(mckits_vec_len(mvec) == 10);
  assert(mckits_vec_capacity(mvec) >= 10);
  assert(mckits_vec_is_empty(mvec) == 0);

  {
    int num = 123;
    mckits_vec_insert(mvec, 0, &num);

    assert(mckits_vec_len(mvec) == 11);
    assert(mckits_vec_capacity(mvec) >= 11);
    assert(mckits_vec_is_empty(mvec) == 0);

    assert(num == *(int*)mckits_vec_get(mvec, 0));
    assert(num == *(int*)mckits_vec_first(mvec));
  }

  mckits_vec_drop(mvec);
}

void test14() {
  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));
  assert(mckits_vec_len(mvec) == 0);
  assert(mckits_vec_capacity(mvec) == 0);
  assert(mckits_vec_is_empty(mvec) == 1);

  int num = 1;
  mckits_vec_push(mvec, &num);
  num += 1;
  mckits_vec_push(mvec, &num);
  num += 1;
  mckits_vec_push(mvec, &num);
  test_int_mvec(mvec, (int[]){1, 2, 3}, 3);

  num = 4;
  mckits_vec_insert(mvec, 1, &num);
  test_int_mvec(mvec, (int[]){1, 4, 2, 3}, 4);

  num = 5;
  mckits_vec_insert(mvec, 4, &num);
  test_int_mvec(mvec, (int[]){1, 4, 2, 3, 5}, 5);

  mckits_vec_drop(mvec);
}

void test15() {
  struct MckitsVector* mvec = mckits_vec_new(sizeof(int));

  int num = 1;
  mckits_vec_push(mvec, &num);
  num += 1;
  mckits_vec_push(mvec, &num);
  num += 1;
  mckits_vec_push(mvec, &num);
  test_int_mvec(mvec, (int[]){1, 2, 3}, 3);

  mckits_vec_remove(mvec, 1);
  test_int_mvec(mvec, (int[]){1, 3}, 2);

  mckits_vec_drop(mvec);
}

void test16() {
  struct MckitsVector* mvec = mckits_vec_new(sizeof(const char*));

  mckits_vec_push(mvec, "foo");
  mckits_vec_push(mvec, "bar");
  mckits_vec_push(mvec, "baz");
  mckits_vec_push(mvec, "qux");
  {
    const char* expected_vec[] = {"foo", "bar", "baz", "qux"};
    test_str_mvec(mvec, expected_vec, 4);
  }

  mckits_vec_swap_remove(mvec, 1);
  {
    const char* expected_vec[] = {"foo", "qux", "baz"};
    test_str_mvec(mvec, expected_vec, 3);
  }

  mckits_vec_drop(mvec);
}

void test17() {
  struct MckitsVector* mvec = mckits_vec_new(sizeof(const char*));

  mckits_vec_push(mvec, "a");
  mckits_vec_push(mvec, "b");
  mckits_vec_push(mvec, "c");
  mckits_vec_push(mvec, "d");
  mckits_vec_push(mvec, "e");

  {
    const char* expected_vec[] = {"a", "b", "c", "d", "e"};
    test_str_mvec(mvec, expected_vec, 5);
  }

  mckits_vec_swap(mvec, 2, 4);
  {
    const char* expected_vec[] = {"a", "b", "e", "d", "c"};
    test_str_mvec(mvec, expected_vec, 5);
  }

  mckits_vec_drop(mvec);
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
  test09();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();
  test17();
  return 0;
}
