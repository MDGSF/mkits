#include "mckits/core/queue/mckits_flowqueue.h"

#include <stdlib.h>

#include "mckits/mstl/mckits_list.h"

struct MckitsFlowQueue {
  size_t capacity_;
  int drop_which_;
  struct MckitsList* list_;
  void (*free_node_value_)(void*);
};

struct MckitsFlowQueue* mckits_flowqueue_new(size_t capacity, int drop_which,
                                             void (*free_node_value)(void*)) {
  struct MckitsFlowQueue* flow_queue =
      (struct MckitsFlowQueue*)malloc(sizeof(struct MckitsFlowQueue));
  flow_queue->capacity_ = capacity;
  flow_queue->drop_which_ = drop_which;
  flow_queue->list_ = mckits_list_new();
  flow_queue->free_node_value_ = free_node_value;
  return flow_queue;
}

void mckits_flowqueue_drop(struct MckitsFlowQueue* flow_queue) {
  mckits_list_drop(flow_queue->list_, flow_queue->free_node_value_);
  free(flow_queue);
}

size_t mckits_flowqueue_size(struct MckitsFlowQueue* flow_queue) {
  return (size_t)mckits_list_len(flow_queue->list_);
}

int mckits_flowqueue_empty(struct MckitsFlowQueue* flow_queue) {
  return mckits_list_len(flow_queue->list_) == 0 ? 1 : 0;
}

int mckits_flowqueue_full(struct MckitsFlowQueue* flow_queue) {
  return mckits_list_len(flow_queue->list_) >= flow_queue->capacity_ ? 1 : 0;
}

int mckits_flowqueue_push(struct MckitsFlowQueue* flow_queue, void* value) {
  if (mckits_flowqueue_full(flow_queue)) {
    if (flow_queue->drop_which_ == 0) {
      struct MckitsListNode* front = mckits_list_front(flow_queue->list_);
      void* front_value = mckits_list_remove(flow_queue->list_, front);
      if (flow_queue->free_node_value_ != NULL) {
        flow_queue->free_node_value_(front_value);
      }
      mckits_list_node_drop(front);
      mckits_list_push_back(flow_queue->list_, value);
      return 1;
    } else {
      return 0;
    }
  } else {
    mckits_list_push_back(flow_queue->list_, value);
    return 1;
  }
}

void* mckits_flowqueue_pop(struct MckitsFlowQueue* flow_queue) {
  if (mckits_flowqueue_empty(flow_queue)) {
    return NULL;
  }

  struct MckitsListNode* front = mckits_list_front(flow_queue->list_);
  void* front_value = mckits_list_remove(flow_queue->list_, front);
  mckits_list_node_drop(front);
  return front_value;
}
