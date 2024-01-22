#include "mckits_heap.h"

#include <stdlib.h>
#include <string.h>

static void mckits_heap_swap(struct MckitsHeap* heap, int i, int j) {
  struct MckitsHeapItem* start = (struct MckitsHeapItem*)heap->array.buffer;
  struct MckitsHeapItem* item_i = start + i;
  struct MckitsHeapItem* item_j = start + j;
  struct MckitsHeapItem temp = *item_i;
  *item_i = *item_j;
  *item_j = temp;
}

static int mckits_heap_less(struct MckitsHeap* heap, int i, int j) {
  struct MckitsHeapItem* start = (struct MckitsHeapItem*)heap->array.buffer;
  struct MckitsHeapItem* item_i = start + i;
  struct MckitsHeapItem* item_j = start + j;
  return heap->compare(item_i, item_j) < 0 ? 1 : 0;
}

static void mckits_heap_up(struct MckitsHeap* heap, int j) {
  while (1) {
    int i = (j - 1) / 2;  // parent
    if (i == j || !mckits_heap_less(heap, j, i)) {
      break;
    }
    mckits_heap_swap(heap, i, j);
    j = i;
  }
}

static int mckits_heap_down(struct MckitsHeap* heap, int i0, int n) {
  int i = i0;
  while (1) {
    int j1 = 2 * i + 1;
    if (j1 >= n || j1 < 0) {  // j1 < 0 after int overflow
      break;
    }
    int j = j1;  // left child
    int j2 = j1 + 1;
    if (j2 < n && mckits_heap_less(heap, j2, j1)) {
      j = j2;  // = 2*i + 2  // right child
    }
    if (!mckits_heap_less(heap, j, i)) {
      break;
    }
    mckits_heap_swap(heap, i, j);
    i = j;
  }
  return i > i0 ? 1 : 0;
}

struct MckitsHeap* mckits_heap_new(
    size_t capacity, int (*compare)(const struct MckitsHeapItem* item0,
                                    const struct MckitsHeapItem* item1)) {
  struct MckitsHeap* heap =
      (struct MckitsHeap*)malloc(sizeof(struct MckitsHeap));

  int ret =
      mckits_array_init(&heap->array, capacity, sizeof(struct MckitsHeapItem));
  if (ret != 0) {
    return NULL;
  }

  heap->compare = compare;

  return heap;
}

void mckits_heap_drop(struct MckitsHeap* heap) {
  mckits_array_destroy(&heap->array);
  free(heap);
}

void mckits_heap_heapify(struct MckitsHeap* heap) {
  int n = mckits_heap_len(heap);
  for (int i = n / 2 - 1; i >= 0; --i) {
    mckits_heap_down(heap, i, n);
  }
}

int mckits_heap_len(struct MckitsHeap* heap) { return heap->array.size; }

int mckits_heap_empty(struct MckitsHeap* heap) {
  return mckits_heap_len(heap) == 0 ? 1 : 0;
}

void mckits_heap_push(struct MckitsHeap* heap, void* priority, void* value) {
  struct MckitsHeapItem* item =
      (struct MckitsHeapItem*)mckits_array_push(&heap->array);
  item->priority = priority;
  item->value = value;
  mckits_heap_up(heap, mckits_heap_len(heap) - 1);
}

struct MckitsHeapItem mckits_heap_pop(struct MckitsHeap* heap) {
  int n = mckits_heap_len(heap) - 1;
  mckits_heap_swap(heap, 0, n);
  mckits_heap_down(heap, 0, n);

  struct MckitsHeapItem* start = (struct MckitsHeapItem*)heap->array.buffer;
  struct MckitsHeapItem* last = start + heap->array.size - 1;
  struct MckitsHeapItem ret = *last;
  heap->array.size -= 1;
  return ret;
}

struct MckitsHeapItem mckits_heap_remove(struct MckitsHeap* heap, int i) {
  int n = mckits_heap_len(heap) - 1;
  if (n != i) {
    mckits_heap_swap(heap, i, n);
    if (!mckits_heap_down(heap, i, n)) {
      mckits_heap_up(heap, i);
    }
  }

  struct MckitsHeapItem* start = (struct MckitsHeapItem*)heap->array.buffer;
  struct MckitsHeapItem* last = start + heap->array.size - 1;
  struct MckitsHeapItem ret = *last;
  heap->array.size -= 1;
  return ret;
}

int mckits_heap_compare_int(const struct MckitsHeapItem* item0,
                            const struct MckitsHeapItem* item1) {
  int64_t priority0 = (int64_t)item0->priority;
  int64_t priority1 = (int64_t)item1->priority;
  if (priority0 < priority1) {
    return -1;
  } else if (priority0 > priority1) {
    return 1;
  }
  return 0;
}

int mckits_heap_compare_str(const struct MckitsHeapItem* item0,
                            const struct MckitsHeapItem* item1) {
  const char* s0 = (const char*)item0->priority;
  const char* s1 = (const char*)item1->priority;
  return strcmp(s0, s1);
}

int mckits_heap_max_compare_int(const struct MckitsHeapItem* item0,
                                const struct MckitsHeapItem* item1) {
  int64_t priority0 = (int64_t)item0->priority;
  int64_t priority1 = (int64_t)item1->priority;
  if (priority0 < priority1) {
    return 1;
  } else if (priority0 > priority1) {
    return -1;
  }
  return 0;
}

int mckits_heap_max_compare_str(const struct MckitsHeapItem* item0,
                                const struct MckitsHeapItem* item1) {
  const char* s0 = (const char*)item0->priority;
  const char* s1 = (const char*)item1->priority;
  int ret = strcmp(s0, s1);
  if (ret < 0) {
    return 1;
  } else if (ret > 0) {
    return -1;
  }
  return 0;
}
