#ifndef MKITS_MCKITS_MSTL_MCKITS_VECTOR_H_
#define MKITS_MCKITS_MSTL_MCKITS_VECTOR_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

/*
@brief: Create a new vector.
@param element_bytes[in]: each element size in byte
*/
struct MckitsVector* mckits_vec_new(size_t element_bytes);

/*
@brief: Create a new vector with capacity.
@param element_bytes[in]: each element size in byte
@param capacity[in]: the new vector's capacity.
*/
struct MckitsVector* mckits_vec_with_capacity(size_t element_bytes,
                                              size_t capacity);

/*
@brief: Initialize vector.
@param element_bytes[in]: each element size in byte
*/
void mckits_vec_init(struct MckitsVector* mvec, size_t element_bytes);

/*
@brief: Initialize vector.
@param element_bytes[in]: each element size in byte
@param capacity[in]: the new vector's capacity.
*/
void mckits_vec_init_with_capacity(struct MckitsVector* mvec,
                                   size_t element_bytes, size_t capacity);

/*
@brief: Drop the vector.
*/
void mckits_vec_drop(struct MckitsVector* mvec);

/*
@brief: Drop the vector's data field, reset the len/cap to zero.
*/
void mckits_vec_drop_data(struct MckitsVector* mvec);

/*
@brief: Returns the number of elements in the vector.
*/
size_t mckits_vec_len(const struct MckitsVector* mvec);

/*
@brief: Returns the total number of elements the vector can hold without
  reallocating.
*/
size_t mckits_vec_capacity(const struct MckitsVector* mvec);

/*
@brief: Check if the vector is empty.
@return:
  1: means vector is empty.
  0: means vector is not empty.
*/
int mckits_vec_is_empty(const struct MckitsVector* mvec);

/*
@brief: Appends an element to the back of vector.
*/
void mckits_vec_push(struct MckitsVector* mvec, void* value);

/*
@brief: Removes the last element from a vector.
*/
void mckits_vec_pop(struct MckitsVector* mvec);

/*
@brief: Get the mvec[index] element.
@return the pointer to the element.
@panics: Panics if index is out of bounds.
*/
void* mckits_vec_get(struct MckitsVector* mvec, size_t index);

/*
@brief: Get the mvec[0] element.
@return the pointer to the element. Or NULL if index is valid.
*/
void* mckits_vec_first(struct MckitsVector* mvec);

/*
@brief: Get the mvec[len - 1] element.
@return the pointer to the element. Or NULL if index is valid.
*/
void* mckits_vec_last(struct MckitsVector* mvec);

/*
@brief: Moves all the elements of other into mvec, leaving other empty.
*/
void mckits_vec_append(struct MckitsVector* mvec, struct MckitsVector* other);

/*
@brief: Clears the vector, removing all values.
@notes: this method has no effect on the allocated capacity of the vector.
*/
void mckits_vec_clear(struct MckitsVector* mvec);

/*
@brief: Returns the pointer to the vector buffer.
*/
void* mckits_vec_as_ptr(struct MckitsVector* mvec);

/*
@brief: Inserts an element at position index within the vector, shifting all
  elements after it to the right.
@panics: Panics if index > len.
*/
void mckits_vec_insert(struct MckitsVector* mvec, size_t index, void* value);

/*
@brief: Removes the element at position index within the vector,
  shifting all elements after it to the left.
@notes: Because this shifts over the remaining elements, it has a worst-case
  performance of O(n).
@panics: Panics if index is out of bounds.
*/
void mckits_vec_remove(struct MckitsVector* mvec, size_t index);

/*
@brief: Removes an element from the vector and returns it.
  The removed element is replaced by the last element of the vector.
  This does not preserve ordering, but is O(1).
@panics: Panics if index is out of bounds.
*/
void mckits_vec_swap_remove(struct MckitsVector* mvec, size_t index);

/*
@brief: Swaps two elements in the vector.
@param a[in]: The index of the first element.
@param b[in]: The index of the second element.
@panics: Panics if a or b is out of bounds.
*/
void mckits_vec_swap(struct MckitsVector* mvec, size_t a, size_t b);

#ifdef __cplusplus
}
#endif

#endif
