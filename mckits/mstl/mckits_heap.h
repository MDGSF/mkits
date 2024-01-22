// Inspired by go/src/container/heap
#ifndef MKITS_MCKITS_MSTL_MCKITS_HEAP_H_
#define MKITS_MCKITS_MSTL_MCKITS_HEAP_H_

#include <stddef.h>
#include <stdint.h>

#include "mckits_array.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Heap item stored in array.
*/
struct MckitsHeapItem {
  void* priority;
  void* value;
};

/*
@brief: Heap used to implement a priority queue.
*/
struct MckitsHeap {
  // array used to store `MckitsHeapItem`
  struct MckitsArray array;
  // compare function
  int (*compare)(const struct MckitsHeapItem* item0,
                 const struct MckitsHeapItem* item1);
};

/*
@brief: Create a new heap.
@param capacity[in]: heap initialize capacity. If buffer is not enough, it will
  automatically extend.
@param compare[in]: compare function.
*/
struct MckitsHeap* mckits_heap_new(
    size_t capacity, int (*compare)(const struct MckitsHeapItem* item0,
                                    const struct MckitsHeapItem* item1));

/*
@brief: Drop the heap. User must free `MckitsHeapItem` manually.
*/
void mckits_heap_drop(struct MckitsHeap* heap);

/*
@brief: Heapify a array.
  The complexity is O(n), where n = mckits_heap_len(heap).
*/
void mckits_heap_heapify(struct MckitsHeap* heap);

/*
@brief: Returns the number of element in heap.
*/
int mckits_heap_len(struct MckitsHeap* heap);

/*
@brief: Check if the heap is empty.
@return:
  1: means queue is empty.
  0: means queue is not empty.
*/
int mckits_heap_empty(struct MckitsHeap* heap);

/*
@brief: Push new value to heap with priority.
  The complexity is O(logn), where n = mckits_heap_len(heap).
@param heap[in]: heap
@param priority[in]: value's priority.
@param value[in]: new value.
*/
void mckits_heap_push(struct MckitsHeap* heap, void* priority, void* value);

/*
@brief: Pop a value from heap. Heap must not be empty.
  The complexity is O(logn), where n = mckits_heap_len(heap).
*/
struct MckitsHeapItem mckits_heap_pop(struct MckitsHeap* heap);

/*
@brief: Removes and returns the element at index i.
  The complexity is O(logn), where n = mckits_heap_len(heap).
*/
struct MckitsHeapItem mckits_heap_remove(struct MckitsHeap* heap, int i);

/*
@brief: Compare callback, `(int64_t)item->priority`. Use this compare function,
  it will be min heap.
@return:
  item0 <  item1: return -1
  item0 >  item1: return 1
  item0 == item1: return 0
*/
int mckits_heap_compare_int(const struct MckitsHeapItem* item0,
                            const struct MckitsHeapItem* item1);

/*
@brief: Compare callback, `(char*)item->priority`. Use strcmp to compare.
  Use this compare function, it will be min heap.
@return:
  item0 <  item1: return -1
  item0 >  item1: return 1
  item0 == item1: return 0
*/
int mckits_heap_compare_str(const struct MckitsHeapItem* item0,
                            const struct MckitsHeapItem* item1);

/*
@brief: Compare callback, `(int64_t)item->priority`. Use this compare function,
  it will be max heap.
@return:
  item0 <  item1: return 1
  item0 >  item1: return -1
  item0 == item1: return 0
*/
int mckits_heap_max_compare_int(const struct MckitsHeapItem* item0,
                                const struct MckitsHeapItem* item1);

/*
@brief: Compare callback, `(char*)item->priority`. Use strcmp to compare.
  Use this compare function, it will be max heap.
@return:
  item0 <  item1: return 1
  item0 >  item1: return -1
  item0 == item1: return 0
*/
int mckits_heap_max_compare_str(const struct MckitsHeapItem* item0,
                                const struct MckitsHeapItem* item1);

#ifdef __cplusplus
}
#endif

#endif
