// Inspired by go/src/container/ring
#ifndef MKITS_MCKITS_CORE_MCKITS_ADT_RING_H_
#define MKITS_MCKITS_CORE_MCKITS_ADT_RING_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: A Ring is an element of a circular list, or ring.
Rings do not have a beginning or end; a pointer to any ring element
serves as reference to the entire ring.
*/
struct MckitsRing {
  struct MckitsRing* prev;
  struct MckitsRing* next;
  void* value;
};

/*
@brief: Create a ring of n elements.
*/
struct MckitsRing* mckits_ring_new(int n);

/*
@brief: Drop ring.
@notes: Your must free `value` field firstly if needed, you can call function
  `mckits_ring_do(ring, free)` to free all elements `value` field.
*/
void mckits_ring_drop(struct MckitsRing* ring);

/*
@brief: Returns the next ring element.
*/
struct MckitsRing* mckits_ring_next(struct MckitsRing* ring);

/*
@brief: Returns the previous ring element.
*/
struct MckitsRing* mckits_ring_prev(struct MckitsRing* ring);

/*
@brief: Move next (n > 0), or move prev (n < 0).
@param ring[in]: pointer to any element in ring.
@param n[in]: n steps.
@return pointer to new position.
*/
struct MckitsRing* mckits_ring_move(struct MckitsRing* ring, int n);

/*
@brief: This function is complicated.
If r and s point to the same ring, this function removes the elements between
  r and s from the ring. Return a pointer to the removed subring.
If ring and s point to different rings, this function insert s after r. Return
  a pointer to the element following the last element of s after insertion.
*/
struct MckitsRing* mckits_ring_link(struct MckitsRing* r, struct MckitsRing* s);

/*
@brief: Removes `n % mckits_ring_len(ring)` elements of the ring.
@return: pointer to the removed subring.
*/
struct MckitsRing* mckits_ring_unlink(struct MckitsRing* ring, int n);

/*
@brief: Compute the number of elements in ring.
*/
int mckits_ring_len(struct MckitsRing* ring);

/*
@brief: Call function f on each element of the ring, in forward order.
*/
void mckits_ring_do(struct MckitsRing* ring, void (*f)(void*));

#ifdef __cplusplus
}
#endif

#endif
