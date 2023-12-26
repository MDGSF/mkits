#include "mckits_adt_mpmcqueue.h"

#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

struct MckitsMpmcQueue {
  size_t capacity_;
  void** buffer_;
  atomic_size_t pread_;
  atomic_size_t pwrite_;
  pthread_mutex_t mtx_;
  pthread_cond_t full_;
  pthread_cond_t empty_;
  int stoped_;
  void (*free_node_value_)(void*);
};

struct MckitsMpmcQueue* mckits_mpmcqueue_new(size_t capacity,
                                             void (*free_node_value)(void*)) {
  struct MckitsMpmcQueue* mpmc_queue =
      (struct MckitsMpmcQueue*)malloc(sizeof(struct MckitsMpmcQueue));
  mpmc_queue->capacity_ = capacity;
  mpmc_queue->buffer_ = malloc(sizeof(void**) * capacity);
  atomic_init(&mpmc_queue->pread_, 0);
  atomic_init(&mpmc_queue->pwrite_, 0);
  pthread_mutex_init(&mpmc_queue->mtx_, NULL);
  pthread_cond_init(&mpmc_queue->full_, NULL);
  pthread_cond_init(&mpmc_queue->empty_, NULL);
  mpmc_queue->stoped_ = 0;
  mpmc_queue->free_node_value_ = free_node_value;
  return mpmc_queue;
}

void mckits_mpmcqueue_drop(struct MckitsMpmcQueue* mpmc_queue) {
  mpmc_queue->stoped_ = 1;
  pthread_mutex_destroy(&mpmc_queue->mtx_);
  pthread_cond_destroy(&mpmc_queue->full_);
  pthread_cond_destroy(&mpmc_queue->empty_);
  if (mpmc_queue->free_node_value_ != NULL) {
    while (!mckits_mpmcqueue_empty(mpmc_queue)) {
      size_t idx = atomic_load(&mpmc_queue->pread_) % mpmc_queue->capacity_;
      mpmc_queue->free_node_value_(mpmc_queue->buffer_[idx]);
      atomic_fetch_add(&mpmc_queue->pread_, 1);
    }
  }
  free(mpmc_queue->buffer_);
  free(mpmc_queue);
}

size_t mckits_mpmcqueue_size(struct MckitsMpmcQueue* mpmc_queue) {
  return atomic_load(&mpmc_queue->pwrite_) - atomic_load(&mpmc_queue->pread_);
}

int mckits_mpmcqueue_empty(struct MckitsMpmcQueue* mpmc_queue) {
  return mckits_mpmcqueue_size(mpmc_queue) == 0 ? 1 : 0;
}

int mckits_mpmcqueue_full(struct MckitsMpmcQueue* mpmc_queue) {
  return mckits_mpmcqueue_size(mpmc_queue) >= mpmc_queue->capacity_ ? 1 : 0;
}

int mckits_mpmcqueue_push(struct MckitsMpmcQueue* mpmc_queue, void* value) {
  pthread_mutex_lock(&mpmc_queue->mtx_);
  while (1) {
    if (mpmc_queue->stoped_) {
      pthread_mutex_unlock(&mpmc_queue->mtx_);
      return 0;
    }
    if (mckits_mpmcqueue_full(mpmc_queue)) {
      pthread_cond_wait(&mpmc_queue->full_, &mpmc_queue->mtx_);
    } else {
      break;
    }
  }

  size_t write_index =
      atomic_load(&mpmc_queue->pwrite_) % mpmc_queue->capacity_;
  mpmc_queue->buffer_[write_index] = value;
  atomic_fetch_add(&mpmc_queue->pwrite_, 1);

  pthread_mutex_unlock(&mpmc_queue->mtx_);
  pthread_cond_signal(&mpmc_queue->empty_);

  return 1;
}

void* mckits_mpmcqueue_pop(struct MckitsMpmcQueue* mpmc_queue) {
  pthread_mutex_lock(&mpmc_queue->mtx_);
  while (1) {
    if (mpmc_queue->stoped_) {
      pthread_mutex_unlock(&mpmc_queue->mtx_);
      return NULL;
    }
    if (mckits_mpmcqueue_empty(mpmc_queue)) {
      pthread_cond_wait(&mpmc_queue->empty_, &mpmc_queue->mtx_);
    } else {
      break;
    }
  }

  size_t read_index = atomic_load(&mpmc_queue->pread_) % mpmc_queue->capacity_;
  void* value = mpmc_queue->buffer_[read_index];
  atomic_fetch_add(&mpmc_queue->pread_, 1);

  pthread_mutex_unlock(&mpmc_queue->mtx_);
  pthread_cond_signal(&mpmc_queue->full_);

  return value;
}

void mckits_mpmcqueue_stop(struct MckitsMpmcQueue* mpmc_queue) {
  pthread_mutex_lock(&mpmc_queue->mtx_);
  mpmc_queue->stoped_ = 1;
  pthread_mutex_unlock(&mpmc_queue->mtx_);
  pthread_cond_broadcast(&mpmc_queue->empty_);
  pthread_cond_broadcast(&mpmc_queue->full_);
}
