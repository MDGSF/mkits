#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_adt_mpmcqueue.h"
#include "mckits_mtime.h"

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

struct Test02Context {
  struct MckitsMpmcQueue* mpmc_queue;
  int64_t sleepus;
  int send_number;
};

void* thread_publisher(void* arg) {
  struct Test02Context* ctx = (struct Test02Context*)arg;
  for (int i = 0; i < ctx->send_number; ++i) {
    char* buf = (char*)malloc(1024);
    memset(buf, 0, 1024);
    strcpy(buf, "hello");
    mckits_mpmcqueue_push(ctx->mpmc_queue, buf);
    mckits_sleep_milliseconds(ctx->sleepus);
  }
  pthread_exit(NULL);
}

void* thread_subscriber(void* arg) {
  struct Test02Context* ctx = (struct Test02Context*)arg;
  int count = 0;
  while (1) {
    void* value = mckits_mpmcqueue_pop(ctx->mpmc_queue);
    if (value == NULL) {
      break;
    }
    char* buf = (char*)value;
    assert(strcmp(buf, "hello") == 0);
    free(buf);
    mckits_sleep_milliseconds(ctx->sleepus);
    ++count;
    if (count >= ctx->send_number) {
      break;
    }
  }
  pthread_exit(NULL);
}

void test02() {
  struct MckitsMpmcQueue* mpmc_queue = mckits_mpmcqueue_new(3, NULL);

  pthread_t thread1, thread2;

  struct Test02Context pub_ctx = {mpmc_queue, 10, 10};
  pthread_create(&thread1, NULL, thread_publisher, &pub_ctx);

  struct Test02Context sub_ctx = {mpmc_queue, 30, 10};
  pthread_create(&thread2, NULL, thread_subscriber, &sub_ctx);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  assert(mckits_mpmcqueue_size(mpmc_queue) == 0);
  assert(mckits_mpmcqueue_empty(mpmc_queue) == 1);
  assert(mckits_mpmcqueue_full(mpmc_queue) == 0);
  mckits_mpmcqueue_drop(mpmc_queue);
}

static atomic_size_t test03_subscriber_started_count;
static atomic_size_t test03_subscriber_ended_count;
void* thread_blocked_subscriber(void* arg) {
  struct MckitsMpmcQueue* mpmc_queue = (struct MckitsMpmcQueue*)arg;
  assert(mckits_mpmcqueue_size(mpmc_queue) == 0);
  assert(mckits_mpmcqueue_empty(mpmc_queue) == 1);
  assert(mckits_mpmcqueue_full(mpmc_queue) == 0);

  while (1) {
    atomic_fetch_add(&test03_subscriber_started_count, 1);
    void* value = mckits_mpmcqueue_pop(mpmc_queue);
    if (value == NULL) {
      break;
    }
  }

  atomic_fetch_add(&test03_subscriber_ended_count, 1);
  pthread_exit(NULL);
}

void test03() {
  atomic_init(&test03_subscriber_started_count, 0);
  atomic_init(&test03_subscriber_ended_count, 0);
  struct MckitsMpmcQueue* mpmc_queue = mckits_mpmcqueue_new(3, NULL);

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, thread_blocked_subscriber, mpmc_queue);
  pthread_create(&thread2, NULL, thread_blocked_subscriber, mpmc_queue);

  while (atomic_load(&test03_subscriber_started_count) < 2) {
    mckits_sleep_milliseconds(10);
  }

  while (atomic_load(&test03_subscriber_ended_count) < 2) {
    mckits_mpmcqueue_stop(mpmc_queue);
    mckits_sleep_milliseconds(10);
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  assert(mckits_mpmcqueue_size(mpmc_queue) == 0);
  assert(mckits_mpmcqueue_empty(mpmc_queue) == 1);
  assert(mckits_mpmcqueue_full(mpmc_queue) == 0);
  mckits_mpmcqueue_drop(mpmc_queue);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
