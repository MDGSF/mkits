#include "mckits/mstl/mckits_vector.h"

#include <assert.h>
#include <string.h>

#include "mckits/mlibc/mckits_malloc.h"
#include "mckits/mstl/mckits_array.h"

struct MckitsVector* mckits_vec_new(size_t element_bytes) {
  struct MckitsVector* mvec =
      (struct MckitsVector*)mckits_malloc(sizeof(struct MckitsVector));
  memset(mvec, 0, sizeof(struct MckitsVector));
  mvec->element_bytes = element_bytes;
  return mvec;
}

struct MckitsVector* mckits_vec_with_capacity(size_t element_bytes,
                                              size_t capacity) {
  struct MckitsVector* mvec =
      (struct MckitsVector*)mckits_malloc(sizeof(struct MckitsVector));
  mvec->size = 0;
  mvec->capacity = capacity;
  mvec->element_bytes = element_bytes;
  mvec->buffer = mckits_malloc(capacity * element_bytes);
  return mvec;
}

void mckits_vec_init(struct MckitsVector* mvec, size_t element_bytes) {
  memset(mvec, 0, sizeof(struct MckitsVector));
  mvec->element_bytes = element_bytes;
}

void mckits_vec_init_with_capacity(struct MckitsVector* mvec,
                                   size_t element_bytes, size_t capacity) {
  mvec->size = 0;
  mvec->capacity = capacity;
  mvec->element_bytes = element_bytes;
  mvec->buffer = mckits_malloc(capacity * element_bytes);
}

void mckits_vec_drop(struct MckitsVector* mvec) {
  mckits_vec_drop_data(mvec);
  mckits_free(mvec);
}

void mckits_vec_drop_data(struct MckitsVector* mvec) {
  if (mvec->buffer == NULL) {
    return;
  }

  mckits_free(mvec->buffer);
  mvec->buffer = NULL;
  mvec->size = 0;
  mvec->capacity = 0;
  mvec->element_bytes = 0;
}

size_t mckits_vec_len(const struct MckitsVector* mvec) { return mvec->size; }

size_t mckits_vec_capacity(const struct MckitsVector* mvec) {
  return mvec->capacity;
}

int mckits_vec_is_empty(const struct MckitsVector* mvec) {
  return mvec->size == 0 ? 1 : 0;
}

static void mckits_vec_grow_size(struct MckitsVector* mvec) {
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
}

void mckits_vec_push(struct MckitsVector* mvec, void* value) {
  mckits_vec_grow_size(mvec);

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

static inline void* mckits_vec_index(struct MckitsVector* mvec, size_t index) {
  return (uint8_t*)mvec->buffer + index * mvec->element_bytes;
}

void* mckits_vec_get(struct MckitsVector* mvec, size_t index) {
  assert(index < mvec->size);
  return mckits_vec_index(mvec, index);
}

void* mckits_vec_first(struct MckitsVector* mvec) {
  return mvec->size == 0 ? NULL : mckits_vec_index(mvec, 0);
}

void* mckits_vec_last(struct MckitsVector* mvec) {
  return mvec->size == 0 ? NULL : mckits_vec_index(mvec, mvec->size - 1);
}

void mckits_vec_append(struct MckitsVector* mvec, struct MckitsVector* other) {
  if (other->size == 0) {
    // other is empty, do nothing.
    return;
  }

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

  mckits_free(other->buffer);
  other->buffer = 0;
  other->size = 0;
  other->capacity = 0;
  other->element_bytes = 0;
}

void mckits_vec_clear(struct MckitsVector* mvec) { mvec->size = 0; }

void* mckits_vec_as_ptr(struct MckitsVector* mvec) { return mvec->buffer; }

void mckits_vec_insert(struct MckitsVector* mvec, size_t index, void* value) {
  assert(index <= mvec->size);

  mckits_vec_grow_size(mvec);

  if (index < mvec->size) {
    void* dst = mckits_vec_index(mvec, index + 1);
    void* src = mckits_vec_index(mvec, index);
    size_t n = (mvec->size - index) * mvec->element_bytes;
    memmove(dst, src, n);
  }

  void* element = mckits_vec_index(mvec, index);
  memcpy(element, value, mvec->element_bytes);
  mvec->size += 1;
}

void mckits_vec_remove(struct MckitsVector* mvec, size_t index) {
  assert(index < mvec->size);

  if (index + 1 < mvec->size) {
    void* dst = mckits_vec_index(mvec, index);
    void* src = mckits_vec_index(mvec, index + 1);
    size_t n = (mvec->size - index - 1) * mvec->element_bytes;
    memmove(dst, src, n);
  }
  mvec->size -= 1;
}

void mckits_vec_swap_remove(struct MckitsVector* mvec, size_t index) {
  assert(index < mvec->size);

  if (index != mvec->size - 1) {
    void* dst = mckits_vec_index(mvec, index);
    void* src = mckits_vec_index(mvec, mvec->size - 1);
    memcpy(dst, src, mvec->element_bytes);
  }

  mvec->size -= 1;
}

void mckits_vec_swap(struct MckitsVector* mvec, size_t a, size_t b) {
  assert(a < mvec->size);
  assert(b < mvec->size);

  if (a == b) {
    return;
  }

  void* temp = mckits_malloc(mvec->element_bytes);
  void* pa = mckits_vec_index(mvec, a);
  void* pb = mckits_vec_index(mvec, b);
  memcpy(temp, pa, mvec->element_bytes);
  memcpy(pa, pb, mvec->element_bytes);
  memcpy(pb, temp, mvec->element_bytes);
  mckits_free(temp);
}
