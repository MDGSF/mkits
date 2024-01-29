#include "mckits_vecdeque.h"

#include <string.h>

#include "mckits_malloc.h"

/*
@brief: Return `1` if the buffer is at full capacity.
*/
static inline int mckits_vecdeque_is_full(
    const struct MckitsVecDeque* vecdeque) {
  return vecdeque->size == vecdeque->capacity;
}

static inline size_t mckits_vecdeque_wrap_index(size_t logical_index,
                                                size_t capacity) {
  if (logical_index >= capacity) {
    return logical_index - capacity;
  }
  return logical_index;
}

static inline size_t mckits_vecdeque_wrap_add(struct MckitsVecDeque* vecdeque,
                                              size_t idx, size_t addend) {
  return mckits_vecdeque_wrap_index(idx + addend, vecdeque->capacity);
}

static inline size_t mckits_vecdeque_wrap_sub(struct MckitsVecDeque* vecdeque,
                                              size_t idx, size_t subtrahend) {
  return mckits_vecdeque_wrap_index(idx - subtrahend + vecdeque->capacity,
                                    vecdeque->capacity);
}

static inline size_t mckits_vecdeque_to_physical_idx(
    struct MckitsVecDeque* vecdeque, size_t idx) {
  return mckits_vecdeque_wrap_add(vecdeque, vecdeque->head, idx);
}

struct MckitsVecDeque* mckits_vecdeque_new(size_t element_bytes) {
  struct MckitsVecDeque* vecdeque =
      (struct MckitsVecDeque*)mckits_malloc(sizeof(struct MckitsVecDeque));
  memset(vecdeque, 0, sizeof(struct MckitsVecDeque));
  vecdeque->element_bytes = element_bytes;
  return vecdeque;
}

struct MckitsVecDeque* mckits_vecdeque_with_capacity(size_t element_bytes,
                                                     size_t capacity) {
  struct MckitsVecDeque* vecdeque =
      (struct MckitsVecDeque*)mckits_malloc(sizeof(struct MckitsVecDeque));
  vecdeque->size = 0;
  vecdeque->capacity = capacity;
  vecdeque->element_bytes = element_bytes;
  vecdeque->buffer = mckits_malloc(capacity * element_bytes);
  vecdeque->head = 0;
  return vecdeque;
}

void mckits_vecdeque_init(struct MckitsVecDeque* vecdeque,
                          size_t element_bytes) {
  memset(vecdeque, 0, sizeof(struct MckitsVecDeque));
  vecdeque->element_bytes = element_bytes;
}

void mckits_vecdeque_init_with_capacity(struct MckitsVecDeque* vecdeque,
                                        size_t element_bytes, size_t capacity) {
  vecdeque->size = 0;
  vecdeque->capacity = capacity;
  vecdeque->element_bytes = element_bytes;
  vecdeque->buffer = mckits_malloc(capacity * element_bytes);
  vecdeque->head = 0;
}

void mckits_vecdeque_drop(struct MckitsVecDeque* vecdeque) {
  mckits_vecdeque_clear(vecdeque);
  mckits_free(vecdeque);
}

void mckits_vecdeque_clear(struct MckitsVecDeque* vecdeque) {
  if (vecdeque->buffer == NULL) {
    return;
  }

  mckits_free(vecdeque->buffer);
  vecdeque->buffer = NULL;
  vecdeque->size = 0;
  vecdeque->capacity = 0;
  vecdeque->element_bytes = 0;
  vecdeque->head = 0;
}

size_t mckits_vecdeque_len(const struct MckitsVecDeque* vecdeque) {
  return vecdeque->size;
}

size_t mckits_vecdeque_capacity(const struct MckitsVecDeque* vecdeque) {
  return vecdeque->capacity;
}

int mckits_vecdeque_is_empty(const struct MckitsVecDeque* vecdeque) {
  return vecdeque->size == 0 ? 1 : 0;
}

static void mckits_vecdeque_grow_size(struct MckitsVecDeque* vecdeque) {
  if (NULL == vecdeque->buffer) {
    // deque is empty

    size_t new_capacity = 4;
    size_t new_size = new_capacity * vecdeque->element_bytes;
    void* new_buffer = mckits_malloc(new_size);

    vecdeque->buffer = new_buffer;
    vecdeque->capacity = new_capacity;

  } else if (mckits_vecdeque_is_full(vecdeque)) {
    // deque is full

    size_t new_capacity = 2 * vecdeque->capacity;
    size_t new_size = new_capacity * vecdeque->element_bytes;
    void* new_buffer = mckits_malloc(new_size);

    if (vecdeque->head <= vecdeque->capacity - vecdeque->size) {
      // is contiguous
      memcpy(new_buffer, vecdeque->buffer,
             vecdeque->capacity * vecdeque->element_bytes);
    } else {
      size_t head_len = vecdeque->capacity - vecdeque->head;
      size_t tail_len = vecdeque->size - head_len;

      void* head =
          (uint8_t*)vecdeque->buffer + vecdeque->head * vecdeque->element_bytes;
      size_t head_size = head_len * vecdeque->element_bytes;

      void* tail = vecdeque->buffer;
      size_t tail_size = tail_len * vecdeque->element_bytes;

      memcpy(new_buffer, head, head_size);
      memcpy(new_buffer + head_size, tail, tail_size);
    }

    mckits_free(vecdeque->buffer);
    vecdeque->buffer = new_buffer;
    vecdeque->capacity = new_capacity;
    vecdeque->head = 0;
  }
}

void mckits_vecdeque_push_back(struct MckitsVecDeque* vecdeque, void* value) {
  mckits_vecdeque_grow_size(vecdeque);

  size_t physical_idx =
      mckits_vecdeque_to_physical_idx(vecdeque, vecdeque->size);
  void* element =
      (uint8_t*)vecdeque->buffer + physical_idx * vecdeque->element_bytes;
  memcpy(element, value, vecdeque->element_bytes);
  vecdeque->size += 1;
}

void mckits_vecdeque_push_front(struct MckitsVecDeque* vecdeque, void* value) {
  mckits_vecdeque_grow_size(vecdeque);

  vecdeque->head = mckits_vecdeque_wrap_sub(vecdeque, vecdeque->head, 1);
  void* element =
      (uint8_t*)vecdeque->buffer + vecdeque->head * vecdeque->element_bytes;
  memcpy(element, value, vecdeque->element_bytes);
  vecdeque->size += 1;
}

void mckits_vecdeque_pop_back(struct MckitsVecDeque* vecdeque) {
  if (mckits_vecdeque_is_empty(vecdeque)) {
    return;
  }
  vecdeque->size -= 1;
}

void mckits_vecdeque_pop_front(struct MckitsVecDeque* vecdeque) {
  if (mckits_vecdeque_is_empty(vecdeque)) {
    return;
  }
  vecdeque->head = mckits_vecdeque_to_physical_idx(vecdeque, 1);
  vecdeque->size -= 1;
}

int mckits_vecdeque_get(struct MckitsVecDeque* vecdeque, size_t index,
                        void** value) {
  if (index >= vecdeque->size) {
    return 0;
  }

  size_t idx = mckits_vecdeque_to_physical_idx(vecdeque, index);
  void* element = (uint8_t*)vecdeque->buffer + idx * vecdeque->element_bytes;
  *value = element;
  return 1;
}

int mckits_vecdeque_back(struct MckitsVecDeque* vecdeque, void** value) {
  return mckits_vecdeque_get(vecdeque, vecdeque->size - 1, value);
}

int mckits_vecdeque_front(struct MckitsVecDeque* vecdeque, void** value) {
  return mckits_vecdeque_get(vecdeque, 0, value);
}
