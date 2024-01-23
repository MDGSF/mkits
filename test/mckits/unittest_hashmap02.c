#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_hashmap.h"
#include "mckits_string.h"

struct Student {
  struct MckitsString name;
  int age;
};

struct Student* new_student(const char* name, int age) {
  struct Student* stu = (struct Student*)malloc(sizeof(struct Student));
  mckits_string_init(&stu->name, name);
  stu->age = age;
  return stu;
}

uint64_t student_hash(void* key, uint64_t seed0, uint64_t seed1) {
  struct MckitsString* name = (struct MckitsString*)key;
  return mckits_hashmap_hash_func_fnv_1a_64(name->data, name->len, seed0,
                                            seed1);
}

int student_compare(void* keya, void* keyb) {
  struct MckitsString* namea = (struct MckitsString*)keya;
  struct MckitsString* nameb = (struct MckitsString*)keyb;
  return mckits_strcmp(namea->data, nameb->data);
}

void student_free_key(void* key) {
  struct MckitsString* name = (struct MckitsString*)key;
  mckits_string_drop(name);
}

void student_free(void* val) {
  struct Student* stu = (struct Student*)val;
  mckits_string_drop_data(&stu->name);
  free(stu);
}

void test01() {
  struct MckitsHashMap* map = mckits_hashmap_with_capacity(2);
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, student_free_key);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  for (int i = 1; i <= 10000; ++i) {
    struct MckitsString* key = mckits_string_from_int(i);

    char name[1024] = {0};
    sprintf(name, "name_%02d", i);
    struct Student* stu = new_student(name, i);

    mckits_hashmap_insert(map, key, stu);

    assert(mckits_hashmap_len(map) == i);
    assert(mckits_hashmap_is_empty(map) == 0);
  }

  mckits_hashmap_drop(map);
}

void test02() {
  struct MckitsHashMap* map = mckits_hashmap_new();
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, student_free_key);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  static const int max_num = 1000;

  for (int count = 0; count < 100; ++count) {
    for (int i = 1; i <= max_num; ++i) {
      struct MckitsString* key = mckits_string_from_int(i);

      char name[1024] = {0};
      sprintf(name, "name_%02d", i);
      struct Student* stu = new_student(name, i);

      mckits_hashmap_insert(map, key, stu);

      assert(mckits_hashmap_len(map) == i);
      assert(mckits_hashmap_is_empty(map) == 0);
    }

    for (int i = 1; i <= max_num; ++i) {
      struct MckitsString* key = mckits_string_from_int(i);

      char name[1024] = {0};
      sprintf(name, "name_%02d", i);

      struct Student* stu = (struct Student*)mckits_hashmap_remove(map, key);
      assert(stu != NULL);
      assert(mckits_strcmp(stu->name.data, name) == 0);
      assert(stu->age == i);

      assert(mckits_hashmap_len(map) == max_num - i);

      mckits_string_drop(key);
      student_free(stu);
    }

    assert(mckits_hashmap_len(map) == 0);
    assert(mckits_hashmap_is_empty(map) == 1);
  }

  mckits_hashmap_drop(map);
}

void test03() {
  struct MckitsHashMap* map = mckits_hashmap_with_capacity(2);
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, student_free_key);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  for (int i = 1; i <= 10; ++i) {
    struct MckitsString* key = mckits_string_from_int(i);

    char name[1024] = {0};
    sprintf(name, "name_%02d", i);
    struct Student* stu = new_student(name, i);

    mckits_hashmap_insert(map, key, stu);

    assert(mckits_hashmap_len(map) == i);
    assert(mckits_hashmap_is_empty(map) == 0);
  }

  mckits_hashmap_clear(map);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  // insert after clear
  for (int i = 1; i <= 10; ++i) {
    struct MckitsString* key = mckits_string_from_int(i);

    char name[1024] = {0};
    sprintf(name, "name_%02d", i);
    struct Student* stu = new_student(name, i);

    mckits_hashmap_insert(map, key, stu);

    assert(mckits_hashmap_len(map) == i);
    assert(mckits_hashmap_is_empty(map) == 0);
  }

  mckits_hashmap_drop(map);
}

// insert same key
void test04() {
  struct MckitsHashMap* map = mckits_hashmap_with_capacity(2);
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, student_free_key);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  for (int i = 1; i <= 2; ++i) {
    struct MckitsString* key = mckits_string_from_int(123);

    char name[1024] = {0};
    sprintf(name, "name_%02d", i);
    struct Student* stu = new_student(name, i);

    mckits_hashmap_insert(map, key, stu);
  }

  assert(mckits_hashmap_len(map) == 1);
  assert(mckits_hashmap_is_empty(map) == 0);

  char name[1024] = {0};
  sprintf(name, "name_%02d", 2);
  struct MckitsString* key = mckits_string_from_int(123);
  struct Student* stu = mckits_hashmap_get(map, key);
  assert(stu->age == 2);
  assert(mckits_strcmp(name, stu->name.data) == 0);
  mckits_string_drop(key);

  mckits_hashmap_drop(map);
}

// remove not exists key
void test05() {
  struct MckitsHashMap* map = mckits_hashmap_with_capacity(2);
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, student_free_key);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  struct MckitsString* key_not_exists = mckits_string_from_int(123);
  assert(mckits_hashmap_remove(map, key_not_exists) == NULL);
  mckits_string_drop(key_not_exists);

  mckits_hashmap_drop(map);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  return 0;
}
