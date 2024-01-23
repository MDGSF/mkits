#include <assert.h>
#include <stdio.h>

#include "mckits_hashmap.h"
#include "mckits_mtime.h"
#include "mckits_string.h"

uint64_t hash_callback(void* key, uint64_t seed0, uint64_t seed1) {
  int64_t key_num = (int64_t)key;
  return mckits_hashmap_hash_func_fnv_1a_64(&key_num, sizeof(int64_t), seed0,
                                            seed1);
}

int compare_callback(void* keya, void* keyb) {
  int64_t keya_num = (int64_t)keya;
  int64_t keyb_num = (int64_t)keyb;
  return keya_num < keyb_num;
}

void bench_hashmap_01() {
  static const int64_t test_size = 5000000;

  struct MckitsHashMap* map = mckits_hashmap_new();
  mckits_hashmap_set_hashfunc(map, hash_callback);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, compare_callback);
  mckits_hashmap_set_free_key(map, NULL);
  mckits_hashmap_set_free_val(map, NULL);

  {
    int64_t count = test_size;
    int64_t start = mckits_current_clock_nanoseconds();
    for (int64_t i = 0; i < count; ++i) {
      mckits_hashmap_insert(map, (void*)i, (void*)i);
    }
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    printf(
        "[hashmap] insert diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
        "count/s\n",
        diff, count, (double)diff / (double)count,
        (double)count / ((double)diff / 1000000000));
  }

  {
    int64_t count = test_size;
    int64_t start = mckits_current_clock_nanoseconds();
    for (int64_t i = 0; i < count; ++i) {
      (void)mckits_hashmap_get(map, (void*)i);
    }
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    printf(
        "[hashmap] get diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
        "count/s\n",
        diff, count, (double)diff / (double)count,
        (double)count / ((double)diff / 1000000000));
  }

  {
    int64_t count = test_size;
    int64_t start = mckits_current_clock_nanoseconds();
    for (int64_t i = 0; i < count; ++i) {
      (void)mckits_hashmap_remove(map, (void*)i);
    }
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    printf(
        "[hashmap] remove diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
        "count/s\n",
        diff, count, (double)diff / (double)count,
        (double)count / ((double)diff / 1000000000));
  }

  mckits_hashmap_drop(map);
}

void bench_hashmap_02() {
  static const int64_t test_size = 5000000;

  struct MckitsHashMap* map = mckits_hashmap_with_capacity(test_size);
  mckits_hashmap_set_hashfunc(map, hash_callback);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, compare_callback);
  mckits_hashmap_set_free_key(map, NULL);
  mckits_hashmap_set_free_val(map, NULL);

  {
    int64_t count = test_size;
    int64_t start = mckits_current_clock_nanoseconds();
    for (int64_t i = 0; i < count; ++i) {
      mckits_hashmap_insert(map, (void*)i, (void*)i);
    }
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    printf(
        "[hashmap cap] insert diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
        "count/s\n",
        diff, count, (double)diff / (double)count,
        (double)count / ((double)diff / 1000000000));
  }

  {
    int64_t count = test_size;
    int64_t start = mckits_current_clock_nanoseconds();
    for (int64_t i = 0; i < count; ++i) {
      (void)mckits_hashmap_get(map, (void*)i);
    }
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    printf(
        "[hashmap cap] get diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
        "count/s\n",
        diff, count, (double)diff / (double)count,
        (double)count / ((double)diff / 1000000000));
  }

  {
    int64_t count = test_size;
    int64_t start = mckits_current_clock_nanoseconds();
    for (int64_t i = 0; i < count; ++i) {
      (void)mckits_hashmap_remove(map, (void*)i);
    }
    int64_t end = mckits_current_clock_nanoseconds();
    int64_t diff = end - start;
    printf(
        "[hashmap cap] remove diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
        "count/s\n",
        diff, count, (double)diff / (double)count,
        (double)count / ((double)diff / 1000000000));
  }

  mckits_hashmap_drop(map);
}

int main() {
  bench_hashmap_01();
  bench_hashmap_02();
  return 0;
}
