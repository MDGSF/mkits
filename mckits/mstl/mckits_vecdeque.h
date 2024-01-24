#ifndef MKITS_MCKITS_MSTL_MCKITS_VECDEQUE_H_
#define MKITS_MCKITS_MSTL_MCKITS_VECDEQUE_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsVecDeque {
  // pointer to array
  void* buffer;
  // the number of elements in buffer. eg. size(), len()
  size_t size;
  // max element buffer can hold. eg. cap(), capacity()
  size_t capacity;
  // each element size in byte
  size_t element_bytes;
  // head of queue
  size_t head;
};

/*
@brief: Create a new VecDeque.
@param element_bytes[in]: each element size in byte
*/
struct MckitsVecDeque* mckits_vecdeque_new(size_t element_bytes);

/*
@brief: Create a new VecDeque with capacity.
@param element_bytes[in]: each element size in byte
@param capacity[in]: the new VecDeque's capacity.
*/
struct MckitsVecDeque* mckits_vecdeque_with_capacity(size_t element_bytes,
                                                     size_t capacity);

/*
@brief: Initialize VecDeque.
@param element_bytes[in]: each element size in byte
*/
void mckits_vecdeque_init(struct MckitsVecDeque* vecdeque,
                          size_t element_bytes);

/*
@brief: Initialize VecDeque.
@param element_bytes[in]: each element size in byte
@param capacity[in]: the new VecDeque's capacity.
*/
void mckits_vecdeque_init_with_capacity(struct MckitsVecDeque* vecdeque,
                                        size_t element_bytes, size_t capacity);

/*
@brief: Drop the VecDeque.
*/
void mckits_vecdeque_drop(struct MckitsVecDeque* vecdeque);

/*
@brief: Drop the VecDeque's data field, reset the len/cap/head to zero.
*/
void mckits_vecdeque_clear(struct MckitsVecDeque* vecdeque);

/*
@brief: Returns the number of elements in the VecDeque.
*/
size_t mckits_vecdeque_len(const struct MckitsVecDeque* vecdeque);

/*
@brief: Returns the total number of elements the VecDeque can hold without
  reallocating.
*/
size_t mckits_vecdeque_capacity(const struct MckitsVecDeque* vecdeque);

/*
@brief: Check if the VecDeque is empty.
@return:
  1: means VecDeque is empty.
  0: means VecDeque is not empty.
*/
int mckits_vecdeque_is_empty(const struct MckitsVecDeque* vecdeque);

/*
@brief: Appends an element to the back of the deque.
*/
void mckits_vecdeque_push_back(struct MckitsVecDeque* vecdeque, void* value);

/*
@brief: Prepends an element to the deque.
*/
void mckits_vecdeque_push_front(struct MckitsVecDeque* vecdeque, void* value);

/*
@brief: Removes the last element from the deque. If deque is empty do nothing.
*/
void mckits_vecdeque_pop_back(struct MckitsVecDeque* vecdeque);

/*
@brief: Removes the first element from the deque. If deque is empty do nothing.
*/
void mckits_vecdeque_pop_front(struct MckitsVecDeque* vecdeque);

/*
@brief: Provides a reference to the element at the given index.
@param vecdeque[in]: VecDeque.
@param index[in]: index of element will be get.
@param value[out]: output data pointer.
@return:
  If index is valid, return 1.
  If index is not valid, return 0.
*/
int mckits_vecdeque_get(struct MckitsVecDeque* vecdeque, size_t index,
                        void** value);

/*
@brief: Provides a reference to the back element.
@param vecdeque[in]: VecDeque.
@param value[out]: output data pointer.
@return:
  If deque is not empty, return 1.
  If deque is empty, return 0, and value will not be touched.
*/
int mckits_vecdeque_back(struct MckitsVecDeque* vecdeque, void** value);

/*
@brief: Provides a reference to the front element.
@param vecdeque[in]: VecDeque.
@param value[out]: output data pointer.
@return:
  If deque is not empty, return 1.
  If deque is empty, return 0, and value will not be touched.
*/
int mckits_vecdeque_front(struct MckitsVecDeque* vecdeque, void** value);

#ifdef __cplusplus
}
#endif

#endif
