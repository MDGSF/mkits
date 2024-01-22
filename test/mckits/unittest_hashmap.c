#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_hashmap.h"
#include "mckits_string.h"

struct Student {
  struct MckitsStr name;
  int age;
};

struct Student* new_student(struct MckitsStr name, int age) {
  struct Student* stu = (struct Student*)malloc(sizeof(struct Student));
  stu->name = name;
  stu->age = age;
  return stu;
}

uint64_t student_hash(void* key, uint64_t seed0, uint64_t seed1) {
  struct MckitsStr* name = (struct MckitsStr*)key;
  return hash_func_fnv_1a_64(name->data, name->len, seed0, seed1);
}

int student_compare(void* keya, void* keyb) {
  struct MckitsStr* namea = (struct MckitsStr*)keya;
  struct MckitsStr* nameb = (struct MckitsStr*)keyb;
  return mckits_strcmp(namea->data, nameb->data);
}

void student_free(void* val) {
  struct Student* stu = (struct Student*)val;
  free(stu);
}

void test01() {
  struct MckitsHashMap* map = mckits_hashmap_new();
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, NULL);
  mckits_hashmap_set_free_val(map, student_free);
  mckits_hashmap_drop(map);
}

void test02() {
  struct MckitsHashMap* map = mckits_hashmap_new();
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, NULL);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  struct Student* stu =
      new_student((struct MckitsStr)mckits_str("xiaoming"), 18);
  mckits_hashmap_insert(map, &stu->name, stu);

  assert(mckits_hashmap_len(map) == 1);
  assert(mckits_hashmap_is_empty(map) == 0);

  mckits_hashmap_drop(map);
}

void test03() {
  struct MckitsHashMap* map = mckits_hashmap_new();
  mckits_hashmap_set_hashfunc(map, student_hash);
  mckits_hashmap_set_seed0(map, 0);
  mckits_hashmap_set_seed1(map, 0);
  mckits_hashmap_set_compare_func(map, student_compare);
  mckits_hashmap_set_free_key(map, NULL);
  mckits_hashmap_set_free_val(map, student_free);

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  {
    struct Student* stu =
        new_student((struct MckitsStr)mckits_str("xiaoming"), 18);
    mckits_hashmap_insert(map, &stu->name, stu);
  }

  {
    struct Student* stu = new_student((struct MckitsStr)mckits_str("john"), 21);
    mckits_hashmap_insert(map, &stu->name, stu);
  }

  assert(mckits_hashmap_len(map) == 2);
  assert(mckits_hashmap_is_empty(map) == 0);

  {
    struct MckitsStr name = mckits_str("xiaoming");
    struct Student* stu = (struct Student*)mckits_hashmap_get(map, &name);
    assert(stu != NULL);
    assert(mckits_strcmp(stu->name.data, "xiaoming") == 0);
    assert(stu->age == 18);
    assert(mckits_hashmap_contains_key(map, &name) == 1);
  }

  {
    struct MckitsStr name = mckits_str("john");
    struct Student* stu = (struct Student*)mckits_hashmap_get(map, &name);
    assert(stu != NULL);
    assert(mckits_strcmp(stu->name.data, "john") == 0);
    assert(stu->age == 21);
    assert(mckits_hashmap_contains_key(map, &name) == 1);
  }

  {
    struct MckitsStr name = mckits_str("not_exists");
    struct Student* stu = (struct Student*)mckits_hashmap_get(map, &name);
    assert(stu == NULL);
    assert(mckits_hashmap_contains_key(map, &name) == 0);
  }

  {
    struct MckitsStr name = mckits_str("xiaoming");
    struct Student* stu = (struct Student*)mckits_hashmap_remove(map, &name);
    assert(stu != NULL);
    assert(mckits_strcmp(stu->name.data, "xiaoming") == 0);
    assert(stu->age == 18);
    free(stu);
  }

  assert(mckits_hashmap_len(map) == 1);
  assert(mckits_hashmap_is_empty(map) == 0);

  {
    struct MckitsStr name = mckits_str("john");
    struct Student* stu = (struct Student*)mckits_hashmap_remove(map, &name);
    assert(stu != NULL);
    assert(mckits_strcmp(stu->name.data, "john") == 0);
    assert(stu->age == 21);
    free(stu);
  }

  assert(mckits_hashmap_len(map) == 0);
  assert(mckits_hashmap_is_empty(map) == 1);

  mckits_hashmap_clear(map);
  mckits_hashmap_drop(map);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
