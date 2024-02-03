#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits/mstl/mckits_nlist.h"

typedef struct Student {
  int id;
  char name[128];
  struct MckitsNList list;
} TStudent;

struct Student* new_student(int id, const char* name) {
  struct Student* student = (struct Student*)malloc(sizeof(struct Student));
  memset(student, 0, sizeof(struct Student));
  student->id = id;
  strcpy(student->name, name);
  return student;
}

int compare(struct MckitsNList* nlist1, struct MckitsNList* nlist2) {
  struct Student* ps1 = mckits_nlist_data(nlist1, TStudent, list);
  struct Student* ps2 = mckits_nlist_data(nlist2, TStudent, list);
  return ps1->id > ps2->id;
}

void dump_student_list(struct MckitsNList* list) {
  printf("--------------------------------\n");
  struct MckitsNList* p = mckits_nlist_next(list);
  while (p != list) {
    struct Student* ps = mckits_nlist_data(p, TStudent, list);
    printf("id:%d, name:%s\n", ps->id, ps->name);
    p = mckits_nlist_next(p);
  }
  printf("\n");
}

void test01() {
  struct Student* s1 = new_student(1, "Alice");
  struct Student* s2 = new_student(2, "Bob");
  struct Student* s3 = new_student(3, "John");
  struct Student* s4 = new_student(4, "Mike");

  struct MckitsNList head;
  mckits_nlist_init(&head);
  assert(1 == mckits_nlist_empty(&head));

  mckits_nlist_insert_tail(&head, &s1->list);
  mckits_nlist_insert_tail(&head, &s2->list);
  mckits_nlist_insert_tail(&head, &s3->list);
  mckits_nlist_insert_tail(&head, &s4->list);

  assert(0 == mckits_nlist_empty(&head));

  assert(mckits_nlist_sentinel(&head) == &head);
  assert(mckits_nlist_head(&head) == &s1->list);
  assert(mckits_nlist_last(&head) == &s4->list);

  assert(mckits_nlist_next(&s1->list) == &s2->list);
  assert(mckits_nlist_next(&s2->list) == &s3->list);
  assert(mckits_nlist_next(&s3->list) == &s4->list);

  assert(mckits_nlist_prev(&s4->list) == &s3->list);
  assert(mckits_nlist_prev(&s3->list) == &s2->list);
  assert(mckits_nlist_prev(&s2->list) == &s1->list);

  struct Student* ps1 = mckits_nlist_data(&s1->list, struct Student, list);
  assert(ps1 == s1);

  struct Student* ps2 = mckits_nlist_data(&s2->list, TStudent, list);
  assert(ps2 == s2);
  assert(ps2->id == 2);
  assert(strcmp(ps2->name, "Bob") == 0);

  free(s1);
  free(s2);
  free(s3);
  free(s4);
}

void test02() {
  struct Student* s1 = new_student(1, "Alice");
  struct Student* s2 = new_student(2, "Bob");
  struct Student* s3 = new_student(3, "John");
  struct Student* s4 = new_student(4, "Mike");
  struct Student* s5 = new_student(5, "KangKang");

  struct MckitsNList head;
  mckits_nlist_init(&head);
  assert(1 == mckits_nlist_empty(&head));

  mckits_nlist_insert_head(&head, &s1->list);
  mckits_nlist_insert_head(&head, &s2->list);
  mckits_nlist_insert_head(&head, &s3->list);
  mckits_nlist_insert_head(&head, &s4->list);
  mckits_nlist_insert_head(&head, &s5->list);

  struct MckitsNList* middle = mckits_nlist_middle(&head);
  struct Student* ps3 = mckits_nlist_data(middle, TStudent, list);
  assert(ps3 == s3);
  assert(ps3->id == 3);
  assert(strcmp(ps3->name, "John") == 0);

  assert(mckits_nlist_next(&s5->list) == &s4->list);
  assert(mckits_nlist_next(&s4->list) == &s3->list);
  assert(mckits_nlist_next(&s3->list) == &s2->list);
  assert(mckits_nlist_next(&s2->list) == &s1->list);

  assert(mckits_nlist_prev(&s1->list) == &s2->list);
  assert(mckits_nlist_prev(&s2->list) == &s3->list);
  assert(mckits_nlist_prev(&s3->list) == &s4->list);
  assert(mckits_nlist_prev(&s4->list) == &s5->list);

  mckits_nlist_sort(&head, compare);

  assert(mckits_nlist_next(&s1->list) == &s2->list);
  assert(mckits_nlist_next(&s2->list) == &s3->list);
  assert(mckits_nlist_next(&s3->list) == &s4->list);
  assert(mckits_nlist_next(&s4->list) == &s5->list);

  assert(mckits_nlist_prev(&s5->list) == &s4->list);
  assert(mckits_nlist_prev(&s4->list) == &s3->list);
  assert(mckits_nlist_prev(&s3->list) == &s2->list);
  assert(mckits_nlist_prev(&s2->list) == &s1->list);

  free(s1);
  free(s2);
  free(s3);
  free(s4);
  free(s5);
}

void test03() {
  struct Student* s1 = new_student(1, "Alice");
  struct Student* s2 = new_student(2, "Bob");

  struct MckitsNList head;
  mckits_nlist_init(&head);
  assert(1 == mckits_nlist_empty(&head));

  mckits_nlist_insert_head(&head, &s1->list);
  mckits_nlist_insert_head(&head, &s2->list);

  mckits_nlist_remove(&s1->list);
  assert(mckits_nlist_next(&head) == &s2->list);

  mckits_nlist_remove(&s2->list);
  assert(1 == mckits_nlist_empty(&head));

  free(s1);
  free(s2);
}

void test04() {
  struct Student* s1 = new_student(1, "Alice");
  struct Student* s2 = new_student(2, "Bob");
  struct Student* s3 = new_student(3, "John");
  struct Student* s4 = new_student(4, "Mike");
  struct Student* s5 = new_student(5, "KangKang");

  struct MckitsNList head;
  mckits_nlist_init(&head);
  assert(1 == mckits_nlist_empty(&head));

  mckits_nlist_insert_tail(&head, &s1->list);
  mckits_nlist_insert_tail(&head, &s2->list);
  mckits_nlist_insert_tail(&head, &s3->list);
  mckits_nlist_insert_tail(&head, &s4->list);
  mckits_nlist_insert_tail(&head, &s5->list);

  struct MckitsNList* middle = mckits_nlist_middle(&head);

  struct MckitsNList newhead;
  mckits_nlist_split(&head, middle, &newhead);

  assert(mckits_nlist_head(&head) == &s1->list);
  assert(mckits_nlist_last(&head) == &s2->list);

  assert(mckits_nlist_head(&newhead) == &s3->list);
  assert(mckits_nlist_last(&newhead) == &s5->list);

  mckits_nlist_add(&head, &newhead);

  assert(mckits_nlist_next(&s1->list) == &s2->list);
  assert(mckits_nlist_next(&s2->list) == &s3->list);
  assert(mckits_nlist_next(&s3->list) == &s4->list);
  assert(mckits_nlist_next(&s4->list) == &s5->list);

  free(s1);
  free(s2);
  free(s3);
  free(s4);
  free(s5);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  return 0;
}
