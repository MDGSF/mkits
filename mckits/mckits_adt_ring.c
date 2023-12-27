#include "mckits_adt_ring.h"

#include <stdlib.h>
#include <string.h>

static void mckits_ring_init(struct MckitsRing* ring) {
  ring->next = ring;
  ring->prev = ring;
}

struct MckitsRing* mckits_ring_new(int n) {
  if (n <= 0) {
    return NULL;
  }

  struct MckitsRing* ring =
      (struct MckitsRing*)malloc(sizeof(struct MckitsRing));
  memset(ring, 0, sizeof(struct MckitsRing));

  struct MckitsRing* p = ring;
  for (int i = 1; i < n; ++i) {
    struct MckitsRing* next =
        (struct MckitsRing*)malloc(sizeof(struct MckitsRing));
    memset(next, 0, sizeof(struct MckitsRing));
    next->prev = p;
    p->next = next;
    p = p->next;
  }
  p->next = ring;
  ring->prev = p;
  return ring;
}

void mckits_ring_drop(struct MckitsRing* ring) {
  if (NULL == ring) {
    return;
  }

  struct MckitsRing* p = mckits_ring_next(ring);
  while (p != ring) {
    struct MckitsRing* next = mckits_ring_next(p);
    free(p);
    p = next;
  }
  free(p);
}

struct MckitsRing* mckits_ring_next(struct MckitsRing* ring) {
  if (NULL == ring->next) {
    mckits_ring_init(ring);
  }
  return ring->next;
}

struct MckitsRing* mckits_ring_prev(struct MckitsRing* ring) {
  if (NULL == ring->next) {
    mckits_ring_init(ring);
  }
  return ring->prev;
}

struct MckitsRing* mckits_ring_move(struct MckitsRing* ring, int n) {
  if (NULL == ring->next) {
    mckits_ring_init(ring);
  }
  if (n < 0) {
    for (; n < 0; ++n) {
      ring = ring->prev;
    }
  } else if (n > 0) {
    for (; n > 0; --n) {
      ring = ring->next;
    }
  }
  return ring;
}

struct MckitsRing* mckits_ring_link(struct MckitsRing* r,
                                    struct MckitsRing* s) {
  struct MckitsRing* next = mckits_ring_next(r);
  if (s != NULL) {
    struct MckitsRing* prev = mckits_ring_prev(s);
    r->next = s;
    s->prev = r;
    next->prev = prev;
    prev->next = next;
  }
  return next;
}

struct MckitsRing* mckits_ring_unlink(struct MckitsRing* ring, int n) {
  if (n <= 0) {
    return NULL;
  }
  return mckits_ring_link(ring, mckits_ring_move(ring, n + 1));
}

int mckits_ring_len(struct MckitsRing* ring) {
  if (NULL == ring) {
    return 0;
  }

  int n = 1;
  for (struct MckitsRing* p = mckits_ring_next(ring); p != ring; p = p->next) {
    ++n;
  }
  return n;
}

void mckits_ring_do(struct MckitsRing* ring, void (*f)(void*)) {
  if (NULL == ring) {
    return;
  }
  f(ring->value);
  for (struct MckitsRing* p = mckits_ring_next(ring); p != ring; p = p->next) {
    f(p->value);
  }
}
