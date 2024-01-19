#ifndef MKITS_MCKITS_MSTL_MCKITS_VECTOR_H_
#define MKITS_MCKITS_MSTL_MCKITS_VECTOR_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsVector;

/*
@brief: Create a new vector.
@param element_bytes[in]: each element size in byte
*/
struct MckitsVector mckits_vec_new(size_t element_bytes);

/*
@brief: Create a new vector with capacity.
@param element_bytes[in]: each element size in byte
@param capacity[in]: the new vector's capacity.
*/
struct MckitsVector mckits_vec_with_capacity(size_t element_bytes,
                                             size_t capacity);

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
@return the pointer to the element. Or NULL if index is valid.
*/
void* mckits_vec_get(struct MckitsVector* mvec, size_t index);

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
@brief: Removes the element at position index within the vector,
  shifting all elements after it to the left.
@notes: Because this shifts over the remaining elements, it has a worst-case
  performance of O(n).
@panics: Panics if index is out of bounds.
*/
void mckits_vec_remove(struct MckitsVector* mvec, size_t index);

#ifdef __cplusplus
}
#endif

#endif
