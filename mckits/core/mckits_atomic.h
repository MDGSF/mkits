#ifndef MKITS_MCKITS_CORE_MCKITS_ATOMIC_H_
#define MKITS_MCKITS_CORE_MCKITS_ATOMIC_H_

#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ATOM_INT atomic_int
#define ATOM_POINTER atomic_uintptr_t
#define ATOM_SIZET atomic_size_t
#define ATOM_ULONG atomic_ulong
#define ATOM_INIT(ref, v) atomic_init(ref, v)
#define ATOM_LOAD(ptr) atomic_load(ptr)
#define ATOM_STORE(ptr, v) atomic_store(ptr, v)

static inline int ATOM_CAS(atomic_int *ptr, int oval, int nval) {
  return atomic_compare_exchange_weak(ptr, &(oval), nval);
}

static inline int ATOM_CAS_SIZET(atomic_size_t *ptr, size_t oval, size_t nval) {
  return atomic_compare_exchange_weak(ptr, &(oval), nval);
}

static inline int ATOM_CAS_ULONG(atomic_ulong *ptr, unsigned long oval,
                                 unsigned long nval) {
  return atomic_compare_exchange_weak(ptr, &(oval), nval);
}

static inline int ATOM_CAS_POINTER(atomic_uintptr_t *ptr, uintptr_t oval,
                                   uintptr_t nval) {
  return atomic_compare_exchange_weak(ptr, &(oval), nval);
}

#define ATOM_FINC(ptr) atomic_fetch_add(ptr, 1)
#define ATOM_FDEC(ptr) atomic_fetch_sub(ptr, 1)
#define ATOM_FADD(ptr, n) atomic_fetch_add(ptr, n)
#define ATOM_FSUB(ptr, n) atomic_fetch_sub(ptr, n)
#define ATOM_FAND(ptr, n) atomic_fetch_and(ptr, n)

#ifdef __cplusplus
}
#endif

#endif
