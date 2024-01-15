#include <assert.h>
#include <pthread.h>
#include <stdio.h>

#include "mckits_spinlock.h"

void test01() {
  struct MckitsSpinlock mtx;
  mckits_spinlock_init(&mtx);
  assert(ATOM_LOAD(&mtx.lock) == 0);

  mckits_spinlock_lock(&mtx);
  assert(ATOM_LOAD(&mtx.lock) == 1);
  mckits_spinlock_unlock(&mtx);
  assert(ATOM_LOAD(&mtx.lock) == 0);

  assert(1 == mckits_spinlock_trylock(&mtx));
  assert(ATOM_LOAD(&mtx.lock) == 1);
  mckits_spinlock_unlock(&mtx);
  assert(ATOM_LOAD(&mtx.lock) == 0);

  assert(1 == mckits_spinlock_trylock(&mtx));
  assert(0 == mckits_spinlock_trylock(&mtx));
  assert(0 == mckits_spinlock_trylock(&mtx));
  assert(ATOM_LOAD(&mtx.lock) == 1);
  mckits_spinlock_unlock(&mtx);
  assert(ATOM_LOAD(&mtx.lock) == 0);
}

struct MckitsSpinlock test02_mtx;
int test02_num = 0;
void* test02_thread_add(void* arg) {
  for (int i = 0; i < 10000; ++i) {
    mckits_spinlock_lock(&test02_mtx);
    test02_num += 1;
    mckits_spinlock_unlock(&test02_mtx);
  }
  pthread_exit(NULL);
}

void test02() {
  pthread_t thread1;
  pthread_t thread2;
  mckits_spinlock_init(&test02_mtx);
  pthread_create(&thread1, NULL, test02_thread_add, NULL);
  pthread_create(&thread2, NULL, test02_thread_add, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  assert(test02_num == 20000);
}

int main() {
  test01();
  test02();
  return 0;
}
