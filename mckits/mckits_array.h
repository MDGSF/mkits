// Inspired by nginx/ngx_array
#ifndef MKITS_MCKITS_MCKITS_ARRAY_H_
#define MKITS_MCKITS_MCKITS_ARRAY_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Dynamic array.
*/
struct MckitsArray {
  // pointer to array
  void* buffer;
  // the number of elements in buffer. eg. size(), len()
  size_t size;
  // max element buffer can hold. eg. cap(), capacity()
  size_t capacity;
  // each element size in byte
  size_t element_bytes;
};

/*
@brief: Init array.
@param array[in]: array will be initialized.
@param capacity[in]: array capacity.
@param element_bytes[in]: each element size in array (byte).
@return:
  On success, return 0.
  On error, -1 is returned, malloc failed.
*/
int mckits_array_init(struct MckitsArray* array, size_t capacity,
                      size_t element_bytes);

/*
@brief: Destroy array. Free array->buffer, and memset array to zero.
*/
void mckits_array_destroy(struct MckitsArray* array);

/*
@brief: Push an new element to array. If array is full, it will automatically
  malloc a new memory block twice as large.
@return: Pointer to new element address. Or NULL if malloc failed.
*/
void* mckits_array_push(struct MckitsArray* array);

/*
@brief: The same as mckits_array_push, except `array->size += n`.
@return: Pointer to first element address. Or NULL if malloc failed.
*/
void* mckits_array_push_n(struct MckitsArray* array, size_t n);

#ifdef __cplusplus
}
#endif

#endif
