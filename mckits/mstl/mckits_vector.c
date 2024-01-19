#include "mckits_vector.h"

#include <assert.h>
#include <string.h>

#include "mckits_array.h"
#include "mckits_malloc.h"

struct MckitsVector {
  // pointer to array
  void* buffer;
  // the number of elements in buffer. eg. size(), len()
  size_t size;
  // max element buffer can hold. eg. cap(), capacity()
  size_t capacity;
  // each element size in byte
  size_t element_bytes;
};

struct MckitsVector mckits_vec_new(size_t element_bytes) {
  struct MckitsVector mvec;
  memset(&mvec, 0, sizeof(struct MckitsVector));
  mvec.element_bytes = element_bytes;
  return mvec;
}

struct MckitsVector mckits_vec_with_capacity(size_t element_bytes,
                                             size_t capacity) {
  struct MckitsVector mvec;
  mvec.size = 0;
  mvec.capacity = capacity;
  mvec.element_bytes = element_bytes;
  mvec.buffer = mckits_malloc(capacity * element_bytes);
  return mvec;
}

size_t mckits_vec_len(const struct MckitsVector* mvec) { return mvec->size; }

size_t mckits_vec_capacity(const struct MckitsVector* mvec) {
  return mvec->capacity;
}

int mckits_vec_is_empty(const struct MckitsVector* mvec) {
  return mvec->size == 0 ? 1 : 0;
}

void mckits_vec_push(struct MckitsVector* mvec, void* value) {
  if (mvec->capacity == 0) {
    // vector is empty

    size_t new_capacity = 4;
    size_t new_size = new_capacity * mvec->element_bytes;
    void* new_buffer = mckits_malloc(new_size);

    mvec->buffer = new_buffer;
    mvec->capacity = new_capacity;

  } else if (mvec->size == mvec->capacity) {
    // vector is full

    size_t new_capacity = 2 * mvec->capacity;
    size_t new_size = new_capacity * mvec->element_bytes;
    void* new_buffer = mckits_malloc(new_size);

    memcpy(new_buffer, mvec->buffer, mvec->capacity * mvec->element_bytes);
    mckits_free(mvec->buffer);
    mvec->buffer = new_buffer;
    mvec->capacity = new_capacity;
  }

  void* element = (uint8_t*)mvec->buffer + mvec->size * mvec->element_bytes;
  memcpy(element, value, mvec->element_bytes);
  mvec->size += 1;
}

void mckits_vec_pop(struct MckitsVector* mvec) {
  if (mvec->size == 0) {
    return;
  }
  mvec->size -= 1;
}

void* mckits_vec_get(struct MckitsVector* mvec, size_t index) {
  if (index >= mvec->size) {
    return NULL;
  }
  return (uint8_t*)mvec->buffer + index * mvec->element_bytes;
}

void mckits_vec_append(struct MckitsVector* mvec, struct MckitsVector* other) {
  if (mvec->capacity == 0) {
    // vector is empty

    mvec->buffer = other->buffer;
    mvec->size = other->size;
    mvec->capacity = other->capacity;
    mvec->element_bytes = other->element_bytes;

    other->buffer = 0;
    other->size = 0;
    other->capacity = 0;
    other->element_bytes = 0;

    return;
  }

  if (mvec->size + other->size > mvec->capacity) {
    // vector is full

    size_t new_capacity =
        2 * ((other->size > mvec->capacity ? other->size : mvec->capacity));
    size_t new_size = new_capacity * mvec->element_bytes;
    void* new_buffer = mckits_malloc(new_size);

    memcpy(new_buffer, mvec->buffer, mvec->size * mvec->element_bytes);
    mckits_free(mvec->buffer);
    mvec->buffer = new_buffer;
    mvec->capacity = new_capacity;
  }

  void* element = (uint8_t*)mvec->buffer + mvec->size * mvec->element_bytes;
  memcpy(element, other->buffer, other->size * other->element_bytes);
  mvec->size += other->size;

  other->buffer = 0;
  other->size = 0;
  other->capacity = 0;
  other->element_bytes = 0;
}

void mckits_vec_clear(struct MckitsVector* mvec) { mvec->size = 0; }

void* mckits_vec_as_ptr(struct MckitsVector* mvec) { return mvec->buffer; }

void mckits_vec_remove(struct MckitsVector* mvec, size_t index) {
  assert(index < mvec->size);

  if (index + 1 < mvec->size) {
    void* dst = (uint8_t*)mvec->buffer + index * mvec->element_bytes;
    void* src = (uint8_t*)mvec->buffer + (index + 1) * mvec->element_bytes;
    size_t n = mvec->size - index - 1;
    memmove(dst, src, n);
  }
  mvec->size -= 1;
}
