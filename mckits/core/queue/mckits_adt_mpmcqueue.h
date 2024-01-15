#ifndef MKITS_MCKITS_CORE_QUEUE_MCKITS_ADT_MPMCQUEUE_H_
#define MKITS_MCKITS_CORE_QUEUE_MCKITS_ADT_MPMCQUEUE_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Message queue, thread safe, fixed queue capacity.
  Support multi-producer, multi-consumer.
  One message can be comsumed only once.
  push behavior when queue is full: block until queue is not full.
  pop behavior when queue is empty: block until queue is not empty.
*/
struct MckitsMpmcQueue;

/*
@brief: Create a new MckitsMpmcQueue.
@param capacity[in]: max size
@param free_node_value: free value callback function, it will be called in
  `mckits_mpmcqueue_drop` function if it is not NULL.
*/
struct MckitsMpmcQueue* mckits_mpmcqueue_new(size_t capacity,
                                             void (*free_node_value)(void*));

/*
@brief: Drop mpmc queue.
*/
void mckits_mpmcqueue_drop(struct MckitsMpmcQueue* mpmc_queue);

/*
@brief: Returns the queue's size (current element count).
*/
size_t mckits_mpmcqueue_size(struct MckitsMpmcQueue* mpmc_queue);

/*
@brief: Check if the queue is empty.
@return:
  1: means queue is empty.
  0: means queue is not empty.
*/
int mckits_mpmcqueue_empty(struct MckitsMpmcQueue* mpmc_queue);

/*
@brief: Check if the queue is full.
@return:
  1: means queue is full.
  0: means queue is not full.
*/
int mckits_mpmcqueue_full(struct MckitsMpmcQueue* mpmc_queue);

/*
@brief: Push a new value into the queue.
@return:
  1: means push value success.
  0: means queue is already stoped, can not push value into stoped queue.
@notes: When queue is full, push will block until queue is not full.
*/
int mckits_mpmcqueue_push(struct MckitsMpmcQueue* mpmc_queue, void* value);

/*
@brief: Pop a value from the queue.
@return: The pointer to the value. Or NULL if queue is stoped.
@notes: When queue is empty, pop will block until queue is not empty.
*/
void* mckits_mpmcqueue_pop(struct MckitsMpmcQueue* mpmc_queue);

/*
@brief: Stop the queue. When queue is stoped, push and pop function will failed.
  At the same time, blocked push and pop function will return immediately. After
  the queue is stoped, don't forget to call `mckits_mpmcqueue_drop` function to
  free the memory.
*/
void mckits_mpmcqueue_stop(struct MckitsMpmcQueue* mpmc_queue);

#ifdef __cplusplus
}
#endif

#endif
