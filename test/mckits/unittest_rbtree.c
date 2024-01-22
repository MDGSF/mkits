#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits_crc.h"
#include "mckits_malloc.h"
#include "mckits_rbtree.h"
#include "mckits_strconv.h"
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

struct School {
  struct MckitsRbtreeStrNode node;
  int id;
  struct MckitsString name;
};

struct School* new_school(int id, const char* name) {
  struct School* school = (struct School*)mckits_malloc(sizeof(struct School));
  memset(school, 0, sizeof(struct School));

  school->id = id;

  mckits_string_init(&school->name, name);

  uint32_t hash = mckits_crc(school->name.data, school->name.len);
  school->node.node.key = hash;
  mckits_string_init(&school->node.str, name);

  return school;
}

void drop_school(struct School* school) {
  mckits_string_drop_data(&school->name);
  mckits_string_drop_data(&school->node.str);
  mckits_free(school);
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

void test03() {
  struct MckitsRbtree tree;
  struct MckitsRbtreeNode sentinel;
  memset(&tree, 0, sizeof(struct MckitsRbtree));
  memset(&sentinel, 0, sizeof(struct MckitsRbtreeNode));
  mckits_rbtree_sentinel_init(&sentinel);
  mckits_rbtree_init(&tree, &sentinel, mckits_rbtree_insert_str_value);

  struct School* school = new_school(1, "1");
  mckits_rbtree_insert(&tree, &school->node.node);

  drop_school(school);
}

void test04() {
  struct MckitsRbtree tree;
  struct MckitsRbtreeNode sentinel;
  memset(&tree, 0, sizeof(struct MckitsRbtree));
  memset(&sentinel, 0, sizeof(struct MckitsRbtreeNode));
  mckits_rbtree_sentinel_init(&sentinel);
  mckits_rbtree_init(&tree, &sentinel, mckits_rbtree_insert_str_value);

  for (int i = 0; i < 10; ++i) {
    char num_string[128] = {0};
    mckits_int_to_char_string(i, num_string, 128);
    struct School* school = new_school(i, num_string);
    mckits_rbtree_insert(&tree, &school->node.node);
  }

  for (int i = 0; i < 10; ++i) {
    char num_string[128] = {0};
    mckits_int_to_char_string(i, num_string, 128);

    struct MckitsString key;
    mckits_string_init(&key, num_string);

    uint32_t hash = mckits_crc(key.data, key.len);

    struct MckitsRbtreeStrNode* node =
        mckits_rbtree_str_lookup(&tree, &key, hash);
    assert(node != NULL);
    assert(mckits_strcmp(node->str.data, num_string) == 0);

    struct School* school = mckits_rbtree_data(node, struct School, node);
    assert(school->id == i);

    mckits_string_drop_data(&key);
  }

  while (tree.root != tree.sentinel) {
    struct School* school = mckits_rbtree_data(tree.root, struct School, node);
    mckits_rbtree_delete(&tree, tree.root);
    drop_school(school);
  }
}

void test05() {
  struct MckitsRbtree tree;
  struct MckitsRbtreeNode sentinel;
  memset(&tree, 0, sizeof(struct MckitsRbtree));
  memset(&sentinel, 0, sizeof(struct MckitsRbtreeNode));
  mckits_rbtree_sentinel_init(&sentinel);
  mckits_rbtree_init(&tree, &sentinel, mckits_rbtree_insert_value);

  struct Student* stu1 = new_student(1, "1");
  mckits_rbtree_insert(&tree, &stu1->node);

  struct Student* stu2 = new_student(1, "2");
  mckits_rbtree_insert(&tree, &stu2->node);

  struct MckitsRbtreeNode* cur = mckits_rbtree_min(tree.root, tree.sentinel);
  struct Student* student = mckits_rbtree_data(cur, struct Student, node);
  // printf("id: %d, name: %s\n", student->id, student->name.data);
  assert(student->id == 1);

  while ((cur = mckits_rbtree_next(&tree, cur)) != NULL) {
    struct Student* student = mckits_rbtree_data(cur, struct Student, node);
    assert(student->id == 1);
    // printf("id: %d, name: %s\n", student->id, student->name.data);
  }

  drop_student(stu1);
  drop_student(stu2);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  return 0;
}
