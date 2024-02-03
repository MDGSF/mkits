// Inspired by skynet/rwlock.h
#ifndef MKITS_INCLUDE_MCKITS_CORE_THREAD_MCKITS_RWLOCKP_H_
#define MKITS_INCLUDE_MCKITS_CORE_THREAD_MCKITS_RWLOCKP_H_

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsRWLockP {
  pthread_rwlock_t lock;
};

static inline void mckits_rwlockp_init(struct MckitsRWLockP* lock) {
  pthread_rwlock_init(&lock->lock, NULL);
}

static inline void mckits_rwlockp_rlock(struct MckitsRWLockP* lock) {
  pthread_rwlock_rdlock(&lock->lock);
}

static inline void mckits_rwlockp_wlock(struct MckitsRWLockP* lock) {
  pthread_rwlock_wrlock(&lock->lock);
}

static inline void mckits_rwlockp_wunlock(struct MckitsRWLockP* lock) {
  pthread_rwlock_unlock(&lock->lock);
}

static inline void mckits_rwlockp_runlock(struct MckitsRWLockP* lock) {
  pthread_rwlock_unlock(&lock->lock);
}

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_THREAD_MCKITS_RWLOCKP_H_
