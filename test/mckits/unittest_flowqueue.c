#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mckits/core/queue/mckits_flowqueue.h"

void test01() {
  struct MckitsFlowQueue* flow_queue = mckits_flowqueue_new(10, 0, NULL);
  assert(mckits_flowqueue_size(flow_queue) == 0);
  assert(mckits_flowqueue_empty(flow_queue) == 1);
  assert(mckits_flowqueue_full(flow_queue) == 0);
  assert(mckits_flowqueue_pop(flow_queue) == NULL);

  for (int64_t i = 0; i < 10; ++i) {
    assert(mckits_flowqueue_push(flow_queue, (void*)i) == 1);
    assert(mckits_flowqueue_size(flow_queue) == i + 1);
  }
  assert(mckits_flowqueue_size(flow_queue) == 10);
  assert(mckits_flowqueue_empty(flow_queue) == 0);
  assert(mckits_flowqueue_full(flow_queue) == 1);

  assert(mckits_flowqueue_push(flow_queue, (void*)10) == 1);
  assert(mckits_flowqueue_size(flow_queue) == 10);
  assert(mckits_flowqueue_pop(flow_queue) == (void*)1);
  assert(mckits_flowqueue_size(flow_queue) == 9);
  assert(mckits_flowqueue_full(flow_queue) == 0);

  int64_t expected_value = 2;
  while (!mckits_flowqueue_empty(flow_queue)) {
    int64_t left = (int64_t)mckits_flowqueue_pop(flow_queue);
    int64_t right = expected_value;
    assert(left == right);
    expected_value += 1;
  }

  assert(mckits_flowqueue_size(flow_queue) == 0);
  assert(mckits_flowqueue_empty(flow_queue) == 1);
  assert(mckits_flowqueue_full(flow_queue) == 0);
  assert(mckits_flowqueue_pop(flow_queue) == NULL);

  mckits_flowqueue_drop(flow_queue);
}

void test02() {
  struct MckitsFlowQueue* flow_queue = mckits_flowqueue_new(10, 1, NULL);
  assert(mckits_flowqueue_size(flow_queue) == 0);
  assert(mckits_flowqueue_empty(flow_queue) == 1);
  assert(mckits_flowqueue_full(flow_queue) == 0);

  for (int64_t i = 0; i < 10; ++i) {
    int64_t* value = (int64_t*)malloc(sizeof(int64_t));
    *value = i;
    assert(mckits_flowqueue_push(flow_queue, value) == 1);
    assert(mckits_flowqueue_size(flow_queue) == i + 1);
  }
  assert(mckits_flowqueue_size(flow_queue) == 10);
  assert(mckits_flowqueue_empty(flow_queue) == 0);
  assert(mckits_flowqueue_full(flow_queue) == 1);

  {
    int64_t* value = (int64_t*)malloc(sizeof(int64_t));
    *value = 10;
    assert(mckits_flowqueue_push(flow_queue, value) == 0);
    free(value);
  }
  assert(mckits_flowqueue_size(flow_queue) == 10);
  assert(mckits_flowqueue_empty(flow_queue) == 0);
  assert(mckits_flowqueue_full(flow_queue) == 1);

  int64_t expected_value = 0;
  while (!mckits_flowqueue_empty(flow_queue)) {
    int64_t* left = (int64_t*)mckits_flowqueue_pop(flow_queue);
    int64_t right = expected_value;
    assert(*left == right);
    expected_value += 1;
    free(left);
  }
  assert(mckits_flowqueue_size(flow_queue) == 0);
  assert(mckits_flowqueue_empty(flow_queue) == 1);
  assert(mckits_flowqueue_full(flow_queue) == 0);

  mckits_flowqueue_drop(flow_queue);
}

void free_node_value_callback(void* value) { free(value); }

void test03() {
  struct MckitsFlowQueue* flow_queue =
      mckits_flowqueue_new(10, 1, free_node_value_callback);

  for (int64_t i = 0; i < 10; ++i) {
    int64_t* value = (int64_t*)malloc(sizeof(int64_t));
    *value = i;
    assert(mckits_flowqueue_push(flow_queue, value) == 1);
    assert(mckits_flowqueue_size(flow_queue) == i + 1);
  }

  mckits_flowqueue_drop(flow_queue);
}

void test04() {
  struct MckitsFlowQueue* flow_queue = mckits_flowqueue_new(10, 1, free);

  for (int64_t i = 0; i < 10; ++i) {
    int64_t* value = (int64_t*)malloc(sizeof(int64_t));
    *value = i;
    assert(mckits_flowqueue_push(flow_queue, value) == 1);
    assert(mckits_flowqueue_size(flow_queue) == i + 1);
  }

  mckits_flowqueue_drop(flow_queue);
}

void test05() {
  struct MckitsFlowQueue* flow_queue = mckits_flowqueue_new(1, 0, free);

  for (int64_t i = 0; i < 10; ++i) {
    int64_t* value = (int64_t*)malloc(sizeof(int64_t));
    *value = i;
    assert(mckits_flowqueue_push(flow_queue, value) == 1);
    assert(mckits_flowqueue_size(flow_queue) == 1);
  }

  mckits_flowqueue_drop(flow_queue);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  return 0;
}
