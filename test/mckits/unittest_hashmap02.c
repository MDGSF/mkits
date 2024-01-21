#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_adt_hashmap.h"
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
  return hash_func_fnv_1a_64(name->data, name->len, seed0, seed1);
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

int main() {
  test01();
  return 0;
}
