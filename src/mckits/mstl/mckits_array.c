#include "mckits/mstl/mckits_array.h"

#include <stdlib.h>
#include <string.h>

int mckits_array_init(struct MckitsArray* array, size_t capacity,
                      size_t element_bytes) {
  array->size = 0;
  array->capacity = capacity;
  array->element_bytes = element_bytes;
  array->buffer = malloc(capacity * element_bytes);
  if (NULL == array->buffer) {
    return -1;
  }
  memset(array->buffer, 0, capacity * element_bytes);
  return 0;
}

void mckits_array_destroy(struct MckitsArray* array) {
  free(array->buffer);
  memset(array, 0, sizeof(struct MckitsArray));
}

void* mckits_array_push(struct MckitsArray* array) {
  if (array->size == array->capacity) {
    // the array is full

    size_t new_capacity = 2 * array->capacity;
    size_t new_size = new_capacity * array->element_bytes;
    void* new_buffer = malloc(new_size);
    if (NULL == new_buffer) {
      return NULL;
    }

    memcpy(new_buffer, array->buffer, array->capacity * array->element_bytes);
    free(array->buffer);
    array->buffer = new_buffer;
    array->capacity = new_capacity;
  }

  void* element = (uint8_t*)array->buffer + array->size * array->element_bytes;
  array->size += 1;

  return element;
}

void* mckits_array_push_n(struct MckitsArray* array, size_t n) {
  if (array->size + n > array->capacity) {
    // the array is full

    size_t new_capacity = 2 * ((n > array->capacity ? n : array->capacity));
    size_t new_size = new_capacity * array->element_bytes;
    void* new_buffer = malloc(new_size);
    if (NULL == new_buffer) {
      return NULL;
    }

    memcpy(new_buffer, array->buffer, array->capacity * array->element_bytes);
    free(array->buffer);
    array->buffer = new_buffer;
    array->capacity = new_capacity;
  }

  void* element = (uint8_t*)array->buffer + array->size * array->element_bytes;
  array->size += n;

  return element;
}
