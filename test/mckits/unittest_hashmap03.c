#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_hashmap.h"
#include "mckits_string.h"

uint64_t hash_callback(void* key, uint64_t seed0, uint64_t seed1) {
  int64_t key_num = (int64_t)key;
  return mckits_hashmap_hash_func_fnv_1a_64(&key_num, sizeof(int64_t), seed0,
                                            seed1);
}

int compare_callback(void* keya, void* keyb) {
  int64_t keya_num = (int64_t)keya;
  int64_t keyb_num = (int64_t)keyb;
  return (int)(keya_num - keyb_num);
}

void test01() {
  struct MckitsHashMap* map = mckits_hashmap_new();
  mckits_hashmap_set_hashfunc(map, hash_callback);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, compare_callback);
  mckits_hashmap_set_free_key(map, NULL);
  mckits_hashmap_set_free_val(map, NULL);

  int64_t expected_sum = 0;
  int64_t expected_count = 10;
  for (int64_t i = 0; i < expected_count; ++i) {
    mckits_hashmap_insert(map, (void*)i, (void*)i);
    expected_sum += i;
  }

  int64_t sum = 0;
  int64_t count = 0;
  struct MckitsHashMapIter* iter = mckits_hashmap_iterator(map);
  void* value = NULL;
  while (mckits_hashmap_iterator_next(iter, &value)) {
    sum += (int64_t)value;
    count += 1;
  }

  assert(expected_sum == sum);
  assert(expected_count == count);

  mckits_hashmap_iterator_drop(iter);
  mckits_hashmap_drop(map);
}

int main() {
  test01();
  return 0;
}
