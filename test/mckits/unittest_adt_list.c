#include <assert.h>
#include <stdio.h>

#include "mckits_adt_list.h"
#include "mckits_mlibc_utils.h"

void check_list_len(struct MckitsList* list, int expected_len) {
  int listlen = mckits_list_len(list);
  mckits_assert_equal(listlen, expected_len, "list.len() = %d, wanted len = %d",
                      listlen, expected_len);
}

void check_list_pointers(struct MckitsList* list, struct MckitsListNode** nodes,
                         int nodes_len) {
  check_list_len(list, nodes_len);

  if (nodes_len == 0) {
    mckits_assert(list->root.next != NULL, "list->root.next != NULL");
    mckits_assert(list->root.prev != NULL, "list->root.prev != NULL");
    return;
  }

  struct MckitsListNode* root = &list->root;
  for (int i = 0; i < nodes_len; ++i) {
    struct MckitsListNode* node = nodes[i];

    struct MckitsListNode* prev1 = root;
    struct MckitsListNode* prev2 = NULL;
    if (i > 0) {
      prev1 = nodes[i - 1];
      prev2 = prev1;
    }
    mckits_assert(node->prev == prev1, "node->prev == prev1");
    mckits_assert(mckits_list_node_prev(node) == prev2,
                  "mckits_list_node_prev(node) == prev2");

    struct MckitsListNode* next1 = root;
    struct MckitsListNode* next2 = NULL;
    if (i < nodes_len - 1) {
      next1 = nodes[i + 1];
      next2 = next1;
    }
    mckits_assert(node->next == next1, "node->next == next1");
    mckits_assert(mckits_list_node_next(node) == next2,
                  "mckits_list_node_next(node) == next2");
  }
}

void check_list(struct MckitsList* list, void** node_values,
                int node_values_len) {
  check_list_len(list, node_values_len);

  int i = 0;
  struct MckitsListNode* node = mckits_list_front(list);
  while (node != NULL) {
    int64_t left = (int64_t)node->value;
    int64_t right = (int64_t)node_values[i];
    mckits_assert_equal(left, right, "i = %d, %ld, %ld", i, left, right);
    node = mckits_list_node_next(node);
    i += 1;
  }
}

void int_to_void(int64_t iarray[], void* parray[], int size) {
  for (int i = 0; i < size; ++i) {
    parray[i] = (void*)iarray[i];
  }
}

void test01() {
  struct MckitsList* list = mckits_list_new();
  {
    struct MckitsListNode* nodes[0];
    int nodes_len = 0;
    check_list_pointers(list, nodes, nodes_len);
  }

  struct MckitsListNode* node = mckits_list_push_front(list, "a");
  {
    struct MckitsListNode* nodes[] = {node};
    check_list_pointers(list, nodes, 1);
  }

  mckits_list_move_to_front(list, node);
  {
    struct MckitsListNode* nodes[] = {node};
    check_list_pointers(list, nodes, 1);
  }

  mckits_list_move_to_back(list, node);
  {
    struct MckitsListNode* nodes[] = {node};
    check_list_pointers(list, nodes, 1);
  }

  mckits_list_remove(list, node);
  mckits_list_node_drop(node);
  {
    struct MckitsListNode* nodes[0];
    check_list_pointers(list, nodes, 0);
  }

  struct MckitsListNode* n2 = mckits_list_push_front(list, (void*)2);
  struct MckitsListNode* n1 = mckits_list_push_front(list, (void*)1);
  struct MckitsListNode* n3 = mckits_list_push_back(list, (void*)3);
  struct MckitsListNode* n4 = mckits_list_push_back(list, "banana");
  {
    struct MckitsListNode* nodes[] = {n1, n2, n3, n4};
    check_list_pointers(list, nodes, 4);
  }

  mckits_list_remove(list, n2);
  mckits_list_node_drop(n2);
  {
    struct MckitsListNode* nodes[] = {n1, n3, n4};
    check_list_pointers(list, nodes, 3);
  }

  mckits_list_move_to_front(list, n3);
  {
    struct MckitsListNode* nodes[] = {n3, n1, n4};
    check_list_pointers(list, nodes, 3);
  }

  mckits_list_move_to_front(list, n1);
  mckits_list_move_to_back(list, n3);
  {
    struct MckitsListNode* nodes[] = {n1, n4, n3};
    check_list_pointers(list, nodes, 3);
  }

  mckits_list_move_to_front(list, n3);
  {
    struct MckitsListNode* nodes[] = {n3, n1, n4};
    check_list_pointers(list, nodes, 3);
  }
  mckits_list_move_to_front(list, n3);
  {
    struct MckitsListNode* nodes[] = {n3, n1, n4};
    check_list_pointers(list, nodes, 3);
  }

  mckits_list_move_to_back(list, n3);
  {
    struct MckitsListNode* nodes[] = {n1, n4, n3};
    check_list_pointers(list, nodes, 3);
  }
  mckits_list_move_to_back(list, n3);
  {
    struct MckitsListNode* nodes[] = {n1, n4, n3};
    check_list_pointers(list, nodes, 3);
  }

  n2 = mckits_list_insert_before(list, (void*)2, n1);
  check_list_pointers(list, (struct MckitsListNode*[]){n2, n1, n4, n3}, 4);

  mckits_list_remove(list, n2);
  mckits_list_node_drop(n2);
  n2 = mckits_list_insert_before(list, (void*)2, n4);
  check_list_pointers(list, (struct MckitsListNode*[]){n1, n2, n4, n3}, 4);

  mckits_list_remove(list, n2);
  mckits_list_node_drop(n2);
  n2 = mckits_list_insert_before(list, (void*)2, n3);
  check_list_pointers(list, (struct MckitsListNode*[]){n1, n4, n2, n3}, 4);

  mckits_list_remove(list, n2);
  mckits_list_node_drop(n2);
  n2 = mckits_list_insert_after(list, (void*)2, n1);
  check_list_pointers(list, (struct MckitsListNode*[]){n1, n2, n4, n3}, 4);

  mckits_list_remove(list, n2);
  mckits_list_node_drop(n2);
  n2 = mckits_list_insert_after(list, (void*)2, n4);
  check_list_pointers(list, (struct MckitsListNode*[]){n1, n4, n2, n3}, 4);

  mckits_list_remove(list, n2);
  mckits_list_node_drop(n2);
  n2 = mckits_list_insert_after(list, (void*)2, n3);
  check_list_pointers(list, (struct MckitsListNode*[]){n1, n4, n3, n2}, 4);

  mckits_list_drop(list, NULL);
}

void test02() {
  struct MckitsList* list1 = mckits_list_new();
  struct MckitsList* list2 = mckits_list_new();

  mckits_list_push_back(list1, (void*)1);
  mckits_list_push_back(list1, (void*)2);
  mckits_list_push_back(list1, (void*)3);

  mckits_list_push_back(list2, (void*)4);
  mckits_list_push_back(list2, (void*)5);

  {
    struct MckitsList* list3 = mckits_list_new();
    mckits_list_push_back_list(list3, list1);
    {
      int64_t iarray[] = {1, 2, 3};
      void* parray[3];
      int_to_void(iarray, parray, 3);
      check_list(list3, parray, 3);
    }
    mckits_list_push_back_list(list3, list2);
    {
      int64_t iarray[] = {1, 2, 3, 4, 5};
      void* parray[5];
      int_to_void(iarray, parray, 5);
      check_list(list3, parray, 5);
    }
    mckits_list_drop(list3, NULL);
  }

  {
    struct MckitsList* list3 = mckits_list_new();
    mckits_list_push_front_list(list3, list2);
    {
      int64_t iarray[] = {4, 5};
      void* parray[2];
      int_to_void(iarray, parray, 2);
      check_list(list3, parray, 2);
    }
    mckits_list_push_front_list(list3, list1);
    {
      int64_t iarray[] = {1, 2, 3, 4, 5};
      void* parray[5];
      int_to_void(iarray, parray, 5);
      check_list(list3, parray, 5);
    }
    {
      int64_t iarray[] = {1, 2, 3};
      void* parray[3];
      int_to_void(iarray, parray, 3);
      check_list(list1, parray, 3);
    }
    {
      int64_t iarray[] = {4, 5};
      void* parray[2];
      int_to_void(iarray, parray, 2);
      check_list(list2, parray, 2);
    }
    mckits_list_drop(list3, NULL);
  }

  {
    struct MckitsList* list3 = mckits_list_new();
    mckits_list_push_back_list(list3, list1);
    {
      int64_t iarray[] = {1, 2, 3};
      void* parray[3];
      int_to_void(iarray, parray, 3);
      check_list(list3, parray, 3);
    }
    mckits_list_push_back_list(list3, list3);
    {
      int64_t iarray[] = {1, 2, 3, 1, 2, 3};
      void* parray[6];
      int_to_void(iarray, parray, 6);
      check_list(list3, parray, 6);
    }
    mckits_list_drop(list3, NULL);
  }

  {
    struct MckitsList* list3 = mckits_list_new();
    mckits_list_push_front_list(list3, list1);
    {
      int64_t iarray[] = {1, 2, 3};
      void* parray[3];
      int_to_void(iarray, parray, 3);
      check_list(list3, parray, 3);
    }
    mckits_list_push_front_list(list3, list3);
    {
      int64_t iarray[] = {1, 2, 3, 1, 2, 3};
      void* parray[6];
      int_to_void(iarray, parray, 6);
      check_list(list3, parray, 6);
    }
    mckits_list_drop(list3, NULL);
  }

  {
    struct MckitsList* list3 = mckits_list_new();
    mckits_list_push_front_list(list1, list3);
    {
      int64_t iarray[] = {1, 2, 3};
      void* parray[3];
      int_to_void(iarray, parray, 3);
      check_list(list1, parray, 3);
    }
    mckits_list_push_front_list(list1, list3);
    {
      int64_t iarray[] = {1, 2, 3};
      void* parray[3];
      int_to_void(iarray, parray, 3);
      check_list(list1, parray, 3);
    }
    mckits_list_drop(list3, NULL);
  }

  mckits_list_drop(list1, NULL);
  mckits_list_drop(list2, NULL);
}

void test03() {
  struct MckitsList* list = mckits_list_new();
  struct MckitsListNode* n1 = mckits_list_push_back(list, (void*)1);
  struct MckitsListNode* n2 = mckits_list_push_back(list, (void*)2);
  check_list_pointers(list, (struct MckitsListNode*[]){n1, n2}, 2);
  struct MckitsListNode* n = mckits_list_front(list);
  mckits_list_remove(list, n);
  check_list_pointers(list, (struct MckitsListNode*[]){n2}, 1);
  mckits_list_remove(list, n);
  check_list_pointers(list, (struct MckitsListNode*[]){n2}, 1);
  mckits_list_node_drop(n);
  mckits_list_drop(list, NULL);
}

void test04() {
  struct MckitsList* list1 = mckits_list_new();
  mckits_list_push_back(list1, (void*)1);
  mckits_list_push_back(list1, (void*)2);

  struct MckitsList* list2 = mckits_list_new();
  mckits_list_push_back(list2, (void*)3);
  mckits_list_push_back(list2, (void*)4);

  struct MckitsListNode* n = mckits_list_front(list1);
  mckits_list_remove(list2, n);
  assert(mckits_list_len(list2) == 2);

  mckits_list_insert_before(list1, (void*)8, n);
  assert(mckits_list_len(list1) == 3);

  mckits_list_drop(list1, NULL);
  mckits_list_drop(list2, NULL);
}

void test05() {
  struct MckitsList* list1 = mckits_list_new();
  mckits_list_push_back(list1, (void*)1);
  mckits_list_push_back(list1, (void*)2);

  struct MckitsListNode* node = mckits_list_front(list1);
  mckits_list_remove(list1, node);
  assert((int64_t)node->value == (int64_t)1);
  assert(mckits_list_node_next(node) == NULL);
  assert(mckits_list_node_prev(node) == NULL);

  mckits_list_node_drop(node);
  mckits_list_drop(list1, NULL);
}

void test06() {
  struct MckitsList* list1 = mckits_list_new();
  struct MckitsListNode* n1 = mckits_list_push_back(list1, (void*)1);
  struct MckitsListNode* n2 = mckits_list_push_back(list1, (void*)2);
  struct MckitsListNode* n3 = mckits_list_push_back(list1, (void*)3);
  struct MckitsListNode* n4 = mckits_list_push_back(list1, (void*)4);

  mckits_list_move_after(list1, n3, n3);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n2, n3, n4}, 4);
  mckits_list_move_before(list1, n3, n3);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n2, n3, n4}, 4);

  mckits_list_move_after(list1, n3, n2);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n2, n3, n4}, 4);
  mckits_list_move_before(list1, n2, n3);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n2, n3, n4}, 4);

  mckits_list_move_before(list1, n2, n4);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n3, n2, n4}, 4);

  mckits_list_move_before(list1, n4, n1);
  check_list_pointers(list1, (struct MckitsListNode*[]){n4, n1, n3, n2}, 4);

  mckits_list_move_after(list1, n4, n1);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n4, n3, n2}, 4);

  mckits_list_move_after(list1, n2, n3);
  check_list_pointers(list1, (struct MckitsListNode*[]){n1, n4, n3, n2}, 4);

  mckits_list_drop(list1, NULL);
}

void test07() {
  struct MckitsList* list1 = mckits_list_new();
  mckits_list_push_front(list1, (void*)1);
  {
    int64_t iarray[] = {1};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list1, parray, 1);
  }

  struct MckitsList* list2 = mckits_list_new();
  mckits_list_push_back(list2, (void*)1);
  {
    int64_t iarray[] = {1};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list2, parray, 1);
  }

  struct MckitsList* list3 = mckits_list_new();
  mckits_list_push_front_list(list3, list1);
  {
    int64_t iarray[] = {1};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list3, parray, 1);
  }

  struct MckitsList* list4 = mckits_list_new();
  mckits_list_push_back_list(list4, list1);
  {
    int64_t iarray[] = {1};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list4, parray, 1);
  }

  mckits_list_drop(list1, NULL);
  mckits_list_drop(list2, NULL);
  mckits_list_drop(list3, NULL);
  mckits_list_drop(list4, NULL);
}

void test08() {
  struct MckitsList* list1 = mckits_list_new();
  mckits_list_push_back(list1, (void*)1);
  mckits_list_push_back(list1, (void*)2);
  mckits_list_push_back(list1, (void*)3);

  struct MckitsListNode* unknown_node = mckits_list_node_new(NULL);
  mckits_list_insert_before(list1, (void*)123, unknown_node);

  {
    int64_t iarray[] = {1, 2, 3};
    void* parray[3];
    int_to_void(iarray, parray, 3);
    check_list(list1, parray, 3);
  }

  mckits_list_node_drop(unknown_node);
  mckits_list_drop(list1, NULL);
}

void test09() {
  struct MckitsList* list1 = mckits_list_new();
  mckits_list_push_back(list1, (void*)1);
  mckits_list_push_back(list1, (void*)2);
  mckits_list_push_back(list1, (void*)3);

  struct MckitsListNode* unknown_node = mckits_list_node_new(NULL);
  mckits_list_insert_after(list1, (void*)123, unknown_node);

  {
    int64_t iarray[] = {1, 2, 3};
    void* parray[3];
    int_to_void(iarray, parray, 3);
    check_list(list1, parray, 3);
  }

  mckits_list_node_drop(unknown_node);
  mckits_list_drop(list1, NULL);
}

void test10() {
  struct MckitsList* list1 = mckits_list_new();
  struct MckitsListNode* node1 = mckits_list_push_back(list1, (void*)1);

  struct MckitsList* list2 = mckits_list_new();
  struct MckitsListNode* node2 = mckits_list_push_back(list2, (void*)2);

  mckits_list_move_after(list1, node1, node2);
  {
    int64_t iarray[] = {1};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list1, parray, 1);
  }
  {
    int64_t iarray[] = {2};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list2, parray, 1);
  }

  mckits_list_move_before(list1, node1, node2);
  {
    int64_t iarray[] = {1};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list1, parray, 1);
  }
  {
    int64_t iarray[] = {2};
    void* parray[1];
    int_to_void(iarray, parray, 1);
    check_list(list2, parray, 1);
  }

  mckits_list_drop(list1, NULL);
  mckits_list_drop(list2, NULL);
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
  test09();
  test10();
  return 0;
}
