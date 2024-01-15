#ifndef MKITS_MCKITS_CORE_QUEUE_MCKITS_ADT_FLOWQUEUE_H_
#define MKITS_MCKITS_CORE_QUEUE_MCKITS_ADT_FLOWQUEUE_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Message queue, not thread safe, fixed queue capacity.
  push behavior when queue is full: drop front or drop back. Non blocking.
  pop behavior when queue is empty: return NULL. Non blocking.
*/
struct MckitsFlowQueue;

/*
@brief: Create a new MckitsFlowQueue.
@param capacity[in]: max size
@param drop_which: 0: head, 1: tail
  When queue is full, and you call push() function to push data into queue.
  `0` means drop the front node, and push new data to backend.
  `1` means drop the new data, do not change the queue.
@param free_node_value: free value callback function, it will be called in
  `mckits_flowqueue_push` function, when drop_which == 0 and queue is full,
  `mckits_flowqueue_push` function will drop front firstly and push back new
  value. If free_node_value is NULL, it will not be called.
*/
struct MckitsFlowQueue* mckits_flowqueue_new(size_t capacity, int drop_which,
                                             void (*free_node_value)(void*));

/*
@brief: Drop flow queue.
*/
void mckits_flowqueue_drop(struct MckitsFlowQueue* flow_queue);

/*
@brief: Returns the queue's size (current element count).
*/
size_t mckits_flowqueue_size(struct MckitsFlowQueue* flow_queue);

/*
@brief: Check if the queue is empty.
@return:
  1: means queue is empty.
  0: means queue is not empty.
*/
int mckits_flowqueue_empty(struct MckitsFlowQueue* flow_queue);

/*
@brief: Check if the queue is full.
@return:
  1: means queue is full.
  0: means queue is not full.
*/
int mckits_flowqueue_full(struct MckitsFlowQueue* flow_queue);

/*
@brief:
  Push a new value into the queue.
  If the queue is full:
    if drop_which == 0 (drop head):
      remove the front value from the queue;
      push the new value to the back of the queue;
      return 1.
    else if drop_which == 1 (drop tail):
      drop the new value;
      the queue is left unchanged;
      return 0.
  else:
    push the new value to the back of the queue;
    return 1.
*/
int mckits_flowqueue_push(struct MckitsFlowQueue* flow_queue, void* value);

/*
@brief: Pop the front value from the queue.
@return: the pointer to the front value. NULL is queue is empty.
*/
void* mckits_flowqueue_pop(struct MckitsFlowQueue* flow_queue);

#ifdef __cplusplus
}
#endif

#endif
