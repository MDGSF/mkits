#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits/core/mckits_mtime.h"
#include "mckits/core/queue/mckits_adt_mpmcqueue.h"

void test01() {
  struct MckitsMpmcQueue* mpmc_queue = mckits_mpmcqueue_new(10, NULL);
  assert(mckits_mpmcqueue_size(mpmc_queue) == 0);
  assert(mckits_mpmcqueue_empty(mpmc_queue) == 1);
  assert(mckits_mpmcqueue_full(mpmc_queue) == 0);

  for (int64_t i = 1; i <= 10; ++i) {
    assert(1 == mckits_mpmcqueue_push(mpmc_queue, (void*)i));
    assert(mckits_mpmcqueue_size(mpmc_queue) == i);
  }
  assert(mckits_mpmcqueue_size(mpmc_queue) == 10);
  assert(mckits_mpmcqueue_empty(mpmc_queue) == 0);
  assert(mckits_mpmcqueue_full(mpmc_queue) == 1);

  for (int64_t i = 1; i <= 10; ++i) {
    void* pvalue = mckits_mpmcqueue_pop(mpmc_queue);
    assert(pvalue != NULL);
    int64_t value = (int64_t)pvalue;
    assert(value == i);
  }
  assert(mckits_mpmcqueue_size(mpmc_queue) == 0);
  assert(mckits_mpmcqueue_empty(mpmc_queue) == 1);
  assert(mckits_mpmcqueue_full(mpmc_queue) == 0);

  mckits_mpmcqueue_drop(mpmc_queue);
}

void test02() {
  struct MckitsMpmcQueue* mpmc_queue = mckits_mpmcqueue_new(10, NULL);
  mckits_mpmcqueue_stop(mpmc_queue);
  assert(0 == mckits_mpmcqueue_push(mpmc_queue, (void*)10));
  mckits_mpmcqueue_drop(mpmc_queue);
}

void test03() {
  struct MckitsMpmcQueue* mpmc_queue = mckits_mpmcqueue_new(1, free);
  int* val = (int*)malloc(sizeof(int));
  *val = 10;
  assert(1 == mckits_mpmcqueue_push(mpmc_queue, (void*)val));
  mckits_mpmcqueue_drop(mpmc_queue);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
