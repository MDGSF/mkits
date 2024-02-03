// Inspired by skynet/spinlock.h
#ifndef MKITS_MCKITS_CORE_THREAD_MCKITS_SPINLOCK_H_
#define MKITS_MCKITS_CORE_THREAD_MCKITS_SPINLOCK_H_

#include "mckits_atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsSpinlock {
  ATOM_INT lock;
};

static inline void mckits_spinlock_init(struct MckitsSpinlock* lock) {
  ATOM_INIT(&lock->lock, 0);
}

static inline void mckits_spinlock_lock(struct MckitsSpinlock* lock) {
  for (;;) {
    if (!atomic_exchange_explicit(&lock->lock, 1, memory_order_acquire)) {
      return;
    }
    while (atomic_load_explicit(&lock->lock, memory_order_relaxed)) {
    }
  }
}

/*
@brief: Try to lock.
@return:
  1 means get lock success.
  0 means get lock failed.
*/
static inline int mckits_spinlock_trylock(struct MckitsSpinlock* lock) {
  return !atomic_load_explicit(&lock->lock, memory_order_relaxed) &&
         !atomic_exchange_explicit(&lock->lock, 1, memory_order_acquire);
}

static inline void mckits_spinlock_unlock(struct MckitsSpinlock* lock) {
  atomic_store_explicit(&lock->lock, 0, memory_order_release);
}

#ifdef __cplusplus
}
#endif

#endif
