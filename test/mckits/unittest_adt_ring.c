#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits_adt_ring.h"

void verify(struct MckitsRing* r, int N, int64_t sum) {
  assert(mckits_ring_len(r) == N);

  int n = 0;
  int64_t s = 0;
  if (r != NULL) {
    n = 1;
    s = (int64_t)r->value;
    for (struct MckitsRing* p = mckits_ring_next(r); p != r; p = p->next) {
      ++n;
      s += (int64_t)p->value;
    }
  }
  assert(n == N);
  if (sum >= 0) {
    assert(s == sum);
  }

  if (r == NULL) {
    return;
  }

  if (r->next != NULL) {
    struct MckitsRing* p = NULL;
    struct MckitsRing* q = r;
    for (; p == NULL || q != r; q = q->next) {
      assert(p == NULL || p == q->prev);
      p = q;
    }
    assert(p == r->prev);
  }

  assert(mckits_ring_next(r) == r->next);
  assert(mckits_ring_prev(r) == r->prev);

  assert(mckits_ring_move(r, 0) == r);
  assert(mckits_ring_move(r, N) == r);
  assert(mckits_ring_move(r, -N) == r);
  for (int i = 0; i < 10; ++i) {
    int ni = N + 1;
    int mi = ni % N;
    assert(mckits_ring_move(r, ni) == mckits_ring_move(r, mi));
    assert(mckits_ring_move(r, -ni) == mckits_ring_move(r, -mi));
  }
}

void test01() {
  struct MckitsRing* r0 = NULL;
  struct MckitsRing r1;
  memset(&r1, 0, sizeof(struct MckitsRing));

  verify(r0, 0, 0);
  verify(&r1, 1, 0);

  mckits_ring_link(&r1, r0);
  verify(r0, 0, 0);
  verify(&r1, 1, 0);

  mckits_ring_link(&r1, r0);
  verify(r0, 0, 0);
  verify(&r1, 1, 0);

  mckits_ring_unlink(&r1, 0);
  verify(&r1, 1, 0);
}

struct MckitsRing* makeN(int64_t n) {
  struct MckitsRing* r = mckits_ring_new(n);
  for (int64_t i = 1; i <= n; ++i) {
    r->value = (void*)i;
    r = mckits_ring_next(r);
  }
  return r;
}

int64_t sumN(int64_t n) { return (n * n + n) / 2; }

void test02() {
  for (int i = 0; i < 10; ++i) {
    struct MckitsRing* r = mckits_ring_new(i);
    verify(r, i, -1);
    mckits_ring_drop(r);
  }
  for (int i = 0; i < 10; ++i) {
    struct MckitsRing* r = makeN(i);
    verify(r, i, sumN(i));
    mckits_ring_drop(r);
  }
}

void test03() {
  struct MckitsRing* r1a = makeN(1);
  struct MckitsRing r1b;
  memset(&r1b, 0, sizeof(struct MckitsRing));
  struct MckitsRing* r2a = mckits_ring_link(r1a, &r1b);
  verify(r2a, 2, 1);
  assert(r2a == r1a);

  struct MckitsRing* r2b = mckits_ring_link(r2a, mckits_ring_next(r2a));
  verify(r2b, 2, 1);
  assert(r2b == mckits_ring_next(r2a));

  struct MckitsRing* r1c = mckits_ring_link(r2b, r2b);
  verify(r1c, 1, 1);
  verify(r2b, 1, 0);

  mckits_ring_drop(r1c);
}

void test04() {
  struct MckitsRing* r0 = NULL;
  struct MckitsRing r1a;
  memset(&r1a, 0, sizeof(struct MckitsRing));
  r1a.value = (void*)42;
  struct MckitsRing r1b;
  memset(&r1b, 0, sizeof(struct MckitsRing));
  r1b.value = (void*)77;
  struct MckitsRing* r10 = makeN(10);

  mckits_ring_link(&r1a, r0);
  verify(&r1a, 1, 42);

  mckits_ring_link(&r1a, &r1b);
  verify(&r1a, 2, 42 + 77);

  mckits_ring_link(r10, r0);
  verify(r10, 10, sumN(10));

  mckits_ring_link(r10, &r1a);
  verify(r10, 12, sumN(10) + 42 + 77);

  mckits_ring_unlink(mckits_ring_prev(&r1a), 2);
  mckits_ring_drop(r10);
}

void test05() {
  struct MckitsRing* r = mckits_ring_new(1);
  int64_t n = 1;
  for (int i = 1; i < 10; ++i) {
    n += i;
    verify(mckits_ring_link(r, mckits_ring_new(i)), n, -1);
  }
  mckits_ring_drop(r);
}

void test06() {
  struct MckitsRing* r10 = makeN(10);
  struct MckitsRing* s10 = mckits_ring_move(r10, 6);
  int64_t sum10 = sumN(10);

  verify(r10, 10, sum10);
  verify(s10, 10, sum10);

  struct MckitsRing* r0 = mckits_ring_unlink(r10, 0);
  verify(r0, 0, 0);

  struct MckitsRing* r1 = mckits_ring_unlink(r10, 1);
  verify(r1, 1, 2);
  verify(r10, 9, sum10 - 2);

  struct MckitsRing* r9 = mckits_ring_unlink(r10, 9);
  verify(r9, 9, sum10 - 2);
  verify(r10, 9, sum10 - 2);

  mckits_ring_drop(r1);
  mckits_ring_drop(r10);
}

void test07() {
  for (int i = 1; i < 4; ++i) {
    struct MckitsRing* ri = mckits_ring_new(i);
    for (int j = 0; j < i; ++j) {
      struct MckitsRing* rj = mckits_ring_unlink(ri, j);
      verify(rj, j, -1);
      verify(ri, i - j, -1);
      mckits_ring_link(ri, rj);
      verify(ri, i, -1);
    }
    mckits_ring_drop(ri);
  }
}

void test08() {
  struct MckitsRing r;
  memset(&r, 0, sizeof(struct MckitsRing));

  mckits_ring_move(&r, 1);
  verify(&r, 1, 0);
}

int main() {
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
  test08();
  return 0;
}
