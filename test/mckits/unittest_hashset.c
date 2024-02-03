#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits/mstl/mckits_hashset.h"
#include "mckits/mstl/mckits_string.h"

uint64_t hash_func(void* value, uint64_t seed0, uint64_t seed1) {
  int* num = (int*)value;
  return mckits_hashset_hash_func_fnv_1a_64(&num, sizeof(int), seed0, seed1);
}

int compare_func(void* a, void* b) {
  int* numa = (int*)a;
  int* numb = (int*)b;
  return numa - numb;
}

void free_value(void* value) { free(value); }

void test01() {
  struct MckitsHashSet* mset = mckits_hashset_new();
  mckits_hashset_set_hashfunc(mset, hash_func);
  mckits_hashset_set_seed0(mset, 0);
  mckits_hashset_set_seed1(mset, 0);
  mckits_hashset_set_compare_func(mset, compare_func);
  mckits_hashset_set_free_value(mset, free_value);

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  for (int i = 0; i < 10; ++i) {
    int* num = (int*)malloc(sizeof(int));
    mckits_hashset_insert(mset, num);
    assert(i + 1 == mckits_hashset_len(mset));
    assert(0 == mckits_hashset_is_empty(mset));
  }

  mckits_hashset_drop(mset);
}

void test02() {
  struct MckitsHashSet* mset = mckits_hashset_new();
  mckits_hashset_set_hashfunc(mset, hash_func);
  mckits_hashset_set_seed0(mset, 0);
  mckits_hashset_set_seed1(mset, 0);
  mckits_hashset_set_compare_func(mset, compare_func);
  mckits_hashset_set_free_value(mset, NULL);

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  // insert zero value
  mckits_hashset_insert(mset, (void*)0);
  assert(1 == mckits_hashset_contains(mset, (void*)0));

  mckits_hashset_drop(mset);
}

void test03() {
  struct MckitsHashSet* mset = mckits_hashset_new();
  mckits_hashset_set_hashfunc(mset, hash_func);
  mckits_hashset_set_seed0(mset, 0);
  mckits_hashset_set_seed1(mset, 0);
  mckits_hashset_set_compare_func(mset, compare_func);
  mckits_hashset_set_free_value(mset, NULL);

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  mckits_hashset_insert(mset, (void*)0);
  mckits_hashset_insert(mset, (void*)1);
  mckits_hashset_insert(mset, (void*)2);

  assert(1 == mckits_hashset_contains(mset, (void*)0));
  assert(1 == mckits_hashset_contains(mset, (void*)1));
  assert(1 == mckits_hashset_contains(mset, (void*)2));
  assert(3 == mckits_hashset_len(mset));
  assert(0 == mckits_hashset_is_empty(mset));

  // insert same value
  mckits_hashset_insert(mset, (void*)0);
  mckits_hashset_insert(mset, (void*)1);
  mckits_hashset_insert(mset, (void*)2);

  assert(1 == mckits_hashset_contains(mset, (void*)0));
  assert(1 == mckits_hashset_contains(mset, (void*)1));
  assert(1 == mckits_hashset_contains(mset, (void*)2));
  assert(3 == mckits_hashset_len(mset));
  assert(0 == mckits_hashset_is_empty(mset));

  // clear
  mckits_hashset_clear(mset);

  assert(0 == mckits_hashset_contains(mset, (void*)0));
  assert(0 == mckits_hashset_contains(mset, (void*)1));
  assert(0 == mckits_hashset_contains(mset, (void*)2));
  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  // insert after clear
  mckits_hashset_insert(mset, (void*)0);
  mckits_hashset_insert(mset, (void*)1);
  mckits_hashset_insert(mset, (void*)2);

  assert(1 == mckits_hashset_contains(mset, (void*)0));
  assert(1 == mckits_hashset_contains(mset, (void*)1));
  assert(1 == mckits_hashset_contains(mset, (void*)2));
  assert(3 == mckits_hashset_len(mset));
  assert(0 == mckits_hashset_is_empty(mset));

  mckits_hashset_drop(mset);
}

void test04() {
  struct MckitsHashSet* mset = mckits_hashset_new();
  mckits_hashset_set_hashfunc(mset, hash_func);
  mckits_hashset_set_seed0(mset, 0);
  mckits_hashset_set_seed1(mset, 0);
  mckits_hashset_set_compare_func(mset, compare_func);
  mckits_hashset_set_free_value(mset, NULL);

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  for (int64_t i = 0; i < 10; ++i) {
    mckits_hashset_insert(mset, (void*)i);
    assert(i + 1 == mckits_hashset_len(mset));
    assert(0 == mckits_hashset_is_empty(mset));
  }

  assert(1 == mckits_hashset_contains(mset, (void*)8));
  mckits_hashset_remove(mset, (void*)8);
  assert(0 == mckits_hashset_contains(mset, (void*)8));

  assert(1 == mckits_hashset_contains(mset, (void*)3));
  mckits_hashset_remove(mset, (void*)3);
  assert(0 == mckits_hashset_contains(mset, (void*)3));

  assert(1 == mckits_hashset_contains(mset, (void*)7));
  mckits_hashset_remove(mset, (void*)7);
  assert(0 == mckits_hashset_contains(mset, (void*)7));

  assert(1 == mckits_hashset_contains(mset, (void*)4));
  mckits_hashset_remove(mset, (void*)4);
  assert(0 == mckits_hashset_contains(mset, (void*)4));

  assert(1 == mckits_hashset_contains(mset, (void*)5));
  mckits_hashset_remove(mset, (void*)5);
  assert(0 == mckits_hashset_contains(mset, (void*)5));

  assert(1 == mckits_hashset_contains(mset, (void*)9));
  mckits_hashset_remove(mset, (void*)9);
  assert(0 == mckits_hashset_contains(mset, (void*)9));

  assert(1 == mckits_hashset_contains(mset, (void*)1));
  mckits_hashset_remove(mset, (void*)1);
  assert(0 == mckits_hashset_contains(mset, (void*)1));

  assert(1 == mckits_hashset_contains(mset, (void*)2));
  mckits_hashset_remove(mset, (void*)2);
  assert(0 == mckits_hashset_contains(mset, (void*)2));

  assert(1 == mckits_hashset_contains(mset, (void*)0));
  mckits_hashset_remove(mset, (void*)0);
  assert(0 == mckits_hashset_contains(mset, (void*)0));

  assert(1 == mckits_hashset_contains(mset, (void*)6));
  mckits_hashset_remove(mset, (void*)6);
  assert(0 == mckits_hashset_contains(mset, (void*)6));

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  // remove not exists value
  for (int64_t i = 0; i < 10; ++i) {
    mckits_hashset_remove(mset, (void*)i);
  }

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  mckits_hashset_drop(mset);
}

void test05() {
  struct MckitsHashSet* mset = mckits_hashset_new();
  mckits_hashset_set_hashfunc(mset, hash_func);
  mckits_hashset_set_seed0(mset, 0);
  mckits_hashset_set_seed1(mset, 0);
  mckits_hashset_set_compare_func(mset, compare_func);
  mckits_hashset_set_free_value(mset, NULL);

  assert(0 == mckits_hashset_len(mset));
  assert(1 == mckits_hashset_is_empty(mset));

  int64_t expected_count = 0;
  int64_t expected_sum = 0;
  for (int64_t i = 0; i < 10; ++i) {
    mckits_hashset_insert(mset, (void*)i);
    assert(i + 1 == mckits_hashset_len(mset));
    assert(0 == mckits_hashset_is_empty(mset));
    expected_count += 1;
    expected_sum += i;
  }

  int64_t count = 0;
  int64_t sum = 0;
  void* value = NULL;
  struct MckitsHashSetIter* iter = mckits_hashset_iterator(mset);
  while (mckits_hashset_iterator_next(iter, &value)) {
    count += 1;
    sum += (int64_t)value;
  }

  assert(expected_count == count);
  assert(expected_sum == sum);

  mckits_hashset_iterator_drop(iter);
  mckits_hashset_drop(mset);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  return 0;
}
