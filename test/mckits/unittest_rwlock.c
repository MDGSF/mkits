#include <assert.h>
#include <pthread.h>
#include <stdio.h>

#include "mckits/core/thread/mckits_rwlock.h"

void test01() {
  struct MckitsRWLock mtx;
  mckits_rwlock_init(&mtx);
  assert(ATOM_LOAD(&mtx.write) == 0);
  assert(ATOM_LOAD(&mtx.read) == 0);

  for (int i = 0; i < 10; ++i) {
    mckits_rwlock_rlock(&mtx);
    assert(ATOM_LOAD(&mtx.write) == 0);
    assert(ATOM_LOAD(&mtx.read) == i + 1);
  }

  for (int i = 10; i > 0; --i) {
    mckits_rwlock_runlock(&mtx);
    assert(ATOM_LOAD(&mtx.write) == 0);
    assert(ATOM_LOAD(&mtx.read) == i - 1);
  }

  mckits_rwlock_wlock(&mtx);
  assert(ATOM_LOAD(&mtx.write) == 1);
  assert(ATOM_LOAD(&mtx.read) == 0);

  mckits_rwlock_wunlock(&mtx);
  assert(ATOM_LOAD(&mtx.write) == 0);
  assert(ATOM_LOAD(&mtx.read) == 0);
}

struct MckitsRWLock test02_mtx;
int test02_num = 0;
void* test02_thread_add(void* arg) {
  for (int i = 0; i < 10; ++i) {
    mckits_rwlock_wlock(&test02_mtx);
    test02_num += 1;
    mckits_rwlock_wunlock(&test02_mtx);
  }
  pthread_exit(NULL);
}

void test02() {
  pthread_t thread1;
  pthread_t thread2;
  mckits_rwlock_init(&test02_mtx);
  pthread_create(&thread1, NULL, test02_thread_add, NULL);
  pthread_create(&thread2, NULL, test02_thread_add, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  assert(test02_num == 20);
}

struct MckitsRWLock test03_mtx;
int test03_num = 0;
void* test03_thread_add(void* arg) {
  for (int i = 0; i < 10000; ++i) {
    mckits_rwlock_wlock(&test03_mtx);
    test03_num += 1;
    mckits_rwlock_wunlock(&test03_mtx);
  }
  pthread_exit(NULL);
}

void* test03_thread_read(void* arg) {
  int num = 0;
  for (;;) {
    mckits_rwlock_rlock(&test03_mtx);
    num = test03_num;
    assert(num <= 20000);
    mckits_rwlock_runlock(&test03_mtx);
    if (num == 20000) {
      break;
    }
  }
  pthread_exit(NULL);
}

void test03() {
  pthread_t thread1;
  pthread_t thread2;
  pthread_t thread3;
  mckits_rwlock_init(&test03_mtx);
  pthread_create(&thread1, NULL, test03_thread_add, NULL);
  pthread_create(&thread2, NULL, test03_thread_add, NULL);
  pthread_create(&thread3, NULL, test03_thread_read, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread3, NULL);

  assert(test03_num == 20000);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}
