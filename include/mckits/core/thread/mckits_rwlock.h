// Inspired by skynet/rwlock.h
#ifndef MKITS_INCLUDE_MCKITS_CORE_THREAD_MCKITS_RWLOCK_H_
#define MKITS_INCLUDE_MCKITS_CORE_THREAD_MCKITS_RWLOCK_H_

#include "mckits/core/thread/mckits_atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsRWLock {
  ATOM_INT write;
  ATOM_INT read;
};

static inline void mckits_rwlock_init(struct MckitsRWLock* lock) {
  ATOM_INIT(&lock->write, 0);
  ATOM_INIT(&lock->read, 0);
}

static inline void mckits_rwlock_rlock(struct MckitsRWLock* lock) {
  for (;;) {
    while (ATOM_LOAD(&lock->write)) {
    }
    ATOM_FINC(&lock->read);
    if (ATOM_LOAD(&lock->write)) {
      ATOM_FDEC(&lock->read);
    } else {
      break;
    }
  }
}

static inline void mckits_rwlock_wlock(struct MckitsRWLock* lock) {
  while (!ATOM_CAS(&lock->write, 0, 1)) {
  }
  while (ATOM_LOAD(&lock->read)) {
  }
}

static inline void mckits_rwlock_wunlock(struct MckitsRWLock* lock) {
  ATOM_STORE(&lock->write, 0);
}

static inline void mckits_rwlock_runlock(struct MckitsRWLock* lock) {
  ATOM_FDEC(&lock->read);
}

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_THREAD_MCKITS_RWLOCK_H_
