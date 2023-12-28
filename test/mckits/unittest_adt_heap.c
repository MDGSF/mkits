#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_adt_heap.h"

void test01() {
  struct MckitsHeap* heap = mckits_heap_new(10, mckits_heap_compare_int);
  assert(0 == mckits_heap_len(heap));

  for (int64_t i = 1; i <= 10; ++i) {
    mckits_heap_push(heap, (void*)i, (void*)i);
    assert(i == mckits_heap_len(heap));
  }

  int64_t i = 1;
  while (!mckits_heap_empty(heap)) {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert((int64_t)item.priority == i);
    assert((int64_t)item.value == i);
    i += 1;
  }

  mckits_heap_drop(heap);
}

void test02() {
  struct MckitsHeap* heap = mckits_heap_new(10, mckits_heap_compare_int);
  assert(0 == mckits_heap_len(heap));

  for (int64_t i = 10; i >= 1; --i) {
    mckits_heap_push(heap, (void*)i, (void*)i);
    assert(10 - i + 1 == mckits_heap_len(heap));
  }

  int64_t i = 1;
  while (!mckits_heap_empty(heap)) {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert((int64_t)item.priority == i);
    assert((int64_t)item.value == i);
    i += 1;
  }

  mckits_heap_drop(heap);
}

void test03() {
  struct MckitsHeap* heap = mckits_heap_new(5, mckits_heap_compare_int);
  assert(0 == mckits_heap_len(heap));

  mckits_heap_push(heap, (void*)3, (void*)3);
  mckits_heap_push(heap, (void*)2, (void*)2);
  mckits_heap_push(heap, (void*)4, (void*)4);
  mckits_heap_push(heap, (void*)5, (void*)5);
  mckits_heap_push(heap, (void*)1, (void*)1);
  assert(5 == mckits_heap_len(heap));

  int64_t i = 1;
  while (!mckits_heap_empty(heap)) {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert((int64_t)item.priority == i);
    assert((int64_t)item.value == i);
    i += 1;
  }

  mckits_heap_drop(heap);
}

struct Student {
  char name[128];
  char phone[128];
  int sex;
  int age;
};

struct Student* new_student(const char* name, const char* phone, int sex,
                            int age) {
  struct Student* student = (struct Student*)malloc(sizeof(struct Student));
  strcpy(student->name, name);
  strcpy(student->phone, phone);
  student->sex = sex;
  student->age = age;
  return student;
}

void test04() {
  struct MckitsHeap* heap = mckits_heap_new(5, mckits_heap_compare_str);
  assert(0 == mckits_heap_len(heap));

  struct Student* s1 = new_student("John", "123000", 1, 18);
  mckits_heap_push(heap, s1->name, s1);

  struct Student* s2 = new_student("Alice", "456000", 0, 19);
  mckits_heap_push(heap, s2->name, s2);

  struct Student* s3 = new_student("Mike", "789000", 1, 20);
  mckits_heap_push(heap, s3->name, s3);

  struct Student* s4 = new_student("Bob", "110119", 1, 21);
  mckits_heap_push(heap, s4->name, s4);

  struct Student* s5 = new_student("Kangkang", "110120", 1, 22);
  mckits_heap_push(heap, s5->name, s5);

  assert(5 == mckits_heap_len(heap));
  assert(0 == mckits_heap_empty(heap));

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Alice") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "456000") == 0);
    assert(student->sex == 0);
    assert(student->age == 19);
    assert(4 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Bob") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "110119") == 0);
    assert(student->sex == 1);
    assert(student->age == 21);
    assert(3 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "John") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "123000") == 0);
    assert(student->sex == 1);
    assert(student->age == 18);
    assert(2 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Kangkang") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "110120") == 0);
    assert(student->sex == 1);
    assert(student->age == 22);
    assert(1 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Mike") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "789000") == 0);
    assert(student->sex == 1);
    assert(student->age == 20);
    assert(0 == mckits_heap_len(heap));
    assert(1 == mckits_heap_empty(heap));
    free(item.value);
  }

  mckits_heap_drop(heap);
}

void test05() {
  struct MckitsHeap* heap = mckits_heap_new(1, mckits_heap_compare_int);
  assert(0 == mckits_heap_len(heap));

  {
    struct MckitsHeapItem* item =
        (struct MckitsHeapItem*)mckits_array_push(&heap->array);
    item->priority = (void*)3;
    item->value = NULL;
  }

  {
    struct MckitsHeapItem* item =
        (struct MckitsHeapItem*)mckits_array_push(&heap->array);
    item->priority = (void*)2;
    item->value = NULL;
  }

  {
    struct MckitsHeapItem* item =
        (struct MckitsHeapItem*)mckits_array_push(&heap->array);
    item->priority = (void*)4;
    item->value = NULL;
  }

  {
    struct MckitsHeapItem* item =
        (struct MckitsHeapItem*)mckits_array_push(&heap->array);
    item->priority = (void*)5;
    item->value = NULL;
  }

  {
    struct MckitsHeapItem* item =
        (struct MckitsHeapItem*)mckits_array_push(&heap->array);
    item->priority = (void*)1;
    item->value = NULL;
  }

  mckits_heap_heapify(heap);

  int64_t i = 1;
  while (!mckits_heap_empty(heap)) {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert((int64_t)item.priority == i);
    i += 1;
  }

  mckits_heap_drop(heap);
}

void test06() {
  struct MckitsHeap* heap = mckits_heap_new(10, mckits_heap_max_compare_int);
  assert(0 == mckits_heap_len(heap));

  for (int64_t i = 1; i <= 10; ++i) {
    mckits_heap_push(heap, (void*)i, (void*)i);
    assert(i == mckits_heap_len(heap));
  }

  int64_t i = 10;
  while (!mckits_heap_empty(heap)) {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert((int64_t)item.priority == i);
    assert((int64_t)item.value == i);
    i -= 1;
  }

  mckits_heap_drop(heap);
}

void test07() {
  struct MckitsHeap* heap = mckits_heap_new(5, mckits_heap_max_compare_str);
  assert(0 == mckits_heap_len(heap));

  struct Student* s1 = new_student("John", "123000", 1, 18);
  mckits_heap_push(heap, s1->name, s1);

  struct Student* s2 = new_student("Alice", "456000", 0, 19);
  mckits_heap_push(heap, s2->name, s2);

  struct Student* s3 = new_student("Mike", "789000", 1, 20);
  mckits_heap_push(heap, s3->name, s3);

  struct Student* s4 = new_student("Bob", "110119", 1, 21);
  mckits_heap_push(heap, s4->name, s4);

  struct Student* s5 = new_student("Kangkang", "110120", 1, 22);
  mckits_heap_push(heap, s5->name, s5);

  assert(5 == mckits_heap_len(heap));
  assert(0 == mckits_heap_empty(heap));

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Mike") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "789000") == 0);
    assert(student->sex == 1);
    assert(student->age == 20);
    assert(4 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Kangkang") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "110120") == 0);
    assert(student->sex == 1);
    assert(student->age == 22);
    assert(3 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "John") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "123000") == 0);
    assert(student->sex == 1);
    assert(student->age == 18);
    assert(2 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Bob") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "110119") == 0);
    assert(student->sex == 1);
    assert(student->age == 21);
    assert(1 == mckits_heap_len(heap));
    assert(0 == mckits_heap_empty(heap));
    free(item.value);
  }

  {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert(strcmp(item.priority, "Alice") == 0);
    struct Student* student = (struct Student*)item.value;
    assert(strcmp(student->phone, "456000") == 0);
    assert(student->sex == 0);
    assert(student->age == 19);
    assert(0 == mckits_heap_len(heap));
    assert(1 == mckits_heap_empty(heap));
    free(item.value);
  }

  mckits_heap_drop(heap);
}

void test08() {
  struct MckitsHeap* heap = mckits_heap_new(10, mckits_heap_compare_int);
  assert(0 == mckits_heap_len(heap));

  for (int64_t i = 1; i <= 10; ++i) {
    mckits_heap_push(heap, (void*)i, (void*)i);
    assert(i == mckits_heap_len(heap));
  }
  assert(10 == mckits_heap_len(heap));

  struct MckitsHeapItem item = mckits_heap_remove(heap, 4);
  assert(9 == mckits_heap_len(heap));

  struct MckitsHeapItem preitem = mckits_heap_pop(heap);
  while (!mckits_heap_empty(heap)) {
    struct MckitsHeapItem item = mckits_heap_pop(heap);
    assert((int64_t)preitem.priority <= (int64_t)item.priority);
  }

  mckits_heap_drop(heap);
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
