#include "mckits_vecdeque.h"

#include <string.h>

#include "mckits_malloc.h"

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
  mckits_vecdeque_drop_data(vecdeque);
  mckits_free(vecdeque);
}

void mckits_vecdeque_drop_data(struct MckitsVecDeque* vecdeque) {
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
