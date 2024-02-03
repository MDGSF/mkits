#include "mckits/mstl/mckits_nlist.h"

static void mckits_nlist_merge(struct MckitsNList* list,
                               struct MckitsNList* tail,
                               int (*cmp)(struct MckitsNList*,
                                          struct MckitsNList*)) {
  struct MckitsNList* q1 = mckits_nlist_head(list);
  struct MckitsNList* q2 = mckits_nlist_head(tail);
  for (;;) {
    if (q1 == mckits_nlist_sentinel(list)) {
      mckits_nlist_add(list, tail);
      break;
    }

    if (q2 == mckits_nlist_sentinel(tail)) {
      break;
    }

    if (cmp(q1, q2) <= 0) {
      q1 = mckits_nlist_next(q1);
      continue;
    }

    mckits_nlist_remove(q2);
    mckits_nlist_insert_before(q1, q2);

    q2 = mckits_nlist_head(tail);
  }
}

struct MckitsNList* mckits_nlist_middle(struct MckitsNList* list) {
  struct MckitsNList* middle = mckits_nlist_head(list);
  if (middle == mckits_nlist_last(list)) {
    return middle;
  }

  struct MckitsNList* next = mckits_nlist_head(list);

  for (;;) {
    middle = mckits_nlist_next(middle);
    next = mckits_nlist_next(next);
    if (next == mckits_nlist_last(list)) {
      return middle;
    }
    next = mckits_nlist_next(next);
    if (next == mckits_nlist_last(list)) {
      return middle;
    }
  }
}

void mckits_nlist_sort(struct MckitsNList* list,
                       int (*cmp)(struct MckitsNList*, struct MckitsNList*)) {
  struct MckitsNList* q = mckits_nlist_head(list);
  if (q == mckits_nlist_last(list)) {
    return;
  }

  struct MckitsNList tail;
  q = mckits_nlist_middle(list);
  mckits_nlist_split(list, q, &tail);
  mckits_nlist_sort(list, cmp);
  mckits_nlist_sort(&tail, cmp);
  mckits_nlist_merge(list, &tail, cmp);
}
