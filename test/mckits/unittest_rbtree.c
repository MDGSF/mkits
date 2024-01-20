#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits_adt_rbtree.h"
#include "mckits_malloc.h"
#include "mckits_string.h"

struct Student {
  struct MckitsRbtreeNode node;
  int id;
  struct MckitsString name;
};

struct Student* new_student(int id, const char* name) {
  struct Student* student =
      (struct Student*)mckits_malloc(sizeof(struct Student));
  student->id = id;
  mckits_string_init(&student->name, name);
  student->node.key = id;
  return student;
}

void drop_student(struct Student* student) {
  mckits_string_drop_data(&student->name);
  mckits_free(student);
}

void test01() {
  struct MckitsRbtree tree;
  struct MckitsRbtreeNode sentinel;
  memset(&tree, 0, sizeof(struct MckitsRbtree));
  memset(&sentinel, 0, sizeof(struct MckitsRbtreeNode));
  mckits_rbtree_sentinel_init(&sentinel);

  mckits_rbtree_init(&tree, &sentinel, mckits_rbtree_insert_value);

  struct Student* stu1 = new_student(1, "1");
  mckits_rbtree_insert(&tree, &stu1->node);

  drop_student(stu1);
}

void test02() {
  struct MckitsRbtree tree;
  struct MckitsRbtreeNode sentinel;
  memset(&tree, 0, sizeof(struct MckitsRbtree));
  memset(&sentinel, 0, sizeof(struct MckitsRbtreeNode));
  mckits_rbtree_sentinel_init(&sentinel);

  mckits_rbtree_init(&tree, &sentinel, mckits_rbtree_insert_value);

  {
    struct Student* stu = new_student(1, "1");
    mckits_rbtree_insert(&tree, &stu->node);
  }

  {
    struct Student* stu = new_student(2, "2");
    mckits_rbtree_insert(&tree, &stu->node);
  }

  {
    struct Student* stu = new_student(3, "3");
    mckits_rbtree_insert(&tree, &stu->node);
  }

  struct MckitsRbtreeNode* cur = mckits_rbtree_min(tree.root, tree.sentinel);
  assert(cur != NULL);
  struct Student* student = mckits_rbtree_data(cur, struct Student, node);
  assert(student->id == 1);

  int id = 2;
  while ((cur = mckits_rbtree_next(&tree, cur)) != NULL) {
    struct Student* student = mckits_rbtree_data(cur, struct Student, node);
    assert(student->id == id);
    id += 1;
  }

  while (tree.root != tree.sentinel) {
    struct Student* student =
        mckits_rbtree_data(tree.root, struct Student, node);
    mckits_rbtree_delete(&tree, tree.root);
    drop_student(student);
  }
}

int main() {
  test01();
  test02();
  return 0;
}
