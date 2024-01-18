#ifndef MKITS_MCKITS_MSTL_MCKITS_VECTOR_H_
#define MKITS_MCKITS_MSTL_MCKITS_VECTOR_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MckitsVector;
struct MckitsVector mckits_vec_new(size_t element_bytes);
struct MckitsVector mckits_vec_with_capacity(size_t element_bytes,
                                             size_t capacity);
size_t mckits_vec_len(const struct MckitsVector* mvec);
size_t mckits_vec_capacity(const struct MckitsVector* mvec);
int mckits_vec_is_empty(const struct MckitsVector* mvec);
void mckits_vec_push(struct MckitsVector* mvec, void* value);
void* mckits_vec_pop(struct MckitsVector* mvec);
void* mckits_vec_get(struct MckitsVector* mvec, size_t index);

#ifdef __cplusplus
}
#endif

#endif
