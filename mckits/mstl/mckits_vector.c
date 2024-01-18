#include "mckits_vector.h"

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
  if (mvec->size == mvec->capacity) {
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

void* mckits_vec_pop(struct MckitsVector* mvec) {
  if (mckits_vec_is_empty(mvec)) {
    return NULL;
  }
  void* element = (uint8_t*)mvec->buffer + mvec->size * mvec->element_bytes;
  mvec->size -= 1;
  return element;
}

void* mckits_vec_get(struct MckitsVector* mvec, size_t index) {
  if (index >= mvec->size) {
    return NULL;
  }
  return (uint8_t*)mvec->buffer + index * mvec->element_bytes;
}
